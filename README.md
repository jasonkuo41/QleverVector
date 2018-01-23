# Qlever C - qVector
Version &nbsp;| &nbsp; 1.1.0 &nbsp; **(PREV)**

One of the best implemenation of C++ Vector for ANSI C, easy to use,

- Extreme flexible : e.g. Multi-dimension arrays doesn't require a consistance type (the first row of an array can be int while the second can be char)
- As fast as C++ Vector, and much faster than it when optimization flag isn't used


_*qVector is part of the Qlever C Library Project allowing ANSI C to be written in a much cleaner and easier to use style_

## Simple Clean and Friendly
All the hard work has all been done in the header file, all you need to do is include it and it's ready to use.

It is as simple as the following code:

```C
    #include "qvector.h"
    int main(){
        qvector myvec = _newVector (int);
        _int.push_back (&a, 5);
        _vec.resize (&a, 4);
        qv_get (int,a,2) = 12;
        destroyAll();
    }
```
which is essentially perform same result as the following with C++ Vector:

```C++
    #include <vector>
    using namespace std;
    int main (){
        vector <int> myvec;
        myvec.push_back(5);
        myvec.resize(4);
        myvec [2] = 12; // It's more like myvec.at(2) = 12;
    }
```
In fact that C++ Vector is still much more tidey, this is as close you can get as close in C.

## Amazingly Fast

As for v1.1.0, test results show that qVectors is as fast as C++ Vector,  (except value assigning) and is much faster than C++ Vector when optimization (-O3) is not available.

