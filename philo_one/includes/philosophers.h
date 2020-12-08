/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 18:44:12 by adorigo           #+#    #+#             */
/*   Updated: 2020/12/07 18:18:08 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <stdio.h>

# define NUM_THREADS	8

typedef struct		s_philo
{
	unsigned long	last_time_ate;
	unsigned long	eat_count;
	unsigned long	start;
	unsigned long	name;
	int				is_dead;
	pthread_t		thread;
	pthread_t		thread_monitoring;
}					t_philo;

typedef struct		s_context
{
	unsigned long	philo_dead;
	unsigned long	num_philo;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	unsigned long	must_eat_count;
	unsigned long	philo_alive;
	t_philo			*philosophers;
	pthread_mutex_t	*forks;
	pthread_mutex_t *eating;
	pthread_mutex_t	print;
	pthread_mutex_t	alive;
	pthread_mutex_t	someone_died;
	pthread_mutex_t pickup;
	pthread_mutex_t dropping;
}					t_context;

typedef enum		e_status
{
	THINKING,
	EATING,
	SLEEPING,
	TAKING_FORK,
	DEAD
}					t_status;

t_context			*ft_get_context(void);
void				ft_putstr_fd(char *str, int fd);
void				ft_putnbr_fd(unsigned long n, int fd);
unsigned long		get_time(void);
int					ft_atoi(char const *str);
int					ft_strlen(char const *str);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
int					format_error(char *arg, int ret);
int					amount_arg_error(int ret);
int					error_ret(char *str, int ret);
int					ft_creating_philo(void);
void				*ft_monitoring(void *vp);
void				print(t_context *context, t_philo *philo, t_status s);
int					ft_free_all(int ret);

#endif
