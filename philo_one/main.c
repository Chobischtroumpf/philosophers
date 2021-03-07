/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 14:14:46 by adorigo           #+#    #+#             */
/*   Updated: 2021/03/07 15:25:02 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void *monitor_count(void *philo_void)
{
	t_philo
}

static void *monitor(void *philo_void)
{
	
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
	while(1)
	{
		take_fork(philo);
		eat(philo);
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
	if (context->must_eat_count > 0)
	{
		if (pthread_create(&tid,  NULL, &monitor_count, (void *)context) != 0)
			return (1);
		pthread_detach(tid);
	}
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
	return (0);
}

int main(int argc, char **argv)
{
	t_context	context;

	if (argc < 5 || argc > 6)
		return (exit_error("error: wrong amount of args\n"));
	if (init(&context, argc, argv))
		return (ft_clear_context(&context) && exit_error("fatal error\n"));
	if (start_thread(&context))
		return (ft_clear_context(&context) && exit_error("fatal error\n"));
	pthread_mutex_lock(&context.mut_philo_dead);
	pthread_mutex_unlock(&context.mut_philo_dead);
	usleep((context.time_to_die + context.time_to_eat + context.time_to_sleep) * 900);
	ft_clear_context(&context);
}