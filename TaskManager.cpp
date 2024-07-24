#include "TaskManager.h"

using std::cout;
using std::endl;
//-------------------------------------Class interface-----------------------------------------
TaskManager::TaskManager() : persons(new Person[10]), length(0) {}

void TaskManager::completeTask(const std::string &personName) {
    for(int i = 0; i < this->length; i++) {
        if(this->persons[i].getName() == personName) {
            this->persons[i].completeTask();
        }
    }
}

void TaskManager::assignTask(const string& personName, const Task& task) {
    for (int i = 0; i < this->length; i++) {
        if (personName == this->persons[i].getName()) {
            this->persons[i].assignTask(task);
        }
    }
    if(this->length >= MAX_PERSONS) {
        throw std::runtime_error("Not enough place for a new person");
    }
    this->persons[length] = Person(personName);
    this->persons[length].assignTask(task);
    this->length++;
}

void TaskManager::bumpPriorityByType(TaskType type, int priority) {
    for (int i = 0; i < this->length; i++) {
        Person person = this->persons[i];
        SortedList<Task> personTasks = person.getTasks();
        SortedList<Task> newPersonTasks;
        for (Task n: personTasks) {
            if (n.getType() == type) {
                Task newTask = Task((n.getPriority() + priority), type, n.getDescription());
                newPersonTasks.insert(newTask);
            }
            newPersonTasks.insert(n);
        }
        person.setTasks(newPersonTasks);
    }
}





// ----------------------------------Printing methods------------------------------------------
void TaskManager::printAllEmployees() const {
    for(int i = 0; i < this->length ; i++){
        cout << persons[i] << endl;
    }
}

void TaskManager::printTasksByType(TaskType type) const {
    TaskManager tasks;
    for (int i = 0; i < this->length; i++) {
        for (Task n: this->persons[i].getTasks()) {
            if (n.getType() == type) {
                tasks.assignTask("tasks", n);
            }
        }
    }
    tasks.printAllTasks();
}
