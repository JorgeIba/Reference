const char AND = '&';
const char OR = '|';
const char NOT = '~';
 
string tokenize(const string& s){
	string ans;
	for(int i = 0; i < SZ(s); i++){
		string aux;
		while(i < SZ(s) && s[i] != ' '){
			aux += s[i];
			i++;
		}
		if(aux == "and") ans += AND;
		else if(aux == "or") ans += OR;
		else if(aux == "not") ans += NOT;
		else{
			forn(i, SZ(aux)){
				char c = aux[i];
				if(c != 'n'){
					ans += c;
				}
				else{
					ans += NOT;
					i += 2;
				}
			}
		}
	}
	return ans;
}
 
bool is_terminal(char c){
	return (
			c != '(' &&
			c != ')' &&
			c != AND &&
			c != OR &&
			c != NOT
			);
}
 
const int MAXN = 3000;
 
int id;
char token[MAXN];
vi adj[MAXN];
 
int build(int u, int l, int r, const string& s, vvi& prv_op){
	int m = -1;
	/* if(l < 0 || l >= SZ(s)) exit(0); */
	/* if(r < 0 || r >= SZ(s)) exit(0); */
	forn(k, 3)
		if(prv_op[r][k] >= l)
			m = prv_op[r][k];
	if(m == -1){
		if(l == r){
			token[u] = s[l];
			return u;
		}
		if(is_terminal(s[r]))
			return build(u, r, r, s, prv_op);
		return build(u, l, r - 1, s, prv_op);
	}
	token[u] = s[m];
	if(s[m] == NOT){
		int m2 = m;
		while((m2 - 1) >= l){
			if(prv_op[m2 - 1][0] >= l)
				m2 = prv_op[m2 - 1][0];
			else
				break;
		}
		adj[u].pb(build(id++, m2 + 1, r, s, prv_op));
	}
	else{
		adj[u].pb(build(id++, l, m - 1, s, prv_op));
		adj[u].pb(build(id++, m + 1, r, s, prv_op));
	}
	return u;
}
 
int parse(const string& s){
	vvi prv_op(SZ(s));
	stack<vi> lst;
	lst.push({-1, -1, -1});
	forn(i, SZ(s)){
		if(s[i] == OR) lst.top()[2] = i;
		if(s[i] == AND) lst.top()[1] = i;
		if(s[i] == NOT) lst.top()[0] = i;
		if(s[i] == '(') lst.push({-1, -1, -1});
		if(s[i] == ')') lst.pop();
		prv_op[i] = lst.top();
	}
	return build(id++, 0, SZ(s) - 1, s, prv_op);
}
