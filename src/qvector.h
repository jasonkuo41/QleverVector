#ifndef QCVECTOR_H_INCLUDED
#define QCVECTOR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define qvec_version 1.1.0
//.1 = proto .2 = beta (e.g. 1.0.4.2, .2 = beta)

/** No downward compatibility with versions before 1.1.0 ***
************************************************************************************************************************
*                                 Qlever C Vector - A C++ Vector implementation for ANSI C                             *
*                                 ---- Written by jasonkuo41 ----- Version 1.1.0 PREV ----                             *
*               Disclaimer: PREV releases are expected to have minor bugs, report it on github if you found one!       *
*                                                                                                                      *
*                                  Github link: https://github.com/jasonkuo41/QleverVector                             *
************************************************************************************************************************
*                                                     CONFIGURATION                                                    *
************************************************************************************************************************
* > Warning: Changing any of the default value will result in error if a code requires QleverC Standard Lib            *
* > The definition here controls how the vector will behavior, it is best to read documents before changing settings   *
************************************************************************************************************************/

    #define ENABLE_NICK_NAMES 1 // enable nicknames like _db or typeof for easier use
    #define ENABLE_UNSAFE_USE 0 // enable use of "vector" instead of "qvector", can be hazard if you don't know the conflicts
    #define ENABLE_GLOBAL_NICKNAME_STRUCT 1
    #define ENABLE_GLOBAL_CONTROL_VECTOR 1 // enable use of returning vector type functions in qvector presets, only \
                                              disable if memory is an tight issue
    #define DIRECT_USE_OF_TYPE 1 // enable macros for quicker ref, close it if your not a big fan of macro expansions
    #define STRING_EXPAND_TO_FIT 1 // This determines if string push backs uses the same reserve method like others or not

// Following will not cause error if changed and user asking for std lib for Qlever C
    #define WARNING_NOT_USING_C99 1
    #define DISABLE_USE_IN_CPP 1
    #define DEBUG_BUILD 1 // This is only debug feature if qvector has glitch and need to be checked

// Following is not implemented whatsoever
    #define ENABLE_AUTO_INIT 1 // enable auto initialize if forgot to initialize a vector
    #define RUNTIME_SPACE_PRIORITY 0

/************************************************************************************************************************
 *                            Code Starts here, don't modify it if you don't know what you are doing                    *
 ************************************************************************************************************************/

#ifdef __cplusplus
    #if DISABLE_USE_IN_CPP > 0
        #error "Qvector / QleverC does not support C++, change DISABLE_USE_IN_CPP to 0 if you force to use it"
    #endif
#endif

#define GCC_COMPILER (defined(__GNUC__) && !defined(__clang__))
#if GCC_COMPILER
    #define USING_GCC_COMPILER 1
#endif

#ifdef __STDC_VERSION__
    #if __STDC_VERSION__ >= 199901L
        #include <stdbool.h>
    #else
        #define USE_OF_SELF_IMPLEMENTED_BOOL
    #endif
#else
    #define USE_OF_SELF_IMPLEMENTED_BOOL
#endif

#ifdef USE_OF_SELF_IMPLEMENTED_BOOL
    #define bool __int16
    #define true 1
    #define false 0
    #if WARNING_NOT_USING_C99 > 0 && USING_GCC_COMPILER > 0
        #warning "suggested to use std+=c99 (or above) for qvector"
    #endif
#endif // USE_OF_SELF_IMPLEMENTED_BOOL

#if ENABLE_NICK_NAMES > 0
    #define _double _db
    #define _vec vec
#endif

#if ENABLE_UNSAFE_USE > 0
    typedef struct qvector vector;
#endif // ENABLE_UNSAFE_USE

#define CAP_GROWTH (a->capacity * set_qvec_growth.times + set_qvec_growth.add)

#if DIRECT_USE_OF_TYPE > 0

    #define qv_get(type,qvector,location) *(type*)getIrr((qvector),(location))
    #define qv_push_back(qvector,element,type) do {\
                type hold = (element); \
                push_backAny ((qvector),&hold);\
            } while (0)
    #define qv_push_back_element(qvector,element) push_backAny ((qvector),&(element))

    #define _newVector(type) newVector(sizeof(type))
    #if ENABLE_GLOBAL_CONTROL_VECTOR > 0
        #define _newLocalVector(type) newLocalVector(sizeof(type))
    #endif

    #define _setMultiVec(qvector,type) setMultiVec(&(qvector),sizeof(type))

