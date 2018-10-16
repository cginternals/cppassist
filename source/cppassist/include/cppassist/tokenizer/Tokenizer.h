
#pragma once


#include <string>
#include <vector>

#include <cppassist/cppassist_api.h>


namespace cppassist
{


/**
*  @brief
*    Text parser tool that converts a text buffer into a stream of tokens
*
*  @remarks
*    A tokenizer takes a text buffer and identifies individual tokens
*    separated by white space. It returns those tokens one by one, removing
*    the white space in between. Based on this low-level parsing tool,
*    text parsers (e.g., JSON) can be implemented.
*/
class CPPASSIST_API Tokenizer
{
public:
    /**
    *  @brief
    *    Parser options
    */
    enum Option
    {
        OptionParseStrings       =   1 ///< Parse strings (use #setQuotationMarks to set string characters)
      , OptionParseNumber        =   2 ///< Parse numbers
      , OptionParseBoolean       =   4 ///< Parse boolean values
      , OptionParseNull          =   8 ///< Parse null value
      , OptionCStyleComments     =  16 ///< Enable '`/* */`' for multi-line comments
      , OptionCppStyleComments   =  32 ///< Enable '`//`' for one-line comments
      , OptionShellStyleComments =  64 ///< Enable '`#`' for one-line comments
      , OptionIncludeComments    = 128 ///< Include comments in the output of the tokenizer
    };

    /**
    *  @brief
    *    Token types
    */
    enum TokenType
    {
        TokenEndOfStream    ///< No token read, end of stream reached
      , TokenWhitespace     ///< %Token contains only whitespace
      , TokenComment        ///< %Token contains a comment
      , TokenStandalone     ///< %Token contains a standalone string
      , TokenString         ///< %Token contains a string
      , TokenNumber         ///< %Token contains number
      , TokenBoolean        ///< %Token contains a boolean value
      , TokenNull           ///< %Token contains a null value
      , TokenSingleChar     ///< %Token contains a single character
      , TokenWord           ///< %Token contains a regular word (any other than above)
    };

    /**
    *  @brief
    *    %Token
    */
    struct Token
    {
        TokenType    type;         ///< Type of token (see #TokenType)
        std::string  content;      ///< %Token content (the actual string read)
        int          intValue;     ///< Only valid if type == #TokenNumber
        double       numberValue;  ///< Only valid if type == #TokenNumber
        std::string  stringValue;  ///< Only valid if type == #TokenString
        bool         booleanValue; ///< Only valid if type == #TokenBoolean
        bool         isDouble;     ///< If type == #TokenNumber and isDouble, use #numberValue
        const char * begin;        ///< Pointer to the first character of the token
        const char * end;          ///< Pointer to the first character after the token
        unsigned int line;         ///< Line number where the token begins
        unsigned int column;       ///< Column number where the token begins
    };

    /**
    *  @brief
    *    Token information from lookahead
    */
    struct Lookahead
    {
        TokenType   type; ///< Type of token (see #TokenType)
        std::string hint; ///< Hint about value or type (only valid for #TokenComment or #TokenStandalone)
    };


public:
    /**
    *  @brief
    *    Constructor
    */
    Tokenizer();

    /**
    *  @brief
    *    Destructor
    */
    ~Tokenizer();

    /**
    *  @brief
    *    Get parsing options
    *
    *  @return
    *    Parsing options
    */
    unsigned int options() const;

    /**
    *  @brief
    *    Set parsing options
    *
    *  @param[in] options
    *    Parsing options
    */
    void setOptions(unsigned int options);

    /**
    *  @brief
    *    Check if a specific parsing option is set
    *
    *  @return
    *    `true` if option is set, else `false`
    */
    bool hasOption(Option option) const;

    /**
    *  @brief
    *    Get whitespace characters
    *
    *  @return
    *    Characters that are considered whitespace
    */
    const std::string & whitespace() const;

    /**
    *  @brief
    *    Set whitespace characters
    *
    *  @param[in] whitespace
    *    Characters that are considered whitespace
    */
    void setWhitespace(const std::string & whitespace);

