/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:17:25 by adorigo           #+#    #+#             */
/*   Updated: 2021/03/13 11:17:39 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_putstr_fd(char *str, int fd)
{
	if (!str)
		return ;
	write(fd, str, ft_strlen(str));
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char		*dest;
	const char	*source;
	size_t		i;
	size_t		dlen;

	dest = dst;
	source = src;
	i = size;
	while (i-- != 0 && *dest)
		dest++;
	dlen = dest - dst;
	i = size - dlen;
	if (i == 0)
		return (dlen + ft_strlen(source));
	while (*source)
	{
		if (i != 1)
		{
			*dest++ = *source;
			i--;
		}
		source++;
	}
	*dest = '\0';
	return (dlen + (source - src));
}

void	ft_usleep(unsigned long sleep_time)
{
	unsigned long end;

	end = get_time() + sleep_time;
	while (get_time() < end)
		usleep(100);
}

void	ft_free_mutex(t_context *cxt)
{
	pthread_mutex_lock(&cxt->alive);
	pthread_mutex_unlock(&cxt->alive);
	pthread_mutex_destroy(&cxt->alive);
	pthread_mutex_lock(&cxt->someone_died);
	pthread_mutex_unlock(&cxt->someone_died);
	pthread_mutex_destroy(&cxt->someone_died);
	if (!cxt->philo_dead)
	{
		pthread_mutex_lock(&cxt->block);
		pthread_mutex_lock(&cxt->print);
	}
	pthread_mutex_unlock(&cxt->block);
	pthread_mutex_destroy(&cxt->block);
	pthread_mutex_unlock(&cxt->print);
	pthread_mutex_destroy(&cxt->print);
}

int		ft_free_all(int ret)
{
	t_context	*cxt;
	int			i;

	i = -1;
	cxt = ft_get_context();
	// ft_free_mutex(cxt);
	// while (++i < cxt->num_philo)
	// {
	// 	pthread_mutex_lock(&cxt->forks[i]);
	// 	pthread_mutex_unlock(&cxt->forks[i]);
	// 	pthread_mutex_destroy(&cxt->forks[i]);
	// 	pthread_mutex_lock(&cxt->eating[i]);
	// 	pthread_mutex_unlock(&cxt->eating[i]);
	// 	pthread_mutex_destroy(&cxt->eating[i]);
	// }
	free(cxt->forks);
	free(cxt->eating);
	free(cxt->philosophers);
	return (ret);
}
