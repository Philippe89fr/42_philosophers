/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prambaud <prambaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:16:37 by prambaud          #+#    #+#             */
/*   Updated: 2025/03/07 10:23:11 by prambaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	pthread_mutex_t		mutex_fork;
	pthread_mutex_t		mutex_eat_count;
	pthread_mutex_t		mutex_write;
	unsigned long long	last_eat_time;
	int					fork_status;
	int					sleep_status;
	int					eat_status;
	int					think_status;
	int					eat_count;
	unsigned int		philo_nbr;
	pthread_t			thread;
	struct s_philo		*prev;
	struct s_philo		*next;
	t_data				*data;
}						t_philo;

typedef struct s_data
{
	pthread_t			thread;
	int					ac;
	char				**av;
	int					current_philo_num;
	unsigned long long	start_time;
	int					num_of_philo;
	unsigned long long	time_to_die;
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;
	int					eat_max;
	unsigned long long	timestamp_in_ms;
	int					death_status;
	int					eat_status;
	int					thread_ready;
	t_philo				*lst_philo;
	t_philo				*current_philo;
	pthread_mutex_t		mutex_death;
	pthread_mutex_t		mutex_eating_done;
	pthread_mutex_t		mutex_thread_ready;
}						t_data;

int						thread_ready(t_data *data);
int						eat_fork_mgnt(t_philo *current, int *fork1, int *fork2);
int						sleeping_routine(t_data *data, t_philo *current);
int						thinking_routine(t_data *data, t_philo *current);
int						eating_routine(t_data *data, t_philo *current);
void					thread_creation_join_100(t_data *data);
void					*philo_routine_100(void *current_philo1);
void					*monitor_routine_100(void *data1);
void					thread_ready_increament(t_data *data);
void					liberator_god(t_data *data);
bool					no_missing_input(char **av);
int						ft_atoi(const char *nptr);
void					status_after_eat(t_philo *current);
void					init_data_struct(t_data *data, int ac, char **av);
t_philo					*ft_lstlast_philo(t_philo *lst);
int						ft_lstsize_philo(t_philo *lst);
void					print_current_time(unsigned long long start_time);
void					print_time(unsigned long long time,
							unsigned long long start_time);
int						death_eat_check(t_data *data);
void					ft_lstclear_philo(t_philo **lst, t_data *data);
t_philo					*lst_philo_maker(t_data *data);
void					malloc_fail(void);
t_philo					*ft_lstlast_philo(t_philo *lst);
void					lst_philo_put_back(t_philo *lst_philo);
void					print_lst_philo(t_data *data);
time_t					get_time_in_ms(void);
void					*philo_routine(void *current_philo1);
void					*monitor_routine(void *data1);
void					print_one_philo(t_philo *current);
void					try_take_fork(t_data *data, t_philo *current);
int						try_take_fork1(t_data *data, t_philo *current);
int						try_take_fork2(t_data *data, t_philo *current);
int						death_check(t_data *data);
void					print_current_time(unsigned long long start_time);
void					print_time(unsigned long long time,
							unsigned long long start_time);
int						enough_food(t_data *data);
void					*one_philo_routine(void *data1);

#endif
