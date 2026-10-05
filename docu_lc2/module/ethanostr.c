/*=================================================================*/
/*  Warning:                                                       */
/*       this module only works with pointers dynamic allocations  */
/*    and some  */
/*=================================================================*/

#include "ethanostr.h"

unsigned char ETHANO_STRTYPE=0xFD;
str STR;

// char * funcs
ull basicstrlen(const char *__s) {
    if (__s==NULL) return INF;
    ull r=0;
    while (*__s++)
        r++;
    return r;
}

char *basicstrsegment(const char *__s,ull st, ull ed) {
    if (st>ed||ed>basicstrlen(__s)) return NULL;
    char *strsgmitm=malloc(ed-st+1);
    if (!strsgmitm) return NULL;
    for (ull i=st;i<ed;i++)
        strsgmitm[i-st]=__s[i];
    strsgmitm[ed-st]='\0';
    return strsgmitm;
}

int basicstreq(const char *__s1,const char *__s2) {
    ull l=basicstrlen(__s1);
    if (l!=basicstrlen(__s2))
        return 0;
    for (ull i=0;i<l;i++)
        if (__s1[i]!=__s2[i])
            return 0;
    return 1;
}

char *basicstrconcat(const char *__s1,const char *__s2) {
    ull s1s=basicstrlen(__s1), s2s=basicstrlen(__s2);
    ull size=s1s+s2s+1;
    char *text=malloc(size);
    if (text==NULL) return NULL;
    for (ull i=0;i<size;i++)
        text[i]=(i<s1s)?__s1[i]:__s2[i-s1s];
    return text;
}

ull basicstrindexc(char *text, char txt) {
    for (ull i=0;text[i];i++) if (text[i]==txt) return i;
    return INF;
}
ull basicstrindex(char *text, char *txt) {
    ull size=basicstrlen(text), wordsize=basicstrlen(txt);
    ull i=0,j=0;
    if (wordsize>size) return INF;
    while (i<=size-wordsize) {
        j=0;
        while (j<wordsize && text[i+j]==txt[j])
            j++;
        if (j==wordsize) return i;
        i++;
    }
    return INF;
}
int basicstrin(char *text, char *txt) {
    ull size=basicstrlen(text), wordsize=basicstrlen(txt);
    ull i=0,j=0;
    if (wordsize>size) return 0;
    while (i<=size-wordsize) {
        j=0;
        while (j<wordsize && text[i+j]==txt[j])
            j++;
        if (j==wordsize) return 1;
        i++;
    }
    return 0;
}

void basicstrcp(char *__t, char *__s) {
    ull size=basicstrlen(__s);
    for (ull i=0;i<=size;i++) __t[i]=__s[i];
}
void basicstrsegmenti(char *__t, char *__s, ull st, ull ed) {
    if (st<=ed&&ed<=basicstrlen(__s)) {
        for (ull i=st;i<ed;i++)
            __t[i-st]=__s[i];
        __t[ed-st]='\0';
    }
}

ull basicstrcount(char *self, const char *s) {
    ull count=0, wordsize=basicstrlen(s);
    char *testword;
    if (wordsize!=0&&basicstrlen(self)>=wordsize) {
        ull effective_size=basicstrlen(self)-wordsize;
        for (ull i=0;i<=effective_size;i++) {
            testword=basicstrsegment(self,i,i+wordsize);
            count+=basicstreq(testword,s);
            free(testword);
        }
    }
    return count;
}

// str funcs
str *Str_charptostr(char *txt) {
    str *text=malloc(sizeof(str));
    if (text==NULL) return NULL;
    text->type=ETHANO_STRTYPE;
    ull len=basicstrlen(txt)+1;
    text->d=malloc(len);
    if (text->d==NULL) {free(text); return NULL;}
    text->tmp=malloc(1);
    if (text->tmp==NULL) {free(text->d); free(text); return NULL;}
    text->tmp[0]='\0';
    for (ull i=0;i<len;i++) text->d[i]=txt[i];
    return text;
}
str *Str_chartostr(char c) {
    char r[2]; r[0]=c ; r[1]='\0';
    return Str_charptostr(r);
}
str *Str_strtostr(str *self) {
    return self;
}


//Str_int/uint/float/ufloat/lfloat/llfloat/ulfloat/ullfloat/l/ll/s/ss/sfloat/ssfloat/usfloat/ussfloat/double/udouble/ldouble/lldouble/uldouble/ulldouble/tostr

//length
ull strlength(str *txt) {
    return basicstrlen(txt->d);
}
ull strlengthm(str *txt) {
    return basicstrlen(txt->d)+1;
}
ull strlengtha(str *txt) {
    return ((ull)sizeof(str))+basicstrlen(txt->d)+1;
}


void strdel(str *self) {
    if (!self) return;
    free(self->d);
    free(self->tmp);
    free(self);
}


// return the index if presents, overwise return 0xFFFFFFFFFFFFFFFF
//modifier plus tard to have right things and no allocs
ull strindexchar(const str *self, const char c) {
    for (ull i=0;self->d[i];i++) if (self->d[i]==c) return i;
    return INF;
}
ull strindexcharp(const str *self, const char *s) {
    char *testword;
    ull size=basicstrlen(self->d),wordsize=basicstrlen(s);
    if (wordsize!=0&&size>=wordsize) {
        ull effective_size=size-wordsize;
        for (ull i=0;i<=effective_size;i++) {
            testword=basicstrsegment(self->d,i,i+wordsize);
            if (basicstreq(testword,s)) {
                free(testword);
                return i;}
            free(testword);
        }
    }
    return INF;
}
ull strindexstr(const str *self, const str *s) {
    char *testword;
    ull size=basicstrlen(self->d),wordsize=basicstrlen(s->d);
    if (wordsize!=0&&size>=wordsize) {
        ull effective_size=size-wordsize;
        for (ull i=0;i<=effective_size;i++) {
            testword=basicstrsegment(self->d,i,i+wordsize);
            if (basicstreq(testword,s->d)) {
                free(testword);
                return i;}
            free(testword);
        }
    }
    return INF;
}

