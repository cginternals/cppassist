
#include <gmock/gmock.h>

#include <cppassist/fs/FilePath.h>


using namespace cppassist;


class FilePath_test : public testing::Test
{
public:
    FilePath_test()
    {
    }
};


TEST_F(FilePath_test, originalPath)
{
    const auto unixPath = "/home/user/path/to/file.ext";
    const auto winPath = "C:\\User\\Path\\To\\File.ext";

    auto unixFilePath = FilePath(unixPath);
    auto winFilePath = FilePath(winPath);

    ASSERT_EQ(unixPath, unixFilePath.originalPath());
    ASSERT_EQ(winPath, winFilePath.originalPath());

    unixFilePath.setPath("/home/user/path/");
    ASSERT_EQ("/home/user/path/", unixFilePath.originalPath());
}

TEST_F(FilePath_test, path)
{
    const auto unixPath = "/home/user/path/to/file.ext";
    const auto winPath = "C:\\User\\Path\\To\\File.ext";

    auto unixFilePath = FilePath(unixPath);
    auto winFilePath = FilePath(winPath);

    ASSERT_EQ(unixPath, unixFilePath.path());
    ASSERT_EQ("C:/User/Path/To/File.ext", winFilePath.path());

    unixFilePath.setPath("/home/user/path/");
    ASSERT_EQ("/home/user/path", unixFilePath.path());
}

TEST_F(FilePath_test, setPath)
{
    auto filePath = FilePath("/home/user/path/to/file.ext");
    filePath.setPath("/another/path/");

    ASSERT_EQ("/another/path/", filePath.originalPath());
    ASSERT_EQ("/another/path", filePath.path());
}

TEST_F(FilePath_test, baseName)
{
    auto unixFilePath = FilePath("/home/user/path/to/file.ext");
    auto winFilePath = FilePath("C:\\User\\Path\\To\\File.ext");

    ASSERT_EQ("file", unixFilePath.baseName());
    ASSERT_EQ("File", winFilePath.baseName());

    unixFilePath.setPath("/home/user/path/to/.file.ext");
    ASSERT_EQ(".file", unixFilePath.baseName());

    unixFilePath.setPath("/home/user/path/to/directory");
    ASSERT_EQ("directory", unixFilePath.baseName());

    unixFilePath.setPath("/home/user/path/to/directory/");
    ASSERT_EQ("directory", unixFilePath.baseName());

    unixFilePath.setPath("/home/user/path/to/directory.ext/");
    ASSERT_EQ("directory", unixFilePath.baseName());
}

TEST_F(FilePath_test, fileName)
{
    auto unixFilePath = FilePath("/home/user/path/to/file.ext");
    auto winFilePath = FilePath("C:\\User\\Path\\To\\File.ext");

    ASSERT_EQ("file.ext", unixFilePath.fileName());
    ASSERT_EQ("File.ext", winFilePath.fileName());

    unixFilePath.setPath("/home/user/path/to/.file.ext");
    ASSERT_EQ(".file.ext", unixFilePath.fileName());

    unixFilePath.setPath("/home/user/path/to/directory");
    ASSERT_EQ("directory", unixFilePath.fileName());

    unixFilePath.setPath("/home/user/path/to/directory/");
    ASSERT_EQ("directory", unixFilePath.fileName());

    unixFilePath.setPath("/home/user/path/to/directory.ext/");
    ASSERT_EQ("directory.ext", unixFilePath.fileName());
}

TEST_F(FilePath_test, extension)
{
    auto unixFilePath = FilePath("/home/user/path/to/file.ext");
    auto winFilePath = FilePath("C:\\User\\Path\\To\\File.ext");

    ASSERT_EQ("ext", unixFilePath.extension());
    ASSERT_EQ("ext", winFilePath.extension());

    unixFilePath.setPath("/home/user/path/to/directory/");
    ASSERT_EQ("", unixFilePath.extension());

    unixFilePath.setPath("/home/user/path/to/file");
    ASSERT_EQ("", unixFilePath.extension());
}

TEST_F(FilePath_test, directoryPath)
{
    auto unixFilePath = FilePath("/home/user/path/to/file.ext");
    auto winFilePath = FilePath("C:\\User\\Path\\To\\File.ext");

    ASSERT_EQ("/home/user/path/to/", unixFilePath.directoryPath());
    ASSERT_EQ("C:/User/Path/To/", winFilePath.directoryPath());

    unixFilePath.setPath("/home/user/path/to/directory");
    ASSERT_EQ("/home/user/path/to/", unixFilePath.directoryPath());

    unixFilePath.setPath("/home/user/path/to/directory/");
    ASSERT_EQ("/home/user/path/to/", unixFilePath.directoryPath());
}

TEST_F(FilePath_test, driveLetter)
{
    auto unixFilePath = FilePath("/home/user/path/to/file.ext");
    auto winFilePath = FilePath("C:\\User\\Path\\To\\File.ext");

    ASSERT_EQ("", unixFilePath.driveLetter());
    ASSERT_EQ("C", winFilePath.driveLetter());
}

TEST_F(FilePath_test, directoryPathPlusFileName)
{
    const auto unixPath = "/home/user/path/to/file.ext";
    const auto winPath = "C:\\User\\Path\\To\\File.ext";

    auto unixFilePath = FilePath(unixPath);
    auto winFilePath = FilePath(winPath);

    ASSERT_EQ(unixPath, unixFilePath.directoryPath() + unixFilePath.fileName());
    ASSERT_EQ("C:/User/Path/To/File.ext", winFilePath.directoryPath() + winFilePath.fileName());
}
