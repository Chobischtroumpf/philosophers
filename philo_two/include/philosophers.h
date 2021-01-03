/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 18:44:12 by adorigo           #+#    #+#             */
/*   Updated: 2021/01/03 17:50:21 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <fcntl.h>
# include <sys/time.h>
# include <string.h>
# include <stdio.h>
# include <semaphore.h>

# define NUM_THREADS	8

typedef struct		s_philo
{
	int				eat_count;
	unsigned long	name;
	unsigned long	last_time_ate;
	unsigned long	start;
	pthread_t		thread;
	pthread_t		thread_monitoring;
}					t_philo;

typedef struct		s_context
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				philo_alive;
	int				philo_dead;
	t_philo			*philosophers;
	sem_t			*forks;
	sem_t			**eating;
	sem_t			*pickup;
	sem_t			*dropping;
	sem_t			*print;
	sem_t			*alive;
	sem_t			*someone_died;
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
void				semaphore_name(int i, char buff[]);
void				init_semlink(void);
void				*ft_memset(void *b, int c, size_t len);

#endif
