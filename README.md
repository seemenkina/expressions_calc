# RPN-based expressions calculator
Калькулятор, который по известному набору простых высказываний определяет значения составных.
Для вычисления выражение переводится в [обратную польскую запись](https://ru.wikipedia.org/wiki/Обратная_польская_запись).

Поддерживаемые операторы: `&`, `|`, `=`.

## Building
Зависимости:
- cmake >= 3.10

Для сборки приложения необходимо выполнить следующие команды:
    $ mkdir build
    $ cd build
    $ cmake ..
    $ make

В результате выполнения в директории `build` будет создан исполняемый файл `skb_project`.

## Usage
    $ ./skb_project InputFile OutputFile

### Формат входных данных

В первой строке записано два целых числа `N` и `M`.
`N` – количество простых высказываний (`1 < N < 106`), a `M` – количество составных (`1 < M < 104`).

Далее следует `N` строк, каждая из которых содержит имя простого высказывания и его значение.
 Имя высказывания может состоять из строчных и заглавных букв латинского алфавита, а также цифр.
 Имя высказывания не может быть пустым и содержит не более 100 символов.
 Значение простого высказывания - 0 (ложь) или 1 (истина).

Далее следует `M` строк, описывающих составные высказывания.
 Сначала указывается имя составного высказывания, далее идет знак `=`, отделенный пробелами,
 затем – формула, содержащая операции конъюнкции `&`, дизъюнкции `|` и имена высказываний.
 Знаки логических операций отделены от своих операндов пробелами.
 Максимальное количество операндов `– 1 < K < 102`.
 Приоритет операций стандартный, т.е. конъюнкция приоритетнее дизъюнкции.

### Формат выходных данных

Файл с результатом работы программы должен содержать `M` строк.
 Строка с номером `i` должна содержать значение составного высказывания `Mi`:
 0 (ложь), 1 (истина) или символ `?`, если определить значение невозможно.

### Пример

| input.txt         | output.txt |
|-------------------|------------|
| 2 3               | 0          |
| A 1               | 1          |
| B 0               | ?          |
| C = A & B         |            |
| D = A &#124 C     |            |
| E = A & F &#124 B |            |