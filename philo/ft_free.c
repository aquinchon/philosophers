/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:04:53 by aquincho          #+#    #+#             */
/*   Updated: 2022/10/13 15:04:55 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_free_mutex(t_table *table)
{
	int	i;

	pthread_mutex_destroy(&table->rules->m_rules);
	pthread_mutex_destroy(&table->msg->m_msg);
	pthread_mutex_destroy(&table->death->m_death);
	i = 0;
	while (i < table->rules->nbr_philo)
	{
		pthread_mutex_destroy(&table->fork[i].m_fork);
		i++;
	}
}

void	ft_free_table(t_table *table)
{
	if (!table)
		return ;
	if (table->mutex_errinit == 0)
		ft_free_mutex(table);
	if (table->msg)
		free (table->msg);
	if (table->death)
		free (table->death);
	if (table->rules)
		free (table->rules);
	if (table->fork)
		free (table->fork);
	if (table->philo)
		free (table->philo);
	free (table);
}
