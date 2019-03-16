#include <iostream>
#include <vector>
#include <set>

using namespace std;

int seed = 0;
const int INF = 1e8;

using ii = pair<int,int>;

struct G {
  vector<vector<ii>> adj;
  set<ii> queue;
  vector<int> dist;

  G(int size): adj(size), dist(size, INF) {}

  void add_edge(int u, int v, int w) {
    adj[u].push_back(ii{v, w});
  }

  void dijkstra(int s) {
    dist[s] = 0;
    // queue.insert({0, s});
    for(int i = 0; i < adj.size(); ++i) {
      queue.insert({dist[i], i});
    }

    while(!queue.empty()) {
      auto link = queue.begin();
      queue.erase(link);
      int u = link->second;
      // int w = link->first;

      for(auto [v, w] : adj[u]) {
        if(dist[u] + w < dist[v]) {
          queue.erase({dist[v], v});
          dist[v] = dist[u]+w;

        }
      }
    }
  }

  friend ostream & operator<<(ostream & out, G & graph) {
    out << "digraph G {\n";
    for(int u = 0; u < graph.adj.size(); ++u) {
      for(auto [v, w] : graph.adj[u]) {
        out << u << " -> " << v << " [label="<<w<<"];\n";
      }
    }
    out << "}\n";
    return out;
  }
};

int cl(int x) {
  return 2*x+1;
}
int cr(int x) {
  return 2*x+2;
}

struct ST {
  vector<int> code;
  G & g;
  bool dir;
  ST(int size, G & g_, bool d):code(4*size), g(g_), dir(d) {
    for(int i = 0; i < 4*size; ++i) {
      code[i] = ++seed;
    }
  }
  void add_edge_seg(int v, int w, int l, int r, int l_, int r_, int x=0) {
    if(l > r_) return;
    if(r < l_) return;
    // if (!(l_ <= l && l <= r_) || !(l_ <= r && r <= r_)) {
    //   return;
    // }
    if(l <= l_ && r_ <= r) {
      if(dir) {
        g.add_edge(v, code[x], w);
      }
      else {
        g.add_edge(code[x], v, w);
      }
      return;
    }
    int center = (l_+r_) / 2;
    add_edge_seg(v, w, l, r, l_, center, cl(x));
    add_edge_seg(v, w, l, r, center+1, r_, cr(x));
  }

  void build(int l_, int r_, int x = 0) {
    if(l_ == r_) {
      if(dir) {
        g.add_edge(code[x], l_, 0);
      }
      else {
        g.add_edge(l_, code[x], 0);
      }
      return;
    }
    int center = (l_+r_) / 2;

    if(dir) {
      g.add_edge(code[x], code[cl(x)], 0);
      g.add_edge(code[x], code[cr(x)], 0);
    }
    else {
      g.add_edge(code[cl(x)], code[x], 0);
      g.add_edge(code[cr(x)], code[x], 0);
    }

    build(l_, center, cl(x));
    build(center+1, r_, cr(x));
  }

};



int main(int argc, char const *argv[]) {

  int N, Q, S;
  cin >> N >> Q >> S;
  G g(10*N);
  seed = N;
  ST type2(N, g, true), type3(N, g, false);

  for(int i = 0; i < Q; ++i) {
    int t, u, v, l, r, w;
    cin >> t;
    if(t == 1) {
      cin >> u >> v >> w;
      u--;
      v--;
      g.add_edge(u, v, w);
    }
    else {
      cin >> v >> l >> r >> w;
      v--;
      l--;
      r--;
      if(t==2) {
        type2.add_edge_seg(v, w, l, r, 0, N-1);
      }
      else {
        type3.add_edge_seg(v, w, l, r, 0, N-1);
      }
    }

  }

  type2.build(0, N-1);
  type3.build(0, N-1);

  g.dijkstra(S-1);

  cout << "// ";
  for(int i = 0; i < N; ++i) {
    cout << g.dist[i] << (i+1==N ? '\n' : ' ');
  }

  cout << g << '\n';

  return 0;
}
