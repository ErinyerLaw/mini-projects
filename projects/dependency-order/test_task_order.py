import unittest

from task_order import order_tasks


class TaskOrderTests(unittest.TestCase):
    def test_orders_tasks_after_dependencies(self):
        text = "shop:\ncook: shop\neat: cook\nclean: eat\n"
        self.assertEqual(order_tasks(text), ["shop", "cook", "eat", "clean"])

    def test_independent_tasks_keep_input_order(self):
        text = "write:\nread:\npublish: write read\n"
        self.assertEqual(order_tasks(text), ["write", "read", "publish"])

    def test_dependency_can_be_declared_later(self):
        self.assertEqual(order_tasks("finish: start\nstart:\n"), ["start", "finish"])

    def test_rejects_cycle(self):
        with self.assertRaisesRegex(ValueError, "цикл"):
            order_tasks("a: b\nb: a\n")

    def test_rejects_unknown_dependency(self):
        with self.assertRaisesRegex(ValueError, "не найдена"):
            order_tasks("a: missing\n")

    def test_rejects_duplicate_task_and_dependency(self):
        for text in ("a:\na:\n", "a: b b\nb:\n"):
            with self.subTest(text=text), self.assertRaises(ValueError):
                order_tasks(text)

    def test_rejects_empty_and_bad_lines(self):
        for text in ("\n", "a\n", ": a\n", "two words:\n"):
            with self.subTest(text=text), self.assertRaises(ValueError):
                order_tasks(text)


if __name__ == "__main__":
    unittest.main()
