#include <stdio.h>
#include <stdlib.h>
#include<string.h>

typedef struct Matrix {
  int n_rows;
  int n_cols;
  int size;
  int stride;
  double *data;
} Matrix;

Matrix matrix_create(int rows, int cols) {
  Matrix matrix;
  matrix.n_rows = rows;
  matrix.n_cols = cols;
  matrix.size = rows * cols;
  matrix.stride = 0;
  matrix.data = (double *)malloc(matrix.size * sizeof(double));
  return matrix;
}

void matrix_destroy(Matrix *matrix) {
  matrix->n_rows = 0;
  matrix->n_cols = 0;
  matrix->size = 0;
  free(matrix->data);
}

void matrix_add_item(Matrix *matrix, int i, int j, double item) {
  int index = i * matrix->n_cols + j;
  matrix->data[index] = item;
}
double matrix_get_item(Matrix *matrix, int i, int j) {
  int index = i * matrix->n_cols + j;
  return matrix->data[index];
}

void matrix_display(Matrix *matrix) {
  printf("Displaying matrix\n");
  int count = 0;
  for (size_t i = 0; i < matrix->n_rows; i++) {
    for (size_t j = 0; j < matrix->n_cols; j++) {
      double item = matrix_get_item(matrix, i, j);
      count++;
      printf(" %f", item);
    }
    printf("\n");
  }
  printf("\nCount : %d", count);
}


int csv_file_get_num_rows(const char *filepath) {
  int MAX_LINE_LENGTH = 10000;
  FILE *file = fopen(filepath, "r");
  if (file == NULL) {
    printf("Failed to open the file.\n");
    return -1;
  }
  int row_count = 0;
  char line[MAX_LINE_LENGTH];
  while (fgets(line, sizeof(line), file) != NULL) {
    row_count++;
  }
  fclose(file);
  return row_count;
}
int csv_file_get_num_cols(const char *filepath) {
  int MAX_LINE_LENGTH = 10000;
  FILE *file = fopen(filepath, "r");
  if (file == NULL) {
    printf("Failed to open file.\n");
    return -1;
  }

  int col_count = 0;
  char line[MAX_LINE_LENGTH];
  fgets(line, sizeof(line), file);
  fgets(line, sizeof(line), file);
  fgets(line, sizeof(line), file);
  fgets(line, sizeof(line), file);

  char *token = strtok(line, ",");
  while (token != NULL) {
    col_count++;
    token = strtok(NULL, ",");
  }
  fclose(file);
  return col_count;
}

int main(int argc, char *argv[]) {

  double arr1[][2] = {{10.4, 2.43}, {3.43, 4}};
  double arr2[][2] = {{4.3, 2}, {3, 4.32}};


 
  
  const char *filepath = "./dataset/train.csv";
  int rows =  csv_file_get_num_rows(filepath);
  int cols  = csv_file_get_num_cols(filepath);

  printf("The number of cols is : %d", cols);

  Matrix mat1 = matrix_create(1, cols);
  Matrix mat2 = matrix_create(28, 28);

  
  FILE *file = fopen(filepath, "r");
  if (file == NULL) {
    printf("Failed to open file\n");
    return 1;
  }

  char line[1000];
  char *token;
  fgets(line, sizeof(line), file);
  
  // populate matrix
  for(int j = 0; j< cols; j++){
      double n = strtod(&line[j],NULL);
     matrix_add_item(&mat1, 0, j,n);
   }
  printf("\nDisplaying matrix \n");
  matrix_display(&mat1);

  printf("Hello, World\n");
  return EXIT_SUCCESS;
}
