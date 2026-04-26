# PC2: LFU Cache

Proyecto diseñado para la Práctica Calificada 2 del curso de Estructuras de Datos y Algoritmos en C++17. Su objetivo principal es implementar un Caché LFU (Least Frequently Used) respetando una complejidad temporal de O(1) para sus operaciones principales, y fijar un flujo de trabajo profesional que incluye:
* Compilación estructurada con **CMake**
* Separación de interfaz y lógica (`.h` y `.cpp`)
* Ejecución de **tests unitarios**
* Ejecución de un **micro-benchmark**
* Organización de entregables previos

---

## Qué contiene (Estructura del Proyecto)

* **`include/LFUCache.h`** y **`src/LFUCache.cpp`**
  Módulo principal del Caché LFU. Utiliza una combinación de `std::unordered_map` y `std::list` (listas doblemente enlazadas) para lograr búsquedas, inserciones y eliminaciones en tiempo constante O(1).
* **`actividades/`**
  Contiene las resoluciones de las actividades previas requeridas como evidencia de avance del curso.
* **`demos/demos_LFU_Cache.cpp`**
  Demostración principal y validación oficial basada en los casos de prueba del problema 460 de LeetCode.
* **`tests/test_lfu.cpp`**
  Pruebas unitarias utilizando `<cassert>` para validar la correctitud del caché frente a casos borde (capacidad cero, empates de frecuencia, etc.).
* **`benchmarks/benchmark_lfu.cpp`**
  Micro-benchmark utilizando `<chrono>` para medir el rendimiento del código ejecutando 100,000 operaciones y comprobar la eficiencia del diseño.

---

## Build normal (Compilación)

Para compilar todo el proyecto desde cero utilizando CMake, ejecuta los siguientes comandos desde la raíz del proyecto:

```bash
mkdir build
cd build
cmake ..
make
```

Una vez finalizado, puedes correr los ejecutables desde la misma carpeta `build`, 

```bash
# 1. Prueba oficial 
./demo_lfu

# 2. Correr las pruebas unitarias
./test_lfu

# 3. Correr la prueba de rendimiento
./benchmark_lfu
```
### 1. Complejidad estricta O(1)
Se evitó el uso de bucles (for/while) y arreglos dinámicos tradicionales para las búsquedas y actualizaciones en las operaciones críticas.El mapa tabla_clave guarda iteradores directos a los nodos dentro de tabla_frecuencia. Esto permite invocar la función .erase() de la lista enlazada instantáneamente, sin incurrir en el costo O(n) de buscar la posición del nodo.

### 2. Resolución de empates (LRU integrado)
La regla exige que, si el caché está lleno y existen múltiples llaves con la misma frecuencia_minima, se debe eliminar la que lleva más tiempo sin usarse (LRU).Este requerimiento se resuelve de forma natural e implícita en la estructura: al utilizar push_front (los elementos nuevos/actualizados van al inicio), los elementos más antiguos caen invariablemente al final de la lista. Así, al usar pop_back(), se garantiza la eliminación del menos usado y más antiguo en tiempo O(1).

### 3. Tests Unitarios
Los tests implementados con cassert están diseñados para estresar la lógica dura del algoritmo.Validan que el sistema no presente fallos de segmentación si se le asigna capacidad = 0 y aseguran que la regla de expulsión funcione de manera determinista cuando hay múltiples llaves compartiendo la misma frecuencia.

### 4. Benchmarks y Optimizaciones
Los micro-benchmarks demuestran que 200,000 operaciones mixtas (put y get) se resuelven en una fracción mínima de tiempo, confirmando empíricamente el tiempo constante.Se incluyó la bandera de optimización -O3 en el archivo CMakeLists.txt (set(CMAKE_CXX_FLAGS "-O3")) para instruir al compilador a priorizar la velocidad máxima de ejecución en hardware, reduciendo la sobrecarga temporal de los mapas hash y el manejo de punteros subyacentes.