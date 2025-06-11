#include "Graf.h"

// Конструктор класса Graf, инициализирует количество вершин нулём
Graf::Graf() : n(0) 
{
}

void Graf::buildFromFile(const string& filename) 
{
    ifstream fin(filename);
    if (!fin) 
    {
        cerr << "Ошибка открытия файла " << filename << endl;
        n = 0;
        matrix.clear();
        return;
    }

    fin >> n;
    if (n <= 0) 
    {
        cerr << "Некорректное количество вершин в файле" << endl;
        n = 0;
        matrix.clear();
        return;
    }

    matrix.assign(n, vector<int>(n, 0));
    bool incorrectValue = false;
    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j < n; ++j) 
        {
            fin >> matrix[i][j];
            if (matrix[i][j] < 0) matrix[i][j] = 0; // защита от отрицательных значений
            // Проверка, чтобы были только 1 или 0 в матрице
            if (matrix[i][j] != 0 && matrix[i][j] != 1)
            {
                cout << "Ошибка: в матрице найдены значения, отличные от 0 и 1. " << "Значение [" << i << "][" << j << "] = " << matrix[i][j] << " будет заменено на 0." << endl;
                matrix[i][j] = 0;
                incorrectValue = true;
            }
        
        }
    }

    fin.close();

    if (incorrectValue)
    {
        cout << "В файле были исправлены некорректные значения матрицы." << endl;
    }

    // Проверка и исправление симметрии
    bool symmetric = true;
    for (int i = 0; i < n && symmetric; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            if (matrix[i][j] != matrix[j][i])
            {
                symmetric = false;
                // Исправляем на максимум из двух значений
                int val = max(matrix[i][j], matrix[j][i]);
                matrix[i][j] = val;
                matrix[j][i] = val;
            }
        }
    }

    if (!symmetric)
    {
        cout << "Внимание: матрица смежности не была симметричной. Она была исправлена автоматически.\n";
    }
}

void Graf::buildFromKeyboard() 
{
    cout << "Введите количество вершин графа: ";
    while (!(cin >> n) || n <= 0) 
    {
        cout << "Некорректный ввод. Введите положительное число: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    matrix.assign(n, vector<int>(n, 0));

    for (int i = 0; i < n; ++i) 
    {
        int count_adj = -1;
        cout << "Введите количество вершин, смежных с вершиной " << (i + 1) << ": ";
        while (!(cin >> count_adj) || count_adj < 0 || count_adj > n) 
        {
            cout << "Некорректное количество. Введите заново: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }

        set<int> adj_set; // Множество для предотвращения повторов смежных вершин
        cout << "Введите номера смежных вершин для вершины " << (i + 1) << " (от 1 до " << n << "): ";
        for (int k = 0; k < count_adj; ++k) 
        {
            int v;
            while (!(cin >> v) || v < 1 || v >= n || adj_set.count(v)) 
            {
                if (adj_set.count(v))
                    cout << "Вершина уже введена. Введите другую: ";
                else
                    cout << "Неверный номер вершины. Введите заново: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }
            adj_set.insert(v);
            matrix[i][v - 1] = 1;
            matrix[v - 1][i] = 1;
        }
    }
}

void Graf::buildRandom() 
{
    cout << "Введите количество вершин графа: ";
    while (!(cin >> n) || n <= 0) 
    {
        cout << "Количество вершин должно быть положительным. Введите заново: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    matrix.assign(n, vector<int>(n, 0));
    srand(static_cast<unsigned int>(time(nullptr)));

    for (int i = 0; i < n; ++i) 
    {
        for (int j = i; j < n; ++j) 
        {
            if (i == j) 
            {
                matrix[i][j] = (rand() % 10 == 0) ? 1 : 0;
            }
            else 
            {
                int val = rand() % 2;
                matrix[i][j] = val;
                matrix[j][i] = val;
            }
        }
    }
}

// Вывод матрицы смежности на экран
void Graf::printMatrix() const 
{
    cout << "Матрица смежности (" << n << "x" << n << "):\n";
    cout << "   ";
    for (int j = 0; j < n; ++j)
        cout << (j + 1) << ' ';
    cout << '\n';

    for (int i = 0; i < n; ++i) 
    {
        cout.width(2);
        cout << (i + 1) << ' '; // Нумерация строк с 1
        for (int j = 0; j < n; ++j)
            cout << matrix[i][j] << ' '; // Вывод значения ячейки матрицы
        cout << '\n';
    }
}

// Вычисление степеней всех вершин графа
vector<int> Graf::computeDegrees() const 
{
    vector<int> degrees(n, 0); // Вектор для хранения степеней

    for (int i = 0; i < n; ++i) 
    {
        int deg = 0;
        for (int j = 0; j < n; ++j) 
        {
            if (i == j) 
            {
                // Петля считается за два ребра в степени вершины
                deg += matrix[i][j] * 2;
            }
            else 
            {
                deg += matrix[i][j];
            }
        }
        degrees[i] = deg;
    }

    return degrees;
}

// Вывод степеней вершин на экран
void Graf::printDegrees() const 
{
    vector<int> degrees = computeDegrees();
    cout << "Степени вершин:\n";
    for (int i = 0; i < n; ++i) 
    {
        cout << "Вершина " << (i + 1) << ": " << degrees[i] << '\n';
    }
}

// Функция для чтения целого числа с проверкой ввода
int readInt(const string& prompt)
{
    int val;
    string line;
    while (true)
    {
        cout << prompt;
        if (!getline(cin, line))
        {
            cout << "Ошибка ввода. Повторите.\n";
            continue;
        }
        stringstream ss(line);
        if (ss >> val)
        {
            char c;
            if (!(ss >> c))
            {
                return val;
            }
        }
        cout << "Неверный ввод. Введите целое число без лишних символов.\n";
    }
}