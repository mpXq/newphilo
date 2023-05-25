/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_checker_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 12:52:53 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/05/25 17:24:13 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philosophers_bonus.h"

void	*death_check(t_philo *p)
{
	int		i;

	i = 0;
	while (1)
	{
		if (gtime() - p->start - p->last_meal >= (size_t)p->time_to_die)
		{
			memset(&p->is_dead, 1, 1);
			printf(RED "%lu %d died\n", gtime() - p->start, p->index + 1);
			break ;
		}
		usleep(70);
	}
	return (NULL);
}
