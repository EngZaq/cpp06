#include "ScalarConverter.hpp"

#include <cctype>
#include <iomanip>
#include <sstream>

enum e_type {
    CHAR,
    INT,
    FLOAT,
    DOUBLE,
    PSEUDO,
    INVALID
};

static e_type parseType(const std::string& literal) {
    if (literal == "-inff" || literal == "+inff" || literal == "nanf" ||
        literal == "-inf"  || literal == "+inf"  || literal == "nan") {
        return PSEUDO;
    }

    if (literal.length() == 1 && !std::isdigit(literal[0])) {
        return CHAR;
    }

    bool hasDot = false;
    bool hasF = false;
    int digitCount = 0;
    
    size_t i = (literal[0] == '-' || literal[0] == '+') ? 1 : 0;

    for (; i < literal.length(); i++) {
        if (literal[i] == '.') {
            if (hasDot)
                return INVALID;
            hasDot = true;
        } else if (literal[i] == 'f') {
            if (hasF || i != literal.length() - 1) return INVALID;
            hasF = true;
        } else if (std::isdigit(literal[i])) {
            digitCount++;
        } else {
            return INVALID;
        }
    }

    if (digitCount == 0)
        return INVALID;

    if (hasF) return FLOAT;
    if (hasDot) return DOUBLE;
    return INT;
}

template <typename T>
static std::string formatValue(T value) {
    std::ostringstream output;

    output << std::setprecision(6) << value;

    std::string result = output.str();
    if (result.find_first_of("eE") != std::string::npos) {
        std::ostringstream fixedOutput;

        fixedOutput << std::fixed
                    << std::setprecision(std::numeric_limits<T>::digits10 + 1)
                    << value;
        result = fixedOutput.str();
    }

    std::string::size_type dot = result.find('.');

    if (dot == std::string::npos) {
        result += ".0";
    } else {
        while (result.length() > dot + 1 && result[result.length() - 1] == '0') {
            result.erase(result.length() - 1);
        }

        if (result[result.length() - 1] == '.') {
            result += '0';
        }
    }

    return result;
}

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter& other) { (void)other; }
ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other) { (void)other; return *this; }
ScalarConverter::~ScalarConverter() {}

void ScalarConverter::convert(const std::string& literal) {
    e_type type = parseType(literal);

    if (type == INVALID) {
        std::cout << "char: impossible\n"
                  << "int: impossible\n"
                  << "float: impossible\n"
                  << "double: impossible\n";
        return;
    }

    if (type == PSEUDO) {
        std::cout << "char: impossible\n"
                  << "int: impossible\n";
        if (literal == "nan" || literal == "nanf") {
            std::cout << "float: nanf\ndouble: nan\n";
        } else if (literal == "+inf" || literal == "+inff") {
            std::cout << "float: +inff\ndouble: +inf\n";
        } else if (literal == "-inf" || literal == "-inff") {
            std::cout << "float: -inff\ndouble: -inf\n";
        }
        return;
    }

    char   c = 0;
    int    i = 0;
    float  f = 0.0f;
    double d = 0.0;
    long double number = 0.0L;
    bool   intImpossible = false;

    switch (type) {
        case CHAR:
            c = literal[0];
            number = static_cast<long double>(c);
            i = static_cast<int>(c);
            f = static_cast<float>(c);
            d = static_cast<double>(c);
            break;
        case INT: {
            number = std::strtold(literal.c_str(), NULL);
            d = static_cast<double>(number);
            f = static_cast<float>(number);
            if (number < std::numeric_limits<int>::min() || number > std::numeric_limits<int>::max()) {
                intImpossible = true;
            } else {
                i = static_cast<int>(number);
                c = static_cast<char>(i);
            }
            break;
        }
        case FLOAT:
            number = std::strtold(literal.c_str(), NULL);
            d = static_cast<double>(number);
            f = static_cast<float>(number);
            c = static_cast<char>(f);
            i = static_cast<int>(f);
            break;
        case DOUBLE:
            number = std::strtold(literal.c_str(), NULL);
            d = static_cast<double>(number);
            f = static_cast<float>(number);
            c = static_cast<char>(d);
            i = static_cast<int>(d);
            break;
        default:
            break;
    }

    bool doubleImpossible = (number > std::numeric_limits<double>::max() ||
                             number < -std::numeric_limits<double>::max() ||
                             number != number);
    bool floatImpossible = doubleImpossible ||
                           (number > std::numeric_limits<float>::max() ||
                            number < -std::numeric_limits<float>::max() ||
                            f != f);

    if (doubleImpossible) {
        std::cout << "char: impossible\n"
                  << "int: impossible\n"
                  << "float: impossible\n"
                  << "double: impossible\n";
        return;
    }

    if (number < 0 || number > 127) {
        std::cout << "char: impossible\n";
    } else if (!std::isprint(c)) {
        std::cout << "char: Non displayable\n";
    } else {
        std::cout << "char: '" << c << "'\n";
    }

    if (intImpossible || number < std::numeric_limits<int>::min() || number > std::numeric_limits<int>::max()) {
        std::cout << "int: impossible\n";
    } else {
        std::cout << "int: " << i << "\n";
    }

    if (floatImpossible) {
        std::cout << "float: impossible\n";
    } else {
        std::cout << "float: " << formatValue(f) << "f\n";
    }

    std::cout << "double: " << formatValue(d) << "\n";
}