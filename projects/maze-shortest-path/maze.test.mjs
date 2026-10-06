import test from 'node:test';
import assert from 'node:assert/strict';
import { solveMaze } from './maze.mjs';

test('finds the shortest path and marks only intermediate cells', () => {
  const maze = 'S..#G\n##.#.\n.....';
  assert.deepEqual(solveMaze(maze), {
    steps: 8,
    drawing: 'S**#G\n##*#*\n..***',
  });
});

test('returns null when the goal is unreachable', () => {
  assert.equal(solveMaze('S#G'), null);
});

test('accepts Windows line endings and a trailing newline', () => {
  assert.deepEqual(solveMaze('S.G\r\n'), { steps: 2, drawing: 'S*G' });
});

test('rejects non-rectangular input', () => {
  assert.throws(() => solveMaze('S.\nG'), /прямоугольником/);
});

test('rejects missing or duplicate endpoints', () => {
  assert.throws(() => solveMaze('S..'), /одну S и одну G/);
  assert.throws(() => solveMaze('SSG'), /ровно одна стартовая/);
});

test('rejects unknown symbols', () => {
  assert.throws(() => solveMaze('S G'), /Недопустимый символ/);
});

