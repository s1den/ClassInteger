#ifndef INTEGER_H
#define INTEGER_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>

class Integer {
private:
    bool sign;
    long long magnitude;

public:
    
    // Constructors
    Integer();
    Integer(bool sign, long long magnitude);
    Integer(int value);
    Integer(double value);
    Integer(bool value);
    Integer(const std::string& str);

    // Setters and Getters
    bool getSign() const;
    long long getMagnitude() const;
    void setSign(bool sign);
    void setMagnitude(long long magnitude);

    // Predicates
    bool isEven() const;
    bool isOdd() const;
    bool isNegative() const;
    bool isPositive() const;
    bool isPrime() const;
    bool isCoprime(const Integer& other) const;
    bool isSameObject(const Integer& other) const;

    // Operations
    long long LCM(const Integer& other) const;
    long long GCD(const Integer& other) const;
    std::vector<long long> primeFactors() const;

    // Operators
    Integer operator-() const;
    Integer operator+() const;


    Integer operator+(const Integer& other) const;
    Integer operator-(const Integer& other) const;
    Integer operator*(const Integer& other) const;
    Integer operator/(const Integer& other) const;
    Integer operator%(const Integer& other) const;

    Integer& operator+=(const Integer& other);
    Integer& operator-=(const Integer& other);
    Integer& operator*=(const Integer& other);
    Integer& operator/=(const Integer& other);
    Integer& operator%=(const Integer& other);

    Integer& operator++();
    Integer operator++(int);
    Integer& operator--();
    Integer operator--(int);

    bool operator==(const Integer& other) const;
    bool operator!=(const Integer& other) const;
    bool operator>(const Integer& other) const;
    bool operator<(const Integer& other) const;
    bool operator>=(const Integer& other) const;
    bool operator<=(const Integer& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Integer& obj);

private:
    void parseString(const std::string& str);
};

#endif