/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 18:44:12 by adorigo           #+#    #+#             */
/*   Updated: 2021/02/04 23:08:05 by adorigo          ###   ########.fr       */
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

typedef struct		s_philo
{
	int				eat_count;
	int				is_dead;
	unsigned long	last_time_ate;
	unsigned long	name;
	pthread_t		thread;
	pthread_t		thread_monitoring;
}					t_philo;

typedef struct		s_context
{
	unsigned long	start;
	int				philo_dead;
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				philo_alive;
	t_philo			*philosophers;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*eating;
	pthread_mutex_t	alive;
	pthread_mutex_t	someone_died;
	pthread_mutex_t	print;
	pthread_mutex_t	block;
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
void				ft_usleep(unsigned long sleep_time);

#endif
