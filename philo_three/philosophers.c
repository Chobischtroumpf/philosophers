/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 11:26:55 by adorigo           #+#    #+#             */
/*   Updated: 2021/04/12 15:42:41 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

t_context *get_context(void)
{
	static t_context context;

	return (&context);
}

void	eating(t_philo *philo)
{
	t_context	*context;

	context = get_context();
	sem_wait(context->sem_forks);
	print(philo, FORK);
	sem_wait(context->sem_forks);
	print(philo, FORK);
	sem_wait(philo->mutex);
	philo->last_time_ate = get_time();
	philo->time_limit = philo->last_time_ate + context->time_to_die;
	print(philo, EATING);
	philo->eat_count++;
	sem_post(philo->mutex);
	ft_usleep(context->time_to_eat);
	sem_post(context->sem_forks);
	sem_post(context->sem_forks);
	print(philo, SLEEPING);
	ft_usleep(context->time_to_sleep);
}

void	*monitor(void *philo_void)
{
	t_context	*cxt;
	t_philo		*philo;

	cxt = get_context();
	philo = philo_void;
	while (1)
	{
		if (cxt->exit_thread)
			return ((void*) 0);
		sem_wait(philo->mutex);
		if (get_time() > philo->time_limit)
		{
			print(philo, DYING);
			sem_wait(cxt->sem_exit_thread);
			cxt->exit_thread = 1;
			sem_post(cxt->sem_exit_thread);
			sem_post(cxt->sem_philo_dead);
			return ((void*) 0);
		}
		sem_post(philo->mutex);
	}

}

int			routine(void *philo_void)
{
	t_philo		*philo;
	pthread_t	tid;
	t_context	*context;

	context = get_context();
	philo = (t_philo*)philo_void;
	philo->last_time_ate = context->start;
	philo->time_limit = philo->last_time_ate + context->time_to_die;
	if (pthread_create(&tid, NULL, &monitor, (void *)philo_void) != 0)
		return (1);
	pthread_detach(tid);
	while (1)
	{
		if (philo->eat_count == context->must_eat_count)
			sem_post(context->sem_eaten_enough);
		if (context->exit_thread)
			break ;
		print(philo, THINKING);
		eating(philo);
	}
	return (0);
}
