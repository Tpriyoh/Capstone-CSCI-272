// File       : FileHandler.h
// Author     : Ibrahim Jahangir
// Date       : 5/5/2026
// Course     : CSCI 272 - Object Oriented Programming
// Role       : Member 5 - File handling, CSV parsing, sorting, and binary search

#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

#include "Event.h"
#include "IntrusionEvent.h"
#include "MalwareEvent.h"

//this class is for my Member 5 part.
//i use it to load events from the csv file, save them back,
//and also help with sorting and searching by event ID.
class FileHandler {

public:

    //loads the events from a csv file and returns them as Event pointers.
    //i used Event* because IntrusionEvent and MalwareEvent both come from Event.
    static vector<Event*> loadEventsFromFile(string filename);

    //saves the current events back into a csv file.
    static void saveEventsToFile(string filename, const vector<Event*>& events);

    //sorts the events by event ID using bubble sort.
    //we picked bubble sort because our test file should not be too large.
    static void bubbleSortByEventID(vector<Event*>& events);

    //searches for an event ID using binary search.
    //this only works correctly after the events are sorted.
    static Event* binarySearchByEventID(vector<Event*>& events, string targetID);

private:

    //takes one csv line and turns it into either an IntrusionEvent or MalwareEvent.
    static Event* parseCSVLine(string line);

    //splits one csv line into separate fields using commas.
    static vector<string> splitCSVLine(string line);
};

#endif
