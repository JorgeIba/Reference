/*
    Example of usage:
    VirtualTreeMaker VTM;
    VTM.build(adjList, root);
    vector<int> relevant_nodes = {1, 2, 3, 4};

    int root_VT = VTM.virtual_tree(relevant_nodes);

    adjListVT will have the edges of the virtual tree rooted with root_VT;

    If relevant_nodes has k nodes, virtual Tree will have at most 2*k-1 total nodes.
*/


const int MAXN = 1e5 + 100;
const int LOG  = 20;
vector<int> adjListVT[MAXN];
int ancestor[MAXN][LOG];
int depth[MAXN];
array<int,2> rang[MAXN];
int Time = 0;

struct VirtualTreeMaker{

    VirtualTreeMaker() {}

    template<class G>
    void build(const G &adjList, int root = 0){
        dfs_prec(root, root, adjList);
    } 

    template<class G>
    void dfs_prec(int u, int p, const G &adjList){
        // Precalculate ancestors
        ancestor[u][0] = p;
        for(int i = 1; i < LOG; i++){
            ancestor[u][i] = ancestor[ancestor[u][i-1]][i-1];
        }

        // DFS order
        rang[u][0] = Time++;
        for(auto v: adjList[u]){
            if(v == p) continue;
            depth[v] = depth[u] + 1;
            dfs_prec(v, u, adjList);
        }

        rang[u][1] = Time - 1;
    }

    bool is_above(int u, int v){
        return rang[u][0] <= rang[v][0] && rang[v][1] <= rang[u][1];
    }

    int get_lca(int u, int v){
        if(is_above(u, v)) return u;
        if(is_above(v, u)) return v;

        for(int i = LOG-1; i >= 0; i--){
            if(!is_above(ancestor[u][i], v)) {
                u = ancestor[u][i];
            }
        }
        return ancestor[u][0];
    }

    int virtual_tree(vector<int> nodes){
        sort(all(nodes), [&](auto u, auto v){
            return rang[u][0] < rang[v][0];
        });

        int n = SZ(nodes);
        for(int i = 0; i < n-1; i++){
            int u = nodes[i], v = nodes[i+1];
            int lca = get_lca(u, v);
            nodes.push_back(lca);
        }

        sort(all(nodes), [&](auto u, auto v){
            return rang[u][0] < rang[v][0];
        });

        nodes.erase(unique(all(nodes)), nodes.end());
        for(auto u: nodes) adjListVT[u].clear();

        stack<int> s;
        s.push(nodes.front());

        for(int i = 1; i < SZ(nodes); i++){
            auto u = nodes[i];
            while(!is_above(s.top(), u)) s.pop();

            adjListVT[s.top()].push_back(u);
            s.push(u);
        }  

        return nodes.front();
    }
};