# minishell

**minishell** is a simple shell implementation written in C that mimics the behavior of the bash shell. The goal of this project is to simulate a Unix-like shell with basic command execution, input/output redirection, and signal handling. The project also includes a 10% bonus that implements custom signal handling.

---

## About

The **minishell** project is a basic shell that reads user input, processes it, and executes commands. It supports built-in commands like `echo`, `cd`, `pwd`, as well as external commands. The bonus part focuses on signal handling, specifically handling signals like `Ctrl+C` and `Ctrl+D`.

### Core Requirements:
- Implement a shell that can execute simple commands.
- Handle basic built-in commands like `echo`, `cd`, and `pwd`.
- Implement input/output redirection (e.g., `>`, `>>`, `<`).
- Use fork, exec, and wait to handle command execution.
- Handle environment variables.
  
---

## Installation

To install **minishell**, follow these steps:

1. Clone this repository:
    ```bash
    git clone https://github.com/ahmedelbahri/minishell.git
    cd minishell
    ```

2. Compile the project:
    ```bash
    make
    ```

3. Optionally, to remove all compiled objects:
    ```bash
    make clean
    ```

4. To remove the executable:
    ```bash
    make fclean
    ```

5. To recompile the project after cleaning:
    ```bash
    make re
    ```

---

## Usage

To run the shell, simply execute the compiled program:

```bash
./minishell
