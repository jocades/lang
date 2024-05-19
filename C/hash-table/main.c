#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_MAX_LOAD 0.75

typedef enum {
  VAL_NIL,
  VAL_BOOL,
  VAL_NUMBER,
} Value;

typedef struct {
  char* key;
  Value value;
} Entry;

typedef struct {
  int count;
  int capacity;
  Entry* entries;
} Table;

#define ALLOCATE(type, count) (type*)allocate(sizeof(type) * (count))

void* allocate(size_t size) {
  void* block = malloc(size);
  if (block == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(1);
  }

  return block;
}

void initTable(Table* table) {
  table->count = 0;
  table->capacity = 8;
  table->entries = ALLOCATE(Entry, table->capacity);

  for (int i = 0; i < table->capacity; i++) {
    table->entries[i].key = NULL;
    table->entries[i].value = VAL_NIL;
  }
}

uint32_t hash(const char* key) {
  uint32_t hash = 2166136261u;
  for (int i = 0; i < strlen(key); i++) {
    hash ^= (uint8_t)key[i];
    hash *= 16777619;
  }

  return hash;
}

Entry* findEntry(Entry* entries, int capacity, const char* key) {
  uint32_t index = hash(key) % capacity;
  Entry* tombstone = NULL;

  for (;;) {
    Entry* entry = &entries[index];

    if (entry->key == NULL) {
      if (entry->value == VAL_NIL) {
        // empty entry
        return tombstone != NULL ? tombstone : entry;
      } else {
        // tombstone
        if (tombstone == NULL) tombstone = entry;
      }
    } else if (strcmp(entry->key, key) == 0) {
      // found the entry
      return entry;
    }

    index = (index + 1) % capacity;
  }
}

Value* tableGet(Table* table, const char* key) {
  if (table->count == 0) return NULL;

  Entry* entry = findEntry(table->entries, table->capacity, key);
  if (entry->key == NULL) return NULL;

  return &entry->value;
}

Value* tableSet(Table* table, char* key, Value value) {
  if (table->count + 1 > table->capacity * TABLE_MAX_LOAD) {
    // adjust capacity
    int capacity = table->capacity * 2;
    Entry* entries = ALLOCATE(Entry, capacity);
    for (int i = 0; i < capacity; i++) {
      entries[i].key = NULL;
      entries[i].value = VAL_NIL;
    }

    // copy entries get rid of tombstones
    table->count = 0;
    for (int i = 0; i < table->capacity; i++) {
      Entry* entry = &table->entries[i];
      if (entry->key == NULL) continue;

      Entry* dest = findEntry(entries, capacity, entry->key);
      dest->key = entry->key;
      dest->value = entry->value;
      table->count++;
    }

    // free old entries and update table
    free(table->entries);
    table->entries = entries;
    table->capacity = capacity;
  }

  Entry* entry = findEntry(table->entries, table->capacity, key);
  bool is_new_key = entry->key == NULL;
  if (is_new_key && entry->value == VAL_NIL) {
    // we hit a tombstone
    table->count++;
  }

  entry->key = key;
  entry->value = value;

  return &entry->value;
}

void tableDelete(Table* table, const char* key) {
  if (table->count == 0) return;

  Entry* entry = findEntry(table->entries, table->capacity, key);
  if (entry->key == NULL) return;

  entry->key = NULL;
  entry->value = VAL_BOOL;  // tombstone
}

void printTable(Table* table) {
  for (int i = 0; i < table->capacity; i++) {
    Entry* entry = &table->entries[i];
    if (entry->key != NULL) {
      printf("key: %s, value: %d\n", entry->key, entry->value);
    } else {
      printf("key: NULL, value: %d\n", entry->value);
    }
  }
}

int main() {
  Table table;
  initTable(&table);

  tableSet(&table, "foo", VAL_NUMBER);
  tableSet(&table, "bar", VAL_NUMBER);
  tableSet(&table, "baz", VAL_NUMBER);

  printTable(&table);

  Value* foo = tableGet(&table, "foo");
  Value* bar = tableGet(&table, "bar");
  Value* baz = tableGet(&table, "baz");

  printf("foo: %d\n", foo != NULL);
  printf("bar: %d\n", bar != NULL);
  printf("baz: %d\n", baz != NULL);

  tableDelete(&table, "bar");

  printTable(&table);

  Value* bar2 = tableGet(&table, "bar");
  printf("bar2: %d\n", bar2 != NULL);

  return 0;
};
