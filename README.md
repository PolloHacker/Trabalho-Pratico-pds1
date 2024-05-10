# Trabalho Pratico pds1

## Description

The project is a practical assignment for the course "PDS1". 

It's a Pokemon battle simulator written in C. The user can specify a file containing the data of the Pokemon teams, and the program will simulate a battle between them. The program will also log all the events of the battle in a file.

The files containing the data of the teams should have the following format:

```json
3 2 // number of pokemons in each team
Squirtle 10 15 15 agua // the pokemon stats: name atk def hp type
Vulpix 15 15 15 fogo // repeat for each pokemon
Onix 5 20 20 pedra
Golem 20 5 10 pedra
Charmander 20 15 12 fogo
```

The program will output the results of the battle and log all the events in a file called `log_DD-MM-YYYY_hh-mm-ss.txt`, with the date and time of the execution.

The user can specify the input files as command-line arguments when running the program. If no input files are specified, the program will default to using `input.txt` and `input_large.txt` as the files containing the data of the teams.

The program will also output the results of the battle to the console.

This project is part of the programming discipline "PDS1" of the course "Ciência de Dados" of the Federal University of Minas Gerais.

## Installation

To install this project, follow these steps:

1. Clone the repository to your local machine.
2. Compile the code using your preferred C compiler.

## Usage

To run the game, execute the compiled binary. You can specify the input file as a command-line argument. If no input file is specified, the game will default to using `input.txt`.

## License

This project is licensed under the [MIT License](LICENSE).
