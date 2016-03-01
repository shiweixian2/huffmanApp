/**
 * @author 石炜贤
 * @date 2016/02/27
 *
 * 构建霍夫曼树,使用最小堆
 * 利用C++实现
 */

#ifndef HUFFMANTEST_HUFFMAN_H
#define HUFFMANTEST_HUFFMAN_H

#include <iomanip>
#include <iostream>
#include <fstream>
#include "HuffmanNode.h"
#include "MinHeap.h"
#include "SeqStack.h"

using namespace std;

template<class T>
class Huffman {
private:
    HuffmanNode<T> *mRoot; //根节点
    ofstream ofile; //定义输出文件
public:
    SeqStack *seq;

    Huffman();

    ~Huffman();

    //前序遍历"Huffman"树
    void preOrder();

    //中序遍历"Huffman"树
    void inOrder();

    //后序遍历"Huffman"树
    void postOrder();

    //创建Huffman树
    void create(int weights[], T datas[], int size);

    //销毁Huffman树
    void destroy();

    //打印Huffman树
    void print();

    // 保存Huffman树到文件
    void saveToFile();

    void hfmc(HuffmanNode<T> *parent, HuffmanNode<T> *child);

    void push(char code);

    void createHFMC(HuffmanNode<T> *tree);

    void setParent(HuffmanNode<T> *parent);

private:
    //前序遍历"Huffman"树
    void preOrder(HuffmanNode<T> *tree);

    //中序遍历"Huffman"树
    void inOrder(HuffmanNode<T> *tree) const;

    //后序遍历"Huffman"树
    void postOrder(HuffmanNode<T> *tree) const;

    //销毁Huffman树
    void destroy(HuffmanNode<T> *tree);

    //打印Huffman树
    void print(HuffmanNode<T> *tree, int w, int direction);

    // 保存Huffman树到文件
    void saveToFile(HuffmanNode<T> *tree);

};

/**
 * 构造函数
 */
template<class T>
Huffman<T>::Huffman() : mRoot(nullptr) {
}

/**
 * 析构函数
 */
template<class T>
Huffman<T>::~Huffman() {
    destroy();
}

/**
 * 前序遍历Huffman树
 * 构建Huffman编码表
 */
template<class T>
void Huffman<T>::preOrder(HuffmanNode<T> *tree) {
    if (tree != nullptr) {
//        cout << tree->weight << " ";
        if (tree->data != 0) {
            cout << tree->data << " ";
            createHFMC(tree);
        }
        preOrder(tree->left);
        preOrder(tree->right);
    }
}

template<class T>
void Huffman<T>::preOrder() {
    preOrder(mRoot);
}

/**
 * 中序遍历Huffman树
 */
template<class T>
void Huffman<T>::inOrder(HuffmanNode<T> *tree) const {
    if (tree != nullptr) {
        inOrder(tree->left);
        cout << tree->weight << " ";
        inOrder(tree->right);
    }
}

template<class T>
void Huffman<T>::inOrder() {
    inOrder(mRoot);
}

/**
 * 后序遍历Huffman树
 */
template<class T>
void Huffman<T>::postOrder(HuffmanNode<T> *tree) const {
    if (tree != nullptr) {
        postOrder(tree->left);
        postOrder(tree->right);
        cout << tree->weight << " ";
    }
}

template<class T>
void Huffman<T>::postOrder() {
    postOrder(mRoot);
}

/**
 * 创建Huffman树
 *
 * 参数说明:
 *       a:权值数组
 *       size:数组大小
 * 返回值:
 *      Huffman数组的根节点
 */
template<class T>
void Huffman<T>::create(int *weights, T *datas, int size) {
//    cout << "Huffman->create" << endl;
//    ofile.open("/Users/mima123/ClionProjects/huffmanApp/files/hfmtree.dat", ios::out);
    ofile.open("/home/weixian/ClionProjects/huffmanAw3pp/files/hfmtree.dat", ios::out);

    int i;
    HuffmanNode<T> *parent, *left, *right;
    //创建临时使用的最小堆
    MinHeap<T> *heap = new MinHeap<T>();
    //建立数组a对应的最小堆
    heap->create(weights, datas, size);
    for (i = 0; i < size - 1; i++) {
        left = heap->dumpFromMinimum(); //从堆中取出最小节点,赋给左孩子
        right = heap->dumpFromMinimum(); //从堆中取出最小节点,赋给右孩子
        //新建parent节点,左右孩子分别是left和right,其大小是左右孩子之和
        parent = new HuffmanNode<T>(left->weight + right->weight, left, right, nullptr);
        left->parent = parent;
        right->parent = parent;

        //将parent节点数据拷贝到最小堆中
        if (heap->copyOf(parent) != 0) {
            cout << "插入失败!" << endl << "结束程序" << endl;
            destroy(parent);
            parent = nullptr;
            break;
        }
    }
    //将最小堆赋给mRoot
    mRoot = parent;

    //销毁最小堆
    heap->destroy();
    delete heap;
    setParent(mRoot);
}

/**
 * 保存Huffman树到文件中
 */
template<class T>
void Huffman<T>::saveToFile() {
    saveToFile(mRoot);
    ofile.close();
}

