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
## Requirements
Needs C++20, because of the single concept that is used to make vector assignments work... If you are having issues, please remove the concept NotInit from conversion operators and replace simply with typename.
