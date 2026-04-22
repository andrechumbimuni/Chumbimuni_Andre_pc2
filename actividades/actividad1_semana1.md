# Actividad 1 - Semana 1

**Integrantes:**
1. Axel Alberto Reyes Baldeón 
2. Andre Dylan Chumbimuni Ricci

## Bloque 1 - Núcleo conceptual de Semana1
---
### 1. Diferencia entre problema, algoritmo, ADT e implementación

* **Problema:** Es simplemente la tarea que queremos resolver (ej. "tengo estos números desordenados, ordénalos"). Es el *qué* hay que hacer.

* **Algoritmo:** Es la secuencia lógica, finita y paso a paso para resolver ese problema, independientemente del lenguaje de programación. Define el *cómo* a nivel conceptual.

* **ADT (Tipo de Dato Abstracto):** Define el comportamiento de los datos desde el punto de vista de quien los usa. Especifica qué operaciones se pueden hacer (ej. `add()`, `remove()`) sin revelar cómo funcionan internamente.


* **Implementación:** Es el código real. Es cuando agarras la estrategia (algoritmo) y el contrato (ADT) y te pones a escribir el código en C++ usando memoria real, punteros y arreglos.

### 2. Observable que conecta correctitud y costo en `bubble_sort.cpp`

El punto clave aquí es darnos cuenta de si el arreglo ya se ordenó antes de tiempo. Para eso observamos si hubo intercambios (el booleano `changed` en la función `bubblePass` o la variable `lastSwapIndex` en la versión optimizada).

* **Correctitud:** Si el algoritmo da una pasada completa por el arreglo y la variable nos dice que nadie cambió de lugar, significa que el orden local ya es perfecto. (`changed == false`), sabemos que el orden local ya cumple con el orden global; es decir, el invariante se ha cumplido y el arreglo ya está matemáticamente ordenado.

* **Costo:** Al observar esta variable, el algoritmo `bubbleSortOptimized` puede abortar el ciclo prematuramente o reducir el rango de evaluación (saltando a `lastSwapIndex`). Esto conecta el saber que el estado es "correcto" con un ahorro directo en el "costo" computacional, evitando iteraciones y comparaciones inútiles en el peor caso.

### 3. Por qué `power` mejora la versión ingenua en `power.cpp`

La versión ingenua (`powerBF`) realiza multiplicaciones sucesivas de uno en uno, lo que significa que su costo temporal crece de forma lineal respecto al exponente `n`. 
Ejemplo : Si `n` es un millón, hará un millón de iteraciones.

La versión optimizada (`power`) utiliza una estrategia matemática de exponenciación binaria usando operaciones a nivel de bits (como `n >>= 1` para dividir el exponente a la mitad y `n & 1` para verificar si es impar). Al elevar la base al cuadrado (`p *= p`) en cada paso, el problema se divide a la mitad en cada ciclo. Esto reduce el costo temporal de lineal a logarítmico, siendo abismalmente más eficiente para exponentes grandes.

### 4. Correctitud vs. mala elección práctica en `fibonacci.cpp`

La versión recursiva pura (`fib(n)`) es totalmente correcta porque es una traducción literal de la fórmula matemática de Fibonacci. Sin embargo, es una pésima elección práctica porque genera un árbol de llamadas recursivas masivo donde resuelve los mismos subproblemas una y otra vez.

El tiempo que tarda explota de forma exponencial y nos vamos a quedar sin memoria rápido (Stack Overflow). En la vida real, lo mejor es usar la versión iterativa o una que guarde el estado (prev), porque te dan la misma respuesta correcta pero pasando una sola vez (tiempo lineal).

### 5. El tamaño de entrada vs. valor numérico en `count_ones.cpp`

En algoritmos orientados a bits, el "tamaño de la entrada" que afecta el costo no es la magnitud del valor de `n` (por ejemplo, si vale 10 o 1,000,000), sino la cantidad de espacio (bits) que requiere el modelo RAM para representarlo.

