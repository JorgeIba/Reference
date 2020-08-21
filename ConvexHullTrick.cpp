bool Q = 0;
struct Line {
	mutable lli m, b, x;
 
	bool operator < (const Line L) const {
		return Q ? x < L.x : m < L.m; 
	}
};
const lli INF = numeric_limits<lli>::max();
struct Hull : multiset<Line> {

    lli ceil (lli a, lli b) {
	if (a < 0 != b < 0) return a / b; // Si uno es negativos y otro no
	return (abs(a) + abs(b) - 1) / abs(b); 
    }
    
    lli intersection (const Line &p, const Line &q) {
        return ceil(q.b - p.b, p.m - q.m);
    }


	bool valid (auto it) {
		if (it == begin()) { // Si el iterador quedo hasta el inicio, entonces su interseccion en X con el anterior es en -INF
			auto sig = it;
			sig++;
			if (sig != end()) sig->x = intersection(*it, *sig); // Si existe una recta con pendiente mayor a it, entonces sig-> x gaurda el
			return it->x = -INF;                                // punto donde se intersectan
		}
 
		auto ant = it, sig = it;
		ant--, sig++;
 
		if (sig == end()) { // Si el iterador quedo hasta el final
			it->x = intersection(*it, *ant);
			return 1;
		}
        // Esta parte es por si quedó entre otras dos rectas, hay que checar el punto de interseccion con el de atras,
        // Si esta mas a la derecha que el punto de interseccion de adelante, significa que no forma parte del convex hull
        // Pero si está mas a la izq, significa que el intervalo es [ant, x] U [x, y] U [y, sig] (Esto para buscar maximos)
		lli x = intersection(*it, *ant); 
		lli y = intersection(*it, *sig);
 
		if (x > y) return 0;
		it->x = x, sig->x = y;
		return 1;
	}
 
	void add (lli m, lli b) {
		auto it = lower_bound({m, b, -INF}); // Pa ver en donde lo voy a poner
                                             // Recuerda que estan ordenados por pendientes
		
        if (it != end() && it->m == m) { //por si enconte una recta con igual pendiente
			if (it->b > b) return; //Si la recta que encontre en el lower bound esta mas hacia arriba, entonces la nueva que 
                                   //quiero insertar no forma parte del Convex Hull
			it->b = b; //Ya no creo otra recta, sino que mofidico la que me encontré
		} else {
			it = insert({m, b, -INF}); //Si no encontré ninguna parecida, creo una nueva recta
		}
 
		if (!valid(it)) { // Checar si el it forma parte del convex hull, además de encontrar los puntos de interseccion
			erase(it);
			return;
		}
 
		auto ant = it;
		while (ant != begin()) { // Para borrar todos las lineas anteriores a it, que no forman parte del convex hull
			if (valid(--ant)) break; // Si una linea forma part del convex hull, todas las anteriores tambien
			erase(ant);
			if (it == begin()) { it->x = -INF; break; }
			ant = it;
		}
 
		auto sig = it;
		sig++;
		while (sig != end() && !valid(sig)) // Para borrar todas las lineas despues de it, que no forman parte dle convex hull
			erase(sig++);
	}
 
	lli query (lli x) {
		if (empty()) return 0; //Si no hay ninguna linea antes
 
		Q = 1; // el comparador de la estructura, ahora compara con las intersecciones
		auto it = upper_bound({0, 0, x});
		it--; // Para obtener la linea con interseccion punto de interseccion mas grande pero que sea menor a x
              // Es decir, obtener el punto de interseccion de la recta que contiene a X, en el convex hull
		Q = 0; // el comparador de la estructura vuelve a comparar respecto a las pendientes y no respecto a los puntos de interseccion
		return x * it->m + it->b; //regresa la evaluacion de la recta en x.
	}
};

struct Line {
	mutable ll k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	const ll inf = LLONG_MAX;
	ll div(ll a, ll b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) { x->p = inf; return false; }
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(ll k, ll m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	ll query(ll x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
};