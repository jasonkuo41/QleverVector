# QVector
Version  |  1.0.2b

An easy to use implementation of C++ Vector for ANSI C, it has everything you like about C++ vectors : 
* Automatic dynamic memory allocation (duh)
* Poppin' & Pushin'
* Automatic memory management and control (Auto rellease memory)
* Verify the size of a vector/ dynamic array
* Automatic boundary check (Not implemented in current version)
* Intuitive design for simulating multi-dimesion arrays
* Able to hold self-defined variable type / struct
* Memory-leak FREE *(Although some incorrect behavior may)*
* No more malloc() and realloc(), all gone along with qVector


### Perfect for C-only applications

For those hardware or some situations, when C is the only option but those who wish to use Vector-like functions, qVector is the way to go. Reason? Clean code and easy to use, from newbies to experts all are recommended.

*( Supports standards before C99, but using C99+ is recommended)*

### Powerful tool for more extensions

The following links all use qVector to exceed their also awesome functions.
* qString (A C++ String implementation) : [Not Available by now]
* qInfint (An integer type without size limit):  [N/A]
* qVar (An dynamic type for C) : [N/A]

*(By now, they are still WIP and not released)*



## Simple, Clean and Friendly
All the hard work has all been done in the header file, all you need to do is include it and it's ready to use.

It is as simple as the following code:
```c++
#include "qvector.h"
int main (){
    qvector a = newVector (setChar);
    _char.pushback (&a, 'B');
}
```
'B' is now pushed into vector a, as simple as that.

*Note: In newer version of qvector, initializer for basic types are no longer neccessary, as it will check automatically for initialization when action is performed.*

## Example and Tutorial
Documents are still WIP, a documention for fully control over and using all the potential of qVector is writing asap. 

### Get started


#### Declaring a vector and initializing
```C
#include "qvector.h"
int main (){
    qvector test = newVector (setInt);
    qvector testself = newVector (typeof(int));
    //...
}
```
qVectors can be declared like normal variables. However, normally initializing is needed for every declartion, otherwise without initializing, using any operations further would cause program to crash.
``` 
newVector (int type)
```
qVector supports both default type and self-defined variable type or struct. For self-defined variable type or other variable type, use typeof(X) or sizeof(X) (X is the variable type)
* Default types : setInt, setChar, setString, setDouble, setVec

Default types sometimes provide more functions then other types. (setVec is for building multi-dimension array)

#### Need to know basic

Befor you continue, you should know that qVector is written in a way to perform clean code and avoiding conflicts (Which is also a feature of qVector) , therefore function can be called mostly like below:
> 
    _(type).(function)
    Such as : _int.push_back(&a, 1);
However you can directly call any functions by its orignal name (push_backInt rather than _int.push_back), it is up to the user which is more comfortable. The following is available _type:
>
    _int. _db. (or _double.) _char. _vec.
    
**Rule of thumb 1:** _vec. is a special type for general use, if it doesn't return a qvector type, it must be common operation for all type of variables. 

Also, _vec. _(type). (function) is also available if you desire everything with qvector operations start with _vec

**Rule of thumb 2:** Whater operation involves what kind of datatype, use that _(type). *(e.g. _int.pushback (&myvec,2), 2 an int type involded in operation therefore use _int )* 

Otherwise if no datatype is involved in the operation use _vec instead *(e.g. _vec.resize (&a) )* 

**Rule of thumb 3:** Everything involving modify the vector itself requires & operands, *e.g. vec.popback (&myvec)* ,others don't. But don't worry, compilers take care of it, just remeber to check warnings.

### Modify Values in qVector
#### Poppin' and Pushin'

The most common way of modifying member of a vector (and also qVector) is by pushing and popping.If you don't know what that is, I suggest you google the basics of vector before continue.

qVector supports the following operations (slightly different from C++ Vectors)
* push_back
* push_front (Not available in current version)
* pop_back
* pop_front 

The following are examples of push and pop:
``` C++
_int.push_back (&yourvector, 5); 
// Push 5 into vector (this is an int operation, therefore _int.)
_char.push_back (&yourvector, '3');
_vec.push_back (&vector1, vector2)
_vec.pop_back (&yourvector);
_vec.pop_front (&yourvector);
```

