# philosophers
This project is about learning how threads work by precisely timing a group of philosophers on when to pick up forks and eat spaghetti without dying from hunger.

• One or more philosophers sit at a round table.
There is a large bowl of spaghetti in the middle of the table.
• The philosophers alternatively eat, think, or sleep.
While they are eating, they are not thinking nor sleeping;
while thinking, they are not eating nor sleeping;
and, of course, while sleeping, they are not eating nor thinking.
• There are also forks on the table. There are as many forks as philosophers.
• Because serving and eating spaghetti with only one fork is very inconvenient, a
philosopher takes their right and their left forks to eat, one in each hand.
• When a philosopher has finished eating, they put their forks back on the table and
start sleeping. Once awake, they start thinking again. The simulation stops when
a philosopher dies of starvation.
• Every philosopher needs to eat and should never starve.
• Philosophers don’t speak with each other.
• Philosophers don’t know if another philosopher is about to die.
• No need to say that philosophers should avoid dying
-------
• Program takes the following arguments:
number_of_philosophers time_to_die time_to_eat time_to_sleep
(number_of_times_each_philosopher_must_eat)
◦ number_of_philosophers: The number of philosophers and also the number
of forks.
◦ time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die
milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
◦ time_to_eat (in milliseconds): The time it takes for a philosopher to eat.
During that time, they will need to hold two forks.
◦ time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.
◦ number_of_times_each_philosopher_must_eat (optional argument): If all
philosophers have eaten at least number_of_times_each_philosopher_must_eat
times, the simulation stops. If not specified, the simulation stops when a
philosopher dies.
• Each philosopher has a number ranging from 1 to number_of_philosophers.
• Philosopher number 1 sits next to philosopher number number_of_philosophers.
Any other philosopher number N sits between philosopher number N - 1 and philosopher number N + 1.
-------
About the logs of the program:
• Any state change of a philosopher is formatted as follows:
◦ timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died
Replacing timestamp_in_ms with the current timestamp in milliseconds
and X with the philosopher number.
• A displayed state message is not mixed up with another message.
• A message announcing a philosopher died is displayed no more than 10 ms
after the actual death of the philosopher.
• Again, philosophers should avoid dying!
------
The specific rules for the mandatory part are:
• Each philosopher should be a thread.
• There is one fork between each pair of philosophers. Therefore, if there are several
philosophers, each philosopher has a fork on their left side and a fork on their right
side. If there is only one philosopher, there should be only one fork on the table.
• To prevent philosophers from duplicating forks, you should protect the forks state
with a mutex for each of them.
------
ALLOWED EXTERNAL FUNCTIONS:
void *memset(void *b, int c, size_t len)
	The memset() function writes len bytes of value c (converted to an unsigned char) to the string b.
	Returns it's first argument.

printf, malloc, free, write

int	usleep(useconds_t microseconds)
	The usleep() function suspends execution of the calling thread until either microseconds microseconds have elapsed or a signal is delivered to the thread and its action is to invoke a signal-catching function or to terminate the process.  System activity or limitations may lengthen the sleep by an indeterminate amount.
	The usleep() function returns the value 0 if successful; otherwise the value -1 is returned and the global variable errno is set to indicate the error.

int	gettimeofday(struct timeval *restrict tp, void *restrict tzp)
	struct timeval {
             time_t       tv_sec;   /* seconds since Jan. 1, 1970 */
             suseconds_t  tv_usec;  /* and microseconds */
    };
    struct timezone {
            int     tz_minuteswest; /* of Greenwich */
            int     tz_dsttime;     /* type of dst correction to apply */
	A 0 return value indicates that the call succeeded.  A -1 return value indicates an error occurred, and in this case an error code is stored into the global variable errno.

int	pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);

int	pthread_detach(pthread_t thread);

int	pthread_join(pthread_t thread, void **value_ptr); 

int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);

int pthread_mutex_destroy(pthread_mutex_t *mutex);

int pthread_mutex_lock(pthread_mutex_t *mutex)
	If successful, pthread_mutex_lock() will return zero, otherwise an error number will be returned to indicate the error.

int pthread_mutex_unlock(pthread_mutex_t *mutex);
	If the current thread holds the lock on mutex, then the pthread_mutex_unlock() function unlocks mutex.
	Calling pthread_mutex_unlock() with a mutex that the calling thread does not hold will result in undefined behavior.
    If successful, pthread_mutex_unlock() will return zero, otherwise an error number will be returned to indicate the error.