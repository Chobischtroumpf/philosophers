/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 13:04:56 by adorigo           #+#    #+#             */
/*   Updated: 2021/03/14 14:20:14 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	init_mutexes(t_context *context)
{
	int	i;

	i = 0;
	pthread_mutex_init(&context->mut_write, NULL);
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
		context->philosophers[i].eating = 0;
		context->philosophers[i].pos = i;
		context->philosophers[i].lfork = i;
		context->philosophers[i].rfork = (i + 1) % context->amount;
		context->philosophers[i].eat_count = 0;
		context->philosophers[i].context = context;
		pthread_mutex_init(&context->philosophers[i].mutex, NULL);
		pthread_mutex_init(&context->philosophers[i].mut_eaten_enough, NULL);
		pthread_mutex_lock(&context->philosophers[i].mut_eaten_enough);
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
		contxt->must_eat_count = ft_atoi(argv[5]);
	else
		contxt->must_eat_count = 0;
	if (contxt->amount < 2 || contxt->amount > 200 || contxt->time_to_die < 60
		|| contxt->time_to_eat < 60 || contxt->time_to_sleep < 60
		|| contxt->must_eat_count < 0)
		return (1);
	contxt->mut_forks = NULL;
	contxt->philosophers = NULL;
	contxt->is_dead = 0;
	if (!(contxt->philosophers = (t_philo*)malloc(sizeof(*(contxt->philosophers)) *contxt->amount)))
		return (1);
	init_philo(contxt);
	return (init_mutexes(contxt));
}