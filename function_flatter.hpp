#include <functional>


template<typename... Params, typename R, typename... Args>
auto _FunctionFlatter(R (*func)(Params...), Args... args){
    if constexpr (std::is_same<R, void>::value)
        func(args...);
    else
        return func(args...);
}

template <typename T>
struct _LambdaUtils
    : public _LambdaUtils<decltype(&T::operator())>
{};

template <typename ClassType, typename R, typename... Params>
struct _LambdaUtils<R(ClassType::*)(Params...) const> {
    using result_type = R;

    template<typename... Args>
    static R _FunctionFlatter(R (*lambda)(Params...), Args... args){
        if constexpr (std::is_void<R>::value)
            lambda(args...);
        else
            return lambda(args...);
    }
};

template<typename... Args>
auto _FunctionFlatter(auto lambda, Args... args){
    using utils = _LambdaUtils<decltype(lambda)>;
    if constexpr (std::is_void<typename utils::result_type>::value)
        utils::_FunctionFlatter(lambda, args...);
    else
        return utils::_FunctionFlatter(lambda, args...);
}

#ifdef $
    #error `$` is already defined.
#endif
#ifdef $$
    #error `$$` is already defined.
#endif
#ifdef $pick
    #error `$pick` is already defined.
#endif

#define $ _FunctionFlatter(
#define $pick(...) _FunctionFlatter<__VA_ARGS__>(
#define $$ )