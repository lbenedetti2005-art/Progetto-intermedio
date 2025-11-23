#include <iostream>
#include "MyVector.h"

int main() {
    std::cout << "=== Test MyVector ===\n";

    // Test costruttore con size
    MyVector<int> v1(5);
    std::cout << "v1 (5 elementi inizializzati): ";
    v1.print();

    // Test initializer_list
    MyVector<int> v2{1, 2, 3};
    std::cout << "v2 {1,2,3}: ";
    v2.print();

    // Test push_back
    v2.push_back(4);
    v2.push_back(5);
    std::cout << "v2 dopo push_back(4), push_back(5): ";
    v2.print();

    // Test pop_back
    v2.pop_back();
    std::cout << "v2 dopo pop_back(): ";
    v2.print();

    // Test operator[]
    std::cout << "v2[1] = " << v2[1] << "\n";

    // Test at() con try/catch
    try {
        std::cout << "v2.at(10) → ";
        std::cout << v2.at(10) << "\n"; // dovrebbe lanciare eccezione
    } catch (MyVector<int>::Invalid&) {
        std::cout << "Eccezione catturata correttamente\n";
    }

    // Test copia
    MyVector<int> v3 = v2;
    std::cout << "v3 (copia di v2): ";
    v3.print();

    // Test move
    MyVector<int> v4 = std::move(v3);
    std::cout << "v4 (move da v3): ";
    v4.print();

    std::cout << "=== Fine test ===\n";
    return 0;
}
