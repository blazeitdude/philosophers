/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldione <ldione@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 18:23:09 by ldione            #+#    #+#             */
/*   Updated: 2022/06/13 22:20:30 by ldione           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "philo_bonus.h"

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
		return (-1);
	return (minp * answ);
}

long long int	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	terminate(char *s)
{
	if (errno == 0)
		printf("%s\n", s);
	else
		perror(s);
	exit(1);
}
