#include <bits/stdc++.h>
using namespace std;

int firstPart(vector<int> &depths) {
  int n = depths.size();
  int ans = 0;
  for (int i = 1; i < n; i++) {
    if (depths[i] > depths[i - 1]) {
      ans++;
    }
  }
  
  return ans;
}

int secondPart(vector<int> &depths) {
  int n = depths.size();
  int ans = 0;
  for (int i = 1; i < n - 2; i++) {
    if (depths[i + 2] > depths[i - 1]) {
      ans++;
    }
  }
  
  return ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL); cout.tie(NULL);

  vector<int> depths;

  int input;
  while (cin >> input) {
    depths.push_back(input);
  }

  cout << firstPart(depths) << endl;
  cout << secondPart(depths) << endl;
}
