#ifndef QCVECTOR_H_INCLUDED
#define QCVECTOR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

//

// CONFIGURATION
// Warning: Changing any of the default value will result in error if a code requires QuickC Standard Lib
// The definition here controls how the vector will behavior, it is best to read documents before changing settings //

    #define ENABLE_NICK_NAMES 1 // enable nicknames like _db or typeof for easier use
    #define ENABLE_UNSAFE_USE 0 // enable use of "vector" instead of "qvector", can be hazard if you don't know the conflicts
    #define ENABLE_GLOBAL_NICKNAME_STRUCT 1
    #define ENABLE_GLOBAL_CONTROL_VECTOR 1 // enable use of returning vector type functions in qvector presets, only disable if memory is an tight issue
    #define ENABLE_AUTO_INIT 1 // enable auto initialize if forgot to initialize a vector
    #define ENABLE_USE_OF_STRING 1

    #define WARNING_NOT_USING_C99 1 // changing this will not hurt QuickC Standard Lib, i.e. Change it at your desire
    #define DISABLE_USE_IN_CPP 1
    #define DEBUG_BUILD 0

    // AWAIT FOR IMPLEMENTATION
    // #define ENABLE_GLOBAL_QUICKREF 1 // enable use of global quick reference such as _int.push_back, disable if memory is an tight issue

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
    #if DISABLE_USE_IN_CPP > 0
        #error "Qvector / QuickC does not support C++, change DISABLE_USE_IN_CPP to 0 if you force to use it"
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
    #if WARNING_NOT_USING_C99 > 0
        //#warning "suggested to use std+=c99 (or above) for qvector"
    #endif
#endif // USE_OF_SELF_IMPLEMENTED_BOOL

#if ENABLE_NICK_NAMES > 0
    #define _double _db
    #define typeof sizeof
    #define _vec vec
#endif

#if ENABLE_UNSAFE_USE > 0
    typedef struct qvector vector;
#endif // ENABLE_UNSAFE_USE

typedef struct qvector qvector;

typedef enum {
    setInt = -1,
    setChar = -2,
    setString = -3,
    setDouble = -4,
    setVec = 0,
} vec_type;

vec_type _type;

struct qvector {
    int *irr;
    unsigned int typesize;
    vec_type type;
    int size;
    int capacity;
    short emptyVec;
    short isInit;
};

struct vecint {
    int (*get) (qvector a, int i);
    bool (*push_back) (qvector *a, int i);
    void (*insert) (qvector *a,int pos, int loc[] ,int len);
};

struct vecchar {
    char (*get) (qvector a, int i);
    bool (*push_back) (qvector *a, char i);
    void (*insert) (qvector *a,int pos, char loc[] ,int len);
};

struct vecdouble {
    double (*get) (qvector a, int i);
    bool (*push_back) (qvector *a, double i);
    void (*insert) (qvector *a,int pos, double loc[] ,int len);
};

struct vecstring {
    void (*cat) (qvector a, char i[]);
    void (*toChar) (qvector a, char i[]);
    bool (*add) (qvector *a, char i[],int len);
    bool (*push_back) (qvector *a, char i[],int len);
    void (*insert) (qvector *a,int pos, char loc[] ,int len);
    void (*print) (qvector a);
};

struct qvecref {
    struct vecint _int;
    struct vecchar _char;
    struct vecstring _string;
    struct vecdouble _double;
    qvector (*get) (qvector a, int i);
    void (*getAny) (qvector a, void *b, int i);
    bool (*push_back) (qvector *a, qvector i);

    bool (*resize) (qvector *a, int i);
    bool (*pop_back) (qvector *a);
    bool (*push_backAny) (qvector *a, void *i);
    bool (*pop_front) (qvector *a);
    void (*erase) (qvector *a, int wstart, int wend);
    short (*empty) (qvector a);
    void* (*begin) (qvector a);
    void* (*end) (qvector a);
    void (*clear)(qvector *a);
    void (*copy) (qvector *a, qvector b);
};

// Control global variable of quick ref.

struct qvecref _vec;
struct vecint _int;
struct vecchar _char;
struct vecdouble _double;
struct vecstring _string;
struct vecstring _String;

//////////////////////////////////////////////

int getInt (qvector a, int i);
char getChar (qvector a, int i);
double getDouble (qvector a, int i);
void getAny (qvector a, void *b, int i);
qvector vget (qvector a, int i);

void toChar (qvector a, char i[]);
void printString (qvector a);

