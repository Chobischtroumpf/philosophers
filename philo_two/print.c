/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 16:43:58 by adorigo           #+#    #+#             */
/*   Updated: 2021/02/06 01:47:27 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_putunbr(unsigned long n)
{
	if (n / 10)
		ft_putunbr(n / 10);
	n = n % 10 + '0';
	write(1, &n, 1);
}

static void	ft_put_time(t_context *cxt)
{
	unsigned long	current_time;

	current_time = get_time() - cxt->start;
	ft_putunbr(current_time);
}

void		print(t_context *cxt, t_philo *philo, t_status s)
{
	if (cxt->philo_dead)
		return ;
	sem_wait(cxt->block);
	if (cxt->philo_dead)
	{
		sem_post(cxt->block);
		return ;
	}
	ft_put_time(cxt);
	write(1, " ", 1);
	ft_putunbr(philo->name + 1);
	if (s == THINKING)
		ft_putstr_fd(" is thinking\n", 1);
	else if (s == EATING)
		ft_putstr_fd(" is eating\n", 1);
	else if (s == SLEEPING)
		ft_putstr_fd(" is sleeping\n", 1);
	else if (s == TAKING_FORK)
		ft_putstr_fd(" has taken a fork\n", 1);
	else if (s == DEAD)
		ft_putstr_fd(" died\n", 1);
	if (!(s == DEAD))
		sem_post(cxt->block);
}
