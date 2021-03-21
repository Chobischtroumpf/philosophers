/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 11:26:55 by adorigo           #+#    #+#             */
/*   Updated: 2021/03/21 15:03:09 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	eating(t_philo *philo)
{
	sem_wait(philo->context->sem_forks);
	print(philo, FORK);
	sem_wait(philo->context->sem_forks);
	print(philo, FORK);
	sem_wait(philo->mutex);
	philo->last_time_ate = get_time();
	philo->time_limit = philo->last_time_ate + philo->context->time_to_die;
	print(philo, EATING);
	philo->eat_count++;
	sem_post(philo->mutex);
	// printf("here %d\n", philo->pos);
	ft_usleep(philo->context->time_to_eat);
	// printf("here2 %d\n", philo->pos);
	sem_post(philo->context->sem_forks);
	// printf("here3 %d\n", philo->pos);
	sem_post(philo->context->sem_forks);
	// printf("here4 %d\n", philo->pos);
	print(philo, SLEEPING);
	ft_usleep(philo->context->time_to_sleep);
}

int	philo_create_odd(t_context *context)
{
	int			i;
	pthread_t	tid;
	t_philo		*philo;

	i = 1;
	while (i < context->amount)
	{
		philo = (void *)(&context->philo[i]);
		if (pthread_create(&tid, NULL, &routine, philo) != 0)
			return (1);
		pthread_detach(tid);
		usleep(20);
		i += 2;
	}
	return (0);
}

int	philo_create_even(t_context *context)
{
	int			i;
	pthread_t	tid;
	t_philo		*philo;

	i = 0;
	while (i < context->amount)
	{
		philo = (void *)(&context->philo[i]);
		if (pthread_create(&tid, NULL, &routine, philo) != 0)
			return (1);
		pthread_detach(tid);
		usleep(20);
		i += 2;
	}
	return (0);
}
