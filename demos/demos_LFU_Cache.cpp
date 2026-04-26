#include <iostream>
#include "../include/LFUCache.h"

int main() {
    std::cout << "Iniciando Test Oficial LeetCode 460: LFU Cache (Capacidad: 2)" << std::endl;

    LFUCache lfu(2);

    lfu.put(1, 1);
    std::cout << "put(1, 1) -> Se inserta llave 1" << std::endl;

    lfu.put(2, 2);
    std::cout << "put(2, 2) -> Se inserta llave 2" << std::endl;

    std::cout << "get(1)    -> Esperado: 1  | Resultado: " << lfu.get(1) << std::endl; 
    // Frecuencias actuales: 1 (2), 2 (1)

    lfu.put(3, 3); 
    std::cout << "put(3, 3) -> Se inserta llave 3. Se elimina la llave 2 (menor frecuencia)." << std::endl;

    std::cout << "get(2)    -> Esperado: -1 | Resultado: " << lfu.get(2) << std::endl;

    std::cout << "get(3)    -> Esperado: 3  | Resultado: " << lfu.get(3) << std::endl;
    // Frecuencias actuales: llave 1 (freq 2), llave 3 (freq 2)
    // Empate en frecuencia. El más antiguo (LRU) en esa frecuencia es la llave 1.

    lfu.put(4, 4);
    std::cout << "put(4, 4) -> Se inserta llave 4. Empate de frecs, se elimina la más antigua (llave 1)." << std::endl;

    std::cout << "get(1)    -> Esperado: -1 | Resultado: " << lfu.get(1) << std::endl;
    
    std::cout << "get(3)    -> Esperado: 3  | Resultado: " << lfu.get(3) << std::endl;
    
    std::cout << "get(4)    -> Esperado: 4  | Resultado: " << lfu.get(4) << std::endl;

    std::cout << "Test Finalizado" << std::endl;

    return 0;
}