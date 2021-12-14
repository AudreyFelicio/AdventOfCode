#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

string original = "";
string curr = "";
unordered_map<string, string> mapper;

void parseInput() {
  getline(cin, original);
  curr = original;
  string line;
  getline(cin, line);
  while (getline(cin, line)) {
    string first = line.substr(0, line.find(" -> "));
    string second = line.substr(line.find(" -> ") + 4);
    mapper[first] = second;
  }
}

void step() {
  string now = "";
  for (int i = 0; i < curr.size() - 1; i++) {
    string extra = mapper[curr.substr(i, 2)];
    now += curr[i];
    now += extra;
  }
  curr = now + curr[curr.size() - 1];
}

ll computeMinMax(unordered_map<char, ll> &occur) {
  ll maximum = 0;
  ll minimum = __LONG_LONG_MAX__;
  for (auto [character, count] : occur) {
    maximum = max(count, maximum);
    minimum = min(count, minimum);
  }
  return maximum - minimum;
}

ll firstPart() {
  for (int i = 0; i < 10; i++) {
    step();
  }
  unordered_map<char, ll> occur;
  for (int i = 0; i < curr.size(); i++) {
    occur[curr[i]]++;
  }
  return computeMinMax(occur);
}

ll secondPart() {
  curr = original;
  unordered_map<char, ll> count;
  unordered_map<string, ll> insertionCount;
  for (int i = 0; i < curr.size(); i++) {
    count[curr[i]]++;
  }
  for (int i = 0; i < curr.size() - 1; i++) {
    insertionCount[curr.substr(i, 2)]++;
  }
  for (int i = 0; i < 40; i++) {
    unordered_map<string, ll> temp;
    for (auto [curr, num] : insertionCount) {
      string generated = mapper[curr];
      temp[curr] -= num;
      temp[generated + curr[1]] += num;
      temp[curr[0] + generated] += num;
      count[generated[0]] += num;
    }
    for (auto [curr, num] : temp) {
      insertionCount[curr] += num;
    }
  }
  return computeMinMax(count);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  parseInput();

  cout << firstPart() << endl;
  cout << secondPart() << endl;
}