    /**
    *  @brief
    *    Get quotation marks
    *
    *  @return
    *    Characters that can enclose a string
    */
    const std::string & quotationMarks() const;

    /**
    *  @brief
    *    Set quotation marks
    *
    *  @param[in] quotationMarks
    *    Characters that can enclose a string
    */
    void setQuotationMarks(const std::string & quotationMarks);

    /**
    *  @brief
    *    Get single characters
    *
    *  @return
    *    Characters that stand on their own
    */
    const std::string & singleCharacters() const;

    /**
    *  @brief
    *    Set single characters
    *
    *  @param[in] singleCharacters
    *    Characters that stand on their own
    */
    void setSingleCharacters(const std::string & singleCharacters);

    /**
    *  @brief
    *    Get standalone strings
    *
    *  @return
    *    Strings that stand on their own
    */
    const std::vector<std::string> & standalones() const;

    /**
    *  @brief
    *    Set standalone strings
    *
    *  @param[in] standalones
    *    Strings that stand on their own
    */
    void setStandalones(const std::vector<std::string> & standalones);

    /**
    *  @brief
    *    Load text document to parse
    *
    *  @param[in] filename
    *    Filename of text document
    *
    *  @return
    *    `true` if file could be loaded, else `false`
    */
    bool loadDocument(const std::string & filename);

    /**
    *  @brief
    *    Set text document to parse
    *
    *  @param[in] document
    *    Text document
    */
    void setDocument(const std::string & document);

    /**
    *  @brief
    *    Set text document to parse
    *
    *  @param[in] beginDoc
    *    Pointer to the first character inside the document
    *  @param[in] endDoc
    *    Pointer to the first character outside of the document
    */
    void setDocument(const char * beginDoc, const char * endDoc);

    /**
    *  @brief
    *    Parse and return the next token
    *
    *  @return
    *    %Token
    *
    *  @remarks
    *    If there are no tokens left, Token::type is set to #TokenEndOfStream.
    */
    Token parseToken();


private:
    /**
    *  @brief
    *    Read next token
    *
    *  @return
    *    %Token
    */
    Token readToken();

    /**
    *  @brief
    *    Read C-style comment
    *
    *  @remarks
    *    Advances the position until the end of the comment is reached
    */
    void readCStyleComment();

    /**
    *  @brief
    *    Read CPP-style comment
    *
    *  @remarks
    *    Advances the position until the end of the comment is reached
    */
    void readCppStyleComment();

    /**
    *  @brief
    *    Read Shell-style comment
    *
    *  @remarks
    *    Advances the position until the end of the comment is reached
    */
    void readShellStyleComment();

    /**
    *  @brief
    *    Read standalone string
    *
    *  @param[in] standalone
    *    String
    *
    *  @remarks
    *    Advances the position by the size of the string
    */
    void readStandaloneString(const std::string & standalone);

    /**
    *  @brief
    *    Read string
    *
    *  @param[in] endChar
    *    Character that marks the end of the string (usually `"` or `'`)
    *
    *  @remarks
    *    Advances the position until the end of the string is reached
    */
    void readString(char endChar);

    /**
    *  @brief
    *    Read number
    *
    *  @param[in] number
    *    Number string that was parsed
    *
    *  @remarks
    *    Advances the position until the end of the number is reached
    */
    void readNumber(const std::string & number);

    /**
    *  @brief
    *    Read word
    *
    *  @remarks
    *    Advances the position until the end of the word is reached.
    *    A word ends when whitespace is encountered or the beginning of
    *    any other token type (e.g., a string, or a comment) is detected.
    */
    void readWord();

    /**
    *  @brief
    *    Skip any whitespace characters
    *
    *  @remarks
    *    Advances the position until a non-whitespace character is found.
    */
    void skipWhitespace();

    /**
    *  @brief
    *    Read one character
    *
    *  @return
    *    Character
    *
    *  @remarks
    *    Advances the position by one character
    */
    char readChar();

    /**
    *  @brief
    *    Determine type of token that starts at the current position
    *
    *  @return
    *    Token type
    *
    *  @remarks
    *    Does not advance the current position.
    */
    Lookahead lookAheadTokenType() const;

