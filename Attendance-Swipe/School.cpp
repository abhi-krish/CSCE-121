#include "School.h"
#include "AttendanceRecord.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

void School::addCourses(string filename) {
    ifstream inFS(filename);
    if (!inFS.is_open()) {
        cout << "Unable to open file: " << filename << endl;
        return;
    }
    while (!inFS.eof()) {
        string line;
        getline(inFS, line);
        istringstream iss(line);
        string courseid;
        getline(iss, courseid, ',');
        string starthour;
        getline(iss, starthour, ',');
        string endhour;
        getline(iss, endhour, ',');
        string classes;
        getline(iss, classes);
        istringstream IS_START(starthour);
        istringstream IS_END(endhour);

        int int_startHour;
        int int_startMin;
        int int_endHour;
        int int_endMin;
        char blank;

        IS_START >> int_startHour;
        IS_START >> blank;
        IS_START >> int_startMin;
        IS_END >> int_endHour;
        IS_END >> blank;
        IS_END >> int_endMin;

        if (!iss.fail() && !IS_START.fail() && !IS_END.fail()) {
            bool check = false;
            for (int i = 0; i < courses.size(); i++) {
                if (courses.at(i).getID() == courseid) {
                    check = true;
                }
            }
            if (!check) {
                courses.push_back(Course(courseid, classes, Date(int_startHour, int_startMin), Date(int_endHour, int_endMin)));
            }
        }
    }
}

void School::addStudents(string filename) {
    ifstream ifs(filename);
    if (!ifs.is_open()) {
        cout << "Unable to open file: " << filename << endl;
        return;
    }
    while (!ifs.eof()) {
        string line;
        getline(ifs, line);
        istringstream ss(line);
        string uin;
        getline(ss, uin, ',');
        string name;
        getline(ss, name);
        if (!ss.fail()) {
            students.push_back(Student(uin, name));
        }
    }
}

void School::addAttendanceData(string filename) {
    ifstream inFS(filename);
    if (!inFS.is_open()) {
        cout << "Unable to open file: " << filename << endl;
        return;
    }
    while (!inFS.eof()) {
        string line;
        getline(inFS, line);
        istringstream iss(line);
        string time;
        getline(iss, time, ',');
        string coursenum;
        getline(iss, coursenum, ',');
        string student_id;
        getline(iss, student_id);

        int int_year;
        int int_month; 
        int int_day;
        int int_hour;
        int int_min;
        int int_sec;
        char space;

        istringstream IS_DATE(time);

        IS_DATE >> int_year;
        IS_DATE >> space;
        IS_DATE >> int_month;
        IS_DATE >> space; 
        IS_DATE >> int_day;
        IS_DATE >> int_hour;
        IS_DATE >> space;
        IS_DATE >> int_min;
        IS_DATE >> space;
        IS_DATE >> int_sec;

        if (!iss.fail() && !IS_DATE.fail()) {
            for (int i = 0; i < courses.size(); i++) {
                if (courses.at(i).getID() == coursenum) {
                    courses.at(i).addAttendanceRecord(AttendanceRecord(coursenum, student_id, Date(int_year, int_month, int_day, int_hour, int_min, int_sec)));
                    break;
                }
            }
        }
    }
}

void School::listCourses() {
    if (courses.size() == 0) {
        cout << "No Courses" << endl;
        return;
    }
    for (int i = 0; i < courses.size(); i++) {
        Course course = courses.at(i);
        Date starttime = course.getStartTime();
        Date endtime = course.getEndTime();
        cout << course.getID() <<","<< course.getStartTime().getTime(false) << "," << course.getEndTime().getTime(false) << ',' << course.getTitle() << endl;
    }
}

void School::listStudents() {
    if (students.size() == 0) {
        cout << "No Students" << endl;
        return;
    }
    else{
        for (int i = 0; i < students.size(); i++) {
            cout << students.at(i).get_id() << ',' << students.at(i).get_name() << endl;
        }
    }
}

void School::outputCourseAttendance(string course_id) {
    for (int i = 0; i < courses.size(); i++) {
        if (courses.at(i).getID() != course_id) {
            continue;
        }
        else{
            courses.at(i).outputAttendance();
            return;
        }
    }
    cout << "No Records" << endl;
}

void School::outputStudentAttendance(string student_id, string course_id) {
    for (int i = 0; i < courses.size(); i++) {
        if (courses.at(i).getID() != course_id) {
            continue;
        }
        else{
            courses.at(i).outputAttendance(student_id);
            return;
        }
    }
    cout << "No Records" << endl;
}