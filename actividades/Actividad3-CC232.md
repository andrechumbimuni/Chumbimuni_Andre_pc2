## Actividad 3-CC232

### Integrantes

Andre Dylan Chumbimuni Ricci

#### Bloque 1 - Núcleo conceptual de la semana

1. Expliquen con sus palabras qué cambia cuando una estructura pasa de almacenamiento contiguo a almacenamiento dinámico.

Se pierde el acceso directo , ya no puedes "saltar" a una posición(el contiguo); debes "navegar" la estructura siguiendo el rastro de enlaces desde el inicio y ganas la libertad de que la estructura crezca o se encoja orgánicamente(el dinamico).

2. Expliquen la diferencia entre acceso por rango y acceso por posición o enlace.

Acceso por posición (ligado a memoria contigua): Es un mecanismo de acceso directo. Al conocer el índice, el sistema calcula su dirección exacta en memoria en tiempo constante O(1).

Acceso por enlace (ligado a memoria dinámica): Es un mecanismo de recorrido secuencial. Estás obligado a empezar desde el primer nodo (la cabeza) y seguir la cadena de referencias de uno en uno. El tiempo de acceso depende directamente de qué tan lejos esté en la secuencia.

3. Expliquen por qué una lista enlazada mejora inserciones y eliminaciones locales, pero empeora el acceso por índice.

Empeora el acceso por índice porque los nodos están dispersos y conectados por referencias, la computadora es ciega a la estructura global. Para leer el índice i, forzosamente debe recorrer secuencialmente todos los nodos anteriores, lo que eleva el costo de acceso a una complejidad de tiempo O(n).

Insertar o eliminar solo requiere "romper" y "reconectar" un par de referencias (punteros) entre los nodos vecinos. En contraste, en una estructura contigua (como un vector), insertar un dato en el medio obliga a desplazar físicamente todos los elementos posteriores hacia la derecha lo cual es costoso.

4. Expliquen por qué `SLList` implementa bien operaciones de `Stack` y `Queue`.

Una lista enlazada simple (SLList) incluye no solo un puntero head (cabeza), sino también un puntero tail (cola).

Para un Stack (LIFO): Las operaciones ocurren en un solo extremo. En SLList, push(x) inserta un nuevo nodo al inicio (apuntando al antiguo head) y pop() elimina el head actual, actualizándolo al siguiente nodo.

Para una Queue (FIFO): La operación de encolar (add(x)) se hace en tiempo O(1) simplemente conectando el nuevo nodo a tail->next y actualizando el tail. 

5. Expliquen por qué `SLList` no implementa naturalmente todas las operaciones de un `Deque` con el mismo costo.

Un Deque (Double-Ended Queue) exige que las operaciones de inserción y eliminación en ambos extremos tengan una complejidad de O(1).

Mientras que SLList puede insertar al final en O(1) (gracias al tail), eliminar en el final (pop_back) le resulta costoso. Dado que los enlaces son unidireccionales (solo apuntan a next), para eliminar el último nodo necesitarias conocer cuál es el penúltimo nodo. La única forma es recorrerla secuencialmente desde el head hasta el final, lo que degrada el costo de eliminación al final a O(n).

6. Expliquen qué aporta el nodo centinela `dummy` en `DLList`.

El nodo centinela (dummy) en la implementación de ods::DLList aporta simetría estructural y eliminación de casos borde (edge cases).

En lugar de usar punteros nulos para representar el inicio o el fin, dummy es un nodo circular donde dummy.next actúa como el head y dummy.prev como el tail lógico. Cuando la lista está vacía, dummy se apunta a sí mismo.
Esto simplifica ya que no es necesario escribir condicionales como if (head == nullptr) o if (u->next != nullptr).

7. Expliquen por qué `DLList` permite justificar `get(i)`, `set(i,x)`, `add(i,x)` y `remove(i)` con costo `O(1 + min(i, n-i))`.

En el método getNode(i), la lista no empieza a recorrer desde el principio siempre sino que evalúa la condición if (i < n / 2).

Si el índice buscado está en la primera mitad de la lista, recorre hacia adelante desde el inicio (dummy.next). En este caso, dará i pasos.

Si el índice está en la segunda mitad, recorre hacia atrás desde el final (dummy.prev). En este caso, dará n - i pasos.

El algoritmo siempre elige el camino más corto. Por tanto, el número máximo de pasos que dará es el min(i, n - i). El +1 constante representa las operaciones locales de desenlace o actualización de valores una vez que se llega al nodo.

