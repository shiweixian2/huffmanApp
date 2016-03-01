//
// Created by 密码123 on 16/2/28.
//

#ifndef HUFFMANTEST_INIT_H
#define HUFFMANTEST_INIT_H

#include "Huffman.h"

template<class T>
class Init {
private:
//    //文件的最大长度
//    int maxLen;
//    //字符集大小
//    int n;
//    T datas[];
//    int weights[];

public:
    Huffman<T> *tree;

    //默认构造函数
    Init() { }

    ~Init() { }

    /**
     * Huffman树的构建
     */
    void create(int w[], T a[], int n);

    /**
     * 获得文件的不同字符,权值,及个数
     */
    int inputHTMF();

    /**
     * 前序遍历
     */
    void preOrder();

    //保存Huffman树到文件中
    void saveToFile();

    void print() { tree->print(); }


    //为字符编码
    void createHFMC();


};


template<class T>
int Init<T>::inputHTMF() {
    int n;//字符个数
    int i; //计数器
    cout << "请输入字符集的大小:" << endl;
    cin >> n;
    if (n <= 0)
        return -1;
    T *a = new T[n]; //字符数组
    int *w = new int[n];//权值数组
    cout << "请输入字符集个字符(字符间用空格隔开):" << endl;
    for (i = 0; i < n; i++) {
        cin >> a[i];
    }
    cout << " 请输入字符集各字符的权值(各权值用空格隔开):" << endl;
    for (i = 0; i < n; i++) {
        cin >> w[i];
    }
    cout << "输入结束" << endl;

    //调用构造函数,构建Huffman树
    create(w, a, n);
    return 0;
}

/**
 * 构建Huffman树
 */
template<class T>
void Init<T>::create(int *w, T *a, int n) {
    tree = new Huffman<T>();
    tree->create(w, a, n);
}

/**
 * 前序遍历
 */
template<class T>
void Init<T>::preOrder() { tree->preOrder(); }

template<class T>
void Init<T>::saveToFile() { tree->saveToFile(); }

//template<class T>
//void Init<T>::createHFMC() { tree->createHFMC(); }

#endif //HUFFMANTEST_INIT_H
