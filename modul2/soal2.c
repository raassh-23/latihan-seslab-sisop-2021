#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <time.h>
#include <stdio.h>

int main() {
  pid_t child_id;
  int status;

  child_id = fork();

  if (child_id < 0) {
    exit(EXIT_FAILURE);
  }

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char date[20];
    sprintf(date, "%02d-%02d-%d_%02d:%02d:%02d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);

  if (child_id == 0) {
    char *argv[] = {"mkdir", date, NULL};
    execv("/bin/mkdir", argv);
  } else {
    while ((wait(&status)) > 0);
    
    char *argv[] = {"cp", "-r", "/home/rauf/Downloads/", date, NULL};
    execv("/usr/bin/cp", argv);
    printf("sudah selesai\n");
  }
}