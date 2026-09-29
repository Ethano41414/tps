#include "teZZt.h"
#include <stdio.h>

const int    __tezzt_registered_signals [] = {SIGINT, SIGQUIT, SIGSEGV, SIGKILL, SIGTERM, -1};
const char * __tezzt_string_signals     [] = { "SIGINT", "SIGQUIT", "SEGMENTATION FAULT", "SIGKILL", "SIGTERM", ""};

__attribute__((unused)) static unsigned __tezzt__passed_tests_counter = 0;
__attribute__((unused)) static unsigned __tezzt__failed_tests_counter = 0;

__attribute__((unused)) static unsigned __tezzt__malloc_counter = 0;
__attribute__((unused)) static unsigned __tezzt__freeed_counter = 0;


void __tezzt__passed_test() {
	++__tezzt__passed_tests_counter;
}
void __tezzt__failed_test() {
	++__tezzt__failed_tests_counter;
}

void __tezzt__signal_handler(int s) {
  int i;
  for(i=0; __tezzt_registered_signals[i]>0 && __tezzt_registered_signals[i]!=s; ++i);
  fprintf(stderr, "Signal intercepted...[%s]\n" , __tezzt_string_signals[i]);
  fprintf( stderr, __ANSI_NOR__ );
  exit(s);
}

void __tezzt__exit_program_with_report() {
  fprintf( stderr, "--- teZZt REPORT ---\n");
  fprintf( stderr, __ANSI_RED__ "%3d test(s) failed\n",   __tezzt__failed_tests_counter);
  fprintf( stderr, __ANSI_GRE__ "%3d test(s) passed\n",   __tezzt__passed_tests_counter);
  fprintf( stderr, __ANSI_NOR__ );
}