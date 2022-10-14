/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 09:45:52 by aquincho          #+#    #+#             */
/*   Updated: 2022/09/23 09:45:57 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (*(s++))
		len++;
	return (len);
}

int	ft_atoi_check(const char *nptr, t_table *table)
{
	int	i;
	int	resultat;

	resultat = 0;
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' && nptr[i + 1]
		&& nptr[i + 1] >= '0' && nptr[i + 1] <= '9')
		i++;
	while (nptr[i])
	{
		if (nptr[i] >= '0' && nptr[i] <= '9')
		{
			resultat = resultat * 10 + (nptr[i] - '0');
			i++;
		}
		else
			resultat = ft_err_free_exit("Argument incorrect", table);
	}
	return (resultat);
}

void	ft_putnbr(unsigned long long lln)
{
	char	c;

	if (lln <= 9)
	{
		c = lln + '0';
		write (1, &c, 1);
	}
	else
	{
		ft_putnbr(lln / 10);
		c = lln % 10 + '0';
		write (1, &c, 1);
	}
}
