/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldione <ldione@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 20:56:36 by ldione            #+#    #+#             */
/*   Updated: 2022/06/15 20:18:28 by ldione           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	init_philo(t_arg *arg)
{
	int		i;
	t_philo	*philo;

	philo = arg->philos;
	i = -1;
	while (++i < arg->philo_numb)
	{
		philo[i].name = i;
		philo[i].arg = arg;
		philo[i].count_ate = 0;
	}
}

static void	init_sema(t_arg *arg)
{
	sem_unlink("!forks!");
	sem_unlink("!writing!");
	sem_unlink("!perm!");
	arg->forks = sem_open("!forks!", O_CREAT, S_IRWXU, arg->philo_numb);
	arg->perm_to_eat = sem_open("!perm!", O_CREAT, S_IRWXU, 1);
}

void	init_all(t_arg *arg, char **argv)
{
	arg->philo_numb = ft_atoi(argv[1]);
	if (!arg->philo_numb || arg->philo_numb >= 201 || arg->philo_numb <= 0)
		terminate(ERR_OF_ARG);
	arg->t_t_d = ft_atoi(argv[2]);
	if (!arg->t_t_d || arg->t_t_d < 60 || arg->t_t_d <= 0)
		terminate(ERR_OF_ARG);
	arg->t_t_e = ft_atoi(argv[3]);
	if (!arg->t_t_e || arg->t_t_e < 60 || arg->t_t_e <= 0)
		terminate(ERR_OF_ARG);
	arg->t_t_s = ft_atoi(argv[4]);
	if (!arg->t_t_s || arg->t_t_s < 60 || arg->t_t_s <= 0)
		terminate(ERR_OF_ARG);
	if (argv[5])
		arg->n_e_p_m_e = ft_atoi(argv[5]);
	else
		arg->n_e_p_m_e = -1;
	if (!arg->n_e_p_m_e && arg->n_e_p_m_e <= 0)
		terminate(ERR_OF_ARG);
	arg->is_any_died = 0;
	init_sema(arg);
	init_philo(arg);
}

static void	philo_exit(t_arg *arg)
{
	int	i;
	int	ret;

	i = 0;
	while (i < arg->philo_numb)
	{
		waitpid(-1, &ret, 0);
		if (ret != 0)
		{
			i = -1;
			while (++i < arg->philo_numb)
				kill(arg->philos[i].pid, 15);
			break ;
		}
		i++;
	}
	sem_close(arg->forks);
	sem_close(arg->writing);
	sem_close(arg->perm_to_eat);
	sem_unlink("!forks!");
	sem_unlink("!writing!");
	sem_unlink("!perm!");
}

void	launcher(t_arg *arg)
{
	t_philo	*philos;
	int		i;

	philos = arg->philos;
	i = -1;
	arg->f_timestamp = timestamp();
	while (++i < arg->philo_numb)
	{
		philos[i].pid = fork();
		if (philos[i].pid < 0)
			terminate(ERR_OF_PROCC);
		if (philos[i].pid == 0)
			philo_life(&philos[i]);
		usleep(200);
	}
	philo_exit(arg);
}
