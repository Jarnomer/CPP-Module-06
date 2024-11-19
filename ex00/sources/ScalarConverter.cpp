#include <ScalarConverter.hpp>

static void printDouble(double number) {
  std::cout << "double: " << std::fixed << std::setprecision(1)
            << static_cast<double>(number) << "\n";
}

static void printFloat(float number) {
  std::cout << "float: " << std::fixed << std::setprecision(1)
            << static_cast<float>(number) << "f" << "\n";
}

static void printInt(int64_t number) {
  if (number < std::numeric_limits<int>::min() ||
      number > std::numeric_limits<int>::max()) {
    std::cout << "int: Impossible\n";
  } else {
    std::cout << "int: " << static_cast<int>(number) << "\n";
  }
}

static void printChar(int64_t number) {
  if (number < std::numeric_limits<char>::min() ||
      number > std::numeric_limits<char>::max()) {
    std::cout << "char: Impossible\n";
  } else if (!std::isprint(static_cast<char>(number))) {
    std::cout << "char: Non displayable\n";
  } else {
    std::cout << "char: '" << static_cast<char>(number) << "'\n";
  }
}

static void convertDouble(std::string str) {
  double number = std::stod(str);
  printChar(number);
  printInt(number);
  printFloat(number);
  printDouble(number);
}

static void convertFloat(std::string str) {
  float number = std::stof(str);
  printChar(number);
  printInt(number);
  printFloat(number);
  printDouble(number);
}

static void convertInt(std::string str) {
  int number = std::stoi(str);
  printChar(number);
  printInt(number);
  printFloat(number);
  printDouble(number);
}

static void convertChar(char c) {
  printChar(c);
  printInt(c);
  printFloat(c);
  printDouble(c);
}

static bool isInt(std::string str) {
  return (str.find('.') == std::string::npos &&
          str.find('f') == std::string::npos);
}

static bool isDouble(std::string str) {
  return (str.find('.') != std::string::npos);
}

static bool isFloat(std::string str) {
  return (str.find('.') != std::string::npos &&
          str.find('f') != std::string::npos);
}

static bool isNanOrInf(std::string str) {
  return (str == "inf" || str == "-inf" || str == "nan");
}

static bool isNanfOrInff(std::string str) {
  return (str == "inff" || str == "-inff" || str == "nanf");
}

static Type getScalarType(std::string str) {
  std::regex pattern(R"(^[-+]?\d+(\.\d+)?f?$)");
  if (str.length() == 1 && !std::isdigit(str[0])) {
    return Type::Char;
  } else if (!isNanfOrInff(str) && !isNanOrInf(str) &&
             !std::regex_match(str, pattern)) {
    return Type::Invalid;
  } else if (isNanfOrInff(str) || isFloat(str)) {
    return Type::Float;
  } else if (isNanOrInf(str) || isDouble(str)) {
    return Type::Double;
  } else if (isInt(str)) {
    return Type::Int;
  } else {
    return Type::Invalid;
  }
}

void ScalarConverter::convert(std::string input) {
  try {
    std::cout << "Converting: " << input << "\n";
    switch (getScalarType(input)) {
    case Type::Char:
      convertChar(input[0]);
      break;
    case Type::Int:
      convertInt(input);
      break;
    case Type::Float:
      convertFloat(input);
      break;
    case Type::Double:
      convertDouble(input);
      break;
    default:
      throw std::invalid_argument(input);
    }
  } catch (std::invalid_argument &e) {
    std::cerr << "Invalid input: " << e.what() << "\n";
  } catch (std::out_of_range &e) {
    std::cerr << "Out of range: " << e.what() << "\n";
  } catch (std::exception &e) {
    std::cerr << "Exception occured: " << e.what() << "\n";
  }
  std::cout << "\n"; // separate results
}
