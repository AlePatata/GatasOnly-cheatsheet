#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>

using namespace std;

const int INF = 1e9;

/* BFS Busqueda a lo ancho
    necesita: 
        grafo vector<int> graph
        nodo inicial a partir del cual recorrer el grafo
*/
int BFS(int begin) { 
    vector<int> dist(n, INF); // Distancias iniciadas en INF
    vector<int> parent(n,-1); // Padres de cada nodo

    int start = begin; // Nodo inicial
    dist[start] = 0;

    queue<int> q; // Nodos a visitar
    q.push(start);
    
    while(!q.empty()) { // Mientras hayan nodos a visitar
        int u = q.front(); // Nodo Actual
        q.pop();

        for(int v : graph[u]){ // Para cada hijo del Nodo Actual
            /* Otras operaciones:
            - Busqueda de un nodo en particular 
            - Conteo de nodos en componente conexa
            */

            if (dist[v] > dist[u] + 1){ // Actualizacion de dist y parent
                dist[v] = dist[u] + 1;
                parent[v] = u; 
                q.push(v); // Siguiente nivel de profundidad
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n, m; // Nodos, Aristas
    cin >> n >> m;
    
// Construcción estandar grafo no dirigido sin peso
    vector<vector<int>> graph(n);
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

// Construcción grafo no dirigido con peso
    vector<vector<pli>> graph(n); // graph[nodo_i] = {peso,nodo_j}
    for(int i = 0; i < m; i++){
        int u, v; 
        ll w;
        cin >> u >> v >> w;
        u--; v--;
        graph[u].push_back({w,v});
        graph[v].push_back({w,u});
    }
    // Visualizacion graph
    for(int i = 0; i < n; i++) {
        for(auto [w, v] : graph[i])
            cout << i << ' ' << v << " peso: " << w << ' ';
        cout << endl;
    }

    return 0;
}