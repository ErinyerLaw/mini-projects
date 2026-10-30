import unittest

from edit_distance import edit_distance


class EditDistanceTests(unittest.TestCase):
    def test_equal_strings(self):
        self.assertEqual(edit_distance("hello", "hello"), 0)
        self.assertEqual(edit_distance("", ""), 0)

    def test_empty_string(self):
        self.assertEqual(edit_distance("", "abc"), 3)
        self.assertEqual(edit_distance("abc", ""), 3)

    def test_single_operations(self):
        self.assertEqual(edit_distance("cat", "cats"), 1)
        self.assertEqual(edit_distance("cats", "cat"), 1)
        self.assertEqual(edit_distance("cat", "cut"), 1)

    def test_multiple_operations(self):
        self.assertEqual(edit_distance("kitten", "sitting"), 3)
        self.assertEqual(edit_distance("Saturday", "Sunday"), 3)

    def test_unicode(self):
        self.assertEqual(edit_distance("кот", "кит"), 1)

    def test_transposition_is_two_operations(self):
        self.assertEqual(edit_distance("ab", "ba"), 2)


if __name__ == "__main__":
    unittest.main()