8. Expliquen cuál es la idea espacial central de `SEList`.

La idea central de la SEList es reducir el desperdicio de memoria y mejorar la localidad espacial (cache locality).
En una lista doble tradicional (DLList), por cada elemento almacenado se gastan dos punteros extra (next y prev). La SEList soluciona esto agrupando múltiples elementos dentro de un solo nodo (una lista desenrollada o unrolled linked list). Cada nodo contiene un pequeño bloque contiguo. De este modo, los punteros next y prev van a cada bloque de elementos, amortizando drásticamente el consumo de memoria dinámica.

9. Expliquen por qué `SEList` reutiliza una `BDeque` basada en `ArrayDeque`.

Dentro de cada nodo de la SEList, los elementos se almacenan en una BDeque (Block Deque), la cual hereda de ArrayDeque.

Un ArrayDeque funciona como un arreglo circular. Esto es crucial porque, cuando la SEList inserta o elimina elementos, a menudo necesita reacomodar los datos hacia otros nodos (operaciones internas spread y gather). Al ser un ArrayDeque, el bloque permite añadir o retirar elementos por cualquiera de sus dos extremos en tiempo O(1) sin tener que desplazar físicamente todos los elementos internos.

10. Expliquen qué papel cumple `DengList` dentro de esta semana y por qué no reemplaza a las estructuras de Morin.

Las estructuras de Pat Morin (ods::DLList, ods::SEList) están diseñadas con un enfoque minimalista: se limitan exclusivamente a retener datos y proveer operaciones de acceso y mutación elementales (CRUD) con alta eficiencia.

Por el contrario, DengList representa un enfoque académico más algorítmico. Expone métodos complejos como sort(), dedup(), uniquify(), y reverse().

#### Bloque 2 - Demostración y trazado guiado

| Archivo | Salida u observable importante | Idea estructural | Argumento de costo, espacio o diseño |
| :--- | :--- | :--- | :--- |
| `demo_sllist.cpp` | `size = 3`, `peek = 5`, `pop = 5`, `remove = 10` | Lista simplemente enlazada con punteros `head` y `tail`. | Operaciones en extremos (Pila/Cola) con costo $O(1)$. No apta para borrado al final $O(N)$. |
| `demo_dllist.cpp` | `DLList: 10 20 30` | Lista doblemente enlazada con nodo centinela (`dummy`). | Navegación bidireccional en $O(1 + \min(i, n-i))$. El centinela elimina *edge cases*. |
| `demo_selist.cpp` | `SEList: 0 10 20 ... 90` | Nodos enlazados que contienen bloques contiguos (`BDeque`). | Reduce el *overhead* de punteros (ahorro espacial) y mejora la localidad de caché. |
| `demo_deng_list.cpp` | `ordenada: 5 10 20 30` | *Wrapper* o fachada que encapsula una lista para algoritmos complejos. | Abstracción de alto nivel enfocada en utilidad (ADT completo) más que en estructura base. |
| `demo_morin_deng_bridge.cpp` | `DLList reforzada... 1 2 3 4` | Patrón adaptador temporal (Puente) entre librerías. | Reutilización de código (DRY). Permite ordenar una `DLList` minimalista sin modificar su fuente. |
| `demo_min_structures.cpp` | `MinStack min=3 top=7` | Aumento de estructura con metadatos (pila/cola monótona). | Intercambia memoria adicional para lograr consulta de mínimo en tiempo constante $O(1)$. |
| `demo_linked_adapters.cpp` | Operaciones estrictas de Stack/Queue. | Adaptador de interfaz que restringe una estructura base. | Diseño seguro. Previene violaciones de política (LIFO/FIFO) ocultando métodos de acceso aleatorio. |
| `demo_contiguous_vs_linked.cpp` | Comparación de `get(4)` entre `ArrayDeque` y `DLList`. | Contraste entre memoria contigua (índices) y dinámica (enlaces). | *Trade-off*: Contiguo gana en acceso $O(1)$ y caché; Enlazado en mutación local sin desplazar memoria. |


1. En `demo_sllist.cpp`, ¿qué secuencia deja más clara la coexistencia de comportamiento tipo pila y tipo cola dentro de `SLList`?

La secuencia donde primero se inserta al final usando q.add(10) y q.add(20) (FIFO) y luego se inserta al inicio usando q.push(5) (LIFO). La estructura soporta ambas gracias a sus punteros head y tail.

