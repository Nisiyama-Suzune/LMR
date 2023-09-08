template <class T>
struct node {
  T *f, *c[2]; int size;
  node() { f = c[0] = c[1] = nullptr; size = 1; }
  void push_down() {}
  void update() {
    size = 1; for (int t = 0; t < 2; ++t)
      if (c[t]) size += c[t]->size; } };
template <class T>
struct reversible_node : node<T> {
  int r;
  reversible_node() : node<T>() { r = 0; }
  void push_down() {
    node<T>::push_down();
    if (r) {
      for (int t = 0; t < 2; ++t)
        if (node<T>::c[t]) node<T>::c[t]->reverse();
      r = 0; } }
  void update() { node<T>::update(); }
  //! Reverse the range of this node.
  void reverse() {
    std::swap(node<T>::c[0], node<T>::c[1]);
    r = r ^ 1; } };
template <class T, int MAXSIZE = 500000>
struct tree {
  T pool[MAXSIZE + 2]; int cap; T *root;
  T *new_node(const T &val = T()) { return &pool[cap++]; }
  tree() {
    cap = 0, root = new_node(), root->c[1] = new_node(), root->size = 2;
    root->c[1]->f = root; }
  void rotate(T *n) {
    int v = n->f->c[0] == n; T *p = n->f, *m = n->c[v];
    if (p->f) p->f->c[p->f->c[1] == p] = n;
    n->f = p->f, n->c[v] = p; p->f = n, p->c[v ^ 1] = m;
    if (m) m->f = p; p->update(), n->update(); }
  void splay(T *n, T *s = nullptr) {
    while (n->f != s) {
      T *m = n->f, *l = m->f;
      if (l == s) rotate(n);
      else if ((l->c[0] == m) == (m->c[0] == n)) rotate(m), rotate(n);
      else rotate(n), rotate(n); }
    if (!s) root = n; }
  int size() { return root->size - 2; }
  int walk(T *n, int &v, int &pos) {
    n->push_down(); int s = n->c[0] ? n->c[0]->size : 0;
    (v = s < pos) && (pos -= s + 1); return s; }
  //! Insert node n to position pos.
  void insert(T *n, int pos) {
    T *c = root; int v; ++pos;
    while (walk(c, v, pos), c->c[v] && (c = c->c[v]));
    c->c[v] = n, n->f = c, splay(n); }
  //! Find the node at position pos. If sp is true, splay it.
  T *find(int pos, int sp = true) {
    T *c = root; int v; ++pos;
    while ((pos < walk(c, v, pos) || v) && (c = c->c[v]));
    if (sp) splay(c);
    return c; }
  //! Find the range [posl, posr) on the splay tree.
  T *find_range(int posl, int posr) {
    T *r = find(posr), *l = find(posl - 1, false);
    splay(l, r);
    if (l->c[1]) l->c[1]->push_down();
    return l->c[1]; }
  //! Insert nn of size nn_size to position pos.
  void insert_range(T **nn, int nn_size, int pos) {
    T *r = find(pos), *l = find(pos - 1, false), *c = l;
    splay(l, r);
    for (int i = 0; i < nn_size; ++i) c->c[1] = nn[i], nn[i]->f = c, c = nn[i];
    for (int i = nn_size - 1; i >= 0; --i) nn[i]->update();
    l->update(), r->update(), splay(nn[nn_size - 1]); }
  void dealloc(T *n) {
    if (!n) return;
    dealloc(n->c[0]); dealloc(n->c[1]);
    pool.dealloc(n); }
  //! Remove from position [posl, posr).
  void erase_range(int posl, int posr) {
    T *n = find_range(posl, posr);
    n->f->c[1] = nullptr, n->f->update(), n->f->f->update(), n->f = nullptr;
    dealloc(n); } };