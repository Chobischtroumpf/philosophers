/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 22:17:02 by adorigo           #+#    #+#             */
/*   Updated: 2020/12/03 23:33:52 by adorigo          ###   ########.fr       */
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
	size_t	size;
	char	t[20];

	size = sizeof(buff);
	memset(t, 0, 20);
	digit = count_digit(time);
	num_to_str(t, time, digit);
	ft_strlcat(buff, t, size);
	ft_strlcat(buff, " ", size);
	memset(t, 0, 20);
	digit = count_digit(index + 1);
	num_to_str(t, index + 1, digit);
	ft_strlcat(buff, t, size);
}

void		print(t_context *context, t_philo *philo, t_status s)
{
	char		buff[100];

	memset(buff, 0, 100);
	copy_to_buff(buff, get_time() - philo->start, philo->name);
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
	pthread_mutex_lock(&context->someone_died);
	if (context->philo_dead)
	{
		pthread_mutex_unlock(&context->someone_died);
		return ;
	}
	pthread_mutex_unlock(&context->someone_died);
	pthread_mutex_lock(&context->print);
	ft_putstr_fd(buff, 1);
	if (!(s == DEAD))
		pthread_mutex_unlock(&context->print);
}
