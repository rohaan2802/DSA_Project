#pragma once
#ifndef Red_Black_H
#define Red_Black_H
#include"Node.h"

class red_black_tree
{
public:
    Node* root;
    const char* folder_name;
    red_black_tree(const char* file_name)
    {
        root = nullptr;
        folder_name = file_name;
    }

    void modify_node_txt_file(Node* node) // MODIFIATION IN TEXT FILE ACCORDING TO ROTATIONS
    {
        if (node == nullptr) 
        {                                                  // MODIFIES ONLY PARENT CHILD RELATION SHIP AFTER ROTATION, 
                                                          // NOT THE ACTUAL DATA OF THE RESPECTED ROW OF EACH NODE
            return; 
        }
        ofstream file(node->file_name);
        if (file.is_open()) 
        {
            if (node)
            {
                file << "NODE_DATA " << node->data<<"   "<< (node->c1 == R ? "R" : "B") << "\n";             
            }
            else
            {
                file << "NODE_DATA nullptr   B\n";
            }
            file << "ROW_DATA " << node->row_data << "\n"; 
            if (node->parent)
            {
                file << "PARENT_NODE " << node->parent->data<<"   " << (node->parent->c1 == R ? "R" : "B") << "\n";
            }
            else 
            {
                file << "PARENT_NODE nullptr   B\n";
            }
            if (node->left_child) 
            {
                file << "LEFT_CHILD " << node->left_child->data << "   " << (node->left_child->c1 == R ? "R" : "B")<<"\n";
            }
            else 
            {
                file << "LEFT_CHILD nullptr    B\n";
            }
            if (node->right_child) 
            {
                file << "RIGHT_CHILD " << node->right_child->data<<"   " << (node->right_child->c1 == R ? "R" : "B") << "\n";
            }
            else
            {
                file << "RIGHT_CHILD nullptr    B\n";
            }
            file.close();
        }
    }

    void left_rotation_function(Node* x)
    {                                                       // LEFT ROTATION FUNCTION AND ALSO UPDATES THE
                                                           //  CHILD-PARENT RELATION IN THE TEXT FILES
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
    }

    void right_rotation_function(Node* x)   // RIGHT ROTATION FUNCTION AND ALSO UPDATES THE
                                           //  CHILD-PARENT RELATION IN THE TEXT FILES
    {
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
    }

    void case_handle_insertion(Node* z) //THIS FUNCTION TRIES TO FIX THE INSERTION WHILE THERE ARE 2 CASES
                                       // IF PARENT'S SIBLING(UNCLE OF THE NODE) IS RED AND SECOND ONE IF 
                                      //  IF THE PARENT'S SIBLING(UNCLE OF THE NODE) IS BLACK
    {
        while (z->parent != nullptr && z->parent->c1 == R)
        {
            Node* gp = z->parent->parent;
            if (z->parent == gp->left_child)
            {
                Node* parent_sibling = gp->right_child;
                if (parent_sibling != nullptr && parent_sibling->c1 == R)
                { 
                    z->parent->c1 = B;
                    parent_sibling->c1 = B;
                    gp->c1 = R;
                    z = gp;
                }
                else 
                { 
                    if (z == z->parent->right_child) 
                    { 
                        z = z->parent;
                        left_rotation_function(z);
                    }
                    z->parent->c1 = B; 
                    gp->c1 = R;
                    right_rotation_function(gp);
                }
            }
            else 
            {
                Node* parent_sibling = gp->left_child;
                if (parent_sibling != nullptr && parent_sibling->c1 == R) 
                { 
                    z->parent->c1 = B;
                    parent_sibling->c1 = B;
                    gp->c1 = R;
                    z = gp;
                }
                else 
                { 
                    if (z == z->parent->left_child) 
                    { 
                        z = z->parent;
                        right_rotation_function(z);
                    }
                    z->parent->c1 = B; 
                    gp->c1 = R;
                    left_rotation_function(gp);
                }
            }
        }
        root->c1 = B;
    }  

    int cmp_str(const char* str1, const char* str2)// TO CHECK THE CHARACTER'S ASCII VALUE TO MAKE INSERTION IN AVL
    {
        int i = 0;
        while (str1[i] != '\0' && str2[i] != '\0')
        {
            if (str1[i] < str2[i])
            {
                return -1;
            }
            if (str1[i] > str2[i])
            {
                return 1;
            }
            i++;
        }
        if (str1[i] == '\0' && str2[i] == '\0')
        {
            return 0;
        }
        return (str1[i] == '\0') ? -1 : 1;
    }

