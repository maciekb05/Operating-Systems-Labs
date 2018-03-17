/** @file hw_power.c
  * Plik funkcji wypisuj±cych wyniki operacji mat
  * $Id$
  */

#include <stdio.h>
#include <math.h>
#include "hw_defs.h"

/**
 * Funkcja wylicza i wypisuje 3. potêgê danej liczby
 * @param   n liczba której potêgê nale¿y wyliczyæ
 * @returns   rezultat pracy, ew. numer b³êdu
 */
int calc_pow3 (int n)
{
    printf("calc_pow3(v%d): \t%d ^ 3 to jest %.2f\n",
	   WERSJA, n, pow((float)n,(float)3));

    return 0;
}