2. En `demo_dllist.cpp`, ¿qué operación muestra mejor la inserción en una posición intermedia?

La ejecución de d.add(1, 20). Previamente se insertó el 10 en el índice 0 y el 30 en el índice 1. Al insertar el 20 en el índice 1, la estructura esta en el punto medio y reconecta los punteros adyacentes, desplazando el 30 sin tener que mover toda la memoria.

3. En `demo_selist.cpp`, ¿qué observable permite defender que la lista mantiene orden lógico aunque internamente trabaje por bloques?

El bucle de impresión final imprime la secuencia: 0 10 20 ... 90. Para el usuario, la estructura se comporta exactamente como una secuencia lineal. El usuario no se entera de que internamente los valores están saltando entre distintos BDeque de tamaño 3.

4. En `demo_deng_list.cpp`, ¿qué evidencia muestra que la lista reforzada por Deng ofrece operaciones más cercanas a un ADT de lista completo?

El uso directo del método lista.sort(), las estructuras minimalistas de Open Data Structures (ods) solo guardan y sacan datos. DengList asume la responsabilidad de proveer algoritmos de transformación (ordenamiento, desduplicación), comportándose como un ADT.

5. En `demo_morin_deng_bridge.cpp`, ¿qué parte de la salida permite justificar que se reutilizan algoritmos sin reescribir la estructura base?

El hecho de que logramos imprimir una DLList (estructura de Morin) totalmente ordenada y sin duplicados (1 2 3 4). Esto fue mediante funciones como stable_sort_with_deng(lista), las cuales transforman temporalmente la DLList en una DengList, la ordenan con la lógica de Deng, y la devuelven.

6. En `demo_min_structures.cpp`, ¿qué diferencia conceptual observan entre almacenar valores y almacenar información adicional para responder `min()`?

Almacenar valores representa guardar la secuencia de datos real del problema. Almacenar información adicional para responder min() representa guardar metadatos de estado operativo. Requiere mantener una estructura secundaria paralela que rastree el mínimo histórico en cada momento, pagando costo espacial para ganar velocidad de consulta.

7. En `demo_linked_adapters.cpp`, ¿qué adaptador representa mejor la idea de reutilizar una estructura existente para ofrecer una interfaz nueva?

Los tres lo hacen LinkedStack, LinkedQueue, LinkedDeque. Un adaptador toma una clase flexible y restringe sus capacidades para ofrecer una interfaz estricta ej: LinkedStack solo te deja usar push, pop y top.

8. En `demo_contiguous_vs_linked.cpp`, ¿qué contraste se observa entre acceso por índice, inserción local y localidad de memoria?

El ArrayDeque gana en el acceso por índice (get(4)) porque calcula la posición matemáticamente en O(1) y aprovecha la caché del procesador (localidad de memoria). Sin embargo, sufre al insertar en medio porque debe desplazar datos.

La DLList (enlazada) no tiene localidad de memoria (los nodos están dispersos) y debe recorrerse secuencialmente para el get(4). Pero es mejor en inserción local: una vez hallado el lugar, reconectar punteros es rapido sin desplazar bloques de memoria.

#### Bloque 3 - Pruebas públicas, stress y correctitud

1. ¿Qué operaciones mínimas valida la prueba pública para `SLList`?

Valida las operaciones de inserción y eliminación elementales: agregar al final (add), agregar al inicio (push), consultar el inicio (peek), eliminar al inicio (pop) y el control del tamaño (size).

2. ¿Qué operaciones mínimas valida la prueba pública para `DLList`?

Valida el acceso y la mutación por índice posicional. Insertar en un índice (add(i, x)), recupera datos por índice (get(i)), elimina por índice (remove(i)) y verifica que el tamaño.

3. ¿Qué operaciones mínimas valida la prueba pública para `SEList`?

Valida el comportamiento como lista indizada comprobando inserciones iniciales en bucle (add(i, x)), recuperación (get(i)), reemplazo (set(i, x)), la eliminación por índice (remove(i)) y el tamaño (size).

4. ¿Qué operaciones nuevas quedan cubiertas por `test_public_extras.cpp`?

Para SLList: recuperación del penúltimo (secondLast), inversión de enlaces (reverse).
Para DLList: rotación de la lista (rotate), validación de palíndromos (isPalindrome).
Valida el comportamiento de estructuras especiales: MinStack, MinQueue, MinDeque y la XorList.

