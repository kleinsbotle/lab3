//
// Created by efg on 30.03.19.
//

#ifndef LAB3_HAFF_CODER_H
#define LAB3_HAFF_CODER_H

#include <string>

#include "List.h"
#include "Map.h"


#define maxrow 7
#define matrix_size 80
#define offset 40



class Haff_coder{

public:

    Haff_coder(std::string str);
    void Coder_print();
    void Encode();
    void OutTree();
    void TablePrint();

private:

    std::string str;
    class Tree_node{   //Haffman tree node

    public:

        char elem;
        size_t freq;
        bool visited;
        bool empty;
        Tree_node *left, *right, *dad;

        Tree_node(char elem, size_t freq)
        {
            this->elem = elem;
            this->freq = freq;
            visited = false;
            empty = false;
            left = nullptr;
            right = nullptr;
            dad = nullptr;
        }

        Tree_node(const Tree_node& node){
            elem = node.elem;
            freq = node.freq;
            visited = node.visited;
            empty = node.empty;
            left = node.left;
            right = node.right;
            dad = node.dad;

        }

        Tree_node& operator = (const Tree_node &node){
            elem = node.elem;
            freq = node.freq;
            visited = node.visited;
            empty = node.empty;
            left = node.left;
            right = node.right;
            dad = node.dad;
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
            if (this->visited != node.visited)
                return false;
            if (this->empty != node.empty)
                return false;
            return true;
        }

        Tree_node(){
        }

    };

    Tree_node *root;
    size_t size;

    List<Tree_node> list;
    RB_Tree<char> table;

    char** SCREEN;                                //matrix to print the tree
    void __clrcsr();                             //fill the matrix with 0
    void __out_nodes(Tree_node* v, int r, int c);     //add keys to the matrix

    bool Haff_find(List<Tree_node> *list, char elem);

    void Tree_build();
    void List_sort();
    void DFS(Tree_node *node, List<int> *code, short *num);
    void Code_convert(size_t num);


};

Haff_coder::Haff_coder(std::string string){

    Tree_node node;
    str = string;
    size = 0;
    SCREEN = new char*[maxrow];
    for (int i = 0; i < maxrow; i++){
        SCREEN[i] = new char[matrix_size];
    }

    for (int i = 0; i < string.length(); i++){
        if (!Haff_find(&list, string[i])){
            node = Tree_node(string[i], 1);
            list.push_front(node);
            size++;
        }
    }

    List_sort();
    Coder_print();
    Tree_build();
}
/*
void Haff_coder::__clrcsr(){
    for (int i = 0; i < maxrow; ++i){
        for (int j = 0; j < matrix_size; j++){
            SCREEN[i][j] = '-';
        }
    }
}

void Haff_coder::__out_nodes(Tree_node* v, int str, int m_size){
    if (str && m_size && (m_size < matrix_size))
        SCREEN[str - 1][m_size - 1] = v->elem;
    if (str < maxrow){
        if (v->left)
            __out_nodes(v->left, str + 1, m_size - (offset >> str));
        if (v->right)
            __out_nodes(v->right, str + 1, m_size + (offset >> str));
    }
}

void Haff_coder::OutTree(){
    __clrcsr();
    if (!size){
        std::cout << "\nThe list is empty\n";
        return;
    }
    __out_nodes(root, 1, offset);

    for (int i = 0; i < maxrow; ++i){
        std::cout << '\n';
        for (int j = 0; j < matrix_size; j++){
            std::cout << SCREEN[i][j];
        }
    }
    std::cout << '\n';
}
*/
bool Haff_coder::Haff_find(List<Tree_node> *list, char elem){
    List<Tree_node>::Node* symbol = list->head;

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
    List<Tree_node>::Node* symbol = list.head;

    std::cout << "\n";
    while (symbol){
        std::cout << symbol->data.elem << " ";
        std::cout << symbol->data.freq << "; ";
        symbol = symbol->next;
    }
    std::cout << std::endl;
}


void Haff_coder::Tree_build(){
    Tree_node *pmin1, *pmin2, *pnew_node;

    Tree_node min1, min2, new_node;

    List<Tree_node>::Node* symbol = list.head;

    while ((symbol) && (symbol->next))
    {
        min1 = symbol->data;
        min2 = symbol->next->data;

        pmin1 = new Tree_node;
        pmin1->elem = min1.elem;
        pmin1->freq = min1.freq;
        pmin1->left = min1.left;
        pmin1->right = min1.right;
        pmin1->dad = min1.dad;

        pmin2 = new Tree_node;
        pmin2->elem = min2.elem;
        pmin2->freq = min2.freq;
        pmin2->left = min2.left;
        pmin2->right = min2.right;
        pmin2->dad = min2.dad;

        list.pop_front();
        list.pop_front();

        pnew_node = new Tree_node('%', min1.freq + min2.freq); //AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
        pnew_node->left = pmin1;
        pnew_node->right = pmin2;
        pmin1->dad = pnew_node;
        pmin2->dad = pnew_node;

        size_t index = 0;                //add new node into the list
        symbol = list.head;

        while (symbol && (symbol->data.freq < pnew_node->freq)){  //searching for a place in list to insert the new node
            symbol = symbol->next;
            index++;
        }
        list.insert(index, *pnew_node);
        symbol = list.head;
    }
    root = pnew_node;  //FIX!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

}

void Haff_coder::List_sort(){
    List<Tree_node>::Node *node1, *node2, *next, *prev;

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
    List<int> *code = new List<int>;
    short num = 1;
    short *ptr = &num;
    DFS(root, code, ptr);
    TablePrint();
}

void Haff_coder::DFS(Tree_node *node, List<int> *code, short *num)
{
    node->visited = true;
    size_t number;
   if ((node->left) && (!node->left->visited))
   {
       if (node->left->elem != '%') {
           code->push_back(0);
           *num = *num * 2;
           std::cout << code << ' ';
           std::cout << '"' << node->left->elem << '"' << std::endl;
           number = *num;
           table.Insert(node->left->elem, number);
           if (code->get_size()){
               code->pop_back();
               *num = *num / 2;
           }
       }
       else
       {
           code->push_back(0);
           *num = *num * 2;
           DFS(node->left, code, num);
       }
   }
   if ((node->right) && (!node->right->visited))
   {
       if (node->right->elem != '%')
       {
            code->push_back(1);
            *num = *num * 2;
            *num = *num + 1;
            std::cout << code << ' ';
            std::cout << '"' << node->right->elem << '"' << std::endl;
            number = *num;
            table.Insert(node->right->elem, number);
            if (code->get_size())
            {
                code->pop_back();
                *num = *num - 1;
                *num = *num/2;
            }
       }
       else{
            code->push_back(1);
            *num = *num * 2;
            *num = *num + 1;
           DFS(node->right, code, num);
       }
   }
   if (code->get_size())
   {
       code->pop_back();
       *num = *num / 2;
   }

}

void Haff_coder::TablePrint()
{
    List<size_t> *keys = table.GetKeys();
    List<char> *values = table.GetValues();
    std::cout << '\n';
    for (int i = 0; i < table.GetSize(); i++)
    {
        std::cout << '"' << values->at(i)  << '"' << ' ';
        Code_convert(keys->at(i));
        std::cout << std::endl;
    }
}

void Haff_coder::Code_convert(size_t num)
{
    while (num != 1)
    {
        std::cout << num % 2 << ' ';
        num = num / 2;
    }
}


//flag
//мб visited не нужно
//указатели в build
//нормальная сортировка

#endif //LAB3_HAFF_CODER_H
