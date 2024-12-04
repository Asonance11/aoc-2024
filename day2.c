#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int *numbers;
  int size;
} NumberArray;

int count_numbers_in_line(char *line) {
  int count = 0;
  char *token = strtok(line, " ");
  while (token != NULL) {
    count++;
    token = strtok(NULL, " ");
  }
  return count;
}

NumberArray *process_line(char *line) {
  NumberArray *result = malloc(sizeof(NumberArray));

  char *line_copy = strdup(line);
  result->size = count_numbers_in_line(line_copy);
  free(line_copy);

  result->numbers = malloc(result->size * sizeof(int));

  char *token = strtok(line, " ");
  int i = 0;
  while (token != NULL && i < result->size) {
    result->numbers[i] = atoi(token);
    token = strtok(NULL, " ");
    i++;
  }

  return result;
}

void process_file(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    printf("Error opening file\n");
    return;
  }

  char line[1024];

  int safeReport = 0;
  while (fgets(line, sizeof(line), file)) {
    line[strcspn(line, "\n")] = 0;

    NumberArray *arr = process_line(line);

    bool ok = true;
    bool only_increasing = true;
    bool only_decreasing = true;

    for (int i = 0; i < arr->size - 1; i++) {
      int diff = arr->numbers[i + 1] - arr->numbers[i];

      if (diff == 0) {
        ok = false;
        break;
      }

      if (diff > 0) {
        only_decreasing = false;
      }
      if (diff < 0) {
        only_increasing = false;
      }

      if (abs(diff) < 1 || abs(diff) > 3) {
        ok = false;
        break;
      }
    }

    if (ok && (only_decreasing || only_increasing)) {
      safeReport++;
    }

    free(arr->numbers);
    free(arr);
  }
  printf("%d \n", safeReport);

  fclose(file);
}

int main() {
  process_file("input2.txt");
  return 0;
}
