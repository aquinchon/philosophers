/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 10:11:32 by aquincho          #+#    #+#             */
/*   Updated: 2022/10/18 10:11:35 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->rfork->m_fork);
	philo->rfork->is_used = false;
	pthread_mutex_unlock(&philo->lfork->m_fork);
	philo->lfork->is_used = false;
}

bool	ft_take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->lfork->m_fork);
	philo->lfork->is_used = true;
	if (!philo->is_dead && !philo->ate_enough && !philo->global->is_end)
		ft_display_msg(philo, ft_get_timestamp(), TYPE_FORK);
	else
	{
		pthread_mutex_unlock(&philo->lfork->m_fork);
		philo->lfork->is_used = false;
		return (true);
	}
	pthread_mutex_lock(&philo->rfork->m_fork);
	philo->rfork->is_used = true;
	if (!philo->is_dead && !philo->ate_enough && !philo->global->is_end)
		ft_display_msg(philo, ft_get_timestamp(), TYPE_FORK);
	else
	{
		ft_release_forks(philo);
		return (true);
	}
	philo->is_dead = ft_isdead(philo);
	return (philo->is_dead);
}

static void	ft_eat_count(t_philo *philo)
{
	if (philo->rules->nbr_eat > 0)
	{
		philo->eat_count++;
		if (!philo->ate_enough && philo->eat_count >= philo->rules->nbr_eat)
		{
			philo->ate_enough = true;
			pthread_mutex_lock(&philo->global->m_nbr_ate_enough);
			philo->global->nbr_ate_enough++;
			pthread_mutex_unlock(&philo->global->m_nbr_ate_enough);
		}
	}
}

bool	ft_eat(t_philo *philo)
{
	if (philo->is_dead || philo->ate_enough || philo->global->is_end)
	{
		ft_release_forks(philo);
		return (true);
	}
	philo->time_left = ft_time_left(philo);
	ft_display_msg(philo, ft_get_timestamp(), TYPE_EAT);
	if (philo->time_left >= philo->rules->time_eat)
	{
		usleep(philo->rules->time_eat * 1000);
		ft_eat_count(philo);
		philo->time_last_meal = ft_get_timestamp();
		philo->is_dead = false;
	}
	else
	{
		usleep (philo->time_left * 1000);
		philo->is_dead = true;
	}
	ft_release_forks(philo);
	return (philo->is_dead);
}

bool	ft_sleep(t_philo *philo)
{
	philo->time_left = ft_time_left(philo);
	if (!philo->is_dead && !philo->ate_enough && !philo->global->is_end)
		ft_display_msg(philo, ft_get_timestamp(), TYPE_SLEEP);
	if (philo->time_left >= philo->rules->time_sleep)
	{
		usleep(philo->rules->time_sleep * 1000);
		philo->is_dead = false;
	}
	else
	{
		usleep(philo->time_left * 1000);
		philo->is_dead = true;
	}
	if (!philo->is_dead && !philo->ate_enough && !philo->global->is_end)
		ft_display_msg(philo, ft_get_timestamp(), TYPE_THINK);
	return (philo->is_dead);
}
