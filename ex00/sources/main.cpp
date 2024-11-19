#include <ScalarConverter.hpp>

void runInvalidTests(void) {
  std::string invalid[] = {"abc", "123.f", "123f", "1.ab", "1.f0",
                           "-0f", "-0.f",  "999.", ".837"};
  std::cout << "Invalid tests\n";
  std::cout << "========================\n\n";
  for (const auto &input : invalid) {
    ScalarConverter::convert(input);
  }
  std::cout << "========================\n";
}

void runValidTests(void) {
  std::cout << "\n";
  std::cout << "Valid tests\n";
  std::cout << "========================\n\n";
  std::string valid[] = {"+", "-115", "1234567890000.34f", "10.00", "nan"};
  for (const auto &input : valid) {
    ScalarConverter::convert(input);
  }
  std::cout << "========================\n";
}

int main(int ac, char **av) {
  if (ac == 2) {
    ScalarConverter::convert(av[1]);
  } else {
    std::cout << "Usage: ./convert <value>\n";
    // runInvalidTests(); // uncomment for tests
    // runValidTests(); // uncomment for tests
  }
  return 0;
}