![](https://i.imgur.com/GNzzrIK.png)

_Note that Pop is much faster due to a "false erasement" technique used in qVector, the data is not essentially erased but only flaged as "to-be-erased", for more info, check the full documentation of qVector_

## Example and Tutorial

### Initializing a qVector

A qVector must be initialized before any use. Using any qVector without initializing is considered as an undefined behavour.

Just like normal vectors, initialization is used to tell qVector what type of data type will be contained in the future.

The prototype of _newVector is alike this:
>
    _newVector (type);

Here's an example:
```C
    qvector myVec = _newVector (int);
    // C++ : vector<int> myVec; 
```

**_newVector** is an macro expansion of **newVector**, which the above code is actually equivalent to ```newVector(sizeof(int))```

The bellow are also initializers that can used to initialize an qVector:
 - ```_newVector```, macro expansion of newVector
 - ```_newLocalVector```, macro expansion of newLocalVector
 - ```_newGlobalVector```, macro expansion of newGlobalVector

However, we simply suggest you use _newVector, since everything is automatically configured using this initializer.

We will mention how local vectors and global vectors are and what they can achieve later.

### Value modification

qVector provides the following method to modify values:
 - push_back, pop_back and pop_front
 - value assigning
 - insert and erase

#### Push_back family
Push_backs are generally performed by using ```qv_push_back``` (which is an macro expansion of ```_vec.push_back```) and ```qv_push_back_element```.

Here's an example of ```qv_push_back```

```C
qv_push_back (&myVec, 1, int);
// C++: myVec.push_back (1);
```

and an example of ```qv_push_back_element```

```C
int i = 1;
qv_push_back (&myVec, i);
// qv_push_back (&myVec, 1); is illegal
```

```qv_push_back_element``` is able to detect the type of element of what accepts, however, this feature is only availbe for those variables with known addresses.

Note that they all start with "qv_" as they are in fact a macro expansion, this does not apply to the pop_back and pop_front since they aren't macros.

There are in fact a lot of different push_backs built in qVector, but for starters this is already enough.

#### Pop_back and pop_front

Prototype of pop_back and pop_front:
>
    _vec.pop_back (qVector *);
    _vec.pop_front (qVector *);
    
Pretty straight foward, here's an example if you still can't figure out what to do:
```C
    _vec.pop_back(&myVec);
    _vec.pop_front(&myVec);
```

and yes, qVector supports pop_front.

#### Insert and erase

Insert in qVector are much alike in C++ Vector. it can be done with ```_vec.insert``` and ```_vec.insertIrr```, here's their prototype:

>
    _vec.insert (qvector *, size_t, void *, size_t)
    _vec.insertIrr (qvector *, size_t, void *,void *)
    
Here's an example of how you use it:
```C
    int arr[] = {1,2,3,4,5,6};
    _vec.insert(&myVec, 2, arr + 1, 4);
    // This will insert the int array from element 1 to 4 into myVec's 2 element
```
Let's say if myVec has already contain ```8,8,8,8,8,8``` in the vector, the above will result as ```8,8,2,3,4,5,8,8,8,8```

Another example:
```C
    int arr[] = {1,2,3,4,5,6};
    _vec.insertIrr(&myVec, 2, arr + 1, arr + 4);
    // This will insert the int array from element 1 to 4 into myVec's 2 element 
```

 which is equivalent to the former example given.
 
 Erase is also easy, here's the prototype:
 >
    _vec.erase(qvector *, size_t,size_t)

Example, I know:
```C
    _vec.erase(&myVec,3,6);
    // Erases myVec from element 3 to 6
```

#### Value Assigning
Value assigning can be done by ```qv_get``` or the combination of insert and erase.

```qv_get``` is an macro expansion of ```getIrr```, here's the somewhat prototype:
>
    qv_get (type, qvector, size_t)
    
Example for better explanation:
```C
    qv_get (int, myVec, 2) = 4; // Now myVec element 2 is 4 
    // C++: myVec [2] = 4;
```
```qv_get``` can also be used to recieve data in the vector:
```C
    char* myString = qv_get(char*, myVec, 5);
```

### Extracting Value from a qVector

- **qv_get**  

qVector provides a vary of ways to extract value from a vector, here we recommend ```qv_get``` (a macro expansion of ```getIrr```). The usage is as same as the above ("Value Assigning")

```C
    struct mytype mytypeVar = qv_get(struct mytype, myVec, 4);
```

- **_vec.getAny**

Another way to do this, if you're not a fan of macro, ```_vec.getAny``` (or simply just ```getAny```) is your other way out. Here's the prototype:
>
    _vec.getAny (qvector, void*, size_t)

Here's an example
```C
    typedef struct mytype mytype;
    mytype myVar;
    _vec.getAny (myVec, &myVar, 3);
    // equal to qv_get: myVar = qv_get(mytype, myVec, 3);
    // Or in C++: myVar = myVec [3];
```

- **_vec.getIrr**

To acquire the iterator of a vector's specific element, although using ```startVec()+n``` is fine in some cases, we suggest you to use ```_vec.getIrr``` (or simply just ```getIrr```). Here's the prototype:
>
    _vec.getIrr (qvector, size_t)
    
This will return a ```size_t``` type value. Example:
```C
    int* i = (int)_vec.getIrr (myVec, 2);
```

 - Other types
    ```_(type).get``` (e.g. ```_int.get```), type only accepts ```int```,```char``` and ```double```, this will return a value of the corresponding data type (old method, replaced by ```qv_get```)

### Memory Management
Although memory management are automatically done by qvector, since there are no destructor in C. Manully pressing the kill switch is needed in qvector after a function is called or the program ends.

For qVectors, there are two types of vector when we talk about memory management: **Global Vector** and **Local Vector**.
 - Global Vector: Exists through the program all only will be destroyed when the program terminates.
 - Local Vector: Destroyed when a function ends or at the time when any local variables are destroyed

Basically Local Vectors should be destroyed whenever a local variable is destoryed. Rule of thumb is any vector that is declared in main() function and not declared in a loop function should be global vectors, others should be local vectors.

Note that any destroyed qvector can be reused by re-initializing.

---


- **newLocal() & destroyLocal()**

In order to let qVectors memory controlling unit knows when a local function starts, a ```newLocal()``` flag should be placed when a left curly brackets is placed.

After a ```newLocal()``` flag is set, vectors that are initialized with ```newVector``` or ```_newVector``` afterwards will automatically flag these vectors as local vectors.

When the function ends, place a ```destroyLocal()``` before the right curly bracket. This will destroy all the vectors initialized in between the ```newLocal()``` and ```destroyLocal()```. 

Here's an full example of a good qvector program:
```C
    #include "qvector.h"
    void testMe () {
        newLocal(); // Placed at where a function starts
        qvector demo = _newVector (int);
        //...
        destroyLocal(); // Placed at where a function ends
        // demo is destroyed since it is between newLocal and destroyLocal
    }
    
    int main () {
        int a;
        testMe();
        for (a= 0 ; a < 5; a++){
            newLocal();
            qvector demo2 = _newVector (char*);
            //...
            destroyLocal();
        }
            // Since demo2 is declared in a loop 
            // demo2 will be destroyed everytime the loop goes through one cycle
            // therefore we need to call newLocal and destroyLocal to destroy
            // demo2 and all other qvectors initialized in between 
        destroyAll(); // Explain later
    }
```

```newLocal()``` and ```destroyLocal()``` can be called many times. Every ```newLocal()``` is called a ```destroyLocal()``` should always be called afterwards to destroy every vectors initialized in between.

An example should be easier to understand this:

```C
    newLocal();
    qvector a = _newVector (int);
    qvector b = _newVector (int);
    qvector c = _newVector (int);
        newLocal();
        qvector d = _newVector (int);
        qvector e = _newVector (int);
        qvector f = _newVector (int);
        qvector g = _newVector (int);
        destroyLocal();
        // qvector d e f g are destroyed
    qvector h = _newVector (int);
    qvector i = _newVector (int);
    destroyLocal();
    //qvector a b c h i are destroyed
    c = _newVector (int); // C is now reused (re-initializing)
    f = _newVector (int); // F is now reused
```

If ```newLocal()``` is called multiple times without any qvectors initialized in between, it will only have the same result as using one ```newLocal()```

```C
    newLocal();
    newLocal();
    newLocal();
    qvector myVec = _newVector(char);
    newLocal();
```
is equal to
```C
    newLocal();
    qvector myVec = _newVector(char);
    newLocal();
```

- **destroyAll**

Although when a program is terminated, the operation system will recycle every memory the program is occupied. A good approach and also to detect other memory leak then qvector is to end the program with ```destoryAll();```

```C
#include "qvector.h"
int main(){
    //...
    destoryAll();
}
```
Of course calling destoryAll will also destory every vector that is used to controll other vectors, which should cause a disaster if any qvector operation is called. However, qvector is smart enough to rebuilt itself. In any case, we do not suggest you to do this.

- **destroyVec**

In any case you wish to destroy an qvector manually (which in most of the time not needed), qvector provides a method:
>
    destroyVec (qvector);

An example:
```C
    qvector myvec = _newVector (int);
    destroyVec (myvec);
```
myvec can still be re-used if a new initializer is given to it, this can use to clean up a vector completely. But we suggest you to use ```_vec.clean(&myvec);``` instead if that is your purpose.

*Note: Do not use destroy() on an multi-dimension vector as a glitch (Not a huge problem, but will lead to memory-leak) may occur, this is a known issue and will be fixed until next version of qvector is published. Suggestion on how to correctly destroy a multi-dimension is showed in "Known Issues"*

- **newLocalVector & newGlobalVector**

In any case you need a vector to be global between newLocal and destroyLocal, use newGlobalVector. (just like newVector)

Or if you have no newLocal and destroyLocal flag and wish to force a vector declared as a local vector, use newLocalVector. This local vector will be destroyed when the last destroyLocal() is called.

### Vector-Wise Operations

- **resizeVec**

- **reserveVec**

### Multi-dimension Array

- Initialize an qvector as an multi-dimension array

- **_setMutliVec**

- **vget**

### Common Mistakes

1. **Assigning vectors with another**:
    Assume a and i are both qvector types:
   ```
   a = i; 
   ```
   Cool? No! Although you can still do things with both a and i, and happy compiler and all that, this will break the qvector. After such value assigning only one is to keep. You can either modify (such as pushing) a or i but not both at the same time. 
   
   The reason is that both a and i share the same  memory space, but there memory control variables do not, thus will not sychronize if both are modified.
   
   The correct way to do this is:
   ```C
   _vec.copy(&a,i);
   ```
2. **Multi-dimension array is manual release with ```destroy();```:**
    Multi-dimension array itself holds mulitple vector, which if an manual release is called only to the array itself, the array holder is released but the vector that are hold will be gone. Thus, if one were to free a multi-dimension array, it is important to 

### Known issues




