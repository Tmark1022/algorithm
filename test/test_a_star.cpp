/*************************************************************************
 @ Author	: tmark
 @ Created Time	: Sat 06 Feb 2021 11:00:27 AM CST
 @ File Name	: test_a_star.cpp
 @ Description	: 
 ************************************************************************/
#include <algorithm>
#include <array>
#include <chrono>
#include <deque>
#include <functional>
#include <iostream>
#include <memory>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
using chrono::high_resolution_clock;

constexpr int N = 3;
constexpr int dirs[] = {0, 1, 0, -1, 0};

struct Node;
typedef string State;
typedef shared_ptr<Node> NodePtr;
typedef function<int(const State& s, const State& t)> Heuristic;

struct Node {
  Node(State s, NodePtr p = nullptr, int h = 0)
      : s(s), p(p), h(h), g(p ? p->g + 1 : 0), f(this->h + g) {}

  vector<State> GetNextStates() const {
    vector<State> states;
    int index = find(s.begin(), s.end(), '0') - s.begin();
    int x = index % N;
    int y = index / N;
    for (int i = 0; i < 4; ++i) {
      int tx = x + dirs[i];
      int ty = y + dirs[i + 1];
      if (tx < 0 || ty < 0 || tx == N || ty == N) continue;
      int new_index = ty * N + tx;
      State next(s);
      next[index] = s[new_index];
      next[new_index] = '0';
      states.push_back(move(next));
    }
    return states;
  }

  NodePtr p;
  int h;
  int g;
  int f;
  State s;
};

bool Sovlable(const State& s) {
  int inv_count = 0;
  for (int i = 0; i < N * N; ++i) {
    for (int j = i + 1; j < N * N; ++j) {
      if (s[i] != '0' && s[j] != '0' && s[i] > s[j]) {
        ++inv_count;
      }
    }
  }
  return inv_count % 2 == 0;
}

NodePtr GetRoot(NodePtr n) { return n->p ? GetRoot(n->p) : n; }
NodePtr WirePath(NodePtr p, NodePtr n) {
  while (n) {
    NodePtr t = n->p;
    n->p = p;
    p = n;
    n = t;
  }
  return p;
}

void ConstructPath(NodePtr node, vector<State>* path) {
  while (node) {
    path->push_back(node->s);
    node = node->p;
  }
  reverse(path->begin(), path->end());
}

class Solver {
 public:
  virtual bool Solve(State start, State target, vector<State>* path,
                     int* opened, int* closed) = 0;
};

class BFSSolver : public Solver {
 public:
  bool Solve(State start, State target, vector<State>* path, int* opened,
             int* closed) override {
    int expended = 0;
    unordered_set<string> seen;
    deque<NodePtr> q{make_shared<Node>(start)};
    while (!q.empty()) {
      auto cur = q.front();
      q.pop_front();
      ++expended;
      if (cur->s == target) {
        ConstructPath(cur, path);
        *opened = seen.size();
        *closed = expended;
        return true;
      }
      for (const auto& s : cur->GetNextStates()) {
        auto r = seen.insert(s);
        if (!r.second) continue;
        q.push_back(make_shared<Node>(s, cur));
      }
    }
    return false;
  }
};

class BidirectionalBFSSolver : public Solver {
 public:
  bool Solve(State start, State target, vector<State>* path, int* opened,
             int* closed) override {
    auto start_node = make_shared<Node>(start);
    auto target_node = make_shared<Node>(target);
    unordered_map<string, NodePtr> seen0{{start, start_node}};
    unordered_map<string, NodePtr> seen1{{target, target_node}};
    deque<NodePtr> q0{start_node};
    deque<NodePtr> q1{target_node};
    int expended = 0;
    while (!q0.empty()) {
      size_t size = q0.size();
      while (size--) {
        auto cur = q0.front();
        q0.pop_front();
        ++expended;

        for (const auto& s : cur->GetNextStates()) {
          auto n = make_shared<Node>(s, cur);
          auto it = seen1.find(s);
          if (it != seen1.end()) {
            auto p = it->second;
            if (GetRoot(n)->s == target) swap(n, p);
            n = WirePath(n, p->p);
            ConstructPath(n, path);
            *opened = seen0.size() + seen1.size();
            *closed = expended;
            return true;
          }

          if (seen0.count(s)) continue;
          seen0[s] = n;
          q0.push_back(n);
        }
      }

      if (q1.size() < q0.size()) {
        swap(q0, q1);
        swap(seen0, seen1);
      }
    }
    return false;
  }

 private:
};

struct NodeCompare : public binary_function<NodePtr, NodePtr, bool> {
  bool operator()(const NodePtr& x, const NodePtr& y) const {
    return x->f > y->f;
  }
};

