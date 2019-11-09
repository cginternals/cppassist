
namespace cppassist
{


// General implementation

template <typename E>
Result<void, E> ok() {
    return Result<void, E>();
}

template <typename T, typename E, typename... Ts>
Result<T, E> error(const std::string & message, Ts... params) {
    // Create error and put it into the result object
    return Result<T, E>::fromError(E(message, params...));
}

template <typename T, typename E, typename... Ts>
Result<T, E> error(std::string && message, Ts... params) {
    // Create error and put it into the result object
    return Result<T, E>::fromError(E(std::move(message), params...));
}

template <typename T, typename E, typename R, typename... Ts>
Result<T, E> error(const std::string & message, R && reason, Ts... params) {
    // Create error and put it into the result object. Move the reason into the error.
    return Result<T, E>::fromError(E(message, std::move(reason), params...));
}

template <typename T, typename E, typename R, typename... Ts>
Result<T, E> error(std::string && message, R && reason, Ts... params) {
    // Create error and put it into the result object. Move the reason into the error.
    return Result<T, E>::fromError(E(std::move(message), std::move(reason), params...));
}

template <typename T, typename E, typename R, typename... Ts>
Result<T, E> error(const std::string & message, const R & reason, Ts... params) {
    // Create error and put it into the result object. Copy the reason into the error.
    return Result<T, E>::fromError(E(message, reason, params...));
}

template <typename T, typename E, typename R, typename... Ts>
Result<T, E> error(std::string && message, const R & reason, Ts... params) {
    // Create error and put it into the result object. Copy the reason into the error.
    return Result<T, E>::fromError(E(std::move(message), reason, params...));
}

template <typename T, typename E>
Result<T, E> Result<T, E>::fromError(const E & error)
{
    // Create error result by copying the error
    Result<T, E> result;
    new (&result.m_error) E(error);
    result.m_valid = false;

    // Return result
    return result;
}

template <typename T, typename E>
Result<T, E> Result<T, E>::fromError(E && error)
{
    // Create error result by moving the error
    Result<T, E> result;
    new (&result.m_error) E(std::move(error));
    result.m_valid = false;

    // Return result
    return result;
}

template <typename T, typename E>
Result<T, E>::Result()
: m_valid(false)
{
    // This is used only internally. When used, it must be made sure that either
    // m_value or m_error is initialized and m_value is set to the appropriate value.
}

template <typename T, typename E>
Result<T, E>::Result(const T & value)
: m_value(value)
, m_valid(true)
{
    // Copy value from other result
}

template <typename T, typename E>
Result<T, E>::Result(T && value)
: m_value(std::move(value))
, m_valid(true)
{
    // Move value from other result
}

template <typename T, typename E>
Result<T, E>::Result(const Result<T, E> & result)
: m_valid(result.m_valid)
{
    // Check other result
    if (m_valid) {
        // Copy value
        new (&m_value) T(result.m_value);
    } else {
        // Copy error
        new (&m_error) E(result.m_error);
    }
}

template <typename T, typename E>
Result<T, E>::Result(Result<T, E> && result)
: m_valid(result.m_valid)
{
    // Check other result
    if (m_valid) {
        // Move value
        new (&m_value) T(std::move(result.m_value));
    } else {
        // Move error
        new (&m_error) E(std::move(result.m_error));
    }
}

template <typename T, typename E>
Result<T, E>::~Result()
{
    // Check if result is valid
    if (m_valid) {
        // Destroy value
        m_value.~T();
    } else {
        // Destroy error
        m_error.~E();
    }
}

template <typename T, typename E>
bool Result<T, E>::isValid() const
{
    // Return if result is valid
    return m_valid;
}

template <typename T, typename E>
T && Result<T, E>::value()
{
    // Check if result is valid
    if (m_valid) {
        // Return value
        return std::move(m_value);
    } else {
        // Error, raise exception
        throw std::bad_cast();
    }
}

template <typename T, typename E>
const T & Result<T, E>::value() const
{
    // Check if result is valid
    if (m_valid) {
        // Return value
        return m_value;
    } else {
        // Error, raise exception
        throw std::bad_cast();
    }
}

template <typename T, typename E>
E && Result<T, E>::error()
{
    // Check if result is valid
    if (!m_valid) {
        // Return error
        return std::move(m_error);
    } else {
        // Error, raise exception
        throw std::bad_cast();
    }
}

template <typename T, typename E>
const E & Result<T, E>::error() const
{
    // Check if result is valid
    if (!m_valid) {
        // Return error
        return m_error;
    } else {
        // Error, raise exception
        throw std::bad_cast();
    }
}


// Implementation for type void

template <typename E>
Result<void, E> Result<void, E>::fromError(const E & error)
{
    // Create error result by copying the error
    Result<void, E> result;
    new (&result.m_error) E(error);
    result.m_valid = false;

    // Return result
    return result;
}

template <typename E>
Result<void, E> Result<void, E>::fromError(E && error)
{
    // Create error result by moving the error
    Result<void, E> result;
    new (&result.m_error) E(std::move(error));
    result.m_valid = false;

    // Return result
    return result;
}

template <typename E>
Result<void, E>::Result()
: m_valid(true)
{
}

template <typename E>
Result<void, E>::Result(const Result<void, E> & result)
: m_valid(result.m_valid)
{
    // Check other result
    if (m_valid) {
        // Remove error
        m_error = E();
    } else {
        // Copy error
        m_error = result.m_error;
    }
}

template <typename E>
Result<void, E>::Result(Result<void, E> && result)
: m_valid(false)
{
    // Check other result
    if (m_valid) {
        // Remove error
        m_error = E();
    } else {
        // Move error
        m_error = std::move(result.m_error);
    }
}

template <typename E>
Result<void, E>::~Result()
{
}

template <typename E>
bool Result<void, E>::isValid() const
{
    // Return if result is valid
    return m_valid;
}

template <typename E>
E && Result<void, E>::error()
{
    // Check if result is valid
    if (!m_valid) {
        // Return error
        return std::move(m_error);
    } else {
        // Error, raise exception
        throw std::bad_cast();
    }
}

template <typename E>
const E & Result<void, E>::error() const
{
    // Check if result is valid
    if (!m_valid) {
        // Return error
        return m_error;
    } else {
        // Error, raise exception
        throw std::bad_cast();
    }
}


} // namespace cppassist
