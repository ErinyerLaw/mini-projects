# Поиск строк в файле

Программа ищет текст в строках файла и показывает совпадения вместе с их
номерами. По умолчанию регистр учитывается. Параметр `--ignore-case` отключает
учёт регистра для латинских букв `A–Z`; остальные символы сравниваются как есть.
Текст поиска воспринимается буквально, не как регулярное выражение.

## Сборка и запуск

Нужен компилятор с поддержкой C++17. Из папки проекта:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic line_search.cpp main.cpp -o line_search
./line_search Error example.txt
```

В PowerShell после сборки запускайте `./line_search.exe Error example.txt`.

Результат:

```text
2: Error: missing file
4: Error: connection lost
```

Если совпадений нет, программа выводит `Совпадений нет.`.

## Тесты

```bash
g++ -std=c++17 -Wall -Wextra -pedantic line_search.cpp line_search_test.cpp -o line_search_test
./line_search_test
```

В PowerShell тестовая программа называется `line_search_test.exe`. При
успешном выполнении она ничего не выводит.
