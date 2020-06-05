struct Edge
{
    lli to, flow, capacity;
    Edge* res;
    Edge(lli to, lli flow, lli capacity): to(to), flow(flow), capacity(capacity) {}

    void addFlow(lli flow)
    {
        this->flow += flow;
        this->res->flow -= flow;
    }
};

vector< vector<Edge*> > adjList;
vector< vector<bool> > rest;
vector<lli> pos;
vector<lli> dist;


void addEdge(lli u, lli v, lli capacity)
{
    Edge* uv = new Edge(v,0,capacity);
    Edge* vu = new Edge(u,0,0);
    uv->res = vu;
    vu->res = uv;
    adjList[u].push_back(uv);
    adjList[v].push_back(vu);
}

const lli INF = 1e18;

lli blockingFlow(lli u, lli t, lli flow)
{
    if(u==t) return flow;
    for(lli &i = pos[u]; i<adjList[u].size(); i++)
    {
        Edge* v = adjList[u][i];
        if(v->capacity > v->flow && dist[u] + 1 == dist[v->to])
        {
            lli f = blockingFlow(v->to, t, min(flow, v->capacity  - v->flow));
            if(f>0)
            {
                v->addFlow(f);
                return f;
            }
        }
    }
    return 0;
}


lli dinic(lli s, lli t)
{
    lli maxFlow = 0;
    dist[t] = 0;
    while(dist[t] != -1)
    {
        fill(all(dist), -1);
        queue<lli> q; q.push(s);
        dist[s] = 0;
        while(!q.empty())
        {
            lli u = q.front(); q.pop();
            for(Edge *v: adjList[u])
            {
                if(dist[v->to]==-1 && v->capacity > v->flow)
                {
                    dist[v->to] = dist[u] + 1;
                    q.push(v->to);
                }
            }
        }
        if(dist[t]!=-1)
        {
            lli f= 0;
            fill(all(pos), 0);
            while(f = blockingFlow(s,t,INF))
            {
                maxFlow += f;
            }
        }
    }
    return maxFlow;
}