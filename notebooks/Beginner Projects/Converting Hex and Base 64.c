#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/* Returns the number of digits that exist in the binary equivalent of the integer */
static int getDigitsFromBinaryInteger(unsigned long long integer){
  return (int) log2(integer) +1;
}

/* Converts an integer into base 64 */
static char convertIntToBase64(int integer){
  if (integer >= 0 && integer < 26){
    return (char) ('A' + (char) integer);
  } else if (integer >= 26 && integer < 52){
    return (char) ('a' + (char) integer - (char) 26);
  } else if (integer >=52 && integer < 62){
    return (char) ('0' + (char) integer - (char) 52);
  } else if (integer == 62) {
    return '+';
  } else if (integer == 63) {
    return '/';
  } else {
    return '-';
  }
}

/* Converts an integer to a Base 64 string */
static char *convertHexToBase64(unsigned long long input_int){
  int digits = getDigitsFromBinaryInteger(input_int);
  char *answer = malloc(sizeof(char)*((int) digits/7) +2);
  if (!answer){
    printf("Failed memory allocation");
    return 0;
  }
  char *stringPtr = answer;
  int shiftValue;
  unsigned long long initialMask;
  if (digits %4 ==0){
    shiftValue = digits - 6;
  } else {
    shiftValue = digits - 5;
  }

  initialMask = 0x3f << (shiftValue -1);
  while (shiftValue >0){
    *stringPtr = (char) convertIntToBase64((input_int & initialMask)>>shiftValue);
    stringPtr ++;
    shiftValue = shiftValue -6;
    initialMask = 0x3f << (shiftValue);
  }
  *stringPtr = (char) convertIntToBase64(input_int & initialMask);
  return answer;
}

/* Converts the hex value into a string */
int main(int argc, char *argv[]) {
  if (argc > 1){
    printf("Program failed, enter a single argument. \n");
    return 0;
  }
  unsigned long long input_val = 0x49276dd;
  char * result = convertHexToBase64(input_val);
  printf("%s", result);
  free (result);
}
