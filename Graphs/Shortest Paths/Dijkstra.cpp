lli dijkstra(lli from, lli to)
{
    vector<lli> dist( adj.size() , INF );

    priority_queue< pair<lli,lli>, vector<pair<lli,lli>>, greater<pair<lli,lli>> > q;
    q.push({0,from}); // {costo, nodo}
    dist[from] = 0;
    while(!q.empty())
    {
        lli u = q.top().second; q.pop();
        for(auto v: adj[u])
        {
            if(dist[u] + v.second < dist[v.first])
            {
                dist[v.first] = dist[u] + v.second;
                q.push({ dist[v.first], v.first});
            }
        }
    }
    return dist[to];
}

