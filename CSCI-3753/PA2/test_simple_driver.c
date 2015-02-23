#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char * argv[]) {
  char cmd;
  char buf[1024];
  int fd;

  printf("Press r to read from device\n");
  printf("Press w to write to device\n");
  printf("Press e to exit the device\n");
  printf("Press anything else to keep reading or writing from the device\n");
  printf("Enter command: ");

  while (1)
  {
    scanf(" %[^\n]", &cmd);
    if (cmd == 'r')
    {
      printf("Data read from device: \n");
      fflush(stdout);
      system("cat /dev/simple_character_device");
      printf("\n");
    }
    else if (cmd == 'w')
    {
      fd = open("/dev/simple_character_device", O_RDWR);
      printf("Enter data you want to write to the device: \n");
      scanf(" %[^\n]", buf);
      write(fd, buf, strlen(buf));
      close(fd);
    }
    else if (cmd == 'e')
      break;
    else if (cmd == '\n')
    {
      //do nothing in the case of newline
    }
    else
    {
      printf("Press r to read from device\n");
      printf("Press w to write to device\n");
      printf("Press e to exit the device\n");
      printf("Press anything else to keep reading or writing from the device\n");
      printf("Enter command: ");
    }     
  }

  return 0;
  
}
