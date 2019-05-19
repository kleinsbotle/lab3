//
// Created by efg on 30.03.19.
//

#ifndef LAB3_HAFF_CODER_H
#define LAB3_HAFF_CODER_H

#include <string>
#include <stdexcept>

#include "List.h"
#include "Map.h"

#pragma once


class Haff_coder{

public:

    Haff_coder();
    Haff_coder(std::string str);
    ~Haff_coder();
    void TablePrint();
    std::string Encode();
    std::string Decode(std::string string);
    void MemInfo();
    void FrequencyPrint();
    RB_Tree<std::string> *GetTable();
    RB_Tree<size_t> *GetFreqTable();

private:
    std::string in_str;
    std::string out_str;

    class Tree_node{       //Haffman tree node
    public:
        char elem;
        size_t freq;
        bool empty;        //if tne node contains char symbol or not
        Tree_node *left, *right, *dad;

        Tree_node(char elem, size_t freq)
        {
            this->elem = elem;
            this->freq = freq;
            empty = false;
            left = nullptr;
            right = nullptr;
            dad = nullptr;
        }

        bool operator == (const Tree_node &node){
            if (this->elem != node.elem)
                return false;
            if (this->freq != node.freq)
                return false;
            if (this->left != node.left)
                return false;
            if (this->right != node.right)
                return false;
            if (this->dad != node.dad)
                return false;
            if (this->empty != node.empty)
                return false;
            return true;
        }

        Tree_node(){
        }

        ~Tree_node(){ left = nullptr; right = nullptr; dad = nullptr;}

    };

    Tree_node *root;

    List<Tree_node> list;
    RB_Tree<std::string> table;
    RB_Tree<size_t> freq_table;

    bool Haff_find(List<Tree_node> *list, char elem);

    void Freq_table();
    void Encode_str();
    void Tree_build();
    void List_sort();
    void DFS(Tree_node *node, std::string *string);
    void Delete_tree(Tree_node *node);
};




//комментарии
//нормальная сортировка
#endif //LAB3_HAFF_CODER_H
