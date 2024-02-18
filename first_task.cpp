#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <iomanip>  
#include <sstream>
#include <algorithm>
#include "first_task.h"

// Default constructor for InfoType struct
InfoType::InfoType()
{
    m_type = "";
    m_name = "";
    m_value = "";
    m_line = 0;
    m_pos = 0;
}

// Initialize InfoType struct with provided values
void InfoType::init(const std::string& type, const std::string& name, const std::string& value,const size_t& line, const size_t& pos)
{
    m_type = type;
    m_name = name;
    m_value = value;
    m_line = line;
    m_pos = pos;
}

// Destructor for collect_types class, closes input and output files if open
collect_types::~collect_types()
{
    if (input_file.is_open()) {
        input_file.close();
    }
    if (output_file.is_open()) {
        output_file.close();
    }
}

// Constructor for collect_types class, initializes input and output files
collect_types::collect_types(const std::string& in_f)
    : input_file{in_f}
    , output_file {"result.txt"}
{
    // Write column headers to output file if it's open
    if (output_file.is_open()) {
        output_file << std::setw(18) << std::left << "Type" 
                    << std::setw(18) << std::left << "Value" 
                    << std::setw(18) << std::left << "Name" 
                    << std::setw(18) << std::left << "Line" 
                    << std::setw(18) << std::left << "Pos" 
                    << "\n\n";
    }
}

// Starts processing the input file
void collect_types::start()
{
    if (!input_file.is_open()) {
        std::cout << "No such file exists" << std::endl;
        return;
    }
    std::string tmp_line = "";
    size_t line = 0;
    while (getline(input_file, tmp_line), !input_file.eof()) {
        // Check if the line needs to be concatenated with the next line
        bool b = false;
        if (tmp_line[tmp_line.size() - 1] != ';'){
            b = true;
        }
        if(b){
            std::string tmp_str = "";
            std::getline(input_file, tmp_str, ';');
            tmp_line += tmp_str;
        }
        // Process the concatenated line
        OneLine(tmp_line, line);
        ++line;
    }
}

// Process a single line of input
void collect_types::OneLine(std::string& str, size_t& line)
{
    std::istringstream iss(str);
    size_t pos = 0;
    std::string word;
    while(std::getline(iss, word, ';')){
        // Tokenize the line and process each token
        token(word, line, pos);
        ++pos;
    }
}

// Tokenize a string and extract type, name, and value information
void collect_types::token(std::string& str, size_t& line, size_t& pos)
{
    std::stringstream s(str);
    std::vector<std::string> vec;
    std::string t = "";
    bool flag = false;
    size_t size = 0;
    while(s >> t){
        vec.push_back(t);
        if (t == "="){
            flag = true;
        }
        ++size;
    }
    std::string tmp_name = "";
    std::string tmp_value = "";
    std::string tmp_type = "";
    if (size > 1){
        if (flag) {
            // Extract type, name, and value from tokens
            tmp_name = vec[size - 3];
            tmp_value = vec[size - 1];
            for (int i = 0; i < size - 3; ++i) {
                tmp_type += vec[i] + " ";
            }
            tmp_type[tmp_type.size() - 1] = '\0';
         } else {
            // No value provided, treat as "GARBAGE"
            tmp_name = vec[size - 1];
            tmp_value = "GARBAGE";
            for (int i = 0; i < size - 1; ++i) {
                tmp_type += vec[i] + " ";
            }
            tmp_type[tmp_type.size() - 1] = '\0';
         } 
         } else {
            // No type provided, check if it's already processed
            tmp_name = vec[size - 1];
            bool b = false;
            for (auto el : m){
                if (el.first == tmp_name){
                    write(el.second);
                    b = true;
                }
            }
            // If not processed, write to output file
            if (!b){
                no_write(tmp_name, line, pos);
            }
            return;
         }
        // Initialize InfoType object with extracted information
        InfoType ob;
        ob.init(tmp_type, tmp_name, tmp_value, line, pos);
        // Store InfoType object in map
        m[tmp_name] = ob;
}

// Write InfoType information to output file
void collect_types::write(InfoType& ob){
    output_file << std::setw(18) << std::left << change(ob.m_type) 
                   << std::setw(18) << std::left << ob.m_value 
                   << std::setw(18) << std::left << ob.m_name
                   << std::setw(18) << std::left << ob.m_line 
                   << std::setw(18) << std::left << ob.m_pos 
                   << std::endl; 
}

// Write placeholder information to output file
void collect_types::no_write(std::string& tmp_name, size_t& line, size_t& pos)
{
    output_file << std::setw(18) << std::left << "-" 
                << std::setw(18) << std::left << "-" 
                << std::setw(18) << std::left << tmp_name 
                << std::setw(18) << std::left << line 
                << std::setw(18) << std::left << pos 
                << std::endl;
}

// Modify a string by extracting the first character of each word
std::string collect_types::change(std::string str)
{
    std::string tmp = "";
    std::string t {};
    int i = 0;
    std::stringstream s(str);

    while (s >> t) {
        tmp += t[0];
    }
    return tmp;
}

