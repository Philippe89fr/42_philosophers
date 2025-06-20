/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prambaud <prambaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:06:38 by prambaud          #+#    #+#             */
/*   Updated: 2025/03/07 09:19:03 by prambaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	sleeping_routine(t_data *data, t_philo *current)
{
	unsigned long long	current_time;
	unsigned long long	time;
	unsigned long long	start_timer;

	time = (unsigned long long)get_time_in_ms() - data->start_time;
	pthread_mutex_lock(&current->mutex_write);
	printf("%lld %d is sleeping\n", time, current->philo_nbr);
	pthread_mutex_unlock(&current->mutex_write);
	start_timer = (unsigned long long)get_time_in_ms();
	while (1)
	{
		usleep(10);
		if (death_eat_check(current->data))
			return (1);
		current_time = (unsigned long long)get_time_in_ms();
		if (current_time - start_timer >= data->time_to_sleep)
			break ;
	}
	current->sleep_status = 1;
	current->eat_status = 0;
	return (0);
}

int	thinking_routine(t_data *data, t_philo *current)
{
	unsigned long long	current_time;
	unsigned long long	time;
	unsigned long long	start_timer;

	time = (unsigned long long)get_time_in_ms() - data->start_time;
	pthread_mutex_lock(&current->mutex_write);
	printf("%lld %d is thinking\n", time, current->philo_nbr);
	pthread_mutex_unlock(&current->mutex_write);
	start_timer = (unsigned long long)get_time_in_ms();
	if (data->ac % 2 == 0)
	{
		usleep(1000);
	}
	if (death_eat_check(current->data))
		return (1);
	current->think_status = 1;
	current->sleep_status = 0;
	return (0);
}

int	eating_routine(t_data *data, t_philo *current)
{
	unsigned long long	current_time;
	unsigned long long	start_timer;
	unsigned long long	time;

	time = (unsigned long long)get_time_in_ms() - data->start_time;
	pthread_mutex_lock(&current->mutex_write);
	printf("%lld %d is eating\n", time, current->philo_nbr);
	pthread_mutex_unlock(&current->mutex_write);
	pthread_mutex_lock(&current->mutex_eat_count);
	current->eat_count++;
	current->last_eat_time = (unsigned long long)get_time_in_ms();
	pthread_mutex_unlock(&current->mutex_eat_count);
	start_timer = (unsigned long long)get_time_in_ms();
	while (1)
	{
		usleep(10);
		if (death_eat_check(current->data))
			return (1);
		current_time = (unsigned long long)get_time_in_ms();
		if (current_time - start_timer >= data->time_to_eat)
			break ;
	}
	status_after_eat(current);
	return (0);
}

int	eat_fork_mgnt(t_philo *current, int *fork1, int *fork2)
{
	if (*fork1 == 0)
		*fork1 = try_take_fork1(current->data, current);
	if (*fork1 == 1)
		*fork2 = try_take_fork2(current->data, current);
	if (*fork1 == 1 && *fork2 == 1)
	{
		if (eating_routine(current->data, current))
			return (1);
		*fork1 = 0;
		*fork2 = 0;
	}
	return (0);
}

void	*philo_routine(void *current_philo1)
{
	t_philo (*current) = (t_philo *)current_philo1;
	int (fork1) = 0;
	int (fork2) = 0;
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
