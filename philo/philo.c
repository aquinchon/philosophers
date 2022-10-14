/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 08:57:37 by aquincho          #+#    #+#             */
/*   Updated: 2022/09/23 08:57:40 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_supervisor(void *data)
{
	t_table	*table;
	int		i;
	int		j; /*FOR TEST*/

	table = (t_table *)data;
	pthread_mutex_lock(&table->rules->m_rules);
	pthread_mutex_lock(&table->death->m_death);
	j = 0;  /*FOR TEST*/
	while (j < 10 &&!table->death->is_death && !table->all_ate_enough)
	{
		i = 0;
		while (i < table->rules->nbr_philo)
		{
			if (table->philo[i].is_dead)
			{
				pthread_mutex_lock(&table->msg->m_msg);
				table->death->is_death = true;
				write (1, "Mort!", 5);
				pthread_mutex_unlock(&table->death->m_death);
				pthread_mutex_unlock(&table->rules->m_rules);
				pthread_mutex_unlock(&table->msg->m_msg);
				return (NULL);
			}
			if (table->philo[i].ate_enough)
				table->all_ate_enough++;
			if (table->all_ate_enough == table->rules->nbr_philo)
			{
				write (1, "Mort!", 5);
				pthread_mutex_unlock(&table->death->m_death);
				pthread_mutex_unlock(&table->rules->m_rules);
				return (NULL);
			}
			i++;
		}
		usleep(100000);
		j++; /*FOR TEST*/
	}
	pthread_mutex_unlock(&table->death->m_death);
	pthread_mutex_unlock(&table->rules->m_rules);
	return (NULL);
}

bool	ft_isdead(t_philo *philo)
{
	philo->time_left = ft_time_left(philo);
	if (philo->time_left < philo->rules->time_die)
		return (false);
	else
	{
		philo->is_dead = true;
		return (true);
	}
}

bool	ft_take_forks(t_philo *philo, bool death)
{
	int		try;
	bool	taken;

	taken = false;
	while (!taken)
	{
		if (ft_isdead(philo))
			return (true);
		pthread_mutex_lock(&philo->lfork->m_fork);
		philo->lfork->is_used = true;
		try = 0;
		while (!taken && try < 3)
		{
			if (!philo->rfork->is_used)
			{
			pthread_mutex_lock(&philo->rfork->m_fork);
			philo->rfork->is_used = true;
			ft_display_msg(philo, TYPE_FORK);
			ft_display_msg(philo, TYPE_FORK);
			taken = true;
			}
			else
				usleep (5);
			try++;
		}
		pthread_mutex_unlock(&philo->lfork->m_fork);
		philo->lfork->is_used = false;
		usleep(10);
	}
	return (death);
}

bool	ft_eat(t_philo *philo, bool death)
{
	philo->time_last_meal = ft_get_timestamp();
	ft_display_msg(philo, TYPE_EAT);
	philo->time_left = ft_time_left(philo);
	if (philo->time_left > philo->rules->time_die)

	usleep(philo->rules->time_eat * 1000);

	pthread_mutex_unlock(&philo->lfork->m_fork);
	pthread_mutex_unlock(&philo->rfork->m_fork);
	ft_display_msg(philo, TYPE_SLEEP);
	return (death);
}

static void	*ft_philo_life(void *data)
{
	t_philo	*philo;
	bool	death;

	death = false;
	philo = (t_philo *)data;
	philo->time_last_meal = ft_get_timestamp();
	while (!death)
	{
		death = ft_take_forks(philo, death);
		if (!death)
			death = ft_eat(philo, death);
		//death = ft_release_forks(philo, death);
		//death = ft_sleep(philo, death);
		//death = think(philo);
	}
	return (NULL);
}

int	ft_philo_create(t_table *table)
{
	int		i;
	int		result;
	void	*philo;

	result = 0;
	
	table->start_time->time = ft_get_timestamp();
	i = 0;
	while (i < table->rules->nbr_philo)
	{
		table->philo[i].start_time->time = table->start_time->time;
		philo = (void *)(&table->philo[i]);
		result = pthread_create(&table->philo[i].thr_id,
				NULL, &ft_philo_life, philo);
		if (result)
			result = ft_err_free_exit("Cannot create philosopher...", table);
		pthread_detach(table->philo[i].thr_id);
		//usleep (5);
		i++;
	}
	return (result);
}

int	main(int argc, char **argv)
{
	int			result;
	t_table		*table;
	//int			i;

	result = 0;
	if (argc < 5 || argc > 6)
		result = ft_err_exit("Wrong number of arguments.");
	table = ft_init(argc, argv);
	if (!table)
		return (result);
	result = pthread_create(&table->thr_superv, NULL, &ft_supervisor, table);
	if (result)
		result = ft_err_free_exit("Cannot create supervisor.", table);
	result = ft_philo_create(table);
	if (result)
		result = ft_err_free_exit("Cannot create philosopher.", table);
	pthread_join(table->thr_superv, NULL);
	/*printf("table: %d %d %d %d %d\n", table->rules->nbr_philo,
		table->rules->time_die, table->rules->time_eat,
		table->rules->time_sleep, table->rules->nbr_eat);
	i = 0;
	while (i < table->rules->nbr_philo)
	{
		printf("philo: %d %d %d %d\n", table->philo[i].id,
			table->philo[i].rules->time_die, table->philo[i].lfork->id,
			table->philo[i].rfork->id);
		i++;
	}*/
	ft_free_table(table);
	return (result);
}
