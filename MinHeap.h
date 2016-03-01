//
// Created by 石炜贤 on 16/2/27.
//
//最小堆相关操作的类
//

#ifndef HUFFMANTEST_MINHEAP_H
#define HUFFMANTEST_MINHEAP_H

#include "HuffmanNode.h"

template<class T>
class MinHeap {
private:
    HuffmanNode<T> *mHeap; //最小堆的数组
    int mCapacity; //总的容量
    int mSize; //当前有效数据的数量

    //上调算法
    void filterUp(int start);

    //下调算法
    void filterDown(int start, int end);

    //交换两个HuffmanNode节点的数据,i和j是节点索引
    void swapNode(int i, int j);

public:
    MinHeap();

    ~MinHeap();

    //將node的全部数据拷贝给"最小堆的指定节点"
    int copyOf(HuffmanNode<T> *node);

    //获取最小节点
    HuffmanNode<T> *dumpFromMinimum();

    //创建最小堆
    void create(int weights[],T datas[], int size);

    //销毁最小堆
    void destroy();
};

template<class T>
MinHeap<T>::MinHeap() { }

template<class T>
MinHeap<T>::~MinHeap() {
    destroy();
}

/**
 * 最小堆的向下调整算法
 *
 * 注意: 数组实现的堆中,节点是从第0个开始的,第N个节点的左孩子的索引为2N+1,右孩子节点索引为2N+2
 *
 * 参数说明:
 *      start -- 被下调节点的起始位置(下标一般为0,表示从第1个开始)
 *      end -- 截止范围(一般为数组最后一个元素的索引)
 */
template<class T>
void MinHeap<T>::filterDown(int start, int end) {
    int c = start; //当前(current)节点的位置
    int l = 2 * c + 1; //左(left)孩子的位置
    HuffmanNode<T> tmp = mHeap[c]; //当前(current)节点

    while (l <= end) {
        //l是左孩子,l+1是右孩子
        if (l < end && mHeap[l].weight > mHeap[l + 1].weight)
            l++; //左右孩子中选择较小的一个
        if (tmp.weight <= mHeap[l].weight)
            break;
        else {
            mHeap[c] = mHeap[l];
            c = l;
            l = 2 * l + 1;
        }
    }
    mHeap[c] = tmp;
}

/**
 * 最小堆的向上调整算法
 *
 * 注意: 数组实现的堆中,节点是从第0个开始的,第N个节点的左孩子的索引为2N+1,右孩子节点索引为2N+2
 *
 * 参数说明:
 *      start -- 被下调节点的起始位置(一般为数组最后一个元素的索引)
 */
template<class T>
void MinHeap<T>::filterUp(int start) {
    int c = start;
    int p = (c - 1) / 2;
    HuffmanNode<T> tmp = mHeap[c];

    while (c > 0) {
        if (mHeap[p].weight <= tmp.weight)
            break;
        else {
            mHeap[c] = mHeap[p];
            c = p;
            p = (p - 1) / 2;
        }
    }
    mHeap[c] = tmp;
}

/**
 * 将node的全部数据拷贝给"最小堆的指定节点"
 *
 * 返回值:
 *      0: 表示成功
 *      -1: 表示失败
 */
template<class T>
int MinHeap<T>::copyOf(HuffmanNode<T> *node) {

    //如果堆已满,返回
    if (mSize == mCapacity)
        return -1;

    mHeap[mSize] = *node; //将node的数据全部拷贝到数组结尾,mHeap[mSize]原本数据为空
    filterUp(mSize); //向上调整堆
    mSize++; //堆的实际容量+1
    return 0; //拷贝成功
}

/**
 * 交换两个HuffmanNode节点的全部数据
 */
template<class T>
void MinHeap<T>::swapNode(int i, int j) {

    HuffmanNode<T> tmp = mHeap[i];
    mHeap[i] = mHeap[j];
    mHeap[j] = tmp;
}

template<class T>
HuffmanNode<T> *MinHeap<T>::dumpFromMinimum() {

    //如果堆已空,则返回
    if (mSize == 0)
        return nullptr;

    HuffmanNode<T> *node;
    if ((node = new HuffmanNode<T>()) == nullptr)
        return nullptr;
    //将最小节点的全部数据拷贝给node
    *node = mHeap[0];

    swapNode(0, mSize - 1); //交换最小节点和最后一个节点
    filterDown(0, mSize - 2); //将[0..mSize-2]构成一个最小堆
    mSize--;

    return node;

}

/**
 * 创建最小堆
 *
 * 参数说明:
 *      weight -- 权值所在的数组
 *      datas -- 节点代表的字符所在的数组
 *      size -- 数组大小
 */
template<class T>
void MinHeap<T>::create(int *weights, T *datas, int size) {
    int i;
    //创建最小堆所对应的数组
    mSize = size;
    mCapacity = size;
    mHeap = new HuffmanNode<T>[size];

    //初始化数组
    for (int i = 0; i < size; ++i) {
        mHeap[i].weight = weights[i];
        mHeap[i].data = datas[i];
        mHeap[i].parent = mHeap[i].left = mHeap[i].right = nullptr; //赋初值为空
    }

    for (i = size / 2 - 1; i >= 0; i--) {
        filterDown(0, size);
    }

}

/**
 * 销毁最小堆
 */
template <class T>
void MinHeap<T>::destroy() {
    mSize = 0;
    mCapacity = 0;
    delete []mHeap;
    mHeap = nullptr;
}


#endif //HUFFMANTEST_MINHEAP_H
