/*
    When all capacities are the unity: O(n*sqrt(n))
    General without scaling: O(V^2*E)
    General with scaling:  O(E*V*log(U)) where U is maximum flow
*/

template<typename T = int>
struct Edge{
    int to;
    T flow, capacity;
    bool rev;
    Edge* res;
    Edge(int to, T capacity, bool rev = false): to(to), flow(0), capacity(capacity), rev(rev) {}
    void addFlow(T flow){
        this->flow += flow;
        this->res->flow -= flow;
    }
};

//MUCHO OJO CON ESTO
const int INF = 1e9;

template<typename T = int>
struct Dinic{
    vector< vector< Edge<T>* > > adjList;
    vector< int > pos, dist;
    int N;
    T limit = 1;
    T maxFlow = 0;
    const bool scaling = false;


    Dinic(int N): N(N){
        adjList.resize(N);
        pos.resize(N);
        dist.resize(N);
    }

    void addEdge(int u, int v, T capacity, bool directed = true){
        Edge<T>* uv = new Edge<T>(v, capacity, false);
        Edge<T>* vu = new Edge<T>(u, directed?0:capacity, true);
        uv->res = vu;
        vu->res = uv;
        adjList[u].push_back(uv);
        adjList[v].push_back(vu);
    }

    T BlockingFlow(int u, int t, T flow){
        if(u == t) return flow;
        for(int &i= pos[u]; i<(int)adjList[u].size(); i++ ){
            Edge<T>* E = adjList[u][i];
            if(E->capacity > E->flow && dist[E->to] == dist[u] + 1){
                lli f = BlockingFlow(E->to, t, min(flow, E->capacity - E->flow));
                if(f>0){
                    E->addFlow(f);
                    return f;
                }
            }
        }
        return 0;
    }
    bool bfs(int s, int t){
        fill(all(dist), -1);
        queue<int> q; q.push(s);
        dist[s] = 0;
        while(!q.empty()){
            lli u = q.front(); q.pop();
            for(auto E: adjList[u]){
                if(dist[E->to] == -1 && E->capacity > E->flow && (!scaling || E->capacity - E->flow >= limit)){
                    dist[E->to] = dist[u] + 1;
                    q.push(E->to);
                }
            }
        }
        return dist[t] != -1;
    }

    void resetFlow() {
        for(int i = 0; i < SZ(adjList); i++){
            for(auto &v: adjList[i]){
                v->flow = 0;
            }
        }
    }
    
    T StartDinic(int s, int t){
        maxFlow = 0;
        for(limit = (scaling?1<<30:1); limit>0; limit>>=1){ // (1<<30) is for maximum capacity = 10^9
            dist[t] = 0;
            while(bfs(s, t)){
                lli f = 0;
                fill(all(pos), 0);
                while((f = BlockingFlow(s, t, INF))){
                    maxFlow += f;
                }
            }
        }
        return maxFlow;
    }

    //To found if an edge is part of min-cut
    //Run dfs(S) and if U is part of T and is
    //visited, then is part of min-cut
    vector<bool> visited;
    void dfs(int u, bool clearing = true) {
        if(clearing) visited.resize(N);
        if(visited[u]) return;
        visited[u] = true;
        for(auto E: adjList[u]){
            if(E->capacity == E->flow) continue;
            dfs(E->to, false);
        }
    }
};

template<typename T = int>
struct LowerBoundDinic: Dinic<T>{
    vector< T > dem;
    int n;
    int s_prime = n, t_prime = n+1;
    // keep track lowers if you need reconstruct the path,
    // you will need to add lower[v->idx] + v->flow
    // vector< int > lowers; 
    // int timee = 0;
    T total_dem = 0;

    LowerBoundDinic(int n): Dinic<T>(n+2), dem(n), n(n), s_prime(n), t_prime(n+1) {}

    void addEdge(int u, int v, T l, T r) {
        dem[u] += l;
        dem[v] -= l;
        // lowers.push_back(l);
        Dinic<T>::addEdge(u, v, r - l);
    }

    bool has_circulation() {
        
        for(int i = 0; i < n; i++){
            if(dem[i] < 0) {
                total_dem += -dem[i];
                Dinic<T>::addEdge(s_prime, i, -dem[i]);
            } else if(dem[i] > 0){
                Dinic<T>::addEdge(i, t_prime, dem[i]);
            }
            dem[i] = 0;
        }

        return Dinic<T>::StartDinic(s_prime, t_prime) == total_dem;
    }

    // Calculate the minimum flow feasible with lower bounds
    T getMinFlow(int s, int t) {
        addEdge(t, s, 0, INF);
        if(!has_circulation()) return -1; // Is not feasible

        auto change_flow_t = [&](T k) {
            for(auto &v: Dinic<T>::adjList[t]) {
                if(v->to == s) {
                    v->capacity = k;
                    v->res->capacity = k;
                }
            }
        };

        int l = 0, r = INF, ans = INF;
        while(l <= r) {
            int mid = l + (r-l)/2;

            Dinic<T>::resetFlow();
            change_flow_t(mid);

            if(has_circulation()) {
                r = mid-1;
                ans = mid;
            } else {
                l = mid+1;
            }
        }

        Dinic<T>::resetFlow();
        change_flow_t(ans);
        has_circulation();

        return ans;
    }

    // Calculate the maximum flow feasible
    T getMaxFlow(int s, int t) {
        addEdge(t, s, 0, INF);
        if(!has_circulation()) return -1;

        Dinic<T>::maxFlow = 0;
        return Dinic<T>::StartDinic(s, t);
    }
};