En `countOnes1`, la operación `n &= (n - 1)` limpia el bit encendido más a la derecha en cada iteración. Por lo tanto, el ciclo `while` se ejecuta exactamente la misma cantidad de veces que "unos" haya en su representación binaria, no en base al valor numérico total. El costo depende de la estructura del dato binario, acotado por el tamaño en bits del tipo `unsigned int`.

### 6. Por qué una interfaz convive con distintas representaciones en `demo_adt_secuencia.cpp`

Esto funciona por el concepto del "contrato" en el ADT. La interfaz IntSequence es ese contrato público: te asegura que puedes usar funciones como size, get o add.

Como el código principal (el cliente) solo interactúa con ese contrato, no le importa si por debajo (en la representación interna) estás usando un arreglo estático con límite de tamaño (FixedArraySequence) o un vector dinámico que crece solo (VectorSequence). 

Es util porque podemos cambiar todo el motor por debajo para hacerlo más rápido, y no vas a romper el resto del código que dependía de esa interfaz.


## Bloque 2 - Demos y trazado guiado

### TABLA DE ANÁLISIS

| Archivo               | Salida u observable importante                                                   | Idea algorítmica                                                                                                                   | Argumento de costo                                                                                                                                    |
| --------------------- | -------------------------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------- |
| `demo_bubblesort.cpp` | Contadores de comparaciones, intercambios y el índice del último intercambio     | Comparar adyacentes y hacer flotar el mayor, optimizando al reducir el rango de búsqueda usando la posición del último intercambio | El conteo de operaciones en la terminal indica si el caso fue el peor(O n²) o mejor(O n).                                                             |
| `demo_power.cpp`      | Tiempos de ejecución y número de pasos entre las diferentes versiones            | Reducir el exponente a la mitad en cada paso usando operaciones de bits(«1) usando la recursividad.                                | Muestra la diferencia entre un crecimiento lineal (O n) y uno logarítmico (menos pasos).                                                              |
| `demo_fibonacci.cpp`  | Tiempos de ejecución de la recursiva clásica contra la iterativa                 | La iterativa construye los valores progresivamente, la recursiva clásica hace call stack recalculando subproblemas (repetidos)     | la versión recursiva colapsa por su costo exponencial (recalculo), mientras la iterativa se mantiene estable (O n)                                    |
| `demo_countones.cpp`  | Cantidad de bits encendidos calculados mediante desplazamientos (forma binaria). | Utiliza máscaras y desplazamientos para sumar los bits en paralelo; suma en bloques (2, 4 ..)                                      | El costo temporal es O log b (cantidad de bits) teóricamente. en la práctica el tiempo es O 1, ya que se resolverá en exactamente 5 operaciones fijas |

### RESPUESTAS A LAS PREGUNTAS

* La impresión de las variables que cuentan las comparaciones y los intercambios.

* Mostrar el arreglo ordenado al final solo demuestra que el algoritmo es correcto, ademas las comparaciones disminuye drásticamente en un arreglo casi ordenado siendo prueba de que la optimización reduce el costo de operaciones.

* Para hallar el exponente de 1000, la fuerza bruta hará un 1000 pasos, mientras que la optimizada lo hará en 10 divisiones.

* La diferencia entre `fibI` y `fib`, si queremos hallar el fibonacci de 20, la versión recursiva se queda calculando por muchísimo tiempo debido a la redundancia, mientras que la iterativa te da la respuesta en milisegundos.

* Usar 1048576(2²⁰) es un valor grande, pero en representación binaria es simplemente un 1 seguido de 20 ceros. El programa terminará rapido dejando claro que el esfuerzo del algoritmo depende del tamaño en bits.


## Bloque 3 - Pruebas públicas y Sustentación

**1. ¿Qué funciones o ideas están verificando las pruebas públicas?**

Al revisar `test_public_week1.cpp` y `test_public_week1_extra.cpp`, las pruebas están verificando el comportamiento mínimo esperado y casos borde de los algoritmos implementados. Específicamente validan:

* **Casos base y extremos:** Arreglos vacíos (tamaño 0) para sumas o exponentes 0 en conteos de bits.

