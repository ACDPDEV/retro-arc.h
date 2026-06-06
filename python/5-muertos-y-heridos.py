from random import randint
from os import system

times_try = 15
count = 0
ans = []

def game_title():
    title = 'MUERTOS Y HERIDOS (MASTERMIND)'
    print(f'{title:^40}')
    print()

def game_instructions():
    print('Instrucciones:')
    print('Debes adivinar el número secreto de cuatro dígitos')
    print('Todos los dígitos deben ser distintos entre sí')
    print(f'Tienes {times_try} intentos para adivinar')
    print()

def num_generate():
    num = ''
    for i in range(4):
        d = str(randint(1,9))
        while d in num:
            d = str(randint(1,9))
        num += d
    return num

def user_number():
    user_num = input('("2" Ver instrucciones / "3" Salir) Escribe un número de 4 dígitos --> ')
    return user_num

def compare_nums(user_num, game_num):
    deads = 0
    injureds = 0
    for i in range(4):
        if user_num[i] == game_num[i]:
            deads += 1
        elif user_num[i] in game_num:
            injureds += 1
    return deads, injureds


def save_result(user_num, deads, injureds):
    global count
    count += 1
    result = [count, user_num, deads, injureds]
    ans.append(result)

def show_results():
    system('cls')
    print('  N  -    Número    ~  Muertos  -  Heridos  ')
    print(' ---     --------     ---------   ---------')
    for i in ans:
        print(f'{i[0]:^5}-{i[1]:^14}~{i[2]:^11}{i[3]:^11}')
    print()


game_title()
game_instructions()

game_num = num_generate()

while True:
    # print('Escribe un número de 4 dígitos  | 2. Ver instrucciones  | 3. Salir')
    user_num = user_number()
    while 4<int(user_num)<1000:
        print('Opción no válida: ')
        user_num = user_number()
    while 9999<int(user_num):
        print('Ingrese un número de 4 cifras.')
        user_num = user_number()

    if len(user_num) == 1:
        match user_num:
            case '2': # Ver instrucciones
                game_instructions()
            case '3': # Salir del juego
                print(f'El número era: {game_num}')
                print('Hasta luego!!')
                # flag = False
                break
            case '4':
                print(f'{game_num}')
            case _:
                pass
    else:
        deads, injureds = compare_nums(user_num, game_num)
        save_result(user_num, deads, injureds)
        show_results()
        if deads == 4:
            print(f'Acertaste!! El número es {user_num}')
            print()
            break
        elif count == times_try:
            print('Agotaste todos tus intentos...')
            break