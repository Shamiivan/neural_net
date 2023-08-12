//# define NDEBUG // uncomment you want to nullfiy assert at compile time 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

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

double matrix_dot_product(Matrix *m1, Matrix *m2){
  assert (m1->size == m2->size); 
  
  int size = m1->size;
  double res;
  for (int i = 0; i < size; i++) {
    res += m1->data[i] * m2->data[i];
    printf("%f", res);
  }
  return res;
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


//returns -1 if filling the dataset fails and 1 if succefull
int populate_dataset(Matrix *dataset) {
  int rows = dataset->n_rows;
  int cols = dataset->n_cols;

  const char *filepath = "./dataset/train.csv";

  FILE *file = fopen(filepath, "r");
  if (file == NULL) {
    printf("Failed to open file\n");
    return -1;
  }

  char line[1000];
  char *token;

  for (size_t i = 0; i < rows; i++) {
    fgets(line, 1000, file);
    for (size_t j = 0; j < cols; j++) {
      double item = strtod(&line[j], NULL);
      matrix_add_item(dataset, i, j, item);
    }
  }

  fclose(file);
  return 1;
}

int main(int argc, char *argv[]) {
  const char *filepath = "./dataset/train.csv";
  // get #rows
  int rows = csv_file_get_num_rows(filepath);
  // get # cols 
  int cols = csv_file_get_num_cols(filepath);

  printf("The number of cols is : %d", cols);


  // 1D Array
  Matrix mat1 = matrix_create(1, cols);
  Matrix dataset = matrix_create(rows, cols);

  if (populate_dataset(&dataset) == 1) {

    printf("\nMatrix population done\n");
  }

  matrix_destroy(&dataset);
  matrix_destroy(&mat1);

  //test dot product 
  double arr1[3] = {0.5, 0.3, 0.2};
  double arr2[3] = {0.4, 0.7, 0.2};

  Matrix m3 = matrix_create(1,3);
  Matrix m4 = matrix_create(1,3);

  for (int j = 0; j <= 3; j++) {
    matrix_add_item(&m3, 1, j, arr1[j]);
    matrix_add_item(&m4, 1, j, arr2[j]);
  }

  matrix_display(&m3);
  matrix_display(&m4);
  double dot_product = matrix_dot_product(&m3, &m4);
  printf("The dot product is  : %f ", dot_product);
  
  return EXIT_SUCCESS;
}
