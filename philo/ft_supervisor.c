/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_supervisor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 10:11:48 by aquincho          #+#    #+#             */
/*   Updated: 2022/10/18 10:11:50 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	ft_end_event(t_table *table, int i, int type)
{
	if (type == TYPE_DIE)
		table->global->is_death = true;
	if (type == TYPE_ENOUGH)
		table->global->all_ate_enough = true;
	table->global->is_end = true;
	ft_display_msg(&table->philo[i], ft_get_timestamp(), type);
	return (true);
}

void	*ft_supervisor(void *data)
{
	t_table	*table;
	int		i;

	table = (t_table *)data;
	while (!table->global->is_end)
	{
		i = 0;
		while (i < table->rules->nbr_philo)
		{
			if (&table->philo[i])
			{
				table->philo[i].is_dead = ft_isdead(&table->philo[i]);
				if (table->philo[i].is_dead || table->global->is_death)
					table->global->is_end = ft_end_event(table, i, TYPE_DIE);
			}
			if ((table->global->nbr_ate_enough == table->rules->nbr_philo
					|| table->global->all_ate_enough)
				&& !table->global->is_death)
				table->global->is_end = ft_end_event(table, i, TYPE_ENOUGH);
			if (table->global->is_end)
				return (NULL);
			i++;
		}
	}
	return (NULL);
}
