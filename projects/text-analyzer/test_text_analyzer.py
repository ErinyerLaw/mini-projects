import unittest

from text_analyzer import analyze_text, extract_words, format_report


class TextAnalyzerTests(unittest.TestCase):
    def test_extract_words_supports_russian_and_hyphens(self):
        text = "Привет, мир! Это мини-проект. Привет."
        self.assertEqual(
            extract_words(text),
            ["привет", "мир", "это", "мини-проект", "привет"],
        )

    def test_analyze_text_counts_main_metrics(self):
        stats = analyze_text("One fish. Two fish!\n\nRed fish?", top=2, words_per_minute=2)
        self.assertEqual(stats["words"], 6)
        self.assertEqual(stats["unique_words"], 4)
        self.assertEqual(stats["sentences"], 3)
        self.assertEqual(stats["paragraphs"], 2)
        self.assertEqual(stats["reading_time_minutes"], 3.0)
        self.assertEqual(stats["top_words"], [("fish", 3), ("one", 1)])

    def test_empty_text_has_zero_metrics(self):
        stats = analyze_text("")
        self.assertEqual(stats["words"], 0)
        self.assertEqual(stats["sentences"], 0)
        self.assertEqual(stats["paragraphs"], 0)
        self.assertEqual(stats["top_words"], [])

    def test_invalid_options_are_rejected(self):
        with self.assertRaises(ValueError):
            analyze_text("text", top=-1)
        with self.assertRaises(ValueError):
            analyze_text("text", words_per_minute=0)

    def test_report_contains_human_readable_summary(self):
        report = format_report(analyze_text("Hello hello world."))
        self.assertIn("Words: 3", report)
        self.assertIn("hello (2)", report)


if __name__ == "__main__":
    unittest.main()

