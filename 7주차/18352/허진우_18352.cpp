/*
 * 이름: 허진우 
 * 언어: C++17
 * 문제: 백준/18352
*/

/*
 * 풀이
 * 방향 그래프 + 모든 간선의 가중치가 양수이므로 다익스트라가 적절하다고 판단함.
 * 거리가 모두 1이기 때문에 우선순위큐가 필요하지는 않아보여 단순한 큐로 해결을 보았다. (sol)
 * 하지만 다익스트라를 공부하기 위해, 다익스트라 알고리즘으로도 해결해보았다. (sol2)
*/

#include <bits/stdc++.h>
#define INF 1e9
using namespace std;
using pii = pair<int, int>;

int n, m, k, x;
vector<vector<pii>> graph;

void input() {
    int start, end;

    cin >> n >> m >> k >> x;
    graph.resize(n + 1);

    for (int i = 0; i < m; i++) {
        cin >> start >> end;
        graph[start].push_back({ 1, end });
    }
}

void sol() { // bfs
    int dist_arr[n + 1] = { 0, };
    bool visit[n + 1] = {false, };
    queue<pii> q;

    q.push({ x, 0 });
    visit[x] = true;

    while (!q.empty()) {
        int prev = q.front().first;
        int dist = q.front().second;
        q.pop();

        for (const auto& p : graph[prev]) {
            int next = p.second, next_dist = p.first;
            if (!visit[next]) {
                q.push({ next, next_dist + dist });
                visit[next] = true;
                dist_arr[next] = next_dist + dist;
            }
        }
    }

    bool cout_flag = true;
    for(int i = 1; i <= n; i++) {
        if (dist_arr[i] == k) {
            cout_flag = false;
            cout << i << endl;
        }
    }
    if (cout_flag) cout << -1;
}

void sol2() { // dijkstra
    int dist_arr[n + 1];
    fill(dist_arr, dist_arr + n + 1, INF);
    bool visit[n + 1] = {false, };
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    pq.push({0, x});
    dist_arr[x] = 0;

    while(!pq.empty()) {
        int prev = pq.top().second;
        pq.pop();
        if (visit[prev]) continue;
        
        visit[prev] = true;
        
        for(const auto& elem : graph[prev]) {
            int next = elem.second, dist = elem.first;
            if (dist_arr[next] > dist_arr[prev] + dist) {
                dist_arr[next] = dist_arr[prev] + dist;
                pq.push({dist_arr[next], next});
            }
        }
    }
    
    bool cout_flag = true;
    for(int i = 1; i <= n; i++) {
        if (dist_arr[i] == k) {
            cout_flag = false;
            cout << i << endl;
        }
    }
    if (cout_flag) cout << -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    input();
    // sol();
    // sol2();
}