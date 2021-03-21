/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 13:04:56 by adorigo           #+#    #+#             */
/*   Updated: 2021/03/21 14:24:14 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static int	init_semaphores(t_context *context)
{
	int	i;

	i = 0;
	context->sem_forks = ft_sem_open(SEM_FORK, context->amount);
	context->sem_exit_thread = ft_sem_open(SEM_EXIT, 1);
	context->sem_write = ft_sem_open(SEM_WRITE, 1);
	context->sem_philo_dead = ft_sem_open(SEM_DEAD, 1);
	if (context->sem_forks < 0 || context->sem_write < 0
		|| context->sem_philo_dead < 0)
		return (1);
	sem_wait(context->sem_philo_dead);
	return (0);
}

static int	init_philo(t_context *context)
{
	int		i;
	char	semaphore[250];

	i = 0;
	while (i < context->amount)
	{
		context->philo[i].pos = i;
		context->philo[i].lfork = i;
		context->philo[i].rfork = (i + 1) % context->amount;
		context->philo[i].eat_count = 0;
		context->philo[i].context = context;
		make_semaphore_name(SEM_PHILO, (char *)semaphore, i);
		context->philo[i].mutex = ft_sem_open(semaphore, 1);
		make_semaphore_name(SEM_PHILOEAT, (char *)semaphore, i);
		context->philo[i].sem_eaten_enough = ft_sem_open(semaphore, 1);
		if (context->philo[i].mutex < 0
			|| context->philo[i].sem_eaten_enough < 0)
			return (1);
		sem_wait(context->philo[i].sem_eaten_enough);
		i++;
	}
	return (0);
}

int	init(t_context *contxt, int argc, char **argv)
{
	contxt->amount = ft_atoi(argv[1]);
	contxt->time_to_die = ft_atoi(argv[2]);
	contxt->time_to_eat = ft_atoi(argv[3]);
	contxt->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		contxt->must_eat_count = ft_atoi(argv[5]);
		if (!contxt->must_eat_count)
			return (1);
	}
	else
		contxt->must_eat_count = -1;
	if (contxt->amount < 2 || contxt->amount > 200 || contxt->time_to_die < 60
		|| contxt->time_to_eat < 60 || contxt->time_to_sleep < 60)
		return (1);
	contxt->sem_forks = NULL;
	contxt->philo = NULL;
	contxt->exit_thread = 0;
	contxt->philo = (t_philo *)malloc(sizeof(*(contxt->philo))
			* contxt->amount);
	if (!contxt->philo || init_philo(contxt))
		return (1);
	return (init_semaphores(contxt));
}