// return the count of occurence of char char* str* text, overwise return 0xFFFFFFFFFFFFFFFF
//modifier plus tard to have right things and no allocs
ull strcountchar(const str *self, const char c) {
    ull count=0;
    for (char *p=self->d;*p;p++) count+=(*p==c);
    return count;
}
ull strcountcharp(const str *self, const char *s) {
    ull count=0, wordsize=basicstrlen(s);
    char *testword;
    if (wordsize!=0&&basicstrlen(self->d)>=wordsize) {
        ull effective_size=basicstrlen(self->d)-wordsize;
        for (ull i=0;i<=effective_size;i++) {
            testword=basicstrsegment(self->d,i,i+wordsize);
            count+=basicstreq(testword,s);
            free(testword);
        }
    }
    return count;
}
ull strcountstr(const str *self, const str *s) {
    ull count=0, wordsize=basicstrlen(s->d);
    char *testword;
    if (wordsize!=0&&basicstrlen(self->d)>=wordsize) {
        ull effective_size=basicstrlen(self->d)-wordsize;
        for (ull i=0;i<=effective_size;i++) {
            testword=basicstrsegment(self->d,i,i+wordsize);
            count+=basicstreq(testword,s->d);
            free(testword);
        }
    }
    return count;
}

//text representations
const char *strrepr(const str *text) {
    return text->d;
}
const char *str__repr__(str *text) {
    if (text==NULL) return NULL;
    ull counts=strcountchar(text,'\n')+strcountchar(text,'\r')+strcountchar(text,'\t');
    ull len=basicstrlen(text->d)+1;
    char *p=realloc(text->tmp,len+counts+2);
    if (!p) return NULL;
    text->tmp=p;
    ull tmp=1;
    text->tmp[0]='"';
    for (ull i=0;i<len;i++) {
        switch (text->d[i]) {
        case '\t':  text->tmp[i+tmp]='\\'; tmp++; text->tmp[i+tmp]='t';  break;
        case '\r':  text->tmp[i+tmp]='\\'; tmp++; text->tmp[i+tmp]='r';  break;
        case '\n':  text->tmp[i+tmp]='\\'; tmp++; text->tmp[i+tmp]='n';  break;
        case '"':  text->tmp[i+tmp]='\\'; tmp++; text->tmp[i+tmp]='"';  break;
        default:  text->tmp[i+tmp]=text->d[i];  break;
        }
    }
    text->tmp[len+counts]='"';
    text->tmp[len+counts+1]='\0';
    return text->tmp;
}


// cut text part
void strselftruncate(str *self, ull st, ull ed) { //modify herself
    if (st>ed||ed>basicstrlen(self->d)) return;
    for (ull i=st;i<ed;i++) self->d[i-st]=self->d[i];
    self->d[ed-st]='\0';
    char *p=realloc(self->d,ed-st+1);
    if (p) self->d=p;
}
str *strsegment(str *self, ull st, ull ed) {
    if (self==NULL) return NULL;
    ull size=basicstrlen(self->d);
    if (st<=ed&&ed<=size) {
        char *text=basicstrsegment(self->d,st,ed);
        str *txt=Str(text);
        free(text);
        return txt;
    }
    return NULL;
}

//take a char from
//a changer plus tard pour verifier l'index et utiliser les négatifs
char *strgetletterpointer(str *self, ull index) {
    return self->d+index;
}
char strget(str *self, ull index) {
    return self->d[index];
}

//concatenation
str *strconcatstrstr(str *s1, str *s2) {
    char *text=basicstrconcat(s1->d,s2->d);
    if (text==NULL) return NULL;
    str *txt=Str(text);
    free(text);
    return txt;
}


//equality
int streq_cc(char s1, char s2) {
    return s1==s2;
}
int streq_ccp(char s1, char *s2) {
    if (s2==NULL) return 0;
    if (basicstrlen(s2)==1)
        return s1==s2[0];
    return 0;
}
int streq_cstr(char s1, str *s2) {
    if (s2==NULL) return 0;
    return streq_ccp(s1,s2->d);
}
int streq_cpc(char *s1, char s2) {
    if (s1==NULL) return 0;
    return streq_ccp(s2,s1);
}
int streq_cpcp(char *s1, char *s2) {
    if (s1==NULL&&s2==NULL) return 1;
    if (s1==NULL||s2==NULL) return 0;
    return basicstreq(s1,s2);
}
int streq_cpstr(char *s1, str *s2) {
    if (s1==NULL&&s2==NULL) return 1;
    if (s1==NULL||s2==NULL) return 0;
    return basicstreq(s1,s2->d);
}
int streq_strc(str *s1, char s2) {
    if (s1==NULL) return 0;
    return streq_ccp(s2,s1->d);
}
int streq_strcp(str *s1, char *s2) {
    if (s1==NULL&&s2==NULL) return 1;
    if (s1==NULL||s2==NULL) return 0;
    return basicstreq(s2,s1->d);
}
int streq_strstr(str *s1, str *s2) {
    if (s1==NULL&&s2==NULL) return 1;
    if (s1==NULL||s2==NULL) return 0;
    return basicstreq(s1->d,s2->d);
}


/*use Str(x) to copy char or char* to a str*/
str *strcp(str *self) {
    if (self==NULL) return NULL;
    str *o=Str(self->d);
    return o;
}


