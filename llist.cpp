/*****************************************************************
//
//  NAME:        Zolbo Tomita
//
//  HOMEWORK:    Project 2
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        April 16th, 2021
//
//  FILE:        llist.cpp
//
//  DESCRIPTION:
//   Defines functions
//
****************************************************************/
#include <stdlib.h>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include "llist.h"

using namespace std;
ostream& operator<<(ostream&, const llist&);

/*****************************************************************
//
//  Function name: llist::llist
//
//  DESCRIPTION:   Constructer for llist.
//
//  Parameters:    None
//
//  Return values: None
//
****************************************************************/
llist::llist ()
{
    start = NULL;
    strcpy(filename, "records.txt");
    readfile();
}

/*****************************************************************
//
//  Function name: llist::llist
//
//  DESCRIPTION:   Constructer for llist.
//
//  Parameters:    (char []) filename : name of the file  
//
//  Return values: None
//
****************************************************************/
llist::llist (char filename[])
{
    start = NULL;
    strcpy(filename, filename);
    readfile();
}

/*****************************************************************
//
//  Function name: llist::~llist
//
//  DESCRIPTION:   Constructer for llist.
//
//  Parameters:    None
//
//  Return values: None
//
****************************************************************/
llist::~llist ()
{
    writefile();
    cleanup();
}

/*****************************************************************
//
//  Function name: addRecord
//
//  DESCRIPTION:   Adds records to the database.
//
//  Parameters:    (int) accountNumber : User inputted Account Number    
//                 (char []) name : User inputted name
//                 (char []) address: User inputted address
//
//  Return values: 0 : Record was added successfully 
//                 -1 : Record was not added
// 
****************************************************************/
int llist::addRecord (int accountNumber, char name[], char address[])
{
    record* tempRecord;
    record* current;
    record* prev;
    int checkAdd = -1;

    #ifdef DEBUG
        cout << "Debug: Entering addRecord method in llist.cpp.\n" << "Account Number: " << accountNumber << "\n" << "Name: " << name << "\n" << "Address: " << address << "\n" ;
    #endif

    current = start;
    prev = new record;
  
    if (current == NULL)
    {
        current = new record;
        current->accountno = accountNumber;
        strcpy(current->name, name);
        strcpy(current->address, address);
        this->start = current;        
        checkAdd = 0;        

    } else if (current->accountno > accountNumber)
    {
        prev->accountno = accountNumber;
        strcpy(prev->name, name);
        strcpy(prev->address, address);
        prev->next = current;
        current = prev;
        start = current;
        checkAdd = 0;
    } else if (current->accountno < accountNumber)
    {
        while (current->accountno < accountNumber)
        {
            prev = current;
            if (current->next == NULL)
            {
                tempRecord = new record;
                tempRecord->accountno = accountNumber;
                strcpy(tempRecord->name, name);
                strcpy(tempRecord->address, address);
                prev->next = tempRecord;
                checkAdd = 0;
            } else 
            {
                current = current->next;
            }
        }
        if (prev->accountno != accountNumber && checkAdd != 0)
        {
            tempRecord = new record;
            if(prev->next == NULL)
            {
                prev->next = tempRecord;
            } else
            {
                prev->next = tempRecord;
                tempRecord->next = current;
            }
            tempRecord->accountno = accountNumber;
            strcpy(tempRecord->name, name);
            strcpy(tempRecord->address, address);
        }
    }
    
    return checkAdd;
}

/*****************************************************************
//
//  Function name: printAllRecords
//
//  DESCRIPTION:   Prints all records in database.
//
//  Parameters:    None
//
//  Return values:  None
//
****************************************************************/
void llist::printAllRecords ()
{
    record* current = this->start;
  
    #ifdef DEBUG
        cout << "Debug: Entering printAllRecords method in llist.cpp.\n";
    #endif
    
    if(current == NULL)
    {
        cout << "There are no records in the database. \n";
    }
    while (current != NULL)
    {
        cout << "Account Number: " << current->accountno << "\n";
        cout << "Account Name: " << current->name << "\n";
        cout << "Account Address: " << current->address << "\n";
        cout << "\n";
        current = current->next;
    }
}

/*****************************************************************
//
//  Function name: operator
//
//  DESCRIPTION:   Prints all records in database.
//
//  Parameters:    (ostream&) os: output stream
//                 (llist&) newList: list of records
//
//  Return values:  ostream: output
//
****************************************************************/
ostream& operator<<(ostream& os, const llist& myList)
{
    record* current = myList.start;
  
    #ifdef DEBUG
        cout << "Debug: Entering operator method in llist.cpp\n";
    #endif
    
    while (current != NULL)
    {
        os << "Account Number: " << current->accountno << "\n";
        os << "Account Name: " << current->name << "\n";
        os << "Account Address: " << current->address << "\n";
        os << "\n";
        current = current->next;
    }
    
    return os;
}

