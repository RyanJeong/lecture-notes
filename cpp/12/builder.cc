#include <iostream>
#include <memory>  // for std::unique_ptr, std::make_unique
#include <string>
#include <utility>  // for std::move

enum class OsType {
  kIos,
  kAndroid
};

class Smartphone {
 public:
  void SetOS(OsType os);
  void SetModelName(const std::string& name);
  void ShowSpec() const;

 private:
  OsType os_;
  std::string model_name_;
};

void Smartphone::SetOS(OsType os) { os_ = os; }

void Smartphone::SetModelName(const std::string& name) { model_name_ = name; }

void Smartphone::ShowSpec() const {
  std::cout << "Smartphone [Model: " << model_name_
            << ", OS: " << ((os_ == OsType::kIos) ? "iOS" : "Android") << "]"
            << std::endl;
}

class SmartphoneBuilder {
 public:
  SmartphoneBuilder() : product_(std::make_unique<Smartphone>()) {}

  SmartphoneBuilder& SetOS(OsType os);
  SmartphoneBuilder& SetModelName(const std::string& name);
  std::unique_ptr<Smartphone> Build();

 private:
  std::unique_ptr<Smartphone> product_;
};

SmartphoneBuilder& SmartphoneBuilder::SetOS(OsType os) {
  product_->SetOS(os);
  return *this;
}

SmartphoneBuilder& SmartphoneBuilder::SetModelName(const std::string& name) {
  product_->SetModelName(name);
  return *this;
}

std::unique_ptr<Smartphone> SmartphoneBuilder::Build() {
  return std::move(product_);
}

int main() {
  SmartphoneBuilder builder;

  std::unique_ptr<Smartphone> my_phone =
      builder.SetOS(OsType::kIos).SetModelName("iPhone 16").Build();

  if (my_phone) my_phone->ShowSpec();
  return 0;
}
