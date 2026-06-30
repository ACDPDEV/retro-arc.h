#include <iostream>
#include <vector>
#include <string>

#include "../Common/Input.h"
#include "../Common/Color.h"
#include "../Common/Theme.h"

using namespace std;

/// @brief Nombres de los tests ejecutados (para reporte final)
vector<string> testNames;

/// @brief Resultados de los tests (true = pass, false = fail)
vector<bool> testResults;

/// @brief Flag global: true si todos los tests pasan, false si alguno falla
bool passed = true;

/// @brief Registra un test ejecutado
/// @param name Nombre descriptivo del test
/// @param result true si pasó, false si falló
/// @details Actualiza testNames, testResults y passed global
void AddTest(string name, bool result) {
    testNames.push_back(name);
    testResults.push_back(result);

    if (!result)
        passed = false;
}

/// @brief Tests para Validate(): valida entradas contra tipos esperados
/// @details Verifica int, float, string, char, bool con entradas válidas
void ValidateTest() {
    AddTest("Validar entero", Validate("1", "int"));
    AddTest("Validar flotante", Validate("1.5", "float"));
    AddTest("Validar cadena", Validate("hello", "string"));
    AddTest("Validar carácter", Validate("a", "char"));
    AddTest("Validar booleano", Validate("true", "bool"));
}

/// @brief Tests para ParseInt(): conversión string -> int (permisivo)
/// @details Casos: "1" ok, "1.5" truncado a 1, inválidos "hello","a","true" lanzan excepción
void ParseIntTest() {
    try { AddTest("Convertir \"1\" a entero", ParseInt("1") == 1); }
    catch (...) { AddTest("Convertir \"1\" a entero", false); }

    try { AddTest("Convertir \"1.5\" a entero", ParseInt("1.5") == 1); }
    catch (...) { AddTest("Convertir \"1.5\" a entero", false); }

    try { ParseInt("hello"); AddTest("Error al convertir \"hello\" a entero", false); }
    catch (...) { AddTest("Error al convertir \"hello\" a entero", true); }

    try { ParseInt("a"); AddTest("Error al convertir \"a\" a entero", false); }
    catch (...) { AddTest("Error al convertir \"a\" a entero", true); }

    try { ParseInt("true"); AddTest("Error al convertir \"true\" a entero", false); }
    catch (...) { AddTest("Error al convertir \"true\" a entero", true); }
}

/// @brief Tests para ParseIntStrict(): conversión estricta sin decimales/notación científica
/// @details Acepta solo enteros puros. Rechaza "1.5", "1e5", "1e-5" (lanzan excepción)
void ParseIntStrictTest() {
    try { AddTest("Convertir \"1\" a entero estricto", ParseIntStrict("1") == 1); }
    catch (...) { AddTest("Convertir \"1\" a entero estricto", false); }

    try { ParseIntStrict("1.5"); AddTest("Error al convertir \"1.5\" a entero estricto", false); }
    catch (...) { AddTest("Error al convertir \"1.5\" a entero estricto", true); }

    try { ParseIntStrict("1e5"); AddTest("Error al convertir \"1e5\" a entero estricto", false); }
    catch (...) { AddTest("Error al convertir \"1e5\" a entero estricto", true); }

    try { ParseIntStrict("1e-5"); AddTest("Error al convertir \"1e-5\" a entero estricto", false); }
    catch (...) { AddTest("Error al convertir \"1e-5\" a entero estricto", true); }
}

/// @brief Tests para ParseFloat(): conversión string -> float
/// @details Casos: "1.5" ok, inválidos "hello","a","true" lanzan excepción
void ParseFloatTest() {
    try { AddTest("Convertir \"1.5\" a flotante", ParseFloat("1.5") == 1.5f); }
    catch (...) { AddTest("Convertir \"1.5\" a flotante", false); }

    try { ParseFloat("hello"); AddTest("Error al convertir \"hello\" a flotante", false); }
    catch (...) { AddTest("Error al convertir \"hello\" a flotante", true); }

    try { ParseFloat("a"); AddTest("Error al convertir \"a\" a flotante", false); }
    catch (...) { AddTest("Error al convertir \"a\" a flotante", true); }

    try { ParseFloat("true"); AddTest("Error al convertir \"true\" a flotante", false); }
    catch (...) { AddTest("Error al convertir \"true\" a flotante", true); }
}

/// @brief Tests para ParseBool(): conversión string -> bool
/// @details Acepta "true"/"false" y "1"/"0". Inválidos "hello","a" lanzan excepción
void ParseBoolTest() {
    try { AddTest("Convertir \"true\" a booleano", ParseBool("true") == true); }
    catch (...) { AddTest("Convertir \"true\" a booleano", false); }

    try { AddTest("Convertir \"false\" a booleano", ParseBool("false") == false); }
    catch (...) { AddTest("Convertir \"false\" a booleano", false); }

    try { AddTest("Convertir \"1\" a booleano", ParseBool("1") == true); }
    catch (...) { AddTest("Convertir \"1\" a booleano", false); }

    try { AddTest("Convertir \"0\" a booleano", ParseBool("0") == false); }
    catch (...) { AddTest("Convertir \"0\" a booleano", false); }

    try { ParseBool("hello"); AddTest("Error al convertir \"hello\" a booleano", false); }
    catch (...) { AddTest("Error al convertir \"hello\" a booleano", true); }

    try { ParseBool("a"); AddTest("Error al convertir \"a\" a booleano", false); }
    catch (...) { AddTest("Error al convertir \"a\" a booleano", true); }
}

/// @brief Punto de entrada: ejecuta todos los tests y reporta resultados
/// @return 0 si todos pasan, 1 si alguno falla
int main() {
    ValidateTest();
    ParseIntTest();
    ParseIntStrictTest();
    ParseFloatTest();
    ParseBoolTest();

    cout << endl;

    if (passed) cout << color(FOREGROUND, BACKGROUND) << "Todos los tests pasaron." << endl << endl;
    else cout << color(ACCENT, BACKGROUND) << "Algunos tests fallaron." << endl << endl;

    for (size_t i = 0; i < testResults.size(); ++i) {
        if (testResults[i]) cout << color(COLOR2, BACKGROUND) + "[PASS] " << color(FOREGROUND, BACKGROUND) << testNames[i] << endl;
        else cout << color(COLOR1, BACKGROUND) + "[FAIL] " << color(FOREGROUND, BACKGROUND) << testNames[i] << endl;
    }

    cout << endl << color(FOREGROUND, BACKGROUND) << "Test que pasaron: ";

    int passedCount = 0;
    for (int i = 0; i < testResults.size(); ++i) if (testResults[i]) passedCount++;

    cout << passedCount << "/" << testResults.size() << endl;

    if (passed) return 0;
    else return 1;
}