/*****************************************************************
//
//  Function name: findRecord
//
//  DESCRIPTION:   Finds user inputted record
//
//  Parameters:    (int) accountNumber: User inputted Account Number
//
//  Return values:  0 : Record was found
//                 -1 : Record couldn't be found
//
****************************************************************/
int llist::findRecord (int accountNumber)
{
    record* current;
    int checkFind;
    
    #ifdef DEBUG
        cout << "Debug: Entering findRecord method in llist.cpp.\n" << "Account Number: " << accountNumber << "\n";
    #endif

    current = start;
   
    if (current == NULL)
    {
        checkFind = -1;
    } else 
    {
        while (current != NULL)
        {
            if(current->accountno == accountNumber)
            {
                cout << "Account Number: " << current->accountno << "\n";
                cout << "Account Name: " << current->name << "\n";
                cout << "Account Address: " << current->address << "\n";
                cout << "\n";
                checkFind = 0;
            }
            current = current->next;
        }
        if (checkFind != 0)
        {
            checkFind = 1;
        }
    }
    return checkFind;
}

/*****************************************************************
//
//  Function name: deleteRecord
//
//  DESCRIPTION:   Deletes user inputted record
//
//  Parameters:    (int) accountNumber: User inputted account number
//
//  Return values:  0 : Record deleted successfully
//                 -1 : Record could not be deleted
//
****************************************************************/
int llist::deleteRecord (int accountNumber)
{
    record* current;
    record* prev;
    record* tempRecord;
    int checkDelete;

    #ifdef DEBUG
        cout << "Debug: Entering deleteRecord method in llist.cpp.\n" << "Account Number: " << accountNumber << "\n";
    #endif

    current = this->start;

    if (current == NULL)
    {
        checkDelete = -1;
    } else if (current->accountno == accountNumber)
    {
        if(current->next == NULL)
        {
            delete current;
            start = NULL;
            checkDelete = 0;
        } else 
        {
            tempRecord = current->next;
            delete current;
            start = tempRecord;
            checkDelete = 0;
        }
    } else if (current->accountno < accountNumber)
    {
        while(current->accountno != accountNumber && current != NULL)
        {
            prev = current;
            current = current->next;
        }
        if(current->accountno == accountNumber)
        {
            if(current->next != NULL)
            {
                prev->next = current->next;
                delete current;
                checkDelete = 0;
            } else 
            {
                prev->next = NULL;
                delete current;
                checkDelete = 0;
            }
        }
    }
    return checkDelete;
}

/*****************************************************************
//
//  Function name: readfile
//
//  DESCRIPTION:   This reads the file before the program starts
//
//  Parameters:    None
//
//  Return values:  0 : Read successfully
//                  -1: Not read
//
****************************************************************/
int llist::readfile ()
{
    ifstream fileRead;
    string str;
    int accountNumber;
    char name[25];
    char address[50];
    int checkRead = 0;
    int count = 0;
    
    #ifdef DEBUG
        cout << "Debug: Entering readfile method in llist.cpp.\n";
    #endif

    fileRead.open("records.txt");

    if(fileRead.fail())
    {
        checkRead = -1;
    } else if (fileRead.good())
    {
        while (!fileRead.eof())
        {
            if(count == 0)
            {
                getline(fileRead, str);
                accountNumber = atoi(str.c_str());
                count++;
            } else if (count == 1)
            {
                getline(fileRead, str);
                strcpy(name, str.c_str());
                count++;
            } else if (count == 2)
            {
                getline(fileRead, str, '|');
                strcpy(address, str.c_str());
                addRecord(accountNumber, name, address);
                fileRead.ignore(1, '\n');
                count = 0;
            }
        }
        fileRead.close();
    }
    if(checkRead == 0)
    {
        cout << "Records have been loaded in.\n";
    } else if (checkRead == -1)
    {
        cout << "Records could not be loaded.\n";
    }
    return checkRead;
}

/*****************************************************************
//
//  Function name: writefile
//
//  DESCRIPTION:   This reads the file before the program starts
//
//  Parameters:    None
//
//  Return values:  0 : Wrote successfully
//                 -1 : Unable to be written
//
****************************************************************/
int llist::writefile ()
{
    ofstream fileWrite;
    record* current;
    int checkWrite = 0;
    
    #ifdef DEBUG
        cout << "Debug: Entering writefile method in llist.cpp.\n";
    #endif

    current = start;
    fileWrite.open("records.txt");

    if (fileWrite.fail())
    {
        checkWrite = -1;
        fileWrite.close();
    } else if (fileWrite.good())
    {
        while (current != NULL && checkWrite == 0)
        {
            fileWrite << current->accountno << "\n" << current->name << "\n" << current->address << "|\n";
            current = current->next;
        }
        fileWrite.close();        
    }
    return checkWrite;
}

/*****************************************************************
//
//  Function name: cleanup
//
//  DESCRIPTION:   Clears database.
//
//  Parameters:    None
//
//  Return values:  None
//
****************************************************************/
void llist::cleanup ()
{
    record* current;
    record* temp;

    #ifdef DEBUG
        cout << "Debug: Entering cleanup method in llist.cpp.\n";
    #endif

    current = start;
    while(current->next != NULL)
    {
        temp = current->next;
        delete current;
        current = temp;
    }
}
