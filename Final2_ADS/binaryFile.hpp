//
//  binaryFile.hpp
//  Final_ADS
//
//  Created by Nicholas Buras on 8/2/21.
//

#ifndef binaryFile_hpp
#define binaryFile_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sys/stat.h>
#include "customErrorClass.h"

const int RECORD_SIZE_BYTES = 38;

enum e_Departments {
    ACCOUNTING = 0,
    BUSINESS = 1,
    HUMAN_RESOURCES = 2,
    SALES = 3,
    PRODUCTION = 4
};

struct s_Record {
    int department;
    int id;
    char name[30];
};

class c_BinaryFile {
public:
    c_BinaryFile();
    ~c_BinaryFile();
    
    void fileHandler(const char*);
    void createOutput();
private:
    //vars
    std::ifstream inputFile;
    std::fstream outputBinaryFile;
    int totalEmployeeRecords;
    std::vector<s_Record> employeeRecords;
    int departmentTotals[5];
    int departmentIndexes[5];
    std::string departmentNames[5] = {"Accounting","Business","Human Resources","Sales","Production"};
    std::string outputBinaryFileName;
    
    //methods
    void p_checkInputFile(const char*);
    void p_handleInput(const char*);
    void p_writeToFile(const char*);
    void p_mergeDepartmentLists(std::vector<s_Record>&,std::vector<s_Record>&,std::vector<s_Record>&,std::vector<s_Record>&,std::vector<s_Record>&);
    void p_findIndexes(std::vector<s_Record>&,std::vector<s_Record>&,std::vector<s_Record>&,std::vector<s_Record>&,std::vector<s_Record>&);
    void p_updateDepartmentTotals(std::vector<s_Record>&,std::vector<s_Record>&,std::vector<s_Record>&,std::vector<s_Record>&,std::vector<s_Record>&);
    
    s_Record* p_retrieveEmployee(int,int);
    void p_printEmployeeName();
    void p_updateRecordName();
    void p_deleteRecord();
    void p_printEmployeeRange(int,int);
};

#endif /* binaryFile_hpp */
