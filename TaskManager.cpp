#include "TaskManager.h"

using std::cout;
using std::endl;
//-------------------------------------Class interface-----------------------------------------
TaskManager::TaskManager() : length(0), id(0) {}

void TaskManager::completeTask(const std::string &personName) {
    for(int i = 0; i < this->length; i++) {
        if(this->persons[i].getName() == personName) {
            this->persons[i].completeTask();
        }
    }
}

void TaskManager::assignTask(const string& personName, const Task& task) {
    Task newTask(task);
    newTask.setId(this->id++);
    for (int i = 0; i < this->length; i++) {
        if (personName == this->persons[i].getName()) {
            this->persons[i].assignTask(newTask);
            return;
        }
    }
    if(this->length >= MAX_PERSONS) {
        throw std::runtime_error("Not enough place for a new person");
    }
    this->persons[length] = Person(personName);
    this->persons[length].assignTask(newTask);
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
                newTask.setId(n.getId());
                newPersonTasks.insert(newTask);
            } else {
                newPersonTasks.insert(n);
            }
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

void TaskManager::printAllTasks() const {
    SortedList<Task> tasks;
    for (int i = 0; i < length; i++) {
        for (const Task &task: persons[i].getTasks()) {
            tasks.insert(task);
        }
    }
    for (const Task &task: tasks) {
        cout << task << endl;
    }
}
	
void TaskManager::printTasksByType(TaskType type) const {
    SortedList<Task> filteredList;
    for (int i = 0; i < this->length; i++) {
        SortedList<Task> personTasks;
        for (Task n: this->persons[i].getTasks()) {
            if (n.getType() == type) {
                filteredList.insert(n);
            }
        }
    }
    for(Task t: filteredList) {
        cout << t << endl;
    }
}
