# Requirements
* CMake
* conan 1.61.0

# Build
(From project-directory)
```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ../
cmake --build ./src
cmake --build ./tests
```

# Execution

### Config structure
JSON-only
```
- memory_limit : int (as bytes)
- input_delay : int (as ms)
- output_delay : int (as ms)
- winding_delay: int (as ms)
- shift_delay: int (as ms)

```

### Command
* `<path-to-exe> -c <path-to-config> -i <path-to-input> -o <path-to-output>`

Example (from `./build`)

```bash
./src/YadroTestTask -c src/config.json -i input.txt -o output.txt
```
Don't forget to create input.txt!

# Testing
(required from `./build/tests`) 

* test-config: `./build/tests/config.json`
```bash
./file_tape_test
./tape_sorter_test
```

# Description

### Основные классы

1. `TapeBase` - чисто виртуальный класс, определяющий интерфейс, работающий с объектом типа "лента".
    * `get_cur()` - текущее положение магнитной головки;
    * `get_length()` - длина ленты;
    * `shift_right()` / `shift_left()` - сдвиг ленты вправо/влево относительно головки на одну позицию;
    * `wind_right(len)` / `wind_left(len)` - прокрутка ленты вправо/влево относительно головки на len позиций;
    * `read()` - чтение текущего элемента;
    * `write(data)` - запись в текущий элемент.

2. `FileTape` - реализация работы с объектом типа "лента" по средствам бинарного файла. Такой подход был выбран, чтобы оптимизировать запись числа в случайное место файла. Поскольку все элементы одного размера, запись не требует сдвига элементов, которые стоят после записываемого.
    * `FileTape(<path_to_txt>, <path_to_bin>)` - создание из текстового файла
    * `FileTape(<size>, <path_to_bin>)` - создание с заданием размера
    * `create_txt()` - создание текстового файла
    * `delete_tape()` - удаление ленты

3. `TapeSorter` - сортировщик объекта типа "лента". За основу была взята идея алгоритма TimSort: разделить, отсортировать, соеденить операцией merge. Однако, если в TimSort деление происходит из алгоритмических соображений, в данном случае - из-за ограничений по памяти. При разумных ограничениях памяти получаем алгоритмическую сложность O(n*logn), в худшем случае O(n^2).
    * `sort(<input_tape>, <output_tape>)` - сортировка

### Вспомогательные классы

1. `Config` - Singltone-класс, являющийся хранилищем параметров конфигурации.

2. `CMDParser` - парсер аргументов командной строки.
