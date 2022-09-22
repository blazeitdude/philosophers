/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldione <ldione@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:33:35 by ldione            #+#    #+#             */
/*   Updated: 2022/06/15 19:19:39 by ldione           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>

static int	init_mutex(t_arg *arg)
{
	int	i;

	i = -1;
	while (++i < arg->philo_numb)
	{
		if (pthread_mutex_init(&arg->forks[i], NULL))
			return (2);
		i++;
	}
	if (pthread_mutex_init(&arg->perm_to_eat, NULL))
		return (2);
	if (pthread_mutex_init(&arg->on_air, NULL))
		return (2);
	return (0);
}

static void	init_philo(t_arg *arg)
{
	int	i;

	i = -1;
	while (++i < arg->philo_numb)
	{
		arg->philo[i].name = i;
		arg->philo[i].left_f = i;
		if (arg->philo_numb != 1)
			arg->philo[i].right_f = (i + 1) % arg->philo_numb;
		else
			arg->philo[i].right_f = -1;
		arg->philo[i].last_eat = 0;
		arg->philo[i].count_eat = 0;
		arg->philo[i].arg = arg;
	}
}

int	init_arg(t_arg *arg, char **argv)
{
	arg->philo_numb = ft_atoi(argv[1]);
	if (!arg->philo_numb || arg->philo_numb > 201 || arg->philo_numb <= 0)
		return (1);
	arg->t_t_d = ft_atoi(argv[2]);
	if (!arg->t_t_d || arg->t_t_d < 60 || arg->t_t_d <= 0)
		return (1);
	arg->t_t_e = ft_atoi(argv[3]);
	if (!arg->t_t_e || arg->t_t_e < 60 || arg->t_t_e <= 0)
		return (1);
	arg->t_t_s = ft_atoi(argv[4]);
	if (!arg->t_t_s || arg->t_t_s < 60 || arg->t_t_s <= 0)
		return (1);
	if (!argv[5])
		arg->n_e_p_m_e = -1;
	else
		arg->n_e_p_m_e = ft_atoi(argv[5]);
	if (!arg->n_e_p_m_e && arg->n_e_p_m_e <= 0)
		return (1);
	arg->is_any_died = 0;
	arg->all_ate = 0;
	init_philo(arg);
	return (init_mutex(arg));
}

static void	deathchecking(t_arg *arg, t_philo *philo)
{
	int	i;

	while (!arg->all_ate)
	{
		while (++i < arg->philo_numb && !(arg->is_any_died))
		{
			pthread_mutex_lock(&arg->perm_to_eat);
			if ((int)(timestamp() - philo[i].last_eat) >= arg->t_t_d)
			{
				printf("%d %d died", (int)(timestamp() - arg->f_timestamp) \
						, philo[i].name + 1);
				arg->is_any_died = 1;
			}
			pthread_mutex_unlock(&arg->perm_to_eat);
			usleep(200);
		}
		if (arg->is_any_died == 1)
			break ;
		i = 0;
		while (arg->n_e_p_m_e != -1 && i < arg->philo_numb
			&& arg->philo[i].count_eat >= arg->n_e_p_m_e)
			i++;
		if (i == arg->philo_numb)
			arg->all_ate = 1;
	}
}

void	launch(t_arg *arg)
{
	int		i;
	t_philo	*philos;

	philos = arg->philo;
	i = -1;
	arg->f_timestamp = timestamp();
	while (++i < arg->philo_numb)
	{
		philos[i].last_eat = timestamp();
		pthread_create(&philos[i].thread_id, NULL, philo_life, &philos[i]);
	}
	deathchecking(arg, arg->philo);
	philo_exit(arg, philos);
}
