/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 12:27:00 by adorigo           #+#    #+#             */
/*   Updated: 2021/03/21 11:21:04 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void
	num_to_str(char t[], unsigned long num, int idx)
{
	if (idx == 1)
		t[idx - 1] = num + '0';
	else
	{
		num_to_str(t, num / 10, idx - 1);
		t[idx - 1] = num % 10 + '0';
	}
}

static int
	count_digit(unsigned long num)
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

static void
	copy_to_buff(char *buff, unsigned long time, int index)
{
	int		digit;
	size_t	size;
	char	t[20];

	size = 100;
	ft_memset(t, 0, 20);
	digit = count_digit(time);
	num_to_str(t, time, digit);
	ft_strlcat(buff, t, size);
	ft_strlcat(buff, " ", size);
	ft_memset(t, 0, 20);
	digit = count_digit(index + 1);
	num_to_str(t, index + 1, digit);
	ft_strlcat(buff, t, size);
}

void
	print(t_philo *philo, t_status s)
{
	static int	end = 0;
	char		buff[100];

	pthread_mutex_lock(&philo->context->mut_write);
	if (!end)
	{
		ft_memset(buff, 0, 100);
		copy_to_buff(buff, get_time() - philo->context->start, philo->pos);
		if (s == THINKING)
			ft_strlcat(buff, " is thinking\n", 100);
		else if (s == FORK)
			ft_strlcat(buff, " picked up a fork\n", 100);
		else if (s == EATING)
			ft_strlcat(buff, " is eating\n", 100);
		else if (s == SLEEPING)
			ft_strlcat(buff, " is sleeping\n", 100);
		else if (s == DYING)
			ft_strlcat(buff, " died\n", 100);
		else if (s == FINISHED)
			ft_strlcat(buff, " finished eating\n", 100);
		if (s == DYING || s == FINISHED)
			end = 1;
		ft_putstr_fd(buff, 1);
	}
	pthread_mutex_unlock(&philo->context->mut_write);
}
