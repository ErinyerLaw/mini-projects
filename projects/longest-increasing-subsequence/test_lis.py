import unittest

from lis import longest_increasing_subsequence


class LongestIncreasingSubsequenceTests(unittest.TestCase):
    def test_example(self):
        self.assertEqual(longest_increasing_subsequence([3, 1, 2, 5, 4]), [1, 2, 4])

    def test_empty_input(self):
        self.assertEqual(longest_increasing_subsequence([]), [])

    def test_decreasing_input(self):
        self.assertEqual(longest_increasing_subsequence([5, 4, 3]), [3])

    def test_equal_values_are_not_increasing(self):
        self.assertEqual(longest_increasing_subsequence([2, 2, 2]), [2])

    def test_negative_values(self):
        self.assertEqual(longest_increasing_subsequence([-4, -2, -3, 1]), [-4, -3, 1])

    def test_result_is_a_subsequence_with_optimal_length(self):
        source = [10, 9, 2, 5, 3, 7, 101, 18]
        result = longest_increasing_subsequence(source)
        self.assertEqual(len(result), 4)
        self.assertTrue(all(a < b for a, b in zip(result, result[1:])))
        iterator = iter(source)
        self.assertTrue(all(any(value == item for item in iterator) for value in result))


if __name__ == "__main__":
    unittest.main()
