/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 14:14:46 by adorigo           #+#    #+#             */
/*   Updated: 2021/03/06 15:09:25 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"



static int	start_thread(t_context *context)
{
	
}

int main(int argc, char **argv)
{
	t_context	context;

	if (argc < 5 || argc > 6)
		return (exit_error("error: wrong amount of args\n"));
	if (init(&context, argc, argv))
		return (ft_clear_context(&context) && exit_error("fatal error\n"));
	if (start_thread(&context))
		return (ft_clear_context(&context) && exit_error("fatal error\n"));
	pthread_mutex_lock(&context.mut_philo_dead);
	pthread_mutex_unlock(&context.mut_philo_dead);
	usleep((context.time_to_die + context.time_to_eat + context.time_to_sleep) * 900);
	ft_clear_context(&context);
}