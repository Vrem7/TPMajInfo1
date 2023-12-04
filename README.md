# TPMajInfo1#

MAYIMONA ZANDU Merveille  
KARDELLAS Amin

![](Image/header.jpg)

## Sommaire
- [Q.1](#q1)
- [Q.2](#q2)
- [Q.3](#q3)
- [Q.4](#q4)
- [Q.5](#q5)
- [Q.6](#q6)
- [Q.7](#q7)
- [Q.8](#q8)
- [Q.9](#q9)

## Q.1

Create a micro shell, which you will call enseash, to be used for launching commands and
displaying information about their execution.  

![](Q1.png)

## Q.2
Execution of the entered command and return to the prompt (REPL : read–eval–print
loop) :
- a) read the command entered by user,
- b) execute this command (simple command for the moment, without argument)),
- c) print the prompt enseash % and waits for a new command

![](Q2.png)

## Q.3

Management of the shell output with the command ”exit” or with <ctrl>+d

![](Q3.png)

## Q.4

Display the return code (or signal) of the previous command in the prompt :

![](Q4.png)

## Q.5

Measurement of the command execution time using the call clock_gettime :

![](Q5_1.png)
![](Q5_2.png)

## Q.6

Execution of a complex command (with arguments)

I did question 6, 7 and 8 with the bin/sh file it works but we need a version with strtok
![](Q6v1.png)
![](Q6.png)

## Q.7

Management of redirections to stdin and stdout with ’<’ and ’>’

We have now a version with strtok

![](Q7.png)
