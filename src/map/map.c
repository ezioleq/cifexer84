#include "map.h"

#include <string.h>

#include "../utils.h"

void map_init(Map *map, size_t key_size, size_t value_size, size_t size) {
	map->count = 0;
	map->size = size;

	map->key_size = key_size;
	map->value_size = value_size;

	map->keys = calloc(map->size, sizeof(Map_Key));
	map->values = calloc(map->size, sizeof(Map_Value));
}

bool map_set(Map *map, Map_Key key, Map_Value value) {
	// TODO: Handle duplicate keys
	if (map->count + 1 > map->size) {
		size_t new_size = map->size + MAP_BUFFER_SIZE;
		map->keys = realloc(map->keys, new_size * sizeof(Map_Key));
		map->values = realloc(map->values, new_size * sizeof(Map_Value));

		if (!map->keys || !map->values) {
			fprintf(stderr, "Cannot reallocate memory for the map object!\n");
			return false;
		}

		for (size_t i = map->size; i < new_size; ++i) {
			map->keys[i] = NULL;
			map->values[i] = NULL;
		}

		map->size = new_size;
	}

	for (size_t i = 0; i < map->size; ++i) {
		if (map->keys[i] == NULL) {
			map->keys[i] = malloc(map->key_size);
			memcpy(map->keys[i], key, map->key_size);

			map->values[i] = malloc(map->value_size);
			memcpy(map->values[i], value, map->value_size);

			if (!map->keys[i] || !map->values[i]) {
				fprintf(stderr, "Cannot allocate memory for the map pair!");
				return false;
			}

			break;
		}
	}

	++map->count;
	return true;
}

void map_clean(Map *map) {
	for (size_t i = 0; i < map->size; ++i) {
		free(map->keys[i]);
		free(map->values[i]);
	}

	free(map->keys);
	free(map->values);
}

Map_Value map_get(Map *map, Map_Key key) {
	for (size_t i = 0; i < map->size; ++i) {
		if (map->keys[i] != NULL && memcmp(map->keys[i], key, map->key_size) == 0)
			return map->values[i];
	}
	return NULL;
}

ALWAYS_INLINE bool map_has(Map *map, Map_Key key) {
	return (map_get(map, key) != NULL);
}

ALWAYS_INLINE size_t map_count(Map *map) {
	return map->count;
}

bool map_delete(Map *map, Map_Key key) {
	bool success = true;

	for (size_t i = 0; i < map->count; ++i) {
		if (memcmp(map->keys[i], key, map->key_size) == 0) {
			free(map->keys[i]);
			free(map->values[i]);
			map->keys[i] = NULL;
			map->values[i] = NULL;

			success = true;
			--map->count;
			break;
		} else {
			success = false;
		}
	}

	return success;
}

void map_empty(Map *map) {
	for (size_t i = 0; i < map->size; ++i) {
		map_delete(map, map->keys[i]);
	}
}