5. ¿Qué valida específicamente `test_public_linked_adapters.cpp` sobre `LinkedStack`, `LinkedQueue` y `LinkedDeque`?

Valida sus invariantes (LIFO y FIFO). Comprueba que LinkedStack apile y desapile en el extremo (LIFO); que LinkedQueue encole por un lado y desencole por el otro (FIFO); y que LinkedDeque permita operar por ambos extremos sin romper la estructura subyacente.

6. ¿Qué demuestra `test_public_deng_bridge.cpp` sobre integración y reutilización?

Prueba que es posible tomar estructuras (DLList y SEList), inyectarles temporalmente el algorítmico de la DengList (para aplicar ordenamiento estable, desduplicación o inversión), y devolver los resultados a la estructura original sin haber modificado ni una sola línea del código fuente de Morin.

7. En `stress_selist_week3.cpp`, ¿qué comportamiento intenta estresar sobre crecimiento, borrado y mantenimiento del tamaño lógico?

Intenta forzar múltiples rutinas de reacomodo interno de los BDeque. Al agregar 500 elementos (creación de bloques). Al remover 250 elementos desde el frente (fusión y eliminación de bloques). Finalmente, al agregar 100 elementos más, verifica que la lista no colapsó y reporta el tamaño lógico (350).

8. ¿Qué sí demuestra una prueba pública sobre una estructura enlazada?

Prueba que, para algunos casos borde previstos en los assert, la lógica de enlaces no genera un error de segmentación, que los datos entran y salen en el orden esperado y que los contadores de estado operan bien.

9. ¿Qué no demuestra una prueba pública por sí sola?

No demuestra eficiencia asintótica. Una prueba puede pasar en verde si un push_back tarda un milisegundo (O(1)) o si tarda un minuto recorriendo un millón de nodos (O(n)). Tampoco demuestra el uso correcto de memoria dinámica, a menos que se corra bajo herramientas de análisis como Valgrind o AddressSanitizer.

10. ¿Por qué pasar pruebas no reemplaza una explicación de invariantes, punteros y complejidad?

Porque un código puede "funcionar" por accidente. Pasar las pruebas solo indica que el resultado coincidió con la aserción. Explicar los invariantes demuestra que entiendes la estructura; explicar los punteros demuestra que domina la manipulación de la memoria y argumentar la complejidad justifica por qué esa estructura es útil en el mundo.

#### Bloque 4 - SLList, DLList y SEList: lectura cercana del código

1. En `SLList`, ¿qué papel cumplen `head`, `tail` y `n`?

head: Mantiene la referencia al primer nodo de la lista.
tail: Mantiene la referencia al último nodo.
n: Actúa como un caché del tamaño lógico de la estructura.

2. En `SLList::push`, `pop`, `add` y `remove`, ¿qué punteros cambian exactamente?

push(x): El next del nuevo nodo se conecta al actual head. Luego, head se reasigna para apuntar a este nuevo nodo.
pop() / remove(): El puntero head se avanza al siguiente nodo (head = head->next). El nodo antiguo queda desconectado y se libera (delete).
add(x): El next del actual tail se conecta al nuevo nodo (tail->next = u). Luego, tail se desplaza al nuevo nodo.

3. Expliquen cómo funciona `secondLast()` y por qué no puede resolverse directamente con solo mirar `tail`.

secondLast() funciona comenzando en head y saltando de nodo en nodo hasta encontrar aquel cuyo enlace next es igual a tail. La estructura es asimétrica y unidireccional: un nodo sabe quién le sigue, pero sabe quién lo precede.

4. Expliquen paso a paso cómo funciona `reverse()` y por qué no necesita estructura auxiliar.

Funciona intercambiando enlaces in-place (sobre la misma memoria) a través de tres punteros en paralelo:Se inicializa prev en nulo y curr en head.Mientras curr no sea nulo, se guarda la referencia al nodo próximo en un temporal next (next = curr->next).Se voltea la flecha: curr->next pasa a apuntar hacia atrás (prev). prev asume el lugar de curr, y curr el de next.Se actualiza head = prev.No requiere estructuras auxiliares porque simplemente invierte el flujo del mapa de punteros existente en espacio extra $O(1)$.

5. Expliquen qué verifica `checkSize()` y por qué esta función ayuda a defender correctitud.

