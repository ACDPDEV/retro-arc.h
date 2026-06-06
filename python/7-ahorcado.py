from os import system
from random import choice

words = ['ARMARIO', 'COLEGIO', 'NAVIDAD', 'CAFETERA', 'MARIPOSA', 'ELEFANTE', 'BELLOTA', 'PEGAMENTO', 'CRUCIGRAMA', 'ESCALERA']
old_words = []
game_word = ''
player_letter = ''
count = 0
option_add_new_words = 'S'

def get_new_words():
    text = input('Escribe las palabras a agregar: ')
    return text

def get_min_length():
    min_length = input('¿Cuántas letras como mínimo?')
    return int(min_length)

def generate_new_pseudo_words(text):
    text_list = text.upper().split()
    return text_list

def generate_new_words(text_list, min_lenght: int):
    alph = 'ABCDEFGHIJKLMNÑOPQRSTUVWXYZÁÉÍÓÚÜÏ'
    for text in text_list:
        if len(text) > min_lenght:
            word = ''
            for t in text:
                if t in alph:
                    word += t
            word = word.replace('Á', 'A').replace('É', 'E').replace('Í', 'I').replace('Ó', 'O').replace('Ú', 'U').replace('Ü', 'U').replace('Ï', 'Ï')
            words.append(word)

def show_player_letter():
    print()
    print('Letras que ya escribiste:')
    for i in player_letter:
        print(f'{i} ',end='')
    print()
    print()
    print()

def game_choice_word():
    word = choice(words)
    while word in old_words:
        word = choice(words)
    return word

def get_letter()->str:
    letter = input('Escribe una letra: ')
    return letter.upper()

def refresh_player_letter(letter: str):
    global player_letter
    player_letter += letter

def game_current_word():
    for i in range(len(game_word)):
        if game_word[i] in player_letter:
            print(f'{game_word[i]} ', end='')
        else:
            print('_ ',end='')
    print()
    print()
    print()

def show_game_word():
    for i in game_word:
        print(f'{i} ',end='')
    print()
    print()

def compare_game_word():
    ans = 1
    for i in game_word:
        if not i in player_letter:
            ans *= 0
        else:
            ans *= 1
    return ans

def menu_play_again():
    play_again = input('Desea jugar de nuevo? (S/N)-> ')
    return play_again.upper()

def refresh_old_words(word):
    old_words.append(word)

def game_play_again():
    global count, player_letter, game_word
    play_again = menu_play_again()
    if play_again == 'S':
        count = 0
        player_letter = ''
        refresh_old_words(game_word)
        game_word = game_choice_word()
        system('cls')
        print('** JUEGO DEL AHORCADO **')
        game_current_hanged()
        game_current_word()
        return 1
    elif play_again == 'N':
        print()
        print('Hasta luego!!!')
        print()
        return 0



def game_current_hanged():
    match count:
        case 0:
            hanged_0()
        case 1:
            hanged_1()
        case 2:
            hanged_2()
        case 3:
            hanged_3()
        case 4:
            hanged_4()
        case 5:
            hanged_5()
        case 6:
            hanged_6()


def hanged_0():
    print('      ╔══════╗')
    print('             ║')
    print('             ║')
    print('             ║')
    print('             ║')
    print('═════════════╩═')

def hanged_1():
    print('      ╔══════╗')
    print('      Ô      ║')
    print('             ║')
    print('             ║')
    print('             ║')
    print('═════════════╩═')

def hanged_2():
    print('      ╔══════╗')
    print('      Ô      ║')
    print('      |      ║')
    print('             ║')
    print('             ║')
    print('═════════════╩═')

def hanged_3():
    print('      ╔══════╗')
    print('      Ô      ║')
    print('     /|      ║')
    print('             ║')
    print('             ║')
    print('═════════════╩═')

def hanged_4():
    print('      ╔══════╗')
    print('      Ô      ║')
    print('     /|\\     ║')
    print('             ║')
    print('             ║')
    print('═════════════╩═')

def hanged_5():
    print('      ╔══════╗')
    print('      Ô      ║')
    print('     /|\\     ║')
    print('     /       ║')
    print('             ║')
    print('═════════════╩═')

def hanged_6():
    print('      ╔══════╗')
    print('      Ô      ║')
    print('     /|\\     ║')
    print('     / \\     ║')
    print('             ║')
    print('═════════════╩═')


while option_add_new_words == 'S':
    option_add_new_words = input('Quieres agregar más posibles palabras? (S/N)')
    option_add_new_words = option_add_new_words.upper()
    if option_add_new_words == 'S':
        text = get_new_words()
        min_lenght = get_min_length()
        t_list = generate_new_pseudo_words(text)
        generate_new_words(t_list, min_lenght)

game_word = game_choice_word()

while True:
    system('cls')
    print('** JUEGO DEL AHORCADO **')
    
    game_current_hanged()

    if count == 6:
        print('Estás ahorcado!!')
        print()
        print('La palabra era:')
        show_game_word()
        play_again = game_play_again()
        if play_again == 0:
            break 
    
    game_current_word()
    show_player_letter()
    game_status = compare_game_word()
    if game_status == 1:
        print('Felicitaciones!! Lo lograste')
        print()
        play_again = game_play_again()
        if play_again == 0:
            break        

    letter = get_letter()
    while len(letter)>1:
        print()
        print('Escribe solo una letra:')
        print()
        letter = get_letter()
    if letter not in game_word or letter in player_letter:
        count += 1
    refresh_player_letter(letter)