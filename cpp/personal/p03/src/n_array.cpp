// [WIP]
#include <iostream>

namespace MyArray {
class Int;

class Array {
  friend Int;

  const int dim_;  // 몇 차원 배열 인지
  int* size_;  // size[0] * size[1] * ... * size[dim - 1] 짜리 배열이다.

  struct Address {
    int level_;
    // 맨 마지막 레벨(dim - 1 레벨) 은 데이터 배열을 가리키고, 그 위 상위
    // 레벨에서는 다음 Address 배열을 가리킨다.
    void* next_;
  };

  Address* top_;

 public:
  class Iterator {
    int* location_;
    Array* array_;

    friend Int;

   public:
    Iterator(Array* arr, int* loc = NULL) : array_(arr) {
      location_ = new int[arr->dim_];
      for (int i = 0; i != arr->dim_; i++)
        location_[i] = (loc != NULL ? loc[i] : 0);
    }
    Iterator(const Iterator& itr) : array_(itr.array_) {
      location_ = new int[array_->dim_];
      for (int i = 0; i != array_->dim_; i++)
        location_[i] = itr.location_[i];
    }
    ~Iterator() { delete[] location_; }
    // 다음 원소를 가리키게 된다.
    Iterator& operator++() {
      if (location_[0] >= array_->size_[0])
        return (*this);

      bool carry = false;  // 받아 올림이 있는지
      int i = array_->dim_ - 1;
      do {
        // 어차피 다시 돌아온다는 것은 carry 가 true
        // 라는 의미 이므로 ++ 을 해야 한다.
        location_[i]++;
        if (location_[i] >= array_->size_[i] && i >= 1) {
          // i 가 0 일 경우 0 으로 만들지 않는다 (이러면 begin 과 중복됨)
          location_[i] -= array_->size_[i];
          carry = true;
          i--;
        } else
          carry = false;

      } while (i >= 0 && carry);

      return (*this);
    }
    Iterator& operator=(const Iterator& itr) {
      array_ = itr.array_;
      location_ = new int[itr.array_->dim_];
      for (int i = 0; i != array_->dim_; i++)
        location_[i] = itr.location_[i];

      return (*this);
    }
    Iterator operator++(int) {
      Iterator itr(*this);
      ++(*this);
      return itr;
    }
    bool operator!=(const Iterator& itr) {
      if (itr.array_->dim_ != array_->dim_)
        return true;

      for (int i = 0; i != array_->dim_; i++)
        if (itr.location_[i] != location_[i]) return true;

      return false;
    }
    Int operator*();
  };

  friend Iterator;
  Array(int dim, int* array_size) : dim_(dim) {
    size_ = new int[dim];
    for (int i = 0; i < dim; i++)
      size_[i] = array_size[i];

    top_ = new Address;
    top_->level_ = 0;

    initialize_address(top_);
  }
  Array(const Array& arr) : dim_(arr.dim_) {
    size_ = new int[dim_];
    for (int i = 0; i < dim_; i++)
      size_[i] = arr.size_[i];

    top_ = new Address;
    top_->level_ = 0;

    initialize_address(top_);
    // 내용물 복사
    copy_address(top_, arr.top_);
  }

  void copy_address(Address* dst, Address* src) {
    if (dst->level_ == dim_ - 1) {
      for (int i = 0; i < size_[dst->level_]; ++i)
        static_cast<int*>(dst->next_)[i] = static_cast<int*>(src->next_)[i];
      return;
    }
    for (int i = 0; i != size_[dst->level_]; i++) {
      Address* new_dst = static_cast<Address*>(dst->next_) + i;
      Address* new_src = static_cast<Address*>(src->next_) + i;
      copy_address(new_dst, new_src);
    }
  }

  // address 를 초기화 하는 함수이다. 재귀 호출로 구성되어 있다.
  void initialize_address(Address* current) {
    if (!current)
      return;
    if (current->level_ == dim_ - 1) {
      current->next_ = new int[size_[current->level_]];
      return;
    }
    current->next_ = new Address[size_[current->level_]];
    for (int i = 0; i != size_[current->level_]; i++) {
      (static_cast<Address*>(current->next_) + i)->level_ = current->level_ + 1;
      initialize_address(static_cast<Address*>(current->next_) + i);
    }
  }
  void delete_address(Address* current) {
    if (!current)
      return;
    for (int i = 0; current->level_ < dim_ - 1 && i < size_[current->level_]; i++) {
      delete_address(static_cast<Address*>(current->next_) + i);
    }

    if (current->level_ == dim_ - 1) {
      delete[] static_cast<int*>(current->next_);
      return; // return need to be added, otherwise error.  
    }
    delete[] static_cast<Address*>(current->next_);
  }
  Int operator[](const int index);
  ~Array() {
    delete_address(top_);
    delete[] size_;
  }

  Iterator begin() {
    int* arr = new int[dim_];
    for (int i = 0; i != dim_; i++)
      arr[i] = 0;

    Iterator temp(this, arr);
    delete[] arr;

    return temp;
  }
  Iterator end() {
    int* arr = new int[dim_];
    arr[0] = size_[0];
    for (int i = 1; i < dim_; i++)
      arr[i] = 0;

    Iterator temp(this, arr);
    delete[] arr;

    return temp;
  }
};
class Int {
  void* data;

  int level;
  Array* array;

 public:
  Int(int index, int _level = 0, void* _data = NULL, Array* _array = NULL)
      : level(_level), data(_data), array(_array) {
    if (_level < 1 || index >= array->size_[_level - 1]) {
      data = NULL;
      return;
    }
    if (level == array->dim_) {
      // 이제 data 에 우리의 int 자료형을 저장하도록 해야 한다.
      data = static_cast<void*>((
          static_cast<int*>(static_cast<Array::Address*>(data)->next_) + index));
    } else {
      // 그렇지 않을 경우 data 에 그냥 다음 addr 을 넣어준다.
      data = static_cast<void*>(static_cast<Array::Address*>(
                                    static_cast<Array::Address*>(data)->next_) +
                                index);
    }
  };

  Int(const Int& i) : data(i.data), level(i.level), array(i.array) {}

  operator int() {
    if (data)
      return *static_cast<int*>(data);
    return 0;
  }
  Int& operator=(const int& a) {
    if (data)
      *static_cast<int*>(data) = a;
    return *this;
  }

  Int operator[](const int index) {
    if (!data)
      return 0;
    return Int(index, level + 1, data, array);
  }
};
Int Array::operator[](const int index) {
  return Int(index, 1, static_cast<void*>(top_), this);
}
Int Array::Iterator::operator*() {
  Int start = array_->operator[](location_[0]);
  for (int i = 1; i <= array_->dim_ - 1; i++) {
    start = start.operator[](location_[i]);
  }
  return start;
}
}  // namespace MyArray
int main() {
  int size[] = {2, 3, 4};
  MyArray::Array arr(3, size);

  MyArray::Array::Iterator itr = arr.begin();
  for (int i = 0; itr != arr.end(); itr++, i++) 
    *itr = i;
  for (itr = arr.begin(); itr != arr.end(); itr++)
    std::cout << *itr << std::endl;

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 4; k++)
        arr[i][j][k] = (i + 1) * (j + 1) * (k + 1) + arr[i][j][k];
    }
  }
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 4; k++) {
        std::cout << i << " " << j << " " << k << " " << arr[i][j][k]
                  << std::endl;
      }
    }
  }

  return 0;
}
