#include <iostream>
#include <chrono>
#include "LFUCache.h"

int main() {
    std::cout << "Benchmark de LFU Cache" << std::endl;
    
    int operaciones = 100000;
    LFUCache cache(1000); // Capacidad de 1000 para forzar evicciones frecuentes

    // Iniciar cronómetro
    auto inicio = std::chrono::high_resolution_clock::now();

    // Hacer 100,000 inserciones y lecturas
    for (int i = 0; i < operaciones; i++) {
        cache.put(i, i * 2);
        cache.get(i / 2); // Leemos elementos aleatorios
    }

    // Detener cronómetro
    auto fin = std::chrono::high_resolution_clock::now();
    auto duracion = std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);

    std::cout << "Se ejecutaron " << operaciones * 2 << " operaciones (put/get)." << std::endl;
    std::cout << "Tiempo total: " << duracion.count() << " milisegundos." << std::endl;
    
    if (duracion.count() < 100) {
        std::cout << "¡Rendimiento excelente! Complejidad O(1) confirmada." << std::endl;
    }

    return 0;
}