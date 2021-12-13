#include <bits/stdc++.h>
using namespace std;

bool board[1500][1500];
vector< pair<bool, int> > ins;
int currX = 0;
int currY = 0;

void parseInput() {
  string line;
  while (getline(cin, line)) {
    if (line == "") {
      break;
    }
    string first = line.substr(0, line.find(","));
    string second = line.substr(line.find(",") + 1);
    board[stoi(second)][stoi(first)] = true;
    currX = max(currX, stoi(first));
    currY = max(currY, stoi(second));
  }

  while (getline(cin, line)) {
    int start = 0;
    int end = line.find(" ");
    string curr = "";
    while (end != string::npos) {
      start = end + 1;
      end = line.find(" ", start);
    }
    curr = line.substr(start);
    int axis = stoi(curr.substr(curr.find("=") + 1));
    if (curr[0] == 'x') {
      ins.push_back({ true, axis });
    } else {
      ins.push_back({ false, axis });
    }
  }
}

void fold(pair<bool, int> &instruction) {
  int axis = instruction.second;
  if (instruction.first) {
    // fold left
    for (int j = axis + 1; j <= currX; j++) {
      for (int i = 0; i <= currY; i++) {
        if (board[i][j]) {
          board[i][j - (2 * (j - axis))] = true;
        }
      }
    }
    currX = axis - 1;
  } else {
    // fold up
    for (int i = axis + 1; i <= currY; i++) {
      for (int j = 0; j <= currX; j++) {
        if (board[i][j]) {
          board[i - (2 * (i - axis))][j] = true;
        }
      }
    }
    currY = axis - 1;
  }
}

int count() {
  int total = 0;
  for (int i = 0; i <= currY; i++) {
    for (int j = 0; j <= currX; j++) {
      if (board[i][j]) {
        total++;
      }
    }
  }
  return total;
}

void printBoard() {
  for (int i = 0; i <= currY; i++) {
    for (int j = 0; j <= currX; j++) {
      cout << board[i][j];
    }
    cout << endl;
  }
}

int firstPart() {
  fold(ins[0]);
  return count();
}

void secondPart() {
  for (int i = 1; i < ins.size(); i++) {
    fold(ins[i]);
  }
  printBoard();
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  memset(board, false, sizeof(board));

  parseInput();

  cout << firstPart() << endl;
  secondPart();
}
