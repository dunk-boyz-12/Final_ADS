//
//  binaryFile.cpp
//  Final_ADS
//
//  Created by Nicholas Buras on 8/2/21.
//
#include <vector>

#include "binaryFile.hpp"

c_BinaryFile::c_BinaryFile() {
    this->totalEmployeeRecords = 0;
}

c_BinaryFile::~c_BinaryFile() {
    
}
/* ############################   PUBLIC FUNCTIONS   ############################ */
void c_BinaryFile::fileHandler(const char* inputFileName) {
    //make sure input is there
    this->p_checkInputFile(inputFileName);
    //get and sort(by department) employee records from file
    this->p_handleInput(inputFileName);
    //write sorted employee list to new binary file
    this->p_writeToFile(inputFileName);
}

/* ############################   PRIVATE FUNCTIONS   ############################ */
void c_BinaryFile::p_checkInputFile(const char* inputFileName) {
    struct stat fileInfo;
    int inputFileSize = stat(inputFileName, &fileInfo);
    if(fileInfo.st_size == 0){
        //input file is empty
        throw MyException("Input file is empty. Exiting...");
    }
}

void c_BinaryFile::p_handleInput(const char* inputFileName) {
    s_Record tempRecord;
    std::vector<s_Record> accounting;
    std::vector<s_Record> business;
    std::vector<s_Record> humanResources;
    std::vector<s_Record> sales;
    std::vector<s_Record> production;
    //open input file
    this->inputFile.open(inputFileName, std::ios::in|std::ios::binary);
    if(!this->inputFile.is_open()) {
        throw MyException("Input File could not be opened. Exiting...");
    } else {
        //sort by department as I read them the records from the file
        while (this->inputFile.read((char*)&tempRecord, RECORD_SIZE_BYTES)) {
            //std::cout << tempRecord.id << " " << tempRecord.department << " " << tempRecord.name << std::endl;
            switch (tempRecord.department) {
                case ACCOUNTING:
                    accounting.push_back(tempRecord);
                    break;
                case BUSINESS:
                    business.push_back(tempRecord);
                    break;
                case HUMAN_RESOURCES:
                    humanResources.push_back(tempRecord);
                    break;
                case SALES:
                    sales.push_back(tempRecord);
                    break;
                case PRODUCTION:
                    production.push_back(tempRecord);
                    break;
            }
            //inc total record count
            this->totalEmployeeRecords++;
        }
    }
    //close file
    this->inputFile.close();
    //update index array
    this->p_findIndexes(accounting, business, humanResources, sales, production);
    //update department totals array
    this->p_updateDepartmentTotals(accounting, business, humanResources, sales, production);
    //merge department lists into single sorted record list
    this->p_mergeDepartmentLists(accounting, business, humanResources, sales, production);
}

void c_BinaryFile::p_findIndexes(std::vector<s_Record>& accounting,std::vector<s_Record>& business,std::vector<s_Record>& humanResources,std::vector<s_Record>& sales,std::vector<s_Record>& production) {
    this->departmentIndexes[ACCOUNTING] = 0;
    this->departmentIndexes[BUSINESS] = accounting.size();
    this->departmentIndexes[HUMAN_RESOURCES] = this->departmentIndexes[BUSINESS] + business.size();
    this->departmentIndexes[SALES] = this->departmentIndexes[HUMAN_RESOURCES] + humanResources.size();
    this->departmentIndexes[PRODUCTION] = this->departmentIndexes[SALES] + sales.size();
}

void c_BinaryFile::p_mergeDepartmentLists(std::vector<s_Record>& accounting,std::vector<s_Record>& business,std::vector<s_Record>& humanResources,std::vector<s_Record>& sales,std::vector<s_Record>& production) {
    for(s_Record record: accounting){
        this->employeeRecords.push_back(record);
    }
    for(s_Record record: business){
        this->employeeRecords.push_back(record);
    }
    for(s_Record record: humanResources){
        this->employeeRecords.push_back(record);
    }
    for(s_Record record: sales){
        this->employeeRecords.push_back(record);
    }
    for(s_Record record: production){
        this->employeeRecords.push_back(record);
    }
}

void c_BinaryFile::p_updateDepartmentTotals(std::vector<s_Record>& accounting,std::vector<s_Record>& business,std::vector<s_Record>& humanResources,std::vector<s_Record>& sales,std::vector<s_Record>& production) {
    this->departmentTotals[ACCOUNTING] = accounting.size();
    this->departmentTotals[BUSINESS] = business.size();
    this->departmentTotals[HUMAN_RESOURCES] = humanResources.size();
    this->departmentTotals[SALES] = sales.size();
    this->departmentTotals[PRODUCTION] = production.size();
}

void c_BinaryFile::p_writeToFile(const char* inputFileName) {
    //create new file name
    this->outputBinaryFileName = "Sorted_"+(std::string)inputFileName;
    //create and open file
    this->outputBinaryFile.open(this->outputBinaryFileName, std::ios::out|std::ios::in|std::ios::binary);
    if(!outputBinaryFile.is_open()){
        throw MyException("Output File could not be opened. Exiting...");
    } else {
        //write to file
        this->outputBinaryFile.write((char*)&this->employeeRecords, RECORD_SIZE_BYTES*this->totalEmployeeRecords);
        //close file
        //this->outputBinaryFile.close();
    }
}

s_Record* c_BinaryFile::p_retrieveEmployee(int department, int offset) {
    s_Record* employeeRecord;
    int employeeNumber = this->departmentIndexes[department] + offset;
    //jump to beginning of open sorted file
    this->outputBinaryFile.seekg(std::ios::beg);
    //jump to employee
    this->outputBinaryFile.seekg(std::ios::beg+employeeNumber);
    this->outputBinaryFile.read((char*)&employeeRecord, RECORD_SIZE_BYTES);
    return employeeRecord;
}
