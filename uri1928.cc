#include <vector>
#include <iostream>
#include <map>
using namespace std;

vector<int> euler, euler_h;
map<pair<int,int>, int> cache;

int p(int a) {
    return a + (a&-a);
}

int mid_(int a, int b) {
    while(p(a) < b) {
        //printf("%d %d %d\n", a, p(a), b);
        a = p(a);
    }
    return a;
}

int search(int pa, int pb) {
    int a = min(pa, pb);
    int b = max(pa, pb);
    if(a==b) {
        return euler_h[a];
    }

    auto it = cache.find({a, b});
    if(it !=cache.end()) { return it->second; }

    //int mid = (a+b) / 2;
    int mid = mid_(a,b);

    return cache[{a,b}] = min(search(a, mid), search(mid+1, b));
    
}

void altura(vector<bool> & vis, vector<vector<int>> & adj, vector<int> & alt, int u, int a) {
    alt[u] = a;
    vis[u] = true;
    for(int v : adj[u]) {
        if(!vis[v]) {
            altura(vis, adj, alt, v, a+1);
        }
    }
}

void euler_tour(vector<bool> & vis, vector<vector<int>> & adj, vector<int> & alt, int u) {
    euler.push_back(u);
    euler_h.push_back(alt[u]);
    vis[u] = true;

    for(int v: adj[u]) {
        if(!vis[v]) {
            euler_tour(vis, adj, alt, v);
            euler.push_back(u);
            euler_h.push_back(alt[u]);
        }
    }
}

int main() {
    int N;
    cin >> N;

    vector<vector<int>> pos(N/2);
    vector<vector<int>> adj(N);
    vector<int> alt(N);

    for(int i = 0; i < N; ++i) {
        int x;
        cin >> x;
        x--;
        pos[x].push_back(i);
    }

    for(int i = 0; i < N - 1; ++i) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<bool> vis(N, false);
    altura(vis, adj, alt, 0, 0);

    vis.assign(N, false);
    euler_h.push_back(0);
    euler_tour(vis, adj, alt, 0);

    vis.assign(N, false);
    vector<int> index(N);
    for(int i = 0; i < euler.size(); ++i) {
        if(!vis[euler[i]]) {
            vis[euler[i]] = true;
            index[euler[i]] = i;
        }
    }


    /*
    for(int i = 0; i < euler.size(); ++i) {
        cout << euler[i] << ' ';
    }
    cout << '\n';

    for(int i = 0; i < euler.size(); ++i) {
        cout << euler_h[i] << ' ';
    }
    cout << '\n';
    */

    int tot = 0;

    for(int i = 0; i < N/2; ++i) {
        int u = pos[i][0];
        int v = pos[i][1];

        int a_h = search(index[u]+1, index[v]+1);
        int x = alt[u] + alt[v] - 2*a_h;
        tot += x;
        //printf("%d -> %d %d euler(%d %d) ancestor(%d)\n", 
        //       i, u, v, index[u], index[v], a_h);
        //printf("%d + %d - 2 * %d = %d\n", 
        //       alt[u], alt[v], a_h, alt[u] + alt[v] - 2*a_h);
    }
    cout << tot << '\n';
}
