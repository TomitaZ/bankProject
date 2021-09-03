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
//  DATE:        February 9th, 2021
//
//  FILE:        user_interface.cpp
//
//  DESCRIPTION: User interface
//
//
****************************************************************/

#include <cstring>
#include <iostream>
#include "llist.h"

using namespace std;

int getOption();
int add(llist &);
void printall(llist &);
int find(llist &);
int deleteRecord(llist &);
int getAccountNumber();
void getName(char[], int);
void getAddress(char[], int);

/*****************************************************************
//
//  Function name: main
//
//  DESCRIPTION:   Directs user through user interface
//
//  Parameters:    int argc : amount of argv array
//                 char *argv[] : inputs
//
//  Return values:  0 : application has been quit
//
****************************************************************/
int main(int argc, char *argv[])
{
    llist myList;
    int checkQuit = 1;
    int optionSelected;
  
    cout << "Welcome to Aspen the bank of the future!";
    cout << "\n";

    do
    {
        optionSelected = getOption();
        if(optionSelected == 1)
        {
            add(myList);
        } else if (optionSelected == 2)
        {
           // printall(myList);
           cout << myList;
        } else if (optionSelected == 3)
        {
            find(myList);
        } else if (optionSelected == 4)
        {
            deleteRecord(myList);
        } else if(optionSelected == 0)
        {
            checkQuit = 0;
        }
        optionSelected = -1;
    } while (checkQuit != 0);

    return 0;
}  

/*****************************************************************
//
//  Function name: getOption
//
//  DESCRIPTION:   Prompts the user with five options to choose from and allows them to navigate application
//
//  Parameters:    None
//
//  Return values:  0: quit option selected
//                  1: add option selected
//                  2: printall option selected
//                  3: find option selected
//                  4: delete option selected
//
****************************************************************/
int getOption()
{
    string str;
    char option[20];
    int optionLength;
    int optionSelected = -1; 
   
    #ifdef DEBUG
        cout << "Debug: Entering the getOption method in user_interface.cpp \n";
    #endif

    cout << "--------------------------------------------------------\n";
    cout << "Select an option by typing the corresponding name.\n";
    cout << "add: Add a new record in the database\n";
    cout << "printall: Print all records in database\n";
    cout << "find: Find record(s) with a specified account number\n";
    cout << "delete: Delete existing record(s) from the database\n";
    cout << "quit: Quit the program\n";
    cout << "--------------------------------------------------------\n";

    cout << "Choose option: ";
    cin >> str;
    strcpy(option, str.c_str());
    optionLength = strlen(option);

    while (optionSelected < 0)
    {
        if(strncasecmp(option, "add", optionLength) == 0 && optionLength <= 3)
        {
            optionSelected = 1;
        } else if (strncasecmp(option, "printall", optionLength) == 0 && optionLength <= 8)
        {
            optionSelected = 2;
        } else if (strncasecmp(option, "find", optionLength) == 0 && optionLength <= 4)
        {
            optionSelected = 3;
        } else if (strncasecmp(option, "delete", optionLength) == 0 && optionLength <= 6)
        {
            optionSelected = 4;
        } else if (strncasecmp(option, "quit", optionLength) == 0 && optionLength <= 4)
        {
            optionSelected = 0;
        } else 
        {
            cout << "You have inputted an invalid entry. Please try again. \n";
        }
    }
    return optionSelected;
}

/*****************************************************************
//
//  Function name: add
//
//  DESCRIPTION:   Guides the user through the add option
//
//  Parameters:    (llist &) myList : list of records
//
//  Return values:  0: add has been completed
//                  -1: record could not be added
//
****************************************************************/
int add(llist &myList)
{
    int addResult;
    int accountNumber;
    char name[25];
    char address[50];
    
    #ifdef DEBUG
        cout << "Debug: Entering the add method in user_interface.cpp.\n"; 
    #endif

    accountNumber = getAccountNumber();
    getName(name, 25);
    getAddress(address, 50);
    addResult = myList.addRecord(accountNumber, name, address);
    if(addResult == 0)
    {
        cout << "Record has been added successfully.\n";
    } else if (addResult == -1)
    {
        cout << "Record could not be added. \n";
    }
    
     return addResult;
}

