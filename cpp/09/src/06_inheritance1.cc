class NonTemplateBase {
  int value_;

 public:
  explicit NonTemplateBase(int val) : value_(val) {}
};

template <typename T>
class TemplateDerived : public NonTemplateBase {
  T value_;

 public:
  explicit TemplateDerived(T val) : NonTemplateBase(0), value_(val) {}
};

int main() {
  TemplateDerived<int> obj(42);
  return 0;
}
