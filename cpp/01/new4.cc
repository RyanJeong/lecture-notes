int main() {
  int rows = 3, cols = 4;

  // Allocate array of pointers
  int** matrix = new int*[rows];
  // Allocate each row
  for (int i = 0; i < rows; ++i) matrix[i] = new int[cols];

  // Do something with the matrix at here
  for (int i = 0; i < rows; ++i)
    for (int j = 0; j < cols; ++j) matrix[i][j] = i * cols + j;

  // Deallocate each row first
  for (int i = 0; i < rows; ++i) delete[] matrix[i];
  // Then deallocate pointer array
  delete[] matrix;
  return 0;
}