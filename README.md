# LazyVal
Single header lazy evaluation interface for vector type classes in C++
## What this does ?
This allows you to:
1) Do straightforward arithmetic operations with vector types (class only needs size() and operator[]) using operator overloading (+,-,*,/)
2) Lazy evaluate only the needed results. You can chain expresssions to your liking, without any additional runtime cost !
Here is example of what you can do:
```cpp
auto a = std::vector<float>(48, 6);
// Create symbolic expression tree
auto t = 4 * (a + a + a + a + 4) / std::vector<float>(48, 6);
// Evaluate ONLY t[4]
std::cout << t[4];
// Evaluate the whole vector
std::vector<float> v = t;
```
