/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 08:57:52 by aquincho          #+#    #+#             */
/*   Updated: 2022/09/23 08:59:13 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
//# include <stdio.h>

typedef enum e_msg_type
{
	TYPE_FORK,
	TYPE_EAT,
	TYPE_SLEEP,
	TYPE_THINK,
	TYPE_DIE,
	TYPE_ENOUGH
}	t_msg_type;

typedef struct s_rules
{
	int				nbr_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nbr_eat;
	pthread_mutex_t	m_rules;
}	t_rules;

typedef struct s_fork
{
	int				id;
	bool			is_used;
	pthread_mutex_t	m_fork;
}	t_fork;

typedef struct s_msg
{
	char			*msg;
	pthread_mutex_t	m_msg;
}	t_msg;

typedef struct s_death
{
	bool			is_death;
	pthread_mutex_t	m_death;
}	t_death;

typedef struct s_time
{
	unsigned long long	time;
	pthread_mutex_t		m_time;
}	t_time;

typedef struct s_philo
{
	int					id;
	pthread_t			thr_id;
	bool				is_dead;
	bool				ate_enough;
	int					eat_count;
	unsigned long long	time_last_meal;
	int					time_left;
	t_time				*start_time;
	t_fork				*lfork;
	t_fork				*rfork;
	t_rules				*rules;
	t_death				*death;
	t_msg				*msg;
}	t_philo;

typedef struct s_table
{
	t_rules		*rules;
	t_philo		*philo;
	t_fork		*fork;
	t_msg		*msg;
	t_death		*death;
	int			all_ate_enough;
	t_time		*start_time;
	pthread_t	thr_superv;
	int			mutex_errinit;
}	t_table;

/* Rules initialization ft_init.c */
t_table				*ft_init(int argc, char **argv);
/* Messages display */
void				ft_display_msg(t_philo *philo, int type);
/* Utilitaries ft_utils.c */
int					ft_atoi_check(const char *nptr, t_table *table);
void				ft_putnbr(unsigned long long lln);
/* Time management ft_time.c */
unsigned long long	ft_get_timestamp(void);
int					ft_time_left(t_philo *philo);
/* Errors management ft_errors.c */
int					ft_strlen(const char *s);
int					ft_err_exit(char *msg);
int					ft_err_free_exit(char *msg, t_table *table);
/* Memory free ft_free.c */
void				ft_free_table(t_table *table);

#endif
