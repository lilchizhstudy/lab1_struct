#pragma once
#include <vector>;
#include <string>;
#include <ctime>;

const int NUMBER_OF_EXAMS = 8;
const int AVERAGE_GRADE = NUMBER_OF_EXAMS + 1;
const int GRADES = NUMBER_OF_EXAMS + 1;

enum Gender { F, M };
enum EducationForm { evening, day, distance };

struct Student {
    std::string name;
    Gender gender;
    int group;
    int numberInGroup;
    int grades[GRADES];
    EducationForm educationForm;
    std::time_t time;
};

std :: vector<Student> * parseStudents () {};