bool push_backInt (qvector *a, int i);
bool push_backChar (qvector *a, char i);
bool push_backString (qvector *a, char i[],int len);
bool push_backDouble (qvector *a, double i);
bool push_backVec (qvector *a, qvector i);
bool push_backAny (qvector *a, void *i);

void insertInt (qvector *a,int pos, int loc[] ,int len);
void insertChar (qvector *a,int pos, char loc[] ,int len);
void insertDouble (qvector *a,int pos, double loc[] ,int len);

bool resizeVec (qvector *a, int i);
bool pop_backVec (qvector *a);
bool pop_frontVec (qvector *a);
void eraseVec (qvector *a, int wstart, int wend);
short emptyVec (qvector a);
void *vecStart (qvector a);
void *vecEnd (qvector a);
void destroyVec (qvector a);
void clearVec(qvector *a);

qvector newVector (int type);

qvector newLocVec (int type);
void check_vector_get_init ();

//////////// Await to process (Abandon?) //////////////

int findVec (qvector a, int i, int type){
    int n;
    for (n =0;n < a.size ; n++)
        if ( getInt(a,n) == i)
            return n+1;
    return a.size;
}

int findVec_of (qvector a, int i, int start , int ends){
    int n;
    for (n =start;n < ends ; n++){
        printf("Find %d | %d\n", i , getInt(a,n));
        if ( getInt(a,n) == i)
            return n;
    }
    return a.size;
}

///////////////////////////////////////////////////////

#if ENABLE_GLOBAL_CONTROL_VECTOR > 0
    struct global_vec {
        qvector loc; // A vector for global use
        qvector loc_pos;
        qvector glb;
    };
    struct global_vec qvec_glb;

void check_glb_vec_init(){
    if (qvec_glb.loc.isInit == 0)
        qvec_glb.loc = newVector(setInt);
    if (qvec_glb.loc_pos.isInit == 0)
        qvec_glb.loc_pos = newVector(setInt);
    if (qvec_glb.glb.isInit == 0)
         qvec_glb.glb = newVector(setInt);
}

#endif

int getInt (qvector a, int i){
    return *(a.irr + i*a.typesize/4);
}

int* getIrr (qvector a, int i){
    return (a.irr + i*a.typesize/4);
}


char getChar (qvector a, int i){
    return *(a.irr + i * a.typesize/4);
}

double getDouble (qvector a, int i){
    return *(a.irr + i * a.typesize/4);
}

void getAny (qvector a, void *b, int i){
    memcpy(b, a.irr + i * a.typesize/4, a.typesize);
}

qvector vget (qvector a, int i){
    qvector b = newVector(a.type);
    memcpy(&b, a.irr + i * a.typesize/4, a.typesize);
    return b;
}

bool copyVec (qvector *a, qvector b){
    // Check of a = b type ?
    bool retry;
    clearVec(a);
    retry = resizeVec(a,b.capacity);
    if (!retry){
        *a = newVector(a->type);
        retry = resizeVec(a,b.capacity);
    }
    if (!retry) return 0;
    int n;
    for (n = 0; n < b.size; n++)
        push_backAny(a,getIrr(b,n));
}

void toChar (qvector a, char i[]){
    int k;
    for (k = 0; k < a.size ; k++)
        i[k] = getChar (a,k);
}

void printString (qvector a){
    int k;
    for (k = 0; k < a.size ; k++)
        printf("%c",getChar(a,k));
}

bool push_backAny (qvector *a, void *i){
    if (a->size +1 > a->capacity) {
        int *trypush = realloc (a->irr, a->typesize * (a->size + 1));
        if (!trypush)
            return 0;
        else
            a->irr = trypush;
        a->capacity ++;
    }
    a->size ++;
    memcpy((a->irr + (a->size -1)*a->typesize/4), i, a->typesize);
    return 1;
}

bool push_backVec (qvector *a, qvector i){
    qvector hold = newVector(i.typesize);
    copyVec(&hold,i);
    return push_backAny (a, &hold);
}

bool push_backInt (qvector *a, int i){
    return push_backAny (a, &i);
}

bool push_backChar (qvector *a, char i){
    int b = i;
    #if DEBUG_BUILD > 0
        push_backAny (a, &b);
        printf("\n From %d ,%c At %d Size: %d Cap: %d Pushed: %c  which %c, Realloc %d",a->irr,*(a->irr),a->irr + (a->size -1),a->size,a->capacity,*(a->irr + (a->size -1)), i,(a->size +1));
    #else
        return push_backAny (a, &b);
    #endif

}

