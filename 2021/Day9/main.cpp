#include <bits/stdc++.h>
using namespace std;

int heights[1010][1010];
int dr[4] = { 0, 1, 0, -1 };
int dc[4] = { 1, 0, -1, 0 };
int rows = 0;
int cols = 0;
vector< pair<int, int> > lowestPoints;
bool visited[1010][1010];

void parseInput() {
  string line;
  while (getline(cin, line)) {
    cols = line.size();
    for (int j = 0; j < line.size(); j++) {
      heights[rows][j] = line[j] - '0';
    }
    rows++;
  }
}

void findLowestPoints() {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      bool lowest = true;
      for (int k = 0; k < 4; k++) {
        int newI = dr[k] + i;
        int newJ = dc[k] + j;
        if (newI >= 0 && newI < rows && newJ >= 0 && newJ < cols) {
          lowest = lowest && heights[i][j] < heights[newI][newJ];
        }
      }
      if (lowest) {
        lowestPoints.push_back({ i, j });
      }
    }
  }
}

void floodFill(pair<int, int> curr, int &size) {
  int i = curr.first;
  int j = curr.second;
  visited[i][j] = true;
  size++;
  for (int k = 0; k < 4; k++) {
    int newI = i + dr[k];
    int newJ = j + dc[k];
    if (newI >= 0 && newI < rows && newJ >= 0 && newJ < cols) {
      if (heights[i][j] < heights[newI][newJ] && heights[newI][newJ] != 9 && !visited[newI][newJ]) {
        visited[newI][newJ] = true;
        floodFill({ newI, newJ }, size);
      }
    }
  }
}

int firstPart() {
  int ans = 0;
  for (int i = 0; i < lowestPoints.size(); i++) {
    ans += 1 + heights[lowestPoints[i].first][lowestPoints[i].second];
  }
  return ans;
}

int secondPart() {
  memset(visited, false, sizeof(visited));
  vector<int> sizes;
  for (int i = 0; i < lowestPoints.size(); i++) {
    int currSize = 0;
    floodFill(lowestPoints[i], currSize);
    sizes.push_back(currSize);
  }
  sort(sizes.begin(), sizes.end());
  int len = sizes.size();
  return sizes[len - 1] * sizes[len - 2] * sizes[len - 3];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  parseInput();

  findLowestPoints();
  cout << firstPart() << endl;
  cout << secondPart() << endl;
}
