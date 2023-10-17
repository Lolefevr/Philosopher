/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolefevr <lolefevr@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 13:04:01 by lolefevr          #+#    #+#             */
/*   Updated: 2023/08/12 14:13:53 by lolefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hfiles/philo.h"

void	ft_created_thread(t_philo **phi)
{
	int	i;
	int	nbphilo;

	i = 0;
	nbphilo = phi[0]->data->nb_philo;
	while (i < nbphilo)
	{
		if (pthread_create(phi[i]->thread, NULL, (void *)&routine, phi[i]) != 0)
			return ;
		i++;
	}
	i = 0;
	while (i < nbphilo)
	{
		if (pthread_join(*phi[i]->thread, NULL) != 0)
			return ;
		i++;
	}
}

t_philo	**init_struct(t_data *data)
{
	int		i;
	int		nbrphilo;
	t_philo	**philo;

	nbrphilo = data->nb_philo;
	philo = malloc(sizeof(t_philo *) * data->nb_philo);
	if (!philo)
		return (NULL);
	i = 0;
	while (i < nbrphilo)
	{
		philo[i] = malloc(sizeof(t_philo));
		if (!philo[i])
			return (NULL);
		philo[i]->data = data;
		philo[i]->id = i + 1;
		philo[i]->nb_meal = 0;
		philo[i]->last_meal = 0;
		philo[i]->state = 2;
		philo[i]->thread = malloc(sizeof(pthread_t));
		i++;
	}
	return (philo);
}

t_data	*ft_data_init(char **argv, t_data *data)
{
	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->start_time = get_time();
	data->nb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->dead = 0;
	if (data->time_to_eat == data->time_to_sleep)
		data->time_to_sleep += 2;
	if (argv[5])
		data->nb_meal_max = ft_atoi(argv[5]);
	else
		data->nb_meal_max = -42;
	data->fork = ft_init_mutex(data);
	if (data->fork == NULL)
		return (NULL);
	return (data);
}

pthread_mutex_t	*ft_init_mutex(t_data *data)
{
	int				i;
	pthread_mutex_t	*fork;

	fork = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!fork)
		return (NULL);
	pthread_mutex_init(&data->mdead, NULL);
	pthread_mutex_init(&data->print, NULL);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&fork[i], NULL);
		i++;
	}
	return (fork);
}

int	main(int argc, char **argv)
{
	t_philo	**philo;
	t_data	*data;

	data = NULL;
	if (ft_check_arg(argc, argv))
		return (1);
	data = ft_data_init(argv, data);
	philo = init_struct(data);
	if ((data == NULL) || philo == NULL)
		return (1);
	if (philo[0]->data->time_to_die * 6 <= philo[0]->data->time_to_eat
		|| philo[0]->data->time_to_die * 6 <= philo[0]->data->time_to_sleep
		|| ft_atoi(argv[1]) > 200 || philo[0]->data->time_to_eat <= 3
		|| philo[0]->data->time_to_sleep <= 3)
	{
		printf("** ROBIN ARG DETECTED ** PLZ PUT A DESCENT ARG\n");
		free_all(philo, data);
		return (0);
	}
	ft_created_thread(philo);
	free_all(philo, data);
	return (0);
}
