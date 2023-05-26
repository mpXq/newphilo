/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:21:45 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/05/26 11:05:17 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philosophers_bonus.h"

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

void	*eat(t_philo *p)
{
	int	i;

	i = 0;
	while (i++ < p->nb_of_philo)
		sem_wait(p->miam);
	p->meals_end = TRUE;
	sem_wait(p->voix);
	kill(p->philo_tab[0], SIGTERM);
	printf(GRN "SUCCESS !!!\n");
	return (NULL);
}

void	need_to_eat(t_philo *p)
{
	pthread_t	food;

	pthread_create(&food, NULL, (void *)eat, p);
}

int	forktab(t_philo *p)
{
	int			i;
	pthread_t	checker;

	i = -1;
	if (p->as_eaten)
		while (++i < p->nb_of_philo)
			sem_wait(p->miam);
	i = -1;
	p->philo_tab = malloc(sizeof(pid_t) * (p->nb_of_philo));
	while (++i < p->nb_of_philo)
	{
		p->philo_tab[i] = fork();
		if (p->philo_tab[i] == 0)
		{
			p->index = i;
			if (p->nb_of_philo != 1)
				pthread_create(&checker, NULL, (void *)death_check, p);
			phases(p);
			exit(0);
		}
	}
	if (p->as_eaten > -1)
		need_to_eat(p);
	i = -1;
	waitpid(-1, &p->status, 0);
	if (WIFEXITED(p->status) || WIFSIGNALED(p->status))
		while (++i < p->nb_of_philo)
			kill(p->philo_tab[i], SIGTERM);
	return (0);
}

int	sem(t_philo *p)
{
	sem_unlink("fourchette");
	p->fork = sem_open("fourchette", O_CREAT | O_EXCL, 0644, p->nb_of_philo);
	if (p->fork == SEM_FAILED)
		return (1);
	sem_unlink("voix");
	p->voix = sem_open("voix", O_CREAT | O_EXCL, 0644, 1);
	if (p->voix == SEM_FAILED)
		return (1);
	sem_unlink("data_race");
	p->data_race = sem_open("data_race", O_CREAT | O_EXCL, 0644, 1);
	if (p->voix == SEM_FAILED)
		return (1);
	sem_unlink("miam");
	p->miam = sem_open("miam", O_CREAT | O_EXCL, 0644, p->nb_of_philo);
	if (p->miam == SEM_FAILED)
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_philo		p;

	if (error_gestion(ac, av))
		return (1);
	p = initializer(av);
	if (sem(&p))
		return (1);
	if (forktab(&p))
		return (1);
	return (0);
}
