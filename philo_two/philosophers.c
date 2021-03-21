/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 11:26:55 by adorigo           #+#    #+#             */
/*   Updated: 2021/03/21 15:49:24 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	eating(t_philo *philo)
{
	if (sem_wait(philo->context->sem_forks) == -1)
		exit_error("error waiting for first semaphore sem_fork\n");
	print(philo, FORK);
	if (sem_wait(philo->context->sem_forks) == -1)
		exit_error("error waiting for second semaphore sem_fork\n");
	print(philo, FORK);
	if (sem_wait(philo->mutex) == -1)
		exit_error("error waiting for semaphore mutex\n");
	philo->last_time_ate = get_time();
	philo->time_limit = philo->last_time_ate + philo->context->time_to_die;
	print(philo, EATING);
	philo->eat_count++;
	if (sem_post(philo->mutex) == -1)
		exit_error("error posting semaphore mutex\n");
	// printf("here %d\n", philo->pos);
	ft_usleep(philo->context->time_to_eat);
	// printf("here2 %d\n", philo->pos);
	if (sem_post(philo->context->sem_forks) == -1)
	{
		exit_error("error posting first semaphore sem_fork\n");
		perror(NULL);
	}
	// printf("here3 %d\n", philo->pos);
	if (sem_post(philo->context->sem_forks) == -1)
		exit_error("error posting second semaphore sem_fork\n");
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
