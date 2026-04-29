## Actividad 2-CC232

### Integrantes
Andre Dylan Chumbimuni Ricci

#### Bloque 1 - Núcleo conceptual de la semana

1. Expliquen con sus palabras qué significa que un arreglo use **memoria contigua**.

Los datos se almacenan físicamente uno al lado del otro en la memoria RAM. Si tienes la dirección física del primer elemento, todos los demás forman un bloque continuo ininterrumpido.

2. Expliquen por qué acceder a `A[i]` es una operación de costo `O(1)`.

El procesador no necesita buscar ni recorrer la estructura. Toma la dirección base de la memoria del arreglo y le suma el índice multiplicado por el tamaño en bytes del tipo de dato. Es un salto de memoria calculado instantáneamente.

3. Expliquen la diferencia entre `size` y `capacity`.

Size (tamaño): Indica cuántos elementos reales y válidos están guardados actualmente en la secuencia.

Capacity (capacidad): Indica cuántos "huecos" de memoria se reservaron en total en el bloque actual.

4. Expliquen por qué un arreglo dinámico no puede crecer "en el mismo sitio" y necesita reservar un bloque nuevo al hacer `resize()`.

Un arreglo no puede simplemente expandirse hacia la derecha porque la memoria contigua que le sigue podría estar ya asignada a otra variable, programa o al SO. Como no se pueden sobrescribir datos ajenos ni "empujarlos".

5. Expliquen por qué duplicar capacidad permite defender costo amortizado `O(1)` para inserciones al final.

El algoritmo garantiza que quedará espacio libre suficiente para realizar al menos n inserciones nuevas de costo puramente constante. Si repartimos el costo pesado de la copia entre todas esas inserciones baratas garantizadas, el promedio matemático de la operación es constante, es decir, O(1) amortizado.

6. Comparen `ArrayStack` y `DengVector`: ¿qué comparten y qué cambia en interfaz o intención didáctica?

Comparten: ambos manejan un arreglo dinámico, la separación capacidad/tamaño y la lógica de redimensionamiento.
ArrayStack se diseña como una implementación básica de la interfaz abstracta List.
DengVector emula la semántica de la biblioteca estándar (std::vector), gestiona exhaustivamente la copia de memoria (constructores, asignaciones profundas) e introduce operaciones específicas como búsqueda lineal algorítmica, deduplicación y mezcla aleatoria.

7. Expliquen qué mejora `FastArrayStack` respecto a `ArrayStack`.

Mejora el rendimiento empírico, usa rutinas de bajo nivel de la biblioteca estándar, como std::copy. Asintóticamente sigue siendo O(n), pero reduce el tiempo porque estas funciones están altamente optimizadas para interactuar con la arquitectura del hardware y mover bloques enteros de memoria de golpe.

8. Expliquen cuál es la idea espacial central de `RootishArrayStack`.

Su objetivo central es reducir el desperdicio drástico de memoria de los arreglos dinámicos. En un ArrayStack normal, puedes llegar a desperdiciar la mitad del arreglo vacío. RootishArrayStack rompe el bloque único y organiza los datos en múltiples arreglos o "bloques", logrando que la cantidad de espacio vacío nunca supere un valor mínimo proporcional a $\sqrt{n}$.

9. Expliquen por qué `RootishArrayStack` usa bloques de tamaños `1, 2, 3, ...`.

Se utilizan bloques de tamaños progresivamente mayores para poder mantener la matemática del acceso aleatorio rápido. Calcular instantáneamente en qué bloque y en qué índice interno exacto se encuentra el elemento que buscas.

10. Expliquen qué relación hay entre representación, costo temporal y desperdicio espacial en estas estructuras.

Para tener un costo temporal inmejorable de lectura, estás obligado a usar una representación geométrica rígida. Para volver a abaratar esas modificaciones temporales, adoptamos políticas de redimensionamiento, circularidad o bloques, lo que nos exige tolerar y administrar intencionalmente un mayor nivel de desperdicio espacial.

#### Bloque 2 - Demostración y trazado guiado

