/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 18:44:12 by adorigo           #+#    #+#             */
/*   Updated: 2021/01/03 17:01:17 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <stdio.h>
# define EXIT 1
# define NO_EXIT 0
# define PHILO_ATE_ENOUGH 0
# define PHILO_DEAD 1

# define NUM_THREADS	8

typedef struct		s_philo
{
	unsigned long	name;
	unsigned long	start;
	int				eat_count;
	unsigned long	last_time_ate;
	pthread_t		thread_monitoring;
}					t_philo;

typedef struct		s_context
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				*pid;
	t_philo			*philosophers;
	sem_t			*pickup;
	sem_t			*forks;
	sem_t			*eating;
	sem_t			*print;
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
void				print(t_philo *philo, t_status s, int is_dead);
int					ft_free_all(int ret);
void				init_semlink(void);
void				*ft_memset(void *b, int c, size_t len);

#endif
