'''
PARTE 1
El programa consta de matrices.
Primero se genera una matriz cero de i x j
Luego se genera un número determinado de números 9
Se ubica aleatoriamente los nueves a los largo de la matriz.

PARTE 2
Se modifica los valores de la matriz detectando la cantidad de 9's cercanos a cada elemento
Se reemplaza los ceros por espacios vacíos y los nueves por # en caso de estar desactivados y 9's por @ en caso de estar activados
Se oculta los valores reemplazando todos los valores por guiones
'''

from random import randint
from os import system


# global
def system_clear_console():
    system('cls')

def user_wait():
    input(' -> ')

# user input
def set_option_menu():
    '''Return the option selected by the user'''
    print()
    option = input('¿w/s/a/d - m - b/v? ').lower()
    while option != 'w' and option != 's' and option != 'a' and option != 'd' and option != 'm' and option != 'b' and option != 'v':
        print()
        print(' Opción no válida.')
        option = input(' Selecciona una opción válida (w|a|s|d|m|b|v) -> ').lower()
        print()
    return option

# menus
def menu_show_matrix(matrix: list):
    print(' ╔═', end= '')
    print('═══' * (len(matrix[0])), end= '')
    print('═╗ ')
    for row in matrix:
        print(' ║ ', end= '')
        for element in row:
            print(f'{element:^3}', end= '')
        print(' ║ ')
    print(' ╚═', end= '')
    print('═══' * (len(matrix[0])), end= '')
    print('═╝ ')

def menu_welcome():
    '''Welcome screen'''
    print('**********************************')
    print('*                                *')
    print('*           BUSCAMINAS           *')
    print('*                                *')
    print('*        w/a/s/d - moverse       *')
    print('*                                *')
    print('*           m - mostrar          *')
    print('*                                *')
    print('*     b/v - marcar/desmarcar     *')
    print('*                                *')
    print('*                                *')
    print('**********************************')
    print()
    input(" 'Enter' para empezar... ")

def menu_count_marked_mines(marked_count, total_mines):
    print(f'Minas marcadas: {marked_count:>3} de{total_mines:>3}')
    print()

# controllers
def get_zero_matrix(rows: int, cols: int, val: int | str) -> list:
    matrix = []
    for i in range(rows):
        matrix.append([val]*cols)
    return matrix

def place_mines(matrix: list, mines_count: int, val_zero: int) -> tuple[list, list]:
    mines_coordinates = []
    count = 0
    while count < mines_count:
        y = randint(0,len(matrix)-1)
        x = randint(0,len(matrix[0])-1)
        if matrix[y][x] == val_zero:
            matrix[y][x] = 9
            mines_coordinates.append((y, x))
            count += 1
    return matrix, mines_coordinates

def change_zeros_to_val(matrix, val):
    for i in range(len(matrix)):
        for j in range(len(matrix[0])):
            if matrix[i][j] == 0:
                matrix[i][j] = val
    return matrix

def set_heat_map(matrix: list) -> list:
    '''Recorre todas las scasillas vencinas, y comprueba si son ceros, si es así las descubre, y recorre las vecinas de estas, hasta encontrar casillas con pistas, que también decubre.'''
    for y in range(len(matrix)):
        for x in range(len(matrix[0])):
            if matrix[y][x] == 9:
                for i in range(-1,2):
                    for j in range(-1,2):
                        if 0 <= y+i <= len(matrix)-1 and 0 <= x+j <= len(matrix[0])-1:
                            if matrix[y+i][x+j] != 9:
                                matrix[y+i][x+j] += 1
    return matrix