/*****************************************************************
//
//  Function name: printall
//
//  DESCRIPTION:   Guides the user through the printall option
//
//  Parameters:    (llist) myList : list of records
//
//  Return values:  None
//
****************************************************************/
void printall(llist &myList)
{
    #ifdef DEBUG
        cout << "Debug: Entering the printall method in user_interface.cpp.\n";
    #endif
    
    myList.printAllRecords();
}

/*****************************************************************
//
//  Function name: find
//
//  DESCRIPTION:   Guides the user through the find option
//
//  Parameters:    (llist) myList : list of records
//
//  Return values:  0: find has been completed
//                  -1: There are no records in the database
//                  1: record could not be found
//
****************************************************************/
int find(llist &myList)
{
    int checkFind;
    int accountNumber;
    
    #ifdef DEBUG
        cout << "Debug: Entering the find method in user_interface.cpp.\n";
    #endif
   
    accountNumber = getAccountNumber();
    checkFind = myList.findRecord(accountNumber);
    
    if(checkFind == -1)
    {
        cout << "There are no records in the database. Select Add to add a record.\n";
    } else if(checkFind == 0)
    {
        cout << "Record Found Successfully...\n";
    } else if(checkFind == 1)
    {
        cout << "Record could not be found. \n";
    }

    return checkFind;
}

/*****************************************************************
//
//  Function name: delete
//
//  DESCRIPTION:   Guides the user through the delete option
//
//  Parameters:    (llist) myList : list of records
//
//  Return values:  0: delete has been completed
//
****************************************************************/
int deleteRecord(llist &myList)
{
    int checkDelete;
    int accountNumber;
    
    #ifdef DEBUG
        cout << "Debug: Entering the deleteRecord method in user_interface.cpp\n";
    #endif
    
    accountNumber = getAccountNumber();

    checkDelete = myList.deleteRecord(accountNumber);
    if (checkDelete == -1)
    {
        cout << "There are no records to be deleted.\n";
    } else if (checkDelete == 0)
    {
        cout << "Record was deleted successfully";
    } else if (checkDelete == 1)
    {
        cout << "Record could not be found.";
    }
    
    return checkDelete;
}

/*****************************************************************
//
//  Function name: getAccountNumber
//
//  DESCRIPTION:   Gets account number from the user
//
//  Parameters:    None
//
//  Return values:  accountNumber: the account number inputted
//
****************************************************************/
int getAccountNumber()
{
   int accountNumber;
   
   #ifdef DEBUG
       cout << "Debug: Entering getAccountNumber method in user_interface.cpp\n";
   #endif
   
   cout << "What is the account number?: ";
   cin >> accountNumber;
   while(accountNumber < 0)
   {
       cout << "The account number you inputted is invalid.\n";
       cin.clear();
       cin >> accountNumber;
   }
   return accountNumber;
}

/*****************************************************************
//
//  Function name: getName
//
//  DESCRIPTION:   Gets name from the user
//
//  Parameters:    char name[]: array to hold user inputted name
//                 int length : length of the array
//
//  Return values:  None
//
****************************************************************/
void getName (char name[], int length)
{
    string str;
    
    #ifdef DEBUG
        cout << "Debug: Entering getName method in user_interface.cpp\n";
    #endif

    cout << "What is your name?: ";
    cin.ignore(1, '\n');
    getline(cin, str);
    strcpy(name, str.c_str());
}

/*****************************************************************
//
//  Function name: getAddress
//
//  DESCRIPTION:   Gets name from the user
//
//  Parameters:    char address[] : array to hold user inputted address
//                 int length : length of the array
//
//  Return values:  None
//
****************************************************************/
void getAddress (char address[], int length)
{
    char line;
    int i = 0;
    
    #ifdef DEBUG
        cout << "Debug: Entering getAddress in user_interface.cpp\n";
    #endif

    cout << "When you are done typing your address put \"|\".\n";
    cout << "What is your address?: ";
    
    while ((line = cin.get()) != '|')
    {
        address[i++] = line;
    }
    
    cout << "\n";
}
