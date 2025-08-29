#include "philo.h"

void think(t_philo *philo)
{
    log_status(philo->id, "is thinking", philo->table);
}

void eat(t_philo *philo)
{
    log_status(philo->id, "is eating", philo->table);
    pthread_mutex_lock(&philo->table->table_mutex);
    philo->last_meal_time = get_time();
    philo->meal_count++;
    pthread_mutex_unlock(&philo->table->table_mutex);
    usleep(philo->table->time_to_eat * 1000);
}

void sleep_philo(t_philo *philo)
{
    log_status(philo->id, "is sleeping", philo->table);
    usleep(philo->table->time_to_sleep * 1000);
}

void pick_forks(t_philo *philo)
{
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->first_fork);
        log_status(philo->id, "has taken a fork", philo->table);
        pthread_mutex_lock(philo->second_fork);
        log_status(philo->id, "has taken a fork", philo->table);
    }
    else
    {
        pthread_mutex_lock(philo->second_fork);
        log_status(philo->id, "has taken a fork", philo->table);
        pthread_mutex_lock(philo->first_fork);
        log_status(philo->id, "has taken a fork", philo->table);
    }
}

void drop_forks(t_philo *philo)
{
    pthread_mutex_unlock(philo->first_fork);
    pthread_mutex_unlock(philo->second_fork);
}