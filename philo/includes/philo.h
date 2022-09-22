/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldione <ldione@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:18:51 by ldione            #+#    #+#             */
/*   Updated: 2022/06/15 18:21:37 by ldione           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <errno.h>
# include "errors.h"
# include <stdbool.h>
# include <pthread.h>

# define TAKEN "has  taken a fork"
# define EATING "is eating"
# define THINKING "is thinking"
# define SLEEPING "is sleeping"

typedef struct s_philo
{
	int				name;
	int				left_f;
	int				right_f;
	int				n_o_e;
	long long int	last_eat;
	int				count_eat;
	struct s_arg	*arg;
	pthread_t		thread_id;
}	t_philo;

typedef struct s_arg
{
	int				all_ate;
	int				philo_numb;
	int				t_t_d;
	int				t_t_e;
	int				t_t_s;
	int				n_e_p_m_e;
	long long int	f_timestamp;
	int				is_any_died;
	pthread_mutex_t	on_air;
	pthread_mutex_t	perm_to_eat;
	pthread_mutex_t	forks[201];
	t_philo			philo[201];
}	t_arg;

void			*philo_life(void *inp1);
void			philo_exit(t_arg *arg, t_philo *philos);
int				init_arg(t_arg *arg, char **argv);
int				ft_atoi(const char *s);
long long int	timestamp(void);
void			say(long long int start, int name, char *s, t_arg *arg);
void			launch(t_arg *arg);
int				write_error(char *str);
int				error_manager(int error);

#endif
