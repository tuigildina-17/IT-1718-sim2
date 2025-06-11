//Дано описание неориентированного графа в текстовом файле с именем FileName.в
//виде матрицы смежности.Первая строка файла содержит количество вершин графа(n), а
//следующие n строк содержат матрицу смежности(m), m[i][j] = 0, если ребра между
//вершинами i и j не существует.Определить степень для каждой вершины графа.Вывести
//степени вершин, перечисляя их в порядке возрастания номеров вершин.Если в графе
//имеются петли, то каждая петля в степени вершины учитывается дважды

#ifndef GRAF_H
#define GRAF_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <set>
#include <sstream>

using namespace std;

class Graf 
{
private:
    int n;
    vector<vector<int>> matrix;

public:
    Graf();

    void buildFromFile(const string& filename);
    void buildFromKeyboard();
    void buildRandom();

    void printMatrix() const;
    void printDegrees() const;

    vector<int> computeDegrees() const;
};

int readInt(const string& prompt);

#endif