# 🐚 Minishell

> As beautiful as a shell. A minimal Unix-like shell implementation in C.

## 💡 About the Project
This project is a recreation of a basic shell program, inspired by bash. It involves deep dives into system administration, process creation, and inter-process communication. The goal was to build a robust program capable of parsing complex command lines, managing file descriptors, and executing built-in commands and external binaries using low-level POSIX system calls.

## 🚀 Features
* **Prompt:** Displays a custom prompt (`minishell-$ `) and handles a working history using the GNU Readline library.
* **Execution:** Searches and launches the right executable based on the `PATH` environment variable or using relative/absolute paths.
* **Redirections:**
  * `<` redirects input.
  * `>` redirects output.
  * `<<` (heredoc) reads input until a delimiter is seen.
  * `>>` redirects output in append mode.
* **Pipes (`|`):** Connects the output of one command to the input of the next.
* **Environment Variables:** Expands environment variables (`$VAR`) and the exit status of the most recently executed foreground pipeline (`$?`).
* **Signal Handling:**
  * `ctrl-C` prints a new prompt on a new line.
  * `ctrl-D` exits the shell.
  * `ctrl-\` does nothing, mirroring bash behavior.
* **Builtins:** `echo` (with `-n`), `cd`, `pwd`, `export`, `unset`, `env`, and `exit`.

## 🛠️ Tech Stack & Dependencies
* **Language:** C
* **Build System:** Makefile
* **Libraries:** GNU Readline
* **Core Concepts:** Process Control (`fork`, `execve`, `waitpid`), File Descriptors (`dup2`, `pipe`), Abstract Syntax Trees, Lexical Analysis.

## ⚙️ Installation & Usage

### Prerequisites
* GCC or Clang compiler
* Make
* GNU Readline library

### Compilation
Clone the repository and compile the project using the provided Makefile:

```bash
git clone [https://github.com/SASSI42/minishell.git](https://github.com/SASSI42/minishell.git)
cd minishell
make
```

### Running the Shell
```bash
./minishell
```

### Example Usage

```bash
minishell-$ echo "Hello 42" > file.txt
minishell-$ cat file.txt | grep "42" | wc -l
1
minishell-$ export TEST="success"
minishell-$ echo $TEST
success
minishell-$ exit
```

## 👨‍💻 Authors
[Mohammed Sassi](https://github.com/SASSI42)

hakaraou
