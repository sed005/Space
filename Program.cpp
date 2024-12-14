#include "Tree.h"
#include <chrono>
#include <iostream>

using namespace std;

int main() {
    int n = 0, kol;
    Tree Tr('a', 'z', 8);
    srand(time(nullptr));
    setlocale(LC_ALL, "Russian");

    auto start1 = chrono::high_resolution_clock::now();
    Tr.MakeTree();
    auto end1 = chrono::high_resolution_clock::now();
    chrono::duration<double> duration1 = end1 - start1;

    if (Tr.exist()) {

        auto start2 = chrono::high_resolution_clock::now();
        kol = Tr.OutTree();
        auto end2 = chrono::high_resolution_clock::now();
        chrono::duration<double> duration2 = end2 - start2;

        cout << "Количество вершин на глубине не более 2: " << kol;
        cout << '\n' << "Обход в глубину: ";

        auto start3 = chrono::high_resolution_clock::now();
        n = Tr.DFS();
        auto end3 = chrono::high_resolution_clock::now();
        chrono::duration<double> duration3 = end3 - start3;

        cout << "\nПройдено узлов = " << n;
        cout << "\nВремя создания дерева: " << duration1.count()<< " секунд." << endl;
        cout << "Время обработки дерева: " << duration2.count()<< " секунд." << endl;
        cout << "Время вывода дерева: " << duration3.count() << " секунд.";
    } else {
        cout << "Дерево пусто!";
    }

    cout << '\n' << "=== Конец ===";
    cin.get();
    return 0;
}
