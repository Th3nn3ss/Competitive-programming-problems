#include <cstring>
#include <fstream>
#include <stack>
using namespace std;  const int MAX_N = 202;  int N, M, sol; int H[MAX_N][MAX_N], D[MAX_N][MAX_N], dp[MAX_N][MAX_N]; char s[MAX_N]; bool A[MAX_N][MAX_N]; void read() {     ifstream f("bmatrix.in");      f >> N >> M;     for(int i = 1; i <= N; ++i) {         f >> s;         for(int j = 0; j < M; ++j)             if(s[j] == '0')                 A[i][j + 1] = 1;     }      f.close(); }  void solveLine(int line, int v[], int n) {     stack < pair < int, int > > st;      for(int i = 1; i <= n; ++i) {         if(st.empty() || v[i] > st.top().first)             st.push(make_pair(v[i], 1));         else if(st.top().first == v[i])             ++st.top().second;         else {             int cnt = 0;             while(!st.empty() && v[i] < st.top().first) {                 cnt += st.top().second;                 int top = st.top().first;                 st.pop();                 H[line][top] = max(H[line][top], cnt);             }             st.push(make_pair(v[i], cnt + 1));         }     }      int cnt = 0;     while(!st.empty()) {         cnt += st.top().second;         int top = st.top().first;         st.pop();         H[line][top] = max(H[line][top], cnt);     } }  void compute() {     memset(H, 0, sizeof(H));     memset(D, 0, sizeof(D));     for(int i = 1; i <= N; ++i) {         for(int j = 1; j <= M; ++j)             if(A[i][j])                 D[i][j] = D[i - 1][j] + 1;         solveLine(i, D[i], M);     }      for(int i = 1; i <= N; ++i) {         for(int j = i; j >= 1; --j)             H[i][j] = max(H[i][j], H[i][j + 1]);         dp[i][i] = H[i][1];     }     for(int h = 1; h < N; ++h)         for(int i = 1; i + h <= N; ++i) {             int j = i + h;             dp[i][j] = max(H[j][j - i + 1] * (j - i + 1), max(dp[i + 1][j], dp[i][j - 1]));         }      for(int i = 1; i < N; ++i)         sol = max(sol, dp[1][i] + dp[i + 1][N]); }  void transpose() {     int T[MAX_N][MAX_N];     memset(T, 0, sizeof(T));     for(int i = 1; i <= N; ++i)         for(int j = 1; j <= M; ++j)             T[j][i] = A[i][j];     swap(N, M);     memset(A, 0, sizeof(A));     for(int i = 1; i <= N; ++i)         for(int j = 1; j <= M; ++j)             A[i][j] = T[i][j]; }  void solve() {     compute();     transpose();     compute(); }  void write() {     ofstream g("bmatrix.out");      g << sol << "\n";      g.close(); }  int main() {     read();     solve();     write();      return 0; }
