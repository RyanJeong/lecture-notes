#pragma once

template <typename T>
T Smaller(const T& op1, const T& op2) {
  return op1 < op2 ? op1 : op2;
}
