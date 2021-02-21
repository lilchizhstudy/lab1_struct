#define _CRT_SECURE_NO_WARNINGS

#include <iostream>;
#include <string>;
#include <ctime>;
#include <vector>;
#include <fstream>;
#include <conio.h>;

const std :: string FILE_NAME = "students.txt";

const int NUMBER_OF_EXAMS = 8;
const int AVERAGE_GRADE = NUMBER_OF_EXAMS;
const int GRADES = NUMBER_OF_EXAMS + 1;

enum Gender { F, M };
enum EducationForm { evening, day, distance };

struct Student {
    std :: string name;
    Gender gender;
    int group;
    int numberInGroup;
    int grades[GRADES];
    EducationForm educationForm;
    std :: string time;
    int readerID;
};

struct Book {
    int ID;
    int readerID;
    std :: string name;
    std :: string author;
    int year;
    int pages;
};

void printMenu ();
void load ( std :: vector <Student> *, struct Book *, int, int );

std :: vector<Student> * parseStudents ();

void printStudent( Student *, int );
void printAllStudents ( std :: vector<Student> * );

void studentsByGender ( std :: vector<Student> * );
void printByNumberInGroup ( std :: vector <Student> *, int);
bool isAboveLimit ( Student *, int);
bool isBelowLimit(Student *, int);
void printWithGradeLimit ( std :: vector <Student> *, int, int);
void printGrantStudents ( std :: vector <Student> *, bool );
void printTopStudents ( std :: vector<Student> * );
void editStudent ( Student * );
void printAllGroup ( std :: vector <Student> *, int );

void appendToFile( Student* );
void rewriteFile ( std :: vector<Student> * );
void writeStudentToFile ( Student *, std :: ofstream & );

Student createStudent ();

EducationForm getForm ( std :: string );
std :: string getForm ( int );

Gender getGender ( std :: string );
char getGender ( int );

int getTimestamp( std::string );
std :: string getCurrentDate ();

void printLibrary ( struct Book *&, int );
void takeBook ( struct Book *& ); 
void returnBook ( struct Book *& ); 

int main () {
    
    std :: vector<Student> * students = parseStudents();

    int librarySize = 5;
    struct Book library[] = {
        0, 0, "War & Peace", "Leo Tolstoy", 1865, 1000,
        1, 0, "1984", "Jeorge Orwell", 1948, 356,
        2, 0, "Master & Margaret", "Mikhail Bulgakov", 1929, 543,
        3, 0, "Dead souls I", "Nikolay Gogol", 1842, 452,
        4, 0, "12 chairs", "Ilf & Petrov", 1928, 341,
        5, 0, "Idiot", "Fyodor Dostoyevsky", 1868, 561
    };

    int menuCase = 0;

    while ( true ) {
    
        printMenu();

        std :: cin >> menuCase;

        std :: cout << "\n";

        switch ( menuCase ) {
            case 18: 
                return 0;
                break;
            default: 
                load(students, library, librarySize, menuCase);
                break;
        }
    
    }

}

std :: vector<Student> * parseStudents () {

    std :: string line;
    std :: ifstream file;

    std :: vector<Student> * students = new std :: vector<Student>;
    int readerCounter = 0;

    file.open(FILE_NAME);

    if ( file.is_open() ) {

        struct Student student;

        while ( !file.eof() ) {
           
            int gradesCounter = 0, averageGrade = 0;
            std :: string form, grades, gender, group, numberInGroup, time;

            std :: getline(file, student.name);

            std :: getline(file, group);

            student.readerID = readerCounter;
            readerCounter++;

            student.group = std :: stoi(group);

            std :: getline(file, numberInGroup);
            student.numberInGroup = std :: stoi(numberInGroup);

            std :: getline(file, gender);
            student.gender = getGender(gender);

            std :: getline(file, form);
            student.educationForm = getForm(form);

            std :: getline(file, grades);

            for ( int i = 0; i < grades.size(); i++ ) {
                if ( grades[i] != ' ' ) {
                    int grade = grades[i] - '0';
                    student.grades[gradesCounter] = grade;
                    averageGrade += grade;
                    gradesCounter++;
                }
            }

            student.grades[AVERAGE_GRADE] = ( averageGrade / NUMBER_OF_EXAMS );
     
            gradesCounter = 0;

            std :: getline(file, time);
            student.time = time;

            std :: getline(file, line);

            students->push_back(student);

        }

    } else {
        
        std :: cout << "Something went wrong\n";

    }

    return students;

}

