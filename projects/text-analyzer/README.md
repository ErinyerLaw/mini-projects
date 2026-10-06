# Анализатор текста

Консольная программа на Python считает символы, слова,
уникальные слова, предложения и абзацы, показывает наиболее частые слова и
оценивает время чтения. Поддерживает UTF-8 и корректно работает с русским
текстом.

## Запуск

Нужен Python 3.10 или новее.

```bash
python text_analyzer.py example.txt
```

Из стандартного ввода:

```bash
echo "Привет, мир! Привет!" | python text_analyzer.py -
```

Результат в JSON:

```bash
python text_analyzer.py example.txt --top 10 --json
```

## Пример результата

```text
Text analysis
Characters: 27
Characters without spaces: 23
Words: 4
Unique words: 3
Sentences: 2
Paragraphs: 1
Estimated reading time: 0.02 min
Most frequent words: привет (2), мир (1), снова (1)
```

## Тесты

```bash
python -m unittest -v
```

Тесты проверяют обработку русского текста и дефисов, основные метрики, пустой
ввод, неверные параметры и формат обычного отчёта.

