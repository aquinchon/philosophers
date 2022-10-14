/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 09:42:52 by aquincho          #+#    #+#             */
/*   Updated: 2022/09/23 09:42:56 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_err_exit(char *msg)
{
	write(2, "\033[33;31mError\n", 14);
	write(2, msg, ft_strlen(msg));
	write(2, "\033[33;37m\n", 9);
	exit (1);
}

int	ft_err_free_exit(char *msg, t_table *table)
{
	int	msg_len;

	if (table)
		ft_free_table(table);
	msg_len = 0;
	while (msg[msg_len])
		msg_len++;
	write(2, "\033[33;31mError\n", 14);
	write(2, msg, ft_strlen(msg));
	write(2, "\033[33;37m\n", 9);
	exit (1);
}
