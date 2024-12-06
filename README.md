# Projeto de Estrutura de Dados - 2º Semestre de 2024

## Objetivo do projeto - "Olha a Boa"

O projeto tem como objetivo criar um gerenciador de cartelas de bingo que interajam com o usuário simulando um sorteio de bingo onde o usuário possa escolher quantas cartelas quiser e ao passar do tempo e de interações o programa irá retornar os números sorteados para o usuário e informar se conseguiu completar uma linha ou coluna ou se está próximo de conquistar o objetivo do jogo retornando **"Olha a boa!"** quando estiver próximo de completar a cartela.

## Como funciona?

- A partir de um menu interativo o usuário pode:
    - Visualizar a cartela que está jogando;
    - Inserir o número chamado, "marcando" ele.
- Essas cartelas solicitadas serão armazenadas localmente em seu dispositivo registrando os números de cada cartela solicitada.
- As cartelas são organizadas em grades de 5x5 com 25 qudrados sendo o quadrado central o **"FREE"**. Essa é a organização oficial das cartelas:
    ```
    Coluna B: contém números de 1 a 15.
    Coluna I: contém números de 16 a 30.
    Coluna N: contém números de 31 a 45 (com o quadrado central como "FREE").
    Coluna G: contém números de 46 a 60.
    Coluna O: contém números de 61 a 75.
    ```
    _Obs: cada número nas colunas é selecionado de forma aleatória dentro de seu intervalo pré-definido, garantindo que não haja repetição._

- Marcando as cartelas e completando 5 quadrados da coluna o programa aparece a mensagem "COLUNA" e caso complete a linha "LINHA".
- Completando a cartela o programa aparece a mensagem **"BINGO"**, e faltando apenas 1 número aparece a mensagem **"Olha a boa!"**.
- O programa irá informar quais números foram chamados.
- Todas as cartelas estarão sendo armazenadas em arquivos de texto (.txt) em arquivos separados localmente em seu dispositivo.

## Como rodar o projeto na sua máquina:

Para preparar o ambiente basta ter as depêndencias necessárias instaladas para compilar e rodar programas em C++, você pode utilizar o compliador da microsoft [VIsual Studio](https://visualstudio.microsoft.com/pt-br/vs/features/cplusplus/), o compilador [Dev C++](https://www.bloodshed.net/) ou utilizando o [Visual Studio Code](https://code.visualstudio.com/) e instalando os pacotes e compiladores nativos disponíveis.

_Obs: Se estiver no Visual Studio (code ou o desktop) procure um ícone de botão play e clique para rodar o programa._

### Se assim como eu estiver utilizando uma distro linux, pode utilizar os seguintes comandos:

**1º Instalar o compilador:**

```
sudo apt install build-essential
```

**2º Na pasta onde se encontra o programa executar o seguinte comando:**

```    
g++ -g *.cpp -o programa
```
**3º Rodar o programa, execute o seguinte comando:**

```
./programa
```

### Instalando e configurando o Valgrind

Para realizar os testes de vazamento de memória (leaks memory) você pode utilizar o valgrind se estiver em uma distro linux ou em um WSL.

**Comandos de instalação:**

```
wget https://sourceware.org/pub/valgrind/valgrind-3.24.0.tar.bz2
tar xvf valgrind-3.24.0.tar.bz2
cd valgrind-3.24.0.tar.bz2
./configure
make
sudo make install
```
Após isso o ambiente estará configurado, basta compilar o arquivo desejado e rodar o comando. No meu caso utilizarei para o arquivo BingoManager.cpp:

```
g++ -g main.cpp BingoManager.cpp -o programa
```
A tag '-g' é essencial para que o valgrind identifique o arquivo a ser testado.

Após compilar rode:

```
valgrind --leak-check=full ./programa
```

No meu caso, fiz algumas interações no programa e este foi o retorno:
```
==75564== HEAP SUMMARY:
==75564==     in use at exit: 0 bytes in 0 blocks
==75564==   total heap usage: 46 allocs, 46 frees, 91,089 bytes allocated
==75564== 
==75564== All heap blocks were freed -- no leaks are possible
==75564== 
==75564== For lists of detected and suppressed errors, rerun with: -s
==75564== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
- **HEAP SUMMARY:**

```
in use at exit: 0 bytes in 0 blocks
total heap usage: 46 allocs, 46 frees, 91,089 bytes allocated
```

**"in use at exit: 0 bytes in 0 blocks":** Isso significa que no momento da execução final, não há memória alocada, ou seja, a memória foi completamente liberada.
**"total heap usage: 46 allocs, 46 frees, 91,089 bytes allocated":** O programa fez 46 alocações e 46 liberações de memória no total, alocando 91,089 bytes no processo. O número de alocações e liberações sendo iguais indica que toda a memória alocada foi corretamente liberada.

**All heap blocks were freed -- no leaks are possible**: Isso confirma que não houve leaks. Todos os blocos de memória que foram alocados durante a execução do programa foram devidamente liberados.

- **ERROR SUMMARY:**
```
ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
Isso significa que não houve erros de memória detectados durante a execução do programa (como acessos inválidos à memória, vazamentos, etc.).
