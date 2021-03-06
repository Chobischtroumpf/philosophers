/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 17:26:35 by adorigo           #+#    #+#             */
/*   Updated: 2021/03/06 13:51:55 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int			parse_input(int argc, char **argv)
{
	t_context *context;

	context = ft_get_context();
	if (argc < 5 || argc > 6)
		return (amount_arg_error(0));
	if ((context->num_philo = ft_atoi(argv[1])) <= 1)
		return (format_error("number_philos", 0));
	if ((context->time_to_die = ft_atoi(argv[2])) <= 0)
		return (format_error("time_to_die", 0));
	if ((context->time_to_eat = ft_atoi(argv[3])) <= 0)
		return (format_error("time_to_eat", 0));
	if ((context->time_to_sleep = ft_atoi(argv[4])) <= 0)
		return (format_error("time_to_sleep", 0));
	if (argc == 6)
		if ((context->must_eat_count = ft_atoi(argv[5])) <= 0)
			return (format_error("num_must_eat", 0));
	return (1);
}

int			init_semunlink(void)
{
	sem_unlink(SEM_EAT);
	sem_unlink(SEM_PICKUP);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_ALIVE);
	sem_unlink(SEM_BLOCK);
	sem_unlink(SEM_DEAD);
	return (1);
}

int			init_context(void)
{
	t_context	*cxt;

	cxt = ft_get_context();
	cxt->philo_alive = cxt->num_philo;
	if (!(cxt->forks = sem_open(SEM_FORKS, O_CREAT, 0777, cxt->num_philo)))
		return (error_ret("ERROR: failed to open 'forks'\n", 0));
	if (!(cxt->pickup = sem_open(SEM_PICKUP, O_CREAT, 0777, 1)))
		return (error_ret("ERROR: failed to open 'pickup'\n", 0));
	if (!(cxt->eating = sem_open(SEM_EAT, O_CREAT, 0777, 1)))
		return (error_ret("ERROR: failed to open 'forks'\n", 0));
	if (!(cxt->alive = sem_open(SEM_ALIVE, O_CREAT, 0777, 1)))
		return (error_ret("ERROR: failed to open 'alive'\n", 0));
	if (!(cxt->block = sem_open(SEM_BLOCK, O_CREAT, 0777, 1)))
		return (error_ret("ERROR: failed to open 'block'\n", 0));
	if (!(cxt->someone_died = sem_open(SEM_DEAD, O_CREAT, 0777, 1)))
		return (error_ret("ERROR: failed to open 'someone_died'\n", 0));
	cxt->start = get_time();
	context->last_time_ate = context->start;
	return (1);
}

int			main(int argc, char *argv[])
{
	t_context *cxt;

	cxt = ft_get_context();
	init_semunlink();
	if (!parse_input(argc, argv))
		return (EXIT_FAILURE);
	else if (init_context() && ft_creating_philo(cxt))
		return (ft_free_all(EXIT_FAILURE));
	while (1)
	{
		if (cxt->philo_alive == 0)
			break ;
		if (cxt->philo_dead)
			break ;
		ft_usleep(1);
	}
	usleep((cxt->time_to_die + cxt->time_to_eat + cxt->time_to_sleep) * 900);
	return (ft_free_all(EXIT_SUCCESS));
}
