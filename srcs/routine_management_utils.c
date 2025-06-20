/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_management_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prambaud <prambaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:06:38 by prambaud          #+#    #+#             */
/*   Updated: 2025/03/07 09:26:40 by prambaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	death_eat_check(t_data *data)
{
	int	death;
	int	eat_status;

	pthread_mutex_lock(&data->mutex_death);
	death = data->death_status;
	pthread_mutex_unlock(&data->mutex_death);
	pthread_mutex_lock(&data->mutex_eating_done);
	eat_status = data->eat_status;
	pthread_mutex_unlock(&data->mutex_eating_done);
	if (death == 0 && eat_status == 0)
		return (0);
	return (1);
}

int	enough_food(t_data *data)
{
	int		i;
	t_philo	*current;

	current = data->lst_philo;
	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_mutex_lock(&current->mutex_eat_count);
		if (current->eat_count < data->eat_max)
		{
			pthread_mutex_unlock(&current->mutex_eat_count);
			return (0);
		}
		pthread_mutex_unlock(&current->mutex_eat_count);
		i++;
		current = current->next;
	}
	pthread_mutex_lock(&data->mutex_eating_done);
	data->eat_status = 1;
	pthread_mutex_unlock(&data->mutex_eating_done);
	pthread_mutex_lock(&data->lst_philo->mutex_write);
	printf("Les philos ont assez manges\n");
	pthread_mutex_unlock(&data->lst_philo->mutex_write);
	return (1);
}

int	death_check(t_data *data)
{
	unsigned long long	last_eat_time;

	unsigned long long (time) = (unsigned long long)get_time_in_ms();
	t_philo (*current) = data->lst_philo;
	int (i) = 0;
	while ((i < data->num_of_philo))
	{
		pthread_mutex_lock(&current->mutex_eat_count);
		last_eat_time = current->last_eat_time;
		pthread_mutex_unlock(&current->mutex_eat_count);
		if (((time - last_eat_time) >= data->time_to_die))
		{
			pthread_mutex_lock(&data->mutex_death);
			data->death_status = 1;
			pthread_mutex_unlock(&data->mutex_death);
			pthread_mutex_lock(&current->mutex_write);
			printf("%lld %d died\n", time - data->start_time,
				current->philo_nbr);
			pthread_mutex_unlock(&current->mutex_write);
			return (1);
		}
		i++;
		current = current->next;
	}
	return (0);
}

int	try_take_fork1(t_data *data, t_philo *current)
{
	unsigned long long	time;

	time = (unsigned long long)get_time_in_ms() - data->start_time;
	pthread_mutex_lock(&current->mutex_fork);
	if (current->fork_status == 0)
	{
		current->fork_status = 1;
		pthread_mutex_unlock(&current->mutex_fork);
		pthread_mutex_lock(&current->mutex_write);
		printf("%lld %d has taken a fork\n", time, current->philo_nbr);
		pthread_mutex_unlock(&current->mutex_write);
		return (1);
	}
	pthread_mutex_unlock(&current->mutex_fork);
	return (0);
}

int	try_take_fork2(t_data *data, t_philo *current)
{
	unsigned long long	time;

	time = (unsigned long long)get_time_in_ms() - data->start_time;
	pthread_mutex_lock(&current->prev->mutex_fork);
	if (current->prev->fork_status == 0)
	{
		current->prev->fork_status = 1;
		pthread_mutex_unlock(&current->prev->mutex_fork);
		pthread_mutex_lock(&current->mutex_write);
		printf("%lld %d has taken a fork\n", time, current->philo_nbr);
		pthread_mutex_unlock(&current->mutex_write);
		return (1);
	}
	pthread_mutex_unlock(&current->prev->mutex_fork);
	return (0);
}
