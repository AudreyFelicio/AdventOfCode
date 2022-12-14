#include <bits/stdc++.h>

using namespace std;

#define BOARD_SIZE 1001

auto drawWalls(vector<vector<char>>& board, const string& line) -> void {
  auto convertToPair = [](const string& s) -> pair<int, int> {
    auto idx = s.find(",");
    return {stoi(s.substr(0, idx)), stoi(s.substr(idx + 1))};
  };

  auto drawLine = [&](const pair<int, int>& start, const pair<int, int>& end) -> void {
    if (start.first == end.first) {
      for (int i = min(start.second, end.second); i <= max(start.second, end.second); ++i) {
        board[i][start.first] = '#';
      }
    } else {
      for (int i = min(start.first, end.first); i <= max(start.first, end.first); ++i) {
        board[start.second][i] = '#';
      }
    }
  };

  const string SEPARATOR = " -> ";

  auto idx = line.find(SEPARATOR);
  auto start = convertToPair(line.substr(0, idx));
  while (idx != string::npos) {
    idx += 4;
    auto next = line.find(SEPARATOR, idx);
    if (next == string::npos) break;
    auto end = convertToPair(line.substr(idx, next - idx));
    drawLine(start, end);
    start = end;
    idx = next;
  }
  drawLine(start, convertToPair(line.substr(idx)));
}

auto dropSand(vector<vector<char>>& board, int lowest) -> bool {
  pair<int, int> location = {0, 500};
  for(;;) {
    auto& [x, y] = location;
    if (x > lowest) return false;
    if (board[x + 1][y] == '.') {
      x++;
    } else if (board[x + 1][y - 1] == '.') {
      y--;
      x++;
    } else if (board[x + 1][y + 1] == '.') {
      y++;
      x++;
    } else {
      break;
    }
  }
  board[location.first][location.second] = 'o';
  return true;
}

auto dropSand2(vector<vector<char>>& board) -> bool {
  pair<int, int> location = {0, 500};
  for(;;) {
    auto& [x, y] = location;
    // cout << x << " " << y << endl;
    if (board[x + 1][y] == '.') {
      x++;
    } else if (board[x + 1][y - 1] == '.') {
      y--;
      x++;
    } else if (board[x + 1][y + 1] == '.') {
      y++;
      x++;
    } else {
      break;
    }
  }
  board[location.first][location.second] = 'o';
  return !(location.first == 0 && location.second == 500);
}

auto main() -> int {
  ifstream input("./input.txt");
  vector<vector<char>> board(BOARD_SIZE, vector<char>(BOARD_SIZE, '.'));

  string line;
  while (getline(input, line)) {
    drawWalls(board, line);
  }

  vector<vector<char>> board2 = board;

  int lowest_wall = 0;
  for (int i = 0; i < BOARD_SIZE; ++i) {
    for (int j = 0; j < BOARD_SIZE; ++j) {
      if (board[i][j] == '#') {
        lowest_wall = max(lowest_wall, i);
      }
    }
  }

  int part1 = 0;
  for(;;) {
    if (!dropSand(board, lowest_wall)) break;
    part1++;
  }
  cout << "Part 1: " << part1 << endl;

  int part2 = 0;
  drawWalls(board2, "0," + to_string(lowest_wall + 2) + " -> " + "1000," + to_string(lowest_wall + 2));
  for(;;) {
    part2++;
    if (!dropSand2(board2)) break;
  }
  cout << "Part 2: " << part2 << endl;
}
