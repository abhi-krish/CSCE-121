#include <string>
#include "AttendanceRecord.h"
#include "Date.h"

using namespace std;

AttendanceRecord::AttendanceRecord(std::string course_id, std::string student_id, Date time) : time(time) {
    this->course_id = course_id;
    this->student_id = student_id;
}

string AttendanceRecord::getStudentID() {
    return student_id;
}

string AttendanceRecord::getCourseID() {
    return course_id;
}

Date AttendanceRecord::getDate(){
    return time;
}


