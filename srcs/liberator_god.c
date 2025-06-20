/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liberator_god.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prambaud <prambaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:02:02 by prambaud          #+#    #+#             */
/*   Updated: 2025/03/07 10:18:12 by prambaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_lstclear_philo(t_philo **lst, t_data *data)
{
	t_philo	*current;
	t_philo	*temp;
	int		i;

	i = 0;
	if (!lst)
		return ;
	current = *lst;
	while (i < data->num_of_philo)
	{
		temp = current;
		current = current->next;
		free(temp);
		i++;
	}
	*lst = NULL;
}

void	liberator_god(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_mutex_destroy(&data->lst_philo->mutex_fork);
		pthread_mutex_destroy(&data->lst_philo->mutex_write);
		pthread_mutex_destroy(&data->lst_philo->mutex_eat_count);
		data->lst_philo = data->lst_philo->next;
		i++;
	}
	pthread_mutex_destroy(&data->mutex_death);
	pthread_mutex_destroy(&data->mutex_eating_done);
	pthread_mutex_destroy(&data->mutex_thread_ready);
	if (data->lst_philo)
		ft_lstclear_philo(&data->lst_philo, data);
}
