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
	if (!(nptr[i] == '+' || (nptr[i] >= '0' && nptr[i] <= '9')))
		resultat = ft_err_free_exit("Argument incorrect", table);
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

/*
static void	ft_itoa(unsigned long long lln, char *resultat, int i)
{
	if (lln <= 9)
		resultat[i] = lln + '0';
	else
	{
		ft_itoa(lln / 10, resultat, i - 1);
		resultat[i] = lln % 10 + '0';
	}
}

void	ft_putnbr(unsigned long long lln, int type)
{
	char				*resultat;
	int					len_nbr;
	unsigned long long	tmp;

	tmp = lln;
	len_nbr = 1;
	while (tmp / 10 > 0)
	{
		len_nbr++;
		tmp /= 10;
	}
	resultat = malloc (sizeof(char) * (len_nbr + 2));
	ft_itoa(lln, resultat, len_nbr - 1);
	if (type == 0)
		resultat[len_nbr] = '\t';
	else
		resultat[len_nbr] = ' ';
	resultat[len_nbr + 1] = '\0';
	write (1, resultat, ft_strlen(resultat));
	free (resultat);
}
*/