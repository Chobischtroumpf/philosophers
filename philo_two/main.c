/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 17:26:35 by adorigo           #+#    #+#             */
/*   Updated: 2020/12/08 12:35:14 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		parse_input(int argc, char **argv)
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
		context->must_eat_count = ft_atoi(argv[5]);
	if (context->must_eat_count < 0)
		return (format_error("num_must_eat", 0));
	return (1);
}

int		init_context(void)
{
	t_context	*cxt;
	int			i;

	i = -1;
	cxt = ft_get_context();
	cxt->philo_alive = cxt->num_philo;
	if (!(cxt->forks = malloc(sizeof(pthread_mutex_t) * cxt->num_philo)))
		return (error_ret("ERROR: failed to malloc 'forks'\n", 0));
	if (!(cxt->eating = malloc(sizeof(pthread_mutex_t) * cxt->num_philo)))
		return (error_ret("ERROR: failed to malloc 'eating'\n", 0));
	while (++i < cxt->num_philo)
	{
		if (pthread_mutex_init(&cxt->forks[i], NULL))
			return (error_ret("ERROR: failed to init 'forks'\n", 0));
		if (pthread_mutex_init(&cxt->eating[i], NULL))
			return (error_ret("ERROR: failed to init 'eating'\n", 0));
	}
	if (pthread_mutex_init(&cxt->pickup, NULL))
		return (error_ret("ERROR: failed to init 'pickup'\n", 0));
	if (pthread_mutex_init(&cxt->dropping, NULL))
		return (error_ret("ERROR: failed to init 'dropping'\n", 0));
	if (pthread_mutex_init(&cxt->alive, NULL))
		return (error_ret("ERROR: failed to init 'alive'\n", 0));
	if (pthread_mutex_init(&cxt->print, NULL))
		return (error_ret("ERROR: failed to init 'print'\n", 0));
	if (pthread_mutex_init(&cxt->someone_died, NULL))
		return (error_ret("ERROR: failed to init 'someone_died'\n", 0));
	return (1);
}

void	*ft_monitoring(void *vp)
{
	t_context	*context;
	t_philo		*p;

	context = ft_get_context();
	p = vp;
	while (1)
	{
		pthread_mutex_lock(&context->eating[p->name]);
		pthread_mutex_lock(&context->alive);
		if (!context->philo_alive)
			break;
		if (get_time() - p->last_time_ate > (unsigned long)context->time_to_die)
		{
			print(context, p, DEAD);
			pthread_mutex_lock(&context->someone_died);
			context->philo_dead = 1;
			break ;
		}
		pthread_mutex_unlock(&context->eating[p->name]);
		pthread_mutex_unlock(&context->alive);
		usleep(500);
	}
	pthread_mutex_unlock(&context->alive);
	pthread_mutex_unlock(&context->someone_died);
	pthread_mutex_unlock(&context->eating[p->name]);
	return (NULL);
}

int		main(int argc, char *argv[])
{
	t_context *context;

	context = ft_get_context();
	if (!parse_input(argc, argv))
		return (EXIT_FAILURE);
	else if (init_context() && ft_creating_philo())
		return (ft_free_all(EXIT_FAILURE));
	while (1)
	{
		pthread_mutex_lock(&context->alive);
		if (context->philo_alive == 0)
		{
			pthread_mutex_unlock(&context->alive);
			break ;
		}
		pthread_mutex_unlock(&context->alive);
		if (context->philo_dead)
			break ;
		usleep(1000);
	}
	if (!context->philo_dead)
	{
		pthread_mutex_lock(&context->print);
		ft_putstr_fd("All philosophers ate enough :)\n", 1);
		pthread_mutex_unlock(&context->print);
	}
	usleep((context->time_to_die + context->time_to_eat) * 1000);
	return (ft_free_all(EXIT_SUCCESS));
}