void printStudent( Student * student, int number ) {

   std :: cout << number + 1 << " - " << student->name << "\n"
        << "Group: " << student->group << "\n"
        << "Number in group: " << student->numberInGroup << "\n"
        << "Gender: " << getGender(student->gender) << "\n"
        << "Education form: " << getForm(student->educationForm) << "\n"
        << "Last exams grades: ";

    for ( int i = 0; i < NUMBER_OF_EXAMS; i++ ) {
            
        std :: cout << student->grades[i] << " ";
        
    }

    std :: cout << "\nLast edit time: " << student->time << "\n\n";
    
}

void printMenu () {

    std::cout
        << "1 - Create new student record\n"
        << "2 - Edit student record\n"
        << "3 - Print all students\n"
        << "4 - Print all students of group\n"
        << "5 - Print top students\n"
        << "6 - Print students by gender\n"
        << "7 - Print students with grant\n"
        << "8 - Print students without grant\n"
        << "9 - Print students with Good & Excellent grades only\n"
        << "10 - Print students with Excellent grades only\n"
        << "11 - Print students with specific number in group\n"
        << "12 - Print students changed by date\n"
        << "13 - Print students changed afternoon\n"
        << "14 - Print sudents changed before noon\n"
        << "15 - Print library\n"
        << "16 - Take book\n"
        << "17 - Return book\n"
        << "18 - Exit\n"
        << "Select option: ";

}

void printAllStudents ( std :: vector<Student> * students ) {

    for ( int i = 0; i < students->size(); i++ ) {

        printStudent(&students->at(i), i);

    }

}

void studentsByGender ( std :: vector<Student> * students ) {

    int m = 0, f = 0;

    for ( int i = 0; i < students->size(); i++ ) {
        
        Gender gender = (&students->at(i))->gender;

        if ( gender == Gender :: F ) {
            f++;
        } else {
            m++;
        }
        
    }

    std :: cout << "Female students: " << f << "\n";
    std :: cout << "Male students: " << m << "\n";

}

void printByNumberInGroup ( std :: vector <Student> * students, int number ) {
    
    for ( int i = 0; i < students->size(); i++ ) {
        if ( (&students->at(i))->numberInGroup == number ) {
            printStudent(&students->at(i), i);
        }
    }

}

bool isAboveLimit ( Student * student, int limit ) {
    
    bool aboveLimit = true;
    int * grades = student->grades;

    for (int i = 0; i < NUMBER_OF_EXAMS; i++) {
        if (grades[i] > limit) {
            aboveLimit = false;
            break;
        }
    }

    return aboveLimit;

}

bool isBelowLimit(Student* student, int limit) {

    bool belowLimit = true;
    int* grades = student->grades;

    for (int i = 0; i < NUMBER_OF_EXAMS; i++) {
        if (grades[i] < limit) {
            belowLimit = false;
            break;
        }
    }

    return belowLimit;

}

void printGrantStudents ( std :: vector <Student> * students, bool grant ) {

    for ( int i = 0; i < students->size(); i++ ) {
        
        bool belowLimit = isBelowLimit(&students->at(i), 4);
        bool dayForm = (&students->at(i))->educationForm == EducationForm::day;

        if ( grant && belowLimit && dayForm ) {
            printStudent(&students->at(i), i);
        } else if ( !grant && ( !belowLimit || !dayForm ) ) {
            printStudent(&students->at(i), i);
        }

    }
        
}

