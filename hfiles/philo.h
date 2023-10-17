/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolefevr <lolefevr@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 13:03:26 by lolefevr          #+#    #+#             */
/*   Updated: 2023/08/11 17:10:14 by lolefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <time.h>

# define EAT 0
# define SLEEP 1
# define THINK 2
# define FORK 3
# define DEAD 4

typedef struct s_data
{
	long int						start_time;
	int								nb_philo;
	long int						time_to_die;
	long int						time_to_eat;
	long int						time_to_sleep;
	int								nb_meal_max;
	int								dead;
	pthread_mutex_t					mdead;
	pthread_mutex_t					print;
	pthread_mutex_t					*fork;
}									t_data;

typedef struct s_philo
{
	int								id;
	int								state;
	int								nb_meal;
	unsigned long int				last_meal;
	pthread_t						*thread;
	t_data							*data;
}									t_philo;

long long int	get_time(void);
int				ft_atoi(const char *str);
t_data			*ft_data_init(char **argv, t_data *data);
t_philo			**init_struct(t_data *data);
pthread_mutex_t	*ft_init_mutex(t_data *data);
void			*routine(t_philo *philo);
void			ft_created_thread(t_philo **philo);
void			free_all(t_philo **philo, t_data *data);
int				is_philo_dead(t_philo *philo);
void			ft_philo_think(t_philo *philo);
void			print_instr(t_philo *philo, int option);
void			ft_miam_miam(t_philo *philo, int odd);
void			ft_miam_suite(t_philo *philo, int odd);
void			ft_print_fork(t_philo *philo);
void			ft_philo_sleep(t_philo *philo);
void			ft_destroy_mut(t_data *data, int nbr);
int				ft_check_arg(int argc, char **argv);
void			ft_chuimort(t_philo *philo);

#endif