* **Correctitud en recursión e iteración:** Que ambas versiones de una misma idea matemática (Suma, Potencias, Fibonacci) den el mismo resultado.

* **Comportamiento de ADTs y modificaciones:** Que funciones como `bubbleSortOptimized`, `reverseRecursive` y `shiftLeftByK` realmente alteren el arreglo al estado esperado (ordenado, invertido o desplazado).

* **Propiedades específicas:** Que la Torre de Hanoi ejecute exactamente el número de movimientos matemáticamente esperados.

**2. ¿Qué sí demuestra una prueba pública?**

Demuestra que el código compila correctamente, que no sufre caídas abruptas (como un error de segmentación por acceder mal a la memoria) bajo esas condiciones exactas, y que, para los casos específicos introducidos por el profesor, el programa genera la salida esperada. Es una validación de presencia de comportamiento esperado en un escenario controlado.

**3. ¿Qué no demuestra una prueba pública?**

**No demuestra la correctitud universal del algoritmo.** 

Una prueba pública no evalúa los infinitos tamaños de entrada posibles, no asegura que el algoritmo sea eficiente (podría pasar la prueba pero tardar horas con un millón de datos), ni garantiza que no vaya a ocurrir un desbordamiento de memoria (Stack Overflow) con casos degenerados o muy grandes que no se incluyeron en el test.

**4. Pregunta de sustentación (Sección 1: Concepto formal de algoritmo)**

### 4. Concepto formal de algoritmo

**4.1. ¿Qué es un algoritmo y qué condiciones debe cumplir para ser considerado correcto y útil?**

Un algoritmo es una secuencia finita, rigurosa y ordenada de pasos lógicos diseñados para resolver un problema específico. 

* Para ser considerado correcto, debe garantizar que, dada cualquier entrada válida, el proceso terminará y producirá exactamente la salida esperada (cumple con su especificación matemática/lógica). 

* Para ser considerado útil (o tratable), debe resolver el problema utilizando una cantidad razonable de recursos computacionales (tiempo de procesamiento y memoria). Un algoritmo correcto que tarda milenios en ejecutarse no es útil en la práctica.

**4.2. Explica con tus palabras las nociones de:**

* **Entrada:** Son los datos iniciales que recibe el algoritmo antes de empezar a trabajar.

* **Salida:** Es el resultado final que entrega el algoritmo una vez que ha terminado de procesar la entrada.

* **Determinismo:** Significa que el algoritmo no tiene ambigüedades ni deja nada al azar. Si le das exactamente la misma entrada cien veces, ejecutará exactamente los mismos pasos y te devolverá la misma salida las cien veces.

* **Factibilidad:** Cada paso del algoritmo debe ser lo suficientemente básico como para que una computadora pueda ejecutarlo en la realidad con recursos físicos posibles.

* **Finitud:** Debe tener un final garantizado después de un número específico de pasos.

* **Corrección:** Es la garantía de que el algoritmo hace exactamente lo que promete hacer. La salida obtenida coincide al 100% con la salida teórica que exige el problema.

**4.3. Da un ejemplo de procedimiento que no califique como algoritmo y explica por qué.**

Un ejemplo clásico es el procedimiento: *"Escribe todos los números pares que existen y luego suma 1"*. O en código, un bucle como `while(true) { imprimir("Hola"); }`.

**¿Por qué no es un algoritmo?** 
Porque viola el principio de finitud,los números pares son infinitos.

**4.4. ¿Por qué la corrección por sí sola no basta para considerar bueno a un algoritmo?**

Porque un algoritmo puede dar el resultado correcto pero ser ineficiente como consumir muchos recursos.

Como vimos con la versión recursiva pura de Fibonacci (`fib(n)`), el código es matemáticamente correcto, pero su costo temporal crece de manera exponencial. Si le pides calcular un número medianamente grande, la computadora se quedará sin memoria o tardará años en terminar.

**4.5. ¿Qué relación hay entre especificación e implementación?**

* La especificación define el "qué" debe hacer el programa (el problema, la entrada esperada, la salida prometida y los casos borde).

* La implementación es la construcción física. Define el "cómo" se logra (el código en C++, el manejo de memoria, las variables, los bucles). 

