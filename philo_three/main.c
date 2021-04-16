/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 14:14:46 by adorigo           #+#    #+#             */
/*   Updated: 2021/04/16 11:35:20 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*monitor_count(void *context_void)
{
	t_context	*context;
	int			i;

	i = 0;
	context = (t_context *)context_void;
	while (i < context->amount)
	{
		if (sem_wait(context->sem_eaten_enough) == -1)
		{
			exit_error("sem_wait error\n");
			return ((void *) 0);
		}
		i++;
	}
	sem_wait(context->sem_exit_thread);
	context->exit_thread = 1;
	sem_post(context->sem_exit_thread);
	sem_post(context->sem_philo_dead);
	return ((void *) 0);
}

static int	start_monitor(void)
{
	pthread_t	tid;
	t_context	*context;

	context = get_context();
	if (context->must_eat_count > 0)
	{
		if (pthread_create(&tid, NULL, &monitor_count, (void *)context) != 0)
			return (1);
		pthread_detach(tid);
	}
	return (0);
}

static int	start_process(void)
{
	int			i;
	void		*philo;
	t_context	*context;

	context = get_context();
	context->start = get_time();
	i = 0;
	while (i < context->amount)
	{
		philo = (void *)(&context->philo[i]);
		context->philo[i].pid = fork();
		if (context->philo[i].pid < 0)
		{
			return (1);
		}
		else if (context->philo[i].pid == 0)
		{
			routine(&context->philo[i]);
			exit(0);
		}
		usleep(100);
		i++;
	}
	return (0);
}

int
	main(int argc, char **argv)
{
	int			i;
	t_context	*context;

	context = get_context();
	if (argc < 5 || argc > 6)
		return (exit_error("error: bad arguments\n"));
	if (init(context, argc, argv)
		|| start_process()
		|| start_monitor())
		return (ft_clear_context() && exit_error("error: fatal\n"));
	sem_wait(context->sem_philo_dead);
	i = 0;
	while (i < context->amount)
		kill(context->philo[i++].pid, SIGKILL);
	ft_clear_context();
	return (0);
}
