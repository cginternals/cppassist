
#pragma once


#include <cppassist/error/Error.h>


namespace cppassist
{


// Forward declaration of result template
template <typename T, typename E>
class Result;


/**
 * @brief
 *   Create a valid result for type void
 *
 * @tparam E
 *   Error type
 *
 * @return
 *   Result containing the valid condition
 *
 * @remarks
 *   This is a convenience function for using Result<void, E>().
 */
template <typename E = Error>
Result<void, E> ok();

/**
 * @brief
 *   Create an error result with a message
 *
 * @tparam T
 *   Result type
 * @tparam E
 *   Error type
 * @tparam Ts
 *   Additional parameters needed for the constructor of type E
 * @param[in] message
 *   Error message
 *
 * @return
 *   Result containing the error condition
 *
 * @remarks
 *   This is a convenience function for using Result<T, E>::fromError
 *   to avoid verbose code.
 */
template <typename T, typename E = Error, typename... Ts>
Result<T, E> error(const std::string & message, Ts... params);

/**
 * @brief
 *   Create an error result with a message
 *
 * @tparam T
 *   Result type
 * @tparam E
 *   Error type
 * @tparam Ts
 *   Additional parameters needed for the constructor of type E
 * @param[in] message
 *   Error message
 *
 * @return
 *   Result containing the error condition
 *
 * @remarks
 *   This is a convenience function for using Result<T, E>::fromError
 *   to avoid verbose code.
 */
template <typename T, typename E = Error, typename... Ts>
Result<T, E> error(std::string && message, Ts... params);

/**
 * @brief
 *   Create an error result with a message and a reason
 *
 * @tparam T
 *   Result type
 * @tparam E
 *   Error type
 * @tparam Ts
 *   Additional parameters needed for the constructor of type E
 * @param[in] message
 *   Error message
 * @param[in] reason
 *   Error that is the reason for this error
 *
 * @return
 *   Result containing the error condition
 *
 * @remarks
 *   This is a convenience function for using Result<T, E>::fromError
 *   to avoid verbose code.
 */
template <typename T, typename E = Error, typename R = Error, typename... Ts>
Result<T, E> error(const std::string & message, R && reason, Ts... params);

/**
 * @brief
 *   Create an error result with a message and a reason
 *
 * @tparam T
 *   Result type
 * @tparam E
 *   Error type
 * @tparam Ts
 *   Additional parameters needed for the constructor of type E
 * @param[in] message
 *   Error message
 * @param[in] reason
 *   Error that is the reason for this error
 *
 * @return
 *   Result containing the error condition
 *
 * @remarks
 *   This is a convenience function for using Result<T, E>::fromError
 *   to avoid verbose code.
 */
template <typename T, typename E = Error, typename R = Error, typename... Ts>
Result<T, E> error(std::string && message, R && reason, Ts... params);

/**
 * @brief
 *   Create an error result with a message and a reason
 *
 * @tparam T
 *   Result type
 * @tparam E
 *   Error type
 * @tparam Ts
 *   Additional parameters needed for the constructor of type E
 * @param[in] message
 *   Error message
 * @param[in] reason
 *   Error that is the reason for this error
 *
 * @return
 *   Result containing the error condition
 *
 * @remarks
 *   This is a convenience function for using Result<T, E>::fromError
 *   to avoid verbose code.
 */
template <typename T, typename E = Error, typename R = Error, typename... Ts>
Result<T, E> error(const std::string & message, const R & reason, Ts... params);

/**
 * @brief
 *   Create an error result with a message and a reason
 *
 * @tparam T
 *   Result type
 * @tparam E
 *   Error type
 * @tparam Ts
 *   Additional parameters needed for the constructor of type E
 * @param[in] message
 *   Error message
 * @param[in] reason
 *   Error that is the reason for this error
 *
 * @return
 *   Result containing the error condition
 *
 * @remarks
 *   This is a convenience function for using Result<T, E>::fromError
 *   to avoid verbose code.
 */
template <typename T, typename E = Error, typename R = Error, typename... Ts>
Result<T, E> error(std::string && message, const R & reason, Ts... params);

/**
 * @brief
 *   Encapsulates an expected result or an error condition
 */
template <typename T, typename E = Error>
class Result
{
public:
    /**
     * @brief
     *   Create error result
     *
     * @param[in] error
     *   Error to copy
     *
     * @return
     *   Result containing the error condition
     */
    static Result fromError(const E & error);

    /**
     * @brief
     *   Create error result
     *
     * @param[in] error
     *   Error to move
     *
     * @return
     *   Result containing the error condition
     */
    static Result fromError(E && error);

protected:
    /**
     * @brief
     *   Default Constructor
     */
    Result();

public:
    /**
     * @brief
     *   Constructor from value
     *
     * @param[in] value
     *   Value to copy
     */
    Result(const T & value);

    /**
     * @brief
     *   Constructor from value
     *
     * @param[in] value
     *   Value to move
     */
    Result(T && value);

    /**
     * @brief
     *   Copy Constructor
     *
     * @param[in] result
     *   Other result
     */
    Result(const Result<T, E> & result);

    /**
     * @brief
     *   Move Constructor
     *
     * @param[in] result
     *   Other result
     */
    Result(Result<T, E> && result);

    /**
     * @brief
     *   Destructor
     */
    ~Result();

    /**
     * @brief
     *   Check if this result has a value or an error
     *
     * @return
     *   true if result contains a value, false if it contains an error
     */
    bool isValid() const;

    /**
     * @brief
     *   Get value
     *
     * @return
     *   Movable reference to the contained value
     *
     * @remarks
     *   You must call this ONLY if isValid() == true!
     *   Otherwise, an exception (std::bad_cast) is thrown.
     */
    T && value();

    /**
     * @brief
     *   Get value
     *
     * @return
     *   Reference to the contained value
     *
     * @remarks
     *   You must call this ONLY if isValid() == true!
     *   Otherwise, an exception (std::bad_cast) is thrown.
     */
    const T & value() const;

    /**
     * @brief
     *   Get error
     *
     * @return
     *   Movable reference to the contained error
     *
     * @remarks
     *   You must call this ONLY if isValid() == false!
     *   Otherwise, an exception (std::bad_cast) is thrown.
     */
    E && error();

    /**
     * @brief
     *   Get error
     *
     * @return
     *   Reference to the contained error
     *
     * @remarks
     *   You must call this ONLY if isValid() == false!
     *   Otherwise, an exception (std::bad_cast) is thrown.
     */
    const E & error() const;

protected:
    union {
        T m_value; ///< Result value (valid only if m_isValid == true)
        E m_error; ///< Error value (valid only if m_isValid == false)
    };
    bool m_valid; ///< Marks if the result holds a valid value
};

// Specialization for type void
template <typename E>
class Result<void, E>
{
public:
    static Result<void, E> fromError(const E & error);
    static Result<void, E> fromError(E && error);

public:
    Result();
    Result(const Result<void, E> & result);
    Result(Result<void, E> && result);
    ~Result();
    bool isValid() const;
    E && error();
    const E & error() const;

protected:
    E m_error; ///< Error value (only used if m_isValid == false)
    bool m_valid; ///< Marks if the result holds a valid value
};


} // namespace cppassist


#include <cppassist/error/Result.inl>
