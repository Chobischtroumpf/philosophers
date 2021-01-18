/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:17:25 by adorigo           #+#    #+#             */
/*   Updated: 2021/01/18 13:51:39 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void			ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void			ft_putstr_fd(char *str, int fd)
{
	if (!str)
		return ;
	write(fd, str, ft_strlen(str));
}

size_t			ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	x;

	i = 0;
	j = 0;
	x = 0;
	while (dst[i] != 0)
		i++;
	while (src[j] != 0)
		j++;
	if (i < dstsize)
		j = i + j;
	else
		j = j + dstsize;
	while (src[x] != '\0' && i + 1 < dstsize)
		dst[i++] = src[x++];
	dst[i] = '\0';
	return (j);
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
