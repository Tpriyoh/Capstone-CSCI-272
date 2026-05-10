// Flie: EventManager.cpp
// Author: Miguel Llapa
// Date: 4/29/2026
// Course: CSCI 272 - Object Oriented Programming

// Moved the code from EventManager.h to EventManager.cpp
// Asked Google AI to help me understand step by step for EventManager.cpp
// and what's needed for cpp so I can understand what I'm doing for clarity on the structure
#include "EventManager.h"
#include <string>
#include <iostream>
//need derived header files here so dynamic_cast can recognnize them in generateReport().
#include "IntrusionEvent.h" 
#include "MalwareEvent.h"
#include <set> //for set<string> uniqueIPs in generateReport()
#include <sstream> //because we used ostringsream in generateReport().


// Destructor to clean up and prevent memory leaks
    EventManager::~EventManager() {
        for (Event* e : events) {
            delete e;
        }
        events.clear();
    }
    
    // ---- ADD EVENT FUNCTION -------
    // Adds event in this function
    void EventManager::addEvent(Event* newEvent) {
        if (newEvent != nullptr) { //added a nullptr for event so it can provide the pointer safely
            events.push_back(newEvent);
        }
    }

    // ---- SEARCH FUNCTION --------
    // Ask Google to help understand the member functions step by step and structure
    // Use void to display events and delete object pointers
    // Search by IP Address
    void EventManager::searchByIp(const string& targetIpAddress) const {
        bool found = false; // enables when searching Ip Address is false
        for (Event* e : events) {
            if (e->getIpAddress() == targetIpAddress) {
                //e->display();
                cout << *e << endl;  //Using template operator <<
                found = true; // enables when searching Ip Address is true and displays it
            }
        }
        if (!found) cout << "No events found for the address: " << targetIpAddress << endl;
    }
    
    // ----- SEARCH BY SERVERITY LEVELS & CVEID ------
    void EventManager::searchBySeverity(const string& level) const {
        bool found = false;
        for (Event* e : events) {
            if (e->getSeverity() == level) {
                //e->display(); // Shows the matching events
                cout << *e << endl;   //Using template operator <<
                found = true;
            }
        }
        if (!found) cout << "No events found at severity: " << level << endl; 
    }
    
    // void EventManager::searchByCveID(const string& targetCveID) const {
    //     bool found = false;
    //     for (Event* e : events) {
    //         if (e->getCveID() == targetCveID) {
    //             //e->display();
    //             cout << *e << endl; //Using template operator <<
    //             found = true;
    //         }
    //     }
    //     if (!found) cout << "No events found for CVE: " << targetCveID << endl;
    // }

    // ---- REMOVES EVENTS -------
    // deletes events from the input by index or ID
    // index used to access events elements of the total event
    // void EventManager::deleteEvent(int index){
    //     if (index >= 0 && index < (int)events.size()) {
    //         delete events[index]; // Frees the memory if dynamically allocated
    //         events.erase(events.begin() + index); // removes from vector
    //     }
    // }
    // void EventManager::deleteEventById(const string& eventID) { //Delete Event by ID and provide confirmation (Option 5) 
    //     for (int i = 0; i < (int)events.size(); i++) {
    //         if (events[i]->getEventID() == eventID) {
    //             delete events[i];
    //             events.erase(events.begin() + i); //start count all the way from left(begin) to the I-th location 
    //             cout << "Deleted event " << eventID << endl;
    //             return;
    //         }
    //     }
    //     cout << "No event found with ID: " << eventID << endl;
    // }

    // ------ HELPER FOR THE REPORT ------
    void EventManager::displayAllEvents() const {
        for (const Event* e : events) {
            e->display();
        }
    }

    // ---- GENERATE REPORTS --------
    // Generates and displays reports for every pointer
    //Edit(Jonathan): I didn't like how unstructured and the wall that the original generate report was giving so for clarity sake and also differentiate from dispaly all events.
    // a set automatically de-duplicates, so we get unique IPs instead of the long winded loop like commented below. 
    //This was a recommendation given by Claude after asking for recommendation for edits and layout for generate rport. 
    void EventManager::generateReport() const {

         // vector<string> seenIPs;
        // for (Event* e : events) {
        //     bool alreadyHave = false;
        //     for (string& ip : seenIPs) {           //loop to check duplicates
        //         if (ip == e->getIpAddress()) {
        //             alreadyHave = true;
        //             break;
        //         }
        //     }
        //     if (!alreadyHave) {
        //         seenIPs.push_back(e->getIpAddress());
        //     }
        // }
        // cout << seenIPs.size();
        int intrusions = 0, malware = 0, low = 0, med = 0, high = 0, crit = 0; // counters for each report category (start at zero)
        set<string> uniqueIPs;

        for (Event* e : events) {
            //(polymorphism + dynamic_cast)
            //dyanimc cast purpose here, a runtyime type check and only works with classses that use virtual and we do use it (Event class) 
            //What it does is essentailly asking the parameter "Is this pointer pointing to intrusion" if it is, return a ptr, if not, a nullptr. 
            if (dynamic_cast<IntrusionEvent*>(e) != nullptr)      intrusions++; //not a nullptr so increment intrusion
            else if (dynamic_cast<MalwareEvent*>(e)   != nullptr) malware++;  //not a nullptr so increment malware

            // severity tally (string comparison)
            const string& sev = e->getSeverity();
            if      (sev == "LOW")      low++;
            else if (sev == "MEDIUM")   med++;
            else if (sev == "HIGH")     high++;
            else if (sev == "CRITICAL") crit++;

            // unique IP collection
            uniqueIPs.insert(e->getIpAddress());
        }

        cout << "\n========== Security Event Report ==========" << endl;
        cout << "Total events       : " << events.size() << endl;
        cout << "  Intrusions       : " << intrusions    << endl;
        cout << "  Malware          : " << malware       << endl;
        cout << "Severity breakdown :"  << endl;
        cout << "  CRITICAL         : " << crit          << endl;
        cout << "  HIGH             : " << high          << endl;
        cout << "  MEDIUM           : " << med           << endl;
        cout << "  LOW              : " << low           << endl;
        cout << "Unique attacker IPs: " << uniqueIPs.size() << endl;
        for (const string& ip : uniqueIPs) {
            cout << "  - " << ip << endl;
        }

   
        ostringstream oss;
        oss << "Compact listing:\n";
        for (Event* e : events) {
            oss << "  " << *e << "\n";   // template operator<< (T = ostringstream)
        }
        cout << oss.str();
        cout << "===========================================\n" << endl;
    }
