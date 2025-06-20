/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prambaud <prambaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:19:20 by prambaud          #+#    #+#             */
/*   Updated: 2025/03/07 10:18:06 by prambaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	j;
	int	nb;

	i = 0;
	j = 0;
	nb = 0;
	while (nptr[i] == ' ' || (nptr[i] <= 13 && nptr[i] >= 9))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			j++;
		i++;
	}
	while (nptr[i] <= '9' && nptr[i] >= '0')
	{
		nb = nb * 10 - '0' + nptr[i];
		i++;
	}
	if (j % 2 != 0)
		nb = nb * (-1);
	return (nb);
}

void	init_data_struct2(t_data *data, char **av)
{
	data->death_status = 0;
	data->eat_status = 0;
	data->thread_ready = 0;
	data->num_of_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	pthread_mutex_init(&data->mutex_death, NULL);
	pthread_mutex_init(&data->mutex_eating_done, NULL);
	pthread_mutex_init(&data->mutex_thread_ready, NULL);
	if (data->ac == 6)
		data->eat_max = ft_atoi(av[5]);
	else
		data->eat_max = 2000000;
}

void	init_data_struct(t_data *data, int ac, char **av)
{
	int	i;

	i = 0;
	data->start_time = (unsigned long long)get_time_in_ms();
	data->current_philo_num = 1;
	data->ac = ac;
	data->av = av;
	init_data_struct2(data, av);
	data->lst_philo = NULL;
	data->lst_philo = lst_philo_maker(data);
	data->current_philo = NULL;
	data->current_philo = data->lst_philo;
	while (i < data->num_of_philo)
	{
		data->current_philo->philo_nbr = i + 1;
		if (data->current_philo->philo_nbr % 2 == 0)
			data->current_philo->sleep_status = 1;
		else
			data->current_philo->eat_status = 1;
		i++;
		data->current_philo = data->current_philo->next;
	}
}
