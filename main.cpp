#include <iostream>
#include "init.h"

using namespace std;

int main() {
    Init<char> *init = new Init<char>();
    if (init->inputHTMF() != 0) {
        cout << "录入字符集出现异常,程序终止." << endl;
        return 0;
    }
    else {
        init->print();
        init->preOrder();
//        init->saveToFile();
//        cout << "执行createHFMC()" << endl;
//        init->createHFMC();
    }

    return 0;
}