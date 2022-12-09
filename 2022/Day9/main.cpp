#include <bits/stdc++.h>

using namespace std;

#define BOARD_SIZE 4000

auto solveKnots(int knots) -> int {
  ifstream input("./input.txt");
  vector<vector<char>> board(BOARD_SIZE, vector<char>(BOARD_SIZE, '.'));
  vector<vector<bool>> visited(BOARD_SIZE, vector<bool>(BOARD_SIZE, false));

  auto pull = [](pair<int, int>& p1, pair<int, int>& p2) {
    if (abs(p1.first - p2.first) <= 1 && abs(p1.second - p2.second) <= 1) return;
    if (p1.second == p2.second - 2) {
      p2.second = p1.second + 1;
      if (p1.first < p2.first) {
        p2.first--;
      } else if (p1.first > p2.first) {
        p2.first++;
      }
    } else if (p1.second == p2.second + 2) {
      p2.second = p1.second - 1;
      if (p1.first < p2.first) {
        p2.first--;
      } else if (p1.first > p2.first) {
        p2.first++;
      }
    } else if (p1.first == p2.first - 2) {
      p2.first = p1.first + 1;
      if (p1.second < p2.second) {
        p2.second--;
      } else if (p1.second > p2.second) {
        p2.second++;
      }
    } else if (p1.first == p2.first + 2) {
      p2.first = p1.first - 1;
      if (p1.second < p2.second) {
        p2.second--;
      } else if (p1.second > p2.second) {
        p2.second++;
      }
    }
  };

  vector<pair<int, int>> rope(knots, {BOARD_SIZE / 2, BOARD_SIZE / 2});
  visited[rope.back().first][rope.back().second] = true;
  char dir;
  int steps;
  while (input >> dir >> steps) {
    while (steps--) {
      switch (dir) {
      case 'R':
        rope[0].second++;
        break;
      case 'U':
        rope[0].first--;
        break;
      case 'L':
        rope[0].second--;
        break;
      case 'D':
        rope[0].first++;
        break;
      default:
        break;
      }
      for (int i = 0; i < knots - 1; ++i) {
        pull(rope[i], rope[i + 1]);
      }
      visited[rope.back().first][rope.back().second] = true;
    }
  }
  int total = 0;
  for (auto& v : visited) {
    for (auto b : v) {
      if (b) total++;
    }
  }
  return total;
}

auto main() -> int {
  cout << "Part 1: " << solveKnots(2) << endl;
  cout << "Part 2: " << solveKnots(10) << endl;
}
