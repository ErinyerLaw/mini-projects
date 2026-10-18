"""Merge overlapping closed intervals from a text file."""

from pathlib import Path
import sys


def parse_intervals(text: str) -> list[tuple[int, int]]:
    intervals = []
    for line_number, line in enumerate(text.splitlines(), start=1):
        if not line.strip():
            continue
        parts = line.split()
        if len(parts) != 2:
            raise ValueError(f"Строка {line_number}: нужны два целых числа.")
        try:
            start, end = map(int, parts)
        except ValueError as error:
            raise ValueError(f"Строка {line_number}: нужны два целых числа.") from error
        if start > end:
            raise ValueError(f"Строка {line_number}: начало больше конца.")
        intervals.append((start, end))
    return intervals


def merge_intervals(intervals: list[tuple[int, int]]) -> list[tuple[int, int]]:
    if not intervals:
        return []

    merged = []
    for start, end in sorted(intervals):
        if start > end:
            raise ValueError("Начало интервала больше конца.")
        if merged and start <= merged[-1][1]:
            previous_start, previous_end = merged[-1]
            merged[-1] = (previous_start, max(previous_end, end))
        else:
            merged.append((start, end))
    return merged


def main() -> int:
    if len(sys.argv) != 2:
        print("Использование: python merge_intervals.py <файл>", file=sys.stderr)
        return 1
    try:
        text = Path(sys.argv[1]).read_text(encoding="utf-8")
        intervals = merge_intervals(parse_intervals(text))
    except (OSError, UnicodeError, ValueError) as error:
        print(f"Ошибка: {error}", file=sys.stderr)
        return 1

    if not intervals:
        print("Интервалов нет.")
    for start, end in intervals:
        print(start, end)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
