"""Arrange tasks so every dependency is completed first."""

from collections import deque
from pathlib import Path
import sys


def order_tasks(text: str) -> list[str]:
    dependencies: dict[str, list[str]] = {}

    for line_number, line in enumerate(text.splitlines(), start=1):
        if not line.strip():
            continue
        name, separator, rest = line.partition(":")
        name = name.strip()
        if not separator or not name or len(name.split()) != 1:
            raise ValueError(f"Строка {line_number}: нужен формат 'задача: зависимости'.")
        if name in dependencies:
            raise ValueError(f"Строка {line_number}: задача '{name}' указана дважды.")
        required = rest.split()
        if len(required) != len(set(required)):
            raise ValueError(f"Строка {line_number}: зависимость указана дважды.")
        dependencies[name] = required

    if not dependencies:
        raise ValueError("Список задач пуст.")

    followers = {name: [] for name in dependencies}
    remaining = {name: len(required) for name, required in dependencies.items()}
    for name, required in dependencies.items():
        for dependency in required:
            if dependency not in dependencies:
                raise ValueError(f"Для '{name}' не найдена задача '{dependency}'.")
            followers[dependency].append(name)

    ready = deque(name for name in dependencies if remaining[name] == 0)
    result = []
    while ready:
        name = ready.popleft()
        result.append(name)
        for follower in followers[name]:
            remaining[follower] -= 1
            if remaining[follower] == 0:
                ready.append(follower)

    if len(result) != len(dependencies):
        raise ValueError("Обнаружен цикл зависимостей.")
    return result


def main() -> int:
    if len(sys.argv) != 2:
        print("Использование: python task_order.py <файл-задач>", file=sys.stderr)
        return 1

    try:
        text = Path(sys.argv[1]).read_text(encoding="utf-8")
        tasks = order_tasks(text)
    except (OSError, UnicodeError, ValueError) as error:
        print(f"Ошибка: {error}", file=sys.stderr)
        return 1

    for number, name in enumerate(tasks, start=1):
        print(f"{number}. {name}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
