#ifndef LFU_CACHE_H
#define LFU_CACHE_H

#include <unordered_map>
#include <list>
#include <stdexcept>

// cada bloque guarda información
struct Node {
    int llave;
    int valor;
    int frecuencia; // cuántas veces se ha accedido a este nodo (get o put)
};

class LFUCache {
private:
    int capacidad;
    int tamaño_actual;
    int frecuencia_minima;     // Nos dice cuál es la frecuencia más baja actual para borrar rápido

    // MAPA 1: llave -> Puntero/Iterador al Nodo
    // Sirve para responder al instante: "¿Existe esta llave? ¿Dónde está exactamente?"
    std::unordered_map<int, std::list<Node>::iterator> tabla_clave;

    // MAPA 2: frecuencia -> Lista Doblemente Enlazada de nodos con esa frecuencia
    // Usamos lista doble porque para borrar toma O(1).
    std::unordered_map<int, std::list<Node>> tabla_frecuencia;

public:
    // Constructor
    LFUCache(int cap);

    // Métodos
    int get(int llave);
    void put(int llave, int valor);

    // Método auxiliar
    void Frecuencia_actualizada(int llave); 
};

#endif