#ifndef MAP_H
#define MAP_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define MAP_BUFFER_SIZE 20

typedef void* Map_Key;
typedef void* Map_Value;

typedef struct Map {
	Map_Key **keys;
	Map_Value **values;

	size_t key_size;
	size_t value_size;

	size_t count;
	size_t size;
} Map;

void map_init(Map *map, size_t key_size, size_t value_size, size_t size);
void map_clean(Map *map);

bool map_set(Map *map, Map_Key key, Map_Value value);
Map_Value map_get(Map *map, Map_Key key);
bool map_has(Map *map, Map_Key key);

size_t map_count(Map *map);
bool map_delete(Map *map, Map_Key key);
void map_empty(Map *map);

#endif