| Archivo | Salida u observable importante | Idea estructural | Argumento de costo o espacio |
|:-|:-|:-|:-|
|`demo_array_basico.cpp` | Muestra el contenido y `length` antes y después de `b = a`. | Tamaño fijo (wrapper básico). | La asignación transfiere la propiedad para ahorrar tiempo. |
|`demo_arraystack.cpp` | Imprime el `size` y cómo cambian los elementos al insertar/eliminar. | Estructura de lista respaldada por un arreglo dinámico. | El costo depende implícitamente de la posición modificada. |
|`demo_arraystack_explicado.cpp` | Imprime mensajes sobre los desplazamientos a la izquierda/derecha. | Expone la mecánica interna del arreglo al insertar/eliminar. | Costo `O(n-i)` explícito en `add(i,x)` y `remove(i)` por el movimiento de elementos. |
|`demo_fastarraystack.cpp` |Insertando en medio y al final. | Reemplaza bucles manuales por `std::copy` y `std::copy_backward`. | Mejora el costo constante moviendo bloques de memoria enteros. |
|`demo_rootisharraystack.cpp` | Muestra inserción y eliminación sin exponer la estructura interna. | Secuencia de arreglos de tamaños crecientes. | Reduce el desperdicio de memoria asociado. |
|`demo_rootisharraystack_explicado.cpp` | Imprime: `índice lógico -> bloque, offset`. | Detalla la matemática de ubicación en bloques progresivos. | El espacio desperdiciado es proporcional a la raíz cuadrada de `n`. |
|`demo_deng_vector.cpp`|Imprime `size` y `capacity` paso a paso. | Vector dinámico clásico con variables de estado. | El crecimiento exponencial de `capacity` garantiza tiempo constante (amortizado). |
|`demo_stl_vector_contraste.cpp` | Imprime `size` y `capacity` usando `std::vector`. | Implementación estándar de la biblioteca de C++. | Crece de manera idéntica al `DengVector`, justificando el análisis amortizado. |


1. En `demo_array_basico.cpp`, ¿qué deja claro sobre arreglo, longitud y asignación?

EL arreglo es de longitud fija (su instanciación a(5)). La asignación b=a no realiza una copia profunda de "a", solo transfiere la memoria (ownership), dejando al arreglo "a" vacío o inutilizado y transfiere todo al nuevo arreglo b.

2. En `demo_arraystack_explicado.cpp`, ¿qué operación muestra mejor el costo por desplazamientos?
esplazamientos?

add y remove (desplaza elementos hacia la derecha desde la posición i hasta n-1, y remove(i) hace lo inverso desplazando hacia la izquierda desde i+1 hasta n-1).

3. En `demo_fastarraystack.cpp`, ¿qué cambia en la implementación aunque no cambie la complejidad asintótica?

Aunque la complejidad asintótica es O(n-i), la implementación sustituye los bucles for por funciones optimizadas:
Usa std::copy_backward en la operación add (para desplazar el bloque hacia la derecha), usa std::copy en la operación remove(desplazar el bloque hacia la izquierda).
Este cambio permite realizar manipulaciones de bloques de memoria a bajo nivel, lo que reduce drásticamente el factor constante del tiempo de ejecución en la práctica.

4. En `demo_rootisharraystack_explicado.cpp`, ¿qué ejemplo explica mejor el mapeo de índice lógico a bloque y offset?

La función print_location al ejecutarla, se imprime en consola cómo un [bloque, offset], se demuestra cómo la estructura ubica elementos en arreglos de tamaños 1, 2, ect.

5. En `demo_deng_vector.cpp`, ¿qué observable permite defender el crecimiento de `capacity`?

El std::cout dentro del bucle for imprime size y capacity en cada inserción. Observando directamente cómo capacity se duplica cuando size lo iguala.

6. En `demo_stl_vector_contraste.cpp`, ¿qué similitud conceptual observan con `DengVector`?

Comparten el size y capacity . La estrategia de duplicación al rebasar la capacidad es basicamente la misma.

7. ¿Qué demo sirve mejor para defender **amortización** y cuál sirve mejor para defender **uso de espacio**?

Amortización: demo_deng_vector.cpp (o demo_stl_vector_contraste.cpp), ya que el la vireasignación de memoria ocurre con tan poca frecuencia que el costo promedio por inserción es O(1).
Uso de espacio: demo_rootisharraystack_explicado.cpp, ya que explica directamente cómo el uso de bloques crecientes previene el desperdicio masivo de memoria que ocurre al duplicar un arreglo dinámico grande.

