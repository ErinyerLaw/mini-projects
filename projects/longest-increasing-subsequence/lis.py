"""Find one longest strictly increasing subsequence."""

import argparse
from bisect import bisect_left


def longest_increasing_subsequence(numbers: list[int]) -> list[int]:
    tails: list[int] = []
    tail_indices: list[int] = []
    previous = [-1] * len(numbers)

    for index, number in enumerate(numbers):
        position = bisect_left(tails, number)
        if position > 0:
            previous[index] = tail_indices[position - 1]
        if position == len(tails):
            tails.append(number)
            tail_indices.append(index)
        else:
            tails[position] = number
            tail_indices[position] = index

    if not tail_indices:
        return []

    result = []
    index = tail_indices[-1]
    while index != -1:
        result.append(numbers[index])
        index = previous[index]
    return result[::-1]


def main() -> None:
    parser = argparse.ArgumentParser(
        description="Найти самую длинную строго возрастающую подпоследовательность"
    )
    parser.add_argument("numbers", nargs="*", type=int, help="целые числа")
    args = parser.parse_args()

    result = longest_increasing_subsequence(args.numbers)
    print(f"Длина: {len(result)}")
    print("Подпоследовательность: " + (" ".join(map(str, result)) if result else "нет"))


if __name__ == "__main__":
    main()
