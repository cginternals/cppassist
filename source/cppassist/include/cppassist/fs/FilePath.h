
#pragma once


#include <string>

#include <cppassist/cppassist_api.h>


namespace cppassist
{


/**
*  @brief
*    Path to file or directory
*
*    This class stores a path to a file or directory and provides common
*    operations like getting the file name or extension.
*
*    FilePath uses a unified format for storing paths, i.e., it uses only
*    forward slashes '`/`' as delimiter. When a FilePath is constructed from
*    a string, the path is translated into the unified format and can then
*    be used in a cross-platform way throughout an application. All operations
*    on FilePath also return paths in the same unified format. To obtain the
*    original input string of a FilePath, use originalPath().
*
*    All operations are completely string-based and don't use any system information.
*    Therefore, paths are treated purely syntactially and do not imply that for example
*    a file does really exist.
*/
class CPPASSIST_API FilePath
{
public:
    /**
    *  @brief
    *    Constructor
    */
    FilePath();

    /**
    *  @brief
    *    Copy constructor
    *
    *  @param[in] filePath
    *    File path to copy
    */
    FilePath(const FilePath & filePath);

    /**
    *  @brief
    *    Move constructor
    *
    *  @param[in] filePath
    *    File path to move
    */
    FilePath(FilePath && filePath);

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] path
    *    File path
    */
    FilePath(const std::string & path);

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] path
    *    File path
    */
    FilePath(std::string && path);

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] path
    *    File path
    */
    FilePath(const char * path);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~FilePath();

    /**
    *  @brief
    *    Get original (unprocessed) input string
    *
    *  @return
    *    Path that was originally provided
    */
    const std::string & originalPath() const;

    /**
    *  @brief
    *    Get processed path as string
    *
    *  @return
    *    File path
    *
    *  @remark
    *    The path is processed and modified in a way that it can be used
    *    consistently on every platform:
    *    - Only forward slashes '`/`' are used as delimiter
    *    - Trailing slashes are removed
    */
    const std::string & path() const;

    /**
    *  @brief
    *    Set path
    *
    *  @param[in] path
    *    File path
    */
    void setPath(const std::string & path);

    /**
    *  @brief
    *    Get base name
    *
    *  @return
    *    Base name of the file the stored path points to, without extension
    *
    *  @remark
    *    This function returns `"something"` for both `"/path/to/something.ex"` and
    *    `"/path/to/something.ex/"`.
    */
    std::string baseName() const;

    /**
    *  @brief
    *    Get full file name
    *
    *  @return
    *    Name of the file the stored path points to, with extension

    *  @remark
    *    This function returns `"something.ex"` for both `"/path/to/something.ex"` and
    *    `"/path/to/something.ex/"`.
    */
    std::string fileName() const;

    /**
    *  @brief
    *    Get file extension
    *
    *  @return
    *    Extension of the file the stored path points to

    *  @remark
    *    If the path has no extension, an empty string is returned.
    */
    std::string extension() const;

    /**
    *  @brief
    *    Get directory path
    *
    *  @return
    *    Path to the directory, with trailing slashes
    *
    *  @remark
    *    The returned path string is in unified form, so only forward slashes '`/`' are used.
    *
    *  @remark
    *    This function returns `"/path/to/"` as directory path for both
    *    `"/path/to/directory"` and `"/path/to/directory/"`.
    */
    std::string directoryPath() const;

    /**
    *  @brief
    *    Get drive letter
    *
    *  @return
    *    Drive letter of the path on Windows (e.g., "C").
    *    If there is no drive letter (Linux, Max), an empty string is returned.
    */
    std::string driveLetter() const;

    /**
    *  @brief
    *    Copy assignment operator
    *
    *  @param[in] filePath
    *    Right-hand value to move
    *
    *  @return
    *    Reference to this value
    */
    FilePath & operator=(const FilePath & filePath);

    /**
    *  @brief
    *    Move assignment operator
    *
    *  @param[in] filePath
    *    Right-hand value to move
    *
    *  @return
    *    Reference to this value
    */
    FilePath & operator=(FilePath && filePath);

    /**
    *  @brief
    *    Equality operator
    *
    *  @param[in] other
    *    The other file path for comparison
    *
    *  @return
    *    `true` if both file paths are equal, else `false`
    *
    *  @remark
    *    Two file paths are considered equal if the contents of the path are equal
    */
    bool operator==(const FilePath & other) const;

    /**
    *  @brief
    *    Inequality operator
    *
    *  @param[in] other
    *    The other file path for comparison
    *
    *  @return
    *    `true` if both file paths differ, else `false`
    *
    *  @remark
    *    Two file paths are considered equal if the contents of the path are equal
    */
    bool operator!=(const FilePath & other) const;


protected:
    /**
    *  @brief
    *    Convert path into unified form
    *
    *  @param[in] path
    *    File path
    *
    *  @return
    *    Unified form of input path (e.g., only forward slashed '`/`').
    */
    static std::string toPath(const std::string & path);


protected:
    std::string m_originalPath; ///< Original unprocessed input string
    std::string m_path;         ///< Path (using only forward slashes '`/`' as delimiter)
};


} // namespace cppassist