def fill_matrix(matrix_hided, matrix_showed, y, x, val_showed):
    '''Recorre todas las scasillas vencinas, y comprueba si son ceros, si es así las descubre, y recorre las vecinas de estas, hasta encontrar casillas con pistas, que también decubre.'''
    zeros = [(y,x)]
    while len(zeros) > 0:
        y, x = zeros.pop()
        for i in range(-1,2):
            for j in range(-1, 2):
                if 0 <= y+i <= len(matrix_hided)-1 and 0 <= x+j <= len(matrix_hided[0])-1:
                    if matrix_showed[y+i][x+j] == val_showed and matrix_hided[y+i][x+j] == 0:
                        matrix_showed[y+i][x+j] = 0
                        if (y+i, x+j) not in zeros:
                            zeros.append((y+i, x+j))
                    else:
                        matrix_showed[y+i][x+j] = matrix_hided[y+i][x+j]
    return matrix_showed

def verify_matrix_filled(matrix: list, val_showed: str) -> bool:
    for y in range(len(matrix)):
        for x in range(len(matrix[0])):
            if matrix[y][x] == val_showed:
                return False
    return True


# workflow
def main():
    system_clear_console()
    rows = 16
    columns = 12
    val_hided = 0
    val_showed = '-'
    val_pointer = 'X'
    mines_count = 8
    mines_coord = []
    marked_coord = []
    playing = True
    game_win = False
    matrix_showed = get_zero_matrix(rows, columns, val_showed)
    matrix_hided = get_zero_matrix(rows, columns, val_hided)
    matrix_hided, mines_coord = place_mines(matrix_hided, mines_count, val_hided)
    matrix_hided = set_heat_map(matrix_hided)
    menu_welcome()
    y = randint(2, rows-2)
    x = randint(2, columns-2)

    real = matrix_showed[y][x]
    matrix_showed[y][x] = val_pointer

    while playing:
        system_clear_console()
        menu_count_marked_mines(len(marked_coord), mines_count)
        menu_show_matrix(matrix_showed)

        if verify_matrix_filled(matrix_showed, val_showed) and \
        sorted(mines_coord) == sorted(marked_coord) and \
        real != val_showed:
            game_win = True
            playing = False
            break
            
        option = set_option_menu()
        match option:
            case 'm': # mostrar
                if matrix_hided[y][x] == 9:
                    matrix_showed[y][x] = '@'
                    playing = False
                elif matrix_hided[y][x] != 0:
                    matrix_showed[y][x] = matrix_hided[y][x]
                    real = matrix_showed[y][x]
                elif matrix_hided[y][x] == 0:
                    matrix_showed[y][x] = 0
                    matrix_showed = fill_matrix(matrix_hided, matrix_showed, y, x, val_showed)
                    matrix_showed = change_zeros_to_val(matrix_showed, ' ')
                    real = matrix_showed[y][x]
            case 'w':
                if y == 0:
                    y = 0
                else:
                    matrix_showed[y][x] = real
                    y -= 1
                    real = matrix_showed[y][x]
                    matrix_showed[y][x] = val_pointer
            case 's':
                if y == rows-1:
                    y = rows-1
                else:
                    matrix_showed[y][x] = real
                    y += 1
                    real = matrix_showed[y][x]
                    matrix_showed[y][x] = val_pointer
            case 'a':
                if x == 0:
                    x = 0
                else:
                    matrix_showed[y][x] = real
                    x -= 1
                    real = matrix_showed[y][x]
                    matrix_showed[y][x] = val_pointer
            case 'd':
                if x == columns-1:
                    x = columns-1
                else:
                    matrix_showed[y][x] = real
                    x += 1
                    real = matrix_showed[y][x]
                    matrix_showed[y][x] = val_pointer
            case 'b':
                if real == val_showed:
                    matrix_showed[y][x] = '#'
                    real = matrix_showed[y][x]
                    if (y, x) not in marked_coord:
                        marked_coord.append((y, x))
            case 'v':
                if real == '#':
                    matrix_showed[y][x] = val_showed
                    real = matrix_showed[y][x]
                    if (y, x) in marked_coord:
                        marked_coord.remove((y, x))

    if game_win:
        print('--------------------------------')
        print('--------- HAS GANADO -----------')
        print('--------------------------------')
    else:
        print('--------------------------------')
        print('--------- HAS PERDIDO ----------')
        print('--------------------------------')

main()