#include "philo.h"

int check_philo_death(t_philo *philo)
{
    long current_time;
    long last_meal;
    
    pthread_mutex_lock(&philo->table->table_mutex);
    current_time = get_time();
    last_meal = current_time - philo->last_meal_time;
    pthread_mutex_unlock(&philo->table->table_mutex);
    
    if (last_meal > philo->table->time_to_die)
    {
        stop_simulation(philo->table);
        
        pthread_mutex_lock(&philo->table->print_mutex);
        printf("%ld %d died\n", current_time - philo->table->start_time, philo->id);
        pthread_mutex_unlock(&philo->table->print_mutex);
        
        return (1);
    }
    return (0);
}

int check_meals_completed(t_table *table)
{
    int i;
    int completed_meals;
    
    if (table->meal_limit == -1)
        return (0);
    
    pthread_mutex_lock(&table->table_mutex);
    i = 0;
    completed_meals = 0;
    
    while (i < table->philo_count)
    {
        if (table->philos[i].meal_count >= table->meal_limit)
            completed_meals++;
        i++;
    }
    pthread_mutex_unlock(&table->table_mutex);
    
    if (completed_meals == table->philo_count)
    {
        stop_simulation(table);
        return (1);
    }
    return (0);
}

int is_simulation_stopped(t_table *table)
{
    int stopped;
    
    pthread_mutex_lock(&table->table_mutex);
    stopped = table->simulation_stop;
    pthread_mutex_unlock(&table->table_mutex);
    
    return (stopped);
}

void stop_simulation(t_table *table)
{
    pthread_mutex_lock(&table->table_mutex);
    table->simulation_stop = 1;
    pthread_mutex_unlock(&table->table_mutex);
}

void *monitor_routine(void *arg)
{
    t_table *table = (t_table *)arg;
    int i;
    
    while (!is_simulation_stopped(table))
    {
        if (check_meals_completed(table))
        {
            break;
        }
        
        i = 0;
        while (i < table->philo_count && !is_simulation_stopped(table))
        {
            if (check_philo_death(&table->philos[i]))
            {
                break;
            }
            i++;
        }
        usleep(1000);
    }
    
    return (NULL);
}
