"""Count insertions, deletions and substitutions between two strings."""

import sys


def edit_distance(first: str, second: str) -> int:
    if len(second) > len(first):
        first, second = second, first

    previous = list(range(len(second) + 1))
    for row, left_char in enumerate(first, start=1):
        current = [row]
        for column, right_char in enumerate(second, start=1):
            current.append(min(
                current[column - 1] + 1,
                previous[column] + 1,
                previous[column - 1] + (left_char != right_char),
            ))
        previous = current
    return previous[-1]


def main() -> int:
    if len(sys.argv) != 3:
        print("Использование: python edit_distance.py <первое> <второе>", file=sys.stderr)
        return 1
    print(f"Расстояние: {edit_distance(sys.argv[1], sys.argv[2])}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
