Mini-projeto: Analisador de Expressões Matemáticas
==================================================

http://github.com/hausen/exprtut

Sumário
-------

Este mini-projeto implementa um simples analisador de
expressões matemáticas em C.

Ele tem como objetivos:

* demonstrar como modularizar seu código, dividindo-o
  em arquivos de implementação (.c) e cabeçalho (.h)

* demonstrar o uso de Makefiles para construir automa-
  ticamente o seu projeto

Descrição
---------

Usando o algoritmo do pátio de manobras, ou
[shunting-yard algorithm] [WIK16a] (criado por
[E. W. Dijkstra] [EWD63]), podemos transformar
uma expressão matemática da notação infixa comum
(operadores entre os operandos) para a notação
posfixa ou [notação polonesa reversa] [WIK16b].

Esta implementação usa a seguinte versão do algoritmo:

    PARA CADA token na entrada FAÇA
      SE token é número ENTÃO
        insere token no topo da pilha de saída
      SE token é um operador o1 ENTÃO
        ENQUANTO existe operador o2 no topo da pilha de
                 operadores 
                 E precedência de o1 ≤ precedência de o2 FAÇA
          remove o2 do topo da pilha de operadores
          insere o2 no topo da pilha de saída
        insere token o1 no topo da pilha de operadores
      SE token é parêntese esquerdo "(" ENTÃO
        insere token no topo da pilha de operadores
      SE token é parêntese direito ")" ENTÃO
        ENQUANTO topo da pilha de operadores não é um
                 parêntese esquerdo FAÇA
          remove operador do topo da pilha de operadores
          insere operador no topo da pilha de saída
        SE pilha de operadores está vazia ENTÃO
          ERRO
        remove parêntese esquerdo da pilha de operadores
    ENQUANTO pilha de operadores não vazia FAÇA
      remove operador do topo da pilha de operadores
      SE operador é parêntese ENTÃO
        ERRO
      insere operador no topo da pilha de saída

A implementação é intencionalmente muito simples.
Apenas estão implementadas as 4 operações aritméticas
básicas, sendo que o operador '-' é sempre binário.
Além disso, o resultado da execução é meramente
uma lista de tokens que representa a expressão na
notação posfixa.

Por ser simples, é fácil adicionar funcionalidades ao
programa. Veja a seção "Exercícios."

Compilando e Executando
-----------------------

Entre no diretório `src` e execute `make`. Isto
irá compilar todos os arquivos fontes e gerará um
programa que pode ser executado, dentro do diretório,
da seguinte forma:

    ./analisador "expressão"

Exemplos
--------

    ./analisador "2 + 3"
    ./analisador "3 + 2 * 4 - 8 * 0.5"
    ./analisador "3 + 4 * 2 / ( 1 - 5 ) * 2 + 3"
    ./analisador "(2.5 + 3 * 5) / (3 - 4.8)"

Exercícios
----------

1) (2,0pt) Faça com que o analisador calcule o resultado
a partir da expressão em notação polonesa reversa.

2) (2,0pt) Implemente o operador unário `-` (como, p. ex., na
 expressão `-3`). [Dicas:] [PEG15]

* se na expressão infixa o caractere `-` aparece
  no início, é precedido por outro operador ou é
  precedido por um parêntese esquerdo, ele é unário

* o tokenizador deve distinguir entre o operador
  binário `-` e o operador unário `-`

* o operador unário `-` não pode retirar outros
  operadores da pilha, pois na expressão posfixa
  ele sempre seguirá imediatamente seu operando

* o operador unário `-` deve ter maior precedência
  que os operadores de multiplicação e divisão

3) (2,0pt) Altere o tokenizador e o parser para implementar
a operação de potenciação, usando o acento
circunflexo `^` para representá-la. Use a função `pow` de
`math.h` para implementá-la. O [pseudocódigo da versão do
algoritmo shunting-yard descrita na Wikipedia] [WIK16a]
mostra como o operador `^` deve ser tratado.

4) (2,0pt) Implemente funções básicas e constantes.
Funções: raiz quadrada (`raiz`), trigonométricas
(`sen`, `cos`, `tan`, `sec`, `csc` e `cot`),
trigonométricas inversas (`asen`, `acos`, `atan`,
`asec`, `acsc` e `acot`), exponencial com base ℯ (`exp`) e
logarítmica natural (`ln`). Constantes: `%pi` para
representar π, `%e` para o número de Euler ℯ. Use as
constantes e funções da biblioteca `math.h`.

5) (1,0pt) Permita múltiplas expressões, separadas por
ponto e vírgula (`;`) e em seguida implemente variáveis,
atribuição e cálculo de expressões envolvendo variáveis.
Variáveis são identificadores precedidos por `$`.

Exemplo: `$x = %pi / 2; sin(5*$x)` deve resultar `1`
pois sen(5π / 2) é 1.

6) (1,0pt) Implemente funções com mais de um parâmetro:
`max(num1, num2)` e `min(num1, num2)`

Exemplo: `max(2, 3)` deve resultar `3`

Licença
-------

[GNU Affero General Public License 3.0] [GNU07]
(ou superior)

[EWD63]: https://www.cs.utexas.edu/~EWD/MCReps/MR35.PDF#page=22
         "Making a translator for ALGOL 60"

[WIK16a]: https://en.wikipedia.org/wiki/Shunting-yard_algorithm
          "Shunting-yard algorithm - Wikipedia"

[WIK16b]: https://pt.wikipedia.org/wiki/Nota%C3%A7%C3%A3o_polonesa_inversa
         "Notação polonesa reversa - Wikipédia"

[PEG15]: http://wcipeg.com/wiki/Shunting_yard_algorithm#Unary_operators
         "Shunting yard algorithm - Unary operators"

[GNU07]: https://www.gnu.org/licenses/agpl-3.0.txt
         "GNU Affero General Public License 3.0"
