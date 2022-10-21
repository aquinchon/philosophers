/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_life.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 10:11:19 by aquincho          #+#    #+#             */
/*   Updated: 2022/10/18 10:11:22 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*ft_philo_life(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	philo->time_last_meal = philo->global->start_time;
	philo->is_dead = ft_isdead(philo);
	while (!philo->is_dead && !philo->ate_enough && !philo->global->is_end)
	{
		if (!philo->is_dead && !philo->ate_enough && !philo->global->is_end)
			philo->is_dead = ft_take_forks(philo);
		if (!philo->is_dead && !philo->ate_enough && !philo->global->is_end)
			philo->is_dead = ft_eat(philo);
		if (!philo->is_dead && !philo->ate_enough && !philo->global->is_end)
			philo->is_dead = ft_sleep(philo);
		philo->is_dead = ft_isdead(philo);
	}
	return (NULL);
}

static int	ft_philo_create_parity(t_table *table, int i)
{
	int		result;
	void	*philo;

	result = 0;
	while (i < table->rules->nbr_philo)
	{
		philo = (void *)(&table->philo[i]);
		result = pthread_create(&table->philo[i].thr_id,
				NULL, &ft_philo_life, philo);
		if (result)
			result = ft_err_free_exit("Cannot create philosopher...", table);
		pthread_detach(table->philo[i].thr_id);
		i += 2;
	}
	return (result);
}

int	ft_philo_create(t_table *table)
{
	int		result;

	result = 0;
	table->global->start_time = ft_get_timestamp();
	if (!result)
	{
		result = ft_philo_create_parity(table, 0);
		usleep(5000);
		result = ft_philo_create_parity(table, 1);
	}
	return (result);
}
