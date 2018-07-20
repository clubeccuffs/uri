#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;


struct G {
    int N;
    typedef pair<int, int> ii;
    vector<vector<ii>> adj;
    G(int n): N(n), adj(n) {}

    void add_edge(int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    int dijkstra(int o, int d) {
        priority_queue<ii, vector<ii>, greater<ii> > q;
        vector<int> dst(N, numeric_limits<int>::max());
        dst[o] = 0;
        q.push({0, o});

        while(!q.empty()) {
            auto [c, u] = q.top(); q.pop();
            //printf("\nworking c=%d u=%d\n", c, u);

            for(auto [v, w] : adj[u]) {
                //printf("edge %d -> %d : %d\n", u, v, w);
                int nc = c+w;
                if(nc < dst[v]) {
                    //printf("relaxing %d + %d = %d   %d\n", c, w, nc, dst[v]);
                    dst[v] = nc;
                    q.push({nc, v});
                    //printf("qsize: %d\n", q.size());
                }
            }

        }

        //for(int x : dst) { cout << x << ' '; }
        //cout << '\n';

        return dst[d];
    }
};

int main() {

    int C, V;
    cin >> C >> V;

    G g(2*C);
    for(int i = 0; i < V; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        g.add_edge(u-1, C+v-1, w);
        g.add_edge(C+u-1, v-1, w);
    }


    /*
    for(int u = 0; u < 2*C; ++u) {
        for(auto [v, w] : g.adj[u]) {
            printf("%d -> %d : %d\n", u, v, w);
        }
    }
    */


    int r = g.dijkstra(0, C-1);
    if(r == numeric_limits<int>::max()) r = -1;

    cout << r << '\n';

}
