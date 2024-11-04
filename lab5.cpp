
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Student
{
    string Name;
    string GroupId;
    vector<unsigned> Ratings;
    vector<string> Subjects;

    void show() {
        cout << "name - " << Name << endl;
        cout << "group ID - " << GroupId << endl;
        for (int i = 0; i < Ratings.size(); i++) {
            cout << Subjects[i] << " - " << Ratings[i] << endl;
        }
        cout << "-----------------------------------" << endl;
    }

    float mean() {
        int sum = 0;
        for (auto i : Ratings) {
            sum += i;
        }
        return sum / Ratings.size();
    }
};

struct Group
{
    string Id;
    vector<Student> Students;

    void show() {
        cout << "ID - " << Id << endl;
        cout << "STUDENTS:" << endl;
        for (auto i : Students) {
            i.show();
        }
        cout << "=====================================================================" << endl;
    }
};

void SortByName(vector<Student>& v) {
    sort(v.begin(), v.end(), [](Student& first, Student& second) {
        return first.Name < second.Name;
        });
}

void SortByRating(vector<Student>& v) {
    sort(v.begin(), v.end(), [](Student& first, Student& second) {
        return first.mean() > second.mean();
        });
}

size_t CountExcellent(const vector<Student>& v) {
    size_t exc = 0;
    for (auto st : v) {
        if (st.mean() == 5) {
            exc++;
        }
    }
    return exc;
}

size_t CountTwoness(const vector<Student>& v) {
    size_t two = 0;
    for (auto st : v) {
        if (find(st.Ratings.begin(), st.Ratings.end(), 2) != st.Ratings.end()) {
            two++;
        }
    }
    return two;
}

vector<Student> VectorMathExcellent(const vector<Student>& v) {
    vector<Student> res;
    for (auto st : v) {
        for (int i = 0; i < st.Subjects.size(); i++) {
            if (st.Subjects[i] == "Math" && st.Ratings[i] == 5) {
                res.push_back(st);
            }
        }
    }
    return res;
}
vector<string> GroupsId(const vector<Student>& v) {
    vector<string> res = {};
    for (auto i : v) {
        if (find(res.begin(), res.end(), i.GroupId) == res.end()) {
            res.push_back(i.GroupId);
        }
    }
    return res;
}

vector<Group> Groups(const vector<Student>& v) {
    vector<string> groups = GroupsId(v);
    vector<Group> res;
    for (auto i : groups) {
        res.push_back(Group{ i, });
    }
    for (auto i : v) {
        for (int j = 0; j < res.size(); j++) {
            if (i.GroupId == res[j].Id) {
                res[j].Students.push_back(i);
            }
        }
    }
    return res;
}

int main()
{
    vector<Student> students = {
     {"Ivan", "Group1", {5, 5}, {"Math", "Physics"}},
     {"Oleg", "Group2", {5, 5}, {"Math", "Physics"}},
     {"Sergey", "Group3", {4, 5}, {"Math", "Physics"}},
     {"Leonid", "Group3", {5, 2}, {"Math", "Physics"}}
    };
    SortByRating(students);
    for (auto i : students) {
        i.show();
    }

    cout << CountExcellent(students) << endl;
    cout << CountTwoness(students) << endl;
    vector<Student> task = VectorMathExcellent(students);
    vector<Group> groups =  Groups(students);
    for (auto i : groups) {
        i.show();
    }
}
