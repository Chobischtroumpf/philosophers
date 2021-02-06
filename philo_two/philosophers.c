/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 10:46:50 by adorigo           #+#    #+#             */
/*   Updated: 2021/02/06 02:30:03 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	taking_fork_and_eating(t_context *cxt, t_philo *philo)
{
	sem_wait(cxt->pickup);
	sem_wait(cxt->forks);
	print(cxt, philo, TAKING_FORK);
	sem_wait(cxt->forks);
	print(cxt, philo, TAKING_FORK);
	sem_post(cxt->pickup);
	philo->is_eating = 1;
	sem_wait(cxt->eating);
	print(cxt, philo, EATING);
	philo->last_time_ate = get_time();
	sem_post(cxt->eating);
	philo->is_eating = 0;
	ft_usleep(cxt->time_to_eat);
	sem_post(cxt->forks);
	sem_post(cxt->forks);
	if ((cxt->must_eat_count && ++philo->eat_count == cxt->must_eat_count) || 
		cxt->philo_dead)
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
		if (context->philo_dead)
			break ;
		print(context, philo, SLEEPING);
		ft_usleep(context->time_to_sleep);
	}
	sem_wait(context->alive);
	context->philo_alive--;
	sem_post(context->alive);
	return (philo);
}

void		*ft_monitoring(void *vp)
{
	t_context	*context;
	t_philo		*p;

	context = ft_get_context();
	p = vp;
	while (1)
	{
		if (!p->is_eating)
		{
			if (!context->philo_alive)
				break ;
			if (get_time() - p->last_time_ate > (unsigned long)context->time_to_die)
			{
				print(context, p, DEAD);
				sem_wait(context->someone_died);
				context->philo_dead = 1;
				sem_post(context->someone_died);
				break ;
			}
		}
		usleep(500);
	}
	return (vp);
}

int			ft_creating_philo(t_context *context)
{
	int	i;

	i = 0;
	if (!(context->philosophers = malloc(sizeof(t_philo) * context->num_philo)))
		return (error_ret("Error: failed to malloc pthread_t 'philo'\n", 0));
	while (i < context->num_philo)
	{
		context->philosophers[i].name = i;
		context->philosophers[i].eat_count = 0;
		context->philosophers[i].last_time_ate = context->start;
		context->philosophers[i].is_eating = 0;
		if (pthread_create(&context->philosophers[i].thread,
				NULL, &philosophing, &context->philosophers[i]))
			return (error_ret("Error: failed to create thread philo\n", 0));
		if (pthread_detach(context->philosophers[i].thread))
			return (error_ret("Error: failed to detach thread philo\n", 0));
		if (pthread_create(&context->philosophers[i].thread_monitoring,
				NULL, &ft_monitoring, &context->philosophers[i]))
			return (error_ret("Error: failed to create thread monitor\n", 0));
		if (pthread_detach(context->philosophers[i].thread_monitoring))
			return (error_ret("Error: failed to detach thread monitor\n", 0));
		usleep(20);
		i++;
	}
	return (EXIT_SUCCESS);
}
