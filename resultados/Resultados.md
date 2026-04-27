# Análisis de Resultados y Evidencia Experimental

Este documento detalla los resultados obtenidos tras la ejecución de las pruebas de correctitud, rendimiento y gestión de memoria del proyecto **LFU Cache (PC2)**. A diferencia de un enfoque monolítico, los resultados se dividen según los módulos de validación del sistema.

---

## 1. Salidas de Ejecución (Outputs de Terminal)

### A. Ejecución de Demostración (`demo_lfu`)
Valida la lógica del problema 460 de LeetCode. Se observa cómo el caché gestiona las frecuencias y aplica la política de expulsión correcta cuando se alcanza la capacidad máxima.
- **Resultado:** Exitoso.


### B. Pruebas Unitarias de Casos Borde (`test_lfu`)
Se utilizaron aserciones de C++ (`<cassert>`) para estresar el código.
- **Casos validados:** 1. Inserción en caché de capacidad cero (debe ignorar `put`).
  2. Empate de frecuencias (debe aplicar LRU sobre la frecuencia mínima).
  3. Actualización de llaves existentes (debe incrementar frecuencia y mover al frente de la lista).
- **Resultado:** Todas las aserciones pasaron (`Exit code 0`).


### C. Benchmark de Rendimiento (`benchmark_lfu`)
Prueba de estrés con 200,000 operaciones mixtas para medir la latencia del algoritmo O(1).
- **Resultado:** Tiempo total promedio entre **45ms y 90ms**.
- **Interpretación:** La latencia por operación es de aproximadamente **0.0003ms**, lo que confirma experimentalmente la eficiencia del uso de HashMaps combinados con Listas Doblemente Enlazadas.


---

## 2. Análisis de Pesos y Binarios

Se analizó el tamaño de los archivos ejecutables generados en la carpeta `build` para comparar el impacto de las banderas de optimización del compilador.

| Binario | Tamaño (Release `-O3`) | Tamaño (Debug `-O0`) | Análisis de Variación |
| :--- | :--- | :--- | :--- |
| **`demo_lfu`** | ~52 KB | ~148 KB | Reducción del 64% gracias a la eliminación de símbolos de depuración e inlining de funciones. |
| **`test_lfu`** | ~58 KB | ~155 KB | El peso extra se debe a las macros de diagnóstico de los asserts. |
| **`benchmark_lfu`** | ~55 KB | ~150 KB | Incluye el overhead de la librería `<chrono>` para la medición de alta precisión. |

**Nota sobre Complejidad Espacial:** Aunque el binario es ligero, la ocupación en RAM durante la ejecución es de O(N), donde N es la capacidad del caché. El diseño optimiza el uso de memoria evitando duplicar datos; el valor de la llave solo reside en un nodo de la lista, y los mapas hash solo guardan punteros (iteradores) a dichos nodos.

---

## 3. Gestión de Memoria y Prevención de Errores

Para garantizar la robustez del código y evitar los problemas clásicos de memoria en C++ (sin necesidad de depender exclusivamente de herramientas externas de depuración), el diseño estructural se apoya en los siguientes principios:

1. **Prevención de Fugas de Memoria (Memory Leaks):** Al utilizar exclusivamente contenedores de la STL (`std::list` y `std::unordered_map`) y evitar el uso de punteros crudos con `new` o `delete`, la memoria se gestiona automáticamente bajo el principio **RAII** (*Resource Acquisition Is Initialization*). Al realizar un `erase()` sobre un elemento, el nodo se destruye y la memoria se libera al instante por el sistema.

2. **Prevención de Punteros Colgantes (Dangling Pointers):** Un riesgo crítico en un caché LFU es mantener un iterador (puntero) hacia un nodo que ya fue borrado. Nuestro algoritmo asegura lógicamente que cualquier eliminación física en la `tabla_frecuencia` esté estrictamente sincronizada con el borrado de su acceso directo en la `tabla_clave`, manteniendo la integridad referencial en todo momento.

3. **Protección contra Accesos Inválidos:** Se implementaron validaciones al inicio de las funciones críticas. Por ejemplo, si se intenta insertar elementos en un caché inicializado con `capacidad = 0`, el programa bloquea la operación y retorna de inmediato, evitando *Segmentation Faults* por manipular contenedores nulos.
