#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// Lazy
template<
  class T1, // answer value stored on nodes
  class T2, // lazy update value stored on nodes
  T1 merge(T1, T1), 
  void push_upd(T2 /*padre*/, T2& /*hijo*/, int, int, int, int), // push update value from a node to another. parent -> child
  void apply_upd(T2, T1&, int, int)           // apply the update value of a node to its answer value. upd -> ans
>
struct segment_tree_lazy{
  int n;
  T2 e; // update neutral element
  vector<T1> ST;
  vector<T2> lazy;
  vector<bool> upd;
  void build(int i, int l, int r, vector<T1>&values){
    if (l == r){
      ST[i] = values[l];
      return;
    }
    build(i << 1, l, (l + r) >> 1, values);
    build(i << 1 | 1, (l + r) / 2 + 1, r, values);
    ST[i] = merge(ST[i << 1], ST[i << 1 | 1]);
  }
  segment_tree_lazy(vector<T1>&values, T2 e) : 
		 	n(values.size()), 
			e(e), 
			ST(n << 2 | 3),
			upd(n << 2 | 3, false),
			lazy(n << 2 | 3, e){
    build(1, 0, n - 1, values);
  }
  segment_tree_lazy(int n, T1 x, T2 e) : 
  		n(n),
  		e(e), 
  		ST(n << 2 | 3),
  		upd(n << 2 | 3, false), 
  		lazy(n << 2 | 3, e){
    vector<T1> v(n, x);
    build(1, 0, n - 1, v);
  }
  segment_tree_lazy(){}
  void push(int i, int l, int r){
    if (upd[i]){
      apply_upd(lazy[i], ST[i], l, r);
      if (l != r){
        push_upd(lazy[i], lazy[i << 1], l, r, l, (l + r) / 2);
        push_upd(lazy[i], lazy[i << 1 | 1], l, r, (l + r) / 2 + 1, r);
        upd[i << 1] = 1;
        upd[i << 1 | 1] = 1;
      }
      lazy[i] = e;
      upd[i] = false;
    }
  }
  void update(int i, int l, int r, int a, int b, T2 &u){
    if (l >= a and r <= b){
      push_upd(u, lazy[i], a, b, l, r);
      upd[i] = true;
    }
    push(i, l, r);
    if (l > b or r < a or (l >= a and r <= b)) return;
    update(i << 1, l, (l + r) >> 1, a, b, u);
    update(i << 1 | 1, (l + r) / 2 + 1, r, a, b, u);
    ST[i] = merge(ST[i << 1], ST[i << 1 | 1]);
  }
  T1 query(int i, int l, int r, int a, int b){
    push(i, l, r);
    if (a <= l and r <= b)
      return ST[i];
    int mid = (l + r) >> 1;
    if (mid < a)
      return query(i << 1 | 1, mid + 1, r, a, b);
    if (mid >= b) 
      return query(i << 1, l, mid, a, b);
    return merge(query(i << 1, l, mid, a, b), query(i << 1 | 1, mid + 1, r, a, b));
  }
  void get_leaves(int i, int l, int r, vector<T1> &res){
    push(i, l, r);
    if (l == r){
      res[l] = ST[i];
      return;
    }
    get_leaves(i << 1, l, (l + r) / 2, res);
    get_leaves(i << 1 | 1, (l + r) / 2 + 1, r, res);
  }

  // user methods
  // update range (a, b) by u
  void update(int a, int b, T2 u){
    update(1, 0, n - 1, a, b, u);
  }
  // query range (a, b)
  T1 query(int a, int b){
    return query(1, 0, n - 1, a, b);
  }
  // push all updates and get leafs values in O(n)
  // leaf values are stored in res
  void get_leaves(vector<T1> &res) {
    res.resize(n);
    get_leaves(1, 0, n - 1, res);
  }
};

template<class T>
T merge(T a, T b){
  return a;
}

// push update value u1 to update value u2
// (l1, r1) is the range of the node of the update u1
// (l2, r2) is the range of the node of the update u2
template<class U>
void push_upd(U u1, U &u2, int l1, int r1, int l2, int r2){
  u2 += u1;
}

// apply update value u to node value v
// both of the same node of range (l, r)
template<class T, class U>
void apply_upd(U u, T &v, int l, int r){
  v += u;
}



// ST
template<class T, T merge(T, T)>
struct segment_tree{
  int n;
  vector<T> ST;
  segment_tree(int n, T def = T()) : n(n), ST(4 * n + 5, def){
    vector<T> a(n, def);
    build(1, 0, n - 1, a);
  }
  segment_tree(vector<T> &a) : n(a.size()), ST(4 * n + 5){
    build(1, 0, n - 1, a);
  }
  segment_tree(){}
  void build(int i, int l, int r, vector<T> &a){
    if (l == r){
      ST[i] = a[l];
      return;
    }
    int mid = (l + r) / 2;
    build(i * 2, l, mid, a);
    build(i * 2 + 1, mid + 1, r, a);
    ST[i] = merge(ST[i * 2], ST[i * 2 + 1]);
  }
  void update(int i, int l, int r, int p, T x){
    if (r < p or l > p)
      return;
    if (l == r){
      ST[i] = x; // cambia valor por x. Tambien podría ser += x
      return;
    }
    int mid = (l + r) / 2;
    update(i * 2, l, mid, p, x);
    update(i * 2 + 1, mid + 1, r, p, x);
    ST[i] = merge(ST[i * 2], ST[i * 2 + 1]);
  }
  T query(int i, int l, int r, int a, int b){
    if (l >= a and r <= b)
      return ST[i];
    int mid = (l + r) / 2;
    if (b <= mid)
      return query(i * 2, l, mid, a, b);
    else if (a > mid)
      return query(i * 2 + 1, mid + 1, r, a, b);
    else
      return merge(
        query(i * 2, l, mid, a, b), 
        query(i * 2 + 1, mid + 1, r, a, b)
      );
  }
  // user methods
  void update(int p, T x){
    update(1, 0, n - 1, p, x);
  }
  T query(int a, int b){
    return query(1, 0, n - 1, a, b);
  }
};


// Funcion que crea al nodo por encima de los nodos a y b
ll merge(ll a, ll b) {
	return a+b;
}

int main(){
	ios::sync_with_stdio(false); cin.tie(0);
	int n, q; cin >> n >> q;
	vector <ll> x(n);
	for (int i = 0; i < n; ++i) {
		cin >> x[i];
	}
	segment_tree <ll, merge> st(x);

	for (int i = 0; i < q; ++i) {
    int inst; cin >> inst; // instruccion
    if (inst == 1) { // update
      int k; cin >> k;
      k--;
      ll u; cin >> u;
      st.update(k,u);
    } else { // query
    	ll l, r; cin >> l >> r;
    	l--; r--;
    	cout << st.query(l,r) << endl;
    }
	}
	return 0;
}
