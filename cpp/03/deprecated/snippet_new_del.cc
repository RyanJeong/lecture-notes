void Foo1() {
#ifdef CPP_03_NOBUILD
  int* p = new int;  // Dynamically allocate an integer
  p = new int;       // Memory leak! The previous memory is lost
                     // The heap object we allocated previously is still there,
                     // but we have no way to access it anymore

#endif  // CPP_03_NOBUILD
}

void Foo2() {
#ifdef CPP_03_NOBUILD
  int* p = new int;  // Dynamically allocate an integer
  delete p;          // Free the dynamically allocated memory
  delete p;          // UB: double deletion of the same memory
#endif               // CPP_03_NOBUILD
}

void Foo3() {
#ifdef CPP_03_NOBUILD
  int* p = new int;  // Dynamically allocate an integer
  delete p;          // Free the dynamically allocated memory
  *p = 100;          // UB: dangling pointer dereferencing
#endif               // CPP_03_NOBUILD
}

void Foo4() {
#ifdef CPP_03_NOBUILD
  int x = 10;
  delete &x;  // UB: trying to delete a stack object
#endif        // CPP_03_NOBUILD
}

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
