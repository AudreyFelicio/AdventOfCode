#include <bits/stdc++.h>
using namespace std;

int minX, maxX, minY, maxY;

void parseInput() {
  int x1, x2, y1, y2;
  scanf("target area: x=%d..%d, y=%d..%d", &x1, &x2, &y1, &y2);
  minX = min(x1, x2);
  maxX = max(x1, x2);
  minY = min(y1, y2);
  maxY = max(y1, y2);
}

int getXDist(int v, int steps) {
  if (steps >= v) {
    return ((v) * (v + 1)) / 2;
  }
  return v * steps - ((steps - 1) * steps) / 2;
}

int getYDist(int v, int steps) {
  return v * steps - ((steps - 1) * steps) / 2;
}

int firstPart() {
  // maximum height happens when steps = v or v + 1
  int maximal = 0;
  for (int x = 1; x <= maxX; x++) {
    for (int step = 1; step <= 2000; step++) {
      int currDist = getXDist(x, step);
      if (minX <= currDist && maxX >= currDist) {
        // brute force y
        for (int y = 1; y <= 1000; y++) {
          int currYDist = getYDist(y, step);
          if (currYDist >= minY && currYDist <= maxY) {
            maximal = max(maximal, (y * (y + 1)) / 2);
          }
        }
      }
    }
  }
  return maximal;
}

int secondPart() {
  unordered_set<string> locations;
  for (int x = 1; x <= maxX; x++) {
    for (int step = 1; step <= 5000; step++) {
      int currDist = getXDist(x, step);
      if (minX <= currDist && maxX >= currDist) {
        for (int y = -2000; y <= 2000; y++) {
          int currYDist = getYDist(y, step);
          if (currYDist >= minY && currYDist <= maxY) {
            locations.insert(to_string(x) + "," + to_string(y));
          }
        }
      }
    }
  }
  return locations.size();
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  parseInput();

  cout << firstPart() << endl;
  cout << secondPart() << endl;
}
