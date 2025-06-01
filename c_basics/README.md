# C Basics: Flight Sensor Data Logger & Rudder Controller Simulation

This project is a simple multi-file C application designed to demonstrate core C programming concepts relevant to embedded systems development, particularly inspired by roles involving flight automation, sensor integration, and safety-critical applications.

It simulates reading data from a flight sensor, processing status flags, and controlling a rudder based on very basic logic.

## C Features Demonstrated:

1.  **Basic Syntax & Control Flow:**

    - Variable declarations (e.g., `int`, `float`, `int8_t`, `uint8_t`).
    - Operators (arithmetic, bitwise, logical, assignment).
    - Control flow statements (`if`, `else if`, `else`, `for` loop).
    - Function calls and return values.

2.  \*\*Modular Programming (Multi-File Project):

    - **Header Files (`.h`):** Used for declarations (interfaces).
      - `sensor_module.h`: Declares `SensorData` struct and functions for sensor simulation.
      - `rudder_control.h`: Declares `RudderConfig` struct and functions for rudder control simulation.
    - **Source Files (`.c`):** Used for definitions (implementations).
      - `sensor_module.c`: Implements sensor-related functions.
      - `rudder_control.c`: Implements rudder control functions.
      - `main.c`: Contains the main application logic, initializes modules, and runs the simulation loop.

3.  **Preprocessor Directives:**

    - `#include <header.h>`: For standard library headers (e.g., `stdio.h`, `stdint.h`, `stdlib.h`, `time.h`).
    - `#include "my_header.h"`: For project-specific header files.
    - `#ifndef HEADER_GUARD_H_ ... #define HEADER_GUARD_H_ ... #endif`: Include guards to prevent multiple inclusions of header files.
    - `#define CONSTANT_NAME value`: Used for defining symbolic constants (e.g., `SENSOR_STATUS_OK`, `RUDDER_MAX_ANGLE`).

4.  \*\*Structs (`struct`):

    - Used to group related data items together into a single custom type.
    - `SensorData` struct in `sensor_module.h`.
    - `RudderConfig` struct in `rudder_control.h`.
    - `typedef struct { ... } TypeName;` used for convenience to avoid writing `struct TypeName` everywhere.

5.  \*_Pointers (`_`):

    - Declaring pointer variables (e.g., `RudderConfig *config`).
    - Passing pointers to functions to allow modification of the original data (e.g., `rudder_set_angle` takes `RudderConfig *`).
    - Using the `->` (arrow) operator to access members of a struct via a pointer (e.g., `config->current_angle_deg`).
    - Using the `&` (address-of) operator to get the memory address of a variable (e.g., `&controlled_rudder` in `main.c`).
    - `const` correctness with pointers (e.g., `const RudderConfig *config` in `rudder_get_current_angle` to indicate the pointed-to data will not be modified by the function).
    - Checking for `NULL` pointers before dereferencing.

6.  \*\*Fixed-Width Integers (`stdint.h`):

    - Using types like `uint8_t`, `int8_t`, `int16_t` for precise control over integer sizes, which is crucial in embedded systems for interacting with hardware registers or communication protocols.

7.  **Bitwise Operations:**

    - `<<` (left shift): Used in `#define` for creating bitmasks (e.g., `(1 << 0)`).
    - `|` (bitwise OR) and `|=` (bitwise OR assignment): Used for setting status bits in `sensor_read_data`.
    - `&` (bitwise AND): Used for checking status bits in `sensor_process_status_flags` and `main.c`.
    - `~` (bitwise NOT): Used with `&` for clearing status bits (e.g., `data.status_flags &= ~SENSOR_STATUS_OK;`).

8.  \*\*Static Variables (File Scope):

    - Variables declared with `static` outside any function (e.g., `static int sensor_initialized;` in `sensor_module.c`) have their scope limited to that specific `.c` file. They are not visible to other files, providing a way to encapsulate module-private state.

9.  **Standard Library Functions:**

    - `printf()` from `stdio.h` for formatted output.
    - `rand()`, `srand()` from `stdlib.h` for pseudo-random number generation (simulation).
    - `time()` from `time.h` to seed the random number generator.
    - `sleep()` from `unistd.h` (POSIX) for pausing execution (commented out in `main.c` due to platform specificity).

10. \*\*`main` Function (`int main(void)`):

    - The entry point of the C application.
    - Returns `0` to indicate successful execution.

11. **Makefile for Compilation:**
    - A simple `Makefile` is provided to automate the build process using `gcc`.
    - Defines compiler, flags, source/object files, and targets (`all`, `clean`, `help`).
    - Separates compilation of individual `.c` files into `.o` object files and then links them into the final executable.

## How to Compile and Run:

1.  **Prerequisites:** You need a C compiler like `gcc` installed and the `make` utility.
2.  **Navigate to the `c_basics` directory** in your terminal.
3.  **Compile:** Run the command `make` or `make all`.
    - This will compile `main.c`, `sensor_module.c`, and `rudder_control.c` into object files (`.o`) and then link them to create an executable named `flight_sim`.
4.  **Run:** Execute the program using `./flight_sim`.
5.  **Clean:** To remove the compiled object files and the executable, run `make clean`.

## Further Learning & Relation to Job Listing:

This project provides a foundation. For the specific job, you would expand on these concepts:

- **Actual Hardware Interaction:** Replace simulated functions with code that reads/writes to real hardware registers for I2C, CAN, SPI, UART using microcontroller-specific libraries or direct memory-mapped I/O.
- **Safety-Critical Aspects:** Introduce error handling, assertions, potentially defensive programming techniques, and consider coding standards like MISRA C (though that's a big topic itself).
- **Real-time Constraints:** Think about how timing and determinism would affect the code (not deeply covered here).
- **More Complex Data Structures & Algorithms:** For flight automation, you'd likely use more advanced data structures and algorithms.
- **Testing:** Develop unit tests for each module and integration tests for the system (hardware/software in the loop simulation).
- **Embedded Linux:** If working with embedded Linux, you might use system calls, device drivers, and higher-level libraries.

This project aims to get you comfortable with the C language's structure, syntax, and common idioms used in multi-file embedded projects.
