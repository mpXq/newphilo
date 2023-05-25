/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phases.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:47:19 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/05/25 12:34:42 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	ft_strncmp(const char *str1, const char *str2, size_t length)
{
	size_t	i;

	if (length == 0)
		return (0);
	if (!str1 && !str2)
		return (0);
	if (!str1)
		return ((unsigned char)str2[0]);
	if (!str2)
		return ((unsigned char)str1[0]);
	i = 0;
	while (str1[i] == str2[i] && i < length - 1 && str1[i] && str2[i])
		i++;
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}

void	print_message(t_philo *p, t_values *v, char *message)
{
	size_t	is_dead;

	sem_wait(p->data_race);
	is_dead = p->is_dead;
	sem_post(p->data_race);
	sem_wait(p->voix);
	if (is_dead == FALSE && !p->meals_end)
		printf("%lu %d %s\n", gtime() - p->start, v->index + 1, message);
	sem_post(p->voix);
}

void	is_eating(t_philo *p, t_values *v)
{
	sem_wait(p->fork);
	print_message(p, v, MAG"has taken a fork"WHT);
	sem_wait(p->fork);
	print_message(p, v, MAG"has taken a fork"WHT);
	print_message(p, v, BLU "is eating" WHT);
	p->last_meal[v->index] = gtime() - p->start;
	v->nb_of_meals++;
	if (v->nb_of_meals >= p->as_eaten && p->as_eaten != -1)
	{
		p->is_full[v->index] = TRUE;
	}
	ft_sleep(p->time_to_eat, p);
	sem_post(p->fork);
	sem_post(p->fork);
}

static void	multiple_philo_case(t_philo *p, t_values *v)
{
	while (p->meals_end == FALSE && p->is_dead == FALSE)
	{
		is_eating(p, v);
		print_message(p, v, CYN "is sleeping" WHT);
		ft_sleep(p->time_to_sleep, p);
		print_message(p, v, GRN "is thinking" WHT);
	}
}

void	*phases(t_philo *p)
{
	t_values	v;
	static int	i = -1;
	int			nb;

	i++;
	v.index = i;
	nb = p->nb_of_philo;
	v.nb_of_meals = 0;
	v.prev = (i + 1) % p->nb_of_philo;
	if (v.index % 2)
		usleep(100);
	if (nb == 1)
	{
		print_message(p, &v, MAG"has taken a fork"WHT);
		ft_sleep(p->time_to_die, p);
		print_message(p, &v, RED "died" WHT);
	}
	else
		multiple_philo_case(p, &v);
	return (NULL);
}
