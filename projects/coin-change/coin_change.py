"""Find a minimum-size set of coins for a target amount."""

import argparse


def minimum_coins(amount: int, denominations: list[int]) -> list[int] | None:
    """Return coins for an optimal solution, or None if no solution exists."""
    if amount < 0:
        raise ValueError("Сумма не может быть отрицательной")
    if any(coin <= 0 for coin in denominations):
        raise ValueError("Номиналы должны быть положительными")

    coins = sorted(set(denominations))
    unreachable = amount + 1
    best = [unreachable] * (amount + 1)
    chosen = [0] * (amount + 1)
    best[0] = 0

    for total in range(1, amount + 1):
        for coin in coins:
            if coin > total:
                break
            candidate = best[total - coin] + 1
            if candidate < best[total]:
                best[total] = candidate
                chosen[total] = coin

    if best[amount] == unreachable:
        return None

    result = []
    while amount:
        coin = chosen[amount]
        result.append(coin)
        amount -= coin
    return result


def main() -> None:
    parser = argparse.ArgumentParser(
        description="Найти минимальное число монет для заданной суммы"
    )
    parser.add_argument("amount", type=int, help="сумма")
    parser.add_argument("coins", nargs="+", type=int, help="номиналы монет")
    args = parser.parse_args()

    try:
        result = minimum_coins(args.amount, args.coins)
    except ValueError as error:
        parser.error(str(error))

    if result is None:
        print("Сумму набрать нельзя.")
    else:
        print(f"Количество монет: {len(result)}")
        print("Монеты: " + (" ".join(map(str, result)) if result else "нет"))


if __name__ == "__main__":
    main()