#endif // DIRECT_USE_OF_TYPE

#if DEBUG_BUILD > 0
    FILE *output;
#endif // DEBUG_BUILD

typedef struct qvector qvector;

typedef struct {
    unsigned int pow;
    size_t times;
    size_t add;
} qvec_cap_growth_algro;

qvec_cap_growth_algro set_qvec_growth = {1,2,1};

struct qvector {
    size_t *irr;
    size_t typesize;
    size_t size;
    size_t capacity;
    size_t glb_loc;
    short isInit;
};

struct vecint {
    int (*get) (qvector a, size_t i);
    bool (*push_back) (qvector *a, size_t i);
    bool (*insert) (qvector *a, size_t pos, void *arr ,size_t len);
};

struct vecchar {
    char (*get) (qvector a, size_t i);
    bool (*push_back) (qvector *a, char i);
    bool (*insert) (qvector *a, size_t pos, void *arr ,size_t len);
};

struct vecdouble {
    double (*get) (qvector a, size_t i);
    bool (*push_back) (qvector *a, double i);
    bool (*insert) (qvector *a, size_t pos, void *arr ,size_t len);
};

struct vecstring {
    void (*cat) (qvector a, char i[]);
    void (*toChar) (qvector a, char i[]);
    bool (*add) (qvector *a, char i[],size_t len);
    bool (*push_back) (qvector *a, char i[],size_t len);
    bool (*insert) (qvector *a, size_t pos, void *arr ,size_t len);
    void (*print) (qvector a);
};

struct qvecref {
    struct vecint _int;
    struct vecchar _char;
    struct vecstring _string;
    struct vecdouble _double;
    qvector (*get) (qvector a, size_t i);
    void (*getAny) (qvector a, void *b, size_t i);
    bool (*push_back) (qvector *a, qvector i);

    bool (*resize) (qvector *a, size_t i);
    bool (*pop_back) (qvector *a);
    bool (*push_backAny) (qvector *a, void *i);
    bool (*pop_front) (qvector *a);
    void (*erase) (qvector *a, size_t wstart, size_t wend);
    bool (*empty) (qvector a);
    void* (*begin) (qvector a);
    void* (*end) (qvector a);
    bool (*clear)(qvector *a);
    bool (*copy) (qvector *a, qvector b);
    bool (*insertIrr) (qvector *a, size_t pos, void *start, void *ends);
    bool (*insert) (qvector *a, size_t pos, void *arr ,size_t len);
};

// Control global variable of quick ref.

struct qvecref _vec;
struct vecint _int;
struct vecchar _char;
struct vecdouble _double;
struct vecstring _string;
struct vecstring _String;

//////////////////////////////////////////////

int getInt (qvector a, size_t i);
char getChar (qvector a, size_t i);
double getDouble (qvector a, size_t i);
void getAny (qvector a, void *b, size_t i);
qvector vget (qvector a, size_t i);

void toChar (qvector a, char i[]);
void printString (qvector a);

bool push_backInt (qvector *a, size_t i);
bool push_backChar (qvector *a, char i);
bool push_backString (qvector *a, char i[],size_t len);
bool push_backDouble (qvector *a, double i);
bool push_backVec (qvector *a, qvector i);
bool push_backAny (qvector *a, void *i);

bool insertAnyIrr (qvector *a, size_t pos, void *start, void *ends);
bool insertAny (qvector *a, size_t pos, void *arr ,size_t len);

bool reserveVec (qvector *a, size_t i);
bool pop_backVec (qvector *a);
bool pop_frontVec (qvector *a);
void eraseVec (qvector *a, size_t wstart, size_t wend);
bool emptyVec (qvector a);
void *vecStart (qvector a);
void *vecEnd (qvector a);
void destroyVec (qvector a);
bool clearVec(qvector *a);

//qvector newVector (int type);

bool initNewVector(qvector *,int);
qvector newVector (int type);
qvector newLocVec (int type);
void check_vector_get_init ();

//////////// Await to process (Abandon?) //////////////

