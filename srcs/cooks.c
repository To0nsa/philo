/**
 * @file cooks.c
 * @author Toonsa
 * @date 2025/01/25
 * @brief Utility functions for time and string output.
 *
 * @details
 * Contains helper functions used throughout the philosopher simulation:
 * - Timestamp acquisition
 * - Safe integer parsing
 * - Error-resilient string output
 * 
 * @ingroup philosopher_core
 */

 #include "../include/philo.h"

 /**
  * @brief Get the current system time in milliseconds.
  *
  * @details
  * Retrieves the current time of day using `gettimeofday` and returns
  * the timestamp in milliseconds.
  * 
  * @return Current time in milliseconds.
  */
 long long	get_current_time(void)
 {
	 struct timeval	timeval;
 
	 gettimeofday(&timeval, NULL);
	 return ((timeval.tv_sec * 1000) + (timeval.tv_usec / 1000));
 }
 
 /**
  * @internal
  * @brief Check whether adding a digit would overflow `INT_MAX`.
  *
  * @details
  * Used internally in `ft_atoi` to detect overflow before it occurs.
  * 
  * @param num Current accumulated number.
  * @param digit Next character digit to evaluate.
  * @return `true` if overflow would occur, `false` otherwise.
  */
 static bool	ft_check_overflow(long long num, char digit)
 {
	 long long	cutoff;
 
	 cutoff = INT_MAX / 10;
	 if (num > cutoff
		 || (num == cutoff && (digit - '0') > (INT_MAX % 10)))
		 return (true);
	 return (false);
 }
 
 /**
  * @brief Convert a string to a positive integer.
  *
  * @details
  * Converts a numeric string into a `long long` value, rejecting
  * any value that would exceed `INT_MAX`. Does not support signs
  * or non-numeric characters.
  * 
  * @note Returns `-1` on overflow or invalid input.
  *
  * @param str Numeric string to convert.
  * @return Parsed integer value, or -1 on error.
  */
 long long	ft_atoi(const char *str)
 {
	 long long	num;
 
	 num = 0;
	 while (*str)
	 {
		 if (ft_check_overflow(num, *str))
			 return (-1);
		 num = num * 10 + (*str - '0');
		 str++;
	 }
	 return (num);
 }
 
 /**
  * @internal
  * @brief Calculate the length of a null-terminated string.
  *
  * @param str The input string.
  * @return The number of characters before the null terminator.
  */
 static int	ft_strlen(const char *str)
 {
	 int	len;
 
	 len = 0;
	 while (str[len] != '\0')
		 len++;
	 return (len);
 }
 
 /**
  * @brief Write a string to a file descriptor safely.
  *
  * @details
  * Writes the entire string even if interrupted by signals (EINTR).
  * On fatal write errors, the function exits with failure.
  * 
  * @note Returns -1 if `str` is NULL. Exits the program on fatal write errors.
  *
  * @param fd The file descriptor to write to.
  * @param str The null-terminated string to output.
  * @return Number of bytes successfully written, or -1 on NULL input.
  */
 int	ft_putstr_fd(int fd, char *str)
 {
	 int	bytes_written;
	 int	total_written;
	 int	len;
 
	 if (str == NULL)
		 return (-1);
	 total_written = 0;
	 len = ft_strlen(str);
	 while (total_written < len)
	 {
		 bytes_written = write(fd, str + total_written, len - total_written);
		 if (bytes_written == -1)
		 {
			 if (errno == EINTR)
				 continue ;
			 exit(EXIT_FAILURE);
		 }
		 total_written += bytes_written;
	 }
	 return (total_written);
 }
 