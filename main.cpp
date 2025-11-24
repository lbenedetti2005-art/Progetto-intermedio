#include <iostream>
#include "InertialDriver.h"
using namespace std;

void print_measure(const array<array<double, NUM_VAL>, NUM_SENS>& m) {
    for (int s = 0; s < NUM_SENS; s++) {
        cout << "Sensor " << s << ": ";
        for (int v = 0; v < NUM_VAL; v++)
            cout << m[s][v] << " ";
        cout << endl;
    }
    cout << endl;
}

array<array<double, NUM_VAL>, NUM_SENS> make_measure(int base) {
    array<array<double, NUM_VAL>, NUM_SENS> m;

    for (int s = 0; s < NUM_SENS; s++)
        for (int v = 0; v < NUM_VAL; v++)
            m[s][v] = base + s * 0.1 + v * 0.01;

    return m;
}

int main() {
    cout << "\n===== TESTER INERTIAL DRIVER =====\n\n";

    InertialDriver d;

    // ------------------------------------------------------------
    cout << "1) INSERISCO 3 MISURE (buffer vuoto)...\n\n";
    // ------------------------------------------------------------
    d.push_back(make_measure(10));
    d.push_back(make_measure(20));
    d.push_back(make_measure(30));

    cout << "Ultima misura salvata:\n";
    cout << d << endl;

    // ------------------------------------------------------------
    cout << "2) TESTO POP_FRONT...\n\n";
    // ------------------------------------------------------------
    auto first = d.pop_front();

    cout << "Misura estratta (pop_front):\n";
    print_measure(first);

    cout << "Ultima misura rimasta dopo il pop:\n";
    cout << d << endl;

    // ------------------------------------------------------------
    cout << "3) RIEMPIO IL BUFFER (BUFFER_DIM = " << BUFFER_DIM << ")...\n\n";
    // ------------------------------------------------------------
    for (int i = 0; i < BUFFER_DIM + 2; i++) {
        d.push_back(make_measure(100 + i * 10));
    }

    cout << "\nStampa dell'ultima misura (dovrebbe essere la più recente):\n";
    cout << d << endl;

    // ------------------------------------------------------------
    cout << "4) TEST get_reading()...\n\n";
    // ------------------------------------------------------------
    try {
        auto r = d.get_reading(5);  // lettura del sensore 5
        cout << "Lettura del sensore 5 dell'ultima misura:\n";
        for (double v : r) cout << v << " ";
        cout << "\n\n";
    }
    catch (...) {
        cout << "ERRORE get_reading()\n";
    }

    // ------------------------------------------------------------
    cout << "5) TEST ECCEZIONI...\n\n";
    // ------------------------------------------------------------
    InertialDriver empty;

    try {
        empty.pop_front();
        cout << "ERRORE: pop_front non ha lanciato eccezione!\n";
    }
    catch (InertialDriver::Invalid&) {
        cout << "OK: pop_front ha lanciato correttamente Invalid()\n";
    }

    try {
        empty.get_reading(0);
        cout << "ERRORE: get_reading non ha lanciato eccezione!\n";
    }
    catch (InertialDriver::Invalid&) {
        cout << "OK: get_reading ha lanciato correttamente Invalid()\n";
    }

    cout << "\n===== FINE TEST =====\n";
    return 0;
}
