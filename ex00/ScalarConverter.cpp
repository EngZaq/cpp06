#include "ScalarConverter.hpp"

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

    switch (type) {
        case CHAR:
            c = literal[0];
            i = static_cast<int>(c);
            f = static_cast<float>(c);
            d = static_cast<double>(c);
            break;
        case INT: {
            long temp = std::strtol(literal.c_str(), NULL, 10);
            i = static_cast<int>(temp);
            c = static_cast<char>(i);
            f = static_cast<float>(i);
            d = static_cast<double>(temp);
            break;
        }
        case FLOAT:
            f = static_cast<float>(std::strtod(literal.c_str(), NULL));
            c = static_cast<char>(f);
            i = static_cast<int>(f);
            d = static_cast<double>(f);
            break;
        case DOUBLE:
            d = std::strtod(literal.c_str(), NULL);
            c = static_cast<char>(d);
            i = static_cast<int>(d);
            f = static_cast<float>(d);
            break;
        default:
            break;
    }

    if (d < 0 || d > 127) {
        std::cout << "char: impossible\n";
    } else if (!std::isprint(c)) {
        std::cout << "char: Non displayable\n";
    } else {
        std::cout << "char: '" << c << "'\n";
    }

    if (d < std::numeric_limits<int>::min() || d > std::numeric_limits<int>::max()) {
        std::cout << "int: impossible\n";
    } else {
        std::cout << "int: " << i << "\n";
    }

    if (f - std::floor(f) == 0.0f) {
        std::cout << "float: " << f << ".0f\n";
    } else {
        std::cout << "float: " << f << "f\n";
    }

    if (d - std::floor(d) == 0.0) {
        std::cout << "double: " << d << ".0\n";
    } else {
        std::cout << "double: " << d << "\n";
    }
}