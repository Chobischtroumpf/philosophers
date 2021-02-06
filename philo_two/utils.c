/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:17:25 by adorigo           #+#    #+#             */
/*   Updated: 2021/02/06 01:23:55 by adorigo          ###   ########.fr       */
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
		usleep(100);
}

int				ft_free_all(int ret)
{
	t_context	*cxt;

	cxt = ft_get_context();
	sem_close(cxt->eating);
	sem_close(cxt->forks);
	sem_close(cxt->alive);
	sem_close(cxt->block);
	sem_close(cxt->someone_died);
	sem_close(cxt->pickup);
	init_semunlink();
	free(cxt->philosophers);
	return (ret);
}
