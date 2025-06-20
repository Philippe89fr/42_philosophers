/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_maker.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prambaud <prambaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:53:03 by prambaud          #+#    #+#             */
/*   Updated: 2025/02/12 12:13:38 by prambaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_lstadd_back_philo(t_philo **lst, t_philo *new)
{
	t_philo	*current;

	if (!lst || lst == &new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	current = ft_lstlast_philo(*lst);
	current->next = new;
}

/*on cree un nouveau noeud dans la liste chainee
ft_strdup utilise pour pouvoir liberer tab_line dans main lexing*/
t_philo	*lstnew_philo(t_data *data)
{
	t_philo	*new;

	new = (t_philo *)malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	new->last_eat_time = data->start_time;
	new->fork_status = 0;
	new->sleep_status = 0;
	new->think_status = 0;
	new->eat_status = 0;
	new->eat_count = 0;
	new->philo_nbr = 0;
	new->prev = NULL;
	new->next = NULL;
	new->data = data;
	pthread_mutex_init(&new->mutex_fork, NULL);
	pthread_mutex_init(&new->mutex_write, NULL);
	pthread_mutex_init(&new->mutex_eat_count, NULL);
	return (new);
}

t_philo	*lst_philo_maker(t_data *data)
{
	t_philo	*lst_philo;
	t_philo	*new_node;
	int		i;

	i = 0;
	lst_philo = NULL;
	while (i < data->num_of_philo)
	{
		new_node = lstnew_philo(data);
		if (!new_node)
		{
			ft_lstclear_philo(&lst_philo, data);
			return (malloc_fail(), NULL);
		}
		ft_lstadd_back_philo(&lst_philo, new_node);
		i++;
	}
	lst_philo_put_back(lst_philo);
	return (lst_philo);
}

/*ici,
	nous mettons en place un lien qui dirige
	vers le noeud precedent chaque noeud.
Le premier noeud previous est NULL*/
void	lst_philo_put_back(t_philo *lst_philo)
{
	t_philo	*current;
	t_philo	*previous;

	previous = lst_philo;
	previous->prev = NULL;
	current = previous->next;
	while (current)
	{
		current->prev = previous;
		previous = current;
		current = current->next;
	}
	previous->next = lst_philo;
	lst_philo->prev = previous;
}