void printWithGradeLimit ( std :: vector <Student> * students, int belowLimit, int aboveLimit ) {
    
    for ( int i = 0; i < students->size(); i++ ) {
       
       bool isAbove = isAboveLimit(&students->at(i), aboveLimit);
       bool isBelow = isBelowLimit(&students->at(i), belowLimit);

       if ( isAbove && isBelow ) {
           printStudent(&students->at(i), i);
       }

    }

}

void printTopStudents ( std :: vector<Student> * students ) {

    int max = 0, max2 = 0, max3 = 0;
    int i = 0, i2 = 0, i3 = 0;

    for ( int j = 0; j < students->size(); j++ ) {
    
        int grade = (&students->at(j))->grades[AVERAGE_GRADE];

        if ( grade > max ) {
            max3 = max2;
            i3 = i2;
            max2 = max;
            i2 = i;
            max = grade;
            i = j;
        } else if ( grade > max2 ) {
            max3 = max2;
            i3 = i2;
            max2 = grade;
            i2 = j;
        } else if ( grade > max3 ) {
            max3 = grade;
            i3 = j;
        }

    }

    std :: cout << "Top 3 students by grades average: \n\n";
    std :: cout << "===First place===\n";
    printStudent(&students->at(i), i);
    std :: cout << "===Second place===\n";
    printStudent(&students->at(i2), i2);
    std :: cout << "===Third place===\n";
    printStudent(&students->at(i3), i3);

};

void printChangedByDate ( std :: vector<Student> * students, std :: string day ) {
    
    for ( int i = 0; i < students->size(); i++ ) {
        
        std :: string date = students->at(i).time;

        if ( date.find(day) != std :: string :: npos ) {
            printStudent(&students->at(i), i);
        }

    }

}

void printChangedByTime ( std :: vector<Student> * students, bool noon ) {

    for ( int i = 0; i < students->size(); i++ ) {
        
        std :: string date = students->at(i).time;
        int time = std :: stoi(date.substr(11, 2));

        if ( !noon && ( time < 12 || time == 0) ) {
            printStudent(&students->at(i), i);
        } else if ( noon && time > 12 ) {
            printStudent(&students->at(i), i);
        }

    }

}

void editStudent ( Student * student ) {
    
    int field;

    std :: cout << "Select field to edit:\n" 
        << "1 - Name\n"
        << "2 - Gender\n"
        << "3 - Group\n"
        << "4 - Number in group\n"
        << "5 - Grades\n"
        << "6 - Education form\n";

    std :: cout << "Enter field to edit: ";
    std :: cin >> field;
    std :: cout << "\n";

    switch ( field ) {
    
        case 1: {
            std :: string name, n;
            std :: cout << "Enter new name: ";
            std::cin.ignore();
            std :: getline(std :: cin, name);
            student->name = name;
            break;
        }
        case 2: {
            std :: string gender;
            std :: cout << "Enter new gender: ";
            std :: cin >> gender;
            student->gender = getGender(gender);
            break;
        }
        case 3: {
            int group;
            std :: cout << "Enter new group: ";
            std :: cin >> group;
            student->group = group;
            break;
        }
        case 4: {
            int numberInGroup;
            std :: cout << "Enter new number in group: ";
            std :: cin >> numberInGroup;
            student->numberInGroup = numberInGroup;
            break;
        }
        case 5: {
            int gradeNumber, grade;
            std :: cout << "Enter grade number: ";
            std :: cin >> gradeNumber;
            std :: cout << "Enter new grade: ";
            std :: cin >> grade;
            student->grades[gradeNumber] = grade;
            break;
        }
        case 6: {
            std :: string form;
            std :: cout << "Enter new education form ( evening | day | distance ): ";
            std :: cin >> form;
            student->educationForm = getForm(form);
            break;
        }
    }

    student->time = getCurrentDate();

    std :: cout << "Student was edited\n";

}

