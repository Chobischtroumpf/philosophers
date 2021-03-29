/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessandro <alessandro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 14:14:46 by adorigo           #+#    #+#             */
/*   Updated: 2021/03/29 15:57:27 by alessandro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*monitor_count(void *context_void)
{
	t_context	*context;
	int			i;

	i = 0;
	context = (t_context*)context_void;
	while (i < context->amount)
	{
		if (sem_wait(context->sem_eaten_enough) == -1)
		{
			exit_error("sem_wait error\n");
			return ((void *) 0);
		}
		i++;
	}
	ft_usleep(context->time_to_sleep);
	print(&context->philo[0], FINISHED);
	sem_wait(context->sem_exit_thread);
	context->exit_thread = 1;
	sem_post(context->sem_exit_thread);
	sem_post(context->sem_philo_dead);
	return ((void*) 0);
}

void	*monitor(void *context_void)
{
	t_context	*cxt;
	int			i;

	cxt = (t_context*)context_void;
	while (1)
	{
		i = -1;
		while (++i < cxt->amount)
		{
			if (cxt->exit_thread)
				return ((void*) 0);
			sem_wait(cxt->philo[i].mutex);
			if (get_time() > cxt->philo[i].time_limit)
			{
				print(&cxt->philo[i], DYING);
				sem_wait(cxt->sem_exit_thread);
				cxt->exit_thread = 1;
				sem_post(cxt->sem_exit_thread);
				sem_post(cxt->sem_philo_dead);
				return ((void*) 0);
			}
			sem_post(cxt->philo[i].mutex);
		}
	}
}

void	*routine(void *philo_void)
{
	t_philo		*philo;

	philo = (t_philo*)philo_void;
	philo->last_time_ate = philo->context->start;
	philo->time_limit = philo->last_time_ate + philo->context->time_to_die;
	while (1)
	{
		if (philo->eat_count == philo->context->must_eat_count)
			sem_post(philo->context->sem_eaten_enough);
		if (philo->context->exit_thread)
			break ;
		print(philo, THINKING);
		eating(philo);
	}
	return ((void *) 0);
}

static int	start_process(t_context *context)
{
	int			i;
	void		*philo;
	pthread_t	tid;
	context->start = get_time();
	i = 0;
	while (i < context->amount)
	{
		philo = (void*)(&context->philo[i++]);
		context->philo[i].pid = fork();
		if (context->philo[i].pid < 0)
			return (1);
		else if (context->philo[i].pid == 0)
		{
			routine(&context->philo[i]);
			exit(0);
		}
		usleep(20);
		i++;
	}
	if (context->must_eat_count > 0)
	{
		if (pthread_create(&tid, NULL, &monitor_count, (void *)context) != 0)
			return (1);
		pthread_detach(tid);
	}
	if (pthread_create(&tid, NULL, &monitor, (void *)context) != 0)
		return (1);
	pthread_detach(tid);
	return (0);
}

int	main(int argc, char **argv)
{
	t_context	cxt;
	int			i;

	if (argc < 5 || argc > 6)
		return (exit_error("error: wrong amount of args\n"));
	if (init(&cxt, argc, argv) || start_process(&cxt))
		return (ft_clear_context(&cxt) && exit_error("fatal error\n"));
	sem_wait(cxt.sem_philo_dead);
	i = 0;
	while (i < cxt.amount)
		kill(cxt.philo[i++].pid, SIGKILL);
	ft_usleep((cxt.time_to_die + cxt.time_to_eat + cxt.time_to_sleep) * 1.1);
	ft_clear_context(&cxt);
}
