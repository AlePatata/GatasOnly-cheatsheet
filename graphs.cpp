#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll,int> pli;

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

/* Dijkstra
Dado un grafo con pesos y un nodo inicial, encuentra el camino más corto 
a cada otro nodo
*/
vector<ll> Dijkstra(pli start) {
    priority_queue<pli, vector<pli>, greater<pli> > pq;
    vector<ll> dist(n, INF);
    dist[start.second] = 0;
    pq.push(start);
    while(!pq.empty()) {
        auto [l, u] = pq.top();    
        pq.pop();
        if (dist[u] < l) 
            continue;

        for(auto [w, v] : graph[u]) {
            if(dist[v] > dist[u] + w){
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
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

    // Camino más corto de un nodo a otro pasando por una cierta ruta
    // Dado un vector de ciertos nodos interesantes y su vector de demas nodos mas
    // cercanos asociados distancias[u]
    sort(ruta.begin()+1,ruta.end());
    do {
        ll lmin = 0;
        for (int i = 0; i<ruta.size()-1; i++) {
            int u = ruta[i];
            lmin += distancias[u][ruta[i+1]];
        }
        if (lmin < min) {
            min = lmin;
           
        }
    } while ( next_permutation(ruta.begin()+1,ruta.end()) );


// FUDGE ALGORITHM
//Se inicializa el vector de distancias con la diagonal en 0 y dist[i][j] = peso del camino i-j
    for(int i = 0; i<n; i++)
        dist[i][i] = 0;
    for(int i = 0; i < m; i++){
        int u, v; 
        ll w;
        cin >> u >> v >> w;
        u--; v--;
        dist[u][v] = min(w, dist[u][v]);
        dist[v][u] = min(w, dist[v][u]);
    }
    // Para un trio de nodos i,j,k el camino mas corto de i a j es
    // el minimo entre el camino directo de i a j o darnos una vuelta
    // mas larga pasando por k (camino de i a k + camino de k a j)
    for(int k = 0; k < n; k++)
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++) 
                dist[i][j] = min(dist[i][j],dist[i][k]+dist[k][j]);


// Coloreado de un grafo - Bipartición
    vector<int> team(n,-1), conex(n,0);

    bool bip = true;
    for (int i = 0; i < n; ++i) {
        int start = i;
        if (!conex[start]) {
            team[start] = 1;
            q.push(start);
            conex[start] = 1;
            while(!q.empty() and bip) {
                int u = q.front();
                q.pop();
                for(int v : graph[u]){
                    if (team[v] == -1) team[v] = 1^team[u];
                    else if (team[v] == team[u]) bip = false; 
                    if (!conex[v]){
                        conex[v] = 1;
                        q.push(v);
                    }
                }
            }
        }
    }
    return 0;
}