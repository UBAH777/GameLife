# GameLife

Здесь реализована известная игра о клеточной жизни, имеющая множество вариантов правил.

# В игре реализован следующий принцип развития жизни:
1) Если у клетки 1 или меньше соседей - клетка погибает (сосед - клетка, каждая координата которой отличается не более чем на единицу)
2) Если у клетки 2 соседа - количество клеток не изменяется
3) Если у клетки 3 соседа - в соседней клетке зарождается новая жизнь
4) Если у клетки 4+ соседей - клетка также погибает


# Как играть:
- Чтобы рисовать клетки на поле необходимо кликать курсоров в произвольную область (в том месте появится клетка) или использовать клавишу R
 для генерации случайного заполнения поля
- Чтобы остановить (заморозить) игру, например, для удобства расстановки клеток собственноручно, следует нажать клавишу P
- Чтобы сохранить текущую игру, нажмите клавишу S, чтобы загрузить сохранённую - нажмите L
- Чтобы очистить поле нажмите Q

! Изменение размеров поля предусмотрено только в коде игры
