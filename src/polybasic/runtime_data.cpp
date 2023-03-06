#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "runtime_data.hpp"

typedef struct Data {
   Value value;
   struct Data *next;

   Data(const Value &v) : value(v), next(NULL) {}
} Data;

static Data *head = NULL;
static Data *tail = NULL;
static Data *current = NULL;

void add_data(const Value &v) {
   Data *tmp = new Data(v);

   if (head == NULL) {
      head = tail = current = tmp;
   }
   else {
      tail->next = tmp;
      tail = tmp;
   }
}

int get_data(Value &v)
{
   if (current) {
      v = current->value;
      current = current->next;
      return 1;
   }
   else {
      return 0;
   }
}

void rewind_data(void) {
   current = head;
}

