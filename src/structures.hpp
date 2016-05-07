template <typename Type> class node {
public:
  Type key;
  node<Type> *father;
  node<Type> *left_child;
  node<Type> *right_child;
  node<Type> *previous;
  node<Type> *next;
  node ( Type key ) : key(key), father(NULL), left_child(NULL), right_child(NULL),
                      previous(NULL), next(NULL) {}
  bool operator == (Type key) { return this->key == key; }
  bool operator != (Type key) { return this->key != key; }
  bool operator < (Type key) { return this->key < key; }
  bool operator > (Type key) { return this->key > key; }
};