bool push_backDouble (qvector *a, double i){
    return push_backAny (a, &i);
}

bool push_backString (qvector *a, char i[],int len){
    int k,flag = 0;
    if (a->type == setString && a->size > 0 && getChar(*a,a->size-1) == '\0')
        pop_backVec(a);
    if (a->size + len > a->capacity) {
        int *trypush = realloc (a->irr, a->typesize * (a->size +len));
        if (!trypush)
            return 0;
        else
            a->irr = trypush;
        a->capacity += len;
    }
    for (k = 0; k < len;k++)
        flag += !(push_backChar(a,i[k]));
    if (a->type == setString)
        flag += !(push_backChar(a,'\0'));
    return flag;
}

void insertInt (qvector *a,int pos, int loc[] ,int len){
    int k , m = 0;
    if ((len + a->size) > a->capacity)
        resizeVec (a, (a-> size + len));
    a->size += len;
    for (k = a->size; k >= pos + len; k--)
        *(a->irr + k) = *(a->irr + k - len);
    for (k = pos; k < pos+len ; k++)
        *(a->irr + k) = loc [m++];
}

void insertChar (qvector *a,int pos, char loc[] ,int len){
    int k , m = 0;
    if ((len + a->size) > a->capacity)
        resizeVec (a, (a-> size + len));
    a->size += len;
    for (k = a->size; k >= pos + len; k--)
        *(a->irr + k) = *(a->irr + k - len);
    for (k = pos; k < pos+len ; k++)
        *(a->irr + k) = loc [m++];
}

void insertDouble (qvector *a,int pos, double loc[] ,int len){
    int k , m = 0;
    if ((len + a->size) > a->capacity)
        resizeVec (a, (a-> size + len));
    a->size += len;
    for (k = a->size; k >= pos + len; k--)
        *(a->irr + k) = *(a->irr + k - len);
    for (k = pos; k < pos+len ; k++)
        *(a->irr + k) = loc [m++];
}

///////////////////////////////////////////////////////

bool pop_backVec (qvector *a){
    if (a->size <0)
        return 0;
    a->size --;
    return 1;
}

bool pop_frontVec (qvector *a){
    if (a->size <0)
        return 0;
    a->size --;
    int n;
    for (n = 0; n < a->size ; n++)
        * (a->irr + n) = * (a->irr + n + 1);
}

bool resizeVec (qvector *a, int i){
    if (i > a->capacity){
        int *trypush = realloc (a->irr,a->typesize * (a->capacity + i));
        if (!trypush)
            return 0;
        else
            a->irr = trypush;
        a->capacity = i;
    } else if (i < a->capacity){
        int *trypush = realloc (a->irr,a->typesize * i +1);
        if (!trypush)
            return 0;
        else
            a->irr = trypush;
        a->capacity = i;
        a->size = i;
    }
    return 1;
}

void eraseVec (qvector *a, int wstart, int wend){
    int k;
    for (k = wstart; (k + wstart - wend +1) < a->size ; k++)
        *(a->irr + k) = *(a->irr + k + (wend - wstart +1));
    a->size -= (wend - wstart +1) ;
}

short emptyVec (qvector a){
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
}

void clearVec (qvector *a){
    resizeVec (a, 0);
}

bool initVector (qvector *vec, int type){
    #if ENABLE_GLOBAL_NICKNAME_STRUCT > 0
        check_vector_get_init ();
    #endif // ENABLE_GLOBAL_CONTROL_VECTOR
    vec->type = type;
    switch (type){
        case setInt:
            vec->irr = malloc (sizeof(int));
            vec->typesize = sizeof (int);
            break;
        case setString:
        case setChar:
            vec->irr = malloc (4);
            vec->typesize = 4;
            break;
        case setDouble:
            vec->irr = malloc (sizeof (double));
            vec->typesize = sizeof (double);
            break;
        case setVec:
            vec->irr = malloc (sizeof(qvector));
            vec->typesize = sizeof(qvector);
            break;
        default:
            vec->irr = malloc (type);
            vec->typesize = type;
            break;
    }
    vec->capacity = 0;
    vec->size = 0;
    vec->isInit = 1;
    #if ENABLE_GLOBAL_CONTROL_VECTOR > 0
        push_backInt(&qvec_glb.glb,(int)vec->irr);
    #endif
}

qvector newVector (int type){
    qvector temp;
    initVector (&temp,type);
    return temp;
}

#if ENABLE_GLOBAL_NICKNAME_STRUCT > 0

