#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class Student
{
public:
    int rollNo;
    string name;
    int age;
    string course;
    float marks;

    void input()
    {
        cout << "Enter Roll Number: ";
        cin >> rollNo;

        cin.ignore();

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Age: ";
        cin >> age;

        cin.ignore();

        cout << "Enter Course: ";
        getline(cin, course);

        cout << "Enter Marks: ";
        cin >> marks;
    }

    void display()
    {
        cout << "\nRoll Number: " << rollNo << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Course: " << course << endl;
        cout << "Marks: " << marks << endl;
        cout << "--------------------------\n";
    }
};

void addStudent()
{
    Student s;

    cout << "\n--- Add Student ---\n";

    s.input();

    ifstream checkFile("students.txt");

    string line;

    while (getline(checkFile, line))
    {
        stringstream ss(line);

        string roll;
        getline(ss, roll, ',');

        if (stoi(roll) == s.rollNo)
        {
            cout << "\nStudent with this roll number already exists.\n";
            checkFile.close();
            return;
        }
    }

    checkFile.close();

    ofstream file("students.txt", ios::app);

    file << s.rollNo << ","
         << s.name << ","
         << s.age << ","
         << s.course << ","
         << s.marks << endl;

    file.close();

    cout << "\nStudent added successfully.\n";
}

void displayStudents()
{
    ifstream file("students.txt");

    if (!file)
    {
        cout << "\nNo student records found.\n";
        return;
    }

    string line;

    cout << "\n--- Student Records ---\n";

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);

        string roll;
        string name;
        string age;
        string course;
        string marks;

        getline(ss, roll, ',');
        getline(ss, name, ',');
        getline(ss, age, ',');
        getline(ss, course, ',');
        getline(ss, marks);

        Student s;

        s.rollNo = stoi(roll);
        s.name = name;
        s.age = stoi(age);
        s.course = course;
        s.marks = stof(marks);

        s.display();
    }

    file.close();
}

void searchStudent()
{
    int rollNo;

    cout << "\nEnter Roll Number: ";
    cin >> rollNo;

    ifstream file("students.txt");

    string line;
    bool found = false;

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);

        string roll;
        string name;
        string age;
        string course;
        string marks;

        getline(ss, roll, ',');
        getline(ss, name, ',');
        getline(ss, age, ',');
        getline(ss, course, ',');
        getline(ss, marks);

        if (stoi(roll) == rollNo)
        {
            Student s;

            s.rollNo = stoi(roll);
            s.name = name;
            s.age = stoi(age);
            s.course = course;
            s.marks = stof(marks);

            cout << "\nStudent Found\n";

            s.display();

            found = true;
            break;
        }
    }

    file.close();

    if (!found)
    {
        cout << "\nStudent not found.\n";
    }
}

void updateStudent()
{
    int rollNo;

    cout << "\nEnter Roll Number to Update: ";
    cin >> rollNo;

    ifstream file("students.txt");
    ofstream tempFile("temp.txt");

    string line;
    bool found = false;

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);

        string roll;
        string name;
        string age;
        string course;
        string marks;

        getline(ss, roll, ',');
        getline(ss, name, ',');
        getline(ss, age, ',');
        getline(ss, course, ',');
        getline(ss, marks);

        if (stoi(roll) == rollNo)
        {
            found = true;

            Student s;

            s.rollNo = rollNo;

            cin.ignore();

            cout << "Enter New Name: ";
            getline(cin, s.name);

            cout << "Enter New Age: ";
            cin >> s.age;

            cin.ignore();

            cout << "Enter New Course: ";
            getline(cin, s.course);

            cout << "Enter New Marks: ";
            cin >> s.marks;

            tempFile << s.rollNo << ","
                     << s.name << ","
                     << s.age << ","
                     << s.course << ","
                     << s.marks << endl;
        }
        else
        {
            tempFile << line << endl;
        }
    }

    file.close();
    tempFile.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
    {
        cout << "\nStudent updated successfully.\n";
    }
    else
    {
        cout << "\nStudent not found.\n";
    }
}

void deleteStudent()
{
    int rollNo;

    cout << "\nEnter Roll Number to Delete: ";
    cin >> rollNo;

    ifstream file("students.txt");
    ofstream tempFile("temp.txt");

    string line;
    bool found = false;

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);

        string roll;
        getline(ss, roll, ',');

        if (stoi(roll) == rollNo)
        {
            found = true;
        }
        else
        {
            tempFile << line << endl;
        }
    }

    file.close();
    tempFile.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
    {
        cout << "\nStudent deleted successfully.\n";
    }
    else
    {
        cout << "\nStudent not found.\n";
    }
}

int main()
{
    int choice;

    do
    {
        cout << "\n==============================\n";
        cout << "   STUDENT MANAGEMENT SYSTEM\n";
        cout << "==============================\n";

        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addStudent();
            break;

        case 2:
            displayStudents();
            break;

        case 3:
            searchStudent();
            break;

        case 4:
            updateStudent();
            break;

        case 5:
            deleteStudent();
            break;

        case 6:
            cout << "\nExiting program...\n";
            break;

        default:
            cout << "\nInvalid choice. Try again.\n";
        }

    } while (choice != 6);

    return 0;
}