template<class T>
void Huffman<T>::saveToFile(HuffmanNode<T> *tree) {
    if (tree != nullptr) {
        ofile << tree->weight << " ";
        cout << "写入权值" << endl;
        if (tree->data != 0)
            ofile << tree->data << " ";
        else
            ofile << -2 << " ";
        cout << "写入字符集" << endl;
        saveToFile(tree->left);
        saveToFile(tree->right);
    }
}

/**
 * 销毁Huffman树
 */
template<class T>
void Huffman<T>::destroy(HuffmanNode<T> *tree) {
    if (tree == nullptr)
        return;
    if (tree->left != nullptr)
        destroy(tree->left);
    if (tree->right != nullptr)
        destroy(tree->right);
    delete tree;
    tree = nullptr;
}

template<class T>
void Huffman<T>::destroy() {
    destroy(mRoot);
}

/**
 * 打印"Huffman"树
 *
 * weight -- 节点的键值
 * direction -- 0:该节点为根节点
 *              -1:该节点为左孩子
 *              1:该节点为右孩子
 */
template<class T>
void Huffman<T>::print(HuffmanNode<T> *tree, int w, int direction) {
    if (tree != nullptr) {
        if (direction == 0) //tree是根节点
            cout << setw(2) << w << "is root " << "data:" << tree->data << endl;
        else  //tree是分支点
        {
            cout << setw(2) << tree->weight << " is " << setw(2) << w << "'s " << setw(2) <<
            (direction == 1 ? "right child" : "left child") << " data:" << tree->data << endl;
        }

        print(tree->left, tree->weight, -1);
        print(tree->right, tree->weight, 1);

    }
}

/**
 * 为每个节点设置父节点
 * （因为在构建Huffman树的构成过程中，每个节点的节点的父节点（除页节点）都被初始化为nullptr）
 */
template<class T>
void Huffman<T>::setParent(HuffmanNode<T> *tree) {
    cout << "setParent" << endl;
    if (tree != nullptr) {
        HuffmanNode<T> *child = tree->left;
        if (child == nullptr)
            child = tree->right;
        else return;
        if (child != nullptr) {
            child->parent = tree;
        }
//        child->parent = tree;
        setParent(tree->left);
        setParent(tree->right);
    }

}

template<class T>
void Huffman<T>::print() {
    if (mRoot != nullptr)
        print(mRoot, mRoot->weight, 0);
}


/**
 * 构造Huffman树对应的编码表
 */
template<class T>
void Huffman<T>::createHFMC(HuffmanNode<T> *tree) {
    //保证每个Huffman树节点对应的存储编码表堆栈都是最新的
    if (seq != nullptr) {
        delete seq;
        seq = nullptr;
    }
    seq = new SeqStack(); //编码表的指针
    HuffmanNode<T> *parent = tree->parent;
    hfmc(parent, tree); //利用递归构建编码表
    cout << 5 << endl;
    int i;
    for (i = 0; i <= seq->top; i++)
        tree->code[i] = seq->code[i];
    //打印下字符对应的编码
    cout << tree->data << ": ";
    for (i = 0; i <= seq->top; i++) {
        cout << tree->code[i];
    }
    cout << endl;
}

/**
 * 构建Huffman树编码库
 */
template<class T>
void Huffman<T>::hfmc(HuffmanNode<T> *parent, HuffmanNode<T> *child) {

    if (parent != nullptr) {
        cout << "hfmc" << endl;
        if (child == parent->left)
            push('0');
        else if (child == parent->right)
            push('1');
        hfmc(parent->parent, parent);
    }
}

/**
 * 保存编码表的指针及编码
 */
template<class T>
void Huffman<T>::push(char code) {
    seq->top++;
    seq->code[seq->top] = code;
    cout << "top: " << seq->top << endl;
}


//    }

//void Huffman<T>::createHFMC() {
//    HuffmanNode<T> *tree = mRoot; //从根节点开始
//    cout << 1 << endl;
//    while (tree != nullptr) {
//        cout << 2 << endl;
//        if (tree->data != 0) {
//            cout << 3 << endl;
//            //保证每个Huffman树节点对应的存储编码表堆栈都是最新的
//            if (seq != nullptr) {
//                delete seq;
//                seq = nullptr;
//                cout << 3 << endl;
//            }
//            cout << 4 << endl;
//            seq = new SeqStack(); //编码表的指针
//            HuffmanNode<T> *parent = tree->parent;
//            hfmc(parent, tree);
//            cout << 5 << endl;
//            int i;
//            for (i = 0; i <= seq->top; i++)
//                tree->code[i] = seq->code[i];
//            //打印下字符对应的编码
//            cout << tree->data << ": ";
//            for (i = 0; i <= seq->top; i++) {
//                cout << tree->code[i];
//            }
//            cout << endl;
//        }
//        //跳到下一个孩子节点
//        if (tree->left != 0)
//            tree = tree->left;
//        else if (tree->right != 0)
//        else if(tree->parent)
//            tree = tree->right;
////        else tree = nullptr;
//    }
//
//}


#endif //HUFFMANTEST_HUFFMAN_H
