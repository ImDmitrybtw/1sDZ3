/* 
1sDZ3.cpp
Разработать программу строковый «калькулятор».

По запросу с клавиатуры в консольном приложении вводится
строка, которая может содержать: знаки операций +,-,*,/; константы
(целые или вещественные). Строка задает некоторое правильное
математическое выражение (формулу в инфиксной форме),
программа вычисляет значение, выдает результат.

В формуле дополнительно использовать скобки () для задания
приоритета операций, а также проверку правильности введенного
выражения, в случае ошибок ввода выдавать сообщения об ошибках.

В формуле дополнительно использовать имена функций sin,
cos, tg, ctg, exp; а также переменную x. После проверки
правильности формулы запрашивается значение переменной x, если
переменная есть в формуле, и вычисляется результат
*/

//Пауль Дмитрий ИУ8-13
//2021

#include <iostream>
#include <cmath>
#include <string>
#include <stack>
#include <vector>
#include <set>
#include <map>
#include <exception> 
#include <algorithm> 

using namespace std;

bool check_num(const string& num) {
    bool ch;
    try
    {
        double dnum = stod(num);
        ch = true;
    }
    catch (std::exception& err)
    {
        ch = false;
    }
    return ch;
}

bool push_num(string& num, vector<string>& in) {
    if (num != "") {
        if (check_num(num))
            in.push_back(num);
        else
            return false;
        num = "";
        return true;
    }
    else
        return true;
}

