/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:17:44 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/05/26 11:08:03 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philosophers_bonus.h"

size_t	gtime(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

void	ft_sleep(int timeobj, t_philo *p)
{
	size_t		time;
	size_t		nb_of_philo;
	t_boolean	is_dead;

	time = gtime();
	nb_of_philo = p->nb_of_philo;
	is_dead = p->is_dead;
	while (gtime() - time < (size_t)timeobj && is_dead == FALSE)
		usleep(nb_of_philo * 2);
}
