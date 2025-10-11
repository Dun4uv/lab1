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
void Polynomial<T>::set(size_t power, const T& value) {
    if (power > degree) throw std::out_of_range("Power exceeds degree");
    coefficients[power] = value;
}

template <typename T>
Polynomial<T> Polynomial<T>::operator+(const Polynomial& other) const {
    size_t max_degree = std::max(degree, other.degree);
    Polynomial result(max_degree);

    for (size_t i = 0; i <= max_degree; ++i) {
        T a = (i <= degree) ? coefficients[i] : T{};
        T b = (i <= other.degree) ? other.coefficients[i] : T{};
        result.set(i, a + b);
    }
    return result;
}

template <typename T>
Polynomial<T> Polynomial<T>::operator-(const Polynomial& other) const {
    size_t max_degree = std::max(degree, other.degree);
    Polynomial result(max_degree);

    for (size_t i = 0; i <= max_degree; ++i) {
        T a = (i <= degree) ? coefficients[i] : T{};
        T b = (i <= other.degree) ? other.coefficients[i] : T{};
        result.set(i, a - b);
    }
    return result;
}

template <typename T>
Polynomial<T> Polynomial<T>::operator*(const T& scalar) const {
    Polynomial result(degree);
    for (size_t i = 0; i <= degree; ++i) {
        result.set(i, coefficients[i] * scalar);
    }
    return result;
}

template <typename T>
T Polynomial<T>::evaluate(const T& x) const {
    T result{};
    T power = 1;
    for (size_t i = 0; i <= degree; ++i) {
        result += coefficients[i] * power;
        power *= x;
    }
    return result;
}

template <typename T>
Polynomial<T> Polynomial<T>::integral() const {
    Polynomial<T> result(degree + 1); 

    result.set(0, T{});

    for (size_t i = 0; i <= degree; ++i) {
        result.set(i + 1, coefficients[i] / static_cast<T>(i + 1));
    }

    return result;
}

template <typename T>
T Polynomial<T>::definite_integral(const T& a, const T& b) const {
    Polynomial<T> indef = this->integral();

    T Fb = indef.evaluate(b);
    T Fa = indef.evaluate(a);

    return Fb - Fa;
}


template <typename T>
void Polynomial<T>::shrink_to_fit() {
    size_t new_degree = degree;
    while (new_degree > 0 && coefficients[new_degree] == T{}) {
        --new_degree;
    }
    if (new_degree != degree) {
        T* new_coeffs = new T[new_degree + 1];
        for (size_t i = 0; i <= new_degree; ++i) new_coeffs[i] = coefficients[i];
        delete[] coefficients;
        coefficients = new_coeffs;
        degree = new_degree;
    }
}

template <typename T>
void Polynomial<T>::expand(size_t new_degree) {
    if (new_degree <= degree) return;
    T* new_coeffs = new T[new_degree + 1]{};
    for (size_t i = 0; i <= degree; ++i) new_coeffs[i] = coefficients[i];
    delete[] coefficients;
    coefficients = new_coeffs;
    degree = new_degree;
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
        os << poly[i];
        if (i != 0) os << "x^" << i;
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
