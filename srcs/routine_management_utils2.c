/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_management_utils2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prambaud <prambaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:06:38 by prambaud          #+#    #+#             */
/*   Updated: 2025/03/06 09:53:34 by prambaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	status_after_eat(t_philo *current)
{
	current->eat_status = 1;
	current->think_status = 0;
	pthread_mutex_lock(&current->mutex_fork);
	current->fork_status = 0;
	pthread_mutex_unlock(&current->mutex_fork);
	pthread_mutex_lock(&current->prev->mutex_fork);
	current->prev->fork_status = 0;
	pthread_mutex_unlock(&current->prev->mutex_fork);
}

void	*monitor_routine(void *data1)
{
	t_data	*data;

	data = (t_data *)data1;
	while (1)
	{
		if (death_check(data))
			return (NULL);
		if (enough_food(data))
			return (NULL);
	}
	return (0);
}

void	*one_philo_routine(void *data1)
{
	t_data				*data;
	unsigned long long	time;
	t_philo				*current;

	data = (t_data *)data1;
	current = data->lst_philo;
	time = (unsigned long long)get_time_in_ms() - data->start_time;
	pthread_mutex_lock(&current->mutex_write);
	printf("%lld %d has taken a fork\n", time,
		current->philo_nbr);
	pthread_mutex_unlock(&current->mutex_write);
	usleep(data->time_to_die * 1000);
	pthread_mutex_lock(&current->mutex_write);
	printf("%lld %d died\n", data->time_to_die,
		current->philo_nbr);
	pthread_mutex_unlock(&current->mutex_write);
	return (0);
}
