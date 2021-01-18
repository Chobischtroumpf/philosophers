/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 17:26:35 by adorigo           #+#    #+#             */
/*   Updated: 2021/01/18 16:42:27 by adorigo          ###   ########.fr       */
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

static int	set_sem_eating(t_context *context)
{
	int		i;
	char	buff[14];

	if (!(context->eating = malloc(sizeof(sem_t *) * context->num_philo)))
		return (error_ret("Error: failed to malloc 'eating'\n", 0));
	i = 0;
	while (i < context->num_philo)
	{
		semaphore_name(i, buff);
		if (!(context->eating[i++] = sem_open(buff, O_CREAT, 0777, 1)))
			return (error_ret("Error: failed to open 'eating'\n", 0));
	}
	return (1);
}

void		init_semlink(void)
{
	t_context	*context;
	char		buff[14];
	int			i;

	context = ft_get_context();
	i = 0;
	while (i < context->num_philo)
	{
		semaphore_name(i++, buff);
		sem_unlink(buff);
	}
	sem_unlink("pickup");
	sem_unlink("putdown");
	sem_unlink("forks");
	sem_unlink("alive");
	sem_unlink("print");
}

int			init_context(void)
{
	t_context	*cxt;

	cxt = ft_get_context();
	cxt->philo_alive = cxt->num_philo;
	if (!(set_sem_eating(cxt)))
		return (0);
	if (!(cxt->pickup = sem_open("pickup", O_CREAT, 0777, 1)))
		return (error_ret("ERROR: failed to open 'pickup'\n", 0));
	if (!(cxt->dropping = sem_open("dropping", O_CREAT, 0777, 1)))
		return (error_ret("ERROR: failed to open 'dropping'\n", 0));
	if (!(cxt->forks = sem_open("forks", O_CREAT, 0777, cxt->num_philo)))
		return (error_ret("ERROR: failed to open 'forks'\n", 0));
	if (!(cxt->alive = sem_open("alive", O_CREAT, 0777, 1)))
		return (error_ret("ERROR: failed to open 'alive'\n", 0));
	if (!(cxt->print = sem_open("print", O_CREAT, 0777, 1)))
		return (error_ret("ERROR: failed to open 'print'\n", 0));
	if (!(cxt->someone_died = sem_open("someone_died", O_CREAT, 0777, 1)))
		return (error_ret("ERROR: failed to open 'someone_died'\n", 0));
	return (1);
}

int			main(int argc, char *argv[])
{
	t_context *context;

	context = ft_get_context();
	if (!parse_input(argc, argv))
		return (EXIT_FAILURE);
	else if (init_context() && ft_creating_philo())
		return (ft_free_all(EXIT_FAILURE));
	while (1)
	{
		sem_wait(context->alive);
		if (context->philo_alive == 0)
		{
			sem_post(context->alive);
			break ;
		}
		sem_post(context->alive);
		if (context->philo_dead)
			break ;
		ft_usleep(1);
	}
	if (!context->philo_dead)
		ft_putstr_fd("All philosophers ate enough :)\n", 1);
	usleep((context->time_to_die + context->time_to_eat) * 1000);
	return (ft_free_all(EXIT_SUCCESS));
}