size_t oldfindVec (qvector a, size_t i, int type){
    size_t n;
    for (n =0;n < a.size ; n++)
        if (getInt(a,n) == i)
            return n+1;
    return a.size;
}

size_t oldfindVec_of (qvector a, size_t i, size_t start , size_t ends){
    size_t n;
    for (n =start;n < ends ; n++)
        if ( getInt(a,n) == i)
            return n;
    return a.size;
}

// New ones

void* findVec (void* tar_start, void* tar_end, void* comp, int type){
    size_t n;
    for (n = 0; n < tar_end - (type + tar_start) ; n+= type)
        if (!memcmp(tar_start + n, comp, type))
            return tar_start + n;
    return tar_end;
}

void* findVec_first_of (void* tar_start, void* tar_end, void* comp_start, void* comp_end){
    size_t n, nsize = (int)(tar_end - (tar_start + (comp_start - comp_end)));
    if ((tar_end-tar_start)>(comp_end-comp_start)){
        for (n = 0; n <= nsize; n++)
            if (!memcmp(tar_start + n, comp_start, comp_end - comp_start + 1))
                //fprintf(output,"\nget %d %d %d %d\n",comp_end - comp_start, tar_end - tar_start,*(int*)comp_end,*(int*)comp_start);
                return tar_start + n;
        return tar_end;
    } else return 0;
}

///////////////////////////////////////////////////////

#if ENABLE_GLOBAL_CONTROL_VECTOR > 0
    struct global_vec {
        long long localflag;
        qvector loc; // A vector for global use
        qvector loc_pos;
        qvector glb;
    };
    struct global_vec qvec_glb = {0};

    #define GLOBEL_VEC_AMOUNT 3

    #define initglbVector(vec)\
        do{\
            vec.irr = malloc (sizeof(size_t));\
            vec.typesize = sizeof(size_t);\
            vec.capacity = 0;\
            vec.size = 0;\
            vec.isInit = 1;\
            if (ENABLE_GLOBAL_CONTROL_VECTOR)\
                push_backInt(&qvec_glb.glb,(size_t)vec.irr);\
            if (DEBUG_BUILD)\
                fprintf(output,"Global Control Vec registered: %d at %#010x\n",qvec_glb.glb.size-1,vec.irr);\
        }while(0);

    #define check_glb_vec_init()\
        do{\
            if (qvec_glb.glb.isInit == 0){\
                if (DEBUG_BUILD)\
                    output = fopen("QVEC_DEBUG_REPORT.txt","w");\
                initglbVector (qvec_glb.glb);\
                initglbVector (qvec_glb.loc);\
                initglbVector (qvec_glb.loc_pos);\
                qvec_glb.localflag = 0;\
            }\
        }while(0);

#endif


#define GET_FUNC (a.irr + i * a.typesize/4)

// Standard get function of v1.1.0 and above

//#define getIrr(a,i) (a.irr + i * a.typesize/4)

size_t* getIrr (qvector a, size_t i){
    size_t* hold = GET_FUNC;
    if (a.isInit == 2)
        destroyVec(a);
    if (i < a.size)
        return hold;
    else
        return 0;
}

qvector vget (qvector a, size_t i){
    return *(qvector*)(getIrr (a,i));
}

// Old but still somewhat use-able get types

int getInt (qvector a, size_t i){
    return *(getIrr (a,i));
}

char getChar (qvector a, size_t i){
    return *(getIrr (a,i));
}

double getDouble (qvector a, size_t i){
    return *(getIrr (a,i));
}

void getAny (qvector a, void *b, size_t i){
    memcpy(b, GET_FUNC, a.typesize);
}

#undef GET_FUNC

bool copyVec (qvector *a, qvector b){
    if(a->isInit){
        size_t* hold = malloc (b.capacity * b.typesize);
        if (!hold)
            return 0;
        else{
            free(a->irr);
            a->irr = hold;
            #if ENABLE_GLOBAL_CONTROL_VECTOR > 0
                if (*(size_t*)getIrr(qvec_glb.glb,a->glb_loc) != (size_t)a->irr)
                    *(size_t*)getIrr(qvec_glb.glb,a->glb_loc) = (size_t)a->irr;
            #endif
        }
    } else {
        *a = newVector(b.typesize);
        if (b.capacity > 0)
            if(!(reserveVec(a,b.capacity)))
                return 0;
    }
    a->size = b.size;
    memcpy(a->irr, b.irr, b.typesize * b.size);
    return 1;
}

