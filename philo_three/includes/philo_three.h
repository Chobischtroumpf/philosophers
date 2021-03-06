/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 14:14:57 by adorigo           #+#    #+#             */
/*   Updated: 2021/04/16 11:33:49 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H 1

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <signal.h>
# include <stdio.h>

# define SEM_FORK		"psemFork"
# define SEM_WRITE		"psemWrite"
# define SEM_DEAD		"psemDead"
# define SEM_EXIT		"psemExit"
# define SEM_PHILO		"psemPhilo"
# define SEM_PHILOEAT	"psemPhiloEat"

# define	EATING 0
# define	SLEEPING 1
# define	FORK 2
# define	THINKING 3
# define	DYING 4

struct	s_context;

typedef struct s_philo
{
	pid_t				pid;
	int					pos;
	unsigned long		time_limit;
	unsigned long		last_time_ate;
	int					eat_count;
	sem_t				*mutex;
}						t_philo;

typedef struct s_context
{
	int					exit_thread;
	int					amount;
	unsigned long		time_to_die;
	unsigned long		time_to_eat;
	unsigned long		time_to_sleep;
	int					must_eat_count;
	unsigned long		start;
	int					end;
	t_philo				*philo;
	sem_t				*sem_forks;
	sem_t				*sem_write;
	sem_t				*sem_philo_dead;
	sem_t				*sem_exit_thread;
	sem_t				*sem_eaten_enough;
}						t_context;

int						ft_strlen(const char *str);
int						ft_atoi(const char *str);
void					ft_putstr_fd(char *str, int fd);
void					*ft_memset(void *b, int c, size_t len);
int						ft_clear_context(void);
int						exit_error(const char *str);
int						init(t_context *contxt, int argc, char **argv);
void					eating(t_philo *philo);
void					print(t_philo *philo, int status);
void					ft_usleep(unsigned long sleep_time);
unsigned long			get_time(void);
size_t					ft_strlcat(char *dst, const char *src, size_t size);
int						philo_create_odd(t_context *context);
int						philo_create_even(t_context *context);
int						routine(void *philo_void);
void					*monitor(void *context_void);
sem_t					*ft_sem_open(char const *name, int value);
char					*make_semaphore_name(char const *base, char *buffer,
							int position);
int						ft_strcpy(char *dst, const char *src);
t_context				*get_context(void);

#endif
