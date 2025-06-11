#include "Graf.h"

// ����������� ������ Graf, �������������� ���������� ������ ����
Graf::Graf() : n(0) 
{
}

void Graf::buildFromFile(const string& filename) 
{
    ifstream fin(filename);
    if (!fin) 
    {
        cerr << "������ �������� ����� " << filename << endl;
        n = 0;
        matrix.clear();
        return;
    }

    fin >> n;
    if (n <= 0) 
    {
        cerr << "������������ ���������� ������ � �����" << endl;
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
            if (matrix[i][j] < 0) matrix[i][j] = 0; // ������ �� ������������� ��������
            // ��������, ����� ���� ������ 1 ��� 0 � �������
            if (matrix[i][j] != 0 && matrix[i][j] != 1)
            {
                cout << "������: � ������� ������� ��������, �������� �� 0 � 1. " << "�������� [" << i << "][" << j << "] = " << matrix[i][j] << " ����� �������� �� 0." << endl;
                matrix[i][j] = 0;
                incorrectValue = true;
            }
        
        }
    }

    fin.close();

    if (incorrectValue)
    {
        cout << "� ����� ���� ���������� ������������ �������� �������." << endl;
    }

    // �������� � ����������� ���������
    bool symmetric = true;
    for (int i = 0; i < n && symmetric; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            if (matrix[i][j] != matrix[j][i])
            {
                symmetric = false;
                // ���������� �� �������� �� ���� ��������
                int val = max(matrix[i][j], matrix[j][i]);
                matrix[i][j] = val;
                matrix[j][i] = val;
            }
        }
    }

    if (!symmetric)
    {
        cout << "��������: ������� ��������� �� ���� ������������. ��� ���� ���������� �������������.\n";
    }
}

void Graf::buildFromKeyboard() 
{
    cout << "������� ���������� ������ �����: ";
    while (!(cin >> n) || n <= 0) 
    {
        cout << "������������ ����. ������� ������������� �����: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    matrix.assign(n, vector<int>(n, 0));

    for (int i = 0; i < n; ++i) 
    {
        int count_adj = -1;
        cout << "������� ���������� ������, ������� � �������� " << (i + 1) << ": ";
        while (!(cin >> count_adj) || count_adj < 0 || count_adj > n) 
        {
            cout << "������������ ����������. ������� ������: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }

        set<int> adj_set; // ��������� ��� �������������� �������� ������� ������
        cout << "������� ������ ������� ������ ��� ������� " << (i + 1) << " (�� 1 �� " << n << "): ";
        for (int k = 0; k < count_adj; ++k) 
        {
            int v;
            while (!(cin >> v) || v < 1 || v >= n || adj_set.count(v)) 
            {
                if (adj_set.count(v))
                    cout << "������� ��� �������. ������� ������: ";
                else
                    cout << "�������� ����� �������. ������� ������: ";
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
    cout << "������� ���������� ������ �����: ";
    while (!(cin >> n) || n <= 0) 
    {
        cout << "���������� ������ ������ ���� �������������. ������� ������: ";
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

// ����� ������� ��������� �� �����
void Graf::printMatrix() const 
{
    cout << "������� ��������� (" << n << "x" << n << "):\n";
    cout << "   ";
    for (int j = 0; j < n; ++j)
        cout << (j + 1) << ' ';
    cout << '\n';

    for (int i = 0; i < n; ++i) 
    {
        cout.width(2);
        cout << (i + 1) << ' '; // ��������� ����� � 1
        for (int j = 0; j < n; ++j)
            cout << matrix[i][j] << ' '; // ����� �������� ������ �������
        cout << '\n';
    }
}

// ���������� �������� ���� ������ �����
vector<int> Graf::computeDegrees() const 
{
    vector<int> degrees(n, 0); // ������ ��� �������� ��������

    for (int i = 0; i < n; ++i) 
    {
        int deg = 0;
        for (int j = 0; j < n; ++j) 
        {
            if (i == j) 
            {
                // ����� ��������� �� ��� ����� � ������� �������
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

// ����� �������� ������ �� �����
void Graf::printDegrees() const 
{
    vector<int> degrees = computeDegrees();
    cout << "������� ������:\n";
    for (int i = 0; i < n; ++i) 
    {
        cout << "������� " << (i + 1) << ": " << degrees[i] << '\n';
    }
}

// ������� ��� ������ ������ ����� � ��������� �����
int readInt(const string& prompt)
{
    int val;
    string line;
    while (true)
    {
        cout << prompt;
        if (!getline(cin, line))
        {
            cout << "������ �����. ���������.\n";
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
        cout << "�������� ����. ������� ����� ����� ��� ������ ��������.\n";
    }
}