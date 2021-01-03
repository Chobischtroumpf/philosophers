/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 10:46:50 by adorigo           #+#    #+#             */
/*   Updated: 2020/12/08 12:32:58 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	taking_fork_and_eating(t_context *cxt, t_philo *philo)
{
	pthread_mutex_lock(&cxt->pickup);
	pthread_mutex_lock(&cxt->forks[philo->name]);
	print(cxt, philo, TAKING_FORK);
	pthread_mutex_lock(&cxt->forks[(philo->name + 1) % cxt->num_philo]);
	print(cxt, philo, TAKING_FORK);
	pthread_mutex_unlock(&cxt->pickup);
	pthread_mutex_lock(&cxt->eating[philo->name]);
	philo->last_time_ate = get_time();
	pthread_mutex_unlock(&cxt->eating[philo->name]);
	print(cxt, philo, EATING);
	usleep(cxt->time_to_eat * 1000);
	pthread_mutex_lock(&cxt->dropping);
	pthread_mutex_unlock(&cxt->forks[philo->name]);
	pthread_mutex_unlock(&cxt->forks[(philo->name + 1) % cxt->num_philo]);
	pthread_mutex_unlock(&cxt->dropping);
	if (cxt->must_eat_count > 0 && ++philo->eat_count == cxt->must_eat_count)
		return (0);
	return (1);
}

static void	*philosophing(void *vp)
{
	t_context	*context;
	t_philo		*philo;

	context = ft_get_context();
	philo = vp;
	while (1)
	{
		if (context->philo_dead)
			break ;
		print(context, philo, THINKING);
		if (!(taking_fork_and_eating(context, philo)))
			break ;
		print(context, philo, SLEEPING);
		usleep(context->time_to_sleep * 1000);
	}
	pthread_mutex_lock(&context->alive);
	context->philo_alive--;
	pthread_mutex_unlock(&context->alive);
	return (NULL);
}

static int	create_philos_odd(t_context *contxt)
{
	int	i;
	int	j;

	i = 0;
	while ((j = 2 * i) < contxt->num_philo)
	{
		contxt->philosophers[j].name = j;
		contxt->philosophers[j].eat_count = 0;
		contxt->philosophers[j].start = get_time();
		contxt->philosophers[j].last_time_ate = contxt->philosophers[j].start;
		if (pthread_create(&contxt->philosophers[j].thread,
				NULL, &philosophing, &contxt->philosophers[j]))
			return (error_ret("Error: failed to create thread philo\n", 0));
		if (pthread_create(&contxt->philosophers[j].thread_monitoring,
				NULL, &ft_monitoring, &contxt->philosophers[j]))
			return (error_ret("Error: failed to create thread monitor\n", 0));
		usleep(20);
		i++;
	}
	return (1);
}

static int	create_philos_even(t_context *contxt)
{
	int	i;
	int	j;

	i = 0;
	while ((j = 2 * i + 1) < contxt->num_philo)
	{
		contxt->philosophers[j].name = j;
		contxt->philosophers[j].eat_count = 0;
		contxt->philosophers[j].start = get_time();
		contxt->philosophers[j].last_time_ate = contxt->philosophers[j].start;
		if (pthread_create(&contxt->philosophers[j].thread,
				NULL, &philosophing, &contxt->philosophers[j]))
			return (error_ret("Error: failed to create thread'philo\n", 0));
		if (pthread_create(&contxt->philosophers[j].thread_monitoring,
				NULL, &ft_monitoring, &contxt->philosophers[j]))
			return (error_ret("Error: failed to create thread monitor\n", 0));
		usleep(20);
		i++;
	}
	return (1);
}

int			ft_creating_philo(void)
{
	t_context	*context;
	int			i;

	i = 0;
	context = ft_get_context();
	if (!(context->philosophers = malloc(sizeof(t_philo) * context->num_philo)))
		return (error_ret("Error: failed to malloc pthread_t 'philo'\n", 0));
	if (!create_philos_odd(context))
		return (0);
	if (!create_philos_even(context))
		return (0);
	return (EXIT_SUCCESS);
}
