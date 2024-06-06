import time
import random

# Escribe tu código aquí
PuntajeCompu1 = 0
PuntajeCompu2 = 0
while True:
    PC1 = random.randint(1,3)
    PC2 = random.randint(1,3)
    if PC1 == 1:
        PC1 = 'piedra'
    elif PC1 == 2:
        PC1 = 'tijera'
    else:
        PC1 = 'papel'

    if PC2 == 1:
        PC2 = 'piedra'
    elif PC2 == 2:
        PC2 = 'tijera'
    else:
        PC2 = 'papel'
    print('la primera compu elijió: ',PC1)
    print('la segunda compu elijió: ',PC2)
    if PC1 == 'piedra' and PC2 == 'tijera':
        print('lA computadora 1 ganó')
        PuntajeCompu1 += 1
    elif PC1 == 'papel' and PC2 == 'piedra':
        print('lA computadora 1 ganó')
        PuntajeCompu1 += 1
    elif PC1 == 'tijera' and PC2 == 'papel':
        print('lA computadora 1 ganó')
        PuntajeCompu1 += 1
    elif PC1 == PC2:
        print('Empataron')
    else:
        print('La computadora te ha ganado :(')
        PuntajeCompu2 += 1
    print("El puntaje de la primera computadora es: ", PuntajeCompu1)
    print("El puntaje de la segunda computadora es: ", PuntajeCompu2)
    if PuntajeCompu1 == 10 or PuntajeCompu2 == 10:
        break;
