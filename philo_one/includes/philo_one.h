/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 14:14:57 by adorigo           #+#    #+#             */
/*   Updated: 2021/03/06 14:41:16 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef enum	e_status
{
	EATING,
	SLEEPING,
	FORK,
	THINKING,
	DYING
}				t_status;

struct s_context;

typedef struct			s_philo
{
	int					pos;
	int					eating;
	unsigned long		time_limit;
	unsigned long		last_time_ate;
	int					lfork;
	int					rfork;
	int					eat_count;
	struct s_context	*context;
	pthread_mutex_t		mutex;
	pthread_mutex_t		mut_eat;
}						t_philo;

typedef struct			s_context
{
	int					amount;
	unsigned long		time_to_die;
	unsigned long		time_to_eat;
	unsigned long		time_to_sleep;
	int					must_eat_count;
	unsigned long		start;
	t_philo				*philosophers;
	pthread_mutex_t		*mut_forks;
	pthread_mutex_t		*mut_write;
	pthread_mutex_t		*mut_philo_dead;
}						t_context;

int						ft_strlen(const char *str);
int						ft_atoi(const char *str);
int						ft_putnbr_fd(unsigned long n, int fd);
int						get_time(void);
int						ft_clear_context(t_context *context);
int						exit_error(const char *str);
int						init(t_context *context, int argc, const char **argv);
void					take_fork(t_philo *philo);
void					drop_fork(t_philo *philo);
void					eating(t_philo *philo);
void					print(t_philo *philo, t_status status);

#endif
