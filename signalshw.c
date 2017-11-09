#include <stdio.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

void sighandler(int signo){
  int fd;
  char* start = "Program excited due to SIGINT\n";
  if (signo == SIGINT){
    fd = open("things", O_CREAT| O_WRONLY | O_APPEND );
    printf("%s\n", start);
    write(fd,&start, sizeof(start));
    close(fd);
    exit(1);
  }
  if (signo == SIGUSR1) {
    printf("PID of Parent:%d\n", getppid());
  }
}

int main(){
  signal(SIGINT, sighandler);
  signal(SIGUSR1, sighandler);
  while(2) {
    printf("PID:%d\n", getpid());
    sleep(1);
  }

}
