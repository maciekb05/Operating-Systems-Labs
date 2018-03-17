/** @file hw_hello.c
  * Plik funkcji wypisuj±cych powitania
  * $Id$
  */

#include <stdio.h>
#include "hw_defs.h"

/**
 * Funkcja wypisuje (prawie) klasyczne powitanie
 * @returns rezultat pracy, ew. numer b³êdu
 */
int hello (void)
{
    printf("hello(v%d): \tHello cruel world!\n", WERSJA);

    return 0;
}