checkSize() iterar manualmente toda la lista desde head contando los nodos uno por uno y registrando el último nodo. Verifica dos invariantes, que el conteo coincida con la variable de control y que el último nodo visitado coincida con el puntero tail. Esto defiende la correctitud de la estructura al detectar si ha ocurrido corrupción de memoria, nodos perdidos, contadores desincronizados o si se ha formado un ciclo infinito por error humano.

6. En `DLList`, expliquen por qué `getNode(i)` puede empezar desde el inicio o desde el final.

Puede hacerlo gracias a la simetría de sus punteros bidireccionales (next y prev) y a que conoce su tamaño n. La función evalúa matemáticamente si el índice deseado i pertenece a la primera o a la segunda mitad. Si pertenece a la primera, inicia desde dummy.next; si no, inicia desde dummy.prev. Esto reduce la complejidad a $O(1 + \min(i, n-i))$.

7. En `DLList::addBefore`, ¿qué enlaces se actualizan y por qué el nodo centinela elimina casos borde?

Al insertar un nodo u antes de w, se actualizan cuatro enlaces: los dos propios del nodo (u->prev = w->prev y u->next = w) y los de sus vecinos inmediatos para "abrazarlo" (u->prev->next = u y u->next->prev = u).
El nodo centinela (dummy) elimina los casos borde porque garantiza la invariante de que todo nodo en la lista siempre tendrá un predecesor y un sucesor real. Si insertas al inicio de una lista vacía, el predecesor y sucesor es la propia dummy.

8. Expliquen cómo funciona `rotate(r)` sin mover los datos elemento por elemento.

rotate(r) calcula un punto de corte lógico (índice n - r). En lugar de sacar y meter datos, simplemente ubica el nodo que debe convertirse en el nuevo primero, su predecesor (que será el nuevo último), e intercambia cuatro punteros con la dummy y con los viejos extremos de la lista. Esta mueve toda una franja de la lista en una sola operación equivalente a encontrar el nodo.

9. Expliquen cómo `isPalindrome()` aprovecha la naturaleza doblemente enlazada de la estructura.

La función posiciona un puntero left en el inicio físico (dummy.next) y un puntero right en el final físico (dummy.prev). Luego, en cada iteración del ciclo, compara ambos, avanzando el left hacia adelante (->next) y el right hacia atrás (->prev) simultáneamente hasta cruzarse. Esta convergencia bidireccional es exclusiva del doble enlace.

10. En `SEList`, expliquen qué representa `Location`.

Location es una abstracción de coordenadas. Dado que la lista es un híbrido entre enlazado y contiguo, un índice no basta. Location encapsula un puntero u (que te dice "en qué bloque o nodo específico de la cadena está") y índice local j (que te indica "en qué celda específica esta el dato").

11. Expliquen qué hacen `spread()` y `gather()` y en qué situaciones aparecen.

spread(): Se invoca durante el add(i, x). Si el bloque objetivo está completamente saturado (desbordamiento) y los bloques vecinos también lo están, no hay dónde poner el dato. spread toma la data de $b$ bloques atestados y los reparte (o "esparce") a lo largo de $b+1$ bloques (inyectando un nodo nuevo a la lista).
gather(): Se invoca durante el remove(i). Si el bloque objetivo está por vaciarse peligrosamente (subdesbordamiento) y sus vecinos también están escasos, se genera desperdicio de memoria. gather toma los pocos elementos de $b$ bloques y los compacta en $b-1$ bloques (eliminando el nodo sobrante de la memoria).

12. Expliquen cómo el tamaño de bloque `b` afecta el trade-off entre acceso, actualización y uso de espacio.

El tamaño b es la "perilla de ajuste" del trade-off:
Si b es muy pequeño (ej. $b=2$), los bloques se llenan y se vacían a la menor provocación; las operaciones locales no mueven casi memoria, pero se gasta mucha sobrecarga espacial por el exceso de punteros prev/next y el acceso se hace linealmente más lento.
Si b es grande, la estructura ahorra memoria al reducir la sobrecarga de los nodos, y la velocidad de indexación aumenta mucho al operar grandes saltos en la secuencia; sin embargo, las inserciones intermedias comienzan a ser sumamente costosas porque obligan a desplazar mucha memoria contigua en las matrices interiores.

#### Bloque 5 - Adaptadores y estructuras derivadas

1. ¿Cómo reutiliza `LinkedStack` a `SLList`?