Note by now, pop_back and pop_front are considered general operation as they do not involve any datatype.

_vec.push_back accepts only vector. See below to push any other type of variable.

Also, push_backs are not garuantee to success ( if the size exceeds the capacity , a failure of finding new space may occur) , if an the operation does not succeed, push_back will return 0 instead of 1.

Here, we now introduce a special function called
>
    _vec.push_backAny() or push_backAny()
The syntax is rather special :
>
    _vec.push_backAny (&targetVec, &pushVar)
    
All arguements require '&' operands.
Because this is a very special one that breaks the rule of thumb, here's a example code:
```C++
#include "qvector.h"

typedef struct { int a,b,c; } _test;

int main(){
    qvector a = newVector (sizeof(struct _test));
    _test myType  = {1,2,3};
    _vec.push_backAny (&a,&myType);
}
```

#### Insert value
*Note : Before v1.0.2b , insertAny is not available, this will fixed in future update*

Prototype:
> _(type).insert (qvector *a, int position, (type) input[] ,int length)

Here's an example:
``` C
_int.insert (&myvector, 2, inputarr, 12);
```
Here, 2 is the location where you wish to insert (counting from 0 of course), "inputarr" is the array you wish to insert, 12 is the size/length of the array, or how much element of inputarr you wish to insert.

#### Remove value
*Note : Before v1.0.2b , insertAny is not available, this will fixed in future update*

Prototype:
> _vec.erase (&myvector, int start, int end)

Here's an example:
``` C
_vec.erase (&myvector,2,5);
```
Here, 2 is the location where you wish to start to erase and 5 is the location to end the erase operation.

#### Replace value (Value Assigning)

(Not implemented by now)

But using the combination of insert and remove will allow you to replace a value, of course we are coming up with a new method that can be much eaiser to use.

An alternative way to assign an self-defined type is by the following, which is much more advanced and requires the use of iterator

```C
#include "qvector.h"

struct _test { int a,b,c; };

int main(){
    qvector a = newVector (sizeof(_test));
    struct _test b1 = {1, 2, 3};
    struct _test b2 = {5, 6, 7};
    _vec.push_backAny (&a,&b1);
    _vec.push_backAny (&a,&b2);
    //... Do something
    struct _test *point = _vec.getIrr (a,0); // Creates an iterator for _test type
    // Now this iterator is pointed to vector a's element 0
    // getIrr will be introduced in "Extracting Value" and "Use of itterator"
    *point = b2; // Assign any value to element 0 as you wish
    point = _vec.getIrr (a,1); // Make the iterator point to vector a's element 1
    // or point ++; will do the same thing too
    *point = b1; // Assign any value to element 1 as you wish
}
```
#### Copying an Vector to another

Prototype:
> _vec.copy (qvector *a,qvector b);

Here's an example:
``` C
_vec.copy (&a,b); // Vector a now equals b
```
Remember that value assisgning like a = b, is not allowed for qvectors (although compilers will not report error, nor will qvector will notice such invalid operation), see "Common mistakes" for details.

### Extracting Value from Vector

Unfortunetly, unlike C++ Vector, accessing value from vectors aren't as easy as arrays. Therefore alternatives are provided as below.

>
    _int.get() or getInt() -- Returns a int value
    _char.get() or getChar() -- Returns a char value
    ... (same applys to all default type)
    _vec.get() or vget() -- Returns a vector
    _vec.getAny() or getAny() -- For self-defined type
>

Syntax
```C++
    _int.get(myvec,2); 
    // Gets Vector myvec's 2 element, same as myvec [2] in C++'s vector
    // ... Others are all the same, expect getAny()
    _vec.getAny (myvec,&target,2);
```
Note that getAny is also special like push_backAny, unlike other get() functions returning their correspond type, getAny doesn't. Instead it requires you to put a pre-declared variable into the function to hold the function.

Here's an example:

```C++
#include "qvector.h"

typedef struct { int a,b,c; } _test;

int main(){
    qvector a = newVector (sizeof(struct _test));
    _test myType  = {1,2,3};
    _test getMy;
    _vec.push_backAny (&a,&myType);
    _vec.getAny (a,&getMy);
    // getMy now has the same value as myType
}
```

This provides a really cool way of extracting multi-dimmension vector, here's an example (detail will be explain in "Multi-dimension"):

```C++
    printf("%d", _int.get(vget(vget(vget(a,1)5)8)9)6); // Prints a[1][5][8][9][6]'s value
    printf("%d", vget(vget(b,1)3).size); // Get's the size of b[1][3]
```

### Memory Management

Although memory management are automatically done by qvector, since there are no destructor in C. Manully pressing the kill switch is needed in qvector after a function is called or the program ends.

#### newLocalVector
Another way of initializing another vector like ```newVector(int type)``` does. However, this tells the qvector that this is a local qvector and should be destroyed when the function it's in is terminated (or whenever ```destroyLocal();``` is called)

The usage of newLocalVector is the same as newVector.

#### newLocal() & destroyLocal()

By calling```newLocal();``` in any part of the program will create a flag that tells qvector when any ```destoryLocal();``` is called all the local vectors ( initialized with ```newLocalVector()``` ) in between these two flags will be destroyed

**Rule of thumb 4:**  ```newLocal();``` should be always be inserted into where a function starts and ```destroyLocal();``` should be placed whenever an function ends. All qvectors in between should be initialized by ```newLocalVector```.

(However, it can be placed in whatever place you like as long you know what your doing; also, if a qvector in between is instead initialized by newVector, it will be treated like global vector and will not destroy upon destroyLocal)

Here's an example function of how it works:
```C
int example_func (){
    newLocal();
    int my_int = 0;
    qvector a = newLocalVector ();
    qvector b = newLocalVector ();
    //.... Do something
    destroyLocal();
    return my_int;
}
//... another function
```
It should be reminded that newLocal() and destoryLocal() should be called equally same time in program runtime. Otherwise, an memory-leak may occur.
#### End of Program (destroyAll)
Although when a program is terminated, the operation system will recycle every memory the program is occupied. A good approach and also to detect other memory leak then qvector is to end the program with ```destoryAll();```

```C
#include "qvector.h"
int main(){
    //...
    destoryAll();
}
```
Of course calling destoryAll will also destory every vector that is used to controll other vectors, which should cause a disaster if any qvector operation is called. However, qvector is smart enough to rebuilt itself. In any case, we do not suggest you to do this.

#### Manual destroy (destroy)

In any case you wish to destroy an qvector manually (which in most of the time not needed), qvector provides a method:
>destroy (qvector a);

An example:
```C
qvector myvec = newVector (setInt);
destroy (myvec);
```
myvec can still be re-used if a new initializer is given to it, this can use to clean up a vector completely. But we suggest you to use ```_vec.clean(&myvec);``` instead if that is your purpose.

*Note: Do not use destroy() on an multi-dimension vector as a glitch (Not a huge problem, but will lead to memory-leak) may occur, this is a known issue and will be fixed until next version of qvector is published. Suggestion on how to correctly destroy a multi-dimension is showed in "Known Issues"*

#### Facts of newLocal and destroyLocal
The following are facts of newLocal and destroyLocal, though may come in handy, it is still suggested not to use them.
1. If no ```newLocal();``` is manually called before an qvector initialized with newLocalVector, a ```newLocal();``` is automatically called by initializer.
2. ```destoryLocal();``` can be called more than ```newLocal();``` and will cause no issue, thus if you don't know how much newLocal() is called, just spam destoryLocal() *(Note that a new function called destoryAllLocal() is probably coming on it's way in the next update)*
3. If two (or more) ```newLocal();``` is called with no newLocalVector initializer called in between, it is as same as calling one ```newLocal()```  .
    ```C
        newLocal();
        newLocal();
        newLocal();
    ```
    is equavilent to ```newLocal();``` since no newLocalVector is called in between
### Vector-wise operations

### Multi-dimension Vectors

### Miscellaneous

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

### Known issues