void check_vector_get_init (){
    if (!_int.get)
        _int.get = getInt;
        _int.push_back = push_backInt;
        _int.insert = insertInt;

        _char.get = getChar;
        _char.push_back = push_backChar;
        _char.insert = insertChar;

        _string.cat = toChar;
        _string.toChar = toChar;
        _string.push_back = push_backString;
        _string.add = push_backString;
        _string.print = printString;

        _double.get = getDouble;
        _double.push_back = push_backDouble;
        _double.insert = insertDouble;

        _vec._int.get = getInt;
        _vec._int.push_back = push_backInt;
        _vec._int.insert = insertInt;

        _vec._char.get = getChar;
        _vec._char.push_back = push_backChar;
        _vec._char.insert = insertChar;

        _vec._string.cat = toChar;
        _vec._string.toChar = toChar;
        _vec._string.push_back = push_backString;
        _vec._string.add = push_backString;
        _vec._string.print = printString;

        _vec._double.get = getDouble;
        _vec._double.push_back = push_backDouble;
        _vec._double.insert = insertDouble;

        _vec.get = vget;
        _vec.getAny = getAny;
        _vec.push_back = push_backVec;
        _vec.push_backAny = push_backAny;
        _vec.resize = resizeVec;
        _vec.pop_back = pop_backVec;
        _vec.pop_front = pop_frontVec;
        _vec.erase = eraseVec;
        _vec.empty = emptyVec;
        _vec.begin = *vecStart;
        _vec.end = *vecEnd;
        _vec.clear = clearVec;
        _vec.copy = copyVec;
}

#endif

// LOCAL MANAGEMENT

#if ENABLE_GLOBAL_CONTROL_VECTOR > 0

void newLocal(){
    // Builds a newLocal0
    check_glb_vec_init();
    if (qvec_glb.loc.size < 1 && qvec_glb.loc_pos.size < 1)
        push_backInt(&qvec_glb.loc_pos,0);
    else if ((qvec_glb.loc.size - 1)!= getInt(qvec_glb.loc_pos,qvec_glb.loc_pos.size-1) && qvec_glb.loc.size > 0)
        push_backInt(&qvec_glb.loc_pos,qvec_glb.loc.size - 1);
}

void destroyLocal(){
    int n, m;
    check_glb_vec_init();
    if (qvec_glb.loc.size > 0) {
        if (qvec_glb.loc_pos.size == 1){
            for (n = qvec_glb.loc.size - 1 ; n >= getInt(qvec_glb.loc_pos,0)  ; n--){
                free((int*) getInt(qvec_glb.loc,n));
                pop_backVec (&qvec_glb.loc);
            }
            pop_backVec(&qvec_glb.loc_pos);
        } else if (qvec_glb.loc_pos.size > 1){
            n = qvec_glb.loc.size - 1;
            m = getInt(qvec_glb.loc_pos,qvec_glb.loc_pos.size - 1);
            for (; n > m; n--){
                free((int*) getInt(qvec_glb.loc,n));
                pop_backVec (&qvec_glb.loc);
            }
            pop_backVec(&qvec_glb.loc_pos);
        }
    }
}

void destroyAllLocal() {
    int n;
    check_glb_vec_init();
    for (n = qvec_glb.loc.size - 1 ; n >= 0  ; n--){
        free((int*) getInt(qvec_glb.loc,n));
        pop_backVec (&qvec_glb.loc);
    }
}

void destroyAll() {
    int n;
    check_glb_vec_init();
    for (n = qvec_glb.loc.size - 1 ; n >= 0  ; n--){
        free((int*) getInt(qvec_glb.loc,n));
        pop_backVec (&qvec_glb.loc);
    }
}

void assignLocal(qvector a){
    check_glb_vec_init();
    push_backInt(&qvec_glb.loc,(int)a.irr);
    push_backInt(&qvec_glb.glb,(int)a.irr);
}

#define newLocalVector newLocVector
#define newLocVector newLocVec

qvector newLocalVector (int type){
    if (qvec_glb.loc_pos.size < 1)
        newLocal();
    qvector temp;
    initVector (&temp,type);
    assignLocal(temp);
    return temp;
}

#endif // ENABLE_GLOBAL_CONTROL_VECTOR

#ifndef QSTRING_H_INCLUDED
    #if ENABLE_USE_OF_STRING > 0
        qvector newString (){
            qvector temp;
            initVector (&temp,setString);
            return temp;
        }
    #endif // ENABLE_USE_OF_STRING
#endif // QSTRING_H_INCLUDED

#endif // CVECTOR_H_INCLUDED
