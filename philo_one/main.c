/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 14:14:46 by adorigo           #+#    #+#             */
/*   Updated: 2021/03/13 14:38:39 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	*monitor_count(void *context_void)
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

static void	*monitor(void *philo_void)
{
	t_philo		*philo;

	philo = (t_philo*)philo_void;
	while (1)
	{
		pthread_mutex_lock(&philo->mutex);
		if (philo->context->must_eat_count &&
			philo->eat_count == philo->context->must_eat_count)
			pthread_mutex_unlock(&philo->mut_eaten_enough);
		if (!philo->eating && get_time() > philo->time_limit)
		{
			print(philo, DYING);
			pthread_mutex_unlock(&philo->mutex);
			pthread_mutex_unlock(&philo->context->mut_philo_dead);
			return ((void*)0);
		}
		pthread_mutex_unlock(&philo->mutex);
		ft_usleep(1);
	}
}

static void	*routine(void *philo_void)
{
	t_philo		*philo;
	pthread_t	tid;

	philo = (t_philo*)philo_void;
	philo->last_time_ate = philo->context->start;
	philo->time_limit = philo->last_time_ate + philo->context->time_to_die;
	if (pthread_create(&tid, NULL, &monitor, philo_void) != 0)
		return ((void*)1);
	while (1)
	{
		take_fork(philo);
		eating(philo);
		drop_fork(philo); 
		print(philo, THINKING);
	}
}

static int	start_thread(t_context *context)
{
	int			i;
	pthread_t	tid;
	void		*philo;

	context->start = get_time();
	i = 0;
	while (i < context->amount)
	{
		philo = (void *)(&context->philosophers[i]);
		if (pthread_create(&tid, NULL, &routine, philo) != 0)
			return (1);
		pthread_detach(tid);
		usleep(20);
		i++;
	}
	if (context->must_eat_count > 0)
	{
		if (pthread_create(&tid, NULL, &monitor_count, (void *)context) != 0)
			return (1);
		pthread_detach(tid);
	}
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
