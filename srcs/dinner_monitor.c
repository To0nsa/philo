/**
 * @file dinner_monitor.c
 * @author 
 * @date 2025/01/25
 * @brief Handles philosopher termination and simulation lifecycle.
 *
 * @details
 * Implements the monitoring thread that continuously checks if a philosopher
 * has died or if all have finished eating. It also handles cleanup logic,
 * including thread joining and mutex destruction.
 *
 * @ingroup philosopher_core
 */

 #include "../include/philo.h"

 /**
  * @brief Free allocated memory for philosophers and forks.
  *
  * @details
  * Releases the memory allocated for the philosopher array
  * and the fork mutex array.
  *
  * @param table Pointer to the shared simulation table.
  *
  * @ingroup philosopher_core
  */
 void	clean_table(t_table *table)
 {
	 free (table->philo);
	 free (table->fork_padlock);
 }
 
 /**
  * @internal
  * @brief Destroy all mutexes initialized for the simulation.
  *
  * @details
  * Destroys fork mutexes as well as the print, eat, and end control mutexes.
  *
  * @param table Pointer to the shared simulation table.
  *
  * @ingroup philosopher_core
  */
 static void	unset_rules(t_table *table)
 {
	 int	i;
 
	 i = -1;
	 while (++i < table->philosopher_count)
		 pthread_mutex_destroy(&table->fork_padlock[i]);
	 pthread_mutex_destroy(&table->print_padlock);
	 pthread_mutex_destroy(&table->eat_padlock);
	 pthread_mutex_destroy(&table->end_padlock);
 }
 
 /**
  * @brief Gracefully ends the simulation and cleans up.
  *
  * @details
  * Waits for all philosopher threads to finish, destroys all
  * synchronization primitives, and frees dynamic memory.
  *
  * @param table Pointer to the shared simulation table.
  *
  * @ingroup philosopher_core
  */
 void	end_dinner(t_table *table)
 {
	 int	i;
 
	 i = -1;
	 while (++i < table->philosopher_count)
		 pthread_join(table->philo[i].thread, NULL);
	 unset_rules(table);
	 clean_table(table);
 }
 
 /**
  * @internal
  * @brief Check if a philosopher died or has eaten enough.
  *
  * @details
  * Verifies whether a philosopher has passed their time-to-die,
  * or has reached the meal requirement. If so, the simulation ends.
  *
  * @param philo Pointer to the philosopher being monitored.
  * @return `true` if simulation must end, `false` otherwise.
  *
  * @ingroup philosopher_core
  */
 static bool	is_someone_dead_or_full(t_philo *philo)
 {
	 pthread_mutex_lock(&philo->table->eat_padlock);
	 if (get_current_time() - philo->last_meal >= philo->table->time_to_die)
	 {
		 print_action(philo, DIE);
		 is_dinner_over(philo, true);
		 pthread_mutex_unlock(&philo->table->eat_padlock);
		 return (true);
	 }
	 else if (philo->table->must_eat_count > 0
		 && philo->meal_count >= philo->table->must_eat_count)
	 {
		 philo->table->is_full++;
		 if (philo->table->is_full >= philo->table->philosopher_count)
		 {
			 is_dinner_over(philo, true);
			 print_action(philo, END);
			 pthread_mutex_unlock(&philo->table->eat_padlock);
			 return (true);
		 }
	 }
	 pthread_mutex_unlock(&philo->table->eat_padlock);
	 return (false);
 }
 
 /**
  * @brief Monitor philosopher states and end dinner when appropriate.
  *
  * @details
  * Continuously checks if any philosopher has died or if all have eaten
  * enough. Ends the simulation accordingly and performs cleanup.
  *
  * @param table Pointer to the shared simulation table.
  *
  * @ingroup philosopher_core
  */
 void	dinner_monitor(t_table *table)
 {
	 int	i;
	 int	continue_flag;
 
	 continue_flag = 1;
	 while (continue_flag)
	 {
		 i = -1;
		 table->is_full = 0;
		 while (++i < table->philosopher_count)
		 {
			 if (continue_flag && is_someone_dead_or_full(&table->philo[i]))
				 continue_flag = 0;
		 }
		 usleep(10);
	 }
	 end_dinner(table);
 }
 