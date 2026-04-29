#include <gtest/gtest.h>
using namespace std;

#include "utils.h"
#include "custom_exceptions.h"

TEST(TestUtilsFindString, test_Unit_Utils_findString_basicStringFound_01)
{
    const string text_input = "basic search_string text";
    const string pattern_input = "search_string";

    EXPECT_TRUE(findString(text_input, pattern_input));
}

TEST(TestUtilsFindString, test_Unit_Utils_findString_basicStringNotFound_02)
{
    const string text_input = "basic search_string text";
    const string pattern_input = "no_str";

    EXPECT_FALSE(findString(text_input, pattern_input));
}

TEST(TestUtilsFindString, test_Unit_Utils_findString_basicEmptyText_03)
{
    const string text_input = "";
    const string pattern_input = "no_str";

    EXPECT_THROW(findString(text_input, pattern_input), ExceptionInFunction);
}

TEST(TestUtilsValidateFile, test_Unit_Utils_ValidateFile_basicOkFile_01)
{
    const string pathInput = "/mnt/d/Janak/Codes/grep_cli/file.txt";

    EXPECT_TRUE(validate_file(pathInput));
}

TEST(TestUtilsValidateFile, test_Unit_Utils_ValidateFile_EmptyFilePath_02)
{
    const string pathInput = "";

    EXPECT_THROW(validate_file(pathInput), ExceptionInFunction);
}

TEST(TestUtilsValidateFile, test_Unit_Utils_ValidateFile_NoPermissionToReadFile_03)
{
    const string pathInput = "~/file_not_readable.txt";

    EXPECT_THROW(validate_file(pathInput), ExceptionInFunction);
}

TEST(TestUtilsValidateFile, test_Unit_Utils_ValidateFile_IsDir_04)
{
    const string pathInput = "/mnt/d/Janak/Codes/grep_cli";

    EXPECT_THROW(validate_file(pathInput), ExceptionInFunction);
}

TEST(TestUtilsValidateFile, test_Unit_Utils_ValidateFile_differentExtension_05)
{
    const string pathInput = "/mnt/d/Janak/Codes/grep_cli/file.docx";

    EXPECT_THROW(validate_file(pathInput), ExceptionInFunction);
}

TEST(TestUtilsOpenFile, test_Unit_Utils_OpenFile_BasicTest_01)
{
    const string pathInput = "/mnt/d/Janak/Codes/grep_cli/file.txt";

    ifstream* expected = new ifstream(pathInput);
    ifstream* output = openFile(pathInput);

    EXPECT_EQ(expected, output);
}