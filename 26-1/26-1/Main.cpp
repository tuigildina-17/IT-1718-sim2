#include "Graf.h"

int main() 
{
    setlocale(LC_ALL, "ru");
    Graf graph;

    int choice = 0;
    do 
    {
        cout << "Выберите способ построения графа:\n";
        cout << "1. Из файла\n";
        cout << "2. С клавиатуры\n";
        cout << "3. Случайными числами\n";

        choice = readInt("Ваш выбор: ");

        if (choice < 1 || choice > 3) 
        {
            cout << "Неверный выбор. Попробуйте снова.\n";
            choice = 0;
        }
    } while (choice == 0);

    switch (choice) 
    {
    case 1:
        graph.buildFromFile("a.txt");
        break;
    case 2:
        graph.buildFromKeyboard();
        break;
    case 3:
        graph.buildRandom();
        break;
    }

    graph.printMatrix();
    graph.printDegrees();

    return 0;
}