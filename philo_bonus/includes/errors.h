/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldione <ldione@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:52:26 by ldione            #+#    #+#             */
/*   Updated: 2022/06/13 22:31:32 by ldione           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include <errno.h>
# define ERR_OF_ARG	"incorrect arguments"
# define ERR_OF_MUTEX "error of init mutex"
# define ERR_OF_DIE "philosopher died"
# define ERR_OF_ALLOC "error of allocation memory"
# define ERR_OF_PROCC "process initialization error"

void	terminate(char *s);

#endif