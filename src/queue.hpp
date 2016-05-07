#pragma once
#include <iostream>
#include "structures.hpp"
template <typename Type> class queue_t {
  node<Type> *begin, *end;
public:
  queue_t() : begin(NULL), end(NULL){}
  ~queue_t();
  void insert ( node<Type> *);
  void swap ( node<Type>*, node<Type> *);
  void pop_back ( );
  void print();
};
//Destructor.
template <typename Type> queue_t<Type>::~queue_t() {
  node<Type> *n;
  while (begin) {
    n = begin;
    begin = begin->next;
    delete n;
  }
}
/*
  Función que se encarga de insertar en la cola.
  Parámetros:
    El nodo a insertar en la cola.
*/
template <typename Type> void queue_t<Type>::insert( node<Type> *_node ) {
  //Como es una cola, simplemente utilizamos la variable end para insertar.
  //Y lo ponemos al final.
  if (begin) end->next = _node;
  else begin = _node;
  _node->previous = end;
  end = _node;
}
/*
  Función que elimina el último elemento en la cola.
*/
template <typename Type> void queue_t<Type>::pop_back() {
  if (end) {
    end = end->previous;
    if (end) end->next = NULL;
    else begin = NULL;
  }
}
/*
  Función que se encarga de intercambiar nodos en la cola.
  Parámetros:
    Los dos nodos a intercambiar.
*/
template <typename Type> void queue_t<Type>::swap( node<Type>* a, node<Type>* b ) {
  //Si es el mismo no hacemos nada
  if (a == b) return;
  //Si se intercambia el begin (muy común) intercambiamos ese puntero también.
  if (begin == a) begin = b;
  else if (begin == b) begin = a;

  //Lo mismo con el end.
  if (end == b) end = a;
  else if (end == a) end = b;

  //Nos aseguramos que el siguiente de b no sea a, de ser así intercambiamos los punteros.
  node<Type> *aux;
  if (b->next == a) {
    aux = b;
    b = a;
    a = aux;
  }
  //Intercambiamos el de la izquierda
  aux = a->previous;
  if (b->previous == a) a->previous = b;
  else a->previous = b->previous;
  b->previous = aux;
  //Intercambiamos el de la derecha.
  aux = b->next;
  if (a->next == b) b->next = a;
  else b->next = a->next;
  a->next = aux;

  //Checamos lo que existe y le decimos quién está a su derecha o izquierda.
  if (a->previous) a->previous->next = a;
  if (a->next)a->next->previous = a;
  if (b->previous) b->previous->next = b;
  if (b->next) b->next->previous = b;
}
template <typename Type> void queue_t<Type>::print() {
  node<Type> *n = begin;
  while (n) {
    std::cout << "Nodo: " << n->key << std::endl;
    if (n->father) std::cout << "Padre: " << n->father->key << std::endl;
    if (n->left_child) std::cout << "Hijo Izquierdo: " << n->left_child->key << std::endl;
    if (n->right_child) std::cout << "Hijo Derecho: " << n->right_child->key << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    n = n->next;
  }
}
