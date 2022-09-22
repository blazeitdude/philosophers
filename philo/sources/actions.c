/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldione <ldione@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 19:03:30 by ldione            #+#    #+#             */
/*   Updated: 2022/06/15 18:59:32 by ldione           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>

void	philo_sleep(int time_sleep, t_arg *arg)
{
	int		start;

	start = timestamp();
	while (!(arg->is_any_died))
	{
		if ((int)(timestamp() - start) >= time_sleep)
			break ;
		usleep(50);
	}
}

void	eat(t_arg *arg, t_philo *me)
{
	if (!arg->is_any_died)
	{
		pthread_mutex_lock(&arg->forks[me->left_f]);
		say(arg->f_timestamp, me->name, TAKEN, arg);
		if (me->right_f == -1)
		{
			arg->is_any_died = 1;
			printf("%d %d died", (int)(timestamp() - arg->f_timestamp) \
						, me->name + 1);
			return ;
		}
		pthread_mutex_lock(&arg->forks[me->right_f]);
		say(arg->f_timestamp, me->name, TAKEN, arg);
		pthread_mutex_lock(&arg->perm_to_eat);
		say(arg->f_timestamp, me->name, EATING, arg);
		me->last_eat = timestamp();
		pthread_mutex_unlock(&arg->perm_to_eat);
		philo_sleep(arg->t_t_e, arg);
		pthread_mutex_unlock(&arg->forks[me->left_f]);
		pthread_mutex_unlock(&arg->forks[me->right_f]);
		me->count_eat++;
	}
}

void	*philo_life(void *inp1)
{
	t_arg	*arg;
	t_philo	*me;

	me = (t_philo *)inp1;
	arg = (t_arg *)me->arg;
	if (me->name % 2 == 1)
		usleep(15000);
	while (!(arg->is_any_died) && (arg->all_ate != 1))
	{
		eat(arg, me);
		if (arg->all_ate == 1)
			break ;
		say(arg->f_timestamp, me->name, SLEEPING, arg);
		philo_sleep(arg->t_t_s, arg);
		say(arg->f_timestamp, me->name, THINKING, arg);
	}
	return (NULL);
}

void	philo_exit(t_arg *arg, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < arg->philo_numb)
		pthread_join(philos[i].thread_id, NULL);
	while (++i < arg->philo_numb)
	{
		pthread_mutex_destroy(&arg->forks[i]);
	}
	pthread_mutex_destroy(&arg->perm_to_eat);
	pthread_mutex_destroy(&arg->on_air);
}

void	say(long long int start, int name, char *s, t_arg *arg)
{
	long long int	t2;

	t2 = timestamp();
	pthread_mutex_lock(&arg->on_air);
	if (!arg->is_any_died)
		printf("%d %d %s\n", (int)(t2 - start), name + 1, s);
	pthread_mutex_unlock(&arg->on_air);
}