void printAllGroup ( std :: vector <Student> * students, int group ) {

    for ( int i = 0; i < students->size(); i++ ) {
    
        if ( (&students->at(i))->group == group ) {
            
            printStudent(&students->at(i), i);

        }

    }

}

void load ( std :: vector <Student> * students, struct Book * library, int librarySize, int menuCase ) {

    switch ( menuCase ) {

        case 1:  {
            Student newStudent = createStudent();
            students->push_back(newStudent);
            appendToFile(&newStudent);
            break;
        }
        case 2: {
            int number;
            printAllStudents(students);
            std :: cout << "Enter number of student to edit: ";
            std :: cin >> number;
            editStudent(&students->at(number - 1));
            rewriteFile(students);
            break;
        } case 3: {
            printAllStudents(students);
            break;
        } case 4: {
            int group;
            std :: cout << "Enter number of group: ";
            std :: cin >> group;
            printAllGroup(students, group);
            break;
        } case 5: {
            printTopStudents(students);
            break;
        } case 6: {
            studentsByGender(students);
            break;
        } case 7: {
            printGrantStudents(students, true);
            break;
        } case 8: {
            printGrantStudents(students, false);
            break;
        } case 9: {
            printWithGradeLimit(students, 4, 5);
            break;
        } case 10: {
            printWithGradeLimit(students, 5, 5);
            break;
        } case 11: {
            int number;
            std :: cout << "Enter number in group: ";
            std :: cin >> number;
            printByNumberInGroup(students, number);
            break;
        } case 12: {
            std :: string day;
            std :: cout << "Enter day ( <month string> <space> <day number> ): ";
            std :: cin >> day; 
            std :: cin.ignore();
            std :: getline(std :: cin, day);
            printChangedByDate(students, day);
            break;
        } case 13: {
            printChangedByTime(students, true);
            break;
        } case 14: {
            printChangedByTime(students, false);
            break;
        } case 15: {
            printLibrary(library, librarySize);
            break;
        } case 16: {
            printLibrary(library, librarySize);
            takeBook(library);
            break;
        } case 17: {
            printLibrary(library, librarySize);
            returnBook(library);
            break;
        }

    }   

     std :: cout << "\n";
    
}

Student createStudent() {

    struct Student newStudent;
    std::string grades, gender, educationForm;
    int averageGrade = 0;

    std::cout << "Enter student name: ";
    std::cin >> newStudent.name;

    std::cout << "Enter student gender ( F / M ): ";
    std::cin >> gender;
    newStudent.gender = getGender(gender);

    std::cout << "Enter student group: ";
    std::cin >> newStudent.group;

    std::cout << "Enter student's number in group: ";
    std::cin >> newStudent.numberInGroup;

    std::cout << "Enter student grades in this order [ math | english | cs | literature | physics | chemistry | philosophy | biology ] ";

    for (int i = 0; i < NUMBER_OF_EXAMS; i++) {
        std::cin >> newStudent.grades[i];
        averageGrade += newStudent.grades[i];
    }

    newStudent.grades[AVERAGE_GRADE] = (averageGrade / NUMBER_OF_EXAMS);

    std::cout << "Enter student education form ( evening | day | distance ): ";
    std::cin >> educationForm;
    newStudent.educationForm = getForm(educationForm);

    newStudent.time = getCurrentDate();

    return newStudent;

};

void appendToFile ( Student * student ) {

    std :: ofstream file;

    file.open(FILE_NAME, std :: ios :: app );

    if ( file.is_open() ) {

        file << "\n";

        writeStudentToFile(student, file);

        file << "\n";

        std :: cout << "Student written!\n";

    } else {
        std :: cout << "Something went wrong during file writing\n";
    }

    file.close();

}

