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
//  DATE:        April 9th, 2021
//
//  FILE:        llist.h
//
//  DESCRIPTION:
//   Declares functions
//
****************************************************************/

#ifndef llist_h
#define llist_h
#include "record.h"

class llist
{
private:
    record *    start;
    char        filename[16];
    int         readfile();
    int         writefile();
    void        cleanup();

public:
    llist();
    llist(char[]);
    ~llist();
    int addRecord(int, char [ ],char [ ]);
    int findRecord(int);
    friend std::ostream& operator<<(std::ostream&, const llist&);
    void printAllRecords();
    int deleteRecord(int);
};

#endif