void toChar (qvector a, char i[]){
    size_t k;
    for (k = 0; k < a.size ; k++)
        i[k] = getChar (a,k);
}

void printString (qvector a){
    size_t k;
    for (k = 0; k < a.size ; k++)
        printf("%c",getChar(a,k));
}

bool push_backAny (qvector *a, void *i){
    if (a->size +1 > a->capacity) {
        int *trypush = realloc (a->irr, a->typesize * CAP_GROWTH);
        if (!trypush)
            return 0;
        else
            a->irr = trypush;
            ++ a->size;
        #if ENABLE_GLOBAL_CONTROL_VECTOR > 0
            //printf("S \t%d \n\t%d\n \t%d\n",*(size_t*)getIrr(qvec_glb.glb,a->glb_loc),trypush,a->glb_loc);
            //if (*(size_t*)getIrr(qvec_glb.glb,a->glb_loc) != (size_t)trypush)
                *(size_t*)getIrr(qvec_glb.glb,a->glb_loc) = (size_t)trypush;
        #endif
        a->capacity = a->capacity * set_qvec_growth.times + set_qvec_growth.add ;
    } else
        ++ a->size;
    memcpy((a->irr + (a->size -1)*a->typesize/4), i, a->typesize);
    return 1;
}

bool push_backVec (qvector *a, qvector i){
    qvector hold = newVector (i.typesize);
    copyVec(&hold,i);
    return push_backAny (a, &hold);
}

bool push_backInt (qvector *a, size_t i){
    return push_backAny (a, &i);
}

bool push_backChar (qvector *a, char i){
    int b = i;
    #if DEBUG_BUILD > 0
        push_backAny (a, &b);
        fprintf(output,"\n From %d ,%c at %#010x Size: %d Cap: %d Pushed: %c  which %c, Realloc %d",a->irr,*(a->irr),a->irr + (a->size -1),a->size,a->capacity,*(a->irr + (a->size -1)), i,(a->size +1));
    #else
        return push_backAny (a, &b);
    #endif

}

bool push_backDouble (qvector *a, double i){
    return push_backAny (a, &i);
}

bool push_backString (qvector *a, char i[],size_t len){
    size_t k,flag = 0;
    if (a->size > 0 && getChar(*a,a->size-1) == '\0')
        pop_backVec(a);
    if (a->size + len > a->capacity) {
        #if STRING_EXPAND_TO_FIT > 0
            int *trypush = realloc (a->irr, a->typesize * (a->size +len));
        #else
            while (a->size + len > a->capacity)
                int *trypush = realloc (a->irr, a->typesize * CAP_GROWTH);
        #endif
        if (!trypush)
            return 0;
        else
            a->irr = trypush;
        #if ENABLE_GLOBAL_CONTROL_VECTOR > 0
        if (*(size_t*)getIrr(qvec_glb.glb,a->glb_loc) != (size_t)trypush)
            *(size_t*)getIrr(qvec_glb.glb,a->glb_loc) = (size_t)trypush;
        #endif
        a->capacity += len;
    }
    for (k = 0; k < len;k++)
        flag += !(push_backChar(a,i[k]));
    flag += !(push_backChar(a,'\0'));
    return flag;
}

bool insertAnyIrr (qvector *a, size_t pos, void *start, void *ends){
    return insertAny (a,pos,start,(ends-start+1)/a->typesize);
}

bool insertAny (qvector *a, size_t pos, void *arr ,size_t len){
    size_t k , m = 0;
    while ((len + a->size) > a->capacity)
        if (!(reserveVec (a, CAP_GROWTH)))
            return 0;
    memcpy(a->irr + pos + len, a->irr + pos, a->typesize * (a->size - pos + 1));
    memcpy(a->irr + pos, arr , a->typesize * len);
    a->size += len;
    return 1;
}

///////////////////////////////////////////////////////

bool pop_backVec (qvector *a){
    if (a->size <= 0)
        return 0;
    a->size --;
    return 1;
}