Usando un ejemplo mas visual la especificación es el contrato; la implementación es el trabajo real para cumplir ese contrato.


**5. Autoevaluación basada en la rúbrica**

* **Comprensión conceptual:** **[Logrado]**. Hemos definido con claridad la diferencia teórica y práctica entre problema, algoritmo, correctitud y eficiencia, distinguiendo por qué "funcionar" no es lo mismo que ser tratable.

* **Sustentación de correctitud:** **[Logrado]**. Hemos justificado que la correctitud no se prueba solo empíricamente (pasando un `test_public`), sino entendiendo las invariantes (como el orden local en bubblesort) y el avance seguro hacia un caso base.

* **Análisis de eficiencia:** **[Logrado]**. Hemos relacionado el costo temporal con los métodos de la semana, identificando cómo optimizaciones asintóticas (ej. dividir el problema en la función `power` o usar programación iterativa en `fib`) salvan al programa de tiempos de ejecución inviables.



## Bloque 4 - Puente corto con Proyecto0

**1. ¿Qué diferencia observable deja `demo_const_refs.cpp` entre lectura, modificación y copia?**

La salida demuestra cómo se comporta la memoria al llamar a las funciones:

* **Lectura (`sum_readonly`):** No altera el vector; la salida muestra que el vector no se altera.
* **Modificación (`append_in_place`):** Muestra que el vector fue alterado directamente, añadiéndole el 4 (`push_back`).
* **Copia (`appended_copy`):** Al imprimir "original" se ve que no cambio, al imprimir "copia", vemos que el 99 fue agregado allí.

**2. En `bench_vector_growth.cpp`, ¿qué cambia con `reserve`?**

* El tiempo de ejecución La función `push_with_reserve` es más rapida porque se solicita el tamaño de memorra al inicio llenando mucho mas rapido que si usaras la funcion `push_without_reserve` que nace con capacidad de 0 al inicio.

**3. En `bench_vector_ops.cpp`, ¿por qué `push_back`, `insert(begin())` e `insert(middle)` no cuestan lo mismo?**

Por la forma en la que se reorganiza la memoria contigua del `std::vector`.

* `push_back` es el más rápido porque coloca el nuevo valor al final.
* `insert(begin)` es el más lento porque cada inserción empuja a todos los elementos anteriores una posición hacia la derecha en la memoria.
* `insert(middle)` solo mueve la mitad de los elementos hacia la derecha insertando el elemento en el medio.

**4. En `bench_cache_effects.cpp`, ¿qué intuición deja sobre localidad de memoria?**
Leer datos ordenados es muchísimo más rápido que leer la misma cantidad de datos desordenados o en estructuras dispersas.
* `sum_vector_sequential` es veloz porque aprovecha la localidad espacial, lee las lineas de cache(bloques) que trae de la CPU a la RAM.
* `sum_vector_random_access` es muy lento porque al leer el vector en un orden aleatorio, el procesador no encuentra el dato en caché (contiguos) y tiene que ir repetidamente a la RAM.
* `sum_list` es lento porque en una lista enlazada los nodos están esparcidos en distintas zonas de la memoria RAM, impidiendo que el procesador los agrupe eficientemente en su caché.


### Bloque 5 - Extensión breve con Ejercicios0

**1. Según `Ejercicios0.md`, ¿cuál es el orden correcto antes de optimizar?**

El documento establece una metodología técnica estricta de cuatro pasos:

- Elegir el algoritmo y la estructura de datos adecuados
- Verificar que la lógica del programa sea correcta
- Medir el rendimiento inicial con datos reales
- Explorar optimizaciones avanzadas del compilador

La premisa es que el microajuste nunca debe reemplazar al buen diseño algorítmico.

**2. ¿Qué quiere mostrar `stl_optimizacion_demostracion.cpp` con `reserve`, `nth_element`, `partial_sort` y `lower_bound`?**

El objetivo principal es demostrar que el algoritmo correcto gana más que el microajuste. 

