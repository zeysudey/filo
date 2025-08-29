#include "philo.h"

int	ft_atoi(char *str)
{
	int	i;
	int	nbr;

	if (!str || !*str)
		return (-1);	
	nbr = 0;
	i = -1;
	while (str[++i])
		if (str[i] < '0' || str[i] > '9')
			return (-1);
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + str[i] - '0';
		i++;
	}
	if (nbr == 0)
		return (-1);
	else
		return (nbr);
}

long get_time(void)
{
    struct timeval tv;
    
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void log_status(int id, char *status, t_table *table)
{
    long timestamp;
    
    pthread_mutex_lock(&table->print_mutex);
    if (!is_simulation_stopped(table))  
    {
        timestamp = get_time() - table->start_time;
        printf("%ld %d %s\n", timestamp, id, status);
    }
    pthread_mutex_unlock(&table->print_mutex);
}

void cleanup(t_table *table)
{
    int i;
    
    i = 0;
    while (i < table->philo_count)
    {
        pthread_mutex_destroy(&table->forks[i].mutex);
        i++;
    }
    pthread_mutex_destroy(&table->print_mutex);
    pthread_mutex_destroy(&table->table_mutex);
}


