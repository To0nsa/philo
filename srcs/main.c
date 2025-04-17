/**
 * @file main.c
 * @author 
 * @date 2025/01/25
 * @brief Entry point of the philosopher simulation.
 *
 * @details
 * This file contains the `main` function which sets up the simulation:
 * - Parses arguments
 * - Initializes the table and rules
 * - Starts philosopher threads
 * - Launches the dinner monitor
 *
 * @ingroup philosopher_core
 */

 #include "../include/philo.h"

 /**
  * @brief Launch the Dining Philosophers simulation.
  *
  * @details
  * Initializes the simulation environment, spawns philosopher threads,
  * and starts the monitor loop that watches for termination conditions.
  *
  * @param argc Argument count from command line.
  * @param argv Argument vector containing configuration parameters.
  * @return Always returns `EXIT_SUCCESS`.
  *
  * @ingroup philosopher_core
  */
 int	main(int argc, char **argv)
 {
	 t_table	table;
 
	 receive_guests(argc, argv);
	 set_table(&table, argc, argv);
	 welcome_philosophers(&table);
	 set_rules(&table);
	 seat_philosophers_at_the_table(&table);
	 dinner_monitor(&table);
	 return (EXIT_SUCCESS);
 }
 