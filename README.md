# LazyVal
Header only lazy evaluation interface for vector type classes in C++
## What can this do ?
1) Do straightforward arithmetic operations with vector types (class only needs constructor(size), size() and operator[] methods) using operator overloading (+,-,*,/)  
2) Lazy evaluate only the needed results (no internal caching). Other than that, you can chain expresssions to your liking, without any additional runtime cost !  
Here is example of what you can do:  
```cpp
#include "lazyval.h"
using namespace Lazy;
auto a = std::vector<float>(48, 6);
// Create templated symbolic expression tree
auto t = 4 * (a + a + a + a + 4) / std::vector<float>(48, 6);
// Evaluate only t[4]
std::cout << t[4];
// Evaluate the whole vector, use this if you need to cache/get all the results.
std::vector<float> v = t;
```
## Basics
The size is always equal to the smallest vector in the whole expression tree. Scalars are applied to all elements, but don't affect the resulting size.  
For forced evaluation or conversion, please use either conversion operator or eval<T>() member method.  
If you want to apply a lambda over 1 - 3 operands, use map() functions.  
Ternary operator is possible using cond() function.  
## Requirements
Works with C++17 and GCC, Clang. (Maybe MSVC too...)  
