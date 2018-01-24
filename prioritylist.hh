// TIE-02006 fall 2017
// Project 04
// Juha Suvanto 189427
// jsuvanto@iki.fi

#ifndef PRIORITYLIST_HH
#define PRIORITYLIST_HH

#include <string>

// Priority list class that holds different chores that have different priority levels.
// Uses a dynamic singly linked list for storing the chores.
class PriorityList
{
public:    
    PriorityList(const int &levels);

    // Print the first chore in the list and erase it.
    // Return false if list is empty, otherwise true.
    bool nextChore();

    // Add a new chore with given description and priority level.
    // Return true if successful, otherwise false.
    bool addChore(const int &level, const std::string &description);

    // Erase a chore by number.
    // Return true if successful, otherwise false.
    bool eraseChore(const int &number);

    // Print all chores in the list.
    void printChores() const;

private:
    int levels_;
    int size_;

    struct Chore {
        std::string description;
        int priority;
        Chore* next_chore;
    };

    Chore* first_chore_ = nullptr;

};

#endif // PRIORITYLIST_HH
