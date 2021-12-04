#include <bits/stdc++.h>
using namespace std;

struct Board {
  pair<int, bool> cells[5][5];
};

bool checkWin(Board &b) {
  for (int i = 0; i < 5; i++) {
    bool winRow = true;
    bool winCol = true;
    for (int j = 0; j < 5; j++) {
      winRow = winRow && b.cells[i][j].second;
      winCol = winCol && b.cells[j][i].second;
    }
    if (winRow || winCol) {
      return true;
    }
  }

  return false;
}

int computeBoardSum(Board &b) {
  int sum = 0;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      if (!b.cells[i][j].second) {
        sum += b.cells[i][j].first;
      }
    }
  }
  return sum;
}

vector<int> draws;
vector<Board> boards;

void parseDraws() {
  string line;
  getline(cin, line);
  
  string token = "";
  for (int i = 0; i < line.size(); i++) {
    if (line[i] == ',') {
      draws.push_back(stoi(token));
      token = "";
      continue;
    }
    token += line[i];
  }
  draws.push_back(stoi(token));
}

void parseBoard() {
  Board board;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      int curr;
      cin >> curr;
      board.cells[i][j] = { curr, false };
    }
  }
  boards.push_back(board);
}

void markBoards(int indicator) {
  for (int i = 0; i < boards.size(); i++) {
    for (int j = 0; j < 5; j++) {
      for (int k = 0; k < 5; k++) {
        if (boards[i].cells[j][k].first == indicator) {
          boards[i].cells[j][k].second = true;
        }
      }
    }
  }
}

int firstPart() {
  for (int i = 0; i < draws.size(); i++) {
    markBoards(draws[i]);
    for (int j = 0; j < boards.size(); j++) {
      bool isWinning = checkWin(boards[j]);
      if (isWinning) {
        return computeBoardSum(boards[j]) * draws[i];
      }
    }
  }
  return -1;
}

int secondPart() {
  vector<bool> winningBoards(boards.size(), false);
  int countNotWin = boards.size();
  for (int i = 0; i < draws.size(); i++) {
    markBoards(draws[i]);
    for (int j = 0; j < boards.size(); j++) {
      bool isWinning = checkWin(boards[j]);
      if (isWinning && !winningBoards[j]) {
        winningBoards[j] = true;
        if (countNotWin == 1) {
          // This is the last winning board
          return computeBoardSum(boards[j]) * draws[i];
        }
        countNotWin--;
      }
    }
  }
  return -1;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  parseDraws();
  string emptyLine;
  while (getline(cin, emptyLine)) {
    parseBoard();
  }

  cout << firstPart() << endl;
  cout << secondPart() << endl;
}
