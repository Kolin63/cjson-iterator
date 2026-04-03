#include <assert.h>
#include <stdio.h>

#include "cJSON.h"
#include "fileio.h"
#include "json_iterator.h"


int main() {
  struct fileio* fileio = fileio_init();
  FILE* file = fopen("data.json", "r");

  fileio_read_all(fileio, file);

  cJSON* json = cJSON_Parse(fileio->buf);

  fileio_cleanup(fileio);
  fclose(file);

  struct json_iterator* iter = json_iterator_init(json);

  while (true) {
    iter = json_iterate(iter);
    if (iter->parent == NULL) break;
    if (iter->json == NULL) continue;

    switch (iter->json->type) {
    case (cJSON_Invalid):
      printf("%s: cJSON_Invalid\n", iter->json->string);
      break;
    case (cJSON_False):
      printf("%s: cJSON_False\n", iter->json->string);
      break;
    case (cJSON_True):
      printf("%s: cJSON_True\n", iter->json->string);
      break;
    case (cJSON_NULL):
      printf("%s: cJSON_NULL\n", iter->json->string);
      break;
    case (cJSON_Number):
      printf("%s: cJSON_Number (%f)\n", iter->json->string,
             iter->json->valuedouble);
      break;
    case (cJSON_String):
      printf("%s: cJSON_String (%s)\n", iter->json->string,
             iter->json->valuestring);
      break;
    case (cJSON_Array):
      printf("%s: cJSON_Array\n", iter->json->string);
      break;
    case (cJSON_Object):
      printf("%s: cJSON_Object\n", iter->json->string);
      break;
    case (cJSON_Raw):
      printf("%s: cJSON_Raw\n", iter->json->string);
      break;
    }
  }

  json_iterator_cleanup(iter);
  cJSON_Delete(json);

  return 0;
}
