template<typename T = int>
struct Edge{
    int to;
    T flow, capacity, cost;
    int idx;
    bool rev;
    Edge* res;
    Edge(int to, T capacity, T cost, int idx, bool rev = false): to(to), flow(0), capacity(capacity), cost(cost), idx(idx), rev(rev) {}
    void addFlow(T flow){
        this->flow += flow;
        this->res->flow -= flow;
    }
};

//MUCHO OJO CON ESTO
const lli INF_FLOW = 1e15, INF_COST = 1e9;

template<typename T = int>
struct MinCostFlow{
    vector< vector< Edge<T>* > > adjList;
    int N;

    MinCostFlow(int N): N(N){
        adjList.resize(N);
    }

    void addEdge(int u, int v, T capacity, T cost, int idx){
        Edge<T>* uv = new Edge<T>(v, capacity, cost, idx);
        Edge<T>* vu = new Edge<T>(u, 0, -cost, idx, true);
        uv->res = vu;
        vu->res = uv;
        adjList[u].push_back(uv);
        adjList[v].push_back(vu);
    }

    pair<T, T> getMinCostFlow(int s, int t) {
        vector<T> dist(N), cap(N);
        vector<bool> inQueue(N);
        vector< Edge<T>* > parent(N);  

        T minCost = 0, maxFlow = 0;

        while(true) {

            fill(all(dist), INF_COST);
            fill(all(cap), 0);
            fill(all(parent), nullptr);

            queue<int> q;
            q.push(s);
            dist[s] = 0;
            cap[s] = INF_FLOW;

            while(!q.empty()) {
                int u = q.front(); q.pop();
                inQueue[u] = 0;

                for(auto E: adjList[u]) {
                    int v = E->to;
                    if(E->flow < E->capacity && dist[u] + E->cost < dist[v]) {

                        dist[v] = dist[u] + E->cost;
                        cap[v] = min(cap[u], E->capacity - E->flow);
                        parent[v] = E;

                        

                        if(!inQueue[v]) {
                            inQueue[v] = 1;
                            q.push(v);
                        }
                    }
                }
            }

            if(!parent[t]) break;
            // if(dist[t] > 0) break;

            maxFlow += cap[t];
            minCost += cap[t] * dist[t];
            
            for(int u = t; u != s; u = parent[u]->res->to){
                parent[u]->addFlow(cap[t]);
            }
        }


        return {minCost, maxFlow};
    }
};
