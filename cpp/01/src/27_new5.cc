int main() {
  int rows = 3, cols = 4;

  // Step 1: Allocate single contiguous 1D array
  int* data = new int[rows * cols];
  // Step 2: Allocate array of pointers (row pointers)
  int** matrix = new int*[rows];
  // Step 3: Set each row pointer to point to correct offset in data array
  for (int i = 0; i < rows; ++i)
    matrix[i] = data + (i * cols);  // Point to start of each row

  // Do something with the matrix here
  for (int i = 0; i < rows; ++i)
    for (int j = 0; j < cols; ++j) matrix[i][j] = i * cols + j;

  // Deallocation: reverse order
  delete[] matrix;  // Delete pointer array first
  delete[] data;    // Then delete data array
  return 0;
}
