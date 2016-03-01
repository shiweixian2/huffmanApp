//
// Created by weixian on 16-2-29.
//

#ifndef HUFFMANAPP_SEQSTACK_H
#define HUFFMANAPP_SEQSTACK_H

#include "HuffmanNode.h"

/**
 * 用堆栈来保存编码字符的指针位置
 */
class SeqStack {
public:
    char code[MAX_LEN]; //
    int top;
};

#endif //HUFFMANAPP_SEQSTACK_H
