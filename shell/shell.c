/*
Created By:  Denizcan BAG
Stephen Brennan's tutorails were really helpful. I accuried some of the ideas from his licanced work from github. I didn't commited
plagiarism or any kind. All of the methods below are implemented by myself. I just wanted to give credit to Stephan Brennan for his work.
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
This function executes and tokenize the string that we gave it.
It returns integer for main loop.(For now it only returns 1).
*/
int executeThreaded(char *string) {
  pid_t pid;
  int statusOfChild;

  //Vars for token function.
  int quitCheck = 0;                                                                      //This var turns 1 when it sees quit function.
  const char s[2] = ";";
  char *token;
  token = strtok(string, s);                                                              //Get the first token if exist then loop through all tokens.
  while (token != NULL) {
    if (strcmp(token, "quit") == 0) {
      quitCheck = 1;
    } else {
      pid = fork();                                                                       //Forking the system call to make process run similtanuisly.
      if (pid == 0) {                                                                     //If true our child process executed sucessfuly.
        if (system(token) == -1) {
          perror("pirateShell :( ");
        }
        exit(1);
      } else if (pid < 0) {                                                               // If true error occured during forking process as our pid is negative.
        perror("pirateShell :( ");
      } else {                                                                            //Waiting for process to finish. This information gethered from Internet as I didnt know how to wait for process to finish.
        do {
          waitpid(pid, &statusOfChild, 0);                                                //Gets the status of the pid and prints it to the statusOfChild var.
        } while (!WIFEXITED(statusOfChild) && !WIFSIGNALED(statusOfChild));               //While process not finished wait.
      }
    }                                                                                     //If we dont strtoken again garbages comes along so we clear the buffer.
    token = strtok(NULL, s);
  }
  if (!quitCheck)
    return 1;                                                                             //If quitCheck var is 0 we should return to the mainLoop.
  printf("Arrgh!, see ya chum!\n");
  return 0;                                                                               //If quitCheck var is 1 that means quit command issued.We should exit the program.
}

/*
Hello fellow pirate. this function here checks wether the given
string parameter is exit parameter or needs to be handled by parent process.
If the given string is not important for parent process our dear friend executeTreated function takes care of the rest.
For further explanation check the executeTread comments.
*/
int pirateCheck(char *string) {
  char *tester;
  char *token;
  const char s[2] = " ";
  if (string == NULL) {
    // An empty command was entered.
    return 1;
  }
  if (strcmp(string, "quit") == 0) {
    printf("Arrgh!, see ya chum!\n");
    return 0;
  }
  tester = strstr(string, ";");                                                            //If there is ; char that means we need thread so we call executeThreaded.
  if (tester != NULL) {
    return executeThreaded(string);
  }
  tester = strstr(string, "cd");
  if (tester != NULL) {
    token = strtok(string, s);
    token = strtok(NULL, s);
    if (chdir(token) != 0) {
      perror("pirateShell :( ");
    }
  } else if (system(string) == -1) {                                                       //If we are here then we didn't need to call child process so the parent process handles it.
    perror("pirateShell :(");
  }
  return 1;
}

/*
Arrrr, I am the pirate that take cares of the system input.
I read users input one by one and collect them into buffer then send it to my papa the main function down below.
I also dynamically allocate the memory so no one can sink this ship with heavy loads.
*/
char *pirateReadLine(void) {
  int bufferSize = 512;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufferSize);
  int c;

  if (!buffer) {
    fprintf(stderr, "pirateShell: allocation error\n");
    exit(1);
  }

  while (1) {
    // Read a character
    c = getchar();

    if (c == EOF) {
      exit(1);
    } else if (c == '\n') {
      buffer[position] = '\0';
      return buffer;
    } else {
      buffer[position] = c;
    }
    position++;

    // If we have exceeded the buffer, reallocate.
    if (position >= bufferSize) {
      bufferSize += 1024;
      buffer = realloc(buffer, bufferSize);
      if (!buffer) {
        fprintf(stderr, "pirateShell: allocation error\n");
        exit(1);
      }
    }
  }
}

/*Ayo matey i am the captains right hand.
When main function fires up i am the one who he calls first.
Also i get information from my fellow functions and send it to another one.
If they say this ship is sinking (when they return 0) I end my loop then captain (main function) decide what to do next.
For now he is only terminating the process. What a lazy chum.
*/
void programLoop(void) {
  char *line;
  int status;

  do {
    printf("pirateShell> ");
    line = pirateReadLine();
    status = pirateCheck(line);

    free(line);
  } while (status);
}

void batchPirate(char *string) {
  FILE *fp;
  char str[256];
  char* filename = string;
  int status = 1;

  fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("Could not open file %s", filename);
    return 1;
  }
  while (fgets(str, 257, fp) != EOF && status != 0 && !feof(fp)) {
    str[strcspn(str, "\n\r")] = 0;
    //str[strcspn(str, "\r")] = 0;
    printf("------------------------\nCommand Issued: %s\n", str);
    status = pirateCheck(str);
  }
  fclose(fp);

  return 0;
}

/*
I am the main function that all other function.
I am a bit lazy I just call my fellow function friend programLoop.
Hahahaha he does most of the dirty job.
I dont even free up the memory because on every loop of the programLoop he clears everything.
I think he has cleaning obsession but never the less works for me.
*/
int main(int argc, char **argv) {
  printf("------------\nAhoy, matey!\n------------\n");
  if (argc > 1) {
    batchPirate(argv[1]);
    return 0;
  }
  // Run command loop.
  programLoop();
  return 0;
}
