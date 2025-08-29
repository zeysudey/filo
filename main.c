#include "philo.h"

int loop(t_philo *philo)
{
    while (!is_simulation_stopped(philo->table))
    {
        think(philo);
        pick_forks(philo);
        if (is_simulation_stopped(philo->table))
        {
            drop_forks(philo);
            break;
        }
        eat(philo);
        drop_forks(philo);
        if (is_simulation_stopped(philo->table))
            break;
        sleep_philo(philo);
    }
    return (0);
}
void *philosopher_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    if (philo->table->philo_count == 1)
    {
        log_status(philo->id, "is thinking", philo->table);
        pthread_mutex_lock(philo->first_fork);
        log_status(philo->id, "has taken a fork", philo->table);
        usleep(philo->table->time_to_die * 1000);
        return (NULL);
    }
    loop(philo);
    return (NULL);
}

int main(int argc, char *argv[])
{
    t_table table;
    pthread_t monitor_thread;

    if(argc != 5 && argc != 6)
    {
        write(2, "wrong number of arguments\n", 27);
        return (1);
    }
    
    check_args(argv);
    
    if (check_init(argv, &table) != 0)
        return (1);

    if (create_philo_threads(&table) != 0)
    {
        cleanup(&table);
        return (1);
    }

    if (create_monitor_thread(&table, &monitor_thread) != 0)
    {
        join_philo_threads(&table);
        cleanup(&table);
        return (1);
    }

    join_all_threads(&table, monitor_thread);
    cleanup(&table);
    return (0);
}