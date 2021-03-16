/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 13:04:56 by adorigo           #+#    #+#             */
/*   Updated: 2021/03/16 14:51:46 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	init_mutexes(t_context *context)
{
	int	i;

	i = 0;
	pthread_mutex_init(&context->mut_write, NULL);
	pthread_mutex_init(&context->mut_exit_thread, NULL);
	pthread_mutex_init(&context->mut_philo_dead, NULL);
	pthread_mutex_lock(&context->mut_philo_dead);
	if (!(context->mut_forks =
	(pthread_mutex_t*)malloc(sizeof(*(context->mut_forks)) * context->amount)))
		return (1);
	while (i < context->amount)
		pthread_mutex_init(&context->mut_forks[i++], NULL);
	return (0);
}

static void	init_philo(t_context *context)
{
	int	i;

	i = 0;
	while (i < context->amount)
	{
		context->philo[i].eating = 0;
		context->philo[i].pos = i;
		context->philo[i].lfork = i;
		context->philo[i].rfork = (i + 1) % context->amount;
		context->philo[i].eat_count = 0;
		context->philo[i].context = context;
		pthread_mutex_init(&context->philo[i].mutex, NULL);
		pthread_mutex_init(&context->philo[i].mut_eaten_enough, NULL);
		pthread_mutex_lock(&context->philo[i].mut_eaten_enough);
		i++;
	}
}

int			init(t_context *contxt, int argc, char **argv)
{
	contxt->amount = ft_atoi(argv[1]);
	contxt->time_to_die = ft_atoi(argv[2]);
	contxt->time_to_eat = ft_atoi(argv[3]);
	contxt->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		contxt->must_eat_count = ft_atoi(argv[5]);
		if (contxt->must_eat_count)
			return (1);
	}
	else
		contxt->must_eat_count = -1;
	if (contxt->amount < 2 || contxt->amount > 200 || contxt->time_to_die < 60
		|| contxt->time_to_eat < 60 || contxt->time_to_sleep < 60)
		return (1);
	contxt->mut_forks = NULL;
	contxt->philo = NULL;
	contxt->exit_thread = 0;
	if (!(contxt->philo = (t_philo *)malloc(sizeof(*(contxt->philo))
	* contxt->amount)))
		return (1);
	init_philo(contxt);
	return (init_mutexes(contxt));
}
