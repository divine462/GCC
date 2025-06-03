#include <stdio.h>

int main() {
  /* TODO: define the grades variable here */
  int average;
    int grades[3] = {80,85,90};
  grades[0] = 80;
  
  /* TODO: define the missing grade
     so that the average will sum to 85. */
  grades[1] = 85; 
  /*take (80+X+90):3 = 85 then determine the value of x*/
  grades[2] = 90;

  average = (grades[0] + grades[1] + grades[2]) / 3;
  printf("The average of the 3 grades is: %d", average);

  return 0;
}
