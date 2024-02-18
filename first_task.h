#ifndef FIRST_TASK_H
#define FIRST_TASK_H

#include <map>      
#include <fstream>  

// Define a struct to hold information about a type
struct InfoType
{
    std::string m_type;     
    std::string m_name;     
    std::string m_value;   
    size_t m_line;     
    size_t m_pos;           

    // Default constructor for InfoType struct
    InfoType();

    // Function to initialize InfoType struct members with provided values
    void init(const std::string&, const std::string&, const std::string&, const size_t&, const size_t&);
};

// Define a class to collect and process information from input files
class collect_types
{
public:
    explicit collect_types(const std::string&); // Constructor to initialize the class with an input file
    void start();   // Function to start processing the input file
    ~collect_types();   // Destructor to clean up resources

private:
    std::ifstream input_file;       // Input file stream
    std::ofstream output_file;      // Output file stream
    std::map<std::string, InfoType> m;  // Map to store information about types

    // Helper function to process a single line of input
    void OneLine(std::string&, size_t&);

    // Helper function to tokenize a string and extract information
    void token(std::string&, size_t&, size_t&);

    // Helper function to write information to the output file
    void write(InfoType&);

    // Helper function to handle cases where writing to the output file is not necessary
    void no_write(std::string&, size_t&, size_t&);

    // Function to modify a string by extracting the first character of each word
     std::string change(std::string str);

};



#endif // FIRST_TASK_H

