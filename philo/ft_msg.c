/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_msg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 12:29:48 by aquincho          #+#    #+#             */
/*   Updated: 2022/10/14 12:29:50 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char	*ft_msg_type(int type)
{
	if (type == 0)
		return ("has taken a fork");
	else if (type == 1)
		return ("is eating");
	else if (type == 2)
		return ("is sleeping");
	else if (type == 3)
		return ("is thinking");
	else if (type == 4)
		return ("died");
	else if (type == 5)
		return ("Philosophers have had enough food!");
	return ("error\n");
}

void	ft_display_msg(t_philo *philo, int type)
{
	pthread_mutex_lock (&philo->msg->m_msg);
	if (type >= 0 && type <= 4)
	{
		ft_putnbr(ft_get_timestamp() - philo->start_time->time);
		write (1, "\t", 1);
		ft_putnbr(philo->id + 1);
		write (1, " ", 1);
	}
	philo->msg->msg = ft_msg_type(type);
	write (1, philo->msg->msg, ft_strlen(philo->msg->msg));
	write (1, "\n", 1);
	pthread_mutex_unlock (&philo->msg->m_msg);
}