    /**
    *  @brief
    *    Look up next character
    *
    *  @param[in] index
    *    Index of character to look at (from current position)
    *
    *  @return
    *    Character
    *
    *  @remarks
    *    Does not advance the current position.
    */
    char nextChar(size_t index = 0) const;

    /**
    *  @brief
    *    Look ahead string at current position
    *
    *  @param[in] length
    *    Number of characters to look ahead
    *
    *  @return
    *    String of the given length (or smaller if end-of-stream)
    *
    *  @remarks
    *    Does not advance the current position.
    */
    std::string lookAhead(size_t length) const;

    /**
    *  @brief
    *    Check if a standalone string matches at the current position
    *
    *  @return
    *    Standalone string that matches, `""` if none does
    */
    const std::string & matchStandaloneStrings() const;

    /**
    *  @brief
    *    Check if there is a (floating point) number at the current position
    *
    *  @return
    *    Number string, `""` if no number was found
    */
    std::string matchNumber() const;

    /**
    *  @brief
    *    Get current line in the document
    *
    *  @return
    *    Line number (starting with 1)
    */
    unsigned int line() const;

    /**
    *  @brief
    *    Get current column in the document
    *
    *  @return
    *    Column number (starting with 1)
    */
    unsigned int column() const;

    /**
    *  @brief
    *    Convert token value into a number
    *
    *  @param[in,out] token
    *    %Token
    */
    void decodeNumber(Token & token);

    /**
    *  @brief
    *    Convert token value into a double value
    *
    *  @param[in,out] token
    *    %Token
    */
    void decodeDouble(Token & token);

    /**
    *  @brief
    *    Convert token value into string
    *
    *  @param[in,out] token
    *    %Token
    */
    void decodeString(Token & token);

    /**
    *  @brief
    *    Decode unicode value
    *
    *  @param[in] current
    *    Position in the character buffer
    *  @param[in] end
    *    Pointer to the first character after the end of the buffer
    *  @param[out] unicode
    *    Unicode value
    *
    *  @return
    *    `true` on success, `false` on error
    */
    bool decodeUnicodeCodePoint(const char * & current, const char * end, unsigned int & unicode) const;

    /**
    *  @brief
    *    Decode unicode escape sequence
    *
    *  @param[in] current
    *    Position in the character buffer
    *  @param[in] end
    *    Pointer to the first character after the end of the buffer
    *  @param[out] unicode
    *    Unicode value
    *
    *  @return
    *    `true` on success, `false` on error
    */
    bool decodeUnicodeEscapeSequence(const char * & current, const char * end, unsigned int & unicode) const;

    /**
    *  @brief
    *    Convert code point to UTF8
    *
    *  @param[in] cp
    *    Code point
    *
    *  @return
    *    UTF8 value
    */
    std::string codePointToUTF8(unsigned int cp) const;

    /**
    *  @brief
    *    Check if given character is one of a given set
    *
    *  @param[in] c
    *    Character
    *  @param[in] chars
    *    Character set
    *
    *  @return
    *    `true` if `c` is on of the characters in chars, else `false`
    */
    bool charIn(char c, const std::string & chars) const;


private:
    // Options
    unsigned int             m_options;          ///< Parsing options
    std::string              m_whitespace;       ///< Characters that are considered whitespace
    std::string              m_quotationMarks;   ///< Characters that can enclose a string
    std::string              m_singleCharacters; ///< Characters that stand on their own
    std::vector<std::string> m_standalones;      ///< List of standalone strings

    // Parser state
    std::string              m_document;         ///< Test document that is parsed
    const char             * m_begin;            ///< Pointer to the beginning of the document
    const char             * m_end;              ///< Pointer to first character after the document
    const char             * m_current;          ///< Current position in the document
    unsigned int             m_line;             ///< Current line number (starts with 1)
    unsigned int             m_column;           ///< Current column number (starts with 1)
    bool                     m_lastCR;           ///< `true` if the last character read was `\r`, else `false`
};


} // namespace cppassist
