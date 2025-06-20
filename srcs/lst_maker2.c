/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_maker2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prambaud <prambaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:53:03 by prambaud          #+#    #+#             */
/*   Updated: 2025/02/12 12:13:28 by prambaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// void	print_lst_philo(t_data *data)
// {
// 	t_philo	*current;
// 	int		i;

// 	i = 0;
// 	current = data->lst_philo;
// 	while (i < data->num_of_philo)
// 	{
// 		printf("N%d: Le philo num %d, thread est %ld, left_fork_status = %d,
// 			sleep status = %d, eat status = %d, think status = %d\n", i + 1,
// 			current->philo_nbr, current->thread, current->fork_status,
// 			current->sleep_status, current->eat_status, current->think_status);
// 		current = current->next;
// 		i++;
// 	}
// }

// void	print_one_philo(t_philo *current)
// {
// 	printf("Thread %lu, Philo N%d, eat_status = %d, sleep_status = %d,
// 		think_status = %d\n", current->thread, current->philo_nbr,
// 		current->eat_status, current->sleep_status, current->think_status);
// }

t_philo	*ft_lstlast_philo(t_philo *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	ft_lstsize_philo(t_philo *lst)
{
	int		count;
	t_philo	*current;

	count = 0;
	current = lst;
	while (current)
	{
		current = current->next;
		count++;
	}
	return (count);
}

void	print_current_time(unsigned long long start_time)
{
	unsigned long long	current_time;

	current_time = (unsigned long long)get_time_in_ms() - start_time;
	printf("Juste le time = %lld \n", current_time);
}

void	print_time(unsigned long long time, unsigned long long start_time)
{
	printf("Juste le time = %lld \n", start_time - time);
}