#### Bloque 3-Pruebas públicas, stress y correctitud

1. ¿Qué operaciones mínimas valida la prueba pública para `ArrayStack`?

Comprueba: inserción al final (add(1)), inserción intermedia provocando desplazamiento (add(1, 99)), actualización correcta del tamaño (size() == 3), integridad del acceso tras el desplazamiento (get()), y que remove(1) devuelva el elemento correcto y ajuste el tamaño de vuelta.

2. ¿Qué operaciones mínimas valida la prueba pública para `FastArrayStack`?

Valida las inserciones al final y en medio, pero hace un énfasis crítico en probar remove(0). Eliminar en la cabeza es el "peor caso" para un arreglo contiguo.

3. ¿Qué operaciones mínimas valida la prueba pública para `RootishArrayStack`?

Verifica que el cálculo de get(4), introduce la prueba de set(4, 40) (mutación en sitio sin desplazamiento) y verifica que una eliminación (remove(2)).

4. ¿Qué sí demuestra una prueba pública sobre una estructura?

Demuestra correctitud funcional básica. Garantiza que la lógica pura de los índices, los "off-by-one errors" y los desplazamientos locales están bien programados.

5. ¿Qué no demuestra una prueba pública?

No demuestra la eficiencia asintótica ni la correctitud del manejo dinámico de memoria. Una prueba pública con 6 elementos nunca detonará múltiples redimensionamientos, no evaluará si el costo amortizado $O(1)$.

6. En `resize_stress_week2.cpp`, ¿qué comportamiento intenta estresar sobre crecimiento, reducción o estabilidad?

Crecimiento (Expand/Grow): Inserta cientos o miles de elementos, forzando a las estructuras a pedir memoria y copiar datos repetidas veces.

Reducción (Shrink): Elimina franjas masivas de datos. Esto fuerza al factor de carga a caer por debajo del límite, detonando reducciones de memoria, probando que no haya errores.

7. ¿Por qué pasar pruebas no reemplaza una explicación de invariantes y complejidad?

Porque las pruebas comprueban qué hace el programa, pero no cómo lo hace ni cuánto cuesta.
Las invariantes y la complejidad demuestran que tu diseño no solo es funcional, sino que respeta la arquitectura teórica prometida.

#### Bloque 4-Vector como puente entre teoría y código

1. ¿Qué papel cumplen `_size`, `_capacity` y `_elem`?

_size: Es la cantidad de elementos reales que el usuario ha insertado y son válidos.

_capacity: Representa la capacidad máxima actual. Es el número total de espacios de memoria que se han reservado para el arreglo antes de necesitar pedir más memoria al sistema.

_elem: Es el puntero que dirige a la dirección de memoria donde está alojado el arreglo dinámico físico.

2. ¿Cuándo debe ejecutarse `expand()`?

Solo se ejecuta cuando el vector está completamente lleno, es decir, cuando _size == _capacity. Si hay espacio disponible no hace nada. Cuando está lleno, duplica la capacidad (_capacity <<= 1) para mantener el costo amortizado $O(1)$.

3. ¿Por qué `insert(r, e)` necesita desplazar elementos?

Si quieres insertar un elemento en el índice r (en el medio o al principio del vector), necesitas hacerle "hueco". Para no perder los datos existentes, todos los elementos desde el índice r hasta el final deben ser movidos una posición hacia la derecha.

4. ¿Qué diferencia conceptual hay entre `remove(r)` y `remove(lo, hi)`?

remove(lo, hi): Elimina un elementos en bloque y desplaza los elementos restantes hacia la izquierda una sola vez. Retorna la cantidad de elementos eliminados.

remove(r): Borra un solo elemento, pero en lugar de retornar 1(cantidad), guarda temporalmente el dato y lo retorna (T e = _elem[r]), permitiendo al usuario saber qué valor fue eliminado.

5. ¿Qué evidencia de copia profunda aparece en la demo?

ods::DengVector<int> copia(v); // copia
ods::DengVector<int> asignado;
asignado = copia;     // asignación

