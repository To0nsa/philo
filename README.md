# philo – Dining Philosophers Simulation in C

![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)
![Language: C](https://img.shields.io/badge/language-C-blue.svg)
![Made at 42/Hive](https://img.shields.io/badge/made%20at-42%20Hive-blueviolet)
[![GitHub Repo](https://img.shields.io/badge/GitHub-philo-black?logo=github)](https://github.com/nicolas-lovis/philo)

> A multithreaded simulation of the classic Dining Philosophers problem.

[🔗 View on GitHub](https://github.com/to0nsa/philo)
**[📚 View full documentation](https://to0nsa.github.io/philo/)**

This project implements a concurrent, real-time simulation of the Dining Philosophers problem using POSIX threads (pthreads) in C. Developed as part of the 42/Hive curriculum, the goal was to explore and solve common issues in **parallel programming** such as **deadlocks**, **race conditions**, and **thread synchronization**.

Philosophers alternate between thinking, eating, and sleeping, while competing for limited resources (forks). The program ensures each philosopher follows the rules safely and fairly, with careful handling of mutexes, timing, and shared state.

---

## ✨ Philo Features

<details>
<summary><strong>see features</strong></summary>

🔒 **Thread-Safe Synchronization**
All shared resources (forks, output, state) are protected with pthread_mutex_t. The simulation ensures no data race or double-access can occur — every action is guarded for correctness and consistency.

⏱️ **Accurate Timing Logic**
Precise delays are implemented using gettimeofday() and short polling loops to control when philosophers eat, sleep, and think — even under tight timing constraints. The system simulates real-time behavior down to the millisecond.

🚨 **Deadlock & Starvation Prevention**
The implementation avoids deadlock by alternating fork acquisition order and managing philosopher timings, especially in edge cases like an odd number of philosophers. No philosopher is allowed to starve or monopolize forks.

💥 **Graceful Termination**
The system monitors each philosopher and terminates the simulation cleanly when a philosopher dies or all have completed their required meals. Mutexes are destroyed, memory is freed, and threads are joined safely.

🧩 **Modular and Readable Codebase**
Each component (init, validation, routines, monitor, utils) is clearly separated and follows consistent naming conventions. Functions are thoroughly documented with Doxygen and grouped for easy navigation.

🎓 **Educational Focus**
This project deepens understanding of pthread basics, critical section design, timing precision, and memory-safe multithreading.

</details>

---

## ⚙️ How It Works

<details>
<summary><strong>see how it works</strong></summary>

The Dining Philosophers problem simulates a group of philosophers sitting around a table with forks placed between them. Each philosopher needs two forks to eat, one on their left and one on their right. The challenge is to design a system where philosophers can eat, sleep, and think without causing deadlocks or starvation.

Here’s how the simulation works internally:

**1. Initialization: Setting the Table**
Before the simulation starts:

- The program reads the command-line arguments to get the number of philosophers and timing constraints (time to die, eat, sleep, and optionally, how many times each must eat).
- It creates a t_philo structure for each philosopher, and sets up pthread_mutex_t for every fork.
- Each philosopher knows:
  - Their ID
  - Their left and right fork indices
  - Their meal count and last meal time

The table is now "set" — and every philosopher has their seat and utensils.

**2. Launching Threads: One Per Philosopher**
Each philosopher is launched in its own thread using pthread_create.
Their routine loops through:

- Thinking – where they prepare to eat
- Eating – where they try to acquire both forks
- Sleeping – where they rest before starting the loop again

To avoid collisions on shared data (forks, output), mutexes are used to ensure synchronization.

**3. Taking Forks: Safe Locking Strategy**
To avoid deadlocks, philosophers follow a fork-picking strategy:

- Even-indexed philosophers pick up the left fork first, then the right.
- Odd-indexed ones do the opposite.

This asymmetry helps prevent a circular wait, which would freeze all threads.

**4. Monitoring Death: Life Clock**
A monitor thread (or a loop in main thread) constantly checks:

- If any philosopher hasn’t eaten within time_to_die
- If all philosophers have eaten must_eat_count times

If a philosopher starves, the simulation ends, printing the time and ID of the dead philosopher. If everyone is full, it also ends cleanly.

**5. Printing Actions: Thread-Safe Logging**
Every action (take fork, is eating, is sleeping, etc.) is logged with:

- Timestamp (in ms since simulation started)
- Philosopher ID
- Action text

A mutex (print_padlock) ensures logs don’t overlap when multiple threads print simultaneously.

**6. Exiting Cleanly**
When the simulation ends:

- All threads are joined
- All mutexes are destroyed
- All memory is freed

No leaks, no deadlocks, no philosophers left hanging.

💡 **Why This Works Efficiently**
The simulation enforces mutual exclusion using well-placed mutexes and a minimal design:

- One thread per philosopher (scalable up to 200)
- Precise timing and fair rotation
- Deadlock avoidance using fork acquisition order

This makes the program not only robust, but predictable, deadlock-free, and easy to reason about under concurrent stress.

</details>

---

## 🚀 Usage

<details>
<summary><strong> See usage guide  </strong></summary>

🛠️ **To build the Philosopher simulation, simply run:**

```bash
make
```

📄 **Arguments**

``` text
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [meals_required]
```

- All values must be positive integers
- meals_required is optional

🧪 **Example run**

``` bash
./philo 5 800 200 200
```

This starts the simulation with:

- 5 philosophers
- 800ms time to die
- 200ms time to eat
- 200ms time to sleep

Each philosopher will cycle through thinking → eating → sleeping until one dies or the end of time.

🧪 **With optional meal limit**

```bash
./philo 5 800 200 200 7
```

This ends the simulation once each philosopher has eaten 7 times.

🖥️ **Expected Output**

``` csharp
0 1 is thinking
1 2 has taken a fork
2 2 has taken a fork
3 2 is eating
...
```

Each log line shows:

```text
[timestamp_ms] [philosopher_id] [action]
```

All logs are synchronized and printed in order without overlap.

</details>

---
## 📝 License

This project is licensed under the [MIT License](LICENSE).

You are free to use, modify, and distribute this code for academic, personal, or professional purposes. Attribution is appreciated but not required.

---

## 📬 Contact

If you have any questions, suggestions, or feedback, feel free to reach out:

- **📧 Email:** nicolas.lovis@hotmail.fr
- **💻 GitHub:** [github.com/to0nsa](https://github.com/to0nsa)

You're also welcome to open an issue or leave a comment on the repository.
