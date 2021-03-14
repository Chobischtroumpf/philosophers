/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 14:14:46 by adorigo           #+#    #+#             */
/*   Updated: 2021/03/14 12:59:47 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*monitor_count(void *context_void)
{
	t_context	*context;
	int			i;

	context = (t_context*)context_void;
	while (i < context->amount)
		pthread_mutex_lock(&context->philosophers[i++].mut_eaten_enough);
	print(&context->philosophers[0], FINISHED);
	pthread_mutex_unlock(&context->mut_philo_dead);
	return ((void*)0);
}

void	*monitor(void *context_void)
{
	t_context	*context;
	int			i;

	context = (t_context*)context_void;
	while (1)
	{
		i = 0;
		// pthread_mutex_lock(&philo->mutex);
		while (i < context->amount)
		{
			if (context->must_eat_count &&
				context->philosophers->eat_count == context->must_eat_count)
				pthread_mutex_unlock(&context->philosophers[i].mut_eaten_enough);
			if (!context->philosophers[i].eating && 
				get_time() > context->philosophers[i].time_limit)
			{
				print(&context->philosophers[i++], DYING);
				// pthread_mutex_unlock(&philo->mutex);
				pthread_mutex_unlock(&context->mut_philo_dead);
				return ((void*)0);
			}
		}
		// pthread_mutex_unlock(&philo->mutex);
		ft_usleep(1);
	}
}

void	*routine(void *philo_void)
{
	t_philo		*philo;
	pthread_t	tid;

	philo = (t_philo*)philo_void;
	philo->last_time_ate = philo->context->start;
	philo->time_limit = philo->last_time_ate + philo->context->time_to_die;
	while (1)
	{
		print(philo, THINKING);
		take_fork(philo);
		eating(philo);
		drop_fork(philo); 
	}
}

static int	start_thread(t_context *context)
{
	int			i;
	pthread_t	tid;
	void		*philo;

	context->start = get_time();
	i = 0;
	if ( philo_create_even(context) || philo_create_odd(context))
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

	if (argc < 5 || argc > 6)
		return (exit_error("error: wrong amount of args\n"));
	if (init(&cxt, argc, argv))
		return (ft_clear_context(&cxt) && exit_error("fatal error\n"));
	if (start_thread(&cxt))
		return (ft_clear_context(&cxt) && exit_error("fatal error\n"));
	pthread_mutex_lock(&cxt.mut_philo_dead);
	pthread_mutex_unlock(&cxt.mut_philo_dead);
	ft_usleep(cxt.time_to_die + cxt.time_to_eat + cxt.time_to_sleep);
	ft_clear_context(&cxt);
}
