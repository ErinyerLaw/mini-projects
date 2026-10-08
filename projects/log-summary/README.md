# Сводка по логу

Программа считает строки с уровнями `[INFO]`, `[WARN]` и `[ERROR]`, а также
показывает номера строк и тексты ошибок. Строки другого формата считаются
пропущенными. Уровень должен стоять в начале строки, после `]` нужен пробел.

## Сборка и запуск

Нужен компилятор C++17. Из папки проекта:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic log_summary.cpp main.cpp -o log_summary
./log_summary sample.log
```

В PowerShell после сборки запускайте `./log_summary.exe sample.log`.

Для `sample.log` вывод будет таким:

```text
INFO: 2
WARN: 1
ERROR: 2
Пропущено строк: 0
Ошибки:
3: Cannot save file
5: Retry failed
```

## Тесты

```bash
g++ -std=c++17 -Wall -Wextra -pedantic log_summary.cpp log_summary_test.cpp -o log_summary_test
./log_summary_test
```

В PowerShell тестовая программа называется `log_summary_test.exe`. Она не
выводит текст, если все проверки прошли.
