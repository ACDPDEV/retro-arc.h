/// @file Test.h
/// @brief Framework de tests header-only para PROC1.
///        Proporciona macros TEST(), ASSERT_TRUE(), ASSERT_EQ() y TEST_RUNNER().
///        Sigue el patrón AddTest/result/pass del proyecto (ver Tests/PokemonLogicTest.cpp).
///        Sin dependencias externas — solo usa <iostream>, <string>, <vector>.
#pragma once

#include <iostream>
#include <string>
#include <vector>

// --- Infraestructura de registro interno ---

/// @brief Almacena el resultado de una única aserción.
struct TestResult {
    std::string testName;
    bool passed;
};

/// @brief Almacena una función de test registrada para ejecución diferida.
struct TestFunc {
    std::string name;
    void (*func)();
};

/// @brief Almacenamiento global para todos los resultados de test de la unidad de traducción.
inline std::vector<TestResult>& GetTestResults() {
    static std::vector<TestResult> results;
    return results;
}

/// @brief Almacenamiento global para todas las funciones de test registradas.
inline std::vector<TestFunc>& GetTestFuncs() {
    static std::vector<TestFunc> funcs;
    return funcs;
}

/// @brief Registra el resultado de una única aserción.
/// @param name Nombre descriptivo del test o aserción
/// @param result true si pasó, false si falló
inline void RecordResult(const std::string& name, bool result) {
    GetTestResults().push_back({name, result});
}

// --- Macros públicas ---

/// @brief Define y registra una función de test. Uso: TEST(NombreTest) { ... }
///        La función se registra via inicialización estática y se ejecuta con TEST_RUNNER().
/// @param testName Nombre del test (se usa como identificador)
#define TEST(testName)                                                          \
    static void testName##_Func();                                               \
    namespace {                                                                  \
        struct testName##_Registrar {                                            \
            testName##_Registrar() {                                             \
                GetTestFuncs().push_back({#testName, testName##_Func});          \
            }                                                                    \
        } testName##_instance;                                                   \
    }                                                                            \
    static void testName##_Func()

/// @brief Verifica que expr sea true. Registra fallo con archivo y línea.
///        NO termina el proceso — la ejecución continúa hasta el final del test.
/// @param expr Expresión booleana a verificar
#define ASSERT_TRUE(expr)                                                        \
    do {                                                                         \
        if (!(expr)) {                                                           \
            std::string msg = std::string(__FILE__) + ":" + std::to_string(__LINE__) \
                + " — ASSERT_TRUE(" #expr ") failed";                            \
            RecordResult(msg, false);                                            \
        } else {                                                                 \
            std::string msg = std::string(__FILE__) + ":" + std::to_string(__LINE__) \
                + " — ASSERT_TRUE(" #expr ")";                                   \
            RecordResult(msg, true);                                             \
        }                                                                        \
    } while (0)

/// @brief Verifica que a == b. Registra fallo si no son iguales.
///        NO termina el proceso — la ejecución continúa hasta el final del test.
///        Nota: el mensaje de fallo muestra las expresiones, no los valores (funciona con cualquier tipo).
/// @param a Primer valor a comparar
/// @param b Segundo valor a comparar
#define ASSERT_EQ(a, b)                                                          \
    do {                                                                         \
        if (!((a) == (b))) {                                                     \
            std::string msg = std::string(__FILE__) + ":" + std::to_string(__LINE__) \
                + " — ASSERT_EQ(" #a ", " #b ") failed";                         \
            RecordResult(msg, false);                                            \
        } else {                                                                 \
            std::string msg = std::string(__FILE__) + ":" + std::to_string(__LINE__) \
                + " — ASSERT_EQ(" #a ", " #b ")";                                \
            RecordResult(msg, true);                                             \
        }                                                                        \
    } while (0)

/// @brief Ejecuta todos los tests registrados e imprime los resultados.
///        Retorna 0 si todos pasan, 1 si alguno falla. Llamar desde main().
#define TEST_RUNNER()                                                            \
    int main() {                                                                 \
        /* Ejecutar todas las funciones de test registradas */                   \
        auto& funcs = GetTestFuncs();                                            \
        for (size_t i = 0; i < funcs.size(); ++i) {                              \
            funcs[i].func();                                                     \
        }                                                                        \
        /* Imprimir resultados */                                                \
        auto& results = GetTestResults();                                        \
        int passedCount = 0;                                                     \
        int failCount = 0;                                                       \
        for (const auto& r : results) {                                          \
            if (r.passed) {                                                      \
                std::cout << "[PASS] " << r.testName << std::endl;               \
                passedCount++;                                                   \
            } else {                                                             \
                std::cout << "[FAIL] " << r.testName << std::endl;               \
                failCount++;                                                     \
            }                                                                    \
        }                                                                        \
        std::cout << std::endl;                                                  \
        if (failCount == 0) {                                                    \
            std::cout << "Todos los tests pasaron." << std::endl;                \
        } else {                                                                 \
            std::cout << "Algunos tests fallaron." << std::endl;                 \
        }                                                                        \
        std::cout << "Tests que pasaron: " << passedCount << "/"                \
                  << results.size() << std::endl;                                \
        return failCount == 0 ? 0 : 1;                                           \
    }
