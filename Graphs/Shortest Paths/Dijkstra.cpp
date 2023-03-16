
typedef pair<lli,lli> pairi;
vector< vector< pairi > > adjList;

const lli INF = 1e17;
vector<lli> dijkstra(int start){   
    int n = SZ(adjList);
    vector<lli> dist( n, INF );

    priority_queue< pairi, vector<pairi>, greater<pairi> > pq;

    pq.push({0,start}); // {costo, nodo}
    dist[start] = 0;

    while(!pq.empty()){
        auto [dist_u, u] = pq.top(); pq.pop();
        
        if(dist_u > dist[u]) continue;

        for(auto [v, w]: adjList[u]){
            if(dist[u] + w < dist[v]){
                dist[v] = dist[u] + w;
                pq.push({ dist[v], v });
            }
        }
    }
    return dist;
}

