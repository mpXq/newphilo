/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:17:44 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/05/26 11:13:01 by pfaria-d         ###   ########.fr       */
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

static void	initialize_status(t_philo *p)
{
	int	i;

	i = 0;
	while (i < p->nb_of_philo)
	{
		p->is_full[i] = FALSE;
		i++;
	}
}

t_philo	initializer(char **av)
{
	t_philo	p;

	p.nb_of_philo = ft_atol(av[1]);
	p.is_dead = FALSE;
	p.is_full = malloc(sizeof(t_boolean) * p.nb_of_philo);
	p.time_to_die = ft_atol(av[2]);
	p.time_to_eat = ft_atol(av[3]);
	p.time_to_sleep = ft_atol(av[4]);
	p.meals_end = FALSE;
	p.start = gtime();
	p.as_eaten = -1;
	p.last_meal = 0;
	initialize_status(&p);
	if (av[5])
		p.as_eaten = ft_atol(av[5]);
	return (p);
}

void	exit_main(t_philo *p)
{
	int	i;

	if (p->as_eaten > -1)
		need_to_eat(p);
	i = -1;
	waitpid(-1, &p->status, 0);
	if (WIFEXITED(p->status) || WIFSIGNALED(p->status))
		while (++i < p->nb_of_philo)
			kill(p->philo_tab[i], SIGTERM);
}
