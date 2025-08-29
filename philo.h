#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>


typedef struct s_philo t_philo;  // "t_philo diye bir tip gelecek" diyoruz
typedef struct s_table t_table;
// Fork struct'ı
typedef struct s_fork
{
	pthread_mutex_t	mutex;
}	t_fork;

// Table/Data struct'ı
typedef struct s_table
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_limit;
	long			start_time;
    int simulation_stop;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	table_mutex;
	t_fork			*forks;
	t_philo			*philos;
}	t_table;

// Philosopher struct'ı
typedef struct s_philo
{
	int				id;
	int				meal_count;
	long			last_meal_time;
	pthread_mutex_t *first_fork;   // ← YENİ
    pthread_mutex_t *second_fork;  // ← YENİ
	pthread_t		thread_id;
	t_table			*table;
}	t_philo;
int init_table(t_table *table, char **argv);

int	ft_atoi(char *str);
void check_args(char **argv);
void error_message(int i);
long get_time(void);
int init_forks(t_table *table);
void cleanup(t_table *table);
int init_philos(t_table *table);
void *philosopher_routine(void *arg);
void think(t_philo *philo);
void eat(t_philo *philo);
void sleep_philo(t_philo *philo);
void log_status(int id, char *status, t_table *table);
void pick_forks(t_philo *philo);
void drop_forks(t_philo *philo);
int check_meals_completed(t_table *table);
void *monitor_routine(void *arg);
void stop_simulation(t_table *table);
int is_simulation_stopped(t_table *table);
int check_philosopher_death(t_philo *philo);
int check_init(char **argv, t_table *table);
int create_philosopher_threads(t_table *table);
int create_monitor_thread(t_table *table, pthread_t *monitor_thread);
void join_all_threads(t_table *table, pthread_t monitor_thread);
void join_philosopher_threads(t_table *table);
#endif