/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldione <ldione@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 18:20:01 by ldione            #+#    #+#             */
/*   Updated: 2022/06/13 22:35:27 by ldione           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include <stdio.h>
#include <philo_bonus.h>

int	main(int argc, char **argv)
{
	t_arg	arg;

	errno = 0;
	if (argc != 5 && argc != 6)
		terminate(ERR_OF_ARG);
	init_all(&arg, argv);
	launcher(&arg);
}
