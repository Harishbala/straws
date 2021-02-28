// Code credit : https://shaharmike.com/cpp/libclang/
// Code credit : https://bastian.rieck.me/blog/posts/2016/baby_steps_libclang_function_extents/
//To compile: clang++ libclang_cursor.cpp -o lcc -I/usr/local/Cellar/llvm/11.1.0/include/ --std=c++11 -L/usr/local/Cellar/llvm/11.1.0/lib -lclang

#include <iostream>
#include <clang-c/Index.h>
#include "directory.hpp"
using namespace std;

ostream& operator<<(ostream& stream, const CXString& str)
{
    auto c_ptr = clang_getCString(str);
    if (c_ptr != nullptr) {
        stream << c_ptr;
    }
    clang_disposeString(str);
    return stream;
}

struct Code_stats
{
    int class_count;
};

void analyze_code(const CXCursor& c)
{
    if (clang_getCursorKind(c) == CXCursor_ClassDecl) {
        cout << "Cursor '" << clang_getCursorSpelling(c) << "' of kind '"
        << clang_getCursorKindSpelling(clang_getCursorKind(c))
        << " ------- ";
        auto extent = clang_getCursorExtent(c);

        CXSourceLocation startLocation = clang_getRangeStart( extent );
        CXSourceLocation endLocation   = clang_getRangeEnd( extent );

        unsigned int startLine = 0, startColumn = 0;
        unsigned int endLine   = 0, endColumn   = 0;

        CXFile file;
        clang_getSpellingLocation( startLocation, &file, &startLine, &startColumn, nullptr );
        clang_getSpellingLocation( endLocation,   nullptr, &endLine, &endColumn, nullptr );

        auto file_full_path = clang_getFileName(file);	

        std::cout << " " << file_full_path <<"  line number start: " << startLine << ", end: " << endLine << " Total: "
        << endLine - startLine << "\n";


    } 
}
int main(int argc, char** argv)
{
    CXIndex index = clang_createIndex(0, 0);
    std::string code_path = "/Users/harish/Projects/straws/straws/dalgos";
    Directory dir(code_path);

    std::vector<std::string> file_entries;
    dir.get_file_entries(file_entries);
    for(const auto& entry : file_entries) {
        std::string file_path = code_path + "/" + entry;
        std::cout << file_path << '\n';

        if (entry.find(".cpp") != string::npos) {
            CXTranslationUnit unit = clang_parseTranslationUnit(
                index,
                file_path.c_str(), nullptr, 0,
                nullptr, 0,
                CXTranslationUnit_None);

              if (unit == nullptr)
              {
                cerr << "Unable to parse translation unit. Quitting." << endl;
              }

              CXCursor cursor = clang_getTranslationUnitCursor(unit);
              clang_visitChildren(
                cursor,
                [](CXCursor c, CXCursor parent, CXClientData client_data)
                {
                  analyze_code(c);
                  return CXChildVisit_Recurse;
                },
                nullptr);

                clang_disposeTranslationUnit(unit);
        }
    }
    clang_disposeIndex(index);
}