Reutiliza SLList mediante composición. LinkedStack restringe su interfaz pública para forzar una política LIFO. Mapea sus métodos a las operaciones: push(x) llama a list.push(x), pop() llama a list.pop(), y top() llama a list.peek().

2. ¿Cómo reutiliza `LinkedQueue` a `SLList`?

Usa composición para imponer una política FIFO. Aprovecha que SLList tiene referencias tanto a la cabeza como a la cola. Mapea add(x) a list.add(x) (que inserta al final en tiempo $O(1)$) y remove() a list.remove(). El método front() consulta list.peek().

3. ¿Por qué `LinkedDeque` se construye naturalmente sobre `DLList` y no sobre `SLList`?

Un Deque exige inserciones y eliminaciones en ambos extremos en tiempo $O(1)$. Si bien SLList no puede eliminar al final en tiempo constante. Para hacer un removeLast() en una SLList se debe recorrer toda la estructura. DLList puede hacer mutaciones en ambos extremos en $O(1)$.

4. En `MinStack`, ¿por qué cada entrada guarda el valor y el mínimo acumulado?

Al guardar el mínimo histórico en cada nodo (current_min), la pila "recuerda" cuál era el mínimo en el momento en que se insertó. Esto permite consultar min() en $O(1)$ sin recálculos.

5. En `MinQueue`, ¿por qué usar dos pilas permite mantener semántica FIFO y consulta de mínimo?

Es el clásico algoritmo de simular una cola con dos pilas (in_ y out_). Conocen su propio mínimo en $O(1)$.
FIFO: Los datos entran por in_. Cuando se necesita sacar un dato, se extrae de out_. Si out_ está vacía, se vacía in_ sobre out_, lo que invierte el orden (LIFO a LIFO = FIFO).
Mínimo: El mínimo global de la cola es simplemente comparar in_.min() y out_.min().

6. En `MinDeque`, ¿qué problema resuelve el rebalanceo entre `front_` y `back_`?

Resuelve el problema de la "inanición" de uno de los extremos. Imagina que insertas 100 elementos por delante (addFirst); todos irán a front_. Si luego el usuario pide un removeLast(), la pila back_ estará vacía.

7. Comparen "implementar una estructura" y "adaptar una estructura existente" usando ejemplos de este bloque.

Implementar: Implica lidiar con la gestión de memoria cruda, punteros y la invariante interna (ej. SLList y DLList haciendo new Node, ajustando next, prev, y previniendo fugas de memoria).

Adaptar: Implica tomar una estructura robusta ya hecha y usarla como "caja negra" para moldear un comportamiento (ej. LinkedStack no toca un solo puntero; solo restringe lo que el usuario puede hacer).

8. ¿Qué operaciones pueden defender como constantes y cuáles deben defender como amortizadas?

Constantes estrictas $O(1)$: Todas las operaciones de LinkedStack, LinkedQueue, LinkedDeque, y MinStack. En estas estructuras, cada llamada a un método ejecuta un número fijo de instrucciones.
Constantes amortizadas $O(1)$: Las extracciones en MinQueue (remove, front) y MinDeque (removeFirst, removeLast). Estas operaciones son baratas pero puede haber reconstrucciones totales (rebalance()) que cuestan $O(N)$. Sin embargo, garantizan $N$ operaciones de costo $O(1)$, el costo promedio por operación se "amortiza" a $O(1)$.

#### Bloque 6 - Deng como refuerzo algorítmico y puente de integración

1. ¿Qué operaciones del ADT de lista aparecen reforzadas en `DengList`?

Búsqueda avanzada: contains(x) y find_index(x).

Ordenamiento: sort() (ordenamiento estable).

Limpieza de datos: dedup() (elimina duplicados) y uniquify() (elimina duplicados consecutivos).

Mutación estructural: reverse() (invierte el orden lógico de los elementos).

2. ¿Qué ventaja tiene encapsular una lista más rica sin cambiar el resto de estructuras de Semana 3?

La principal ventaja es la separación de responsabilidades y el respeto al principio de diseño abierto/cerrado (Open/Closed Principle). Modificarlas directamente para añadir algoritmos complejos ensuciaría su código base y complicaría el análisis de sus invariantes.

3. Expliquen qué hacen `to_deng` y `assign_from_deng`.

