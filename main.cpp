#include <iostream>
#include "first_task.h"

int main(int argc, char* argv[]) {

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1; 
    }

    std::string filename = argv[1];
    collect_types obj(filename);
    obj.start();

    return 0; 
}

