#ifndef LFU_CACHE_H
#define LFU_CACHE_H

#include <unordered_map>
#include <list>
#include <stdexcept>

// cada bloque guarda información
struct Node {
    int key;
    int value;
    int freq; // cuántas veces se ha accedido a este nodo (get o put)
};

class LFUCache {
private:
    int capacity;
    int current_size;
    int min_freq;     // Nos dice cuál es la frecuencia más baja actual para borrar rápido

    // MAPA 1: key -> Puntero/Iterador al Nodo
    // Sirve para responder al instante: "¿Existe esta llave? ¿Dónde está exactamente?"
    std::unordered_map<int, std::list<Node>::iterator> key_table;

    // MAPA 2: frecuencia -> Lista Doblemente Enlazada de nodos con esa frecuencia
    // Usamos lista doble porque para borrar toma O(1).
    std::unordered_map<int, std::list<Node>> freq_table;

public:
    // Constructor
    LFUCache(int cap) {
        capacity = cap;
        current_size = 0;
        min_freq = 0;
    }

    // Métodos
    int get(int key);
    void put(int key, int value);

    // Método auxiliar
    void updateFreq(int key); 
};

#endif