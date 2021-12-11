#include <bits/stdc++.h>
using namespace std;

int board[10][10];
int original[10][10];
int dr[8] = { 0, 1, 0, -1, 1, -1, 1, -1 };
int dc[8] = { -1, 0, 1, 0, 1, -1, -1, 1 };

void printBoard(int (&currBoard)[10][10]) {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      cout << currBoard[i][j];
    }
    cout << endl;
  }
  cout << endl;
}

void reset() {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      board[i][j] = original[i][j];
    }
  }
}

void parseInput() {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      char c;
      cin >> c;
      board[i][j] = c - '0';
      original[i][j] = board[i][j];
    }
  }
}

int simulate() {
  int newBoard[10][10];
  bool flashing[10][10];
  bool canUpdate = false;
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      newBoard[i][j] = board[i][j] + 1;
      flashing[i][j] = false;
      if (newBoard[i][j] > 9) {
        canUpdate = true;
      }
    }
  }

  while (canUpdate) {
    canUpdate = false;
    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 10; j++) {
        if (newBoard[i][j] > 9 && !flashing[i][j]) {
          flashing[i][j] = true;
          for (int k = 0; k < 8; k++) {
            int newI = i + dr[k];
            int newJ = j + dc[k];
            if (newI >= 0 && newI < 10 && newJ >= 0 && newJ < 10) {
              newBoard[newI][newJ]++;
              if (newBoard[newI][newJ] > 9 && !flashing[newI][newJ]) {
                canUpdate = true;
              }
            }
          }
        }
      }
    }
  }

  int countFlash = 0;
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      board[i][j] = newBoard[i][j];
      if (flashing[i][j]) {
        countFlash++;
        board[i][j] = 0;
      }
    }
  }
  return countFlash;
}

int firstPart() {
  reset();
  int ans = 0;
  for (int i = 0; i < 100; i++) {
    ans += simulate();
  }
  return ans;
}

int secondPart() {
  reset();
  int step = 0;
  while (true) {
    step++;
    if (simulate() == 100) {
      break;
    }
  }
  return step;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  parseInput();

  cout << firstPart() << endl;
  cout << secondPart() << endl;
}
