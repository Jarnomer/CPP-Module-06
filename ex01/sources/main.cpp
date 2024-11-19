#include <iostream>

#include <Data.hpp>
#include <Serializer.hpp>

int main(void) {
  Data data = {42, "Example"};

  uintptr_t raw = Serializer::serialize(&data);
  Data *ptr = Serializer::deserialize(raw);

  std::cout << "Serialized value: " << raw << "\n";

  std::cout << "Deserialized Data: value = " << ptr->value
            << ", name = " << ptr->str << "\n";

  if (ptr == &data) {
    std::cout << "Pointers match!\n";
  } else {
    std::cout << "Pointers don't match!\n";
  }
  return 0;
}
