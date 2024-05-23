/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytsyrend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:59:13 by ytsyrend          #+#    #+#             */
/*   Updated: 2024/03/06 16:17:55 by ytsyrend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdbool.h>
# include <errno.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

# ifndef DEBUG_MODE
#  define DEBUG_MODE 0
# endif

# ifndef PHILO_MAX
#  define PHILO_MAX 200 
# endif

# define RST	"\033[0m"
# define RED	"\033[1;31m"
# define G		"\033[1;32m"
# define Y		"\033[1;33m"
# define B		"\033[1;34m"
# define M		"\033[1;35m"
# define C		"\033[1;36m"
# define W		"\033[1;37m"

/****************************************
 *   ___ _ __  _   _ _ __ ___  ___     *
 *  / _ \ '_ \| | | | '_ ` _ \/ __|    *
 * |  __/ | | | |_| | | | | | \__ \    *
 *  \___|_| |_|\__,_|_| |_| |_|___/    *
 ****************************************/

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,	
}			t_opcode;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}		t_philo_status;

typedef enum e_time_code
{
	SECONDS,
	MILLISECOND,
	MICROSECOND,
}			t_time_code;

typedef enum e_errors
{
	CHECK_ARG_NUMBER,
	INVALID_MAX_PHILO,
	INVALID_TIMESTAMP,
	INVALID_INT,
	NEGATIVE_VALUE,
	NOT_DIGIT,
	INVALID_MALLOC,
	WRONG_MUTEX_OP,
	WRONG_THREAD_OP,
	FAILED_GET_TIME,
	WRONG_TIME_OP,
}			t_errors;

/****************************************
 *     | |                 | |         	*
 *  ___| |_ _ __ _   _  ___| |_ ___    	*
 * / __| __| '__| | | |/ __| __/ __|   	*
 * \__ \ |_| |  | |_| | (__| |_\__ \   	*
 * |___/\__|_|   \__,_|\___|\__|___/   	*
 ****************************************/

typedef pthread_mutex_t	t_mtx;
typedef struct s_table	t_table;

typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}				t_fork;

typedef struct s_bool
{
	bool	value;
	int		error;
}				t_bool;

typedef struct s_philo
{
	int			id;
	long		meals_counter;
	bool		full;
	long		last_meal_time;
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;
	t_table		*table;
	t_mtx		philo_mutex;
}				t_philo;

struct s_table
{
	long		philo_nbr;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		nbr_limit_meals;
	long		start_simulation;
	bool		end_simulation;
	t_fork		*forks;
	bool		all_threads_ready;
	long		threads_running_nbr;
	pthread_t	monitor;
	t_mtx		table_mutex;
	t_mtx		write_mutex;
	t_philo		*philos;
};

/********************************************************
*                 | |      | |                          *
*  _ __  _ __ ___ | |_ ___ | |_ _   _ _ __   ___  ___   *
* | '_ \| '__/ _ \| __/ _ \| __| | | | '_ \ / _ \/ __|  *
* | |_) | | | (_) | || (_) | |_| |_| | |_) |  __/\__ \  *
* | .__/|_|  \___/ \__\___/ \__|\__, | .__/ \___||___/  *
* | |                            __/ | |                *
* |_|                           |___/|_|                *
********************************************************/

t_bool	simulation_finished(t_table *table);
t_bool	all_threads_running(t_mtx *mutex, long *threads, long philo_nbr);
t_bool	get_bool(t_mtx *mutex, bool *value);
time_t	get_time(int time_code);
long	ft_atol(const char *str);
long	get_long(t_mtx *mutex, long *value);
bool	is_digit(char c);
bool	is_space(char c);
bool	is_error(t_bool result);
bool	is_true(t_bool result);
void	*monitor_dinner(void *data);
void	*lone_philo(void *arg);
void	*actions(void *data);
void	*malloc_handler(size_t bytes);
int		thread_handler(pthread_t *thread, void *(*foo)(void *),
			void *data, t_opcode opcode);
int		mutex_handler(t_mtx *mutex, t_opcode opcode);
int		thinking(t_philo *philo, bool pre_simulation);
int		de_synchronize_philos(t_philo *philo);
int		parse_input(t_table *table, char **av);
int		data_init(t_table *table);
int		dinner_start(t_table *table);
int		set_bool(t_mtx *mutex, bool *dest, bool value);
int		set_long(t_mtx *mutex, long *dest, long value);
int		precise_usleep(long usec, t_table *table);
int		clean(t_table *table);
int		c_error(t_errors errors);
int		ft_putstr_fd(char *s);
int		write_status(t_philo_status status, t_philo *philo, bool debug);
int		wait_all_threads(t_table *table);
int		parse_philosopher_number(t_table *table, char *arg);
int		increase_long(t_mtx *mutex, long *value);
int		parse_time_to_die(t_table *table, char *arg);
int		parse_time_to_eat(t_table *table, char *arg);
int		parse_time_to_sleep(t_table *table, char *arg);
int		parse_nbr_limit_meals(t_table *table, char *arg);
int		is_non_digit(const char *str);
int		is_full(t_philo *philo);
int		thinking(t_philo *philo, bool pre_simulation);
int		eat(t_philo *philo);

#endif
