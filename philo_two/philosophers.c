/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 10:46:50 by adorigo           #+#    #+#             */
/*   Updated: 2020/12/14 10:50:47 by adorigo          ###   ########.fr       */
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
	sem_wait(cxt->eating[philo->name]);
	philo->last_time_ate = get_time();
	sem_post(cxt->eating[philo->name]);
	print(cxt, philo, EATING);
	usleep(cxt->time_to_eat * 1000);
	sem_wait(cxt->dropping);
	sem_post(cxt->forks);
	sem_post(cxt->forks);
	sem_post(cxt->dropping);
	if (cxt->must_eat_count && ++philo->eat_count == cxt->must_eat_count)
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
	sem_wait(context->alive);
	context->philo_alive--;
	sem_post(context->alive);
	return(philo);
}

void	*ft_monitoring(void *vp)
{
	t_context	*context;
	t_philo		*p;

	context = ft_get_context();
	p = vp;
	while (1)
	{
		sem_wait(context->eating[p->name]);
		if (!context->philo_alive)
			break;
		if (get_time() - p->last_time_ate > (unsigned long)context->time_to_die)
		{
			print(context, p, DEAD);
			sem_wait(context->someone_died);
			context->philo_dead = 1;
			sem_post(context->someone_died);
			break ;
		}
		sem_post(context->eating[p->name]);
		usleep(500);
	}
	sem_post(context->eating[p->name]);
	return (NULL);
}

void	semaphore_name(int i, char buff[])
{
	int idx;

	ft_memset(buff, 0, 14);
	buff[0] = 'e';
	buff[1] = 'a';
	buff[2] = 't';
	idx = 3;
	while (i > 0)
	{
		buff[idx++] = i % 10;
		i = i / 10;
	}
}

int			ft_creating_philo(void)
{
	t_context	*context;
	int			i;

	i = 0;
	context = ft_get_context();
	if (!(context->philosophers = malloc(sizeof(t_philo) * context->num_philo)))
		return (error_ret("Error: failed to malloc pthread_t 'philo'\n", 0));
	while (i < context->num_philo)
	{
		context->philosophers[i].name = i;
		context->philosophers[i].eat_count = 0;
		context->philosophers[i].start = get_time();
		context->philosophers[i].last_time_ate = context->philosophers[i].start;
		if (pthread_create(&context->philosophers[i].thread,
				NULL, &philosophing, &context->philosophers[i]))
			return (error_ret("Error: failed to create thread'philo\n", 0));
		if (pthread_create(&context->philosophers[i].thread_monitoring,
				NULL, &ft_monitoring, &context->philosophers[i]))
			return (error_ret("Error: failed to create thread monitor\n", 0));
		usleep(20);
		i++;
	}
	return (EXIT_SUCCESS);
}
