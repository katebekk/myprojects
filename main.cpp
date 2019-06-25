#include <iostream>
#include <string.h>

using namespace std;

struct StringDlElem {
    char val;
    StringDlElem *next;
    StringDlElem *prev;
};

class StringDl {
    StringDlElem *L, *R;

    void add(char elem) {
        StringDlElem *elemStr = new StringDlElem;
        elemStr->val = elem;
        if (L == NULL) {
            L = R = elemStr;
            elemStr->next = NULL;
            elemStr->prev = NULL;
        } else {
            elemStr->next = L;
            L->prev = elemStr;
            L = elemStr;
            L->prev = NULL;
        }
    }

public:

    StringDl(const char *elem = "") {
        int numb = strlen(elem);
        L = R = NULL;
        for (int i = 0; i < numb; i++) {
            add(elem[i]);
        }

    }

    ~StringDl() {
        while (R != nullptr) {
            R = L->next;
            delete L;
            L = R;
        }
    }


    int length() {//длина строки
        StringDlElem *cur;
        cur = L;
        int numb = 0;
        if (cur == NULL) {
            return 0;
        } else {
            while (cur != NULL) {
                cur = cur->next;
                numb++;
            }
            return numb;
        }
    }

    int Pos(char *str) {//позиция подстроки в строке
        StringDl new_str(str);
        int pos = this->Pos(new_str);
        return pos;
    }

    int Pos(StringDl StringDl) {//позиция подстроки в строке

        StringDlElem *cur1 = R;
        StringDlElem *cur2 = R;
        StringDlElem *cur3 = StringDl.R;
        StringDlElem *cur4 = StringDl.R;
        int len = StringDl.length();
        int i = 0, j = 0;
        while ((cur1 != NULL) && (j != len)) {
            if (cur1->val == cur3->val) {
                while ((cur2 != NULL) && (j != len) && (cur2->val == cur4->val)) {
                    j++;
                    cur2 = cur2->prev;
                    cur4 = cur4->prev;
                }
                if (j != len) {
                    j = 0;
                    i++;
                    cur1 = cur1->prev;
                    cur2 = cur1;

                    cur4 = cur3;
                }

            } else {
                j = 0;
                i++;
                cur1 = cur1->prev;
                cur2 = cur1;

                cur4 = cur3;
            }
        }
        if (j == len) {
            return i;
        } else return -1;
    }


    int DelSub(StringDl StringDl) {
        int sub_pos = Pos(StringDl);
        if (sub_pos == -1) return -1;
        int k = 0;
        int len = StringDl.length();
        StringDlElem *cur1 = R;
        StringDlElem *cur2 = R;
        if (len == length()) {
            R = L = NULL;
            return 0;

        }
        while (k < sub_pos - 1) {
            cur1 = cur1->prev;
            k++;
        }
        k = 0;
        cur2 = cur1;
        while ((k < len)) {
            cur2 = cur2->prev;
            k++;
        }
        if (sub_pos == 0) {
            cur2->next = NULL;
            R = cur2;
            return 0;
        }
        if (cur2->prev == NULL) {
            cur1->prev = NULL;
            L = cur1;
            return 0;
        }
        cur1->prev = cur2;
        cur2->next = cur1;
        return 0;
    }

    int DelSub(char *DelSub) {
        StringDl new_str(DelSub);
        return this->DelSub(new_str);

    }

    int DelSub(size_t l, size_t r) {//l- с какого символа,r- сколько символов
        int sub_pos = l;
        int k = 0;
        StringDlElem *cur1 = R;
        StringDlElem *cur2 = R;
        if ((l == 0) && (r == length())) {
            R = L = NULL;
            return 0;
        }
        if ((sub_pos + r) > length()) {
            return -1;
        }
        if (sub_pos == 0) {
            while (k < r - 1) {
                cur2 = cur2->prev;
                k++;
            }
            cur2 = cur2->prev;
            R = cur2;
            R->next = NULL;
            return 0;
        }
        while (k < sub_pos - 1) {
            cur1 = cur1->prev;
            k++;
        }
        k = 0;

        while (k < r + sub_pos - 1) {
            cur2 = cur2->prev;
            k++;
        }

        if (cur2->prev == NULL) {
            L = cur1;
            cur1->prev = NULL;
            return 0;
        }
        //cur1 = cur1->next;
        cur2 = cur2->prev;
        cur1->prev = cur2;
        cur2->next = cur1;

        return 0;
    }

    void SubStr(StringDl &str_return, size_t first, size_t numb) {

        size_t k = 0;
        StringDlElem *cur1 = R;
        int len = length();
        if (len >= first + numb) {
            while (k < first) {
                cur1 = cur1->prev;
                k++;
            }
            k = 0;
            while (k < numb) {
                str_return.add(cur1->val);
                cur1 = cur1->prev;
                k++;
            }
        }
    }


    StringDl(StringDl &StringDl1) {//конструктор копирования
        StringDlElem *cur1 = StringDl1.R;
        L = R = NULL;
        while (cur1 != NULL) {
            add(cur1->val);
            cur1 = cur1->prev;
        }
    }

    StringDl &operator+(StringDl &rightch) {
        StringDl right(rightch);
        StringDlElem *cur1 = right.R;
        while (cur1 != NULL) {
            add(cur1->val);
            cur1 = cur1->prev;
        }
        return *this;

    }

    StringDl &operator+(char *rightch) {
        StringDl right(rightch);
        StringDlElem *cur1 = right.R;
        while (cur1 != NULL) {
            add(cur1->val);
            cur1 = cur1->prev;
        }
        return *this;

    }


    StringDl &operator=(StringDl right) {
        //StringDl *stringDl1 = new StringDl(right);
        if (this == &right) {
            return *this;
        }
        R = L = NULL;
        StringDlElem *cur1 = right.R;
        while (cur1 != NULL) {
            add(cur1->val);
            cur1 = cur1->prev;
        }
        return *this;
    }

    StringDl &operator=(char *right) {
        //StringDl *stringDl1 = new StringDl(right);
        StringDl stringDl(right);
        if (this == &stringDl) {
            return *this;
        }
        R = L = NULL;
        StringDlElem *cur1 = stringDl.R;
        while (cur1 != NULL) {
            add(cur1->val);
            cur1 = cur1->prev;
        }
        return *this;
    }

    void print() {
        StringDlElem *cur = R;
        if (R == NULL) {
            cout << "пустая строка";
            cout << endl;
        } else {
            while (cur != NULL) {
                cout << cur->val;
                cur = cur->prev;
            }
            cout << endl;
        }
    }

};

void Replacement(StringDl &s, StringDl s1, StringDl s2) {
    StringDl str1(s);
    StringDl str2(s);
    StringDl str3(s2);
    StringDl str4(s1);
    StringDl str("");
    int lens = str1.length();
    int lens1 = str4.length();
    int pos = str1.Pos(str4);
    if (pos == -1) {
        s = str1;
    } else {
        str1.DelSub(pos, lens - pos);
        str2.DelSub(0, pos + lens1);
        str = str1 + str3;
        str = str + str2;
        s = str;
    }
}


int main() {
    StringDl stringDl;
    StringDl stringDl1("Hello");
    StringDl stringDl2("world");
    StringDl stringDl3("l");
    StringDl stringDl4;
    Replacement(stringDl1, stringDl3, stringDl1);
    StringDl stringDl5;
    stringDl1.print();


    return 0;
}