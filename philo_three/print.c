/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 12:27:00 by adorigo           #+#    #+#             */
/*   Updated: 2021/04/12 14:43:10 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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
	int	i;

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
	print(t_philo *philo, int status)
{
	static int	end = 0;
	char		buff[100];
	t_context	*context;

	context = get_context();
	// printf("before wait sem_write\n");
	sem_wait(context->sem_write);
	// printf("after wait sem_write\n");
	if (!end)
	{
		ft_memset(buff, 0, 100);
		// printf("after memset\n");
		copy_to_buff(buff, get_time() - context->start, philo->pos);
		if (status == THINKING)
			ft_strlcat(buff, " is thinking\n", 100);
		else if (status == FORK)
			ft_strlcat(buff, " picked up a fork\n", 100);
		else if (status == EATING)
			ft_strlcat(buff, " is eating\n", 300);
		else if (status == SLEEPING)
			ft_strlcat(buff, " is sleeping\n", 100);
		else if (status == DYING)
			ft_strlcat(buff, " died\n", 100);
		else if (status == FINISHED)
			ft_strlcat(buff, " finished eating\n", 100);
		if (status == DYING || status == FINISHED)
			end = 1;
		// printf("before puts\n");
		ft_putstr_fd(buff, 1);
	}
	// printf("before post sem_write\n");
	sem_post(context->sem_write);
	// printf("before post sem_write\n");
}