bool pop_frontVec (qvector *a){
    if (a->size <=0)
        return 0;
    else if (a->size > 1)
        memcpy(a->irr, a->irr + 1, a->typesize * (a->size-1));
    a->size --;
    return 1;
}

bool reserveVec (qvector *a, size_t i){
    if (i > a->capacity){
        int *trypush = realloc (a->irr,a->typesize * (a->capacity + i));
        if (!trypush)
            return 0;
        #if ENABLE_GLOBAL_CONTROL_VECTOR > 0
            if (*(size_t*)getIrr(qvec_glb.glb,a->glb_loc) != (size_t)trypush)
                *(size_t*)getIrr(qvec_glb.glb,a->glb_loc) = (size_t)trypush;
        #endif
        a->irr = trypush;
        a->capacity = i;
    } else if (i < a->capacity){
        int *trypush = realloc (a->irr,a->typesize * i +1);
        if (!trypush)
            return 0;
        #if ENABLE_GLOBAL_CONTROL_VECTOR > 0
            if (*(size_t*)getIrr(qvec_glb.glb,a->glb_loc) != (size_t)trypush)
                *(size_t*)getIrr(qvec_glb.glb,a->glb_loc) = (size_t)trypush;
        #endif
        a->irr = trypush;
        a->capacity = i;
        a->size = i;
    }
    return 1;
}

bool resizeVec (qvector *a, size_t i){
    if (i > a->capacity){
        int *trypush = realloc (a->irr,a->typesize * (a->capacity + i));
        if (!trypush)
            return 0;
        #if ENABLE_GLOBAL_CONTROL_VECTOR > 0
            if (*(size_t*)getIrr(qvec_glb.glb,a->glb_loc) != (size_t)trypush)
                *(size_t*)getIrr(qvec_glb.glb,a->glb_loc) = (size_t)trypush;
        #endif
        a->irr = trypush;
        a->capacity = i;
        a->size = i;
    } else if (i < a->capacity){
        int *trypush = realloc (a->irr,a->typesize * i +1);
        if (!trypush)
            return 0;
        #if ENABLE_GLOBAL_CONTROL_VECTOR > 0
            if (*(size_t*)getIrr(qvec_glb.glb,a->glb_loc) != (size_t)trypush)
                *(size_t*)getIrr(qvec_glb.glb,a->glb_loc) = (size_t)trypush;
        #endif
        a->irr = trypush;
        a->capacity = i;
        a->size = i;
    }
    return 1;
}

void eraseVec (qvector *a, size_t wstart, size_t wend){
    memcpy(a->irr + wstart, a->irr + wend + 1, a->typesize * (a->size - wend));
    a->size -= (wend - wstart +1) ;
}

bool emptyVec (qvector a){
    if (a.size) return 0;
    else return 1;
}

void *vecStart (qvector a){
    return a.irr;
}

void *vecEnd (qvector a){
    return a.irr + a.size;
}

void destroyVec (qvector a){
    free (a.irr);
    #if ENABLE_GLOBAL_CONTROL_VECTOR > 0
        #if DEBUG_BUILD > 0
            fprintf(output,"\tDestroy (Manual) %d at %#010x\n",a.glb_loc,a.irr);
        #endif
    eraseVec(&qvec_glb.glb,a.glb_loc,a.glb_loc);

    size_t n,m;
    for (n = 0; n < qvec_glb.loc.size; n++)
        if (getInt(qvec_glb.loc,n) == a.glb_loc){
            fprintf(output,"\t\tRemove Local Register %d at %#010x\n",n,getInt(qvec_glb.loc,n));
            eraseVec(&qvec_glb.loc,n,n);
            for (m = 0; m < qvec_glb.loc.size; m++)
                if (getInt(qvec_glb.loc,m)>a.glb_loc)
                    *(size_t*)getIrr(qvec_glb.loc,m) -= 1;
            for (m = 0; m < qvec_glb.loc_pos.size; m++){
                if (getInt(qvec_glb.loc_pos,m) > n){
                    *(size_t*)getIrr(qvec_glb.loc_pos,m) -= 1;
                    fprintf(output,"\t\tRemove Local Position %d at %#010x",m,getInt(qvec_glb.loc_pos,m));
                }
            }
            break;
        }
    #endif
}

