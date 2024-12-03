#include <stdio.h>
#include <stdlib.h>

int count_lines(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    return -1;
  }

  int lines = 0;
  char ch;
  while (!feof(file)) {
    ch = fgetc(file);
    if (ch == '\n') {
      lines++;
    }
  }
  fclose(file);

  return lines;
}

int read_file_to_arrays(const char *filename, int *left_array, int *right_array,
                        int size) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    return -1;
  }

  for (int i = 0; i < size; i++) {
    if (fscanf(file, "%d %d", &left_array[i], &right_array[i]) != 2) {
      fclose(file);
      return -2;
    }
  }

  fclose(file);
  return 0;
}

int comp(const void *a, const void *b) { return (*(int *)a - *(int *)b); }

int main(void) {
  const char *filename = "input1.txt";

  int sum = 0;

  int num_lines = count_lines(filename);
  if (num_lines == -1) {
    printf("Error: Could not open file\n");
    return 1;
  }

  int *left_array = (int *)malloc(num_lines * sizeof(int));
  int *right_array = (int *)malloc(num_lines * sizeof(int));

  if (!left_array || !right_array) {
    printf("Error: Memory allocation failed\n");
    free(left_array);
    free(right_array);
    return 1;
  }

  int result =
      read_file_to_arrays(filename, left_array, right_array, num_lines);
  if (result == -1) {
    printf("Error: Could not open file\n");
  } else if (result == -2) {
    printf("Error: Invalid file format\n");
  } else {
    qsort(left_array, num_lines, sizeof(left_array[0]), comp);
    qsort(right_array, num_lines, sizeof(right_array[0]), comp);
    // printf("Left array:  ");
    // for (int i = 0; i < num_lines; i++) {
    //   printf("%d ", left_array[i]);
    // }
    // printf("\nRight array: ");
    // for (int i = 0; i < num_lines; i++) {
    //   printf("%d ", right_array[i]);
    // }
    // printf("\n");

    for (int i = 0; i < num_lines; i++) {
      int diferrence = left_array[i] - right_array[i];
      sum += abs(diferrence);
    }

    printf("%d\n", sum);
  }
  return 0;
}
