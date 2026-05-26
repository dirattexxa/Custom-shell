# Daunshell 🖥️

A custom, low-level Linux Shell written from scratch in modern C++ to deeply understand operating system internals, process management, and the POSIX API.

## 🚀 Overview

`Daunshell` is a lightweight command-line interpreter that communicates directly with the Linux kernel. Instead of using high-level wrappers, it utilizes native system calls to clone processes, handle memory, and execute binaries.

## 🛠️ Features Implemented

* **Command Parsing:** Efficiently splits user input into tokens using `std::stringstream`, preserving arguments and stripping extra spaces.
* **Process Clones (`fork`):** Leverages the `fork()` system call to duplicate the shell into parent and child processes.
* **Binary Execution (`execvp`):** The child process dynamically replaces its own memory image with the requested system binary (e.g., `ls`, `pwd`, `uname`).
* **Process Synchronization (`waitpid`):** The parent shell safely goes into suspension until the executed child process completely exits, preventing I/O mixing.

## 🧬 Under the Hood (How it works)
