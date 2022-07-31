// Code credit : https://shaharmike.com/cpp/libclang/
// Code credit : https://bastian.rieck.me/blog/posts/2016/baby_steps_libclang_function_extents/
//To compile: clang++ libclang_cursor.cpp -o lcc -I/usr/local/Cellar/llvm/11.1.0/include/ --std=c++11 -L/usr/local/Cellar/llvm/11.1.0/lib -lclang

#include <iostream>
#include <map>
#include <sstream>
#include <clang-c/Index.h>
#include "clang_helpers.h"
#include "directory.hpp"
using namespace std;

std::map<std::string, std::vector<std::string>> class_details;

struct Code_stats
{
    int class_count;
};

void analyze_code(const CXCursor& c, CXClientData client_data)
{
    if (clang_getCursorKind(c) == CXCursor_ClassDecl) {
        std::stringstream class_name;
        class_name << clang_getCursorSpelling(c);
        class_details[class_name.str()] = {};
        print_location(c);
    } 
    else {
        std::cout << clang_getCursorSpelling(c) << " - "
           << cursor_kind_to_string ( clang_getCursorKind(c) ) << '\n';
        print_location(c);

        auto parent_cursor = clang_getCursorSemanticParent(c);
        if (clang_getCursorKind(parent_cursor) == CXCursor_ClassDecl) {
            auto acc_spec = clang_getCXXAccessSpecifier(c);
            std::stringstream member_description{""};
            if (acc_spec == CX_CXXPublic) {
                member_description << "+ ";
            }
            else {
                member_description << "- ";
            }
            member_description << clang_getCursorSpelling(c); 

            std::stringstream parent_name;
            parent_name << clang_getCursorSpelling(parent_cursor);
            class_details[parent_name.str()].push_back(member_description.str());
        }
        if(clang_getCursorKind(c) == CXCursor_CompoundStmt) {
            auto extent = clang_getCursorExtent(c);

            CXSourceLocation startLocation = clang_getRangeStart( extent );
            CXSourceLocation endLocation   = clang_getRangeEnd( extent );

            CXTranslationUnit* pUnit = static_cast<CXTranslationUnit*>(client_data);
            CXSourceRange src_range = clang_getRange(startLocation, endLocation);

            CXToken* ppTokens = nullptr;
            unsigned int numToken = 0;

            clang_tokenize(*pUnit, src_range, &ppTokens, &numToken);
            std::cout << "Number of tokens :" << numToken << '\n';
            for (int i = 0; i < numToken; ++i) {
                CXToken* pToken = ppTokens + i;
                std::cout << "------------------- Token ------------------";
                std::cout << clang_getTokenSpelling(*pUnit, *pToken) << '\n';
            }
        }
    }
}

int main(int argc, char** argv)
{
    CXIndex index = clang_createIndex(0, 0);
    std::string code_path{};
    if (argc > 1) {
        code_path = std::string{argv[1]};
    }
    else {
        std::cout << "Missing code path\n";
        return 1;
    } 
    Directory dir(code_path);

    std::vector<std::string> file_entries;
    dir.get_file_entries(file_entries);
    for(const auto& entry : file_entries) {
        std::string file_path = code_path + "/" + entry;
	std::cout << "Processing file: " << entry << "\n";

        if (entry.find(".cpp") != string::npos ||
                entry.find(".hpp") != string::npos ||
                entry.find(".h") != string::npos ||
                entry.find(".c") != string::npos) {
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
                  analyze_code(c, client_data);
                  return CXChildVisit_Recurse;
                },
                static_cast<CXClientData>(&unit));

                clang_disposeTranslationUnit(unit);
        }
    }
    clang_disposeIndex(index);

    for (const auto& class_item : class_details) {
        std::cout << class_item.first << '\n';
        for (const auto& member_item : class_item.second) {
            std::cout << member_item << '\n';
        }
    }
}
