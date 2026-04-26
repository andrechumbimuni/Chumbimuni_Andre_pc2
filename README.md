## PC2 - CC232

### Estudiante
- Nombre:   Andre Dylan Chumbimuni Ricci
- Código:   20230303J
- Problema asignado:    LeetCode 460 - LFU Cache
- Enlace:   https://leetcode.com/problems/lfu-cache/

### Referencia oficial
- Archivo de asignación:
  https://github.com/kapumota/CC-232/blob/main/Practicas/Practica2_CC232/Problemas-Evaluacion2.csv

### Tema principal
- Semana: 3 (Listas enlazadas, pilas, colas y deques)
- Estructura o técnica principal: HashMap + Doubly Linked List (std::unordered_map y std::list) con complejidad temporal O(1).

### Resumen de la solución
Se implementó un Caché LFU utilizando una estructura combinada. Se utiliza una tabla hash (`tabla_valores`) para almacenar los valores y frecuencias, una tabla hash de iteradores (`tabla_claves`) para acceso directo a los nodos, y un mapa de listas doblemente enlazadas (`tabla_frecuencia`) para agrupar las llaves por su frecuencia de uso. Esto permite aislar las operaciones en tiempo constante sin recurrir a bucles de búsqueda.

### Complejidad
- Tiempo:O(1) para las operaciones `get` y `put`.
- Espacio:O(N) donde N es la capacidad máxima del caché (capacidad límite de los mapas y listas).

### Invariante o idea clave
El invariante principal es que todos los elementos con la misma frecuencia se agrupan en una misma lista doblemente enlazada. Dentro de esa lista, se mantiene un orden temporal (LRU integrado): los elementos más recientes se insertan al frente (`push_front`) y los más antiguos se acumulan al final, permitiendo su eliminación inmediata en caso de empate de frecuencias mediante `pop_back`.

### Archivos relevantes
- include/LFUCache.h
- src/LFUCache.cpp
- tests/test_lfu.cpp
- demos/demos_LFU_Cache.cpp
- benchmark/benchmark_lfu.cpp

### Compilación
Para compilar el proyecto, ejecuta los siguientes comandos desde la raíz del repositorio:
```bash
mkdir build
cd build
cmake ..
make
```

### Ejecución
```bash
./build/demo_lfu
./build/test_lfu
./build/benchmark_lfu
```

### Casos de prueba
Describe al menos 3 casos:
1. Capacidad cero: Valida que el caché rechace inserciones y no genere fallos de memoria si se inicializa con capacidad 0.

2. Empate de frecuencias: Valida que, ante caché lleno y elementos con frecuencia 1, se expulse al elemento por LRU (el más antiguo).

3. Actualización de valores: Comprueba que al hacer put sobre una llave existente, se actualice su valor, se incremente su frecuencia y se ponga primero.

### Historial de commits
El historial de los commits realizados en días distintos se evidencia en el video de sustentación.

### Declaración de autoría
Declaro que entiendo el código entregado, que puedo explicarlo, compilarlo, ejecutarlo y modificarlo sin ayuda externa durante la grabación.