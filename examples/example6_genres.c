#include "../tdas/map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main() {
  char input[] = "Comedy, Action, Adventure,Thriller,Comedy,Romance";
  List *result = split_string(input, ",");

  for (char *str = list_first(result); str != NULL; str = list_next(result))
    printf("%s\n", str);

  return 0;
}
