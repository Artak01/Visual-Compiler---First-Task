#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <iomanip>  
#include <sstream>
#include <algorithm> 


int count_words_in_stringstream(std::stringstream& s);
std::string change(std::string);

struct info{
    std::string type;
    std::string value;
    int line;
    int pos;
};

int main()
{
    std::ifstream input_file("text.txt");
    if (!input_file.is_open()){
        throw std::invalid_argument("Don't open input file");
    }

    std::ofstream output_file("result.txt");
    std::ofstream output_file1("typeInfo.txt");

    output_file << std::setw(18) << std::left << "Type" 
    << std::setw(18) << std::left << " Value" 
    << std::setw(18) << std::left << "Name" 
    << std::setw(18) << std::left << "Line" 
    << std::setw(18) << std::left << "Pos" 
    << std::endl;
; 
    output_file << std::endl << std::endl;


    std::vector<std::string> AllTypes {"int", "short", "long", "long long", "float", "double", "long double", "char", "wchar_t", "bool", "long int",
    "long long int", "short int", "const int", "const char","const float", "const double", "const bool", "const long","const long long", "const short",
    "const long double", "const wchar_t", "unsigned int", "unsigned char", "unsigned float", "unsigned double", "unsigned long long", "unsigned wchar_t",
    "unsigned short", "unsigned long double", "unsigned long", "unsigned bool", "signed int", "signed char", "signed float", "signed double", 
    "signed long long", "signed wchar_t", "signed short", "signed long double", "signed long", "const unsigned int", "const unsigned char", 
    "const unsigned float", "const unsigned double", "const unsigned long long", "const unsigned wchar_t", "const unsigned short", 
    "const unsigned long double", "const unsigned long", "const unsigned bool", "const signed int", "const signed char", "const signed float", 
    "const signed double", "const signed long long", "const signed wchar_t", "const signed short", "const signed long double", "const signed long int", 
    "const signed long long int", "const unsigned long int", "const unsigned long long int", "size_t", "const size_t" };   
    
    std::map<std::string, info> m;
    
    int line = 0;
    std::string oneline = "";
    while(std::getline(input_file, oneline), !input_file.eof()){
        bool b = false;
        if (oneline[oneline.size() - 1] != ';'){
            b = true;
        }
        
        int pos = 0;
        if (b){
            std::string tmp1 = "";
            std::getline(input_file, tmp1, ';');
            oneline += tmp1;
            oneline += ';';
        }
        std::string str = "";
        std::istringstream ssi(oneline);
        while(std::getline(ssi, str, ';'), !ssi.eof()){ 
        
        std::vector<std::string> vec;
        std::stringstream s(str);
        std::string tmp;
        bool flag = false;
        int size = 0;
        while (s >> tmp){
            ++size;
            vec.push_back(tmp);
            if (tmp == "="){
                flag = true;
            }
        }
        
        std::string tmp_name = "";
        std::string tmp_value = "";
        std::string tmp_type = "";
        if (size > 1){
            if (flag) {
                tmp_name = vec[size - 3];
                tmp_value = vec[size - 1];
                for (int i = 0; i < size - 3; ++i) {
                    tmp_type += vec[i] + " ";
                }
                tmp_type[tmp_type.size() - 1] = '\0';
            } else {
                tmp_name = vec[size - 1];
                tmp_value = "GARBAGE";
                for (int i = 0; i < size - 1; ++i) {
                    tmp_type += vec[i] + " ";
                }
                tmp_type[tmp_type.size() - 1] = '\0';
            }
        auto it = std::find(AllTypes.begin(), AllTypes.end(), tmp_type);
            if (it == AllTypes.end()){
               tmp_type = "Undefine";
            }


        } else {
            tmp_name = vec[size - 1];
            bool b = false;
            for (auto el : m){
                if(el.first == tmp_name){
                   b = true;
                   output_file << std::setw(18) << std::left << change(el.second.type) 
                   << std::setw(18) << std::left << el.second.value 
                   << std::setw(18) << std::left << el.first 
                   << std::setw(18) << std::left << el.second.line 
                   << std::setw(18) << std::left << el.second.pos 
                   << std::endl;  
                 break;
                 }
            }
            if (!b){
                output_file << std::setw(18) << std::left << "-" 
                << std::setw(18) << std::left << "-" 
                << std::setw(18) << std::left << tmp_name 
                << std::setw(18) << std::left << line 
                << std::setw(18) << std::left << pos 
                << std::endl;
            }
            ++pos;
            continue;
        }

        info ob {tmp_type, tmp_value, line, pos};
        m[tmp_name] = ob;
        ++pos;
        }
        ++line;
    }

    
    for (auto el : AllTypes){
        output_file1 << el << "  val" << std::endl;
    }

    input_file.close();
    output_file.close();
    output_file1.close();
    return 0;
}




std::string change(std::string str)
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

int count_words_in_stringstream(std::stringstream& s) {
    int word_count = 0;
    std::string word;
    while (s >> word) {
        ++word_count;
    }
    return word_count;
}

