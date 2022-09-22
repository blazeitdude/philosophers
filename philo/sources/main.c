/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldione <ldione@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:33:15 by ldione            #+#    #+#             */
/*   Updated: 2022/06/15 18:48:56 by ldione           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	int		err;
	t_arg	arg;

	if (argc != 5 && argc != 6)
		return (write_error(ERR_OF_ARG));
	err = init_arg(&arg, argv);
	if (err)
		return (error_manager(err));
	launch(&arg);
	return (0);
}
