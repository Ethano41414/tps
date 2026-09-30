#include "teZZt.h"

#ifdef MEMTEZZT
#include <dlfcn.h>
#endif 

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


void *(*mallocp)(size_t);
void *(*callocp)(size_t, size_t);
void *(*reallocp)(void *, size_t);
void  (*freep)(void *);
void *(*memalignp)(size_t, size_t);
void *(*aligned_allocp)(size_t, size_t);

size_t(*strlenp)(const char*);


__attribute__((unused)) int tezzt_count_alloc   = 0;
__attribute__((unused)) int tezzt_count_dealloc = 0;
__attribute__((unused)) int tezzt_bytes_alloc   = 0;

__attribute__((unused)) int tezzt_count_strlen = 0;


#ifdef MEMTEZZT

void * malloc(size_t len) {
	void * ret;
     
    ret = (*mallocp)(len);
    //printf("MALLOC");
    if (ret) {
    	++tezzt_count_alloc;
	    tezzt_bytes_alloc+=len;
    }

	return ret;
}

void * calloc(size_t count, size_t size) {
   void * ret;
   //printf("CALLOC");
   ret = (*callocp)(count, size);
   if (ret) {
    	++tezzt_count_alloc;
	    tezzt_bytes_alloc+=(count*size);
    }

   return ret;
}

void * memalign(size_t count, size_t size) {
   void * ret;

   ret = (*memalignp)(count, size);
   if (ret) {
    	++tezzt_count_alloc;
	    tezzt_bytes_alloc+=(count*size);
    }

   return ret;
}

void * aligned_alloc(size_t alignment, size_t size) {
  void * ret;

  ret = (*aligned_allocp)(alignment, size);
  
  if (ret) {
     ++tezzt_count_alloc;
     tezzt_bytes_alloc+=size;
  }

  return ret;
}


void * realloc(void * ptr, size_t size) {
	void * ret;

	ret = (*reallocp)(ptr, size);

	if ((ptr) && (!size))
		++tezzt_count_dealloc;
	else {
		++tezzt_count_alloc;
		tezzt_bytes_alloc += size;
	}

	return ret;
}
void free(void * p) {
	if (p) {
		(*freep)(p);
		++tezzt_count_dealloc;
	}
}

size_t strlen(const char* s) {
  ++tezzt_count_strlen;
	return strlenp(s);
}

static void __attribute__((constructor)) init() {
    mallocp        = (void *(*)(size_t)) dlsym (RTLD_NEXT, "malloc");
    freep          = (void (*)(void *)) dlsym(RTLD_NEXT, "free");
    callocp        = (void*(*)(size_t, size_t)) dlsym(RTLD_NEXT, "calloc");
    memalignp      = (void*(*)(size_t, size_t)) dlsym(RTLD_NEXT, "memalign");
    aligned_allocp = (void*(*)(size_t, size_t)) dlsym(RTLD_NEXT, "aligned_alloc");
    reallocp       = (void*(*)(void *, size_t)) dlsym(RTLD_NEXT, "realloc");
    
    strlenp        = (size_t(*)(const char *)) dlsym(RTLD_NEXT, "strlen");
}

#endif