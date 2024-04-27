#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
    char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {
  //funcion hash a current, para guardar el nuevo par
  map->current = hash(key, map->capacity);
  
  if(map->buckets[map->current] == NULL || map->buckets[map->current]->key == NULL){
    map->buckets[map->current] = createPair(key, value);
    map->size++;
  }
  else{
    while(map->buckets[map->current] != NULL && map->buckets[map->current]-> key != NULL){
      if(is_equal(map->buckets[map->current]->key, key)){
        return; //como la key ya existe, no se inserta nada
      }
      //metodo de resolucion de colisiones (busqueda lineal)
        map->current = (map->current + 1) % map->capacity;
    }
    map->buckets[map->current] = createPair(key,  value);
    map->size++;
  }
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) {
  HashMap * mapa = (HashMap *)malloc(sizeof(HashMap));
  mapa->buckets = (Pair **)calloc(capacity,sizeof(Pair*));
  mapa->size = 0;
  mapa->capacity = capacity;
  mapa->current = -1;
  return mapa;
}

void eraseMap(HashMap * map,  char * key) {    
  Pair * elem = searchMap(map, key);
  if(elem != NULL){
    elem->key = NULL; 
  }
  map->size--;
}

Pair * searchMap(HashMap * map,  char * key) {
  map->current = hash(key, map->capacity);
  do{
    if(is_equal(map->buckets[map->current]->key, key)){
      return map->buckets[map->current];
    }
    map->current = (map->current + 1) % map->capacity;
  } while(map->buckets[map->current] != NULL);
  return NULL;
}

Pair * firstMap(HashMap * map) {
    if (map == NULL || map->buckets == NULL) return NULL;

    // Encuentra el primer par válido en el arreglo buckets
    for (long i = 0; i < map->capacity; i++) {
        if (map->buckets[i] != NULL && map->buckets[i]->key != NULL) {
            map->current = i; // Actualiza el índice current
            return map->buckets[i];
        }
    }

    return NULL; // No se encontró ningún par válido
}

Pair * nextMap(HashMap * map) {

  return NULL;
}
