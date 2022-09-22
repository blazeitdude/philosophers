/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldione <ldione@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 18:16:44 by ldione            #+#    #+#             */
/*   Updated: 2022/06/13 22:29:53 by ldione           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include "errors.h"
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

# define TAKEN "taken a fork"
# define EATING "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DEAD   "is dead"

typedef struct s_philo
{
	int				name;
	pid_t			pid;
	long long int	last_eat;
	int				count_ate;
	struct s_arg	*arg;
	pthread_t		death_checker;
}	t_philo;

typedef struct s_arg
{
	int				philo_numb;
	int				t_t_d;
	int				t_t_e;
	int				t_t_s;
	int				n_e_p_m_e;
	int				is_any_died;
	long long int	f_timestamp;
	sem_t			*forks;
	sem_t			*writing;
	sem_t			*perm_to_eat;
	t_philo			philos[201];
}	t_arg;

long long int	timestamp(void);
void			philo_life(void *v_philo);
void			launcher(t_arg *arg);
void			say(long long int start, int name, char *s, sem_t *writing);
void			init_all(t_arg *arg, char **argv);
int				ft_atoi(const char *s);

#endif