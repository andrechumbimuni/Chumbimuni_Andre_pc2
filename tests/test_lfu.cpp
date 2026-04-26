#include <iostream>
#include <cassert>
#include "LFUCache.h"

void test_basico() {
    LFUCache cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    assert(cache.get(1) == 1); // Frecuencia de 1 pasa a ser 2
    
    cache.put(3, 3); // Expulsa al 2 (frecuencia 1)
    assert(cache.get(2) == -1); // 2 ya no debe estar
    assert(cache.get(3) == 3);  // 3 sí debe estar
}

void test_capacidad_cero() {
    LFUCache cache(0);
    cache.put(1, 1);
    assert(cache.get(1) == -1); // No debió guardar nada
}

void test_empate_frecuencias() {
    LFUCache cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    // Ambos tienen freq 1. El más antiguo es el 1.
    cache.put(3, 3); // Debería expulsar al 1
    
    assert(cache.get(1) == -1);
    assert(cache.get(2) == 2);
    assert(cache.get(3) == 3);
}

int main() {
    std::cout << "Corriendo pruebas unitarias." << std::endl;
    
    test_basico();
    test_capacidad_cero();
    test_empate_frecuencias();
    
    std::cout << "¡Todas las pruebas pasaron con éxito!" << std::endl;
    return 0;
}