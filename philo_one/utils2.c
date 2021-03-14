/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 13:03:21 by adorigo           #+#    #+#             */
/*   Updated: 2021/03/14 16:05:06 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

unsigned long	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (unsigned long)1000) + (tv.tv_usec / 1000));
}

void			*ft_memset(void *b, int c, size_t len)
{
	unsigned char *i;

	if (b == 0)
		return (NULL);
	if (len == 0)
		return (b);
	i = b;
	while (len--)
	{
		*i = (unsigned char)c;
		if (len)
			i++;
	}
	return (b);
}

int				ft_clear_context(t_context *contxt)
{
	int	i;

	if (contxt->mut_forks)
	{
		i = 0;
		while (i < contxt->amount)
			pthread_mutex_destroy(&contxt->mut_forks[i++]);
		free(contxt->mut_forks);
	}
	if (contxt->philo)
	{
		i = 0;
		while (i < contxt->amount)
			pthread_mutex_unlock(&contxt->philo[i++].mut_eaten_enough);
		i = 0;
		while (i < contxt->amount)
		{
			pthread_mutex_destroy(&contxt->philo[i].mutex);
			pthread_mutex_destroy(&contxt->philo[i++].mut_eaten_enough);
		}
		free(contxt->philo);
	}
	pthread_mutex_destroy(&contxt->mut_write);
	pthread_mutex_destroy(&contxt->mut_philo_dead);
	return (1);
}

int				exit_error(const char *str)
{
	if (str)
		write(1, str, ft_strlen(str));
	return (1);
}
