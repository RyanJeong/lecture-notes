#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
void AllocateMatrixFixedRows(int col_nums) {  // col_nums is unspecified
  int* matrix[4];                             // row_nums is fixed to 4

  // Approach 1: allocate each row separately
  for (int i = 0; i < 4; ++i) matrix[i] = new int[col_nums];
  for (int i = 0; i < 4; ++i)  // manipulate the matrix
    for (int j = 0; j < col_nums; ++j) matrix[i][j] = i * col_nums + j;
  for (int i = 0; i < 4; ++i) delete[] matrix[i];

  // Approach 2: allocate a single block for all rows
  // Note: It could be failed to allocate memory if `i * col_nums` is too large.
  int* data = new int[4 * col_nums];
  for (int i = 0; i < 4; ++i) matrix[i] = &data[i * col_nums];
  for (int i = 0; i < 4; ++i)  // manipulate the matrix
    for (int j = 0; j < col_nums; ++j) matrix[i][j] = i * col_nums + j;
  delete[] data;
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
void AllocateMatrix(int col_nums, int row_nums) {
  int** matrix = new int*[row_nums];  // allocate an array of int*

  // Approach 1: allocate each row separately
  for (int i = 0; i < row_nums; ++i) matrix[i] = new int[col_nums];
  for (int i = 0; i < row_nums; ++i)  // manipulate the matrix
    for (int j = 0; j < col_nums; ++j) matrix[i][j] = i * col_nums + j;
  for (int i = 0; i < row_nums; ++i) delete[] matrix[i];

  // Approach 2: allocate a single block for all rows
  // Note: It could be failed to allocate memory if `i * col_nums` is too large.
  int* data = new int[row_nums * col_nums];
  for (int i = 0; i < row_nums; ++i) matrix[i] = &data[i * col_nums];
  for (int i = 0; i < row_nums; ++i)  // manipulate the matrix
    for (int j = 0; j < col_nums; ++j) matrix[i][j] = i * col_nums + j;
  delete[] data;

  delete[] matrix;
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
