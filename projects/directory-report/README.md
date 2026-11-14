# Отчёт по каталогу

Программа обходит каталог и вложенные папки, считает обычные файлы и их общий
размер в байтах. Также показывает самый большой файл. Символические ссылки
не учитываются.

## Сборка и запуск

Нужен компилятор с поддержкой C++17. Из папки проекта:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic directory_report.cpp main.cpp -o directory_report
./directory_report example
```

В PowerShell после сборки запускайте `./directory_report.exe example`.

В каталоге `example` лежат файлы `a.txt` (3 байта) и `sub/b.txt` (5 байт).
Результат:

```text
Файлов: 2
Всего байт: 8
Самый большой: sub/b.txt (5 байт)
```

Если каталог пуст, выводятся только количество файлов и общий размер.

## Тесты

```bash
g++ -std=c++17 -Wall -Wextra -pedantic directory_report.cpp directory_report_test.cpp -o directory_report_test
./directory_report_test
```

В PowerShell тестовая программа называется `directory_report_test.exe`.
При успешном выполнении она ничего не выводит.