Demuestra objetivamente que elegir la función correcta de la biblioteca estándar (STL) tiene un impacto mucho mayor en la eficiencia que cualquier optimización de bajo nivel.

* `reserve()`:  Es como avisarle a la memoria: "Oye, voy a guardar 1000 cosas, guárdame espacio de una vez". Evita el costo computacional de pedir memoria y copiar datos repetidas veces cuando un vector crece.

* `nth_element()`: Permite hallar la mediana o el k-ésimo elemento en tiempo promedio $O(n)$, evitando el costo innecesario $O(n \log n)$ de un `sort()` completo.

* `partial_sort()`: Es más eficiente para obtener el Top-K sin ordenar la lista entera.

* `lower_bound()`: Aprovecha vectores previamente ordenados para hacer búsquedas
binarias ultrarrápidas en $O(\log n)$, aplastando el rendimiento de la búsqueda lineal.

**3. ¿Qué tipo de evidencia puede producir `resolver_ejercicios0_v4.2.sh`?**

El script produce **evidencia empírica integral y automatizada**. Al ejecutarlo, compila y mide múltiples variantes, produciendo:

- Tiempos de ejecución en segundos (usando el comando `time`)
- Tamaño físico de los ejecutables en bytes
- Conteo de advertencias (warnings) del compilador
- Reportes de cobertura de código y condiciones (`gcov`)
- Trazas de sanitizers (ASan, UBSan, TSan) revelando errores de memoria y data races
- Un archivo resumen consolidado (`reporte_ejercicios0.md`)

**4. ¿Qué limitaciones de entorno menciona `INSTRUCCIONES_Ejercicios0_v4.2.md`?**

El documento advierte que los usuarios de Windows (usando Git Bash o MSYS2) pueden enfrentarse a serios problemas de compatibilidad.

Si intentas usar los sanitizers (que revisan la memoria) o el profiler (que revisa el rendimiento), puede que no enganchen bien o tiren error.

Para mitigar esto, recomienda usar el entorno UCRT64 para compilaciones normales y WSL Ubuntu o Linux nativo para aprovechar plenamente los sanitizers y el profiling.

**5. ¿Por qué esta parte no reemplaza la discusión de correctitud de Semana1?**

Porque evalúan dimensiones totalmente distintas del software. Las pruebas de este bloque (tiempos, uso de STL, cobertura) solo miden el rendimiento físico y el comportamiento empírico frente a casos de prueba limitados. 

Una prueba puede indicar que el código se ejecuta en 1 milisegundo, pero eso no garantiza que la respuesta sea matemáticamente correcta para todos los escenarios posibles. La Semana 1 provee las herramientas lógicas (como invariantes y casos base) para asegurar que el algoritmo es infalible; este bloque solo se encarga de medir su eficiencia física.


## Bloque 6

En la primera semana el objetivo era responder a la pregunta "¿El código hace lo que debe hacer?", mientras que con evidencia experimental respondemos "¿Cómo interactúa este código con el hardware real bajo estrés?".

* **Afirmación de especificación:** La especificación deja de ser el objetivo final y se convierte únicamente en el contrato base. Múltiples implementaciones pueden cumplir con la misma especificación de entrada/salida, pero tener comportamientos físicos distintos.

* **Afirmación de correctitud:** Producir el resultado correcto para cualquier entrada ya no es la meta sino el requisito mínimo. Un código mal programado simplemente queda descalificado antes de siquiera entrar a un benchmark.

* **Afirmación de costo:** La complejidad teórica clásica puede ser engañosa, dos algoritmos O(n) pueden tener tiempos de ejecución abismalmente diferentes debido a constantes ocultas y latencias del hardware.

* **Afirmación de representación o memoria:** La eficiencia de la memoria no depende la capacidad usamos, sino de como la estructuramos. Una representación de memoria contigua aprovecha la localidad espacial, mientras que una representación fragmentada destruye el rendimiento.

* **Advertencia metodológica:** Nunca se debe confiar en una sola medición simple. Es obligatorio diseñar pruebas que midan el movimiento de datos; engañar a los optimizadores del compilador para evitar que eliminen el código que intentamos medir.

