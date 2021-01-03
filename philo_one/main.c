/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 17:26:35 by adorigo           #+#    #+#             */
/*   Updated: 2021/01/03 17:49:34 by adorigo          ###   ########.fr       */
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

int		init_context(int i)
{
	t_context	*cxt;
	int			ret;

	ret = 0;
	cxt = ft_get_context();
	cxt->philo_alive = cxt->num_philo;
	if (!(cxt->forks = malloc(sizeof(pthread_mutex_t) * cxt->num_philo)))
		return (error_ret("ERROR: failed to malloc 'forks'\n", 0));
	if (!(cxt->eating = malloc(sizeof(pthread_mutex_t) * cxt->num_philo)))
		return (error_ret("ERROR: failed to malloc 'eating'\n", 0));
	while (++i < cxt->num_philo)
	{
		ret = pthread_mutex_init(&cxt->forks[i], NULL);
		ret = pthread_mutex_init(&cxt->eating[i], NULL);
	}
	ret = pthread_mutex_init(&cxt->pickup, NULL);
	ret = pthread_mutex_init(&cxt->dropping, NULL);
	ret = pthread_mutex_init(&cxt->alive, NULL);
	ret = pthread_mutex_init(&cxt->print, NULL);
	ret = pthread_mutex_init(&cxt->someone_died, NULL);
	if (ret)
		return (error_ret("failed to init one or several mutex\n", 0));
	return (1);
}

void	*ft_monitoring(void *vp)
{
	t_context	*contxt;
	t_philo		*p;

	contxt = ft_get_context();
	p = vp;
	while (1)
	{
		pthread_mutex_lock(&contxt->eating[p->name]);
		if (!contxt->philo_alive)
			break ;
		if (get_time() - p->last_time_ate > (unsigned long)contxt->time_to_die)
		{
			print(contxt, p, DEAD);
			pthread_mutex_lock(&contxt->someone_died);
			contxt->philo_dead = 1;
			break ;
		}
		pthread_mutex_unlock(&contxt->eating[p->name]);
		usleep(500);
	}
	pthread_mutex_unlock(&contxt->someone_died);
	pthread_mutex_unlock(&contxt->eating[p->name]);
	return (NULL);
}

int		main(int argc, char *argv[])
{
	t_context *context;

	context = ft_get_context();
	if (!parse_input(argc, argv))
		return (EXIT_FAILURE);
	else if (init_context(-1) && ft_creating_philo())
		return (ft_free_all(EXIT_FAILURE));
	while (1)
	{
		if (context->philo_alive == 0)
			break ;
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
