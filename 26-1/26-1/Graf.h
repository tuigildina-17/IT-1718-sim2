//���� �������� ������������������ ����� � ��������� ����� � ������ FileName.�
//���� ������� ���������.������ ������ ����� �������� ���������� ������ �����(n), �
//��������� n ����� �������� ������� ���������(m), m[i][j] = 0, ���� ����� �����
//��������� i � j �� ����������.���������� ������� ��� ������ ������� �����.�������
//������� ������, ���������� �� � ������� ����������� ������� ������.���� � �����
//������� �����, �� ������ ����� � ������� ������� ����������� ������

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