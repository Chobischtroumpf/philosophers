/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:17:25 by adorigo           #+#    #+#             */
/*   Updated: 2021/01/19 11:13:01 by adorigo          ###   ########.fr       */
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
	unsigned long end;

	end = get_time() + sleep_time;
	while (get_time() < end)
		usleep(400);
}

int				ft_free_all(int ret)
{
	t_context	*cxt;
	int			i;

	i = 0;
	cxt = ft_get_context();
	while (i < cxt->num_philo)
	{
		sem_close(cxt->eating[i]);
		if (pthread_detach(cxt->philosophers[i].thread))
			return (error_ret("Error: failed to detach thread 'philo'\n", 0));
		if (pthread_detach(cxt->philosophers[i++].thread_monitoring))
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