bool clearVec (qvector *a){
    return reserveVec (a, 0);
}

bool setMultiVec (qvector *a,int type){
    qvector hold = newVector (type);
    push_backVec(a,hold);
    destroyVec (hold);
}

bool initNewVector (qvector *vec, int type){
    #if ENABLE_GLOBAL_NICKNAME_STRUCT > 0
        check_vector_get_init ();
    #endif // ENABLE_GLOBAL_CONTROL_VECTOR
    if (type % 4 != 0)
        type += 4 - (type % 4);
    vec->irr = malloc (type);
    vec->typesize = type;
    vec->capacity = 0;
    vec->size = 0;
    vec->isInit = 1;
    #if ENABLE_GLOBAL_CONTROL_VECTOR > 0
        check_glb_vec_init();
        push_backInt(&qvec_glb.glb,(size_t)vec->irr);
        vec->glb_loc = qvec_glb.glb.size - 1;
    #endif
    #if DEBUG_BUILD > 0
        fprintf(output,"Created %d at %#010x\n",qvec_glb.glb.size-1,vec->irr);
    #endif
    if (vec->irr) return 1;
    else return 0;
}

qvector newGlobalVector (int type){
    qvector temp;
    initNewVector (&temp,type);
    return temp;
}


qvector newVector (int type){
    #if ENABLE_GLOBAL_CONTROL_VECTOR > 0
    if (qvec_glb.localflag)
        return newLocVec(type);
    else {
    #endif
        qvector temp;
        initNewVector (&temp,type);
        return temp;
    #if ENABLE_GLOBAL_CONTROL_VECTOR > 0
    }
    #endif
}

qvector newString (){
    qvector temp = newVector (sizeof(char));
    return temp;
}



#if ENABLE_GLOBAL_NICKNAME_STRUCT > 0

void check_vector_get_init (){
    if (!_int.get)
        _int.get = getInt;
        _int.push_back = push_backInt;
        _int.insert = insertAny;

        _char.get = getChar;
        _char.push_back = push_backChar;
        _char.insert = insertAny;

        _string.cat = toChar;
        _string.toChar = toChar;
        _string.push_back = push_backString;
        _string.add = push_backString;
        _string.print = printString;

        _double.get = getDouble;
        _double.push_back = push_backDouble;
        _double.insert = insertAny;

        _vec._int.get = getInt;
        _vec._int.push_back = push_backInt;
        _vec._int.insert = insertAny;

        _vec._char.get = getChar;
        _vec._char.push_back = push_backChar;
        _vec._char.insert = insertAny;

        _vec._string.cat = toChar;
        _vec._string.toChar = toChar;
        _vec._string.push_back = push_backString;
        _vec._string.add = push_backString;
        _vec._string.print = printString;

        _vec._double.get = getDouble;
        _vec._double.push_back = push_backDouble;
        _vec._double.insert = insertAny;

        _vec.get = vget;
        _vec.getAny = getAny;
        _vec.push_back = push_backVec;
        _vec.push_backAny = push_backAny;
        _vec.resize = reserveVec;
        _vec.pop_back = pop_backVec;
        _vec.pop_front = pop_frontVec;
        _vec.erase = eraseVec;
        _vec.empty = emptyVec;
        _vec.begin = *vecStart;
        _vec.end = *vecEnd;
        _vec.clear = clearVec;
        _vec.copy = copyVec;
        _vec.insert = insertAny;
        _vec.insertIrr = insertAnyIrr;
}

#endif

// LOCAL MANAGEMENT

#if ENABLE_GLOBAL_CONTROL_VECTOR > 0

void newLocal(){
    check_glb_vec_init();
    bool hold = 1;
    if (qvec_glb.loc_pos.size > 0)
        hold = ((qvec_glb.loc.size - 1)!= getInt(qvec_glb.loc_pos,qvec_glb.loc_pos.size-1));
    if (qvec_glb.loc.size > 0 && hold){
        push_backInt(&qvec_glb.loc_pos,qvec_glb.loc.size - 1);
        ++qvec_glb.localflag;
    } else if (qvec_glb.loc.size == 0){
        qvec_glb.localflag = 1;
    }
}

