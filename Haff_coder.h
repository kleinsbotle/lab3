//
// Created by efg on 30.03.19.
//

#ifndef LAB3_HAFF_CODER_H
#define LAB3_HAFF_CODER_H

#include <string>

#include "List.h"
#include "Map.h"





class Haff_coder{

public:

    Haff_coder(std::string str);
    void Coder_print();
    void Encode();
    void Test();

private:

    std::string str;
    struct symb{    //information about every character in input string
        char elem;
        size_t freq;
    };

    class Tree_node{   //Haffman tree node

    public:

        char elem;
        size_t freq;
        bool color;
        Tree_node *left, *right, *dad;

        Tree_node(char elem, size_t freq)
        {
            this->elem = elem;
            this->freq = freq;
            color = true;
            left = nullptr;
            right = nullptr;
            dad = nullptr;
        }
        /*
        Tree_node(const Tree_node& node){
            elem = node.elem;
            freq = node.freq;
            left = node.left;
            right = node.right;
            dad = node.dad;

        }

        Tree_node& operator = (const Tree_node &node){
            elem = node.elem;
            freq = node.freq;
            left = node.left;
            right = node.right;
            dad = node.dad;
        }

        Tree_node(){
            right = nullptr;
            left = nullptr;
            dad = nullptr;
        }*/

    };

    Tree_node *root;
    size_t size;

    List<struct symb> list;
    RB_Tree<char> table;

    bool Haff_find(List<struct symb> *list, char elem);

    void Tree_build();
    void List_sort();
    void DFS(Tree_node *node);


};

Haff_coder::Haff_coder(std::string string){

    struct symb symbol;
    str = string;
    size = 0;

    for (int i = 0; i < string.length(); i++){
        if (!Haff_find(&list, string[i])){
            symbol.elem = string[i];
            symbol.freq = 1;
            list.push_front(symbol);
            size++;
        }
    }

    List_sort();
    Coder_print();
    Tree_build();
}

bool Haff_coder::Haff_find(List<struct symb> *list, char elem){
    List<struct symb>::Node* symbol = list->head;

    while (symbol){
        if (symbol->data.elem == elem){
            symbol->data.freq++;
            return true;
        }
        symbol = symbol->next;
    }
    return false;
}

void Haff_coder::Coder_print(){
    List<struct symb>::Node* symbol = list.head;

    std::cout << "\n";
    while (symbol){
        std::cout << symbol->data.elem << " ";
        std::cout << symbol->data.freq << "; ";
        symbol = symbol->next;
    }
    std::cout << std::endl;
}

void Haff_coder::Tree_build(){
    Tree_node *min1, *min2, *new_node;

    List<struct symb>::Node* symbol = list.head;
    struct symb new_elem;

    while ((symbol) && (symbol->next))
    {
        min1 = new Tree_node(symbol->data.elem, symbol->data.freq);  //find 2 minimal elements in the list
        symbol = symbol->next;
        min2 = new Tree_node(symbol->data.elem, symbol->data.freq);

        list.pop_front();
        list.pop_front();

        new_node = new Tree_node('%', min1->freq + min2->freq); //AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
        new_node->left = min1;
        new_node->right = min2;
        min1->dad = new_node;
        min2->dad = new_node;

        size_t index = 0;                //add new node into the list
        symbol = list.head;
        new_elem.elem = new_node->elem; //REMOVE!!!!!!!!!!!!!!
        new_elem.freq = new_node->freq;

        while (symbol && (symbol->data.freq < new_elem.freq)){  //searching for a place in list to insert the new node
            symbol = symbol->next;
            index++;
        }
        list.insert(index, new_elem);
        symbol = list.head;
    }
    root = new_node;  //FIX!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

void Haff_coder::List_sort(){
    List<struct symb>::Node *node1, *node2, *next, *prev;

    for (int i = 0; i < list.size - 2; i++){
        node1 = list.head;
        for (int j = 0; j < list.size - 1; j++){
            node2 = node1->next;
            if (node1->data.freq > node2->data.freq){
                if (node1 == list.head)
                {
                    next = node2->next;
                    node2->prev = nullptr;
                    node2->next = node1;
                    list.head = node2;
                    node1->prev = list.head;
                    node1->next = next;
                    next->prev = node1;
                }

                else if (node2 == list.tail)
                {
                    prev = node1->prev;
                    list.tail = node1;
                    node1->next = nullptr;
                    node1->prev = node2;
                    node2->next = node1;
                    node2->prev = prev;
                    prev->next = node2;
                }

                else
                {
                    prev = node1->prev;
                    next = node2->next;
                    prev->next = node2;
                    next->prev = node1;
                    node2->next = node1;
                    node1->prev = node2;
                    node2->prev = prev;
                    node1->next = next;
                }
            }
            else
                node1 = node1->next;
        }
    }
}



void Haff_coder::Encode()
{
    DFS(root);
}

void Haff_coder::DFS(Tree_node *node)
{
   /* Tree_node data = *node;
    visited->push_back(data);
    if (node->left)
    {
        if (node->left->elem != '%')
            std::cout << node->left->elem << std::endl;
        else
            std::cout << 0;
        DFS(node->left, visited);
    }
    if (node->right)
    {
        if (node->right->elem != '%')
            std::cout << node->right->elem << std::endl;
        else
            std::cout << 1;
        DFS(node->right, visited);

    }*/


   node->color = false;
   if ((node->left) && (node->left->color))
   {
       if (node->left->elem != '%')
           std::cout << node->left->elem << std::endl;
       else
           std::cout << 0;
       DFS(node->left);
   }
    if ((node->right) && (node->right->color))
    {
        if (node->right->elem != '%')
            std::cout << node->right->elem << std::endl;
        else
            std::cout << 1;
        DFS(node->right);
    }


}

void Haff_coder::Test()
{
    Tree_node *node = root;
    while (node){
        std::cout << 0;
        node = node->right;
    }
    std::cout << std::endl;
    node = root;
    while (node){
        std::cout << 0;
        node = node->left;
    }
}

//flag
//нормальная сортировка

#endif //LAB3_HAFF_CODER_H
