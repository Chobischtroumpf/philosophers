/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 11:26:55 by adorigo           #+#    #+#             */
/*   Updated: 2021/03/13 14:34:25 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	philo->eating = 1;
	philo->last_time_ate = get_time();
	philo->time_limit = philo->last_time_ate + philo->context->time_to_die;
	print(philo, EATING);
	ft_usleep(philo->context->time_to_eat);
	philo->eat_count++;
	philo->eating = 0;
	pthread_mutex_unlock(&philo->mutex);
}

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->context->mut_forks[philo->lfork]);
	print(philo, FORK);
	pthread_mutex_lock(&philo->context->mut_forks[philo->rfork]);
	print(philo, FORK);
}

void	drop_fork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->context->mut_forks[philo->lfork]);
	pthread_mutex_unlock(&philo->context->mut_forks[philo->rfork]);
	print(philo, SLEEPING);
	ft_usleep(philo->context->time_to_sleep);

}