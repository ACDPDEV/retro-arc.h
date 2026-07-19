#include <iostream>
#include <vector>
#include <string>

<<<<<<< HEAD
<<<<<<< HEAD
#include "../Common/Color.h"
#include "../Common/Theme.h"
=======
#include "../Common/Theme.h"
#include "../Common/Color.h"
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08
=======
#include "../Common/Theme.h"
#include "../Common/Color.h"
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08

using namespace std;

/// @brief Nombres de los tests registrados
vector<string> testNames;
/// @brief Resultados de los tests registrados (true = pass, false = fail)
vector<bool> testResults;
/// @brief Flag global: true si todos los tests pasan, false si alguno falla
bool passed = true;

/// @brief Registra un test y actualiza estado global
/// @param name Nombre descriptivo del test
/// @param result Resultado del test (true = pasó, false = falló)
/// @details Si falla, marca passed = false
void AddTest(string name, bool result) {
    testNames.push_back(name);
    testResults.push_back(result);

    if (!result)
        passed = false;
}

/// @brief Ejecuta suite de tests para la función color()
/// @details Verifica generación de secuencias ANSI True Color para combinaciones RGB
void ColorTest() {
<<<<<<< HEAD
<<<<<<< HEAD
    AddTest("Convertir el color Negro; Negro", color({0,0,0}, {0,0,0}) == "\033[38;2;0;0;0;48;2;0;0;0m");
    AddTest("Convertir el color Blanco; Blanco", color({255,255,255}, {255,255,255}) == "\033[38;2;255;255;255;48;2;255;255;255m");
    AddTest("Convertir el color Rojo; Azul", color({255,0,0}, {0,0,255}) == "\033[38;2;255;0;0;48;2;0;0;255m");
    AddTest("Convertir colores random", color({128, 64, 32}, {16, 8, 4}) == "\033[38;2;128;64;32;48;2;16;8;4m");
    AddTest("Convertir en un solo canal", color({255, 0, 0}, {0, 255, 0}) == "\033[38;2;255;0;0;48;2;0;255;0m");
    AddTest("Convertir máximo y mínimo", color({255, 255, 255}, {0, 0, 0}) == "\033[38;2;255;255;255;48;2;0;0;0m");
=======
=======
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08
    AddTest("Convertir el color Negro; Negro", Common::Color({0,0,0}, {0,0,0}) == "\033[38;2;0;0;0;48;2;0;0;0m");
    AddTest("Convertir el color Blanco; Blanco", Common::Color({255,255,255}, {255,255,255}) == "\033[38;2;255;255;255;48;2;255;255;255m");
    AddTest("Convertir el color Rojo; Azul", Common::Color({255,0,0}, {0,0,255}) == "\033[38;2;255;0;0;48;2;0;0;255m");
    AddTest("Convertir colores random", Common::Color({128, 64, 32}, {16, 8, 4}) == "\033[38;2;128;64;32;48;2;16;8;4m");
    AddTest("Convertir en un solo canal", Common::Color({255, 0, 0}, {0, 255, 0}) == "\033[38;2;255;0;0;48;2;0;255;0m");
    AddTest("Convertir máximo y mínimo", Common::Color({255, 255, 255}, {0, 0, 0}) == "\033[38;2;255;255;255;48;2;0;0;0m");
<<<<<<< HEAD
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08
=======
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08
}

int main() {
    ColorTest();

    cout << endl;

<<<<<<< HEAD
<<<<<<< HEAD
    if (passed) cout << color(FOREGROUND, BACKGROUND) << "Todos los tests pasaron." << endl << endl;
    else cout << color(ACCENT, BACKGROUND) << "Algunos tests fallaron." << endl << endl;

    for (size_t i = 0; i < testResults.size(); ++i) {
        if (testResults[i]) cout << color(COLOR2, BACKGROUND) + "[PASS] " << color(FOREGROUND, BACKGROUND) << testNames[i] << endl;
        else cout << color(COLOR1, BACKGROUND) + "[FAIL] " << color(FOREGROUND, BACKGROUND) << testNames[i] << endl;
    }

    cout << endl << color(FOREGROUND, BACKGROUND) << "Test que pasaron: ";
=======
=======
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08
    if (passed) cout << Common::Color(Common::FOREGROUND_DARK, Common::BACKGROUND) << "Todos los tests pasaron." << endl << endl;
    else cout << Common::Color(Common::ACCENT, Common::BACKGROUND) << "Algunos tests fallaron." << endl << endl;

    for (size_t i = 0; i < testResults.size(); ++i) {
        if (testResults[i]) cout << Common::Color(Common::LIGHT_GREEN, Common::BACKGROUND) + "[PASS] " << Common::Color(Common::FOREGROUND_DARK, Common::BACKGROUND) << testNames[i] << endl;
        else cout << Common::Color(Common::RED, Common::BACKGROUND) + "[FAIL] " << Common::Color(Common::FOREGROUND_DARK, Common::BACKGROUND) << testNames[i] << endl;
    }

    cout << endl << Common::Color(Common::FOREGROUND_DARK, Common::BACKGROUND) << "Test que pasaron: ";
<<<<<<< HEAD
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08
=======
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08

    int passedCount = 0;

    for (int i = 0; i < testResults.size(); ++i) if (testResults[i]) passedCount++;

    cout << passedCount << "/" << testResults.size() << endl;

    if (passed) return 0;
    else return 1;
<<<<<<< HEAD
<<<<<<< HEAD
}
=======
}
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08
=======
}
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08
