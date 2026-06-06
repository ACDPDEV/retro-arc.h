'''
        Inteligencia artificial para Piedra, papel, tijeras:
TENDENCIAS BÁSICAS DEL SER HUMANO FRENTE A ESTE JUEGO:
- Si tras una jugada gana habrá más probabilidades de que siga con la misma jugada.
- Si pierde habrá más probabilidades de que cambie de jugada siguiendo el orden.

Orden: (1) Piedra - (2) Papel - (3) Tijeras - (4) Piedra - ...


IMPLEMENTACIÓN:
- En el caso de que el jugador humano gane la última tirada:
    Prever que en la siguiente tirada elegirá la misma jugada, o la jugada anterior en el orden (piedra, papel, tijeras)
- En el caso de que el jugador humano pierda la última tirada:
    Prever que en la siguiente tirada elegirá la siguiente jugada en el orden, o la anterior.
    (Elección aleatoria entre estas dos posibilidades por parte del ordenador).
'''
from os import system
from random import randint
from random import choice

# Se usará los índice para convertir a cada movimiento en un número. Por eso: PIEDRA == 0 , PAPEL == 1 y TIJERA == 2
posible_moves = [['PIEDRA', ' @@', '@@@'], ['PAPEL', '===', '===='], ['TIJERA', '|/ ', 'OO ']]

def system_clear_console():
    '''Clear the console screen'''
    system('cls')

def menu_game_title():
    '''Show the name of the game'''
    print('╔══════════════  PIEDRA - PAPEL - TIJERAS  ═════════════╗')
    print('║                                                       ║')

def menu_game_title_ingame(current_round: int, total_rounds: int):
    '''Show the name of the game, the current round and the total rounds'''
    print(f'╔════════  PIEDRA - PAPEL - TIJERAS : {current_round:>2} de {total_rounds:<2} ═════════╗')
    print('║                                                       ║')

def menu_player_name():
    print('║                                                       ║')
    print('║                                                       ║')
    print('║                                                       ║')
    print('║                   Escribe tu nombre                   ║')
    print('║                                                       ║')
    print('║                                                       ║')
    print('║                                                       ║')
    print('║                                                       ║')
    print('║                                                       ║')
    print('╚═══════════════════════════════════════════════════════╝')
    print('')    

def set_player_name():
    player_name = input('-> ').title()
    while len(player_name) > 16:
        player_name = input('Escribe 16 caracteres máximo -> ').title()
    return player_name

def menu_game_welcome(player_name: str):
    '''Show the available levels in the game'''
    print('║                                                       ║')
    print(f'║              BIENVENIDO {player_name:>16}              ║')
    print('║                                                       ║')
    print('║                  Selecciona el nivel                  ║')
    print('║                                                       ║')
    print('║                                                       ║')
    print('║          1- Fácil         |        2- Difícil         ║')
    print('║                                                       ║')
    print('║                                                       ║')
    print('╚═══════════════════════════════════════════════════════╝')
    print('')

def set_game_level()-> str:
    game_level = input(' -> ')
    while game_level != '1' and game_level != '2':
        game_level = input('Escribe (1) o (2) ->')
    return game_level

def menu_game_rounds():
    '''Show the "¿Cuántas rondas?" text'''
    print('║                                                       ║')
    print('║                                                       ║')
    print('║                                                       ║')
    print('║                                                       ║')
    print('║                   ¿Cuántas rondas?                    ║')
    print('║                                                       ║')
    print('║                                                       ║')
    print('║                                                       ║')
    print('║                                                       ║')
    print('╚═══════════════════════════════════════════════════════╝')
    print('')

def set_game_total_rounds():
    nums = '0123456789'
    total_rounds = input(' -> ')
    aux = 1
    for i in range(len(total_rounds)):
        if total_rounds[i] not in nums:
            aux *= 0
            break
        else:
            aux += 1
    while aux == 0:
        total_rounds = input('Escribe solo números -> ')
        for i in range(len(total_rounds)):
            if total_rounds[i] not in nums:
                aux *= 0
                break
            else:
                aux += 1
    return int(total_rounds)

def menu_game_score(user_name: str, user_score: int, computer_score: int):
    '''Display a banner with the current score'''
    print('║                     P U N T A J E                     ║')
    print(f'║      {user_name:>16}  {user_score:>2} | {computer_score:<2}  Computadora           ║')
    print('║-------------------------------------------------------║')

def menu_player_move():
    print('║                                                       ║')
    print('║                                                       ║')
    print('║               H A Z   T U   J U G A D A               ║')
    print('║                                                       ║')
    print('║                                                       ║')
    print('║              PIEDRA  |  PAPEL  |  TIJERA              ║')
    print('║                                                       ║')
    print('╚═══════════════════════════════════════════════════════╝')
    print('')

def player_move() -> str:
    player_move = input('-> ').upper()
    while player_move != 'PIEDRA' and player_move != 'PAPEL' and player_move != 'TIJERA':
        player_move = input('piedra | papel | tijera-> ').upper()
    return player_move

def convert_move(move: str, posible_moves: list):
    '''Converts the name of the move into a number for future operations'''
    for m in posible_moves:
        if move in m:
            move_number = posible_moves.index(m)
    return move_number

def computer_move_easy() -> int:
    '''Return a random number between 0 and 2 (inclusive)'''
    return randint(0,2)

