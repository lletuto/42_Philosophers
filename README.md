# philosophers — École 42

> A simulation of the dining philosophers problem using threads and mutexes.

---

## Description

`philosophers` simulates the classic **dining philosophers problem**: a number of philosophers sit at a round table, alternating between eating, sleeping, and thinking. A fork is placed between each pair of adjacent philosophers, and a philosopher needs both forks to eat. The challenge is to avoid deadlocks and race conditions while ensuring no philosopher starves.

Each philosopher is a **thread**, and each fork is protected by a **mutex**.

---

## Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

| Argument | Description |
|---|---|
| `number_of_philosophers` | Number of philosophers (and forks) at the table |
| `time_to_die` | Time in ms before a philosopher dies if they haven't eaten |
| `time_to_eat` | Time in ms a philosopher spends eating |
| `time_to_sleep` | Time in ms a philosopher spends sleeping |
| `number_of_times_each_philosopher_must_eat` | (Optional) Simulation stops when all philosophers have eaten this many times |

### Examples

```bash
./philo 5 800 200 200
./philo 5 800 200 200 7
./philo 1 800 200 200   # one philosopher, cannot eat, must die
```

---

## Rules

- A philosopher picks up their left fork, then their right fork
- A philosopher must hold both forks to eat
- After eating, they put down both forks and go to sleep
- After sleeping, they think until they can eat again
- If a philosopher has not started eating within `time_to_die` milliseconds since their last meal (or since the start), they die
- The simulation stops as soon as one philosopher dies, or when all philosophers have eaten enough times

---

## How it works

### Threads
Each philosopher runs in its own thread, looping through eat → sleep → think until the simulation ends.

### Mutexes
Each fork is a mutex. A philosopher locks both adjacent mutexes before eating and unlocks them after. A monitoring thread continuously checks timestamps to detect if any philosopher has exceeded `time_to_die` without eating.

### Death detection
A dedicated monitor thread polls each philosopher's last meal timestamp at regular intervals. All timestamps are protected by mutexes to prevent data races. As soon as a death is detected, a shared flag is set and all threads stop.

### Avoiding deadlocks
To prevent all philosophers from picking up their left fork simultaneously and waiting forever, even-numbered philosophers pick up their right fork first.

---

## Compilation & Usage

```bash
make
./philo 5 800 200 200
```

---

## École 42

Project completed as part of the École 42 curriculum. Only `pthread` functions are used for threading and synchronization — no bonus (processes/semaphores) implemented.
