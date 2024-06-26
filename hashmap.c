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
  //si el espacio esta ocupado y la clave es distinta
  //no se deben ingresar claves iguales
  while (map -> buckets[indice] != NULL && map -> buckets[indice] -> key != key)
  {
    indice = (indice +1) % map -> capacity; //si el indice esta ocupado, se busca el siguiente.
  }

  //agrego key y value al lugar con el indice antes obtenido.
  Pair *aux = (Pair*) malloc(sizeof(Pair));
  aux -> key = key;
  aux -> value = value;
  map -> buckets[indice] = aux;
  map -> size++;
  map -> current = indice;  
} 

void enlarge(HashMap * map) 
{
  enlarge_called = 1; //no borrar (testing purposes)

  Pair** oldBuckets = map -> buckets;;
  
  int newCapacity = map -> capacity * 2;
  map -> capacity = newCapacity;
  
  map -> buckets = (Pair**) calloc(newCapacity, sizeof(Pair*));
  if (map -> buckets == NULL)
  {
    return;
  }
  
  int oldSize = map -> size;
  map -> size = 0;

  for (int i = 0; i < oldSize; i++)
  {
    if (oldBuckets[i] != NULL)
    {
      insertMap(map, oldBuckets[i] -> key, oldBuckets[i] -> value);
      free(oldBuckets[i]);
    }
  }
  free(oldBuckets);
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

void eraseMap(HashMap * map,  char * key) 
{    
  int index = hash(key, map -> capacity);

  while(map -> buckets[index] != NULL)
  {
    if (strcmp(map -> buckets[index] -> key, key) == 0)
    {
      map -> buckets[index] -> key = NULL;
      map -> size--;
    }
    index = (index + 1) % map -> capacity;
  }
}

Pair * searchMap(HashMap * map,  char * key) 
{   
  int index = hash(key, map -> capacity);

  while (map -> buckets[index] != NULL)
  {
    if (strcmp(map -> buckets[index] -> key, key) == 0) 
    {
      map -> current = index;
      return map -> buckets[index];
    }
    index = (index + 1) % map -> capacity;
  }
  return NULL;
}

Pair * firstMap(HashMap * map) 
{
  for (map -> current = 0; map -> current < map -> capacity; map -> current++)
  {
    if (map -> buckets[map -> current] != NULL && map -> buckets[map -> current] -> key != NULL)
    {
      return map -> buckets[map -> current];
    }
      
  }
  
  return NULL;
}

Pair * nextMap(HashMap * map) 
{
  map -> current ++;
  while (map -> current < map -> capacity)
  {
    if (map -> buckets[map -> current] != NULL)
      return map -> buckets[map -> current];
  
    map -> current ++;
  }
  return NULL;
}
