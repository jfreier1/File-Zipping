#include "huffmannode.h"
#include <iostream>

using namespace std;

HuffmanNode::HuffmanNode(pair<char,int> specs) {
    this->code = "";
    this->character = specs.first;
    this->weight = specs.second;
    this->leftChild = NULL;
    this->rightChild = NULL;
}

bool HuffmanNode::isRoot() {
    return (leftChild == NULL && rightChild == NULL);
}

bool HuffmanNode::operator <(HuffmanNode& other) {
    return weight < other.weight;
    cout<<weight<<" "<<other.weight<<endl;
}