    void insert(const char* data, const char* row)
                                                                // INSERTION , HERE WE PASS NODE(AS A ROOT INITIALLY),
                                                               //  VAL AS A DATA, ROW IS DATA OF ROW FOR EACH RESPECTED 
                                                              //   NODE,PARENT IS DUE TO TRACK THE PARENT FOR EACH NODE
                                                             //   ,FOLDER_NAME IS THE ACTUALY BRANCH NAME WHERE TO UPDATE 
                                                            //     OR INSERT
    {
        Node* new_node = new Node(data, row, folder_name);
        if (root == nullptr)
        {
            root = new_node;
            root->c1 = B;
            return;
        }
        Node* parent = nullptr;
        Node* current = root;
        while (current != nullptr) 
        {
            parent = current;
            if (strcmp(data, current->data) < 0)
            {
                current = current->left_child;
            }
            else
            {
                current = current->right_child;
            }
        }
        new_node->parent = parent;
        if (strcmp(data, parent->data) < 0) 
        {
            parent->left_child = new_node;
        }
        else
        {
            parent->right_child = new_node;
        }
        case_handle_insertion(new_node);
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

    Node* get_sucessor(Node* node) // RETURNS THE INORDER SUCESSOR TO DELETE THE NODE IN THE AVL TREE
    {
        Node* current = node;
        while (current->left_child != nullptr)
        {
            current = current->left_child;
        }
        return current;
    }

    void delete_node_in_RB(Node*& root, const char* data)
    {// THIS FUNCTION DELETES THE NODE ONLY AND UPDATE ONLY IN THE AVL TREE AND IN THE TEXT FILE.
        if (root == nullptr)
        {
            return; 
        }
        if (strcmp(data, root->data) < 0)
        {
            delete_node_in_RB(root->left_child, data);
        }
        else if (strcmp(data, root->data) > 0) 
        {
            delete_node_in_RB(root->right_child, data);
        }
        else
        {
            if (root->left_child == nullptr || root->right_child == nullptr)
            {
                Node* temp = root->left_child ? root->left_child : root->right_child;
                if (temp == nullptr) 
                {
                    temp = root;
                    root = nullptr;
                }
                else 
                { 
                    *root = *temp; 
                }

                delete temp;
            }
            else 
            {
                Node* temp = get_sucessor(root->right_child);
                str_cpy(root->data, temp->data);
                delete_node_in_RB(root->right_child, temp->data); 
            }
        }
        if (root == nullptr)
        {
            return;
        }
        root->height = 1 + max(get_height(root->left_child), get_height(root->right_child));
        int balance = get_balance(root);
        if (balance > 1 && get_balance(root->left_child) >= 0) 
        {
            helper_fun_right(root);
        }
        if (balance > 1 && get_balance(root->left_child) < 0)
        {
            helper_fun_left(root->left_child);
            helper_fun_right(root);
        }
        if (balance < -1 && get_balance(root->right_child) <= 0)
        {
            helper_fun_left(root);
        }
        if (balance < -1 && get_balance(root->right_child) > 0)
        {
            helper_fun_right(root->right_child);
            helper_fun_left(root);
        }
    }   

    int get_height(Node* node)
    {                                                   // FUNCTION TO RETURN THE HEIGHT AFTER UPDATING WHEN ROTATION PERFORMS
                                                       //  NEEDED BECAUSE AFTER ROTATION, HEIGHT ALSO AFFECTS, ALSO TO RETURN 
                                                      //   THE MAX HEIGHT TO PERFORM CORRECT ROTATION
        if (node == nullptr)
        {
            return 0;
        }
        return node->height;
    }

    int get_balance(Node* node)
    {
        if (node == nullptr) 
        {
            return 0;
        }
        return get_height(node->left_child) - get_height(node->right_child);
    }

    void helper_fun_right(Node*& y)                         // RIGHT ROTATION_HELPER FUNCTION
    {
        Node* x = y->left_child;
        Node* T2 = x->right_child;
        x->right_child = y;
        y->left_child = T2;
        y->height = max(get_height(y->left_child), get_height(y->right_child)) + 1;
        x->height = max(get_height(x->left_child), get_height(x->right_child)) + 1;
        y = x;
    }

    void helper_fun_left(Node*& x)                          // LEFT ROTATION_HELPER FUNCTION                                                       
    {
        Node* y = x->right_child;
        Node* T2 = y->left_child;
        y->left_child = x;
        x->right_child = T2;
        x->height = max(get_height(x->left_child), get_height(x->right_child)) + 1;
        y->height = max(get_height(y->left_child), get_height(y->right_child)) + 1;
        x = y;
    }

    void print_tree(Node* node)
    {
        if (!node)
        {
            return;
        }
        modify_node_txt_file(node);
        cout << "\n\nNODE_DATA--->      " << node->data << "   " << (node->c1 == R ? "R" : "B") << "\n";
        cout << "                       ROW_DATA   --->    " << node->row_data << "\n";
        cout << "                       PARENT_NODE--->    " << (node->parent ? node->parent->data : "nullptr") << "   " << (node->parent && node->parent->c1 == R ? "R" : "B") << "\n";
        cout << "                       LEFT_CHILD --->    " << (node->left_child ? node->left_child->data : "nullptr") << "   " << (node->left_child && node->left_child->c1 == R ? "R" : "B") << "\n";
        cout << "                       RIGHT_CHILD--->    " << (node->right_child ? node->right_child->data : "nullptr") << "   " << (node->right_child && node->right_child->c1 == R ? "R" : "B") << "\n";
        print_tree(node->left_child);
        print_tree(node->right_child);
    }

    void help_print()
    {
        print_tree(root);
    }

};
#endif