bool calc(stack<string>& st_func, stack<double>& st_val) {
    if (st_val.empty()) {
        cerr << "Неверный формат ввода: у одной из функций не хватает операндов\n";
        return false;
    }
    string t = st_func.top();
    st_func.pop();
    if (t == "cos") {
        double val = st_val.top();
        st_val.top() = cos(val);
    }
    else if (t == "tg") {
        double val = st_val.top();
        st_val.top() = tan(val);
    }
    else if (t == "ctg") {
        double val = st_val.top();
        st_val.top() = 1 / tan(val);
    }
    else if (t == "sin") {
        double val = st_val.top();
        st_val.top() = sin(val);
    }
    else if (t == "exp") {
        double val = st_val.top();
        st_val.top() = exp(val);
    } 
    else if (t == "u-") {
        double val = st_val.top();
        st_val.top() = -val;
    } 
    else if (static_cast<int>(st_val.size()) == 1) {
        cerr << "Неверный формат ввода: у одной из функций не хватает операндов\n";
        return false;
    }
    else if (t == "*") {
        double val1 = st_val.top();
        st_val.pop();
        double val2 = st_val.top();
        st_val.pop();
        st_val.push(val2 * val1);
    }
    else if (t == "/") {
        double val1 = st_val.top();
        st_val.pop();
        double val2 = st_val.top();
        st_val.pop();
        if (val1 == 0) {
            cerr << "Деление на ноль\n";
            return false;
        }
        st_val.push(val2 / val1);
    }
    else if (t == "+") {
        double val1 = st_val.top();
        st_val.pop();
        double val2 = st_val.top();
        st_val.pop();
        st_val.push(val2 + val1);
    }
    else if (t == "-") {
        double val1 = st_val.top();
        st_val.pop();
        double val2 = st_val.top();
        st_val.pop();
        st_val.push(val2 - val1);
    }
    return true;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    map<string, int> prior = {
        {"(", 0}, {")", 0},
        {"u-", 1},
        {"cos", 2}, {"sin", 2}, {"tg", 2}, {"ctg", 2}, {"exp", 2}, //Триг ф-ии считают в радианах
        {"*", 3}, {"/", 3},
        {"+", 4}, {"-", 4} };
    stack<string> st_func;
    stack<double> st_val;
    string input;
    string num = "";

    std::cout << "Введите математическое выражение\n";
    getline(cin, input);
    input.erase(remove(input.begin(), input.end(), ' '), input.end());
    vector<string> in;
    
    int psp = 0; //Счетчик для проверки правильной скобочной последовательности
    //Разбиваем данные на функции и числа
    for (int i = 0; i != static_cast<int>(input.size()); i++) {
        char symb = input[i];
        switch (symb) {
        case '+':
            if (!push_num(num, in)) {
                cerr << "Неверный формат ввода\n";
                return 1;
            }
            in.push_back("+");
            continue;
        case '-':
            if (!push_num(num, in)) {
                cerr << "Неверный формат ввода\n";
                return 1;
            }
            in.push_back("-");
            continue;
        case '/':
            if (!push_num(num, in)) {
                cerr << "Неверный формат ввода\n";
                return 1;
            }
            in.push_back("/");
            continue;
        case '*':
            if (!push_num(num, in)) {
                cerr << "Неверный формат ввода\n";
                return 1;
            }
            in.push_back("*");
            continue;
        case 'c':
            if (!push_num(num, in)) {
                cerr << "Неверный формат ввода\n";
                return 1;
            }
            if (i + 2 >= static_cast<int>(input.size())) {
                cerr << "Неверный формат ввода\n";
                return 1;
            }
            if (input[i + 1] == 'o' && input[i + 2] == 's') {
                in.push_back("cos");
                i += 2;
                continue;
            }
            if (input[i + 1] == 't' && input[i + 2] == 'g') {
                in.push_back("ctg");
                i += 2;
                continue;
            }
            cerr << "Неверный формат ввода\n";
            return 1;
        case 's':
            if (!push_num(num, in)) {
                cerr << "Неверный формат ввода\n";
                return 1;
            }
            if (i + 2 >= static_cast<int>(input.size())) {
                cerr << "Неверный формат ввода\n";
                return 1;
            }
            if (input[i + 1] == 'i' && input[i + 2] == 'n') {
                in.push_back("sin");
                i += 2;
                continue;
            }
            cerr << "Неверный формат ввода\n";
            return 1;
        case 't':
            if (!push_num(num, in)) {
                cerr << "Неверный формат ввода\n";
                return 1;
            }
            if (i + 1 >= static_cast<int>(input.size())) {
                cerr << "Неверный формат ввода\n";
                return 1;
            }
            if (input[i + 1] == 'g') {
                in.push_back("tg");
                i++;
                continue;
            }
            cerr << "Неверный формат ввода\n";
            return 1;
        case 'e':
            if (!push_num(num, in)) {
                cerr << "Неверный формат ввода\n";
                return 1;
            }
            if (i + 2 >= static_cast<int>(input.size())) {
                cerr << "Неверный формат ввода\n";
                return 1;
            }
            if (input[i + 1] == 'x' && input[i + 2] == 'p') {
                in.push_back("exp");
                i += 2;
                continue;
            }
            cerr << "Неверный формат ввода\n";
            return 1;
        case 'x':
            if (!push_num(num, in)) {
                cerr << "Неверный формат ввода\n";
                return 1;
            }
            in.push_back("x");
            continue;
        case '(':
            if (!push_num(num, in)) {
                cerr << "Неверный формат ввода\n";
                return 1;
            }
            in.push_back("(");
            psp++;
            continue;
        case ')':
            if (!push_num(num, in)) {
                cerr << "Неверный формат ввода\n";
                return 1;
            }
            in.push_back(")");
            psp--;
            if (psp < 0) {
                cerr << "Неверный формат ввода\n";
                return 1;
            }
            continue;
        default:
            num += symb;
            if(i == static_cast<int>(input.size()) - 1)
                if (!push_num(num, in)) {
                    cerr << "Неверный формат ввода\n";
                    return 1;
                }
        }
    }
    if (psp != 0) {
        cerr << "Неверный формат ввода\n";
        return 1;
    }

    //Ввод x
    for (auto i = 0; i != static_cast<int>(in.size()); ++i)
        if (in[i] == "x") {
            string x;
            std::cout << "Введите значение x\n";
            getline(cin, x);
            if (!check_num(x)) {
                cerr << "Некорректое значение x\n";
                return 1;
            }
            transform(in.begin(), in.end(), in.begin(), [x](string a) { return a == "x"? x : a; });
            break;
        }
    //Алгоритм вычисления
    for (auto i = 0; i != static_cast<int>(in.size()); ++i) {
        string t = in[i];
        if (prior.find(t) != prior.end()) {//Если это не число
            if (t == ")") {
                while (st_func.top() != "(")
                    if (!calc(st_func, st_val)) {return 2;}
                st_func.pop();
                continue;
            }
            if (st_func.empty()) {
                if (t == "-" && st_val.empty()) {
                    st_func.push("u-");
                    continue;
                }
                st_func.push(t);
                continue;
            }
            if (in[i - 1] == "(") {
                if (t == "-") {
                    st_func.push("u-");
                    continue;
                }
            }
            while (prior[st_func.top()] <= prior[t]) {//Выполняем все операции большего приоритета до данной операции
                if (st_func.top() == "(") {
                    break;
                }
                if (!calc(st_func, st_val)) { return 2; }
                if (st_func.empty()) {
                    break;
                }
            }
            st_func.push(t);
        }
        else st_val.push(stod(t));
    }
    //Вывод результата
    while (!st_func.empty())
        if (!calc(st_func, st_val)) return 2;
    cout << "Результат: " << st_val.top();
    return 0;
}
