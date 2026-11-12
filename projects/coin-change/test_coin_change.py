import unittest

from coin_change import minimum_coins


class MinimumCoinsTests(unittest.TestCase):
    def test_greedy_choice_is_not_optimal(self):
        self.assertEqual(minimum_coins(6, [1, 3, 4]), [3, 3])

    def test_unreachable_amount(self):
        self.assertIsNone(minimum_coins(7, [2, 4]))

    def test_zero_amount(self):
        self.assertEqual(minimum_coins(0, [2, 5]), [])

    def test_unsorted_duplicate_denominations(self):
        self.assertEqual(minimum_coins(11, [6, 1, 5, 6]), [5, 6])

    def test_empty_denominations(self):
        self.assertIsNone(minimum_coins(3, []))

    def test_rejects_invalid_values(self):
        with self.assertRaises(ValueError):
            minimum_coins(-1, [1])
        with self.assertRaises(ValueError):
            minimum_coins(3, [0, 1])
        with self.assertRaises(ValueError):
            minimum_coins(3, [-2, 1])


if __name__ == "__main__":
    unittest.main()
