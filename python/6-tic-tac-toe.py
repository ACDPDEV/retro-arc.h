'''
        ----JUEGO TRES EN RAYA----

'''
from os import system

ttt = {
        '1': ' ',
        '2': ' ',
        '3': ' ',
        '4': ' ',
        '5': ' ',
        '6': ' ',
        '7': ' ',
        '8': ' ',
        '9': ' ',
    }

symbols = {
    'X': [],
    'O': []
}

def system_clear_console():
    system('cls')

def user_wait():
    input('-> ')

# --- Menus ---
def menu_game_title():
    print('                 TRES EN RAYA')
    print('══════════════════════════════════════════════')

def menu_game_welcome():
    print()
    print('             B I E N V E N I D O')
    print()

def menu_game_number_of_players():
    print('     (1) Un jugador      (2) Dos jugadores ')
    print()
    print('══════════════════════════════════════════════')

def menu_game_player_name():
    print('Escribe tu nombre--- ')
    print()

def menu_score(player_1_name: str, player_1_score: int, player_2_name: str, player_2_score: str):
    print(f'{player_1_name:>14} {player_1_score:>3d}    ║    {player_2_score:<3d} {player_2_name:<14}')
    print('══════════════════════╩═══════════════════════')

def menu_player_turn(player_symbol, game_winner):
    if game_winner != None:
        print()
        print()
        print()
    elif player_symbol == 'X':
        print('       ^^^^^^^^^^ (X)')
        print()
        print()
    elif player_symbol == 'O':
        print('                        (O) ^^^^^^^^^^')
        print()
        print()

def menu_current_board(ttt_dict: dict):
    print('          1      ║2      ║3      ')
    print(f'             {ttt_dict['1']}   ║   {ttt_dict['2']}   ║   {ttt_dict['3']}   ')
    print('                 ║       ║       ')
    print('          ═══════╬═══════╬═══════')
    print('          4      ║5      ║6      ')
    print(f'             {ttt_dict['4']}   ║   {ttt_dict['5']}   ║   {ttt_dict['6']}   ')
    print('                 ║       ║       ')
    print('          ═══════╬═══════╬═══════')
    print('          7      ║8      ║9      ')
    print(f'             {ttt_dict['7']}   ║   {ttt_dict['8']}   ║   {ttt_dict['9']}   ')
    print('                 ║       ║       ')

# --- User inputs ----
def set_number_of_players():
    option = input('-> ')
    while option != '1' and option != '2':
        option = input('(1 | 2) -> ')
    return option

def set_player_name(player) -> str:
    player_name = input(f'Nombre de jugador {player} -> ').upper()
    while not (2 < len(player_name) < 14):
        print('Escoge un nombre entre 2 y 14 caracteres')
        player_name = input(f'Nombre de jugador {player} -> ').upper()
    print()
    return player_name

def set_player_choice(options_taked: list) -> str:
    options = ['1','2','3','4','5','6','7','8','9','Q']
    player_choice = input(' -> ').upper()
    while player_choice not in options or player_choice in options_taked:
        if player_choice in options_taked:
            print(f'La opción {player_choice} ya está marcada')
            player_choice = input('Elige otra opción ->').upper()
        elif player_choice not in options:
            print('Opción no válida')
            player_choice = input('(1 - 9) -> ').upper()
    return player_choice

def set_game_player_symbol() -> str:
    symbol = input(f'¿Quién juega primero? (X  |  O) -> ').upper()
    while symbol != 'X' and symbol != 'O':
        symbol = input('Escribe (X) u (O) ->').upper()
    print()
    return symbol

def set_player_1_symbol(player_name) -> str:
    symbol = input(f'{player_name}, escoge tu símbolo (X  |  O) -> ').upper()
    while symbol != 'X' and symbol != 'O':
        symbol = input('Escribe (X) u (O) ->').upper()
    print()
    return symbol
    
# --- Controlers ---
def set_player_2_symbol(player_1_symbol: str) -> str:
    if player_1_symbol == 'X':
        player_2_symbol = 'O'
    elif player_1_symbol == 'O':
        player_2_symbol = 'X'
    return player_2_symbol

def refresh_options_taked(player_choice: str, options_taked: list):
    options_taked.append(player_choice)

def refresh_game_options(game_options: dict, player_choice: str, player_symbol: str):
    game_options[player_choice] = player_symbol

def refresh_game_symbols(game_symbols: dict, player_symbol: str, player_choice:str):
    game_symbols[player_symbol].append(player_choice)

def switch_player_symbol(player_symbol: str) -> str:
    if player_symbol == 'X':
            player_symbol = 'O'
    elif player_symbol == 'O':
        player_symbol = 'X'
    return player_symbol