to_deng (Exportador): Recibe una estructura base (como DLList o SEList), itera sobre sus elementos desde el índice 0 hasta el tamaño final, e inserta secuencialmente cada elemento en una nueva instancia de DengList.
assign_from_deng (Importador): Hace la operación inversa. Primero, vacía completamente la estructura destino (dst.clear()). Luego, itera sobre los elementos de la DengList de origen e inserta cada uno de vuelta en la estructura original.

4. Expliquen por qué `stable_sort_with_deng` no obliga a reimplementar ordenamiento dentro de `DLList` o `SEList`.

El ordenamiento se resuelve externamente y la estructura original solo sufre operaciones de vaciado y llenado ordenado.La función extrae los datos de DLList o SEList convirtiéndolos temporalmente a una DengList, invoca el método sort() y finalmente devuelve los datos ordenados a la estructura original (usando assign_from_deng)

5. Expliquen qué hace `dedup_with_deng` y qué relación guarda con `deduplicate()` o `uniquify()` de la teoría.

dedup_with_deng extrae los elementos a una lista temporal DengList, aplica el método de limpieza, guarda la cantidad de elementos eliminados, reasigna los elementos únicos a la lista original y retorna la cantidad de elementos removidos.

dedup() / deduplicate(): Elimina todas las ocurrencias duplicadas de un elemento a lo largo de toda la lista, independientemente de su posición(O(n²)).

uniquify(): Solo elimina duplicados consecutivos. Es altamente eficiente, requiriendo un costo de tiempo lineal O(n), pero exige que la estructura esté previamente ordenada.

6. Expliquen por qué `reverse_with_deng` es un ejemplo de reutilización de algoritmos sobre una interfaz común.

reverse_with_deng, al depender únicamente de operaciones de interfaz comunes (recorrer los elementos y volver a insertarlos) mediante el puente a DengList, logra aplicar una mutación lógica idéntica sobre dos implementaciones físicas distintas, maximizando el reciclaje de código (DRY).

7. ¿Qué costo adicional introduce la conversión entre estructuras y cuándo vale la pena aceptarlo?

Por cada puente realizado, se gasta memoria adicional O(n) para instanciar la DengList, y tiempo O(n) en las iteraciones repetidas de copiar y vaciar/repoblar datos.

Vale la pena aceptarlo cuando: La complejidad del algoritmo a ejecutar (como un ordenamiento o deduplicación exhaustiva) supera ampliamente la sobrecarga lineal de las transferencias. También es justificable cuando la prioridad del sistema es la estabilidad, seguridad y limpieza del código (evitar bugs) sobre el consumo estricto de recursos, especialmente si la cantidad de datos en memoria no es masiva.

#### Bloque 7 - Comparación enlazado vs contiguo, variantes y evidencia experimental

1. Comparen `ArrayDeque` y `LinkedDeque`: ¿qué cambia en representación y qué cambia en costo observable?

Representación: ArrayDeque se sostiene sobre un arreglo dinámico en memoria contigua, utilizando aritmética modular para conectar lógicamente el final con su principio. LinkedDeque, por su parte, se sostiene sobre una lista doblemente enlazada, dispersando sus elementos en memoria y conectándolos mediante punteros prev y next.

Costo observable: En teoría, ambas logran inserciones y eliminaciones en tiempo O(1). En la práctica, LinkedDeque paga el precio de interactuar con el sistema operativo para asignar y liberar memoria (new y delete) por cada nodo, lo que añade tiempo. ArrayDeque es mucho más rápido asintóticamente en el día a día, aunque su costo O(1) es amortizado.

2. ¿Qué significa que una representación contigua tenga mejor localidad de memoria?

La localidad de memoria significa que los datos lógicamente adyacentes también están físicamente adyacentes en la RAM. Cuando la CPU solicita leer un elemento de un ArrayDeque, no solo trae ese número, sino que arrastra un bloque entero de datos continuos hacia su memoria caché profunda. Las representaciones enlazadas obliga a la CPU a buscar en la lenta memoria RAM tras cada puntero.

3. ¿Qué tipo de operaciones favorecen más a la representación enlazada?

La representación enlazada favorece enormemente a las inserciones y eliminaciones en posiciones intermedias de la colección, siempre que tenga una referencia a dicho nodo. También es imbatible para operaciones como dividir una lista en dos, o concatenar dos listas gigantes.

4. En el benchmark, ¿qué comparación sirve mejor para discutir acceso aleatorio y cuál sirve mejor para discutir operaciones en extremos?

