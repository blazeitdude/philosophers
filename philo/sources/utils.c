/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldione <ldione@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 16:48:38 by ldione            #+#    #+#             */
/*   Updated: 2022/06/15 19:21:37 by ldione           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <stdio.h>
#include <pthread.h>

int	ft_atoi(const char *s)
{
	int		minp;
	int		answ;
	int		count;

	count = 0;
	minp = 1;
	answ = 0;
	while (*s && (*s == ' ' || *s == '\n' || *s == '\v' \
				|| *s == '\f' || *s == '\r' || *s == '\t'))
		s++;
	if (*s == '-')
		minp = -1;
	if (*s == '-' || *s == '+')
		s++;
	while (*s >= '0' && *s <= '9' && *s)
	{
		answ = answ * 10 + *s - 48;
		count++;
		s++;
	}
	if (count > 10 && minp == -1)
		return (0);
	else if (count > 10 && minp == 1)
		return (0);
	return (minp * answ);
}

long long int	timestamp(void)
{
	struct timeval	t1;

	gettimeofday(&t1, NULL);
	return ((t1.tv_sec * 1000) + (t1.tv_usec / 1000));
}

int	write_error(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	write(2, "Error: ", 7);
	write(2, str, len);
	write(2, "\n", 1);
	return (1);
}

int	error_manager(int error)
{
	if (error == 1)
		return (write_error("error of argument"));
	if (error == 2)
		return (write_error("error of intializing mutex"));
	return (1);
}
