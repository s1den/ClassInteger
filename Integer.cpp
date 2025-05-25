#include "Integer.h"
#include <limits>
#include <stdexcept>

long long abs_ll(long long n) {
    return (n < 0) ? -n : n;
}

Integer::Integer() : sign(true), magnitude(0) {}

Integer::Integer(bool sign, long long magnitude) : sign(sign), magnitude(magnitude) {}

Integer::Integer(int value) : sign(value >= 0), magnitude(abs_ll(static_cast<long long>(value))) {}

Integer::Integer(double value) {
    if (std::isnan(value) || std::isinf(value)) {
        throw std::invalid_argument("Cannot convert NaN or Infinity to Integer");
    }

    sign = (value >= 0);
    magnitude = abs_ll(static_cast<long long>(value));

    if (value > std::numeric_limits<long long>::max() || value < std::numeric_limits<long long>::min()) {
        throw std::out_of_range("Double value is out of range for Integer");
    }


}

Integer::Integer(bool value) : sign(true), magnitude(value ? 1 : 0) {}

Integer::Integer(const std::string& str) {
    parseString(str);
}

// Setters and Getters
bool Integer::getSign() const { return sign; }
long long Integer::getMagnitude() const { return magnitude; }
void Integer::setSign(bool sign) { this->sign = sign; }
void Integer::setMagnitude(long long magnitude) { this->magnitude = magnitude; }

// Predicates
bool Integer::isEven() const { return magnitude % 2 == 0; }
bool Integer::isOdd() const { return magnitude % 2 != 0; }
bool Integer::isNegative() const { return !sign && magnitude != 0; }
bool Integer::isPositive() const { return sign || magnitude == 0; }

bool Integer::isPrime() const {
    if (magnitude <= 1) return false;
    for (long long i = 2; i * i <= magnitude; ++i) {
        if (magnitude % i == 0) return false;
    }
    return true;
}

bool Integer::isCoprime(const Integer& other) const {
    return GCD(other) == 1;
}

bool Integer::isSameObject(const Integer& other) const {
    return this == &other;
}

// Operations
long long Integer::LCM(const Integer& other) const {
    if (magnitude == 0 || other.magnitude == 0) return 0;
    return (magnitude * other.magnitude) / GCD(other);
}

long long Integer::GCD(const Integer& other) const {
    long long a = magnitude;
    long long b = other.magnitude;
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

std::vector<long long> Integer::primeFactors() const {
    std::vector<long long> factors;
    long long n = magnitude;
    if (n <= 1) return factors;

    while (n % 2 == 0) {
        factors.push_back(2);
        n /= 2;
    }

    for (long long i = 3; i * i <= n; i += 2) {
        while (n % i == 0) {
            factors.push_back(i);
            n /= i;
        }
    }

    if (n > 2) {
        factors.push_back(n);
    }

    return factors;
}

// Operators
Integer Integer::operator-() const {
    return Integer(!sign, magnitude);
}

Integer Integer::operator+() const {
    return *this;
}


Integer Integer::operator+(const Integer& other) const {
    if (sign == other.sign) {
        return Integer(sign, magnitude + other.magnitude);
    }
    else {
        if (magnitude > other.magnitude) {
            return Integer(sign, magnitude - other.magnitude);
        }
        else {
            return Integer(other.sign, other.magnitude - magnitude);
        }
    }
}

Integer Integer::operator-(const Integer& other) const {
    return *this + (-other);
}

Integer Integer::operator*(const Integer& other) const {
    return Integer(sign == other.sign, magnitude * other.magnitude);
}

Integer Integer::operator/(const Integer& other) const {
    if (other.magnitude == 0) {
        throw std::runtime_error("Division by zero");
    }
    return Integer(sign == other.sign, magnitude / other.magnitude);
}

Integer Integer::operator%(const Integer& other) const {
    if (other.magnitude == 0) {
        throw std::runtime_error("Division by zero");
    }
    return Integer(sign, magnitude % other.magnitude);
}

Integer& Integer::operator+=(const Integer& other) {
    *this = *this + other;
    return *this;
}

Integer& Integer::operator-=(const Integer& other) {
    *this = *this - other;
    return *this;
}

Integer& Integer::operator*=(const Integer& other) {
    *this = *this * other;
    return *this;
}

Integer& Integer::operator/=(const Integer& other) {
    if (other.magnitude == 0) {
        throw std::runtime_error("Division by zero");
    }
    *this = *this / other;
    return *this;
}

Integer& Integer::operator%=(const Integer& other) {
    if (other.magnitude == 0) {
        throw std::runtime_error("Division by zero");
    }
    *this = *this % other;
    return *this;
}

Integer& Integer::operator++() {
    *this += 1;
    return *this;
}

Integer Integer::operator++(int) {
    Integer temp = *this;
    ++(*this);
    return temp;
}

Integer& Integer::operator--() {
    *this -= 1;
    return *this;
}

Integer Integer::operator--(int) {
    Integer temp = *this;
    --(*this);
    return temp;
}

bool Integer::operator==(const Integer& other) const {
    return sign == other.sign && magnitude == other.magnitude;
}

bool Integer::operator!=(const Integer& other) const {
    return !(*this == other);
}

bool Integer::operator>(const Integer& other) const {
    if (sign && !other.sign) return true;
    if (!sign && other.sign) return false;

    if (sign) {
        return magnitude > other.magnitude;
    }
    else {
        return magnitude < other.magnitude;
    }
}

bool Integer::operator<(const Integer& other) const {
    return other > *this;
}

bool Integer::operator>=(const Integer& other) const {
    return (*this > other) || (*this == other);
}

bool Integer::operator<=(const Integer& other) const {
    return (*this < other) || (*this == other);
}

std::ostream& operator<<(std::ostream& os, const Integer& obj) {
    if (!obj.sign) os << "-";
    os << obj.magnitude;
    return os;
}


void Integer::parseString(const std::string& str) {
    size_t i = 0;
    sign = true;
    if (str[0] == '-') {
        sign = false;
        i = 1;
    }
    else if (str[0] == '+') {
        i = 1;
    }

    std::string numberPart = str.substr(i);
    if (numberPart.empty()) {
        throw std::invalid_argument("Invalid string format for Integer");
    }

    try {
        magnitude = std::stoll(numberPart);
    }
    catch (const std::invalid_argument& e) {
        throw std::invalid_argument("Invalid string format for Integer (invalid argument)");
    }
    catch (const std::out_of_range& e) {
        throw std::out_of_range("String value is out of range for Integer");
    }
}