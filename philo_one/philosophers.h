/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 18:44:12 by adorigo           #+#    #+#             */
/*   Updated: 2020/08/04 10:48:37 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define NUM_THREADS	8

typedef struct	s_data
{
	int				amount;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				philo_idx;
	int				n_eating;
	int				max_eating;

	uint64_t		start;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	dead;
	pthread_mutex_t pickup;
}				t_data;

typedef struct			s_philo
{
	pthread_mutex_t		*left;
	pthread_mutex_t		*right;
	int					idx;
	int					is_stopped;
	int					count;
	uint64_t			last_eat_time;
}						t_philo;

#endif
