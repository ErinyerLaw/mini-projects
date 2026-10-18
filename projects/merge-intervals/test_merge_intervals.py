import unittest

from merge_intervals import merge_intervals, parse_intervals


class MergeIntervalsTests(unittest.TestCase):
    def test_merges_unsorted_overlapping_intervals(self):
        intervals = [(8, 10), (2, 6), (1, 3), (15, 18), (10, 12)]
        self.assertEqual(merge_intervals(intervals), [(1, 6), (8, 12), (15, 18)])

    def test_merges_nested_intervals(self):
        self.assertEqual(merge_intervals([(1, 10), (3, 4), (5, 8)]), [(1, 10)])

    def test_shared_endpoint_merges_but_gap_does_not(self):
        self.assertEqual(merge_intervals([(1, 3), (3, 5)]), [(1, 5)])
        self.assertEqual(merge_intervals([(1, 3), (4, 5)]), [(1, 3), (4, 5)])

    def test_handles_negative_numbers_and_single_point(self):
        self.assertEqual(merge_intervals([(-5, -2), (-3, 0), (2, 2)]),
                         [(-5, 0), (2, 2)])

    def test_parses_blank_lines(self):
        self.assertEqual(parse_intervals("\n-2 3\n\n4 5\n"), [(-2, 3), (4, 5)])

    def test_empty_input(self):
        self.assertEqual(parse_intervals("\n"), [])
        self.assertEqual(merge_intervals([]), [])

    def test_rejects_bad_input(self):
        for text in ("1\n", "a 2\n", "1 2 3\n", "5 1\n"):
            with self.subTest(text=text), self.assertRaises(ValueError):
                parse_intervals(text)

    def test_rejects_invalid_interval_passed_directly(self):
        with self.assertRaises(ValueError):
            merge_intervals([(5, 1)])


if __name__ == "__main__":
    unittest.main()
