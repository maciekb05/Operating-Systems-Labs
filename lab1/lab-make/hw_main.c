/** @file hw_main.c
  * Plik g³ówny programu
  * $Id$
  */

#include "hw_defs.h"
#include "hw_hello.h"
#include "hw_power.h"

/**
 * G³ówna funkcja programu
 * @param argc liczba argumentów wywo³ania
 * @param argv lista argumentów wywo³ania
 * @returns rezultat pracy, ew. numer b³êdu
 */
int main (int argc, char *argv[])
{
    int r;

    r = hello();
    r = calc_pow3(4);

    return r;
}
