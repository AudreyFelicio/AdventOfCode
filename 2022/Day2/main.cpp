#include <bits/stdc++.h>

using namespace std;

auto main() -> int {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  char move;
  char opponent;
  bool turn = false;
  int64_t score = 0;
  ifstream input("input.txt");
  while (input >> move) {
    if (!turn) {
      opponent = move;
      turn = !turn;
      continue;
    }
    switch (move) {
      case 'X':
        score += 1;
        if (opponent == 'A') {
          score += 3;
        } else if (opponent == 'B') {
          score += 0;
        } else {
          score += 6;
        }
        break;
      case 'Y':
        score += 2;
        if (opponent == 'A') {
          score += 6;
        } else if (opponent == 'B') {
          score += 3;
        } else {
          score += 0;
        }
        break;
      case 'Z':
        score += 3;
        if (opponent == 'A') {
          score += 0;
        } else if (opponent == 'B') {
          score += 6;
        } else {
          score += 3;
        }
        break;
    }
    turn = !turn;
  }
  cout << "Part 1: " << score << endl;


  turn = false;
  score = 0;
  input = ifstream("input.txt");
  unordered_map<char, int64_t> lose = {{'A', 3}, {'B', 1}, {'C', 2}};
  unordered_map<char, int64_t> draw = {{'A', 4}, {'B', 5}, {'C', 6}};
  unordered_map<char, int64_t> win = {{'A', 8}, {'B', 9}, {'C', 7}};
  while (input >> move) {
    if (!turn) {
      opponent = move;
      turn = !turn;
      continue;
    }
    switch (move) {
      case 'X':
        score += lose[opponent];
        break;
      case 'Y':
        score += draw[opponent];
        break;
      case 'Z':
        score += win[opponent];
        break;
    }
    turn = !turn;
  }
  cout << "Part 2: " << score << endl;
}
