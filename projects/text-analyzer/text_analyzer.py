"""Small command-line text analyzer with no external dependencies."""

from __future__ import annotations

import argparse
import json
import re
import sys
from collections import Counter
from pathlib import Path
from typing import Any


WORD_PATTERN = re.compile(r"[^\W\d_]+(?:[-'’][^\W\d_]+)*", re.UNICODE)
SENTENCE_PATTERN = re.compile(r"[.!?]+")


def extract_words(text: str) -> list[str]:
    """Return normalized words while keeping hyphenated words together."""
    return [match.group(0).lower() for match in WORD_PATTERN.finditer(text)]


def analyze_text(text: str, top: int = 5, words_per_minute: int = 200) -> dict[str, Any]:
    """Calculate useful text statistics."""
    if top < 0:
        raise ValueError("top must be zero or greater")
    if words_per_minute <= 0:
        raise ValueError("words_per_minute must be greater than zero")

    words = extract_words(text)
    word_counts = Counter(words)
    stripped = text.strip()
    paragraphs = [part for part in re.split(r"\n\s*\n", stripped) if part.strip()]

    return {
        "characters": len(text),
        "characters_without_spaces": sum(not char.isspace() for char in text),
        "words": len(words),
        "unique_words": len(word_counts),
        "sentences": len(SENTENCE_PATTERN.findall(text)) if stripped else 0,
        "paragraphs": len(paragraphs),
        "reading_time_minutes": round(len(words) / words_per_minute, 2),
        "top_words": word_counts.most_common(top),
    }


def format_report(stats: dict[str, Any]) -> str:
    """Format statistics as a readable console report."""
    top_words = stats["top_words"]
    frequent = ", ".join(f"{word} ({count})" for word, count in top_words) or "—"

    return "\n".join(
        [
            "Text analysis",
            f"Characters: {stats['characters']}",
            f"Characters without spaces: {stats['characters_without_spaces']}",
            f"Words: {stats['words']}",
            f"Unique words: {stats['unique_words']}",
            f"Sentences: {stats['sentences']}",
            f"Paragraphs: {stats['paragraphs']}",
            f"Estimated reading time: {stats['reading_time_minutes']:.2f} min",
            f"Most frequent words: {frequent}",
        ]
    )


def read_text(path: str) -> str:
    """Read UTF-8 text from a file or stdin when path is '-' ."""
    if path == "-":
        return sys.stdin.read()
    return Path(path).read_text(encoding="utf-8")


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(description="Analyze a UTF-8 text file.")
    parser.add_argument("path", help="Path to a text file, or '-' to read from stdin")
    parser.add_argument("--top", type=int, default=5, help="number of frequent words to show")
    parser.add_argument("--wpm", type=int, default=200, help="reading speed in words per minute")
    parser.add_argument("--json", action="store_true", help="print machine-readable JSON")
    return parser


def main() -> None:
    args = build_parser().parse_args()
    try:
        stats = analyze_text(read_text(args.path), top=args.top, words_per_minute=args.wpm)
    except (OSError, UnicodeError, ValueError) as error:
        raise SystemExit(f"Error: {error}") from error

    if args.json:
        print(json.dumps(stats, ensure_ascii=False, indent=2))
    else:
        print(format_report(stats))


if __name__ == "__main__":
    main()