Se modifico la copia sumándole 1 a cada elemento, y al asignado multiplicando sus elementos por 2. Al imprimir muestran secuencias numéricas totalmente diferentes. La salida en consola demuestra que cada vector tiene su propia memoria aislada.

6. ¿Por qué `traverse()` es una buena interfaz didáctica?

Porque ilustra el patrón de diseño Visitor. Enseña como desacoplar la estructura de datos de la lógica de negocio: el vector sabe cómo iterar sobre sí mismo, pero delega qué hacer con cada elemento a una función externa.

Punteros a función: void (*visit)(T&)

Funtores (Objetos función) / Plantillas: template<class VST> void traverse(VST& visit)

7. ¿Qué ventaja tiene implementar un vector propio antes de depender de `std::vector`?

Implementar uno propio te obliga a construir el motor del auto. Las ventajas son:

Gestión de memoria: Obliga a entender el uso de new[] y delete[], y cómo evitar fugas de memoria (memory leaks).
Análisis amortizado: Permite ver matemáticamente cómo la estrategia de duplicar la capacidad garantiza que la inserción cueste $O(1)$ en promedio.

#### Bloque 5 - RootishArrayStack: espacio y mapeo

1. ¿Cómo se distribuyen los elementos entre bloques?

El primer bloque (índice 0) tiene tamaño 1; el segundo bloque tiene tamaño 2 y así sucesivamente. Cuando un bloque se llena, los siguientes elementos continúan en la posición 0 del siguiente bloque.

2. ¿Por qué con `r` bloques la capacidad total es `r(r+1)/2`?

Porque el tamaño de los bloques forma la progresión aritmética $1, 2, 3, ..., $r$. La suma de los primeros $r$ números enteros consecutivos se calcula exactamente con la fórmula de Gauss: $\frac{r(r+1)}{2}$.

3. ¿Qué problema resuelve `i2b(i)`?

Resuelve el mapeo inverso (acceso directo sin iteración). Dado un índice lógico i (por ejemplo, el elemento 50 de la secuencia), la estructura necesita saber físicamente en qué bloque está. i2b(i) toma la fórmula de Gauss, calcula de forma matemática el índice.

4. ¿Qué información produce `locate(i)` en la versión explicada?

Produce una tupla o par de valores (std::pair<int, int>) que traduce la coordenada unidimensional lógica a una coordenada bidimensional física:

b: El número del bloque físico donde está el dato.

j: El desplazamiento interno u offset.

5. ¿Qué se gana en espacio frente a `ArrayStack`?

Un ArrayStack clásico puede llegar a tener un 50% de sus celdas vacías. En cambio, RootishArrayStack solo desperdicia espacio en el último bloque agregado. Como el tamaño de ese último bloque es aproximadamente $\sqrt{2n}$, el espacio máximo desperdiciado cae a O($\sqrt{n}$).

6. ¿Qué se conserva igual respecto a la interfaz?

Para el programador le sigue pareciendo un arreglo unidimensional simple de tamaño n. Las firmas de los métodos get(i), set(i, x), add(i, x) y remove(i) y sus resultados lógicos son idénticos a los de ArrayStack.

7. ¿Qué parte les parece más difícil de defender oralmente: el mapeo, el análisis espacial o el costo amortizado de `grow/shrink`?

El costo oculto de los desplazamientos en add/remove cruzando fronteras de bloques suele ser lo más difícil de defender.
Explicar el mapeo es solo aplicar álgebra, y el espacio es solo la suma de Gauss. Sin embargo, la constante temporal en la práctica puede ser considerablemente más lenta, haciendo que el trade-off requiera una justificación muy sólida.

#### Bloque 6-Refuerzo de lectura

1. ¿Qué aporta `operator[]` a la idea de vector?

Al sobrecargar los corchetes, el vector permite que el usuario acceda a los elementos con la misma sintaxis de un arreglo estático básico (V[i]), pero manteniendo toda la protección, seguridad y encapsulamiento de un ADT.

2. ¿Qué supone `find(e)` sobre igualdad entre elementos?

Como find(e) es una búsqueda secuencial, el algoritmo confía en que el elemento sabrá responder "sí" o "no" cuando se le pregunte si es idéntico a e.

3. ¿Qué muestra `traverse()` sobre procesamiento uniforme de toda la estructura?

