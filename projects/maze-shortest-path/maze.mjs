import { readFile } from 'node:fs/promises';
import { resolve } from 'node:path';
import { fileURLToPath } from 'node:url';

export function solveMaze(text) {
  const rows = text.replace(/\r/g, '').replace(/\n+$/, '').split('\n');
  const width = rows[0]?.length ?? 0;
  const height = rows.length;

  if (width === 0 || rows.some((row) => row.length !== width)) {
    throw new Error('Лабиринт должен быть непустым прямоугольником.');
  }

  let start = -1;
  let goal = -1;
  for (let y = 0; y < height; y++) {
    for (let x = 0; x < width; x++) {
      const cell = rows[y][x];
      const index = y * width + x;
      if (!'#.SG'.includes(cell)) {
        throw new Error(`Недопустимый символ ${JSON.stringify(cell)} в строке ${y + 1}.`);
      }
      if (cell === 'S') {
        if (start !== -1) throw new Error('Нужна ровно одна стартовая клетка S.');
        start = index;
      }
      if (cell === 'G') {
        if (goal !== -1) throw new Error('Нужна ровно одна конечная клетка G.');
        goal = index;
      }
    }
  }
  if (start === -1 || goal === -1) {
    throw new Error('Лабиринт должен содержать одну S и одну G.');
  }

  const parent = Array(width * height).fill(-1);
  const queue = [start];
  parent[start] = start;
  let head = 0;

  while (head < queue.length && parent[goal] === -1) {
    const current = queue[head++];
    const x = current % width;
    const y = Math.floor(current / width);

    for (const [dx, dy] of [[0, -1], [1, 0], [0, 1], [-1, 0]]) {
      const nextX = x + dx;
      const nextY = y + dy;
      if (nextX < 0 || nextX >= width || nextY < 0 || nextY >= height) continue;
      if (rows[nextY][nextX] === '#') continue;
      const next = nextY * width + nextX;
      if (parent[next] !== -1) continue;
      parent[next] = current;
      queue.push(next);
    }
  }

  if (parent[goal] === -1) return null;

  const picture = rows.map((row) => [...row]);
  let steps = 0;
  for (let cell = goal; cell !== start; cell = parent[cell]) {
    if (cell !== goal) picture[Math.floor(cell / width)][cell % width] = '*';
    steps++;
  }
  return { steps, drawing: picture.map((row) => row.join('')).join('\n') };
}

async function main() {
  if (process.argv.length !== 3) {
    console.error('Использование: node maze.mjs <файл-лабиринт>');
    process.exitCode = 1;
    return;
  }

  try {
    const result = solveMaze(await readFile(process.argv[2], 'utf8'));
    console.log(result ? `Шагов: ${result.steps}\n${result.drawing}` : 'Путь не найден.');
  } catch (error) {
    console.error(`Ошибка: ${error.message}`);
    process.exitCode = 1;
  }
}

if (process.argv[1] && resolve(process.argv[1]) === fileURLToPath(import.meta.url)) {
  await main();
}

