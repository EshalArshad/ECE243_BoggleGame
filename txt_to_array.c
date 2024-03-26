#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ELEMENTS 10000     // Maximum number of strings
#define MAX_STRING_LENGTH 100  // Maximum length of each string

int main(void) {
  FILE *file = fopen("english_words.txt", "r");
  if (file == NULL) {
    printf("Error opening file.\n");
    return 1;
  }

  char array[MAX_ELEMENTS][MAX_STRING_LENGTH];
  int count = 0;

  // Read file contents into array
  while (fgets(array[count], MAX_STRING_LENGTH, file)) {
    // Remove newline character read by fgets, if present
    if (array[count][strlen(array[count]) - 1] == '\n') {
      array[count][strlen(array[count]) - 1] = '\0';
    }
    count++;
    if (count >= MAX_ELEMENTS) break;
  }

  fclose(file);

  // Print the C code for the array declaration and initialization
  printf("char *array[%d] = {\n", count);
  for (int i = 0; i < count; i++) {
    printf("    \"%s\"", array[i]);
    if (i < count - 1) printf(",\n");
  }
  printf("\n};\n");

  return 0;
}
