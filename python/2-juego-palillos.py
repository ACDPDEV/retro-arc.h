'''
        --JUEGO DE LOS PALILLOS (O NIM)---
1. Presentación del juego
2. Elección por el usuario de nivel (fácil / difícil)
3. Elección aleatoria de palillos totales (entre 16 y 23)
4. Elección aleatoria de quitas de palillos (entre 1 y 3/4/5)
5. El jugador humano empezará siempre primero.
6. Mostrar el área de juego con los palillos totales
7. Turno del usuario humano:
    Elige palillos a quitar.
    Se muestra el área de juego sin esos palillos.
    Se cambia de turno
8. Turno del ordenador:
    Si el nivel es fácil elige aleatoriamente
    Si el nivel es difícil se llama a la IA
    Se muestra el área de juego sin los palillos elegidos
    Se cambia de turno
9. Después de cada movimiento se comprueba si no hay más palillos:
    Si es así se comprueba quién cogió el último
    Se muestra el ganador de la partida.
10. Si aún hay palillos, se sigue con el turno siguiente de quien toque.
''' 
from random import randint
from os import system
from time import sleep

total_sticks = 0
max_remove = 0
game_over = 0

def system_clear_console():
    '''Clear the console screen'''
    system('cls')

def menu_game_title():
    '''Show the name of the game'''
    print('****************  JUEGO DE LOS PALILLOS  ****************')

def menu_game_welcome():
    print('*                                                       *')
    print('*                                                       *')
    print('*           Gana quien coge el último palillo           *')
    print('*                                                       *')
    print('*                                                       *')
    print('*                                                       *')
    print('*          1- Fácil         |        2- Difícil         *')
    print('*                                                       *')
    print('*                                                       *')
    print('*********************************************************')
    print('')

def menu_game_instructions(total_sticks: int, max_remove: int):
    print('*                                                       *')
    print('*                                                       *')
    print(f'*              Habrá {total_sticks:2} palillos en total               *')
    print('*                                                       *')
    print(f'*         Se pueden quitar entre 1 y {max_remove:1} palillos         *')
    print('*                                                       *')
    print('*                                                       *')
    print('*                  Empiezas a mover tú                  *')
    print('*                                                       *')
    print('*********************************************************')
    print('')

def menu_winner(player):
    if player == 'user':
        print('*                                                       *')
        print('*                                                       *')
        print('*                   ¡ G A N A S T E !                   *')
        print('*                                                       *')
        print('*               Cogiste el último palillo               *')
    if player == 'computer':
        print('*                                                       *')
        print('*                                                       *')
        print('*                Ganó la computadora...                 *')
        print('*                                                       *')
        print('*              Puedes intentarlo de nuevo               *')

def menu_play_again():
    print('*                                                       *')
    print('*     1- Jugar de nuevo     |         2- Salir          *')
    print('*                                                       *')
    print('*                                                       *')
    print('*********************************************************')
    print('')

def menu_game_over():
    print('*                                                       *')
    print('*                                                       *')
    print('*                F I N   D E L   J U E G O              *')
    print('*                                                       *')
    print('*                     ¡Hasta luego!                     *')
    print('*                                                       *')
    print('*                                                       *')
    print('*                                                       *')
    print('*                                                       *')
    print('*********************************************************')
    print('')


def menu_select_level():
    level = input('Elige nivel (1 | 2) ->')
    while not(level == '1' or level == '2'):
        level = input('(1) para fácil | (2) para difícil -> ')
    return level

def menu_continue():
    input('(Enter para continuar...)')

def set_total_sticks():
    '''Return a random number between 16 and 23'''
    return randint(16,23)

def set_max_remove(level: str):
    'Sets the max number of sticks allowed to remove in the game. Each player will be able to remove a number of sticks between 1 and this number.'
    if level == '1':
        max_remove = 3
    if level == '2':
        max_remove = randint(4,5)
    return max_remove

