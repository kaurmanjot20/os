#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include<string.h>

int main() {
int ret_val;
int fd[2];
char buff[32];
char string1[10];

ret_val = pipe(fd);                 /* Create pipe */
if (ret_val != 0) {             /* Test for success */
  printf("Unable to create a pipe; errno=%d\n",errno);

  exit(1);                         /* Print error message and exit */
}

printf("enter data \n");
   fgets(string1,10,stdin);
if (fork() == 0) {
   /* child program */
   close(fd[0]); /* close the read end */
   
   ret_val = write(fd[1],string1,strlen(string1)); /*Write to pipe*/
   if (ret_val != strlen(string1)) {
      printf("Write did not return expected value\n");
      exit(2);                       /* Print error message and exit */
   }
}
else {
   /* parent program */
   close(fd[1]); /* close the write end of pipe */
   ret_val = read(fd[0],buff,strlen(string1)); /* Read from pipe */
   if (ret_val != strlen(string1)) {
      printf("Read did not return expected value\n");
      exit(3);                       /* Print error message and exit */
   }
   printf("parent read %s from the child program\n",buff);
}
exit(0);
}
