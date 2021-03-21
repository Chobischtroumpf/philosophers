/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 14:14:46 by adorigo           #+#    #+#             */
/*   Updated: 2021/03/21 15:58:37 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	*monitor_count(void *context_void)
{
	t_context	*context;
	int			i;

	i = 0;
	context = (t_context*)context_void;
	while (i < context->amount)
	{
		if (sem_wait(context->philo[i++].sem_eaten_enough) == -1)
		{
			exit_error("sem_wait error\n");
			return ((void *) 0);
		}
	}
	// ft_usleep(context->time_to_sleep);
	print(&context->philo[0], FINISHED);
	printf("before sem_post\n");
	exit(0);
	if (sem_wait(context->sem_exit_thread) == -1)
		exit_error("error waiting for semaphore exit_thread\n");
	context->exit_thread = 1;
	if (sem_post(context->sem_exit_thread) == -1)
		exit_error("error posting for semaphore exit_thread\n");
	if (sem_post(context->sem_philo_dead) == -1)
		exit_error("error posting semaphore philo_dead\n");
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
			if (cxt->philo[i].eat_count == cxt->must_eat_count)
			{
				sem_post(cxt->philo[i].sem_eaten_enough);
			}
			sem_wait(cxt->philo[i].mutex);
			if (get_time() > cxt->philo[i].time_limit)
			{
				print(&cxt->philo[i], DYING);
				printf("is dying\n");
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
		if (philo->context->exit_thread)
			break ;
		print(philo, THINKING);
		eating(philo);
	}
	printf("exiting routine\n");
	return ((void *) 0);
}

static int	start_thread(t_context *context)
{
	int			i;
	pthread_t	tid;

	context->start = get_time();
	i = 0;
	if (philo_create_even(context) || philo_create_odd(context))
		return (1);
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

	errno = 0;
	if (argc < 5 || argc > 6)
		return (exit_error("error: wrong amount of args\n"));
	perror(NULL);
	if (init(&cxt, argc, argv))
		return (ft_clear_context(&cxt) && exit_error("fatal error\n"));
	perror(NULL);
	if (start_thread(&cxt))
		return (ft_clear_context(&cxt) && exit_error("fatal error\n"));
	sem_wait(cxt.sem_philo_dead);
	ft_usleep((cxt.time_to_die + cxt.time_to_eat + cxt.time_to_sleep) * 1.1);
	ft_clear_context(&cxt);
}
