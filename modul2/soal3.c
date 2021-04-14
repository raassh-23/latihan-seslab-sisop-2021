#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

int main() {
  pid_t pid, sid;        // Variabel untuk menyimpan PID

  pid = fork();     // Menyimpan PID dari Child Process

  /* Keluar saat fork gagal
  * (nilai variabel pid < 0) */
  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  /* Keluar saat fork berhasil
  * (nilai variabel pid adalah PID dari child process) */
  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  int no=1;
  char *sourcePath = "/home/rauf/modul2/error.txt";
  char destPath[50];

  while (1) {
    FILE *source;
    FILE *dest;

    sprintf(destPath, "%s%d", "/home/rauf/modul2/error.log.", no);

    source = fopen(sourcePath, "r");
    dest = fopen(destPath, "w");
    
    char ch = fgetc(source);
    while (ch != EOF)
    {
        fputc(ch, dest);

        ch = fgetc(source);
    }

    fclose(freopen(sourcePath, "w", source));
    fclose(dest);
    no++;

    sleep(10);
  }
}