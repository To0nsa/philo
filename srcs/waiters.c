/**
 * @file waiters.c
 * @author 
 * @date 2025/01/25
 * @brief Handles timing, printing, and end-state checking for philosophers.
 *
 * @details
 * This module defines support functions used by all philosopher threads:
 * - Delaying execution for a precise time span
 * - Displaying philosopher actions in a thread-safe way
 * - Checking and setting simulation termination status
 *
 * @ingroup philosopher_core
 */

 #include "../include/philo.h"

 /**
  * @brief Block the current thread for a specific number of milliseconds.
  *
  * @details
  * Sleeps the current philosopher using `usleep` until `time_to` ms has passed,
  * or until the dinner ends. Precision is maintained with short sleeps and polling.
  *
  * @param philo Pointer to the philosopher context.
  * @param time_to Time in milliseconds to wait.
  *
  * @ingroup philosopher_core
  */
 void	advance_time(t_philo *philo, long long time_to)
 {
	 long long	start;
 
	 start = get_current_time();
	 while (!is_dinner_over(philo, false)
		 && (get_current_time() - start) < time_to)
		 usleep(100);
 }
 
 /**
  * @brief Print a philosopher's current action with a timestamp.
  *
  * @details
  * Outputs a log line including:
  * - The time since simulation start
  * - The philosopher ID
  * - The action string (e.g., "is eating", "has taken a fork")
  *
  * Uses a mutex to ensure output remains synchronized across threads.
  * Special-case: if action starts with `'e'`, prints END_MSG after the line.
  *
  * @param philo Pointer to the philosopher who is performing the action.
  * @param action String representing the action being performed.
  *
  * @ingroup philosopher_core
  */
 void	print_action(t_philo *philo, const char *action)
 {
	 long long	time;
 
	 pthread_mutex_lock(&philo->table->print_padlock);
	 if (!is_dinner_over(philo, false))
	 {
		 time = get_current_time() - philo->table->start_time;
		 printf("%lld %d %s\n", time, philo->id, action);
	 }
	 pthread_mutex_unlock(&philo->table->print_padlock);
	 if (action[0] == 'e')
		 printf("%s\n", END_MSG);
 }
 
 /**
  * @brief Check or update the global simulation termination flag.
  *
  * @details
  * If `end` is true, the simulation is marked as finished. Otherwise,
  * the function checks whether the end flag has already been set.
  * Thread-safe access is ensured via a mutex.
  *
  * @param philo Pointer to the current philosopher.
  * @param end If true, set the global end flag.
  * @return `true` if the simulation is (or has been) marked as ended.
  *
  * @ingroup philosopher_core
  */
 bool	is_dinner_over(t_philo *philo, bool end)
 {
	 pthread_mutex_lock(&philo->table->end_padlock);
	 if (end || philo->table->end_flag)
	 {
		 if (end)
			 philo->table->end_flag = 1;
		 pthread_mutex_unlock(&philo->table->end_padlock);
		 return (true);
	 }
	 pthread_mutex_unlock(&philo->table->end_padlock);
	 return (false);
 }
 