Muestra que el vector no es un almacén pasivo, sino una estructura que facilita operaciones masivas separando responsabilidades. El vector se encarga exclusivamente de la logística de iteración, delegando a un agente externo (como un puntero a función) la lógica (qué acción específica aplicar a cada dato).

4. ¿Por qué esta lectura sirve como refuerzo natural de `DengVector` aunque no sea el centro exclusivo de la semana?

Porque actúa como la teória detrás del caso práctico del código. Cada decisión de diseño en DengVector se encuentra en este texto:

Las variables _size y _capacity nacen para gestionar la memoria dinámica.

La duplicación de capacidad en expand() se justifica aquí mediante el análisis amortizado para garantizar un rendimiento a largo plazo.

Los bucles manuales de insert y remove reflejan la tensión estructural que es el alto costo temporal que se paga por mantener la contigüidad física de la memoria.

Los constructores especiales existen para garantizar la copia profunda.

#### Bloque 7 - Cierre comparativo

**¿Qué cambia cuando pasamos de "usar un arreglo" a "diseñar una estructura dinámica basada en arreglo"?**

Pasar de simplemente "usar un arreglo" a "diseñar una estructura dinámica basada en un arreglo" significa abandonar la rigidez de un bloque de memoria estático para construir una abstracción inteligente que gestione su propio ciclo de vida y responda a las necesidades de la aplicación.

Sobre la representación: Al diseñar una estructura dinámica, la representación separa la memoria física de la secuencia lógica. Se crea un arreglo de respaldo con una capacidad y se lleva un registro del tamaño.

Sobre la correctitud: La correctitud ya no consiste únicamente en no leer fuera de los límites de la memoria. En una estructura dinámica, implica mantener y restaurar invariantes estructurales después de cada modificación.

Sobre el costo amortizado: El diseño dinámico garantiza mediante matemáticas que, al crecer multiplicativamente, este costo se diluye entre muchas operaciones baratas, logrando que el costo amortizado de mantenimiento y de inserciones al final sea $O(1)$.

Sobre el uso de espacio: El diseño dinámico acepta el clásico trade-off de la computación: se paga espacio para comprar tiempo.

Comparación entre ArrayStack, FastArrayStack y RootishArrayStack:

ArrayStack: Representa el diseño más tradicional. Emplea un solo bloque contiguo y favorece la simplicidad absoluta y la velocidad algorítmica. Su debilidad es el uso de espacio $O(n)$.

FastArrayStack: Es idéntico a ArrayStack en su representación lógica y en su gasto de espacio. Su diferencia radica en que optimiza la velocidad a nivel de hardware.

RootishArrayStack: Priorizar el uso de espacio. Reduce de forma drástica el espacio desperdiciado a solo $O(\sqrt{n})$. Sin embargo, el costo de este diseño es computacional: debe ejecutar complejas fórmulas matemáticas cada vez que necesita averiguar en qué bloque físico reside un índice lógico.


#### Autoevaluación breve
```
- Qué podemos defender con seguridad:
La teoría fundamental del trade-off (compromiso) entre tiempo y espacio. Podemos explicar por qué el acceso en memoria contigua es $O(1)$, cómo el crecimiento multiplicativo garantiza un costo amortizado $O(1)$ al final de la secuencia, y cómo RootishArrayStack altera inteligentemente la geometría para reducir el desperdicio de memoria de $O(n)$ a $O(\sqrt{n})$ usando bloques progresivos y la suma de Gauss.

- Qué todavía confundimos:
A veces cuesta separar la complejidad teórica del rendimiento real en el procesador. Puede resultar mentalmente difícil trazar paso a paso cómo un desplazamiento logra cruzar correctamente la frontera invisible entre dos bloques de distintos tamaños en un RootishArrayStack.

- Qué evidencia usaríamos en una sustentación:
Usaríamos las fórmulas implementadas en i2b(i) y locate(i) para demostrar que el mapeo matemático es constante y no iterativo. Además, utilizaríamos resize_stress_week2.cpp como prueba de que nuestra gestión dinámica (grow y shrink) no solo funciona en papel, sino que soporta miles de operaciones sin corromper la memoria, manteniendo estables los índices lógicos.
```