Para discutir acceso aleatorio: La comparación clave es t_array_random_get vs. t_linked_random_get. El arreglo lo resuelve matemáticamente en O(1), mientras que la lista doble se ve obligada a iterar desde un extremo en O(n).

Para discutir operaciones en extremos: La comparación ideal es t_array_deque_ends vs. t_linked_deque_ends. Ambas pruebas insertan repetidamente y luego consumen por ambos extremos. Servirá para demostrar el peso real en microsegundos de invocar a los asignadores de memoria (new Node) frente a simples sumas modulares.

5. ¿Por qué el benchmark no debe leerse como prueba absoluta de superioridad de una estructura sobre otra?

El benchmark está altamente condicionado por su diseño. No mide escenarios donde las listas enlazadas son superiores. Además, ignora el comportamiento de latencia en tiempo real: un sistema crítico podría preferir un LinkedDeque, en lugar de un ArrayDeque. Los resultados también variarán según el hardware local, la optimización del compilador y el tamaño de los datos elegidos.

6. ¿Qué idea intenta mostrar `XorList` respecto al ahorro de punteros?

Busca demostrar que es posible obtener todos los beneficios bidireccionales de una lista doblemente enlazada, pero consumiendo la misma cantidad de memoria que una lista simplemente enlazada. Lo logra almacenando en un solo campo (link) el resultado lógico de aplicar una compuerta XOR a nivel de bits (^) entre las direcciones del nodo anterior y el nodo siguiente.

7. ¿Qué desventaja práctica introduce una estructura como `XorList` aunque sea interesante desde el punto de vista del espacio?.

Navegación con estado: No puedes acceder a un nodo al azar, obligatoriamente necesitas conocer la dirección del nodo exacto desde el que vienes.

Inseguridad de tipos: Requiere saltarse la seguridad del lenguaje (usando reinterpret_cast exhaustivos) para tratar direcciones de memoria como enteros de cálculo.

Incompatibilidad con recolectores de basura y herramientas: Los sistemas modernos de rastreo de memoria o sanitizadores se "rompen" al no ver punteros reales.

#### Bloque 8 - Cierre comparativo y preparación de sustentación

¿Qué cambia cuando pasamos de "usar arreglos dinámicos" a "diseñar estructuras enlazadas y adaptadores sobre nodos"?

El paso de utilizar arreglos dinámicos a diseñar estructuras enlazadas y adaptadores representa que ya no pensamos en "bloques" físicos rígidos, sino en "grafos" de relaciones dinámicas.

1. La separación de la representación lógica y física

2. Acceso por posición frente a acceso por enlace (rango)

3. La agilidad de las inserciones y eliminaciones locales

4. Complejidad y evolución: SLList, DLList y SEList

5. Reutilización mediante adaptadores y puentes
Cuando pasamos a pensar en nodos, manipular punteros constantemente se vuelve propenso a errores (bugs, fugas de memoria).

6. Representación contigua vs. Enlazada
La representación contigua domina en velocidad de lectura cruda y amigabilidad con la memoria caché del procesador.
La representación enlazada arruina la localidad de caché.

#### Autoevaluación breve
    - Qué podemos defender con seguridad:
    Entendemos que un ADT define qué se puede hacer, pero no cómo se organiza en la RAM.
    Podemos argumentar sólidamente por qué un arreglo dinámico aplasta a una lista en acceso aleatorio pero pierde estrepitosamente cuando toca insertar o eliminar.
    Sabemos que es mejor "exportar" datos a una estructura rica para aplicar algoritmos complejos (sort, dedup) en lugar de ensuciar el código base de estructuras minimalistas.
    
    - Qué todavía confundimos:
    El O(1) amortizado de un arreglo dinámico y el O(1) estricto de una lista enlazada tienen impactos muy distintos en el reloj del procesador.
    Manipulación de punteros a bajo nivel: Técnicas agresivas como la de XorList todavía resultan contraintuitivas (rompen reglas de seguridad).

    - Qué evidencia usaríamos en una sustentación:
    Los resultados del Benchmark (t_array_random_get vs. t_linked_random_get): Demostrar que el acceso en memoria contigua es superior al recorrido por nodos.
    El código de t_array_deque_ends vs. t_linked_deque_ends: El asignador de memoria añade un "peso" por cada nodo, que se nota el peso en la ejecución.
    El método assign_from_deng: Reciclamos algoritmos bajo una misma interfaz.
