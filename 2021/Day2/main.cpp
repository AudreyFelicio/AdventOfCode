#include <bits/stdc++.h>
using namespace std;

vector< pair<string, int> > instructions;

void tokenize(string &line) {
  vector<string> tokens;
  string token = "";
  for (int i = 0; i < line.size(); i++) {
    if (line[i] == ' ') {
      tokens.push_back(token);
      token = "";
      continue;
    }
    token += line[i];
  }
  tokens.push_back(token);

  instructions.push_back({ tokens[0], stoi(tokens[1]) });
}

void parseInput() {
  string line;
  while (getline(cin, line)) {
    tokenize(line);
  }
}

int firstPart() {
  int n = instructions.size();
  int forward = 0;
  int depth = 0;
  for (int i = 0; i < n; i++) {
    if (instructions[i].first == "forward") {
      forward += instructions[i].second;
    } else if (instructions[i].first == "up") {
      depth -= instructions[i].second;
    } else {
      depth += instructions[i].second;
    }
  }

  return forward * depth;
}

int secondPart() {
  int n = instructions.size();
  int forward = 0;
  int depth = 0;
  int aim = 0;
  for (int i = 0; i < n; i++) {
    if (instructions[i].first == "forward") {
      forward += instructions[i].second;
      depth += aim * instructions[i].second;
    } else if (instructions[i].first == "up") {
      aim -= instructions[i].second;
    } else {
      aim += instructions[i].second;
    }
  }

  return forward * depth;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  parseInput();

  cout << firstPart() << endl;
  cout << secondPart() << endl;
}
