#include "LFUCache.h"

// Constructor: Inicializa la capacidad y otras variables
LFUCache::LFUCache(int cap) {
    capacidad = cap;
    frecuencia_minima = 0;
}

// Método Auxiliar: Actualiza la frecuencia de una llave existente
void LFUCache::Frecuencia_actualizada(int llave) {
    // 1. Obtener la información del nodo actual
    auto node_it = tabla_clave[llave];
    int val = node_it->valor;
    int freq = node_it->frecuencia;

    // 2. Borrar el nodo de su lista de frecuencia actual
    tabla_frecuencia[freq].erase(node_it);

    // 3. Si la lista de donde lo sacamos quedó vacía y era la mínima, la frecuencia mínima global debe aumentar.
    if (tabla_frecuencia[freq].empty() && frecuencia_minima == freq) {
        frecuencia_minima++;
    }

    // 4. Aumentar su frecuencia y meter el nodo al frente de la nueva lista
    freq++;
    tabla_frecuencia[freq].push_front({llave, val, freq});

    // 5. Actualizar el puntero en la tabla Hash para no perder el rastro
    tabla_clave[llave] = tabla_frecuencia[freq].begin();
}

// Método GET: Devuelve el valor si existe, o sino -1.
int LFUCache::get(int llave) {
    // Si la llave no está en nuestro mapa, no existe
    if (tabla_clave.find(llave) == tabla_clave.end()) {
        return -1; 
    }
    
    // Si existe, actualizamos su frecuencia
    Frecuencia_actualizada(llave);
    
    return tabla_clave[llave]->valor;
}

// Método PUT: Inserta un nuevo valor o actualiza uno existente
void LFUCache::put(int llave, int valor) {
    if (capacidad == 0) return; // Caso borde de capacidad nula

    // Caso 1: La llave ya existe. Solo actualizamos valor y frecuencia.
    if (tabla_clave.find(llave) != tabla_clave.end()) {
        tabla_clave[llave]->valor = valor;
        Frecuencia_actualizada(llave);
        return;
    }

    // Caso 2: La llave no existe y el caché está lleno (EVICT).
    if (tabla_clave.size() == capacidad) {
        // Sacamos al nodo más antiguo de la lista de menor frecuencia
        auto evict_node = tabla_frecuencia[frecuencia_minima].back();

        // Lo borramos de ambas estructuras
        tabla_clave.erase(evict_node.llave);
        tabla_frecuencia[frecuencia_minima].pop_back();
    }

    // Caso 3: Insertar el elemento nuevo
    frecuencia_minima = 1; // la frecuencia mínima debe ser 1
    tabla_frecuencia[1].push_front({llave, valor, 1}); // Lo metemos al frente de la lista
    tabla_clave[llave] = tabla_frecuencia[1].begin();    // Guardamos su posición en el mapa
}