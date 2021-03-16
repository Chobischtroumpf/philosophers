/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 11:26:55 by adorigo           #+#    #+#             */
/*   Updated: 2021/03/16 17:47:51 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->context->mut_forks[philo->lfork]);
//	print(philo, FORK);
	pthread_mutex_lock(&philo->context->mut_forks[philo->rfork]);
//	print(philo, FORK);
	pthread_mutex_lock(&philo->mutex);
	philo->eating = 1;
	philo->last_time_ate = get_time();
	philo->time_limit = philo->last_time_ate + philo->context->time_to_die;
	print(philo, EATING);
	philo->eat_count++;
	philo->eating = 0;
	pthread_mutex_unlock(&philo->mutex);
	ft_usleep(philo->context->time_to_eat);
	pthread_mutex_unlock(&philo->context->mut_forks[philo->lfork]);
	pthread_mutex_unlock(&philo->context->mut_forks[philo->rfork]);
	print(philo, SLEEPING);
	ft_usleep(philo->context->time_to_sleep);
}

//void	take_fork(t_philo *philo)
//{
//	pthread_mutex_lock(&philo->context->mut_forks[philo->lfork]);
//	print(philo, FORK);
//	pthread_mutex_lock(&philo->context->mut_forks[philo->rfork]);
//	print(philo, FORK);
//}

//void	drop_fork(t_philo *philo)
//{
//	pthread_mutex_unlock(&philo->context->mut_forks[philo->lfork]);
//	pthread_mutex_unlock(&philo->context->mut_forks[philo->rfork]);
//	print(philo, SLEEPING);
//	ft_usleep(philo->context->time_to_sleep);
//}

int		philo_create_odd(t_context *context)
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

int		philo_create_even(t_context *context)
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
