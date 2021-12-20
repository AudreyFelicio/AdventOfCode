#include <bits/stdc++.h>
using namespace std;

int xOffset = 750;
int yOffset = 750;
string imageAlgo = "";
char board[2010][2010];
char copyBoard[2010][2010];
int n = 0, m = 0;
char oddResetVal;
char evenResetVal;

void parseInput() {
  memset(board, '.', sizeof(board));
  getline(cin, imageAlgo);
  string line;
  getline(cin, line);
  while (getline(cin, line)) {
    m = line.size();
    for (int i = 0; i < m; i++) {
      board[n + yOffset][i + xOffset] = line[i];
    }
    n++;
  }
}

int convertToInt(string &s) {
  int ans = 0;
  for (int i = 0; i < s.size(); i++) {
    if (s[i] == '1') ans += (1 << (s.size() - i - 1));
  }
  return ans;
}

char genPixel(int i, int j) {
  string currBinary = "";
  for (int y = -1; y <= 1; y++) {
    for (int x = -1; x <= 1; x++) {
      if (board[i + y + yOffset][j + x + xOffset] == '.') {
        currBinary += '0';
      } else {
        currBinary += '1';
      }
    }
  }
  int index = convertToInt(currBinary);
  return imageAlgo[index];
}

void enhance(int step) {
  memset(copyBoard, step % 2 == 0 ? evenResetVal : oddResetVal, sizeof(copyBoard));
  xOffset--;
  yOffset--;
  n += 2;
  m += 2;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      copyBoard[i + yOffset][j + xOffset] = genPixel(i, j);
    }
  }
  for (int i = 0; i < 2010; i++) {
    for (int j = 0; j < 2010; j++) {
      board[i][j] = copyBoard[i][j];
    }
  }
}

void printBoard() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cout << board[i + yOffset][j + xOffset];
    }
    cout << endl;
  }
}

int countLit() {
  int count = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (board[i + yOffset][j + xOffset] == '#') {
        count++;
      }
    }
  }
  return count;
}

int firstPart() {
  enhance(1);
  enhance(2);
  return countLit();
}

int secondPart() {
  for (int i = 3; i <= 50; i++) {
    enhance(i);
  }
  return countLit();
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  
  parseInput();
  oddResetVal = imageAlgo[0];
  evenResetVal = imageAlgo[511];

  cout << firstPart() << endl;
  cout << secondPart() << endl;
}
