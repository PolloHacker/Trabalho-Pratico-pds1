# Trabalho Pratico pds1

## Descrição

Este projeto é um trabalho prático da disciplina de PDS1 (Programação E Desenvolvimento de Software 1) do curso de Ciência de Dados da Universidade Federal de Minas Gerais.

É um simulador de batalha de Pokemons escrito em C. O usuário pode especificar um arquivo contendo os dados das equipes e o programa irá simular uma batalha entre eles. Este também registrará todos os eventos da batalha em um arquivo.

## Instalação e uso

Para usar este projeto, siga os passos abaixo:

1. Clone o repositório para sua máquina local.

    ```bash
    git clone https://github.com/PolloHacker/Trabalho-Pratico-pds1.git
    ```

2. Compile o código usando o seu compilador preferido.

    - Usando o compilador GCC

        ```bash
        gcc -W -Wall -Werror main.c file_utils.c pok_utils.c -o main
        ```

    - Usando CMake e Makefile

        ```bash
        mkdir build
        cd build
        cmake ..
        make
        ```

        Caso a compilação resulte em erro, opte pelo compilador GCC e abra um *issue* no repositório.

3. Execute o programa gerado.

    ```bash
    ./tp_pds1.<extensão> <input_file>.txt
    ```

    Se nenhum arquivo de entrada for especificado, o programa irá usar o arquivo `input.txt` como a entrada de dados.
    A estrutura do arquivo de entrada deve ser a seguinte:

    ```C
    3 2 // número de pokemons em cada equipe
    Squirtle 10 15 15 agua // os status de cada pokemon: nome ataque defesa tipo
    Vulpix 15 15 15 fogo // repita para cada pokemon
    Onix 5 20 20 pedra
    Golem 20 5 10 pedra
    Charmander 20 15 12 fogo
    ```

## Licença

Este projeto está licenciado sob [MIT License](LICENSE).
