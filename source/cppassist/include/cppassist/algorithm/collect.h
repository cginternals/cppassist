
#pragma once


#include <utility>
#include <type_traits>
#include <unordered_map>
#include <map>


namespace cppassist
{
namespace algorithm
{


namespace detail
{


// Get result type of converter function

template <typename SourceValueType, typename Function>
using ResultValueType = typename std::result_of<Function(SourceValueType)>::type;

template <typename SourceType, typename Function>
using ResultValueTypeFromContainer = ResultValueType<typename SourceType::value_type, Function>;


// Fully specify a base container template for a value type and a variable number of other arguments

template <template <typename...> class BaseContainer, typename ValueType, template <typename> class... Args>
struct Container
{
    using Type = BaseContainer<ValueType, Args<ValueType>...>;
};

// specializations for map

template <typename ValueType>
struct Container<std::map, ValueType>
{
    using Type = std::map<typename ValueType::first_type, typename ValueType::second_type>;
};

template <typename ValueType, template <typename> class Compare>
struct Container<std::map, ValueType, Compare>
{
    using Type = std::map<typename ValueType::first_type, typename ValueType::second_type, Compare<typename ValueType::first_type>>;
};

template <typename ValueType, template <typename> class Compare, template <typename> class Allocator>
struct Container<std::map, ValueType, Compare, Allocator>
{
    using Type = std::map<typename ValueType::first_type, typename ValueType::second_type, Compare<typename ValueType::first_type>, Allocator<std::pair<const typename ValueType::first_type, typename ValueType::second_type>>>;
};

// specializations for unordered_map

template <typename ValueType>
struct Container<std::unordered_map, ValueType>
{
    using Type = std::unordered_map<typename ValueType::first_type, typename ValueType::second_type>;
};

template <typename ValueType, template <typename> class Hash>
struct Container<std::unordered_map, ValueType, Hash>
{
    using Type = std::unordered_map<typename ValueType::first_type, typename ValueType::second_type, Hash<typename ValueType::first_type>>;
};

template <typename ValueType, template <typename> class Hash, template <typename> class EqualTo>
struct Container<std::unordered_map, ValueType, Hash, EqualTo>
{
    using Type = std::unordered_map<typename ValueType::first_type, typename ValueType::second_type, Hash<typename ValueType::first_type>, EqualTo<typename ValueType::first_type>>;
};

template <typename ValueType, template <typename> class Hash, template <typename> class EqualTo, template <typename> class Allocator>
struct Container<std::unordered_map, ValueType, Hash, EqualTo, Allocator>
{
    using Type = std::unordered_map<typename ValueType::first_type, typename ValueType::second_type, Hash<typename ValueType::first_type>, EqualTo<typename ValueType::first_type>, Allocator<std::pair<const typename ValueType::first_type, typename ValueType::second_type>>>;
};


// Instantiate with a copy of the source allocator, if present

template <typename SourceType, typename ResultType, typename Enable = void>
struct Instantiator
{
    static ResultType create(const SourceType &)
    {
        return ResultType{};
    }
};

template <typename SourceType, typename ResultType>
struct Instantiator<SourceType, ResultType, typename SourceType::allocator_type>
{
    static ResultType create(const SourceType & source)
    {
        return ResultType{ source.get_allocator() };
    }
};


} // namespace detail


// Fully specified container type

template <typename ResultType, typename SourceType, typename Function>
ResultType collect(const SourceType & source, const Function & f)
{
    using std::begin;
    using std::end;
    using std::inserter;

    auto result = detail::Instantiator<SourceType, ResultType>::create(source);
    std::transform(begin(source), end(source), inserter(result, begin(result)), f);
    return result;
}


// Result container matches source container

template <
    template <typename...> class BaseContainer
  , typename Function
  , typename SourceValueType
  , template <typename> class ... Args
>
auto collect(const BaseContainer<SourceValueType, Args<SourceValueType>...> & source, const Function & f)
-> typename detail::Container<BaseContainer, detail::ResultValueType<SourceValueType, Function>, Args...>::Type
{
    return collect<typename detail::Container<BaseContainer, detail::ResultValueType<SourceValueType, Function>, Args...>::Type>(source, f);
}

template <
    typename Function
  , typename SourceKeyType
  , typename SourceValueType
  , template <typename> class Compare
  , template <typename> class Allocator
  , typename CompoundType = detail::ResultValueType<std::pair<const SourceKeyType, SourceValueType>, Function>
  , typename KeyType = typename CompoundType::first_type
  , typename ValueType = typename CompoundType::second_type
  , typename ResultType = std::map<KeyType, ValueType, Compare<KeyType>, Allocator<std::pair<const KeyType, ValueType>>>
>
ResultType collect(const std::map<SourceKeyType, SourceValueType, Compare<SourceKeyType>, Allocator<std::pair<const SourceKeyType, SourceValueType>>> & source, const Function & f)
{
    return collect<ResultType>(source, f);
}

template <
    typename Function
  , typename SourceKeyType
  , typename SourceValueType
  , template <typename> class Hash
  , template <typename> class EqualTo
  , template <typename> class Allocator
  , typename CompoundType = detail::ResultValueType<std::pair<const SourceKeyType, SourceValueType>, Function>
  , typename KeyType = typename CompoundType::first_type
  , typename ValueType = typename CompoundType::second_type
  , typename ResultType = std::unordered_map<KeyType, ValueType, Hash<KeyType>, EqualTo<KeyType>, Allocator<std::pair<const KeyType, ValueType>>>
>
ResultType collect(const std::unordered_map<SourceKeyType, SourceValueType, Hash<SourceKeyType>, EqualTo<SourceKeyType>, Allocator<std::pair<const SourceKeyType, SourceValueType>>> & source, const Function & f)
{
    return collect<ResultType>(source, f);
}


// Result container differs from source container

template <
    template <typename...> class BaseContainer
  , typename SourceType
  , typename Function
  , typename ResultType = typename detail::Container<BaseContainer, detail::ResultValueTypeFromContainer<SourceType, Function>>::Type
>
ResultType collect(const SourceType & source, const Function & f)
{
    return collect<ResultType>(source, f);
}

template <
    template <typename...> class BaseContainer
  , template <typename> class Arg1
  , typename SourceType
  , typename Function
  , typename ResultType = typename detail::Container<BaseContainer, detail::ResultValueTypeFromContainer<SourceType, Function>, Arg1>::Type
>
ResultType collect(const SourceType & source, const Function & f)
{
    return collect<ResultType>(source, f);
}

template <
    template <typename...> class BaseContainer
  , template <typename> class Arg1
  , template <typename> class Arg2
  , typename SourceType
  , typename Function
  , typename ResultType = typename detail::Container<BaseContainer, detail::ResultValueTypeFromContainer<SourceType, Function>, Arg1, Arg2>::Type
>
ResultType collect(const SourceType & source, const Function & f)
{
    return collect<ResultType>(source, f);
}

template <
    template <typename...> class BaseContainer
  , template <typename> class Arg1
  , template <typename> class Arg2
  , template <typename> class Arg3
  , typename SourceType
  , typename Function
  , typename ResultType = typename detail::Container<BaseContainer, detail::ResultValueTypeFromContainer<SourceType, Function>, Arg1, Arg2, Arg3>::Type
>
ResultType collect(const SourceType & source, const Function & f)
{
    return collect<ResultType>(source, f);
}

template <
    template <typename...> class BaseContainer
  , template <typename> class Arg1
  , template <typename> class Arg2
  , template <typename> class Arg3
  , template <typename> class Arg4
  , typename SourceType
  , typename Function
  , typename ResultType = typename detail::Container<BaseContainer, detail::ResultValueTypeFromContainer<SourceType, Function>, Arg1, Arg2, Arg3, Arg4>::Type
>
ResultType collect(const SourceType & source, const Function & f)
{
    return collect<ResultType>(source, f);
}


} // namespace algorithm
} // namespace cppassist