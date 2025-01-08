#pragma once
#ifndef AVL_TRE_H
#define AVL_TREE_H
#include"Node.h"

class AVL
 {
public:
    Node* root;

    AVL()
    {
        root = nullptr;
    }

    void modify_node_txt_file(Node* node)                   // MODIFIATION IN TEXT FILE ACCORDING TO ROTATIONS
    {
        if (node == nullptr)
        {
            return;                                       // MODIFIES ONLY PARENT CHILD RELATION SHIP AFTER ROTATION, 
                                                         // NOT THE ACTUAL DATA OF THE RESPECTED ROW OF EACH NODE
        }
        ofstream file(node->file_name);
        if (file.is_open())
        {
            if (node)
            {
                file << "NODE_DATA--->    " << node->data << "\n";
            }
            else
            {
                file << "NODE_DATA--->    nullptr\n";
            }

            file << "ROW_DATA--->    " << node->row_data << "\n"; 

            if (node->parent)
            {
                file << "PARENT_NODE--->    " << node->parent->data << "\n";
            }
            else
            {
                file << "PARENT_NODE--->    nullptr\n";
            }

            if (node->left_child)
            {
                file << "LEFT_CHILD--->    " << node->left_child->data << "\n";
            }
            else
            {
                file << "LEFT_CHILD--->    nullptr\n";
            }

            if (node->right_child)
            {
                file << "RIGHT_CHILD--->    " << node->right_child->data << "\n";
            }
            else
            {
                file << "RIGHT_CHILD--->    nullptr\n";
            }
            file.close();

        }
    }

    int get_height(Node* node)// FUNCTION TO RETURN THE HEIGHT AFTER UPDATING WHEN ROTATION PERFORMS
                             //  NEEDED BECAUSE AFTER ROTATION, HEIGHT ALSO AFFECTS, ALSO TO RETURN 
                            //   THE MAX HEIGHT TO PERFORM CORRECT ROTATION
    {
        if (node == nullptr)
        {
            return 0;
        }
        return max(get_height(node->left_child), get_height(node->right_child)) + 1;
    }

    int get_balance_function(Node* node) //RETURNS THE BALANCE FACTOR TO MAKE THE AVL TREE STABLE
    {
        if (node == nullptr)
        {
            return 0;
        }
        return get_height(node->left_child) - get_height(node->right_child);
    }

    Node* left_rotation_function(Node* x)// LEFT ROTATION FUNCTION AND ALSO UPDATES THE
                                        //  CHILD-PARENT RELATION IN THE TEXT FILES
    {
        if (x->right_child == nullptr)
        {
            return x; 
        }
        Node* y = x->right_child;
        x->right_child = y->left_child;
        if (y->left_child != nullptr)
        {
            y->left_child->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr)
        {
            root = y;
        }
        else if (x == x->parent->left_child)
        {
            x->parent->left_child = y;
        }
        else
        {
            x->parent->right_child = y;
        }
        y->left_child = x;
        x->parent = y;
        return y;
    }

    Node* right_rotation_function(Node* x)// RIGHT ROTATION FUNCTION AND ALSO UPDATES THE
                                         //  CHILD-PARENT RELATION IN THE TEXT FILES
    {
        if (x->left_child == nullptr) 
        {
            return nullptr;
        }
       Node* y = x->left_child;
        x->left_child = y->right_child;
        if (y->right_child != nullptr)  
        {
            y->right_child->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) 
        {
            root = y;
        }
        else if (x == x->parent->right_child) 
        {
            x->parent->right_child = y;
        }
        else 
        {
            x->parent->left_child = y;
        }
        y->right_child = x;
        x->parent = y;
        return y;
    }

    void print_tree(Node* node)
    {
        if (!node)
        {
            return;
        }
        modify_node_txt_file(node);
        cout << "\n\nNODE_DATA--->      " << node->data  << "\n";
        cout << "                       ROW_DATA   --->    " << node->row_data << "\n";
        cout << "                       PARENT_NODE--->    " << (node->parent ? node->parent->data : "nullptr")  << "\n";
        cout << "                       LEFT_CHILD --->    " << (node->left_child ? node->left_child->data : "nullptr") << "\n";
        cout << "                       RIGHT_CHILD--->    " << (node->right_child ? node->right_child->data : "nullptr") << "\n";
        print_tree(node->left_child);
        print_tree(node->right_child);
    }

    void help_print()
    {
		print_tree(root);
    }
    Node* insert(Node* node, const char* data, const char* row,const char* folder_name)
    {
                                                                  // INSERTION, HERE WE PASS NODE(AS A ROOT INITIALLY),
                                                                 //  VAL AS A DATA, ROW IS DATA OF ROW FOR EACH RESPECTED 
                                                                //   NODE,PARENT IS DUE TO TRACK THE PARENT FOR EACH NODE
                                                               //   ,FOLDER_NAME IS THE ACTUALY BRANCH NAME WHERE TO UPDATE 
                                                              //     OR INSERT
        if (node == nullptr) 
        {
            Node* new_node = new Node(data, row, folder_name);
            return new_node;
        }
        if (strcmp(data, node->data) < 0) 
        {
            node->left_child = insert(node->left_child, data, row,folder_name);
            node->left_child->parent = node;
        }
        else 
        {
            node->right_child = insert(node->right_child, data, row,folder_name);
            node->right_child->parent = node;
        }
        int balance = get_balance_function(node);
        if (balance > 1 && strcmp(data, node->left_child->data) < 0) 
        {
            return right_rotation_function(node);
        }
        if (balance < -1 && strcmp(data, node->right_child->data) > 0) 
        {
            return left_rotation_function(node);
        }
        if (balance > 1 && strcmp(data, node->left_child->data) > 0)
        {
            node->left_child = left_rotation_function(node->left_child);
            return right_rotation_function(node);
        }
        if (balance < -1 && strcmp(data, node->right_child->data) < 0)
        {
            node->right_child = right_rotation_function(node->right_child);
            return left_rotation_function(node);
        }
        return node;
    }

    void insert_in_AVL(char* val, char* row, const char* foler_name)        // HELPER FUNCTION CALLER FOR 
                                                                           //  THE SAKE OF INSERTION
    {       
      root = insert(root, val, row, foler_name);
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

    Node* delete_node(Node* node, const char* data)
    {// THIS FUNCTION DELETES THE NODE ONLY AND UPDATE ONLY IN THE AVL TREE AND IN THE TEXT FILE.
        if (node == nullptr)
        {
            return node;
        }
        if (strcmp(data, node->data) < 0) 
        {
            node->left_child = delete_node(node->left_child, data);
        }
        else if (strcmp(data, node->data) > 0)
        {
            node->right_child = delete_node(node->right_child, data);
        }
        else 
        {
            if ((node->left_child == nullptr) || (node->right_child == nullptr)) 
            {
                Node* temp=nullptr;
                if (node->left_child)
                {
                     temp = node->left_child;
                }
                else
                {
                     temp = node->right_child;
                }
                if (temp == nullptr) 
                { 
                    temp = node;
                    node = nullptr;
                }
                else 
                { 
                    *node = *temp;
                }
                delete temp;
            }
            else 
            {
                Node* temp = get_sucessor(node->right_child);
                str_cpy(node->data, temp->data);
                str_cpy(node->row_data, temp->row_data);
                node->right_child = delete_node(node->right_child, temp->data);
            }
        }
        if (node == nullptr)
        {
            return node;
        }
        int balance = get_balance_function(node);
        if (balance > 1 && get_balance_function(node->left_child) >= 0) 
        {
            return right_rotation_function(node);
        }
        if (balance > 1 && get_balance_function(node->left_child) < 0)
        {
            node->left_child = left_rotation_function(node->left_child);
            return right_rotation_function(node);
        }
        if (balance < -1 && get_balance_function(node->right_child) <= 0)
        {
            return left_rotation_function(node);
        }
        if (balance < -1 && get_balance_function(node->right_child) > 0) 
        {
            node->right_child = right_rotation_function(node->right_child);
            return left_rotation_function(node);
        }
        return node;
    }

    void delete_node_helper_function(const char* data)
    {
        root = delete_node(root, data);
    }

    Node* get_sucessor(Node* node) // RETURNS THE INORDER SUCESSOR TO DELETE THE NODE IN THE AVL TREE
    {
        Node* current = node;
        while (current && current->left_child)
        {
            current = current->left_child;
        }
        return current;
    }
};
#endif