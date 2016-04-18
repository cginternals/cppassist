
#include <cppassist/io/filename.h>


namespace
{
#ifdef WIN32
    const std::string g_sep = "\\";
#elif __APPLE__
    const std::string g_sep = "/";
#else
    const std::string g_sep = "/";
#endif
	const std::string g_allSep = "/\\";

bool endsWith(const std::string & str, const std::string & ending)
{
    return str.find_last_of(ending) == str.size() - 1;
}

} // namespace


namespace iozeug
{


std::string getBaseName(const std::string & filePath)
{
    auto i = filePath.find_last_of(g_allSep);

    std::string fileName = filePath;

    if (i == std::string::npos)
    {
        fileName = filePath.substr(++i);
    }

    while (fileName.length() > 0 && fileName[0] == '.') // note: filename might start with '.'
        fileName = fileName.substr(1);

    i = fileName.find_last_not_of(".");

    return i == fileName.npos ? fileName : fileName.substr(--i);
}

std::string getPath(const std::string & filePath)
{
    auto i = filePath.find_last_of(g_allSep);
    return i == filePath.npos ? "" : filePath.substr(0, i);
}

std::string getExtension(const std::string & filename)
{
    // [TODO] What about .tar.gz? Maybe better use the first occurence, not the last?

    size_t pos = filename.find_last_of('.');

    if (pos == std::string::npos)
        return std::string();

    return filename.substr(pos+1);
}

std::string removeTrailingPathSeparator(const std::string & path)
{
    auto returnPath = path;

    while (returnPath.size() > 0 && (endsWith(returnPath, g_allSep)))
    {
        returnPath = returnPath.substr(0, returnPath.size() - 1);
    }

    return returnPath;
}

std::string ensurePathSeparatorEnding(const std::string & path)
{
	if (endsWith(path, g_allSep))
	{
		return path;
	}

	auto i = path.find_last_of(g_allSep);

	if (i == std::string::npos)
	{
		return path + g_sep;
	} else {
		return path + path[i];
	}
}


} // namespace iozeug
