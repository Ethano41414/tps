/*=================================================================*/
/*  Warning:                                                       */
/*       this module only works with pointers dynamic allocations  */
/*=================================================================*/
#ifndef ETHANO_STR_MODULE
#define ETHANO_STR_MODULE
#include <stdio.h>
#include <stdlib.h>

#define INF (-1ULL)

extern unsigned char ETHANO_STRTYPE;

typedef unsigned char uc;
typedef long long ll;
typedef unsigned long ul;
typedef unsigned long long ull;

// object definitions
typedef struct {
    unsigned char type;
    char *d;
    char *tmp;
} str;

typedef enum {
    TYPE_CHAR,
    TYPE_CSTR,
    TYPE_STR
} argtype;

typedef union {
    char c;
    const char *s;
    const str *str;
} argvalue;

typedef struct {
    argtype type;
    argvalue value;
} arg;

extern str STR;

// char * funcs
ull basicstrlen(const char *__s);

char *basicstrsegment(const char *__s,ull st, ull ed);

int basicstreq(const char *__s1,const char *__s2);

char *basicstrconcat(const char *__s1,const char *__s2);

ull basicstrindexc(char *text, char txt);

ull basicstrindex(char *text, char *txt);

int basicstrin(char *text, char *txt);

void basicstrcp(char *__t,char *__s);

void basicstrsegmenti(char *__t, char *__s, ull st, ull ed);

ull basicstrcount(char *self, const char *s);

// str funcs
str *Str_charptostr(char *txt);
str *Str_chartostr(char c);
str *Str_strtostr(str *self);
#define Str(s) _Generic((s), \
    int: Str_chartostr, \
    char: Str_chartostr, \
    char *: Str_charptostr, \
    const char *: Str_charptostr, \
    str *: Str_strtostr, \
    const str *: Str_strtostr \
)(s)

//Str_int/uint/float/ufloat/lfloat/llfloat/ulfloat/ullfloat/l/ll/s/ss/sfloat/ssfloat/usfloat/ussfloat/double/udouble/ldouble/lldouble/uldouble/ulldouble/tostr

//length
ull strlength(str *txt);
ull strlengthm(str *txt);
ull strlengtha(str *txt);

void strdel(str *self);

// return the index if presents, overwise return 0xFFFFFFFFFFFFFFFF
ull strindexchar(const str *self, const char c);
ull strindexcharp(const str *self, const char *s);
ull strindexstr(const str *self, const str *s);

// return the count of occurence of char char* str* text, overwise return 0xFFFFFFFFFFFFFFFF
ull strcountchar(const str *self, const char c);
ull strcountcharp(const str *self, const char *s);
ull strcountstr(const str *self, const str *s);

//text representations
const char *strrepr(const str *text);
const char *str__repr__(str *text);


// cut text part
void strselftruncate(str *self, ull st, ull ed);
str *strsegment(str *self, ull st, ull ed);

//take a char from
char *strgetletterpointer(str *self, ull index);
char strget(str *self, ull index);

//concatenation
str *strconcatstrstr(str *s1, str *s2);


//equality
int streq_cc(char s1, char s2);
int streq_ccp(char s1, char *s2);
int streq_cstr(char s1, str *s2);
int streq_cpc(char *s1, char s2);
int streq_cpcp(char *s1, char *s2);
int streq_cpstr(char *s1, str *s2);
int streq_strc(str *s1, char s2);
int streq_strcp(str *s1, char *s2);
int streq_strstr(str *s1, str *s2);


/*use Str(x) to copy char or char* to a str*/
str *strcp(str *self);


#define strcount(self, s) _Generic((s), \
    int: strcountchar, \
    char: strcountchar, \
    char *: strcountcharp, \
    const char *: strcountcharp, \
    str *: strcountstr, \
    const str *: strcountstr \
)(self, s)

#define strindex(self, s) _Generic((s), \
    int: strindexchar, \
    char: strindexchar, \
    char *: strindexcharp, \
    const char *: strindexcharp, \
    str *: strindexstr, \
    const str *: strindexstr \
)(self, s)

#define streq(s1, s2) _Generic((s1), \
    int: _Generic((s2),int: streq_cc,char: streq_cc,char *: streq_ccp,const char *: streq_ccp,str *: streq_cstr,const str *: streq_cstr \
    ), \
    char: _Generic((s2),int: streq_cc,char: streq_cc,char *: streq_ccp,const char *: streq_ccp,str *: streq_cstr,const str *: streq_cstr \
    ), \
    char *: _Generic((s2), int: streq_cpc,char: streq_cpc,char *: streq_cpcp,const char *: streq_cpcp,str *: streq_cpstr,const str *: streq_cpstr \
    ), \
    const char *: _Generic((s2), int: streq_cpc,char: streq_cpc,char *: streq_cpcp,const char *: streq_cpcp,str *: streq_cpstr,const str *: streq_cpstr \
    ), \
    str *: _Generic((s2), int: streq_strc,char: streq_strc,char *: streq_strcp,const char *: streq_strcp,str *: streq_strstr,const str *: streq_strstr \
    ), \
    const str *: _Generic((s2), int: streq_strc,char: streq_strc,char *: streq_strcp,const char *: streq_strcp,str *: streq_strstr,const str *: streq_strstr \
    ) \
)(s1, s2)



#endif



