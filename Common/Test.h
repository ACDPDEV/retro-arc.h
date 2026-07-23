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

/// @brief Nombres de todos los resultados de test registrados.
inline std::vector<std::string>& GetTestResultNames() {
    static std::vector<std::string> names;
    return names;
}

/// @brief Resultados (pass/fail) de cada aserción registrada.
inline std::vector<bool>& GetTestResultValues() {
    static std::vector<bool> values;
    return values;
}

/// @brief Nombres de todas las funciones de test registradas.
inline std::vector<std::string>& GetTestFuncNames() {
    static std::vector<std::string> names;
    return names;
}

/// @brief Punteros a funciones de test registradas.
inline std::vector<void (*)()>& GetTestFuncPointers() {
    static std::vector<void (*)()> ptrs;
    return ptrs;
}

/// @brief Registra el resultado de una única aserción.
/// @param name Nombre descriptivo del test o aserción
/// @param result true si pasó, false si falló
inline void RecordResult(const std::string& name, bool result) {
    GetTestResultNames().push_back(name);
    GetTestResultValues().push_back(result);
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
                GetTestFuncNames().push_back(#testName);                         \
                GetTestFuncPointers().push_back(testName##_Func);                \
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
        auto& funcNames = GetTestFuncNames();                                    \
        auto& funcPtrs = GetTestFuncPointers();                                  \
        for (size_t i = 0; i < funcPtrs.size(); ++i) {                           \
            funcPtrs[i]();                                                       \
        }                                                                        \
        /* Imprimir resultados */                                                \
        auto& resultNames = GetTestResultNames();                                \
        auto& resultValues = GetTestResultValues();                              \
        int passedCount = 0;                                                     \
        int failCount = 0;                                                       \
        for (size_t i = 0; i < resultValues.size(); ++i) {                       \
            if (resultValues[i]) {                                               \
                std::cout << "[PASS] " << resultNames[i] << std::endl;           \
                passedCount++;                                                   \
            } else {                                                             \
                std::cout << "[FAIL] " << resultNames[i] << std::endl;           \
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
                  << resultValues.size() << std::endl;                           \
        return failCount == 0 ? 0 : 1;                                           \
    }
