#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <vector>
#include <iostream>

class Student {
public:
    Student(int rollNo, const std::string& name, float marks)
        : rollNo(rollNo), name(name), marks(marks) {}

    int getRollNo() const {
        return rollNo;
    }

    std::string getName() const {
        return name;
    }

    float getMarks() const {
        return marks;
    }

private:
    int rollNo;
    std::string name;
    float marks;
};

class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void addStudent();
    void displayStudents();

private:
    std::vector<Student> students;
    QLineEdit *rollNoEdit;
    QLineEdit *nameEdit;
    QLineEdit *marksEdit;
};

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout;

    QLabel *titleLabel = new QLabel("Student Management System", this);
    mainLayout->addWidget(titleLabel);

    QHBoxLayout *addLayout = new QHBoxLayout;
    QLabel *addLabel = new QLabel("Add Student:", this);
    addLayout->addWidget(addLabel);

    rollNoEdit = new QLineEdit(this);
    rollNoEdit->setPlaceholderText("Roll No");
    addLayout->addWidget(rollNoEdit);

    nameEdit = new QLineEdit(this);
    nameEdit->setPlaceholderText("Name");
    addLayout->addWidget(nameEdit);

    marksEdit = new QLineEdit(this);
    marksEdit->setPlaceholderText("Marks");
    addLayout->addWidget(marksEdit);

    QPushButton *addButton = new QPushButton("Add", this);
    connect(addButton, &QPushButton::clicked, this, &MainWindow::addStudent);
    addLayout->addWidget(addButton);

    mainLayout->addLayout(addLayout);

    QPushButton *displayButton = new QPushButton("Display Students", this);
    connect(displayButton, &QPushButton::clicked, this, &MainWindow::displayStudents);
    mainLayout->addWidget(displayButton);

    setLayout(mainLayout);
}

void MainWindow::addStudent() {
    int rollNo = rollNoEdit->text().toInt();
    std::string name = nameEdit->text().toStdString();
    float marks = marksEdit->text().toFloat();

    students.push_back(Student(rollNo, name, marks));

    rollNoEdit->clear();
    nameEdit->clear();
    marksEdit->clear();

    QMessageBox::information(this, "Success", "Student added successfully!");
}

void MainWindow::displayStudents() {
    std::string message = "Students:\n";

    for (const auto& student : students) {
        message += "Roll No: " + std::to_string(student.getRollNo()) + "\n";
        message += "Name: " + student.getName() + "\n";
        message += "Marks: " + std::to_string(student.getMarks()) + "\n\n";
    }

    QMessageBox::information(this, "Student Details", QString::fromStdString(message));
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.setWindowTitle("Student Management System");
    mainWindow.show();

    return app.exec();
}

#include "main.moc"
