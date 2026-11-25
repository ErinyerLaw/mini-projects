# Сводка расходов

Программа читает расходы из текстового файла, складывает суммы по категориям
и выводит общий итог. Каждая непустая строка содержит название категории
без пробелов и неотрицательную сумму в копейках. Такой формат позволяет
считать суммы целыми числами.

## Сборка и запуск

Нужен компилятор с поддержкой C++17. Из папки проекта:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic expense_summary.cpp main.cpp -o expense_summary
./expense_summary example.txt
```

В PowerShell после сборки запускайте `./expense_summary.exe example.txt`.
Пример вывода для файла `example.txt`:

```text
food: 500.00
transport: 120.00
Итого: 620.00
```

При ошибке в строке программа сообщает её номер и завершает работу.

## Тесты

```bash
g++ -std=c++17 -Wall -Wextra -pedantic expense_summary.cpp expense_summary_test.cpp -o expense_summary_test
./expense_summary_test
```

В PowerShell тестовая программа называется `expense_summary_test.exe`.
При успешном выполнении она ничего не выводит.
