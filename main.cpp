#include <iostream>
#include "File_Reader.h"
#include"Node.h"
using namespace std;
// MOHAMMAD ROHAAN 22I-2327
// ALI BIN SALMAN  22I-0894
// M.BILAL BAIG    22I-0819           
int main()
{
label_9:
    max_win_size();
    font(24);
    int command_get;
    const char* file_name = input_file_name();
    char branches_array[100][50];
    char branch_file[100] = { 0 };
    char folder_name[50] = "Main_Folder";
     char* current_branch = folder_name;
    cout << "\n\t\t";
    system("pause");
    system("cls");
label_13:
    int select_tree = tree_menu();
    if (select_tree == 0)
    {
        goto label_9;
    }
label_24:
    int col_count = 0, select_col = -1;
    show_menu(select_col, file_name, col_count);
    if (select_col == 0)
    {
        cin.ignore();
        system("cls");
        goto label_13;
    }
      cin.ignore();
    if (select_tree == 1) // TREE SELECTION BASED ON INIT COMMAND
    {
        AVL_Main_Implementation(file_name, select_col, folder_name);
    }
    else if (select_tree == 3)
    {
        RB_Main_Implementation(file_name, select_col, folder_name);
    }
    command_get = 1;
    char result[256];
    while (command_get != 0)
    {
        command_get = get_command(branch_file); // GET THE COMMAND/INSTRUCTION
        if (command_get == 0)
        {
            goto label_24;
        }
        if (command_get == 1) // CREATE A NEW BRANCH/FOLDER
        {
            txt_file_copies_function(current_branch, branch_file);
            add_branch_to_array(branch_file, branches_array, "Branches");
            append_text("branch ", branch_file, result);
            add_command_history(current_branch, result);
        }
        else if (command_get == 2) // SWITCH BETWEEN TWO BRANCHES/FOLDERS
        {       
            str_cpy(current_branch, branch_file);
            system("cls");
            append_text("checkout ", branch_file, result);
            add_command_history(current_branch, result);
        }
        else if (command_get == 6) // SHOW ALL THE BRANCHES/FOLDERS
        {
            read_branches_from_file("Branches", branches_array);
            append_text("branches ", branch_file, result);
            add_command_history(current_branch, result);
            cout << "\t\t\t";
            system("pause");
            system("cls");
        }
        else if (command_get == 10) // SHOW THE CURRENT FOLDER/BRANCH
        {
            show_current_branch(current_branch);
            add_command_history(current_branch, "current-branch ");
        }
        else if (command_get == 7) // DELETE THE BRANCH/FOLDER
        {
            if (compare_char_arrays(current_branch, branch_file))
            {
                cout << "\n\n\t\t\tCAN'T DELETE THE ACTIVE BRANCH,YOU MAY HAVE TO SWITCH FIRST BEFORE DELETING ACTIVE BRANCH\n\n\t\t\t";
                system("pause");
                system("cls");
                continue;
            }
            delete_branch(branch_file, "Branches", "branches.txt");
            append_text("delete-branch ", branch_file, result);
            add_command_history(current_branch, result);
        }
        else if (command_get == 4) // ADD THE NEW REPOSITORY
        {
            if (select_tree == 1)
            {
                add_command_history(current_branch, " add");
                add_node_in_AVL_TREE(file_name, select_col, current_branch);
                AVL_Main_Implementation(file_name, select_col, folder_name);
                cout << "\n\n\t\t\t\tNODE HAS ADDEDD SUCCESSFULLY\n\t\t\t";
                system("pause");
                system("cls");
           }
            else if (select_tree == 3)
            {
                add_command_history(current_branch, " add");
                add_node_in_RED_BLACK_TREE(file_name, select_col, current_branch);
                cout << "\n\n\t\t\t\tNODE HAS ADDEDD SUCCESSFULLY\n\t\t\t";
                system("pause");
                system("cls");
            }
        }
        else if (command_get == 8) // MERGE THE TWO REPOSITORIES
        {
            append_text("merge ", branch_file, result);
            add_command_history(current_branch, result);
            cout << "\t\t\t";
            system("pause");
            system("cls");
        }
        else if (command_get == 11) // SAVE THE REPOSITORY
        {
            add_command_history(current_branch, "save ");
            save_repository("Branches", "branches.txt", current_branch, file_name, select_col);
        }
        else if (command_get == 9) // VISUALIZE THE DATA IN REPOSITORY
        {
            append_text("visualize-tree ", branch_file, result);
            add_command_history(current_branch, result);
			if (select_tree == 1)
			{
                AVL_Main_Implementation(file_name, select_col, folder_name);
			}
			else if (select_tree == 3)
			{
                RB_Main_Implementation(file_name, select_col, folder_name);
            }
            cout << "\n\t\t\t";
            system("pause");
            system("cls");
        }
        else if (command_get == 12) // LOADING THE REPOSITORY
        {
            append_text("load ", branch_file, result);
            add_command_history(current_branch, result);
            cout << "\n\n\n\t\t\tLOADING THE REPOSITORY..........\n\n\n";
            load_repo(branch_file);
            cout << "\t\t\t";
            system("pause");
            system("cls");
        }
        else if (command_get == 3) //DISPLAY THE COMAND HISTORY
        {
            add_command_history(current_branch, "log");
            commit_history_display_function(current_branch);
            cout << "\t\t\t";
            system("pause");
            system("cls");
        }
        else if (command_get == 13) // DELETE THE REPOSITORY
        {
            if (select_tree == 3)
            {
                add_command_history(current_branch, "commit delete");
                if (delete_node_in_RED_BLACK_TREE(file_name, select_col - 1, current_branch))
                {
                    RB_Main_Implementation(file_name, select_col, folder_name);
                }                
                    cout << "\t\t\t";
                    system("pause");
                    system("cls");                
                continue;
           }
            else if (select_tree == 1)
            {
                add_command_history(current_branch, "commit delete");
                if (delete_node_in_AVL_TREE(file_name, select_col - 1, current_branch))
                {
                    AVL_Main_Implementation(file_name, select_col, folder_name);
                }
                cout << "\t\t\t";
                system("pause");
                system("cls");
                continue;
            }
        }
        else if (command_get == 5)  // UPDATE THE REPOSITORY
        {
            if (select_tree == 1)
            {
                add_command_history(current_branch, " update");
                if (update_node_in_AVL_TREE(file_name, select_col - 1, current_branch))
                {
                    add_node_in_AVL_TREE(file_name, select_col, folder_name);
                    AVL_Main_Implementation(file_name, select_col, folder_name);
                }
                    cout << "\t\t\t";
                    system("pause");
                    system("cls");
           }
            else if (select_tree == 3)
            {
                add_command_history(current_branch, " update");
                if (update_node_in_RED_BLACK_TREE(file_name, select_col - 1, current_branch))
                {
                    add_node_in_RED_BLACK_TREE(file_name, select_col, folder_name);
                    RB_Main_Implementation(file_name, select_col, folder_name);
                }
                    cout << "\t\t\t";
                    system("pause");
                    system("cls");
            }
        }
        else if (command_get == 14) //TO DISPLAY ALL THE COMMANDS SYNTAX
        {
            display_commands_syntax();
        }
    }
    return 0;
}