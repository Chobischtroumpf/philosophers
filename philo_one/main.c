/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 17:26:35 by adorigo           #+#    #+#             */
/*   Updated: 2020/08/04 10:46:41 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

extern int	g_died;
t_data		g_data;

int		init(t_data *data)
{
	data->mutex = \
		(pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) * data->amount);
}

int		parse_input(int argc, char **argv, t_data *data)
{
	if (argc != 6 && argc != 5)
		return (0);
	data->amount = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->must_eat_count = ft_atoi(argv[5]);
	else
		data->must_eat_count = -1;
	
}

int		main (int argc, char *argv[])
{
	pthread_t	*threads;
	t_philo		*philos;

	if (!parse_input(argc, argv, &g_data))
		return (error_ret("Argument Error\n"));
	else if (init(&g_data) == -1)

}