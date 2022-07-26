#include "frontend/Symbol_table.h"

std::string SymbolTable::get_line(int line_num) const{

    if (line_num < 1){

        return std::string{};
    }

    int line_begin = ends_of_lines[line_num - 1];
    int line_end = ends_of_lines[line_num];
    int line_size = line_end - line_begin;
    std::string line(line_size, '\0');

    fseek(src_file, line_begin, SEEK_SET);
    if (fread(line.data(), sizeof(char), line_size, src_file) != line_size){

        throw std::runtime_error{"Can't read feom file"};
    }

    return line;
}

void SymbolTable::add_line(const std::string& new_line){

    int bytes_wrote = fwrite(line.data(), sizeof(char), line.size(), src_file);
    if (bytes_wrote != line.size()){

        throw std::runtime_error{"Can't write to file"};
    }

    int prev_end = ends_of_lines.back();
    ends_of_lines.push_back(prev_end + bytes_wrote);
}

std::string SymbolTable::get_token(TokenHandle handle) const{

    auto&& token_it = tokens_table.find(handle);

    if (token_it == tokens_table.end()){

        return std::string{};
    }

    return token_it->second;
}

void SymbolTable::add_token(int line, int col, std::string token){

    TokenHandle new_handle{line, col};

    auto&& ret_val = tokens_table.insert({new_handle, token});

    if (!ret_val.second){

        std::string error{"Can't add token "};
        error.append(token);
        throw std::runtime_error{error};
    }
}