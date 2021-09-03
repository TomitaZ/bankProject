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
//  FILE:        record.h
//
//  DESCRIPTION:
//   Declares variables.
//
****************************************************************/

#ifndef record_h
#define record_h
int f(int a);

struct record
{
    int                accountno;
    char               name[25];
    char               address[50];
    struct record*     next;
};

#endif

