/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:17:25 by adorigo           #+#    #+#             */
/*   Updated: 2020/12/13 16:55:55 by adorigo          ###   ########.fr       */
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

int				ft_free_all(int ret)
{
	t_context	*cxt;
	int			i;

	i = -1;
	cxt = ft_get_context();
	while (++i < cxt->num_philo)
	{
		sem_close(cxt->eating[i]);
		if (pthread_join(cxt->philosophers[i].thread, NULL))
			return (error_ret("Error: failed to detach thread 'philo'\n", 0));
		if (pthread_join(cxt->philosophers[i].thread_monitoring, NULL))
			return (error_ret("Error: failed to detach thread 'mphilo'\n", 0));
	}
	sem_close(cxt->pickup);
	sem_close(cxt->dropping);
	sem_close(cxt->forks);
	sem_close(cxt->alive);
	sem_close(cxt->print);
	sem_close(cxt->someone_died);
	init_semlink();
	free(cxt->eating);
	free(cxt->philosophers);
	return (ret);
}