void Foo1() {
  int score = 92;        // Declaring and initializing score
  int& r_score = score;  // Declaring r_score and binding it to score
}

void Foo2() {
  int score = 92;        // Declaring and initializing score
  int& r_score = score;  // Declaring r_score and binding it to score
  int num = 80;
  r_score = num;  // now, score becomes 80
}

void Foo3() {
#ifdef CPP_03_NOBUILD
  int& x = 92;  // Error: cannot bind non-const lvalue reference to an rvalue

#endif  // CPP_03_NOBUILD
}

void Foo4() {
  int temp = 100;
  int& ref1 = temp;       // lvalue reference to temp
  const int& ref2 = 200;  // rvalue reference to a literal
}