def verify_game_winner(game_symbols: dict, player_symbol: str, game_options: dict) -> str | None:
    if game_options['1'] == game_options['2'] == game_options['3'] != ' ' or \
        game_options['4'] == game_options['5'] == game_options['6'] != ' ' or \
            game_options['7'] == game_options['8'] == game_options['9'] != ' ' or \
                game_options['1'] == game_options['4'] == game_options['7'] != ' ' or \
                    game_options['2'] == game_options['5'] == game_options['8'] != ' ' or \
                        game_options['3'] == game_options['6'] == game_options['9'] != ' ' or \
                            game_options['1'] == game_options['5'] == game_options['9'] != ' ' or \
                                game_options['3'] == game_options['5'] == game_options['7'] != ' ':
        return game_symbols[player_symbol]
    # if ('1' in game_symbols[player_symbol] and '2' in game_symbols[player_symbol] and '3' in game_symbols[player_symbol]) or \
    #     ('4' in game_symbols[player_symbol] and '5' in game_symbols[player_symbol] and '6' in game_symbols[player_symbol]) or \
    #         ('7' in game_symbols[player_symbol] and '8' in game_symbols[player_symbol] and '9' in game_symbols[player_symbol]) or \
    #             ('1' in game_symbols[player_symbol] and '5' in game_symbols[player_symbol] and '9' in game_symbols[player_symbol]) or \
    #                 ('3' in game_symbols[player_symbol] and '5' in game_symbols[player_symbol] and '7' in game_symbols[player_symbol]) or\
    #                     ('1' in game_symbols[player_symbol] and '4' in game_symbols[player_symbol] and '7' in game_symbols[player_symbol]) or \
    #                         ('2' in game_symbols[player_symbol] and '5' in game_symbols[player_symbol] and '8' in game_symbols[player_symbol]) or \
    #                             ('3' in game_symbols[player_symbol] and '6' in game_symbols[player_symbol] and '9' in game_symbols[player_symbol]):
    #     return player_symbol
    elif game_options['1'] != ' ' and game_options['2'] != ' ' and game_options['3'] != ' ' and game_options['4'] != ' ' and game_options['5'] != ' ' and game_options['6'] != ' ' and game_options['7'] != ' ' and game_options['8'] != ' ' and game_options['9'] != ' ':
        return 'draw'
    # elif len(game_symbols[player_symbol]) == 6:
    #     return 'draw'
    else:
        return None

def reset_game_options(game_options):
    game_options['1'] = ' '
    game_options['2'] = ' '
    game_options['3'] = ' '
    game_options['4'] = ' '
    game_options['5'] = ' '
    game_options['6'] = ' '
    game_options['7'] = ' '
    game_options['8'] = ' '
    game_options['9'] = ' '

def reset_game_symbols(game_symbols: dict, player_1_name: str, player_2_name: str):
    game_symbols['X'] = [player_1_name]
    game_symbols['O'] = [player_2_name]

def reset_player_symbol():
    pass

def main():
    system_clear_console()
    game_options = ttt
    game_symbols = symbols
    menu_game_title()
    menu_game_welcome()
    menu_game_number_of_players()
    num_of_players = set_number_of_players()
    system_clear_console()
    menu_game_title()
    menu_game_player_name()
    player_1_name = set_player_name('UNO: ')
    if num_of_players == '2':
        player_2_name = set_player_name('DOS: ')
    elif num_of_players == '1':
        player_2_name = 'COMPUTADORA'
    player_1_symbol = set_player_1_symbol(player_1_name)
    player_2_symbol = set_player_2_symbol(player_1_symbol)
    game_symbols[player_1_symbol].append(player_1_name)
    game_symbols[player_2_symbol].append(player_2_name)
    player_1_score = 0
    player_2_score = 0
    player_symbol = set_game_player_symbol()
    options_taked = []
    game_winner = None
    while True:
        system_clear_console()
        menu_game_title()
        menu_score(player_1_name, player_1_score, player_2_name, player_2_score)
        menu_player_turn(player_symbol, game_winner)
        menu_current_board(game_options)
        if game_winner == 'draw':
            print('* * * * * * * * * * * * * * * * * * * * * *')
            print('             -- E M P A T E --')
            print('* * * * * * * * * * * * * * * * * * * * * *')
            print()
            game_winner = True
            user_wait()
        elif game_winner != None:
            player_symbol = switch_player_symbol(player_symbol)
            print('* * * * * * * * * * * * * * * * * * * * * *')
            print(f'GANA ---{game_symbols[player_symbol][0]}---')
            print('* * * * * * * * * * * * * * * * * * * * * *')
            print()
            if game_symbols[player_symbol][0] == player_1_name:
                player_1_score += 1
            elif game_symbols[player_symbol][0] == player_2_name:
                player_2_score += 1
            game_winner = True
            user_wait()
        if game_winner == None:
            player_choice = set_player_choice(options_taked)
            refresh_game_options(game_options, player_choice, player_symbol)
            refresh_game_symbols(game_symbols, player_symbol, player_choice)
            refresh_options_taked(player_choice, options_taked)
            game_winner = verify_game_winner(game_symbols, player_symbol, game_options)
            player_symbol = switch_player_symbol(player_symbol)
        if game_winner == True:
            reset_game_options(game_options)
            reset_game_symbols(game_symbols, player_1_name, player_2_name)
            options_taked = []
            player_symbol = set_game_player_symbol()
            game_winner = None
        
main()