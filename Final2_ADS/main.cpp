//
//  main.cpp
//  Final_ADS
//
//  Created by Nicholas Buras on 7/28/21.
//

#include <iostream>
#include <fstream>
#include <vector>

#include "binaryFile.hpp"


int main(int argc, const char * argv[]) {
    const char* inputFileName = argv[1];
    c_BinaryFile BF;
    //check inputFiles
    try {
        BF.fileHandler(inputFileName);
    } catch(MyException &error) {
        std::cout << error.what() << std::endl;
    } catch(std::exception &error) {
        std::cout << error.what() << std::endl;
    }
}

/*
 std::fstream myFile;
 record in;
 int totalRecords = 0;
 std::vector<record> V;
 
 myFile.open("/Users/nicholasburas/XcodeProjects/CSC310_ADS_Projects/Final_ADS/Final_ADS/binaryData/smallBinaryInput.dat", std::ios::in|std::ios::binary);
 
 if (!myFile.is_open()) {
     std::cout << "Fuck!\n";
 } else {
     //extern const int RECORD_SIZE_BYTES;
     //std::cout << RECORD_SIZE_BYTES << std::endl;
     //myFile.seekg(std::ios::beg);
     //std::cout << sizeof(in) << std::endl; //pads 2 bytes to structure to minimize memory bank reads
     //std::cout << sizeof(int) << std::endl;
     //std::cout << sizeof(int) << std::endl;
     //std::cout << sizeof(char[30]) << std::endl;
     //for(int i = 0; i < 10; i++){ //10 employees
     while(myFile.read((char*)&in, 38)) {
         //myFile.read((char*)&in, 38);
         std::cout << in.id << " " << in.department << " " << in.name << std::endl;
         totalRecords++;
         V.push_back(in);
     }
     std::cout << totalRecords << std::endl;
         //myFile.read((char*)&in, 38);
         //std::cout << in.id << " " << in.department << " " << in.name << std::endl;
         //myFile.seekg(std::ios::beg+((i+1)*38));
     //}
 }
*/
