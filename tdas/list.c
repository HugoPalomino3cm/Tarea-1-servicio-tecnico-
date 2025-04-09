#include "list.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  void *data;
  struct Node *next;
} Node;

struct List {
  Node *head;
  Node *tail;
  Node *current;
  int size;
};

typedef List List;

List *list_create() {
  List *newList = (List *)malloc(sizeof(List));
  if (newList == NULL) {
    return NULL; // Fallo en la asignación de memoria
  }
  newList->head = NULL;
  newList->tail = NULL;
  newList->current = NULL;
  newList->size = 0;
  return newList;
}

void *list_first(List *L) {
  if (L == NULL || L->head == NULL) {
    return NULL; // Lista vacía o no inicializada
  }
  L->current = L->head;
  return L->current->data;
}

void *list_next(List *L) {
  if (L == NULL || L->current == NULL || L->current->next == NULL) {
    return NULL; // Lista vacía, no inicializada o no hay más elementos
  }
  L->current = L->current->next;
  return L->current->data;
}

void list_pushFront(List *L, void *data) {
  if (L == NULL) {
    return; // Lista no inicializada
  }
  Node *newNode = (Node *)malloc(sizeof(Node));
  if (newNode == NULL) {
    return; // Fallo en la asignación de memoria
  }
  newNode->data = data;
  newNode->next = L->head;
  L->head = newNode;
  if (L->tail == NULL) { // Si la lista estaba vacía
    L->tail = newNode;
  }
  L->size++;
}

void list_pushBack(List *L, void *data) {
  if (L == NULL) {
    return; // Lista no inicializada
  }
  Node *newNode = (Node *)malloc(sizeof(Node));
  if (newNode == NULL) {
    return; // Fallo en la asignación de memoria
  }
  newNode->data = data;
  newNode->next = NULL;
  if (L->tail == NULL) { // Si la lista está vacía
    L->head = newNode;
    L->tail = newNode;
  } else {
    L->tail->next = newNode;
    L->tail = newNode;
  }
  L->size++;
}

void list_pushCurrent(List *L, void *data) {
  if (L == NULL || L->current == NULL) {
    return; // Lista no inicializada o current no está definido
  }
  Node *newNode = (Node *)malloc(sizeof(Node));
  if (newNode == NULL) {
    return; // Fallo en la asignación de memoria
  }
  newNode->data = data;
  newNode->next = L->current->next;
  L->current->next = newNode;
  if (L->current == L->tail) {
    L->tail = newNode; // Actualizar tail si se inserta al final
  }
  L->size++;
}

void list_sortedInsert(List *L, void *data,
                       int (*lower_than)(void *data1, void *data2)) {
  if (L == NULL) {
    return; // Lista no inicializada
  }

  // Caso especial: inserción al principio o en lista vacía
  if (L->head == NULL || lower_than(data, L->head->data)) {
    list_pushFront(L, data);
    return;
  }

  // Caso general: encontrar la posición correcta para insertar
  Node *current = L->head;
  while (current->next != NULL && !lower_than(data, current->next->data)) {
    current = current->next;
  }

  // Preparar para usar list_pushCurrent
  L->current = current;

  // Insertar el nodo en la posición actual
  list_pushCurrent(L, data);
}

void *list_popFront(List *L) {
  if (L == NULL || L->head == NULL) {
    return NULL; // Lista vacía o no inicializada
  }
  Node *temp = L->head;
  L->head = L->head->next;
  if (L->head == NULL) {
    L->tail = NULL; // La lista ahora está vacía
  }
  void *data = temp->data;
  free(temp);
  L->size--;
  return data;
}

void *list_popBack(List *L) {
  if (L == NULL || L->head == NULL) {
    return NULL; // Lista vacía o no inicializada
  }
  if (L->head == L->tail) { // Solo un elemento en la lista
    return list_popFront(L);
  }
  Node *current = L->head;
  while (current->next != L->tail) {
    current = current->next;
  }
  void *data = L->tail->data;
  free(L->tail);
  current->next = NULL;
  L->tail = current;
  L->size--;
  return data;
}

int list_size(List *L){
    return L->size;
}

void *list_popCurrent(List *L) {
  if (L == NULL || L->current == NULL) {
    return NULL; // Lista no inicializada o current no definido
  }
  if (L->current == L->head) {
    return list_popFront(L);
  }
  Node *temp = L->head;
  while (temp != NULL && temp->next != L->current) {
    temp = temp->next;
  }

  temp->next = L->current->next;
  if (L->current == L->tail) {
    L->tail = temp; // Actualizar tail si se elimina el último elemento
  }
  void *data = L->current->data;
  free(L->current);
  L->current = temp->next;
  L->size--;
  return data;
}

void list_clean(List *L) {
  if (L == NULL) {
    return; // Lista no inicializada
  }
  Node *current = L->head;
  Node *next;
  while (current != NULL) {
    next = current->next;
    free(current);
    current = next;
  }
  L->head = NULL;
  L->tail = NULL;
  L->current = NULL;
  L->size = 0;
}
