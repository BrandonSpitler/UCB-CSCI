#include <stdio.h>
#include <sys/syscall.h>

int main(int argc, char * argv[]) {
  int num1 = 214;
  int num2 = 19;
  int dummy;
  int* result = &dummy;

  syscall(319, num1, num2, result);

  printf("The result is %d\n", *result);
}
