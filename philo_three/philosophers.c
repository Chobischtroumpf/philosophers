/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 10:46:50 by adorigo           #+#    #+#             */
/*   Updated: 2021/01/18 16:52:31 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	taking_fork_and_eating(t_context *cxt, t_philo *philo)
{
	sem_wait(cxt->pickup);
	sem_wait(cxt->forks);
	print(philo, TAKING_FORK, NO_EXIT);
	sem_wait(cxt->forks);
	print(philo, TAKING_FORK, NO_EXIT);
	print(philo, EATING, NO_EXIT);
	sem_post(cxt->pickup);
	sem_wait(cxt->eating);
	philo->last_time_ate = get_time();
	sem_post(cxt->eating);
	ft_usleep(cxt->time_to_eat);
	sem_post(cxt->forks);
	sem_post(cxt->forks);
	if (cxt->must_eat_count && ++philo->eat_count == cxt->must_eat_count)
		return (0);
	return (1);
}

void		*ft_monitoring(void *vp)
{
	t_context	*contxt;
	t_philo		*p;

	contxt = ft_get_context();
	p = vp;
	while (1)
	{
		sem_wait(contxt->eating);
		if (get_time() - p->last_time_ate > (unsigned long)contxt->time_to_die)
		{
			print(p, DEAD, EXIT);
			exit(PHILO_DEAD);
		}
		sem_post(contxt->eating);
		usleep(1000);
	}
	return (vp);
}

static void	create_monitor_thread(t_philo *philo)
{
	if (pthread_create(&philo->thread_monitoring, NULL, &ft_monitoring, philo))
		exit(error_ret("Error: failed to create thread 'monitor'\n", 1));
	if (pthread_detach(philo->thread_monitoring))
		exit(error_ret("Error: failed to detach thread 'monitor'\n", 1));
}

static void	philosophing(void *vp)
{
	t_context	*context;
	t_philo		*philo;

	context = ft_get_context();
	philo = vp;
	philo->start = get_time();
	philo->last_time_ate = philo->start;
	create_monitor_thread(philo);
	while (1)
	{
		print(philo, THINKING, NO_EXIT);
		if (!(taking_fork_and_eating(context, philo)))
			exit(PHILO_ATE_ENOUGH);
		print(philo, SLEEPING, NO_EXIT);
		usleep(context->time_to_sleep);
	}
	exit(0);
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
		if ((context->pid[i] = fork()) == 0)
			philosophing(&context->philosophers[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