def computer_move_hard(user_move: int, round_winner: str) -> int:
    '''Set a move based on the previous move of the user.'''
    if round_winner == 'user' or round_winner == 'draw':
        if user_move == 0:
            computer_move = choice([0,1])
        elif user_move == 1:
            computer_move = choice([1,2])
        elif user_move == 2:
            computer_move = choice([2,0])
    elif round_winner == 'computer':
        if user_move == 0:
            computer_move = choice([0,2])
        elif user_move == 1:
            computer_move = choice([1,0])
        elif user_move == 2:
            computer_move = choice([2,1])
    return computer_move

def computer_move(game_level: str, user_move: int, round_winner: str) -> int:
    if game_level == '1':
        computer_move = computer_move_easy()
    elif game_level == '2':
        computer_move = computer_move_hard(user_move, round_winner)
    return computer_move

def set_round_winner(user_move: int, computer_move: int) -> str:
    if user_move != computer_move:
        if (user_move == 0 and computer_move == 1) or (user_move == 1 and computer_move == 2) or (user_move == 2 and computer_move == 0):
            return 'computer'
        elif (user_move == 0 and computer_move == 2) or (user_move == 1 and computer_move == 0) or (user_move == 2 and computer_move == 1):
            return 'user'
    return 'draw'

def refresh_game_score(round_winner: str, user_score: int, computer_score: int):
    if round_winner == 'draw':
        return user_score, computer_score
    elif round_winner == 'user':
        user_score += 1
        return user_score, computer_score
    elif round_winner == 'computer':
        computer_score += 1
        return user_score, computer_score

def refresh_current_round(current_round):
    new_current_round = current_round + 1
    return new_current_round

def menu_game_moves(user_move: int, computer_move: int, posible_moves: list):
    print('║                                                       ║')
    print('║                                                       ║')
    print(f'║         {posible_moves[user_move][1]:^9}                   {posible_moves[computer_move][1]:^9}         ║')
    print(f'║         {posible_moves[user_move][2]:^9}                   {posible_moves[computer_move][2]:^9}         ║')
    print('║                                                       ║')
    print(f'║         {posible_moves[user_move][0]:^9}         |         {posible_moves[computer_move][0]:^9}         ║')
    print('║                                                       ║')
    print('╚═══════════════════════════════════════════════════════╝')
    print('')

def game_moves_sleep():
    input('(Enter para continuar) ->')

def menu_winner_draw():
    print('║                                                       ║')
    print('║                    - E M P A T E -                    ║')
    print('║                                                       ║')

def menu_winner_computer():
    print('║                                                       ║')
    print('║                 Ganó la computadora...                ║')
    print('║                                                       ║')

def menu_winner_user():
    print('║                                                       ║')
    print('║                    ¡ G A N A S T E !                  ║')
    print('║                                                       ║')

def menu_game_winner(user_score: int, computer_score: int):
    if user_score == computer_score:
        menu_winner_draw()
    elif user_score < computer_score:
        menu_winner_computer()
    elif user_score > computer_score:
        menu_winner_user()

def menu_play_again():
    print('║                                                       ║')
    print('║                 Puedes jugar de nuevo                 ║')
    print('║                                                       ║')
    print('║     (S) Jugar de nuevo    |        (N) Salir          ║')
    print('║                                                       ║')
    print('║                                                       ║')
    print('╚═══════════════════════════════════════════════════════╝')
    print('')

def play_again():
    user_play_again = input('(S | N)->').upper()
    while user_play_again != 'S' and user_play_again != 'N':
        user_play_again = input('Escriba (S) o (N) ->').upper()
    return user_play_again

# ------- Programa principal ---------
def main():
    game_over = 0
    game_posible_moves = posible_moves
    while game_over == 0:
        system_clear_console()
        menu_game_title()
        menu_player_name()
        user_name = set_player_name()
        while True:
            system_clear_console()
            menu_game_title()
            menu_game_welcome(user_name)
            game_level = set_game_level()
            system_clear_console()
            menu_game_title()
            menu_game_rounds()
            round_winner = 'draw'
            user_move_int = 0
            total_rounds = set_game_total_rounds()
            current_round = 1
            user_score = 0
            computer_score = 0
            while current_round <= total_rounds:
                system_clear_console()
                menu_game_title_ingame(current_round, total_rounds)
                menu_game_score(user_name, user_score, computer_score)
                menu_player_move()
                computer_move_int = computer_move(game_level, user_move_int, round_winner)
                user_move_str = player_move()
                user_move_int = convert_move(user_move_str, game_posible_moves)
                round_winner = set_round_winner(user_move_int, computer_move_int)
                user_score, computer_score = refresh_game_score(round_winner, user_score, computer_score)
                system_clear_console()
                menu_game_title_ingame(current_round, total_rounds)
                menu_game_score(user_name, user_score, computer_score)
                menu_game_moves(user_move_int, computer_move_int, game_posible_moves)
                current_round = refresh_current_round(current_round)
                game_moves_sleep()
            system_clear_console()
            menu_game_title()
            menu_game_score(user_name, user_score, computer_score)
            menu_game_winner(user_score, computer_score)
            menu_play_again()
            user_play_again = play_again()
            if user_play_again == 'N':
                game_over = 1
                break

main()