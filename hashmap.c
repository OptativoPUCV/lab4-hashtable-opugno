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


void insertMap(HashMap * map, char * key, void * value) 
{
  int indice = hash(key, map -> capacity); //obtener el indice del dato.
  if (map -> buckets[indice] == NULL && map -> buckets[indice] -> key == NULL)
  {
    Pair *aux = (Pair *) malloc(sizeof(Pair)); // crear una auxiliar
    aux -> key = key;
    aux -> value = value;
    map -> buckets[indice] = aux;
  }
  else
  {
    for (int i = 0; i < map -> capacity; i++)
    {
      if (map -> buckets[i] == NULL)
      {
        Pair *aux = (Pair*) malloc(sizeof(Pair));
        aux -> key = key;
        aux -> value = value;
        map -> buckets[i] = aux;
      }
    }
  }
} 

void enlarge(HashMap * map) 
{
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) 
{
  HashMap * map = (HashMap *) malloc(sizeof(HashMap));        //crar mapa
  map -> buckets = (Pair **) calloc(sizeof(Pair), capacity);  //inicializar cada espacio del la tabla.
  map -> size = 0;                                            //inicializar el tamaño
  map -> current = -1;                                        //el current es -1, ya que todavia no estamos en ningún espacio.
  map -> capacity = capacity;
  return map;
}

void eraseMap(HashMap * map,  char * key) {    


}

Pair * searchMap(HashMap * map,  char * key) 
{   
  //int indice = hash(key, map -> capacity);

  //fo

    return NULL;
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
