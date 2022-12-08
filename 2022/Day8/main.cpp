#include <bits/stdc++.h>

using namespace std;

auto main() -> int {
  ifstream input("./input.txt");

  string line;
  vector<vector<int64_t>> grid;
  while (getline(input, line)) {
    vector<int64_t> curr_row;
    for (auto x : line) {
      curr_row.push_back(x - '0'); 
    }
    grid.push_back(curr_row);
  }
  int64_t count = 0;
  int h = grid.size();
  int w = grid[0].size();
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      int curr = grid[i][j];
      bool acc = false;
      bool visible = true;
      for (int k = i - 1; k >= 0; --k) {
        if (curr <= grid[k][j]) {
          visible = false;
        }
      }
      acc = acc || visible;
      visible = true;
      for (int k = i + 1; k < h; ++k) {
        if (curr <= grid[k][j]) {
          visible = false;
        }
      }
      acc = acc || visible;
      visible = true;
      for (int k = j + 1; k < w; ++k) {
        if (curr <= grid[i][k]) {
          visible = false;
        }
      }
      acc = acc || visible;
      visible = true;
      for (int k = j - 1; k >= 0; --k) {
        if (curr <= grid[i][k]) {
          visible = false;
        }
      }
      acc = acc || visible;
      if (acc) count++;
    }
  }
  cout << "Part 1: " << count << endl;

  int64_t mx = 0;
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      int64_t curr_score = 1LL;
      int64_t curr = grid[i][j];
      int64_t dir = 0LL;
      for (int k = i - 1; k >= 0; --k) {
        dir++;
        if (curr <= grid[k][j]) {
          break;
        }
      }
      curr_score *= dir;
      dir = 0;
      for (int k = i + 1; k < h; ++k) {
        dir++;
        if (curr <= grid[k][j]) {
          break;
        }
      }
      curr_score *= dir;
      dir = 0;
      for (int k = j + 1; k < w; ++k) {
        dir++;
        if (curr <= grid[i][k]) {
          break;
        }
      }
      curr_score *= dir;
      dir = 0;
      for (int k = j - 1; k >= 0; --k) {
        dir++;
        if (curr <= grid[i][k]) {
          break;
        }
      }
      curr_score *= dir;
      mx = max(curr_score, mx);
    }
  }
  cout << "Part 2: " << mx << endl;
}
