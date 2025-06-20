/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_management_100.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prambaud <prambaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:06:38 by prambaud          #+#    #+#             */
/*   Updated: 2025/03/10 09:25:14 by prambaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	thread_ready_increament(t_data *data)
{
	pthread_mutex_lock(&data->mutex_thread_ready);
	data->thread_ready++;
	pthread_mutex_unlock(&data->mutex_thread_ready);
}

int	thread_ready(t_data *data)
{
	int	thread_read_check;

	pthread_mutex_lock(&data->mutex_thread_ready);
	thread_read_check = data->thread_ready;
	pthread_mutex_unlock(&data->mutex_thread_ready);
	if (thread_read_check != data->num_of_philo + 1)
		return (0);
	return (1);
}

void	*philo_routine_100(void *current_philo1)
{
	t_philo (*current) = (t_philo *)current_philo1;
	int (fork1) = 0;
	int (fork2) = 0;
	thread_ready_increament(current->data);
	while (!thread_ready(current->data))
		current->data->start_time = (unsigned long long)get_time_in_ms();
	while (!death_eat_check(current->data))
	{
		if (current->sleep_status == 1 && !death_eat_check(current->data))
		{
			if (thinking_routine(current->data, current))
				return (NULL);
		}
		if (current->eat_status == 1 && !death_eat_check(current->data))
		{
			if (sleeping_routine(current->data, current))
				return (NULL);
		}
		if (current->think_status == 1 && !death_eat_check(current->data))
		{
			if (eat_fork_mgnt(current, &fork1, &fork2))
				return (NULL);
		}
	}
	return (NULL);
}

void	*monitor_routine_100(void *data1)
{
	t_data	*data;
	int		i;

	data = (t_data *)data1;
	pthread_mutex_lock(&data->mutex_thread_ready);
	data->thread_ready++;
	pthread_mutex_unlock(&data->mutex_thread_ready);
	while (!thread_ready(data))
		i = 0;
	while (1)
	{
		if (death_check(data))
			return (NULL);
		if (enough_food(data))
			return (NULL);
	}
	return (0);
}

void	thread_creation_join_100(t_data *data)
{
	int	i;

	i = 0;
	pthread_create(&data->thread, NULL, monitor_routine_100, data);
	while (i < data->num_of_philo)
	{
		pthread_create(&data->current_philo->thread, NULL, philo_routine_100,
			data->current_philo);
		i++;
		data->current_philo = data->current_philo->next;
	}
	data->current_philo = data->lst_philo;
	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_join(data->current_philo->thread, NULL);
		data->current_philo = data->current_philo->next;
		i++;
	}
	pthread_join(data->thread, NULL);
}
