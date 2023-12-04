# TPMajInfo1 - Micro Shell Implementation

## Welcome to ENSEA Tiny Shell

### Table of Contents
- [Q.1: Micro Shell Implementation (enseash)](#q1)
- [Q.2: Execution and REPL Loop](#q2)
- [Q.3: Exit Command and CTRL+D](#q3)
- [Q.4: Display Return Code/Signal](#q4)
- [Q.5: Measurement of Execution Time](#q5)
- [Q.6: Execution of Complex Commands](#q6)
- [Q.7: Redirections with `<` and `>`](#q7)

## Q.1: Micro Shell Implementation (enseash) <a name="q1"></a>

Create a micro shell, named `enseash`, for launching commands and displaying information about their execution.

![Q1](Q1.png)

## Q.2: Execution and REPL Loop <a name="q2"></a>

Implement a Read-Eval-Print Loop (REPL) for the micro shell:
- a) Read the command entered by the user.
- b) Execute the command (simple command without arguments).
- c) Print the prompt `enseash %` and wait for a new command.

![Q2](Q2.png)

## Q.3: Exit Command and CTRL+D <a name="q3"></a>

Manage the shell output with the command `exit` or with `<ctrl>+d`.

![Q3](Q3.png)

## Q.4: Display Return Code/Signal <a name="q4"></a>

Display the return code or signal of the previous command in the prompt.

![Q4](Q4.png)

## Q.5: Measurement of Execution Time <a name="q5"></a>

Measure the command execution time using `clock_gettime`.

![Q5_1](Q5_1.png)
![Q5_2](Q5_2.png)

## Q.6: Execution of Complex Commands <a name="q6"></a>

Implement the execution of complex commands with arguments. But I did question 6, 7 and 8 with the bin/sh file it works but we need a version with strtok.

![Q6v1](Q6v1.png)
![Q6](Q6.png)

## Q.7: Redirections with `<` and `>` <a name="q7"></a>

We have now a version with strtok. Manage redirections to stdin and stdout with `<` and `>`.

![Q7](Q7.png)
