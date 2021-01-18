/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:17:25 by adorigo           #+#    #+#             */
/*   Updated: 2021/01/18 16:49:15 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void			ft_putstr_fd(char *str, int fd)
{
	if (!str)
		return ;
	write(fd, str, ft_strlen(str));
}

void			ft_usleep(unsigned long sleep_time)
{
	usleep(sleep_time * 200);
	usleep(sleep_time * 200);
	usleep(sleep_time * 200);
	usleep(sleep_time * 200);
	usleep(sleep_time * 200);
}

void			ft_free_mutex(t_context *cxt)
{
	pthread_mutex_lock(&cxt->alive);
	pthread_mutex_unlock(&cxt->alive);
	pthread_mutex_destroy(&cxt->alive);
	pthread_mutex_lock(&cxt->someone_died);
	pthread_mutex_unlock(&cxt->someone_died);
	pthread_mutex_destroy(&cxt->someone_died);
	// pthread_mutex_lock(&cxt->pickup);
	// pthread_mutex_unlock(&cxt->pickup);
	// pthread_mutex_destroy(&cxt->pickup);
	// pthread_mutex_lock(&cxt->dropping);
	// pthread_mutex_unlock(&cxt->dropping);
	// pthread_mutex_destroy(&cxt->dropping);
	pthread_mutex_lock(&cxt->print);
	pthread_mutex_unlock(&cxt->print);
	pthread_mutex_destroy(&cxt->print);
}

int				ft_free_all(int ret)
{
	t_context	*cxt;
	int			i;

	i = -1;
	cxt = ft_get_context();
	ft_free_mutex(cxt);
	while (++i < cxt->num_philo)
	{
		pthread_mutex_lock(&cxt->forks[i]);
		pthread_mutex_unlock(&cxt->forks[i]);
		pthread_mutex_destroy(&cxt->forks[i]);
		pthread_mutex_lock(&cxt->eating[i]);
		pthread_mutex_unlock(&cxt->eating[i]);
		pthread_mutex_destroy(&cxt->eating[i]);
		// if (pthread_join(cxt->philosophers[i].thread, NULL))
		// 	return (error_ret("Error: failed to join thread 'philo'\n", 0));
		// if (pthread_join(cxt->philosophers[i].thread_monitoring, NULL))
			// return (error_ret("Error: failed to join thread 'mphilo'\n", 0));
	}
	free(cxt->forks);
	free(cxt->eating);
	free(cxt->philosophers);
	return (ret);
}
