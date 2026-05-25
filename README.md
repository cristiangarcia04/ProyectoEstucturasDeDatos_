# Proyecto Estructuras de Datos - El Caso del Detective

## Compilar
```bash
make
```

O directamente:
```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp entidades/*.cpp datos/*.cpp juego/*.cpp -o detective_game
```

## Ejecutar
```bash
./detective_game
```

## Comandos durante la partida
- `W`: mover arriba
- `S`: mover abajo
- `A`: mover izquierda
- `D`: mover derecha
- `T`: ver pila de pistas recogidas
- `X`: usar la ultima pista de la pila
- `s` minuscula: ver Tabla Hash de sospechosos y atributos revelados
- `I`: interrogar el siguiente testigo en cola
- `Q`: rendirse

Nota: se dejo `s` minuscula para sospechosos porque `S` mayuscula ya se usa para moverse hacia abajo.
