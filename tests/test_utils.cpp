#include <gtest/gtest.h>
#include <sstream>
#include <iostream>
#include <fstream>
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

TEST(TestUtilsOpenFile, test_Unit_Utils_OpenFile_ContentCheck_Basic_01)
{
    const string pathInput = "/mnt/d/Janak/Codes/grep_cli/file.txt";
    ifstream output = openFile(pathInput);

    string firstLine;
    getline(output, firstLine);

    EXPECT_EQ(firstLine, "I found the search_string in the file.\r");
}

TEST(TestUtilsReturnLine, test_Unit_Utils_ReturnLine_BasicTest_01)
{
    const string pathInput = "/mnt/d/Janak/Codes/grep_cli/file.txt";
    vector<string> expectedOutput = {"I found the search_string in the file.\r", "Another line also contains the search_string.\r"};

    // 4. Compare the captured string
    EXPECT_EQ(returnLine(pathInput, "search_string", false), expectedOutput);
}

TEST(TestStdInput, test_Unit_StdInput_InjectedStreams)
{
    std::stringstream input_stream;
    input_stream << "apple pie\n"
                 << "banana bread\n"
                 << "pineapple juice\n"
                 << "orange soda";

    std::stringstream output_stream;
    std::string pattern = "apple";

    vector<string> output = stdInput(pattern, false, input_stream, output_stream);

    vector<string> expected = {"apple pie", "pineapple juice"};

    EXPECT_EQ(output, expected);
}

TEST(TestWriteToFile, test_Unit_writeToFile_Basic_01)
{
    string path = "/mnt/d/Janak/Codes/grep_cli/file.txt";
    vector<string> input = {"I found the search_string in the file.\r", "Another line also contains the search_string.\r"};

    string line;
    fstream fs(path);

    getline(fs, line);
    EXPECT_EQ(line, input[0]);
}

TEST(TestWriteToFile, test_Unit_writeToFile_Basic_01)
{
    string path = "/mnt/d/Janak/Codes/grep_cli/file.txt";
    vector<string> input = {"I found the search_string in the file.\r", "Another line also contains the search_string.\r"};

    string line;
    fstream fs(path);

    getline(fs, line);
    EXPECT_EQ(line, input[0]);
}

TEST(TestconvertToLowerCase, test_Unit_ConvertToLowerCase_Basic_01)
{
    string input = "HuLLu";
    string output = convertToLowerCase(input);
    string expected = "hullu";

    EXPECT_EQ(output, expected);
}

TEST(TestconvertToLowerCase, test_Unit_ConvertToLowerCase_Basic_01)
{
    string input = "";
    string output = convertToLowerCase(input);

    EXPECT_THROW(output, ExceptionInFunction);
}