template <typename T>
class TemplateBase {
  T value_;

 public:
  explicit TemplateBase(T val) : value_(val) {}
};

template <typename T>
class TemplateDerived : public TemplateBase<T> {
  T value_;

 public:
  explicit TemplateDerived(T val) : TemplateBase<T>(0), value_(val) {}
};

int main() {
  TemplateDerived<int> obj(42);
  return 0;
}
