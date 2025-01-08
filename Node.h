#pragma once
#ifndef NODE_H
#define NODE_H
#include<iostream>
#include"File_Reader.h"
using namespace std;

enum color_of_nodes { R, B };
class Node
{
public:
    char* data;
    Node* left_child;
    Node* right_child;
    int height;
    Node* parent;
    color_of_nodes c1;
    char file_name[100];
    char row_data[1000];
    Node(const char* val, const char* row, const char* folder_name)
    {
        data = new char[str_len(val) + 1];
        str_cpy(data, val);
        parent=left_child = right_child = nullptr;
        c1 = R; 
        height = 1;                 // INITIALIZING HEIGHT WITH 1 TO MAKE THE TREE BALANCE ALSO TO CHECK BALANCE FACTOR
        str_cpy(row_data, row);    //  TO SEPRATE DATA FOR EACH NODE, SO IT'LL MAKE DATA OR EACH RESPECTED ROW SEPRATE AND SAVE
        create_node_text_file(folder_name, data, row, nullptr, nullptr, nullptr);
    }

    ~Node()
    {
        delete[] data;
        if (file_name)
        {
            remove(file_name);
        }
    }

    bool file_exists(const char* filename)      // TO MAKE SURE NOT TO RECREATE THE FILE, IF IT ALREADY EXISTS
    {
        ifstream f1(filename);
        return f1.good(); 
    }

    void create_node_text_file(const char* folder_name, const char* values, const char* row, const Node* left_ptr, const Node* right_ptr, const Node* parent_ptr)
    {       // THIS FUNCTION CREATES THE TXT'S FOR EACH NODE SEPRATELY, SO IT'LL MAKE SURE NOT TO LOAD WHOLE TREE IN RAM
           //  , WHICH NODE WE WANT, WE'LL GET THAT PARTICULAR NODE DATA AFTER READING AND OPENING IT.
        int i = 0;
        while (folder_name[i] != '\0' && i < sizeof(file_name) - 1)
        {
            file_name[i] = folder_name[i];
            i++;
        }
        file_name[i++] = '\\';
        int j = 0;
        while (values[j] != '\0')
        {
            file_name[i++] = values[j++];
        }
        file_name[i++] = '.';       // TO MAKE SURE, THE FILE WILL BE TXT FILE
        file_name[i++] = 't';
        file_name[i++] = 'x';
        file_name[i++] = 't';
        file_name[i] = '\0';
        if (file_exists(file_name) == true)
        {
            return;
        }
        ofstream file(file_name);
        if (file.is_open())
        {
            file << row << "\n";
            file.close();
        }
    }

    void str_cpy(char* dest, const char* src)       // TO COPY THE STRING USING POINTERS
    {
        int i = 0;
        while (src[i] != '\0')
        {
            dest[i] = src[i];
            i++;
        }
        dest[i] = '\0';
    }

    int str_len(const char* str) // RETURN THE LENGTH OF THE CHARACTER ARRAY 
    {
        int length = 0;
        while (str[length] != '\0')
        {
            length++;
        }
        return length;
    }
};
#endif