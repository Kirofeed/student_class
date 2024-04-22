#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>



using namespace std;

struct SMark {
    std::string Subject;
    int Mark;
    SMark(const std::string& subject, int mark) : Subject(subject), Mark(mark) {}
};

class SStudData
{
    string Name; // фамилия
    int ID; // номер зачетки
    vector <SMark> Marks; // рез-ты сессии – пустой на момент создания
public:
    // конструкторы,
    SStudData(string Name, int ID, vector<SMark> Marks) : Name(Name), ID(ID), Marks(Marks) {}
    // SStudData(SStudData& stud) : Name(stud.Name), ID(stud.ID), Marks(stud.Marks) {}
    // SStudData(SStudData&& stud) : Name(std::move(stud.Name)), ID(stud.ID), Marks(std::move(stud.Marks)) {}
    // перегрузка =
    SStudData& operator=(SStudData& stud) {
        Name = stud.Name;
        Marks = stud.Marks;
        return *this;
    }
    // перегрузка <<
    friend ostream& operator<<(ostream& os, SStudData& stud);
    
    // get-методы,
    const string& getName() const {
        return Name;
    }
    const int getID() const {
        return ID;
    }
    // метод для добавления оценки
    void addMark(const string& subject, int mark) {
        Marks.push_back(SMark(subject, mark));
    }


};


ostream& operator<<(ostream& os, SStudData& stud) {
    os << stud.Name << endl;
    for (const auto& mark : stud.Marks) {
        os << mark.Subject << ": " << mark.Mark << endl;
    }
    return os;
}

vector<SStudData> GetDataFromFile() {
    ifstream in("input.txt");
    if (!in.is_open()) 
    {
        throw "can't open file";
    }
    vector<SStudData> students;
    string line;
    while (getline(in, line))
    {
        string name;
        bool is_name = false;
        int id;
        bool is_id = false;
        vector <SMark> Marks;
        size_t pos = 0;
        while (pos != line.size())
        {
            pos = line.find(";");
            if (pos > line.size()) {
                string subj_mark = line.substr(0, line.size());
                size_t pos_ = subj_mark.find("-");
                string subj = subj_mark.substr(0, pos_);
                subj_mark.erase(0, pos_ + 1);
                int mark = stoi(subj_mark);
                Marks.push_back(SMark(subj, mark));
                SStudData stud(name, id, Marks);
                Marks.clear();
                students.push_back(stud);
                break;
            }
            else {
                if (!is_name)
                {
                    name = line.substr(0, pos);
                    line.erase(0, pos + 1);
                    is_name = true;
                    continue;
                }
                else if (!is_id) {
                    id = stoi(line.substr(0, pos));
                    line.erase(0, pos + 1);
                    is_id = true;
                    continue;
                }
                else {
                    string subj_mark = line.substr(0, pos);
                    line.erase(0, pos + 1);
                    size_t pos_ = subj_mark.find("-");
                    string subj = subj_mark.substr(0, pos_);
                    subj_mark.erase(0, pos_ + 1);
                    int mark = stoi(subj_mark);
                    Marks.push_back(SMark(subj, mark));
                }
            }
        }
        
    }
    return students;
}

// Функция для сравнения студентов по фамилиям
// bool compareByLastName(const Student& a, const Student& b) {
//     // Предполагаем, что фамилия находится первой в поле fullName
//     size_t posA = a.fullName.find_last_of(' ');
//     size_t posB = b.fullName.find_last_of(' ');
//     std::string lastNameA = (posA != std::string::npos) ? a.fullName.substr(posA + 1) : a.fullName;
//     std::string lastNameB = (posB != std::string::npos) ? b.fullName.substr(posB + 1) : b.fullName;

//     return lastNameA < lastNameB;
// }

// // Функция для сравнения студентов по курсам и группам
// bool compareByCourseGroup(const Student& a, const Student& b) {
//     if (a.course != b.course) {
//         return a.course < b.course;
//     }
//     if (a.group != b.group) {
//         return a.group < b.group;
//     }
//     // Предполагаем, что фамилия находится первой в поле fullName
//     size_t posA = a.fullName.find_last_of(' ');
//     size_t posB = b.fullName.find_last_of(' ');
//     std::string lastNameA = (posA != std::string::npos) ? a.fullName.substr(posA + 1) : a.fullName;
//     std::string lastNameB = (posB != std::string::npos) ? b.fullName.substr(posB + 1) : b.fullName;

//     return lastNameA < lastNameB;
// }

bool sort_stud(const SStudData& student1, const SStudData& student2) {
    if (student1.getName() < student2.getName())
    {
        return true;
    }
    else if(student1.getName() == student2.getName()) {
        if (student1.getID() < student2.getID()) 
        {
            return true;
        }
        else {
            return false;
        }        
    }
    else {
        return false;
    }
}


int main() {

    auto vec = GetDataFromFile();

    for (auto i : vec) {
        cout << i << endl;
    }
    sort(vec.begin(), vec.end(), sort_stud);
    cout << endl << endl << endl;
    for (auto i : vec) {
        cout << i << endl;
    }
    // std::ifstream inputFile("Students.txt");
    // if (!inputFile) {
    //     std::cerr << "Ошибка открытия файла Students.txt" << std::endl;
    //     return 1;
    // }

    // std::vector<Student> students;

    // // Чтение данных из файла
    // while (!inputFile.eof()) {
    //     Student student;
    //     std::getline(inputFile, student.fullName, ';');
    //     inputFile >> student.course;
    //     inputFile.ignore(); // Пропускаем символ ';'
    //     std::getline(inputFile, student.group);
    //     students.push_back(student);
    // }

    // // Закрываем файл
    // inputFile.close();

    // // Сортируем студентов по фамилиям
    // std::sort(students.begin(), students.end(), compareByLastName);

    // // Создаем и записываем данные в файл Fio.txt
    // std::ofstream fioFile("Fio.txt");
    // for (const auto& student : students) {
    //     fioFile << student.fullName << "; " << student.course << "; " << student.group << std::endl;
    // }
    // fioFile.close();

    // // Сортируем студентов по курсам и группам
    // std::sort(students.begin(), students.end(), compareByCourseGroup);

    // // Создаем и записываем данные в файл Groups.txt
    // std::ofstream groupsFile("Groups.txt");
    // for (const auto& student : students) {
    //     groupsFile << student.fullName << "; " << student.course << "; " << student.group << std::endl;
    // }
    // groupsFile.close();
}
