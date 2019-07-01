# Trabalho de comprensão de imagem

> Para buildar e utilizar o programa:  
```shell
make clean; make; ./arvore
```

> Comandos de utilização  
 - `Q` monta a árvore necessaria para toda a operação
 - `I` muda entre visualização completa da imagem e modos de comprensão
 - `J` muda entre visualizar comprensão por Nivel ou por Percentual de Erro
 - `K` diminui a quantidade de nivel ou erro
 - `L` aumenta a quantidade de nivel ou erro

## Observações:  
 - Irá quebrar se utilizar qualquer comando antes de montar a árvore
 - Veja a diferença entre a comprensão e a imagem normal com `I`
 - O percentual de erro ultrapassa 100%, já que o calculo é feito utilizando o(s) 
 pixel(s) como valor absoluto

## Organização:  
 As modificações feitas são apenas a inclusão de dois arquivos
 `Quadtree.h` e `Quadtree.c`.
 Além da adição de algumas linhas de codigo em arvore.c para conexão com a estrutura de dados criada.
 Os dados da quadtree são os fornecidos pelo professor, sem nenhuma modificação.

## arvore.c
  Contem a inclusão do quadtree.h para utilização das funções,
  além de algumas variaveis globais que são utilizadas entre as funções.  

  ```c
  TQuadtree *root = NULL;
  ```
  Raiz da árvore


  ```c
  int level = 0, max_level = 0;
  bool isErro = true;
  int max_erro = 100;
  ```
  Variaveis de controle da renderização, onde:
   - `level`, `max_level` e `isErro` fazem parte do estado da aplicação e são 
   preenchidas automaticamente enquanto manipula a imagem
   - `max_erro` pode ser modificada e diz qual será o erro maximo admitido, e assim 
   qualquer percentual de erro maior que isso terá esse valor, sendo 1 = 100%
  

  Dentro da função `desenhaArvore()` ocorre a chamada da função 
  `inNivel(TQuadtree node, int lvl, bool isErro)` do arquivo quadtree.h,
  essa função atravessa a arvore e chama a função desenha quadrante se uma 
  condição é satisfeita, a condição no caso é a arvore ter o nivel igual ao
  parametro `lvl` ou o erro menor que este mesmo parametro, sendo controlado 
  se deve ser por nivel ou por erro pelo parametro `isErro` que serve de flag.  

  Dentro da função `teclado()` tem uma pequena lógica, a qual modifica as
  variaveis globais `isErro` e `level` que são utilizadas de entrada na 
  função `inNivel()`, assim `teclado()` pode aumentar ou diminuir o valor
  da visualização(em nivel ou em erro).

  Já na função `montaArvore()` chama a função `monta()` de quadtree.h, e
  assim `monta()` analisa a imagem e monta a quadtree para ser utilizada no resto da aplicação.

## Estrutura tQuadtree e função monta

  A struct TQuadtree contem como chave o tQuadrante disponibilizado pelo professor, 
  e um vetor com 4 TQuadtrees como filhas

  ```c
  typedef struct quadtree
  {
  	tQuadrante *key_value;
  
  	struct quadtree *childs[4];
  
  } TQuadtree;
  ```

  A função monta comentada anteriormente faz a montagem da árvore sobre essa estrutura,
  de acordo a composição da imagem lida.
  No começo ela seta a variavel global `max_level` se chegar em um nivel maior 
  que o de `max_level`, após isso é feita uma iteração por todo o setor da imagem
  de acordo as coordenadas recebidas por parametro, fazendo a soma de todos os pixeis
  e guardando eles em um vetor, com a soma feita é realizada a media e uma iteração que
  realiza o calculo percentual de todos os pixeis em relação ao quadrante, retirando o
  maior percentual de erro.
  Assim é nó é criado( já sendo inserido no ponteiro passado pela função ), e caso a
  largura sejá de um pixel a função acaba já q não é necessario dividir o 
  pixel( além de causar recursão infinita e estoura a pilha de memoria ), e logo se o valor 
  da largura for maior que um pixel é possivel dividir a obter mais nós na árvore, 
  e é feita a chamada da propria função 4 vezes e com as coordenadas pela metade sendo 
  distruibuidas por 4 partes do quadrante atual.
