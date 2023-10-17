/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolefevr <lolefevr@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 01:55:04 by lolefevr          #+#    #+#             */
/*   Updated: 2023/08/11 17:12:33 by lolefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hfiles/philo.h"

void	print_instr(t_philo *philo, int option)
{
	long long int	actual_time;

	actual_time = (get_time() - philo->data->start_time);
	if (is_philo_dead(philo))
		return ;
	pthread_mutex_lock(&philo->data->print);
	if (option == THINK)
		printf("%lld %d is thinking\n", actual_time, philo->id);
	else if (option == EAT)
		printf("%lld %d is eating\n", actual_time, philo->id);
	else if (option == SLEEP)
		printf("%lld %d is sleeping\n", actual_time, philo->id);
	else if (option == DEAD)
		printf("%lld %d died\n", actual_time, philo->id);
	pthread_mutex_unlock(&philo->data->print);
}

void	ft_print_fork(t_philo *philo)
{
	long long int	time;

	time = get_time() - philo->data->start_time;
	if (is_philo_dead(philo))
		return ;
	pthread_mutex_lock(&philo->data->print);
	printf("%lld %d has taken a fork\n", time, philo->id);
	printf("%lld %d has taken a fork\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->print);
}

int	ft_check_arg(int argc, char **argv)
{
	if (argc < 5 || argc > 6 || ft_atoi(argv[1]) <= 0)
	{
		printf("To start : number_of_philosophers | time_to_die | time_to_eat");
		printf(" | time_to_sleep |(number_of_times_each_philosopher_must_eat)");
		printf("\n");
		return (1);
	}
	else if (argv[1][0] == '1' && !argv[1][1])
	{
		printf("0 1 is thinking\n");
		printf("1 1 has taken a fork\n");
		printf("2 1 died\n");
		return (1);
	}
	return (0);
}

void	ft_chuimort(t_philo *philo)
{
	long long int	actual_time;

	pthread_mutex_lock(&philo->data->mdead);
	philo->data->dead += 1;
	pthread_mutex_unlock(&philo->data->mdead);
	philo->state = DEAD;
	usleep(5000);
	actual_time = (get_time() - philo->data->start_time);
	pthread_mutex_lock(&philo->data->print);
	printf("%lld %d died\n", actual_time, philo->id);
	pthread_mutex_unlock(&philo->data->print);
}
