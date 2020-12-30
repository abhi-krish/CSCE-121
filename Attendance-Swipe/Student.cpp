#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "Student.h"

using namespace std;

Student::Student(std::string student_id, std::string name) {
    id = student_id;
    this->name = name;
}

std::string Student::get_id() {
    return id;
}

std::string Student::get_name() {
    return name;
}

void Student::addCourse(std::string course_id) {
    bool check = false;
    for(int i = 0; i < course_ids.size(); i++) {
        if(course_ids.at(i) == course_id){
            check = true;
        }
    }
    if(check == false){
        course_ids.push_back(course_id);
    }
}

void Student::listCourses() {
    cout << "Courses for " << id << endl;
    for(int i = 0; i < course_ids.size(); i++) {
        cout << course_ids.at(i) << endl;
    }
}