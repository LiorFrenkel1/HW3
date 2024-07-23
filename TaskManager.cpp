#include "TaskManager.h"

using std::cout;
//-------------------------------------Class interface-----------------------------------------
TaskManager::TaskManager() : persons(new Person[10]), length(0) {}

void TaskManager::completeTask(const std::string &personName) {
    for(int i = 0; i < length; i++) {
        if(persons[i].getName() == name) {
            persons[i].completeTask();
        }
    }
}










// ----------------------------------Printing methods------------------------------------------
void TaskManager::printAllEmployees() const {
    for(int i = 0; i < this->length ; i++){
        cout << persons[i] << endl;
    }
}

