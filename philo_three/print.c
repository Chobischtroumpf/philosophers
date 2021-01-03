/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 16:43:58 by adorigo           #+#    #+#             */
/*   Updated: 2021/01/03 17:32:05 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	num_to_str(char t[], unsigned long num, int idx)
{
	if (idx == 1)
		t[idx - 1] = num + '0';
	else
	{
		num_to_str(t, num / 10, idx - 1);
		t[idx - 1] = num % 10 + '0';
	}
}

static int	count_digit(unsigned long num)
{
	int i;

	i = 0;
	if (num == 0)
		return (1);
	while (num)
	{
		num = num / 10;
		i++;
	}
	return (i);
}

static void	copy_to_buff(char *buff, unsigned long time, int index)
{
	int		digit;
	char	t[20];

	ft_memset(t, 0, 20);
	digit = count_digit(time);
	num_to_str(t, time, digit);
	ft_strlcat(buff, t, 50);
	ft_strlcat(buff, " ", 50);
	ft_memset(t, 0, 20);
	digit = count_digit(index + 1);
	num_to_str(t, index + 1, digit);
	ft_strlcat(buff, t, 50);
}

void		print(t_philo *p, t_status s, int is_dead)
{
	t_context	*cxt;
	char		buff[100];

	cxt = ft_get_context();
	ft_memset(buff, 0, 100);
	copy_to_buff(buff, get_time() - p->start, p->name);
	if (s == THINKING)
		ft_strlcat(buff, " is thinking\n", 100);
	else if (s == EATING)
		ft_strlcat(buff, " is eating\n", 100);
	else if (s == SLEEPING)
		ft_strlcat(buff, " is sleeping\n", 100);
	else if (s == TAKING_FORK)
		ft_strlcat(buff, " has taken a fork\n", 100);
	else if (s == DEAD)
		ft_strlcat(buff, " died\n", 100);
	sem_wait(cxt->print);
	ft_putstr_fd(buff, 1);
	if (!is_dead)
		sem_post(cxt->print);
}
