#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <stdexcept>
#include <complex>

template <typename T>
class Polynomial {
private:
    T* coefficients;
    size_t degree;
    static constexpr double EPSILON = 1e-9;

public:
    explicit Polynomial(size_t max_degree);
    explicit Polynomial(const T* values, size_t size);

    Polynomial(const Polynomial& other);
    Polynomial& operator=(const Polynomial& other);
    ~Polynomial();

    T operator[](size_t power) const;
    bool operator==(const Polynomial& other) const;
    bool operator!=(const Polynomial& other) const;

    size_t get_degree() const { return degree; }
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Polynomial<T>& poly);

#endif 
