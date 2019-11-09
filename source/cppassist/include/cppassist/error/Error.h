
#pragma once


#include <string>
#include <memory>

#include <cppassist/cppassist_api.h>


namespace cppassist
{


/**
 * @brief
 *   Error condition
 * 
 *   An Error describes a runtime error condition. It contains an error message,
 *   which explains the error in more details, and optionally it contains another
 *   error, which is the reason for this error. This way, errors can be chained
 *   together in reflect the interdependence of runtime errors.
 *
 *   Error can also be used as a base type for derived error classes. This can
 *   be used for example to store more context information in a specific error
 *   class,e.g., the input that caused an error or the number of retries that
 *   were attempted. In general, however, the basic Error class should be
 *   sufficient and can be used directly.
 */
class CPPASSIST_API Error
{
public:
    /**
     * @brief
     *   Constructor with an error message
     *
     * @param[in] message
     *   Error message
     */
    Error(const std::string & message = "");

    /**
     * @brief
     *   Constructor with an error message
     *
     * @param[in] message
     *   Error message
     */
    Error(std::string && message);

    /**
     * @brief
     *   Constructor with an error message and a reason
     *
     * @tparam E
     *   Type of the reason error
     * @param[in] message
     *   Error message
     * @param[in] reason
     *   Previous error that caused this error
     */
    template<typename E>
    Error(const std::string & message, const E & reason);

    /**
     * @brief
     *   Constructor with an error message and a reason
     *
     * @tparam E
     *   Type of the reason error
     * @param[in] message
     *   Error message
     * @param[in] reason
     *   Previous error that caused this error
     */
    template<typename E>
    Error(std::string && message, const E & reason);

    /**
     * @brief
     *   Constructor with an error message and a reason
     *
     * @tparam E
     *   Type of the reason error
     * @param[in] message
     *   Error message
     * @param[in] reason
     *   Previous error that caused this error
     */
    template<typename E>
    Error(const std::string & message, E && reason);

    /**
     * @brief
     *   Constructor with an error message and a reason
     *
     * @tparam E
     *   Type of the reason error
     * @param[in] message
     *   Error message
     * @param[in] reason
     *   Previous error that caused this error
     */
    template<typename E>
    Error(std::string && message, E && reason);

    /**
     * @brief
     *   Copy constructor
     *
     * @param[in] error
     *   Other error
     */
    Error(const Error & error);

    /**
     * @brief
     *   Move constructor
     *
     * @param[in] error
     *   Other error
     */
    Error(Error && error);

    /**
     * @brief
     *   Destructor
     */
    virtual ~Error();

    /**
     * @brief
     *   Copy operator
     *
     * @param[in] error
     *   Other error
     *
     * @return
     *   Reference to this error
     */
    Error & operator =(const Error & error);

    /**
     * @brief
     *   Move operator
     *
     * @param[in] error
     *   Other error
     *
     * @return
     *   Reference to this error
     */
    Error & operator =(Error && error);

    /**
     * @brief
     *   Clone error object
     *
     * @return
     *   Error that is a copy of this error
     */
    virtual Error * clone() const;

    /**
     * @brief
     *   Get error message
     *
     * @return
     *   Error message
     */
    const std::string & message() const;

    /**
     * @brief
     *   Check if this error has a reason
     *
     * @return
     *   true if error has a reason, else false
     */
    bool hasReason() const;

    /**
     * @brief
     *   Get reason for this error
     *
     * @return
     *   Reason for this error (can be nullptr)
     */
    Error * reason() const;

    /**
     * @brief
     *   Print error to std::cout
     *
     * @param[in] indent
     *   Current indentation
     * @param[in] indentStep
     *   Indentation added in each step
     */
    void print(const std::string & indent = "", const std::string & indentStep = "  ") const;

    /**
     * @brief
     *   Print error to output stream
     *
     * @param[in] os
     *   Output stream
     * @param[in] indent
     *   Current indentation
     * @param[in] indentStep
     *   Indentation added in each step
     */
    virtual void printTo(std::ostream & os, const std::string & indent = "", const std::string & indentStep = "  ") const;


protected:
    std::string m_message; ///< Error message
    std::unique_ptr<Error> m_reason; ///< Reason for this error (can be nullptr)
};


} // namespace cppassist


#include <cppassist/error/Error.inl>
