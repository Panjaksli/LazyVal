# LazyVal
Single header lazy evaluation interface for vector type classes in C++
## What this does ?
1) Do straightforward arithmetic operations with vector types (class only needs size() and operator[]) using operator overloading (+,-,*,/)
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
## Two versions
By default lazyval.h contains operators implemented as structs with static methods op, this should result in most optimization.  
Alternatively lazyval_c.h is implemented using callable objects, meaning you can pass lambdas directly into maps and constructors of Expr.
