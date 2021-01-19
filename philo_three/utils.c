/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:17:25 by adorigo           #+#    #+#             */
/*   Updated: 2021/01/19 13:06:14 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_usleep(unsigned long sleep_time)
{
	unsigned long end;

	end = get_time() + sleep_time;
	while (get_time() < end)
		usleep(400);
}

void	ft_putstr_fd(char *str, int fd)
{
	if (!str)
		return ;
	write(fd, str, ft_strlen(str));
}

int		ft_free_all(int ret)
{
	t_context	*cxt;

	cxt = ft_get_context();
	sem_post(cxt->eating);
	sem_close(cxt->eating);
	sem_post(cxt->pickup);
	sem_close(cxt->pickup);
	sem_post(cxt->forks);
	sem_close(cxt->forks);
	sem_post(cxt->print);
	sem_close(cxt->print);
	init_semlink();
	free(cxt->philosophers);
	free(cxt->pid);
	return (ret);
}
