/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolefevr <lolefevr@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 13:04:03 by lolefevr          #+#    #+#             */
/*   Updated: 2023/08/11 17:08:30 by lolefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hfiles/philo.h"

void	free_all(t_philo **philo, t_data *data)
{
	int	i;
	int	nbr;

	usleep(30000);
	nbr = data->nb_philo - 1;
	ft_destroy_mut(data, nbr);
	i = 0;
	while (i < nbr)
	{
		free(philo[i]->thread);
		free(philo[i]);
		i++;
	}
	free(philo[i]->thread);
	free(philo[i]);
	free(data->fork);
	free(data);
	free(philo);
}

void	ft_destroy_mut(t_data *data, int nbr)
{
	int	i;

	i = 0;
	while (i < nbr)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&data->mdead);
	pthread_mutex_destroy(&data->print);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	isnegative;

	result = 0;
	isnegative = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
	{
		str++;
	}
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			isnegative = -isnegative;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str -48;
		str++;
	}
	return (result * isnegative);
}

long long int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	is_philo_dead(t_philo *philo)
{
	int	time_before_die;

	if (philo->last_meal == 0)
		return (0);
	if (philo->state == DEAD)
		return (1);
	pthread_mutex_lock(&philo->data->mdead);
	if (philo->data->dead != 0)
	{
		pthread_mutex_unlock(&philo->data->mdead);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->mdead);
	time_before_die = get_time() - philo->last_meal;
	if (time_before_die > philo->data->time_to_die)
	{
		ft_chuimort(philo);
		return (1);
	}
	return (0);
}