int ManhattanDistance(const State& s, const State& t) {
  int h = 0;
  for (int i1 = 0; i1 < N * N; ++i1) {
    int i2 = t.find(s[i1]);
    int x1 = i1 % N;
    int y1 = i1 / N;
    int x2 = i2 % N;
    int y2 = i2 / N;
    h += abs(x1 - x2) + abs(y1 - y2);
  }
  return h;
}

int HammingDistance(const State& s, const State& t) {
  int h = 0;
  for (size_t i = 0; i < s.size(); ++i) {
    if (s[i] != t[i]) ++h;
  }
  return h;
}

class AStarSolver : public Solver {
 public:
  explicit AStarSolver(Heuristic heuristic) : heuristic_(heuristic) {}
  bool Solve(State start, State target, vector<State>* path, int* opened,
             int* closed) override {
    unordered_map<string, NodePtr> o;
    unordered_set<string> c;
    priority_queue<NodePtr, vector<NodePtr>, NodeCompare> q;
    q.emplace(new Node(start, nullptr, heuristic_(start, target)));
    while (!q.empty()) {
      auto cur = q.top();
      q.pop();
      if (cur->s == target) {
        ConstructPath(cur, path);
        *opened = o.size();
        *closed = c.size();
        return true;
      }
      if (!c.insert(cur->s).second) continue;
      for (const auto& s : cur->GetNextStates()) {
        auto it = o.find(s);
        auto n = make_shared<Node>(s, cur, heuristic_(s, target));
        if (it != o.end() && n->f >= it->second->f) continue;
        o[s] = n;
        q.push(n);
      }
    }
    return false;
  }

 private:
  Heuristic heuristic_;
};

class BiAStarSolver : public Solver {
 public:
  explicit BiAStarSolver(Heuristic heuristic) : heuristic_(heuristic) {}
  bool Solve(State start, State target, vector<State>* path, int* opened,
             int* closed) override {
    unordered_map<string, NodePtr> o0, o1;
    unordered_map<string, NodePtr> c0, c1;
    priority_queue<NodePtr, vector<NodePtr>, NodeCompare> q0, q1;
    q0.emplace(new Node(start, nullptr, heuristic_(start, target)));
    q1.emplace(new Node(target, nullptr, heuristic_(target, start)));
    bool farward = true;
    while (!q0.empty()) {
      auto size = q0.size();
      while (size--) {
        auto cur = q0.top();
        q0.pop();
        if (c0.count(cur->s)) continue;
        c0[cur->s] = cur;
        if (c1.count(cur->s)) {
          auto p = c1[cur->s];
          if (GetRoot(cur)->s == target) swap(cur, p);
          cur = WirePath(cur, p->p);
          ConstructPath(cur, path);
          *opened = o0.size() + o1.size();
          *closed = c0.size() + c1.size();
          return true;
        }
        for (const auto& s : cur->GetNextStates()) {
          auto it = o0.find(s);
          auto n = make_shared<Node>(s, cur,
                                     heuristic_(s, farward ? target : start));
          if (it != o0.end() && n->f >= it->second->f) continue;
          o0[s] = n;
          q0.push(n);
        }
      }
      if (q1.size() < q0.size()) {
        swap(q0, q1);
        swap(c0, c1);
        swap(o0, o1);
        farward = !farward;
      }
    }
    return false;
  }

 private:
  Heuristic heuristic_;
};

bool VerifyPath(const vector<State>& path, const State& s, const State& t) {
  if (path.empty()) return false;
  if (path.front() != s || path.back() != t) return false;
  for (size_t i = 1; i < path.size(); ++i) {
    Node n(path[i - 1]);
    auto states = n.GetNextStates();
    if (find(begin(states), end(states), path[i]) == end(states)) {
      return false;
    }
  }
  return true;
}

void StatisticsMode() {
  State s{"123456780"};
  State t{"123456780"};

  vector<unique_ptr<Solver>> solvers;
  solvers.emplace_back(new BFSSolver);
  solvers.emplace_back(new AStarSolver(HammingDistance));
  solvers.emplace_back(new AStarSolver(ManhattanDistance));
  solvers.emplace_back(new BidirectionalBFSSolver);
  solvers.emplace_back(new BiAStarSolver(ManhattanDistance));

  for (int i = 0; i < 1000;) {
    random_shuffle(s.begin(), s.end());
    if (!Sovlable(s)) continue;
    ++i;
    for (auto& solver : solvers) {
      vector<State> path;
      int opened;
      int closed;
      auto t0 = high_resolution_clock::now();
      bool sovlable = solver->Solve(s, t, &path, &opened, &closed);
      auto t1 = high_resolution_clock::now();

      if (!VerifyPath(path, s, t)) {
        cerr << "Invalid path!" << endl;
        return;
      }

      auto time_span = chrono::duration_cast<chrono::duration<double>>(t1 - t0);

      cout << closed << "\t" << time_span.count() * 1000 << "\t";
    }
    cout << endl;
  }
}

int main() { StatisticsMode(); }
