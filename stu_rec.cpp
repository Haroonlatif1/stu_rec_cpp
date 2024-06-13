#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Student {
public:
    string name;
    string enrollDate;
    string major;
    double fee;
    bool feePaid;
    string feeReceiptPath;

    Student(string n, string ed, string m, double f) : name(n), enrollDate(ed), major(m), fee(f), feePaid(false), feeReceiptPath("") {}

    void payFee(const string& receiptPath) {
        feePaid = true;
        feeReceiptPath = receiptPath;
        cout << "Fee has been paid for " << name << " and receipt has been submitted." << endl;
    }

    void display() const {
        cout << "Name: " << name << ", Enroll Date: " << enrollDate << ", Major: " << major
             << ", Fee: " << fee << ", Fee Paid: " << (feePaid ? "Yes" : "No")
             << (feePaid ? ", Receipt Path: " + feeReceiptPath : "") << endl;
    }
};

class ManagementSystem {
private:
    vector<Student> students;

public:
    void addStudent(const Student& student) {
        students.push_back(student);
    }

    void displayAllStudents() const {
        for (const auto& student : students) {
            student.display();
        }
    }

    void displayPendingFees() const {
        for (const auto& student : students) {
            if (!student.feePaid) {
                student.display();
            }
        }
    }

    void payFeeForStudent(const string& studentName) {
        for (auto& student : students) {
            if (student.name == studentName) {
                string receiptPath;
                cout << "Enter the file path of the fee receipt: ";
                cin.ignore(); // To ignore the newline character left in the buffer
                getline(cin, receiptPath);
                student.payFee(receiptPath);
                return;
            }
        }
        cout << "Student not found!" << endl;
    }
};

int main() {
    ManagementSystem system;

    // Adding some students
    system.addStudent(Student("Alice", "2023-09-01", "Computer Science", 1500.00));
    system.addStudent(Student("Bob", "2023-09-02", "Mechanical Engineering", 1400.00));
    system.addStudent(Student("Charlie", "2023-09-03", "Electrical Engineering", 1300.00));

    int choice;
    string studentName;

    do {
        cout << "1. Display All Students" << endl;
        cout << "2. Display Students with Pending Fees" << endl;
        cout << "3. Pay Fee for a Student" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                system.displayAllStudents();
                break;
            case 2:
                system.displayPendingFees();
                break;
            case 3:
                cout << "Enter the name of the student: ";
                cin.ignore(); // To ignore the newline character left in the buffer
                getline(cin, studentName);
                system.payFeeForStudent(studentName);
                break;
            case 4:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    } while (choice != 4);

    return 0;
}