void rewriteFile ( std :: vector<Student> * students ) {

    std :: ofstream file;

    file.open(FILE_NAME, std :: ios :: trunc );

    if ( file.is_open() ) {

        for ( int i = 0; i < students->size(); i++ ) {

            writeStudentToFile(&students->at(i), file);
            
            if ( i < students->size() -1 ) {
                file << "\n\n";
            } else {
                file << "\n";
            }

        }

        std::cout << "Changes saved!\n";

    } else {
        std :: cout << "Something went wrong\n";
    }

    file.close();

}

void writeStudentToFile ( Student * student, std :: ofstream & file ) {

    file << student->name << "\n"
        << student->group << "\n"
        << student->numberInGroup << "\n"
        << getGender(student->gender) << "\n"
        << getForm(student->educationForm) << "\n";

    for ( int i = 0; i < NUMBER_OF_EXAMS; i++ ) {
        file << student->grades[i] << " ";
    }

    file << "\n" << student->time;

}

//Helpers

EducationForm getForm ( std :: string form ) {

    if ( form == "evening" ) {
        return EducationForm :: evening;
    } else if ( form == "day" ) {
        return EducationForm :: day;
    } else if ( form == "distance" ) {
        return EducationForm :: distance;
    }

}

std :: string getForm ( int form ) {
    
    switch ( form ) {
    
        case 0: return "evening";
        case 1: return "day";
        case 2: return "distance";

    }

}

Gender getGender ( std :: string gender ) {
    
    if ( gender == "F" ) {
        return Gender :: F;
    } else if ( gender == "M" ) {
        return Gender :: M;
    }

}

char getGender ( int gender ) {

    switch ( gender ) {
        case 0: return 'F';
        case 1: return 'M';
    }

}

std :: string getCurrentDate () {

    time_t timestamp = time(0);
    std :: string date = asctime(localtime(&timestamp));

    date.pop_back(); // Removing last '\n'

    return date;

}

// Library 

void printLibrary ( struct Book *& library, int size ) {

    std :: cout << "===Library===\n\n";

    for ( int i = 0; i < size; i++ ) {

        std::cout
            << "ID: " << library[i].ID << "\n"
            << "Name: " << library[i].author << "\n"
            << "Author: " << library[i].name << "\n"
            << "Year: " << library[i].year << "\n"
            << "Pages: " << library[i].pages << "\n"
            << "Available: " << ( library[i].readerID ? "No" : "Yes" )
            << "\n\n";

    }

}

void takeBook ( struct Book *& library ) {

    int bookID = 0, readerID;
    bool taken = false;

    std :: cout << "Enter your reader ID: ";
    std :: cin >> readerID;

    while ( !taken && bookID != -1 ) {

        std :: cout << "Select book to take ( -1 to exit ) : ";

        std :: cin >> bookID;

        if ( !library[bookID].readerID ) {
            taken = true;
            library[bookID].readerID = readerID;
            std :: cout << "You succefully took " << library[bookID].name << " by " << library[bookID].author << "\n";
        } else if ( library[bookID].readerID == readerID ) {
            std :: cout << "Book was already taken by you\n";
        } else if ( bookID != -1 )  {
            std :: cout << "Book was already taken or does not exist, select another book\n";
        }

    }

}

void returnBook ( struct Book *& library ) {
 
    int bookID = 0, readerID;
    bool returned = false;

    std :: cout << "Enter your reader ID: ";
    std :: cin >> readerID;

    while ( !returned && bookID != -1 ) {

        std :: cout << "Select book to return ( -1 to exit ): ";

        std :: cin >> bookID;

        if ( library[bookID].readerID == readerID ) {
            returned = true;
            library[bookID].readerID = 0;
            std :: cout << "You succefully returned " << library[bookID].name << " by " << library[bookID].author << "\n";
        } else if ( library[bookID].readerID == 0 ) {
            std :: cout << "Book was not taken or does not exist\n";
        } else if ( library[bookID].readerID != readerID ) {
            std :: cout << "Book was taken not by you\n";
        }

    }

}