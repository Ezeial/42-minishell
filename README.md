# minishell - Minimal Unix Shell in C

**42 School Project** – Recreate a minimal bash-like shell.

This project implements a simple interactive shell that handles external commands, pipes, redirections, environment variables, signals, and basic built-ins.

**Final grade: 110/100** (with bonuses)

## Features

- Custom prompt (`minishell$ `)
- Execution of external commands (e.g., `ls`, `cat`, `grep`, etc.)
- Built-ins:
  - `echo` (with `-n` option)
  - `cd` (with `-` and no argument support)
  - `pwd`
  - `export` / `unset`
  - `env`
  - `exit`
- Environment variables handling (`$PATH`, `$USER`, `$?`, etc.)
- Redirections (`>`, `>>`, `<`, `<<`)
- Pipes (`|`)
- Signal handling (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`)
- Single/double quotes and escape characters (`\"`, `\'`, `\$`, etc.)
- Command history (using readline)
- Proper error handling and exit statuses

## Installation

```bash
# Clone the repository
git clone https://github.com/Ezeial/42-minishell.git
cd 42-minishell

# Compile
make

# Clean (if needed)
make fclean