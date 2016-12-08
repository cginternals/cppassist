
namespace cppassist
{


template <typename Class, typename Type>
std::ptrdiff_t offset(Type Class::*member)
{
    return reinterpret_cast<std::ptrdiff_t>(&(((Class*)0)->*member));
}


} // namespace cppassist
