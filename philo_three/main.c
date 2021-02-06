/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 17:26:35 by adorigo           #+#    #+#             */
/*   Updated: 2021/02/04 22:01:43 by adorigo          ###   ########.fr       */
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
		if ((context->must_eat_count = ft_atoi(argv[5])) < 0)
			return (format_error("num_must_eat", 0));
	return (1);
}

void		init_semlink(void)
{
	sem_unlink("forks");
	sem_unlink("eat");
	sem_unlink("print");
}

int			init_context(void)
{
	t_context	*cxt;

	cxt = ft_get_context();
	if (!(cxt->pid = malloc(sizeof(int) * cxt->num_philo)))
		return (error_ret("ERROR: failed to malloc\n", 0));
	if (!(cxt->forks = sem_open("forks", O_CREAT, 0777, cxt->num_philo)))
		return (error_ret("ERROR: failed to open 'forks'\n", 0));
	if (!(cxt->print = sem_open("print", O_CREAT, 0777, 1)))
		return (error_ret("ERROR: failed to open 'print'\n", 0));
	if (!(cxt->eating = sem_open("eat", O_CREAT, 0777, 1)))
		return (error_ret("ERROR: failed to open 'eat'\n", 0));
	cxt->start = get_time();
	return (1);
}

static void	wait_and_kill(void)
{
	t_context	*context;
	int			i;
	int			status;

	context = ft_get_context();
	status = 0;
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status) && (WEXITSTATUS(status) == PHILO_DEAD))
		{
			i = 0;
			while (i < context->num_philo)
				kill(context->pid[i++], SIGINT);
		}
		else if (WIFEXITED(status) && (WEXITSTATUS(status) == PHILO_ATE_ENOUGH))
		{
			if (--context->num_philo == 0)
			{
				ft_putstr_fd("Every philosopher eat enough!\n", 1);
				return ;
			}
		}
	}
}

int			main(int argc, char *argv[])
{
	init_semlink();
	if (!parse_input(argc, argv))
		return (EXIT_FAILURE);
	else if (init_context() && ft_creating_philo())
		return (ft_free_all(EXIT_FAILURE));
	wait_and_kill();
	return (ft_free_all(EXIT_SUCCESS));
}
