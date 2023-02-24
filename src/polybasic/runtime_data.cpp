#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "runtime_data.h"

typedef struct Data {
   char typ;
   union {
      double dval;
      int64_t ival;
      Rational *rval;
      const char *sval;
   };
   struct Data *next;
} Data;

static Data *head = NULL;
static Data *tail = NULL;
static Data *current = NULL;

void add_data(double d) {
   Data *tmp = (Data *) malloc(sizeof(Data));
   tmp->typ = 'd';
   tmp->dval = d;
   tmp->next = NULL;

   if (head == NULL) {
      head = tail = current = tmp;
   }
   else {
      tail->next = tmp;
      tail = tmp;
   }
}

void add_data(int64_t i) {
   Data *tmp = (Data *) malloc(sizeof(Data));
   tmp->typ = 'i';
   tmp->ival = i;
   tmp->next = NULL;

   if (head == NULL) {
      head = tail = current = tmp;
   }
   else {
      tail->next = tmp;
      tail = tmp;
   }
}

void add_data(Rational *r) {
   Data *tmp = (Data *) malloc(sizeof(Data));
   tmp->typ = 'r';
   tmp->rval = new Rational(*r);
   tmp->next = NULL;

   if (head == NULL) {
      head = tail = current = tmp;
   }
   else {
      tail->next = tmp;
      tail = tmp;
   }
}

void add_data(const char *s) {
   Data *tmp = (Data *) malloc(sizeof(Data));
   tmp->typ = 's';
   tmp->sval = strdup(s);
   tmp->next = NULL;

   if (head == NULL) {
      head = tail = current = tmp;
   }
   else {
      tail->next = tmp;
      tail = tmp;
   }
}

char next_data_type(void) {
   if (!current) {
      return 0;
   }
   return current->typ;
}

int get_data(double &d)
{
   if (current) {
      d = current->dval;
      current = current->next;
      return 1;
   }
   else {
      return 0;
   }
}

int get_data(int64_t &i)
{
   if (current) {
      i = current->ival;
      current = current->next;
      return 1;
   }
   else {
      return 0;
   }
}

int get_data(Rational *&r)
{
   if (current) {
      r = current->rval;
      current = current->next;
      return 1;
   }
   else {
      return 0;
   }
}

int get_data(const char *&s)
{
   if (current) {
      s = current->sval;
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

