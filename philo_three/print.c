/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 16:43:58 by adorigo           #+#    #+#             */
/*   Updated: 2021/01/18 16:37:58 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_putunbr(unsigned long n)
{
	if (n / 10)
		ft_putunbr(n / 10);
	n = n % 10 + '0';
	write(1, &n, 1);
}


void	ft_put_time(t_philo *philo)
{
	unsigned long	current_time;

	current_time =  get_time() - philo->start;
	ft_putunbr(current_time);
}

void		print(t_philo *p, t_status s, int is_dead)
{
	t_context	*cxt;

	cxt = ft_get_context();
	sem_wait(cxt->print);
	ft_put_time(p);
	write(1, " ", 1);
	ft_putunbr(p->name + 1);
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
	if (!is_dead)
		sem_post(cxt->print);
}
