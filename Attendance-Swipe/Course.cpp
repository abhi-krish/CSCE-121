#include <iostream>
#include <fstream>
#include <string>
#include "Course.h"
#include "Date.h"
#include "AttendanceRecord.h"

using namespace std;

Course::Course(std::string id, std::string title, Date startTime, Date endTime) : startTime(startTime), endTime(endTime) {
    this->id = id;
    this->title = title;
}

std::string Course::getID(){
    return id;
}

std::string Course::getTitle(){
    return title;
}

Date Course::getStartTime(){
    return startTime;
}

Date Course::getEndTime(){
    return endTime;
}

void Course::addAttendanceRecord(AttendanceRecord ar) {
    if(ar.getDate() < getStartTime() || ar.getDate() > getEndTime()) {
        cout << "Did not save this record" << endl;
        return;
    }
    attendanceRecords.push_back(ar);
}


void Course::outputAttendance() {
    if (attendanceRecords.size() == 0) {
        cout << "No records" << endl;
        return;
    }
    for (int i = 0; i < attendanceRecords.size(); i++) {
        cout << attendanceRecords.at(i).getDate().getDateTime() << "," << attendanceRecords.at(i).getCourseID() << "," << attendanceRecords.at(i).getStudentID() << endl;   
    }
}

void Course::outputAttendance(std::string student_id) {
    bool check = false;
    for (int i = 0; i < attendanceRecords.size(); i++) {
        if (attendanceRecords.at(i).getStudentID() != student_id) {
            continue;
        }
        cout << attendanceRecords.at(i).getDate().getDateTime() << "," << attendanceRecords.at(i).getCourseID() << "," << attendanceRecords.at(i).getStudentID() << endl;
        check = true;
    }
    if (check == false) {
        cout << "No Records" << endl;
    }
}
