/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prambaud <prambaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:26:28 by prambaud          #+#    #+#             */
/*   Updated: 2025/03/10 09:25:04 by prambaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	close_inherited_fds(void)
{
	int	fd;

	fd = 3;
	while (fd < 1024)
	{
		close(fd);
		fd++;
	}
}

void	thread_creation_join(t_data *data)
{
	int	i;

	i = 0;
	pthread_create(&data->thread, NULL, monitor_routine, data);
	while (i < data->num_of_philo)
	{
		pthread_create(&data->current_philo->thread, NULL, philo_routine,
			data->current_philo);
		i++;
		data->current_philo = data->current_philo->next;
	}
	data->current_philo = data->lst_philo;
	i = 0;
	pthread_join(data->thread, NULL);
	while (i < data->num_of_philo)
	{
		pthread_join(data->current_philo->thread, NULL);
		data->current_philo = data->current_philo->next;
		i++;
	}
}

void	one_philo_management(t_data *data)
{
	pthread_create(&data->thread, NULL, one_philo_routine, data);
	pthread_join(data->thread, NULL);
	pthread_mutex_destroy(&data->lst_philo->mutex_fork);
	pthread_mutex_destroy(&data->lst_philo->mutex_write);
	pthread_mutex_destroy(&data->lst_philo->mutex_eat_count);
	pthread_mutex_destroy(&data->mutex_death);
	pthread_mutex_destroy(&data->mutex_eating_done);
	ft_lstclear_philo(&data->lst_philo, data);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		i;

	i = 0;
	close_inherited_fds();
	if ((ac != 6 && ac != 5) || !no_missing_input(av))
	{
		printf("Wrong_input\n");
		return (0);
	}
	init_data_struct(&data, ac, av);
	if (data.num_of_philo == 1)
		one_philo_management(&data);
	else if (data.num_of_philo < 100)
	{
		thread_creation_join(&data);
		liberator_god(&data);
	}
	else
	{
		thread_creation_join_100(&data);
		liberator_god(&data);
	}
	return (0);
}