def set_computer_remove_sticks(max_remove: int, total_sticks: int):
    '''Return a random number between 1 and the max number especified (both inclusive). The number will always be less than the total_sticks'''
    remove_range = min(max_remove, total_sticks)
    remove_sticks = randint(1,remove_range)
    return remove_sticks

def set_computer_ai_remove_sticks(max_remove, total_sticks):
    for i in range(total_sticks-1,-1,-1):
        if i % (max_remove+1) == 0:
            new_total_sticks = i
            break
        new_total_sticks = 1
    
    ideal_remove = total_sticks - new_total_sticks
    if total_sticks <= max_remove:
        remove_sticks = total_sticks
    elif ideal_remove <= max_remove and new_total_sticks>1:
        remove_sticks = ideal_remove
    else:
        remove_sticks = randint(1,max_remove)
    return remove_sticks
    
def menu_computer_sleep(time: float):
    print('La computadora está pensando...')
    sleep(time)

def menu_show_total_sticks(total_sticks: int, max_remove: int):
    '''Display the total sticks remaining in the game. The sticks are grouped in four to make them more readable.'''
    for i in range(4):
        for j in range(total_sticks):
            print('|  ', end='')
            if (j+1) % max_remove == 0:
                print('   ',end='')
        print()

def menu_user_remove_sticks(max_remove: int, total_sticks: int):
    '''Displays a text input for the user to specify the number of sticks they want to remove. Return a integer.'''
    remove_range = min(max_remove, total_sticks)
    user_remove_sticks = int(input('Palillos a quitar: '))
    while user_remove_sticks<1 or remove_range<user_remove_sticks:
        user_remove_sticks = int(input(f'Palillos a quitar (de 1 a {remove_range})'))
    return user_remove_sticks

def set_remove_sticks(max_remove: int, player: str, level: str, computer_sleep: float, total_sticks: int):
    if player == 'user':
        remove_sticks = menu_user_remove_sticks(max_remove, total_sticks)
    elif level == '1' and player == 'computer':
        remove_sticks = set_computer_remove_sticks(max_remove, total_sticks)
        menu_computer_sleep(computer_sleep)
    elif level == '2' and player == 'computer':
        remove_sticks = set_computer_ai_remove_sticks(max_remove, total_sticks)
        menu_computer_sleep(computer_sleep)
    return remove_sticks

def menu_user_play_again():
    user_play_again = input('Elige una opción (1 | 2) -> ')
    while not (user_play_again == '1' or user_play_again == '2'):
        user_play_again = input('(1) para Jugar de nuevo | (2) para Salir -> ')
    return user_play_again

def refresh_total_sticks(remove_sticks: int, total_sticks: int):
    total_sticks -= remove_sticks
    return total_sticks

def check_game_status(total_sticks: int):
    if total_sticks>0:
        return False
    return True

def switch_player(player):
    if player == 'user':
        new_player = 'computer'
    elif player == 'computer':
        new_player = 'user'
    return new_player

def main():
    game_over = 0
    while game_over == 0:
        system_clear_console()
        menu_game_title()
        menu_game_welcome()
        level = menu_select_level()
        system_clear_console()
        total_sticks = set_total_sticks()
        max_remove = set_max_remove(level)
        player = 'user'
        computer_sleep = 3
        menu_game_title()
        menu_game_instructions(total_sticks, max_remove)
        menu_continue()
        system_clear_console()
        while player == 'user' or player == 'computer':
            menu_game_title()
            menu_show_total_sticks(total_sticks, max_remove)
            remove_sticks = set_remove_sticks(max_remove, player, level, computer_sleep, total_sticks)
            total_sticks = refresh_total_sticks(remove_sticks, total_sticks)
            system_clear_console()
            if check_game_status(total_sticks):
                menu_game_title()
                menu_winner(player)
                menu_play_again()
                user_play_again = menu_user_play_again()
                if user_play_again == '1':
                    system_clear_console()
                    break
                else:
                    system_clear_console()
                    menu_game_title()
                    menu_game_over()
                    game_over = 1
                    break
            player = switch_player(player)
 
main()