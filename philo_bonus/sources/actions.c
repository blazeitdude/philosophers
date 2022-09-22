/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldione <ldione@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 21:22:12 by ldione            #+#    #+#             */
/*   Updated: 2022/06/15 20:19:57 by ldione           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	*death_checker(void *inp)
{
	t_arg	*arg;
	t_philo	*me;

	me = (t_philo *)inp;
	arg = (t_arg *)me->arg;
	while (!arg->is_any_died)
	{
		sem_wait(arg->perm_to_eat);
		if ((int)(timestamp() - me->last_eat) >= arg->t_t_d)
		{
			say(arg->f_timestamp, me->name, DEAD, arg->writing);
			arg->is_any_died = 1;
			sem_wait(arg->writing);
			exit(1);
		}
		sem_post(arg->perm_to_eat);
		usleep(500);
		if ((arg->n_e_p_m_e != -1) && (me->count_ate >= arg->n_e_p_m_e))
			break ;
	}
	return (NULL);
}

static void	philo_sleep(t_arg *arg, int time)
{
	long long int	t;

	t = timestamp();
	while (!arg->is_any_died)
	{
		if ((int)(timestamp() - t) >= time)
			break ;
		usleep(100);
	}
}

static void	philo_eat(t_arg *arg, t_philo *me)
{
	if (!arg->is_any_died)
	{
		sem_wait(arg->forks);
		say(arg->f_timestamp, me->name, TAKEN, arg->writing);
		sem_wait(arg->forks);
		say(arg->f_timestamp, me->name, TAKEN, arg->writing);
		sem_wait(arg->perm_to_eat);
		say(arg->f_timestamp, me->name, EATING, arg->writing);
		me->last_eat = timestamp();
		sem_post(arg->perm_to_eat);
		philo_sleep(arg, arg->t_t_e);
		sem_post(arg->forks);
		sem_post(arg->forks);
		me->count_ate++;
	}
}

void	say(long long int start, int name, char *s, sem_t *writing)
{
	sem_wait(writing);
	printf("%d %d %s\n", (int)(timestamp() - start), name + 1, s);
	sem_post(writing);
}

void	philo_life(void *v_philo)
{
	t_arg	*arg;
	t_philo	*me;

	me = (t_philo *)v_philo;
	arg = me->arg;
	me->last_eat = timestamp();
	pthread_create(&me->death_checker, NULL, death_checker, me);
	if (me->name % 2)
		usleep(20000);
	while (!arg->is_any_died)
	{
		philo_eat(arg, me);
		if ((arg->n_e_p_m_e != -1) && (me->count_ate >= arg->n_e_p_m_e))
			break ;
		say(arg->f_timestamp, me->name, SLEEP, arg->writing);
		philo_sleep(arg, arg->t_t_s);
		say(arg->f_timestamp, me->name, THINK, arg->writing);
	}
	pthread_join(me->death_checker, NULL);
	exit(0);
}
