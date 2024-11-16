#include <iostream> 
#include <Windows.h>
#include <sstream>
#include <map>
#include <fstream>
#include <algorithm>

using namespace std;

void read(string& txt);
void record(const string& new_txt);
void count(const string& txt);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string txt;
    int choice;

    cout << "Меню:\n1. Зчитати текст з файлу\n2. Додати текст до файлу і після цього зчитать його\n";
    cout << "Виберіть опцію (1 або 2): ";
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        read(txt);
        if (txt.empty()) {
            cout << "Тексту в файлі немає!" << endl;
            return 0;
        }
    }
    else if (choice == 2) {
        cout << "Введіть текст для додавання до файлу: ";
        string new_txt;
        getline(cin, new_txt);
        record(new_txt);
        read(txt);
    }
    else {
        cout << "Невірний вибір!" << endl;
        return 1;
    }

    count(txt);

    return 0;
}

void read(string& txt) {
    ifstream text_file("text.txt");
    if (!text_file) {
        cout << "Файл не знайдено. Введіть текст для збереження в файл: ";
        string new_txt;
        getline(cin, new_txt);
        record(new_txt);
        txt = new_txt;
    }
    else {
        getline(text_file, txt, '\0');
        text_file.close();
    }
}

void record(const string& new_txt) {
    ofstream info_file("text.txt", ios::app);
    if (!info_file) {
        cout << "Не вдалося відкрити файл для запису" << endl;
        return;
    }
    info_file << new_txt << endl;
    info_file.close();
}

void count(const string& txt) {
    string word;
    map<string, int> num_word;

    stringstream txt_ss(txt);

    while (txt_ss >> word) {
        while (!word.empty() && (word[0] == ',' || word[0] == '.' || word[0] == '!' || word[0] == '?')) {
            word.erase(word.begin());
        }
        while (!word.empty() && (word[word.size() - 1] == ',' || word[word.size() - 1] == '.' || word[word.size() - 1] == '!' || word[word.size() - 1] == '?')) {
            word.pop_back();
        }

        if (!word.empty()) {
            num_word[word]++;
        }
    }

    cout << "\nПідрахунок слів: " << endl;
    for (auto it = num_word.begin(); it != num_word.end(); it++) {
        cout << it->first << ": " << it->second << endl;
    }

    int max = 0;
    for (auto it = num_word.begin(); it != num_word.end(); it++) {
        if (it->second > max) {
            max = it->second;
        }
    }

    cout << "\nНайбільш часто вживані слова: ";
    bool first = true;
    for (auto it = num_word.begin(); it != num_word.end(); it++) {
        if (it->second == max) {
            if (!first) {
                cout << ", ";
            }
            cout << it->first;
            first = false;
        }
    }

    cout << " (вжито " << max << " разів)" << endl;

    ofstream info_file("info.txt");
    if (!info_file) {
        cout << "Не вдалося відкрити файл для запису" << endl;
        return;
    }

    for (auto it = num_word.begin(); it != num_word.end(); it++) {
        info_file << it->first << ": " << it->second << endl;
    }

    info_file << "\nНайбільш часто вживані слова: ";
    first = true;
    for (auto it = num_word.begin(); it != num_word.end(); it++) {
        if (it->second == max) {
            if (!first) {
                info_file << ", ";
            }
            info_file << it->first;
            first = false;
        }
    }

    info_file << " (вжито " << max << " разів)" << endl;

    info_file.close();
}
