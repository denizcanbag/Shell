# Shell
This shell program crated with C language for OS project. It is writtten for linux based kernel so it wont work on Windows.
Shell.c has two main usage. One is interactive mod and the other one is batch mode(just like windows .bat file).
To us it in interactive mod you can download the compiled shell or you may compile the shell.c file on you own preferably using
gcc compiler. Just executing the compiled file opens the program in interactive mode.
To use the shell in batch mode all you have to do is giving the filepath to the program at execution(start up).

Example1: ./shell ~~ Open in interactive mode.

Example2: ./shell [pathToBatch] ~~ Open program in batch mode.



PS: When reading batch file line by line, if shell sees quit command it will quit.

PS2:While in interactive mode if arguments includes simultaneously running commands(seperated with ';') and sees quit command it will
finish the other child process then kills the parent program.
Example For PS2: ls;quit;ls -a ~~ will issue the commands ls and ls -a simultaneously then quit.

Cd command is working like a charm :) and theme of the shell is pirate.

Ofcourse shell has a known bug unfortunatly :( It is that if you give ; command on batched file it will loop infinitly because of child process not being relaesing the memory on time so fgets couldnt find the EOF(In theory ofc.) So if you are going to use ; command with batch mode please give quit command too in anywhere of the file so execution can stop after the first iteration.
