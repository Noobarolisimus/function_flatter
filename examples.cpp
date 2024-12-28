#include <iostream>
#include "function_flatter.hpp"

void F1(const std::string& s, int n){
    std::cout << "F1 " << s << " " << n << "\n";
}

std::string GetString(){
    return "qwe";
}

int overloaded(float a, float b) { return a + b; }
int overloaded(int   a, float b) { return a + b; }

int main()
{
    // Same as `std::string s1 = GetString();`.
    std::string s1 = $ GetString $$;
    // Same as `F1(GetString(), 123);`.
    $ F1, $ GetString $$, 123 $$;
    // Same as `F1([]{ return "asd"; }, 321);`.
    $ F1, $ []{ return "asd"; } $$, 321 $$;
    // Same as `[](int a, const std::string& b){ std::cout << a << ' ' << b << '\n'; }(333, "qweqwe");`.
    $ [](int a, const std::string& b){ std::cout << a << ' ' << b << '\n'; }, 333, "qweqwe" $$;

    // Only simple lambdas are supported,
    // so no capture group.
    // $ [&]{ return "asd"; } $$;  // Error.

    // Fuction overloading becomes wierd. You should pick wanted parameter types.
    // Same as `std::string s2 = std::to_string(123);`.
    std::string s2 = $pick(int) std::to_string, 123 $$;
    
    // You should specifie all parameter types.
    // `$pick(int) overloaded, 1, 2 $$;` cause an error,
    // though we clearly wanted pick `overloaded(int, float)`.
    
    // Same as `overloaded(1, 2)`.
    $pick(int, float) overloaded, 1, 2 $$;
}
