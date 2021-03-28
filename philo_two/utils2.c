/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 13:03:21 by adorigo           #+#    #+#             */
/*   Updated: 2021/03/28 12:18:35 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

unsigned long	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (unsigned long) 1000) + (tv.tv_usec / 1000));
}

int	ft_strcpy(char *dst, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (i);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*i;

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

int	ft_clear_context(t_context *contxt)
{
	int		i;
	char	semaphore[255];

	sem_unlink(SEM_FORK);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_DEAD);
	sem_unlink(SEM_PHILOEAT);
	if (contxt->philo)
	{
		i = -1;
		while (++i < contxt->amount && &contxt->philo[i] != NULL)
		{
			make_semaphore_name(SEM_PHILO, (char *)semaphore, i);
			sem_unlink(semaphore);
		}
		free(contxt->philo);
	}
	return (1);
}

int	exit_error(const char *str)
{
	if (str)
		write(1, str, ft_strlen(str));
	return (1);
}
