#include <bits/stdc++.h>
using namespace std;

int cave[510][2525];
int dist[510][2525];
bool visited[510][2525];
int dr[4] = { 0, 1, 0, -1 };
int dc[4] = { -1, 0, 1, 0 };
int rows = 0;
int cols = 0;

int extendedCave[510][2525];
int extendedDist[510][2525];
bool extendedVisited[510][2525];
int extendedRows = 0;
int extendedCols = 0;

struct Info {
  int i, j, d;
};

bool cmp(const Info &i1, const Info &i2) {
  return i1.d > i2.d;
}

void parseInput() {
  string line;
  while (getline(cin, line)) {
    cols = line.size();
    for (int i = 0; i < cols; i++) {
      cave[rows][i] = line[i] - '0';
    }
    rows++;
  }
}

void genExtended() {
  extendedRows = rows * 5;
  extendedCols = cols * 5;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      extendedCave[i][j] = cave[i][j];
      for (int x = 0; x < 5; x++) {
        for (int y = 0; y < 5; y++) {
          extendedDist[i + (x * rows)][j + (y * rows)] = 1e9;
          if (x == 0 && y == 0) {
            continue;
          }
          if (y == 0) {
            if (extendedCave[i + ((x - 1) * rows)][j] == 9) {
              extendedCave[i + (x * rows)][j + (y * rows)] = 1;
            } else {
              extendedCave[i + (x * rows)][j + (y * rows)] = extendedCave[i + ((x - 1) * rows)][j] + 1;
            }
          } else {
            if (extendedCave[i + (x * rows)][j + ((y - 1) * rows)] == 9) {
              extendedCave[i + (x * rows)][j + (y * rows)] = 1;
            } else {
              extendedCave[i + (x * rows)][j + (y * rows)] = extendedCave[i + (x * rows)][j + ((y - 1) * rows)] + 1;
            }
          }
        }
      }
    }
  }
}

void reset() {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      dist[i][j] = 1e9;
    }
  }
}

void printExtended() {
  for (int i = 0; i < extendedRows; i++) {
    for (int j = 0; j < extendedCols; j++) {
      cout << extendedCave[i][j];
    }
    cout << endl;
  }
}

void djikstra(int (&c)[510][2525], int (&d)[510][2525], bool (&v)[510][2525], int limRows, int limCols) {
  priority_queue<Info, vector<Info>, decltype(&cmp)> pq(cmp);
  pq.push({ 0, 0, c[0][0] });
  d[0][0] = c[0][0];
  while (!pq.empty()) {
    auto [currI, currJ, currD] = pq.top(); pq.pop();
    if (v[currI][currJ]) {
      continue;
    }
    v[currI][currJ] = true;
    for (int k = 0; k < 4; k++) {
      int newI = currI + dr[k];
      int newJ = currJ + dc[k];
      if (newI >= 0 && newI < limRows && newJ >= 0 && newJ < limCols) {
        int update = d[currI][currJ] + c[newI][newJ];
        if (update < d[newI][newJ]) {
          d[newI][newJ] = update;
          pq.push({ newI, newJ, update });
        }
      }
    }
  }
}

int firstPart() {
  memset(visited, false, sizeof(visited));
  reset();
  djikstra(cave, dist, visited, rows, cols);
  return dist[rows - 1][cols - 1] - cave[0][0];
}

int secondPart() {
  memset(extendedVisited, false, sizeof(extendedVisited));
  djikstra(extendedCave, extendedDist, extendedVisited, extendedRows, extendedCols);
  return extendedDist[extendedRows - 1][extendedCols - 1] - extendedCave[0][0];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  parseInput();
  genExtended();

  cout << firstPart() << endl;
  cout << secondPart() << endl;
}
