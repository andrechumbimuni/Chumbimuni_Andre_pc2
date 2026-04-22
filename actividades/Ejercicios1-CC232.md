### Lista de ejercicios - Semana 1

#### Ejercicio 4. Afirmaciones con notación `O`: demostrar o refutar

Sean `f(n)` y `g(n)` funciones no negativas. Suponga que `f(n) = O(n^2)` y `g(n) = O(n)`.

##### Para cada afirmación siguiente
Indique si es siempre verdadera o no. Si es verdadera, demuéstrela; si no lo es, entrega un contraejemplo.

1. `f(n) + g(n) = O(n^2)`
2. `f(n) · g(n) = O(n^3)`
3. `f(n) / g(n) = O(n)`
4. `g(n) = O(f(n))`

Finalmente, explica brevemente por qué en notación asintótica no basta "intuir" el crecimiento, sino que se necesita una justificación formal.

Para 1:
f(n) + g(n)=O(n^2) (verdadero)
El límite f(n) es n^2 y el de g(n) es n, el término mayor (n^2) absorbe al menor.La suma C1 x n^2 + C2 x n siempre podrá ser acotada por una nueva constante(tomando el mayor de C1 y C2) por n^2.

Para 2:
f(n) · g(n) = O(n^3) (verdadero)
definimos sus cotas f(n)<=C1 x n^2 y multiplicamos por g(n)<=C2 x n resultando en f(n)g(n)<=(C1 x C2) x n^3 que tiene la forma: C3 x n^3

Para 3:
f(n) / g(n) = O(n) (Falso)
Podemos tomar f(n)=n^2 y g(n)=1 (Por contraejemplo)
n^2/1=O(n) -> n^2=O(n) -> n^2<=C1 x n -> n <=C1

Para 4:
g(n) = O(f(n)) (Falso)
Tomamos f(n)=1 y g(n)=n (Por contraejemplo)
n=O(1) -> n<= C1 

Como vemos podemos tomar diferentes formas para la forma de O porque es la cota superior pero se confunde con la forma Theta que es la ajustada por arriba y abajo por eso se tiene que aplicar teoria formalmente para demostrar afirmaciones o refutarlas. 