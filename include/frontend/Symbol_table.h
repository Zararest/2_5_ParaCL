#pragma once
#include <unordered_map>
#include <vector>
#include <string>



namespace ParaCL{

class TokenHandle{

    std::pair<int, int> file_pos;

public:

    TokenHandle(int line, int col): file_pos{line, col}{}    
    TokenHandle(): TokenHandle{-1, -1}{}

    bool operator ==(TokenHandle rhs) const{

        return file_pos == rhs.file_pos;
    }

    int get_line() const{

        return file_pos.first;
    }

    int get_col() const{

        return file_pos.second;
    }
};
}

template<>
struct std::hash<ParaCL::TokenHandle>{

    std::size_t operator ()(const ParaCL::TokenHandle& token) const{

        return std::hash<int>()(token.get_col()) | std::hash<int>()(token.get_line());
    }
};

namespace ParaCL{

class SymbolTable{

    std::unordered_map<TokenHandle, std::string> tokens_table;
    std::vector<int> ends_of_lines;
    FILE* src_file;

public:

    SymbolTable(){

        src_file = tmpfile();
        ends_of_lines.push_back(0);
    }

    SymbolTable(const SymbolTable&) = delete;
    
    ~SymbolTable(){

        fclose(src_file);
    }
    
    std::string get_line(int line_num) const;
    void add_line(const std::string& new_line);

    std::string get_token(TokenHandle handle) const;
    void add_token(int line, int col, std::string token);
};
}