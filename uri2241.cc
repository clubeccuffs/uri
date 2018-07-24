#include <iostream>
#include <cstring>
using namespace std;

int pedras[2][500][500];
int cache[2][500][500][500];

int solve(int i, int j, int si, int sj, int cor) {
    if(si == sj && cache[cor][i][j][si] != -1) {
        return cache[cor][i][j][si];
    } 

    //printf("solve? %d %d %d %d %d \n", i, j, si, sj, cor);
    if(si==0 || sj == 0) return 0;
    if(si==1 && sj == 1) {
        return pedras[cor][i][j];
    }
    int t = 0;

    if(sj > si) {
        t += solve(i, j     , si, sj/2   , cor);
        if(t == 0)
            t += solve(i, j+sj/2, si, sj-sj/2, cor);
    }
    else {
        t += solve(i,     j, si/2    , sj, cor);
        if(t == 0)
            t += solve(i+si/2, j, si-si/2 , sj, cor);
    }

    if(si == sj) cache[cor][i][j][si] = t;
    return t;
}

int main() {
    int N, P;
    cin >> N >> P;

    memset(pedras, 0, sizeof(pedras));
    memset(cache, -1, sizeof(cache));

    for(int j = 0; j < 2; ++j) {
        for(int i = 0; i < P; ++i) {
            int x, y;
            cin >> x >> y;
            pedras[j][x-1][y-1]++;
        }
    }


    /*
    */
    int b[2] = { 0, 0 };

    for(int cor = 0; cor < 2; ++cor)
        for(int s = 1; s <= N; ++s) {
            printf("s => %d\n", s);
            for(int i = 0; i+s-1 < N; ++i) {
                for(int j = 0; j+s-1 < N; ++j) {
                    if(solve(i, j, s, s, cor) > 0 && solve(i, j, s, s, 1-cor) == 0) {
                        b[cor]++;
                    }
                }
            }
        }

    cout << b[0] << ' ' << b[1] << '\n';


    /*
    printf("|> %d \n", solve(0, 0, 2, 2, 0));

    printf("> %d \n", solve(0, 0, 1, 1, 0));
    printf("> %d \n", solve(0, 1, 1, 1, 0));
    printf("> %d \n", solve(1, 0, 1, 1, 0));
    printf("> %d \n", solve(1, 1, 1, 1, 0));
    
    printf("|> %d \n", solve(0, 0, 2, 2, 1));
    printf("> %d \n", solve(0, 0, 1, 1, 1));
    printf("> %d \n", solve(0, 1, 1, 1, 1));
    printf("> %d \n", solve(1, 0, 1, 1, 1));
    printf("> %d \n", solve(1, 1, 1, 1, 1));
    */
}
