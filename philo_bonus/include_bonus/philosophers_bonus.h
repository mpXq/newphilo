/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:19:09 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/05/15 10:30:34 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# define BLK "\e[0;90m"
# define RED "\e[0;91m"
# define GRN "\e[0;92m"
# define YEL "\e[0;93m"
# define BLU "\e[0;94m"
# define MAG "\e[0;95m"
# define CYN "\e[0;96m"
# define WHT "\e[0;97m"

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef int	t_boolean;
# define TRUE 1
# define FALSE 0

typedef struct s_philo
{
	pthread_t		*threadtab;
	size_t			start;
	t_boolean		*is_full;
	t_boolean		is_dead;
	t_boolean		meals_end;
	size_t			*last_meal;
	int				*index;
	int				nb_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				as_eaten;
}	t_philo;

/*		UTILITIES		*/

size_t  gtime(void);

/*		ERROR_MANAGEMENT		*/

int		error_gestion(int ac, char **av);
long	ft_atol(const char *str);

#endif