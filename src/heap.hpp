#include "queue.hpp"

template <typename Type> class heap {
public:
  node<Type> *father;
  node<Type> *root;
  queue_t<Type> *queue;
  heap();
  ~heap(){}
  void drop( node<Type>* );
  void insert( Type );
  void swap ( node<Type>*, node<Type>* );
  Type pop_first();
  void rise( node<Type>* );
  void print() { queue->print(); }
};

template <typename Type> heap<Type>::heap() {
  father = root = NULL;
  queue = new queue_t<Type>;
}
/*
  Función que es encarga de regresar el elemento que está hasta arriba del heap, que es el más pequeño también.
  Valor de retorno:
    El elemento que está hasta arriba del montón.
*/
template <typename Type> Type heap<Type>::pop_first () {
  //Si el montón está vacío vamos a regresar un elemento predifinido.
  //Elegí el -9999999 pero puede ser cualquiera con tal que no interfiera en los elementos del heap.
  if (!root) return Type(-9999999);
  //Dos nodos, igualados a root. Por si la n no cambia de valor.
  node<Type>*n = root;
  node<Type>*m = root;
  //Si el padre tiene hijo izquierdo entonces n va a ser ese hijo izquierdo.
  if (father->left_child) n = father->left_child;
  else {
    //Si no va a ser el hijo derecho del padre anterior.
    father = father->previous;
    if (father) n = father->right_child;
  }
  //Intercambiamos
  swap(m,n);
  //Quitamos de la cola.
  queue->pop_back();
  //Sacamos el valor
  Type key = m->key;
  //Sacamos al hijo.
  if (m->father)
    if (m->father->right_child == m) m->father->right_child = NULL;
    else m->father->left_child = NULL;
  if (m == root) root = NULL;
  //Borramos, dropeamos n y regresamos la llave. (el valor.)
  delete m;
  drop(n);
  return key;
}
/*
  Función que se encarga de bajar a los nodos a su lugar correspondiente.
  Parámetros:
    El nodo a bajar.
*/
template <typename Type> void heap<Type>::drop( node<Type> *n) {
  node<Type> *m;
  //Primero nos aseguramos que tenga al menos un hijo.
  while (n->left_child || n->right_child) {
    //Si no tiene hijo izquierdo, entonces tiene hijo derecho.
    //Vamos a guardar ese hijo en m.
    if (!n->left_child) m = n->right_child;
    //Si no tiene hijo derecho entonces tiene un hijo izquierdo.
    else if (!n->right_child) m = n->left_child;
    //Y si no, entonces tiene dos hijos, y vamos a guardar en m al hijo menor.
    else if (n->left_child->key < n->right_child->key) m = n->left_child;
    else m = n->right_child;
    //Vemos si ese hijo es menor, de ser así lo intercambiamos.
    if (n->key > m->key) swap(n,m);
    //Si no ya está todo en orden.
    else return;
  }
}
/*
  Función que se encarga de hacer un swap de dos nodos en el heap.
  Parámetros:
    Los dos nodos a intercambiar
*/
template <typename Type> void heap<Type>::swap( node<Type> *n, node<Type> *m ) {
  //Si los nodos son iguales no hacemos nada.
  if (n == m) return;

  //Checamos si alguno de ellos es el root, de ser así cambiamos este apuntador
  if (root == n) root = m;
  else if (root == m) root = n;

  //Lo mismo con el padre, que es nuestro puntero que nos dice en qué parte del heap vamos.
  if (father == n) father = m;
  else if (father == m) father = n;

  //Checamos que el padre de n no sea m.
  //De ser así intercambiamos los punteros.
  node<Type> *aux;
  if (n->father == m) {
    aux = n;
    n = m;
    m = aux;
  }
  //Cambiamos esos nodos en la cola.
  queue->swap(n,m);
  //Intercambiamos al hijo izquierdo.
  aux = m->left_child;
  if (n->left_child == m) m->left_child = n;
  else m->left_child = n->left_child;
  n->left_child = aux;
  //Intercambiamos al hijo derecho.
  aux = m->right_child;
  if (n->right_child == m) m->right_child = n;
  else m->right_child = n->right_child;
  n->right_child = aux;
  //Intercambiamos al padre.
  aux = n->father;
  if (m->father == n) n->father = m;
  else n->father = m->father;
  m->father = aux;
  //Vemos qué es lo que existe y le decimos quién es su nuevo hijo/padre.
  if (n->left_child) n->left_child->father = n;
  if (m->left_child) m->left_child->father = m;
  if (n->right_child) n->right_child->father = n;
  if (m->right_child) m->right_child->father = m;
  if (n->father)
    if (n->father->right_child == m) n->father->right_child = n;
    else if (n->father->left_child == m) n->father->left_child = n;
  if (m->father)
    if (m->father->right_child == n) m->father->right_child = m;
    else if (m->father->left_child == n) m->father->left_child = m;
}
/*
  Función que toma un nodo en el heap y lo va subiendo en el mismo hasta que esté
  en su lugar correspondiente.
*/
template <typename Type> void heap<Type>::rise(node<Type>* _node) {
  //Mientras su padre exista y su padre sea mayor que el nodo, hacer un intercambio.
  while (_node->father && _node->father->key > _node->key) swap(_node->father, _node);
}
/*
  Función que inserta en el heap.
  Parámetros: La llave de tipo Type
*/
template <typename Type> void heap<Type>::insert( Type key ) {
  //Se permite repetición en el heap.
  node<Type> *n = new node<Type>(key);
  //Insertamos en la cola.
  queue->insert(n);
  //Vemos si ya hay algo en el heap checando la raíz.
  //El caso donde hay algo es más común así que lo checamos primero.
  if (root) {
    //Aquí vamos a checar si nuestra variable father tiene un hijo izquierdo.
    //Si tiene un hijo izquierdo esto quiere decir que le debemos poner un hijo derecho
    //Y cambiar la variable a la siguiente 'father = father->next'
    if (father->left_child) {
      father->right_child = n;
      n->father = father;
      father = father->next;
    } else {
      //Si no, entonces sólo le ponemos un hijo izquierdo.
      father->left_child = n;
      n->father = father;
    }
    //Para asegurar que lo más chico esté siempre arriba en el heap hacemos rise a todo.
    rise(n);
  }
  else {
    //Si no hay raíz el heap está vacío así que sólo asignamos la raíz y el padre.
    root = n;
    father = n;
  }
}
