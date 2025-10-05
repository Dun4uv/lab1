#include "polynomial.h"

template <typename T>
Polynomial<T>::Polynomial(size_t max_degree) : degree(max_degree) {
    coefficients = new T[degree + 1]{};
}

template <typename T>
Polynomial<T>::Polynomial(const T* values, size_t size) : degree(size - 1) {
    coefficients = new T[size];
    for (size_t i = 0; i < size; ++i) coefficients[i] = values[i];
}

template <typename T>
Polynomial<T>::Polynomial(const Polynomial& other) : degree(other.degree) {
    coefficients = new T[degree + 1];
    for (size_t i = 0; i <= degree; ++i) coefficients[i] = other.coefficients[i];
}

template <typename T>
Polynomial<T>& Polynomial<T>::operator=(const Polynomial& other) {
    if (this != &other) {
        delete[] coefficients;
        degree = other.degree;
        coefficients = new T[degree + 1];
        for (size_t i = 0; i <= degree; ++i) coefficients[i] = other.coefficients[i];
    }
    return *this;
}

template <typename T>
Polynomial<T>::~Polynomial() {
    delete[] coefficients;
}

template <typename T>
T Polynomial<T>::operator[](size_t power) const {
    if (power > degree) return T{};
    return coefficients[power];
}


template <typename T>
bool Polynomial<T>::operator==(const Polynomial& other) const {
    if (degree != other.degree) return false;
    for (size_t i = 0; i <= degree; ++i) {
        if (coefficients[i] != other.coefficients[i]) return false;
    }
    return true;
}

template <typename T>
bool Polynomial<T>::operator!=(const Polynomial& other) const {
    return !(*this == other);
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Polynomial<T>& poly) {
    for (size_t i = 0; i <= poly.get_degree(); ++i) {
        os << poly[i] << "*x^"<<i;
        if (i != poly.get_degree()) os << " + ";
    }
    return os;
}

template class Polynomial<int>;
template class Polynomial<float>;
template class Polynomial<double>;
template class Polynomial<std::complex<float>>;
template class Polynomial<std::complex<double>>;

template std::ostream& operator<< <int>(std::ostream&, const Polynomial<int>&);
template std::ostream& operator<< <float>(std::ostream&, const Polynomial<float>&);
template std::ostream& operator<< <double>(std::ostream&, const Polynomial<double>&);
template std::ostream& operator<< <std::complex<float>>(std::ostream&, const Polynomial<std::complex<float>>&);
template std::ostream& operator<< <std::complex<double>>(std::ostream&, const Polynomial<std::complex<double>>&);
