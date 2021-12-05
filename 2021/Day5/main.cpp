#include <bits/stdc++.h>
using namespace std;

struct Vent {
  int x1;
  int y1;
  int x2;
  int y2;
};

int w = 0, h = 0;
vector<Vent> vents;

void parseLine(string &line) {
  string delimiter = " -> ";
  string first = line.substr(0, line.find(delimiter));
  string second = line.substr(line.find(delimiter) + delimiter.length());
  string commaDelimiter = ",";
  int x1 = stoi(first.substr(0, first.find(commaDelimiter)));
  int y1 = stoi(first.substr(first.find(commaDelimiter) + 1));
  int x2 = stoi(second.substr(0, second.find(commaDelimiter)));
  int y2 = stoi(second.substr(second.find(commaDelimiter) + 1));
  vents.push_back({ x1, y1, x2, y2 });
  w = max(max(x1, x2), w);
  h = max(max(y1, y2), h);
}

void parseInput() {
  string line;
  while (getline(cin, line)) {
    parseLine(line);
  }
}

int firstPart() {
  // Fill up board
  vector<vector<int>> board(h + 1, vector<int>(w + 1, 0));
  for (int i = 0; i < vents.size(); i++) {
    if (vents[i].x1 == vents[i].x2 || vents[i].y1 == vents[i].y2) {
      for (int j = min(vents[i].x1, vents[i].x2); j <= max(vents[i].x1, vents[i].x2); j++) {
        for (int k = min(vents[i].y1, vents[i].y2); k <= max(vents[i].y1, vents[i].y2); k++) {
          board[k][j]++;
        }
      }
    }
  }

  int ans = 0;
  for (int i = 0; i <= h; i++) {
    for (int j = 0; j <= w; j++) {
      if (board[i][j] >= 2) {
        ans++;
      }
    }
  }
  return ans;
}

int secondPart() {
    // Fill up board
  vector<vector<int>> board(h + 1, vector<int>(w + 1, 0));
  for (int i = 0; i < vents.size(); i++) {
    if (vents[i].x1 == vents[i].x2 || vents[i].y1 == vents[i].y2) {
      for (int j = min(vents[i].x1, vents[i].x2); j <= max(vents[i].x1, vents[i].x2); j++) {
        for (int k = min(vents[i].y1, vents[i].y2); k <= max(vents[i].y1, vents[i].y2); k++) {
          board[k][j]++;
        }
      }
      continue;
    }
    // Fill diagonals
    int dist = max(vents[i].x1, vents[i].x2) - min(vents[i].x1, vents[i].x2);
    int currX = vents[i].x1;
    int currY = vents[i].y1;
    if (vents[i].x1 > vents[i].x2 && vents[i].y1 > vents[i].y2) {
      for (int k = 0; k <= dist; k++) {
        board[currY - k][currX - k]++;
      }
    } else if (vents[i].x1 > vents[i].x2 && vents[i].y1 < vents[i].y2) {
      for (int k = 0; k <= dist; k++) {
        board[currY + k][currX - k]++;
      }
    } else if (vents[i].x1 < vents[i].x2 && vents[i].y1 > vents[i].y2) {
      for (int k = 0; k <= dist; k++) {
        board[currY - k][currX + k]++;
      }
    } else {
      for (int k = 0; k <= dist; k++) {
        board[currY + k][currX + k]++;
      }
    }
  }

  int ans = 0;
  for (int i = 0; i <= h; i++) {
    for (int j = 0; j <= w; j++) {
      if (board[i][j] >= 2) {
        ans++;
      }
    }
  }
  return ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  parseInput();

  cout << firstPart() << endl;
  cout << secondPart() << endl;
}