void destroyLocal(){
    check_glb_vec_init();
    size_t n, k;
    if (qvec_glb.loc_pos.size > 0 && qvec_glb.loc.size > 0){
        for (n = qvec_glb.loc.size - 1; n > getInt(qvec_glb.loc_pos,qvec_glb.loc_pos.size - 1); n--){
            k = getInt(qvec_glb.loc,n);
            #if DEBUG_BUILD > 0
                fprintf(output,"Freed Local: %d at %#010x %d (A)\n",k,getInt(qvec_glb.glb,k),n);
            #endif
            free((size_t*)getInt(qvec_glb.glb,k));
            eraseVec(&qvec_glb.glb,k,k);
            pop_backVec (&qvec_glb.loc);
        }
        #if DEBUG_BUILD > 0
            fprintf(output,"\t\tLocal Position SIZE%d\n",qvec_glb.loc_pos.size);
        #endif // DEBUG_BUILD
        pop_backVec(&qvec_glb.loc_pos);
        --qvec_glb.localflag;
    }
    else if (qvec_glb.loc.size > 0){
        for (n = qvec_glb.loc.size; n > 0 ; n--){
            k = getInt(qvec_glb.loc,n-1); // n -1 because n will break if size_t decrease to 0
            #if DEBUG_BUILD > 0
                fprintf(output,"Freed Local: %d at %#010x (B)\n",k,getInt(qvec_glb.glb,k));
            #endif
            free((size_t*)getInt(qvec_glb.glb,k));
            eraseVec(&qvec_glb.glb,k,k);
            pop_backVec (&qvec_glb.loc);
        }
        pop_backVec(&qvec_glb.loc_pos);
        --qvec_glb.localflag;
        #if DEBUG_BUILD > 0
            fprintf(output,"\t\tLocal Position SIZE%d\n",qvec_glb.loc_pos.size);
        #endif
    }
    // Bug caused here
    if (qvec_glb.localflag == 0){
        clearVec(&qvec_glb.loc);
        clearVec(&qvec_glb.loc_pos);
    }
}

void destroyAllLocal() {
    size_t n,k;
    check_glb_vec_init();
    for (n = qvec_glb.loc.size; n > 0 ; n--){
        k = getInt(qvec_glb.loc,n-1); // n -1 because n will break if size_t decrease to 0
        #if DEBUG_BUILD > 0
            fprintf(output,"Freed All Local: %d at %#010x\n",k,getInt(qvec_glb.glb,k));
        #endif
        free((size_t*)getInt(qvec_glb.glb,k));
        eraseVec(&qvec_glb.glb,k,k);
        pop_backVec (&qvec_glb.loc);
    }
    qvec_glb.localflag = 0;
    clearVec(&qvec_glb.loc);
    clearVec(&qvec_glb.loc_pos);
}

void destroyAll() {
    check_glb_vec_init();
    size_t chk = qvec_glb.glb.size;
    #if DEBUG_BUILD > 0
        fprintf(output,"#Destroy All");
    #endif
    if (chk > 1){
        size_t n;
        for (n = qvec_glb.glb.size - 1 ; n >= GLOBEL_VEC_AMOUNT  ; n--){
            free((int*)getInt(qvec_glb.glb,n));
            #if DEBUG_BUILD > 0
                fprintf(output,"Destroy Global %d at %d\n",n,getInt(qvec_glb.glb,n));
            #endif
            pop_backVec (&qvec_glb.glb);
        }
        free(qvec_glb.loc.irr);
        free(qvec_glb.loc_pos.irr);
        free(qvec_glb.glb.irr);
    } else if (chk > 0)
        free(qvec_glb.glb.irr);
}

void assignLocal(qvector a){
    check_glb_vec_init();
    push_backInt(&qvec_glb.loc,a.glb_loc);
}

#define newLocalVector newLocVector
#define newLocVector newLocVec

qvector newLocalVector (int type){
    if (qvec_glb.localflag == 0)
        qvec_glb.localflag = 1;
    qvector temp;
    initNewVector (&temp,type);
    assignLocal(temp);
    return temp;
}

#endif // ENABLE_GLOBAL_CONTROL_VECTOR

/******** UNDEF SO PPL CANT USEIT *********/
#undef CAP_GROWTH

#endif // CVECTOR_H_INCLUDED
