#include "headers/Polynomial/Polynomial.h"

int main() {
    Polynomial<int> p1(3);
    p1.set(0, 1);
    p1.set(1, 2);
    p1.set(2, 3);
    p1.set(3, 4);

    Polynomial<int> p2(2);
    p2.set(0, 5);
    p2.set(1, -2);
    p2.set(2, 1);

    std::cout << "p1(x) = " << p1 << "\n";
    std::cout << "p2(x) = " << p2 << "\n";

    auto sum = p1 + p2;
    std::cout << "p1 + p2 = " << sum << "\n";

    auto diff = p1 - p2;
    std::cout << "p1 - p2 = " << diff << "\n";

    auto scaled = p1 * 2;
    std::cout << "p1 * 2 = " << scaled << "\n";

    std::cout << "p1(2) = " << p1.evaluate(2) << "\n";

    return 0;
}

