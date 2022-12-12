#include <bits/stdc++.h>

using namespace std;

struct Info {
  int i, j, dist;
};

int dr[4] = {0, 1, 0, -1};
int dc[4] = {1, 0, -1, 0};

auto solve(int part) {
  ifstream input("./input.txt");
  vector<string> board;
  string s;
  while (getline(input, s)) {
    board.push_back(s);
  }
  int h = board.size();
  int w = board[0].size();
  vector<vector<bool>> visited(h, vector<bool>(w, false));
  queue<Info> q;
  pair<int, int> goal;
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      if (board[i][j] == 'S') {
        q.push({i, j, 0});
        board[i][j] = 'a';
        visited[i][j] = true;
      } else if (board[i][j] == 'E') {
        goal = {i, j};
        board[i][j] = 'z';
      } else if (board[i][j] == 'a' && part == 2) {
        q.push({i, j, 0});
        visited[i][j] = true;
      }
    }
  }
  int total = 0;
  while (!q.empty()) {
    auto [x, y, d] = q.front(); q.pop();
    if (make_pair(x, y) == goal) {
      total = d;
      break;
    }
    for (int k = 0; k < 4; ++k) {
      int newX = x + dr[k];
      int newY = y + dc[k];
      if (newX >= 0 && newX < h && newY >= 0 && newY < w) {
        if (board[newX][newY] <= board[x][y] + 1 && !visited[newX][newY]) {
          visited[newX][newY] = true;
          q.push({newX, newY, d + 1});
        }
      }
    }
  }
  cout << "Part "<< part << ": " << total << endl;
}

auto main() -> int {
  solve(1);
  solve(2);
}
