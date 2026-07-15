/* Compiled by the Makefile (never run) to find out whether this machine has
 * a working OpenMP toolchain, so `make` adapts instead of demanding a flag.
 * Kept as a real file because generating it inline from make + printf means
 * escaping '#' through both make and the shell — which silently produced a
 * broken probe that reported "no OpenMP" on machines that had it.
 */
#include <omp.h>

int main(void) {
  return omp_get_num_threads();
}
