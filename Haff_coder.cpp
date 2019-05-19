//
// Created by efg on 06.04.19.
//
#include "Haff_coder.h"


Haff_coder::Haff_coder(){
    in_str = "";
    root = nullptr;
}

Haff_coder::Haff_coder(std::string string){


    if (!string.length())
        throw std::invalid_argument("The string is empty");

    Tree_node node;
    in_str = string;
    out_str = "";
    root = nullptr;


    for (int i = 0; i < string.length(); i++){
        if (!Haff_find(&list, string[i])){
            node = Tree_node(string[i], 1);
            list.push_front(node);
        }
    }

    List_sort();
    Freq_table();
    if (freq_table.GetSize() == 1){
        table.Insert("1", string[0]);
        for (int i = 0; i < string.length(); i++)
            out_str += "1";
    }
    else{
        Tree_build();
        Encode_str();
    }
}

Haff_coder::~Haff_coder(){
    Delete_tree(root);
    root = nullptr;
}

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

void Haff_coder::Freq_table(){
    List<Tree_node>::Node* symbol = list.head;

    while (symbol){
        freq_table.Insert(symbol->data.freq, symbol->data.elem);
        symbol = symbol->next;
    }
}


void Haff_coder::Tree_build(){
    Tree_node *pmin1, *pmin2, *pnew_node;

    Tree_node min1, min2;

    List<Tree_node>::Node* symbol = list.head;

    while ((symbol) && (symbol->next))
    {
        min1 = symbol->data;
        min2 = symbol->next->data;

        pmin1 = new Tree_node;
        *pmin1 = min1;

        pmin2 = new Tree_node;
        *pmin2 = min2;

        list.pop_front();
        list.pop_front();

        pnew_node = new Tree_node(' ', min1.freq + min2.freq);
        pnew_node->empty = true;             //this node doesn't contain char symbol
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
    root = pnew_node;
}

void Haff_coder::List_sort(){
    List<Tree_node>::Node *node1, *node2, *next, *prev;

    for (int i = 0; i < list.size; i++){
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



void Haff_coder::Encode_str(){
    std::string string = "";
    DFS(root, &string);

    for (int i = 0; i < in_str.length(); i++){
        out_str += table.Find((size_t)in_str[i]);
    }
}

void Haff_coder::DFS(Tree_node *node, std::string *string){
    if (node->left){
        if (!node->left->empty){
            *string = *string + '0';
            table.Insert(*string, node->left->elem);
            *string = string->erase(string->length() - 1, string->length());
        }
        else{
            *string = *string + '0';
            DFS(node->left, string);
        }
    }
    if (node->right){
        if (!node->right->empty){
            *string = *string + '1';
            table.Insert(*string, node->right->elem);
            *string = string->erase(string->length() - 1, string->length());
        }
        else{
            *string = *string + '1';
            DFS(node->right, string);
        }
    }
    if (string->length())
        *string = string->erase(string->length() - 1, string->length());
}

void Haff_coder::TablePrint(){
    List<size_t> *symbs = table.GetKeys();
    List<std::string> *codes = table.GetValues();
    std::cout << '\n';
    for (int i = 0; i < table.GetSize(); i++){
        std::cout << '"' << (char)symbs->at(i)  << '"' << ' ';
        std::cout << codes->at(i);
        std::cout << std::endl;
    }
}


std::string Haff_coder::Decode(std::string string){
    if (!string.length())
        throw std::invalid_argument("Wrong input");
    Tree_node *node = root;
    std::string result = "";
    for (int i = 0; i < string.length(); i++){
        if (string[i] == '0'){
            if (!node->left)
                throw std::invalid_argument("Wrong input");
            else if (!node->left->empty){
                result += node->left->elem;
                node = root;
            }
            else
                node = node->left;
        }
        else if (string[i] == '1'){
            if (!node->right)
                throw std::invalid_argument("Wrong input");
            else if (!node->right->empty){
                result += node->right->elem;
                node = root;
            }
            else
                node = node->right;
        }
        else
            throw std::invalid_argument("Wrong input");
    }
    return result;
}

void Haff_coder::MemInfo(){

    float in, out;
    in = in_str.length()*8;
    out = out_str.length();
    std::cout << "Input string memory size: " << in << std::endl;
    std::cout << "Encoded string memory size: " << out << std::endl;
    std::cout << "Compression: " << in/out << std::endl;
}

void Haff_coder::FrequencyPrint(){
    List<size_t> *symbols = freq_table.GetKeys();
    List<size_t> *freq = freq_table.GetValues();
    List<size_t>::Node *node1, *node2;
    node1 = symbols->head;
    node2 = freq->head;
    while (node1){
        std::cout << '"' << (char)node1->data << '"' << ' ';
        std::cout << node2->data << std::endl;
        node1 = node1->next;
        node2 = node2->next;
    }
}

std::string Haff_coder::Encode(){
    return out_str;
}

void Haff_coder::Delete_tree(Tree_node *node){
    if (node){
        Delete_tree(node->right);
        Delete_tree(node->left);
    }
    delete node;
}

RB_Tree<std::string>* Haff_coder::GetTable(){
    RB_Tree<std::string> *table_copy = new RB_Tree<std::string>;
    *table_copy = table;
    return table_copy;
}

RB_Tree<size_t>* Haff_coder::GetFreqTable(){
    RB_Tree<size_t> *table_copy = new RB_Tree<size_t>;
    *table_copy = freq_table;
    return table_copy;
}