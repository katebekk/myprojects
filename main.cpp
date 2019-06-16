#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <cmath>


using namespace std;

class ReadFile {
public:
    size_t GetExampleNumber(string path) {
        size_t ex_numb;
        ifstream fin;
        fin.open(path, ios_base::in);
        if (fin.is_open()) {
            fin >> ex_numb;
            fin.close();
            return ex_numb;

        } else {
            cout << "File not found!";
            fin.close();
        }
    }

    string GetExample(string path) {
        int a = 1;
        string str;
        ifstream fin(path);
        if (fin.is_open()) {
            while (!fin.eof()) {
                getline(fin, str);
                if (a == 2) break;
                ++a;
            }
            fin.close();
            return str;

        } else {
            cout << "File not found!";
            fin.close();
        }
    }

};

class Parser {
public:
    int *ParseringNumbs(string example) {
        size_t length_ex = example.length();
        int *result = new int[length_ex];
        int num = 0;
        string sty;
        int i = 0, j = 0;
        for (int k = 0; k < length_ex; k++) {
            result[k] = 0;
        }

        while ((i < length_ex)) {
            while (isdigit(example[i])) {
                i++;
            }
            if (i > j) {
                sty = example.substr(j, i - j);
                result[num] = stoi(sty);
                num++;
            } else if (example[i] == 'x') {

                result[num] = 1;
                num++;
            }
            if ((example[i] == 'x') && (example[i + 1] == '2')) {
                i += 3;
            } else i++;
            j = i;
        }

        return result;
    }

    string *ParseringOps(string example) {
        size_t length_ex = example.length();
        string *result = new string[length_ex];
        int num = 0;
        string sty;
        int i = 1, j = 1;
        if ((example[0]) == '-') {
            result[num] = example[0];
            num++;
        } else {
            result[num] = '+';
            num++;
        }
        while ((i < length_ex)) {
            while (isdigit(example[i])) {
                j++;
                i++;
            }
            if ((example[i] == 'x') && (example[i + 1] == '2')) {
                i += 2;
            } else i++;
            if (i > j) {
                sty = example.substr(j, i - j);
                result[num] = sty;
                num++;
                j = i;
            }

        }
        if (num < length_ex) {
            result[num] = '!';
        }
        return result;
    }

};


class ExSolutionInterface {
public:
    virtual double *solution(string ex) = 0;
};

class ExSolution1 : public ExSolutionInterface {
    Parser parser;
public:
    double *solution(string example) override {
        double *answ = new double[2];
        int *var = parser.ParseringNumbs(example);
        string *oop = parser.ParseringOps(example);
        double D, x1, x2;
        double a = var[0], b = var[1], c = var[2] - var[3];
        if (oop[0] == "-") {//проверка на знаки
            a = -a;
        }
        if (oop[2] == "-") {//проверка на знаки
            b = -b;
        }
        if (oop[4] == "-") {//проверка на знаки
            c = -c;
        }

        D = b * b - 4 * a * c;
        try
        {
            if (D <= 0)throw 1;
        }
        catch(int i)
        {
            cout << "Ошибка №" << i << " - нет корней" << endl;
        }
        x1 = (-b - sqrt(D)) / (2 * a);
        x2 = (-b + sqrt(D)) / (2 * a);
        answ[0] = x1;
        answ[1] = x2;
        return answ;
    }
};

class ExSolution2 : public ExSolutionInterface {
    Parser parser;
public:
    double *solution(string example) override {
        double *answ = new double[1];
        int *var = parser.ParseringNumbs(example);
        string *oop = parser.ParseringOps(example);
        answ[0] = var[0] + var[1];
        return answ;
    }
};

class ExSolution3 : public ExSolutionInterface {
    Parser parser;
public:
    double *solution(string example) override {
        double *answ = new double[1];
        int *var = parser.ParseringNumbs(example);
        string *oop = parser.ParseringOps(example);
        answ[0] = var[0] - var[1];
        return answ;
    }
};

class ExSolution4 : public ExSolutionInterface {
    Parser parser;
public:
    double *solution(string example) override {
        double *answ = new double[1];
        int *var = parser.ParseringNumbs(example);
        string *oop = parser.ParseringOps(example);
        answ[0] = var[0] * var[1];
        return answ;
    }

};

class ExSolution5 : public ExSolutionInterface {
    Parser parser;
public:
    double *solution(string example) override {
        double *answ = new double[1];
        double x1,x2;
        int *var = parser.ParseringNumbs(example);
        string *oop = parser.ParseringOps(example);
        try
        {
            if (var[1] == 0)throw 2;
        }
        catch(int i)
        {
            cout << "Ошибка №" << i << " - на 0 делить нельзя!!!!" << endl;
        }
        x1 = var[0];
        x2 = var[1];
        answ[0] = x1/x2;

        return answ;
    }

};

class SolutionsLib {
private:
    vector<ExSolutionInterface *> allSolutions;

public:

    void addSolution(ExSolutionInterface *solution) {
        allSolutions.push_back(solution);
    }

    ExSolutionInterface *returnSolution(int exNumb) {
        return allSolutions[exNumb - 1];

    }
};

class Printer {
public:
    void print(double *answ, int ex_numb, string example) {
        if (ex_numb == 1) {
            cout << example << endl;
            if (answ == 0) {
                cout << " корней нет" << endl;
            } else {
                cout << "x1 = " << answ[0] << endl << "x2 = " << answ[1] << endl;
            }
        } else {
            if (answ == 0) {
                cout << "нет решения" << endl;
            } else {
                cout << example << " = " << answ[0] << endl;
            }
        };
    }

};

class Calculator {
    SolutionsLib *solutionsLib;
    ReadFile reader;
    Printer printer;

public:
    Calculator(SolutionsLib *solutionsLib, ReadFile reader, Printer printer)
            : solutionsLib(solutionsLib), reader(reader), printer(printer) {
    }

    ExSolutionInterface *setSolution(string path) {
        size_t exNumb = reader.GetExampleNumber(path);
        return solutionsLib->returnSolution(exNumb);
    }

    void calcSolution(string path) {
        ExSolutionInterface *exSolution;
        exSolution = setSolution(path);
        double *answ = exSolution->solution(reader.GetExample(path));
        printer.print(answ, reader.GetExampleNumber(path), reader.GetExample(path));
    }

};

int main() {
    ReadFile readFile;
    Printer printer;
    string path1 = "C:/cprojects/Repositorii/primerchiki/files/f1";
    string path2 = "C:/cprojects/Repositorii/primerchiki/files/f2";
    string path3= "C:/cprojects/Repositorii/primerchiki/files/f3";
    string path4 = "C:/cprojects/Repositorii/primerchiki/files/f4";
    string path5 = "C:/cprojects/Repositorii/primerchiki/files/f5";
    SolutionsLib solutionsLib;
    ExSolution1 exSol1;
    ExSolution2 exSol2;
    ExSolution3 exSol3;
    ExSolution4 exSol4;
    ExSolution5 exSol5;
    solutionsLib.addSolution(&exSol1);
    solutionsLib.addSolution(&exSol2);
    solutionsLib.addSolution(&exSol3);
    solutionsLib.addSolution(&exSol4);
    solutionsLib.addSolution(&exSol5);

    Calculator calculator(&solutionsLib, readFile, printer);
    calculator.calcSolution(path1);
    calculator.calcSolution(path2);
    calculator.calcSolution(path3);
    calculator.calcSolution(path4);
    calculator.calcSolution(path5);


    return 0;

}