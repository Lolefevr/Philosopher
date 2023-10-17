/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolefevr <lolefevr@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:45:34 by lolefevr          #+#    #+#             */
/*   Updated: 2023/08/11 19:14:20 by lolefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hfiles/philo.h"

void	ft_philo_think(t_philo *philo)
{
	print_instr(philo, THINK);
	philo->state = EAT;
}

void	ft_philo_sleep(t_philo *philo)
{
	print_instr(philo, SLEEP);
	usleep(philo->data->time_to_sleep * 1000);
	philo->state = THINK;
}

void	ft_miam_miam(t_philo *philo, int odd)
{
	if (philo->id % 2 != 0)
	{
		if (philo->id == philo->data->nb_philo && odd == 1)
		{
			pthread_mutex_lock(&philo->data->fork[philo->id - 1]);
			pthread_mutex_lock(&philo->data->fork[philo->id - 2]);
			ft_print_fork(philo);
		}
		else
		{
			pthread_mutex_lock(&philo->data->fork[philo->id]);
			pthread_mutex_lock(&philo->data->fork[philo->id - 1]);
			ft_print_fork(philo);
		}
	}
	else
	{
		pthread_mutex_lock(&philo->data->fork[philo->id - 1]);
		pthread_mutex_lock(&philo->data->fork[philo->id - 2]);
		ft_print_fork(philo);
	}
	ft_miam_suite(philo, odd);
}

void	ft_miam_suite(t_philo *philo, int odd)
{
	print_instr(philo, EAT);
	philo->nb_meal++;
	philo->last_meal = get_time();
	usleep(philo->data->time_to_eat * 1000);
	philo->state = SLEEP;
	if (philo->id % 2 != 0)
	{
		if (philo->id == philo->data->nb_philo && odd == 1)
		{
			pthread_mutex_unlock(&philo->data->fork[philo->id - 1]);
			pthread_mutex_unlock(&philo->data->fork[philo->id - 2]);
		}
		else
		{
			pthread_mutex_unlock(&philo->data->fork[philo->id]);
			pthread_mutex_unlock(&philo->data->fork[philo->id - 1]);
		}
	}
	else
	{
		pthread_mutex_unlock(&philo->data->fork[philo->id - 1]);
		pthread_mutex_unlock(&philo->data->fork[philo->id - 2]);
	}
}

void	*routine(t_philo *p)
{
	while (p->data->nb_meal_max > p->nb_meal || p->data->nb_meal_max == -42)
	{
		if (is_philo_dead(p))
			return (NULL);
		if (p->state == THINK)
			ft_philo_think(p);
		else if (p->state == EAT)
		{
			if (p->data->nb_philo % 2 == 0)
				ft_miam_miam(p, 0);
			else
				ft_miam_miam(p, 1);
		}
		else if (p->state == SLEEP)
			ft_philo_sleep(p);
	}
	return (NULL);
}
