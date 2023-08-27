/* 
Tuan Luong
Use to generate waypoints.txt file for use with BolderFlightSystem SPAARO framework.
This allows for persistent storage of flight plans
*/

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

/* Union for wp params*/
union wp_param_type{
  int i;
  float f;
  uint8_t bytes[4];
};

void write_union(uint8_t byte[4], FILE *file_){
  /*
  Function to write 4 bytes to a file. For convenience
  */
  fwrite(byte, 1, 4, file_);
}

int main(int argc, char** argv){
    /* Input file name */
    std::string input_file_name(argv[1]);

    /* Count number of line */
    int num_line = 0;
    std::string line;

    std::ifstream reader(input_file_name.c_str());

    if (!reader){
        std::cout << "There was an error opening file" << std::endl;
        return -1;
        }

    
    while (!reader.eof()){
        getline(reader, line);
        num_line++;
        }

    std::vector<std::vector<std::string>> content;
	std::vector<std::string> row;
	std::string word;
    std::fstream input(input_file_name.c_str(), std::ios::in);
    while(getline(input, line)){
        row.clear();
        std::stringstream str(line);
        while(getline(str, word, ',')){
            row.push_back(word);
        }
        content.push_back(row);
    }

    /* Create the output file */
    std::string output_file_name = "waypoints.txt";
    FILE *output = fopen(output_file_name.c_str(), "wb");
    if (!output) {
        std::cerr << "ERROR: Unable to open output file." << std::endl;
        return -1;
    }

    wp_param_type chunk_;
    chunk_.i = num_line;
    write_union(chunk_.bytes, output);
    /* Write some padding data. Not used for flight */
    chunk_.i = 3;
    write_union(chunk_.bytes, output);
    chunk_.i = 16;
    write_union(chunk_.bytes, output);
    chunk_.i = 15000000;
    write_union(chunk_.bytes, output);
    chunk_.i = 15000000;
    write_union(chunk_.bytes, output);
    chunk_.f = 1.0f;
    write_union(chunk_.bytes, output);
    
    
    //std::cout<<content.size();
    for (uint32_t i = 0; i < content.size(); i++){
        chunk_.i = 3;
        write_union(chunk_.bytes, output);
        chunk_.i = 16;
        write_union(chunk_.bytes, output);
        for(uint32_t j = 0; j < content[i].size(); j++){
            if (j < 2){
                chunk_.i = int(std::stof(content[i][j]) * 10000000);
                write_union(chunk_.bytes, output);
            }
            else{
                chunk_.f = std::stof(content[i][j]);
                write_union(chunk_.bytes, output);
            }
        }
    }
}


