// TIE-02006 fall 2017
// Project 04
// Juha Suvanto 189427
// jsuvanto@iki.fi

#include "prioritylist.hh"
#include <string>
#include <iostream>

PriorityList::PriorityList(const int &levels): levels_(levels), size_(0), first_chore_(nullptr) {
    std::cout << "New priority list with levels 1-" << levels << " initialized." << std::endl;
}

bool PriorityList::nextChore() {
    if (first_chore_ != nullptr) {
        std::cout << first_chore_->description << std::endl;
        eraseChore(1);
        return true;
    }
    else {
        std::cout << "--- no chores left ---" << std::endl;
        return false;
    }
}

bool PriorityList::addChore(const int &priority, const std::string &description) {

    if (priority > levels_ || priority < 1) {
        std::cout << "Error: priority level must be an integer between 1-" << levels_ << std::endl;
        return false;
    } else if (description == "") {
        std::cout << "Error: chore description is missing." << std::endl;
        return false;
    }

    Chore* new_chore = new Chore;
    new_chore->priority = priority;
    new_chore->description = description;

    if (first_chore_ == nullptr || priority > first_chore_->priority) { // New chore goes first if the linked list is empty, or its priority is higher than the old first chore.
        new_chore->next_chore = first_chore_;
        first_chore_ = new_chore;
    } else {

        Chore* current_chore = first_chore_;

        while (current_chore != nullptr) {
            if (current_chore->next_chore == nullptr) { // We've reached the end of the list
                break;
            } else if (current_chore->next_chore->priority < priority) { // Item in the middle of the linked list.
                break;
            }
            current_chore = current_chore->next_chore;
        }
        new_chore->next_chore = current_chore->next_chore;
        current_chore->next_chore = new_chore;

    }
    ++size_;
    std::cout << "New chore added to priority level " << priority << "." << std::endl;
    return true;
}

bool PriorityList::eraseChore(const int &number) {
    if (number > size_) {
        std::cout << "Error: there is no such chore." << std::endl;
        return false;
    } else if (number < 1) {
        std::cout << "Error: the running number must be larger than 0." << std::endl;
        return false;
    } else {
        Chore* current_chore = first_chore_;

        if (number == 1) {
            first_chore_ = first_chore_->next_chore;
            delete current_chore;
        } else {
            int i = 1;

            // find the chore just before the one we want to delete
            while (i < number-1) {
                ++i;
                current_chore = current_chore->next_chore;
            }
            Chore* delete_chore = current_chore->next_chore;
            current_chore->next_chore = current_chore->next_chore->next_chore;
            delete delete_chore;

        }
        --size_;
        return true;
    }
}

void PriorityList::printChores() const {
    Chore* chore_iter = first_chore_;
    int chorecount = 0;
    int lastprintedlevel = levels_+1;

    while (chore_iter != nullptr) {
        if (lastprintedlevel > chore_iter->priority) {
            std::cout << "Priority level " << chore_iter->priority << ":" << std::endl;
            lastprintedlevel = chore_iter->priority;
        }

        std::cout << "  " << ++chorecount << ". " << chore_iter->description << std::endl;
        chore_iter = chore_iter->next_chore;

    }
}
