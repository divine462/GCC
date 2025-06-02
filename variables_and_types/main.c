#include <stdio.h>

int main() {
  int a = 3;
  float b = 4.5;
  double c = 5.25;
  float sum;

  /* Your code goes here */

    /*help to convert int (%d) and float (%f) and the number 2 beforef that allow only 2 nbr after the comma */
  sum = a + b + c;
  printf("The sum of a, b, and c is %.2f", sum);
  return 0;
}
