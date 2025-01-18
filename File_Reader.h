#pragma once
#ifndef FILE_READER_H
#define FILE_READER_H
#include<fstream>
#include <iostream>
#include<windows.h>
#include"AVL_TREE.h"
#include"Red_Black.h"
#include <filesystem>
namespace fs = std::filesystem;
using namespace std;

int str_len(const char* str)   // RETURN THE LENGTH OF THE CHARACTER ARRAY 
{
    int length = 0;
    while (str[length] != '\0')
    {
        length++;
    }
    return length;
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

void commit_history_display_function(const char* folder_name) // DISPLAY THE HISTORY OF THE ACTIONS YOU DID ON CONSOLE
{
    char array[100];
    char p_array[] = "/commit_history.txt";
    int i = 0;
    while (folder_name[i] != '\0')
    {
        array[i] = folder_name[i];
        i++;
    }
    for (int j = 0; p_array[j] != '\0'; j++)
    {
        array[i++] = p_array[j];
    }
    array[i] = '\0';
    ifstream obj1(array);
    cout << "\n\n\n\t\t\tDISPLAYING COMMIT HISTORY\n\n";
    char read_row[100];
    while (obj1.getline(read_row, sizeof(read_row)))
    {
        cout <<"\t\t\t" << read_row << endl;
    }
    obj1.close();
}

void i_to_s(int val, char* arr)// HELPER FUNCTION TO CONVERT INTEGER VALUE TO STRING
{
    int i = 0;
    char temp[20];
    bool flag = (val < 0);
    if (flag==true)
    {
        val = -val;
    }
    do
    {
        temp[i++] = (val % 10) + '0';
        val /= 10;
    } while (val > 0);
    if (flag==true)
    {
        temp[i++] = '-';
    }
    int j = 0;
    while (i > 0) arr[j++] = temp[--i];
    arr[j] = '\0';
}

void add_command_history(const char* branchFolder, const char* commitMessage) // FUNCTION TO STORE COMMAND HISTORY IN THE 
                                                                             //  TEXT FILES FOR EACH BRANCH/FOLDER SEPRATELY
{
    char array[100];
    char p_array[] = "/commit_history.txt";
    int i = 0;
    while (branchFolder[i] != '\0')
    {
        array[i] = branchFolder[i];
        i++;
    }
    for (int j = 0; p_array[j] != '\0'; j++)
    {
        array[i++] = p_array[j];
    }
    array[i] = '\0';
    ifstream c1(array);
    int count = 0;
    if (c1.is_open())
    {
        char line[256];
        while (c1.getline(line, sizeof(line)))
        {
            count++;
        }
        c1.close();
    }
    ofstream c2(array, ios::app); 
    count++; 
    char arr1[20];
    i_to_s(count, arr1);

    c2 << "- Commit #" << arr1 << "-> \"" << commitMessage << "\"" << endl;
    c2.close();
}

void load_repo(const char* folder_name) //FUNCTION TO READ NODES DATA STORED IN TEXT FILES AND 
                                       // DISPLAY_NODES DATA FROM FILES
{
    for (const auto& val : fs::directory_iterator(folder_name))
    {
        if (fs::is_regular_file(val))
        {
            const string file_path = val.path().string();
            const string file_name = val.path().filename().string();
            if (file_name == "commit_history.txt" || file_name == "commit_history")
            {
                continue;
            }
            if (file_path.substr(file_path.find_last_of('.') + 1) == "txt")
            {
                ifstream obj1(file_path);
                if (obj1.is_open()) {
                    char data[256] = { 0 };
                    obj1.getline(data, sizeof(data));
                    cout << "\t--->" << data << "\n";
                    data[0] = '\0';
                    obj1.getline(data, sizeof(data));
                    cout << "\t\t" << data << "\n";
                    data[0] = '\0';
                    obj1.getline(data, sizeof(data));
                    if (data[0] != '\0')
                    {
                        cout << "\t\t" << data << "\n";
                    }
                    data[0] = '\0';
                    obj1.getline(data, sizeof(data));
                    if (data[0] != '\0')
                    {
                        cout << "\t\t" << data << "\n";
                    }
                    data[0] = '\0';
                    obj1.getline(data, sizeof(data));
                    if (data[0] != '\0')
                    {
                        cout << "\t\t" << data << "\n\n";
                    }
                    data[0] = '\0';
                }
            }
        }
    }
}

void max_win_size()// TO OPEN CONSOLE WINDOW IN MAXIMIZE FORMAT WHEN THE PROGRAM STARTS TO EXECUTE/RUN
{
    HWND console_window = GetConsoleWindow();
    ShowWindow(console_window, SW_MAXIMIZE);
}

void show_current_branch(const char* ch)// TO DISPLAY IN WHICH BRANCH/FOLDER USER CURRENTLY WORKS OR AVAILABLE
{
    cout << "\n\n\n\t\t\tCURRENT-BRANCH --->   " << ch << "\n\n\t\t\t";
    system("pause");
    system("cls");
}

void font(int fontSize)//   TO SET THE FONT SIZE AND FONT STYLE ON CONSOLE SCREEN
{
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
    wcscpy_s(cfi.FaceName, L"Consolas");
    cfi.dwFontSize.X = 0;
    cfi.dwFontSize.Y = fontSize;
    SetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
}

bool compare_char_arrays(const char* arr1, const char* arr2) // TO COMPARE THE CHARACTER ARRAYS AND RETURN TRUE/FALSE 
                                                            //  BASED ON EQUALITY CRITERIA 
{
    int i = 0,max_i;
    max_i = str_len(arr1) > str_len(arr2) ? str_len(arr1) : str_len(arr2);
    while (i<max_i)
    {
        if (arr1[i] != arr2[i])
        {
            return false;
        }
        i++;
    }
    return true;
}

bool compare_char_arrays_ascii(const char* arr1, const char* arr2)// TO COMPARE THE CHARACTER ARRAYS AND RETURN TRUE/FALSE 
                                                                 //  BASED ON ASCII VALUES, LIKE IF WE WANT TO CONSIDER "A" 
                                                                //   AND "a" BOTH AS SAME
{
    int i = 0;
    while (arr1[i] != '\0' && arr2[i] != '\0') 
    {
        char ch1 = (arr1[i] >= 'A' && arr1[i] <= 'Z') ? (arr1[i] + 'a' - 'A') : arr1[i];
        char ch2 = (arr2[i] >= 'A' && arr2[i] <= 'Z') ? (arr2[i] + 'a' - 'A') : arr2[i];
        if (ch1 != ch2) 
        {
            return false;
        }
        i++;
    }
    return arr1[i] == '\0' && arr2[i] == '\0';
}

void create_folder(const char* folder_name) // TO CREATE THE DIRECTORIES/FOLDERS ALSO CHECK IF DIRECTORY ALREADY EXIT THEN
                                           //  RETURN, AND IF NOT THEN CREATE THE DIRECTORY/FOLDER
{
    fs::path obj1(folder_name);
    if (!fs::exists(obj1))
    {
        fs::create_directory(obj1);
    }
    else
    {
        return;
    }
}

void show_menu(int& select_column, const char* file_name, int& count) // FUNCTION DISPLAY THE MENU OPTION TO SELECT THE 
                                                                     //  GIVEN FIELDS IN EXCEL SHEET SO ON THE BASIS OF 
                                                                    //   SELECTED COLUMN, CREATION OF TREE WILL PROCESS 
{
    while (true) 
    {
        ifstream file(file_name);
        char ch;
        bool flag = true;
        count = 0;
        int x = 0;
        system("cls"); 
        cout << "\n\n\n\t\t=====================\t SELECT ONE OF THE FOLLOWING OPTIONS \t=======================\n\n\n";
        while (file.get(ch))
        {
            if (flag == true)
            {
                ++x;
                if (x < 10)
                {
                    cout<<"\t\t\t" << "0" << x << ") ";
                }
                else
                {
                    cout<<"\t\t\t" << x << ") ";
                }
                flag = false;
            }
            if (ch == '\n')
            {
                break;
            }
            if (ch == ',')
            {
                cout << endl;
                count++;
                flag = true;
            }
            else
            {
                cout << ch;
            }
        }
        count++;
        cout << "\n\n\n";
        file.close();
        int choice;
        cout << "\n\n\t\t\tENTER THE CHOICE BETWEEN 1 AND " << count << " OR PRESS 0 FOR GO BACK: ";
        cin >> choice;
        if (cin.fail()) 
        {
            cin.clear();                 
            cin.ignore(10000, '\n');    
            cout << "\n\n\t\t\tINVALID INPUT. PLEASE ENTER A VALID INTEGER.\n\t\t\t";
            system("pause");
            continue; 
        }
        if (choice >= 0 && choice <= count)
        {
            select_column = choice;
            system("cls");
            return; 
        }
        else
        {
            cout << "\n\n\t\t\tINVALID INPUT. PLEASE ENTER A VALID INTEGER.\n\t\t\t";
            system("pause");
        }
    }
}

void add_branch_to_array(const char* branch_name, char branches_array[100][50], const char* main_folder)
{                      // THIS FUNCTION JUST APPEND THE NAMES OF BRANCHES IN TEXT FILE WHENEVER A NEW BRANCH IS CREATED
                       //  SO WHEN USER WANTS TO SEE THE BRANCHES,IT SHOWS THE BRANCHES BY OPENING AND READING THAT TEXT FILE
    fs::path s1(branch_name);
    if (fs::exists(branch_name)|| fs::is_directory(branch_name))
    {
        return;
    }
    int i = 0;
    while (branch_name[i] != '\0' && i < 50)
    {
        branches_array[0][i] = branch_name[i];
        i++;
    }
    branches_array[0][i] = '\0';
    create_folder(main_folder);
    char arr[100];
    int j = 0;
    i = 0;
    while (main_folder[i] != '\0' && i < 50)
    {
        arr[j] = main_folder[i];
        j++;
        i++;
    }
    const char* ch1 = "/branches.txt";
    i = 0;
    while (ch1[i] != '\0')
    {
        arr[j] = ch1[i];
        j++;
        i++;
    }
    arr[j] = '\0';
    ofstream b1(arr, ios::app);
    if (b1.is_open()) {
        b1 << branches_array[0] << endl;
        b1.close();
    }
}

void read_branches_from_file(const char* folder_name, char branches_array[120][50])
{               // THIS FUNCTION READS THE DATA FROM THE TEXT FILE IN WHICH THE NAMES OF ALL BRANCHES/FOLDERS ARE STORED
               //  ALSO DISPLAYS THE NAME OF BRANCHES/FOLDERS CREATED
    fs::path filePath(folder_name);
    filePath /= "branches.txt";
    ifstream file(filePath);
    int count = 0;
    cout << "\n\n\n\n\t\t\tLISTING ALL BRANCHES.........\n\n";
    if (file.is_open()) 
    {
        int index = 0;
        while (file.getline(branches_array[index], 50) && index < 120)
        {
            cout << "\t\t\t" << ++count << ")  " << branches_array[index] << "\n\n";
            index++;
        }
        file.close();
    }
}

int tree_menu()// THIS FUNCTION SHOWS THE MENU TO SELECT ONE OF FOLLOWING TREE ALSO  
              //  IT RETURNS INTEGER NUMBER BUT TAKES INPUT IN A CHARACTER ARRAY
{
    static char arr[50];
    while (true) 
    {
        cout << "\n\n\t\t\t\tENTER THE COMMAND" << " OR PRESS 0 FOR GO BACK    ";
        cout << "\n\n\t\t\t\t\t1) AVL TREE STRUCTURE\n";
        cout << "\n\n\t\t\t\t\t2)  B  TREE STRUCTURE\n";
        cout << "\n\n\t\t\t\t\t3) RED-BLACK TREE STRUCTURE\n\n\t\t\t\t\t";
        cin.getline(arr, 50);
        if (arr[0] == '0' && arr[1] == '\0')
        {
            cout << "\n\t\t\t\t";
            system("pause");
            system("cls");
            return 0;
        }
        if (compare_char_arrays(arr, "init AVL"))
        {
            cout << "\n\t\t\t\t";
            system("pause");
            system("cls");
            return 1;
        }
        else if (compare_char_arrays(arr, "init B"))
        {
            cout << "\n\t\t\t\t";
            system("pause");
            system("cls");
            return 2;
        }
        else if (compare_char_arrays(arr, "init RED-BLACK"))
        {
            cout << "\n\t\t\t\t";
            system("pause");
            system("cls");
            return 3;
        }
        else
        {
            cout << "\n\n\t\t\tERROR -> INVALID INPUT.\n\t\t\t";
            system("pause");
            system("cls");
        }
    }
}

const char* input_file_name() // THIS FUNCTION UPLOADS THE .CSV FILE ALSO IF USER JUST WRITE THE NAME OF FILE, 
//  IT AUTOMATICALLY APPENDS THE .CSV EXTENSION BUT IF USER ALREADY WROTE IT THEN IT'LL NOT APPEND  
{
    static char file_name_input[15];
    static char new_file_name[20];
    while (true)
    {
        cout << "\n\n\n\n\n\n\t\tUPLOAD THE CSV FILE OR PRESS 0 TO CLOSE PROGRAM \t";
        cin.getline(file_name_input, 50);
        if (file_name_input[0] == '0' && file_name_input[1] == '\0')
        {
            cout << "\n\n\t\tPROGRAM CLOSING...\n\n\t\t";
            Sleep(1000);
            HWND obj1 = GetConsoleWindow(); // CLOSE THE PROGRAM/CONSOLSE SCREEN WHEN USER PRESS 0
            if (obj1)
            {
                PostMessage(obj1, WM_CLOSE, 0, 0);
            }
            return nullptr;
        }
        int i = 0;
        if (file_name_input[i++] == 'i' && file_name_input[i++] == 'n' && file_name_input[i++] == 'i' && file_name_input[i++] == 't' && file_name_input[i++] == ' ')
        {
            if (file_name_input[i] != '\0')
            {
                int j = 0;
                while (file_name_input[i] != '\0' && j < 50)
                {
                    new_file_name[j++] = file_name_input[i++];
                }
                new_file_name[j] = '\0';
                if (j < 4 || !(new_file_name[j - 4] == '.' && new_file_name[j - 3] == 'c' && new_file_name[j - 2] == 's' && new_file_name[j - 1] == 'v'))
                {
                    new_file_name[j++] = '.';
                    new_file_name[j++] = 'c';
                    new_file_name[j++] = 's';
                    new_file_name[j++] = 'v';
                    new_file_name[j] = '\0';
                }
                ifstream file(new_file_name);
                if (file.is_open())
                {
                    file.close();
                    return new_file_name;
                }
                else
                {
                    cout << "\n\t\tERROR-> FILE NOT EXIT.\n";
                }
            }
        }
        else
        {
            cout << "\n\t\tERROR-> INVALID INPUT.\n";
        }
        cout << "\n\t\t";
        system("pause");
        system("cls");
    }
}

void string_array_function(const char* str, char**& array, int& size)// THIS FUNCTION DIVIDES THE ROW INTO COLUMNS 
                                                                    //  OR SAY THAT TO SEPRATE DATA OF CELLS
{
    int len = str_len(str);
    size = 0;
    for (int i = 0; i < len; ++i)
    {
        if (str[i] == ',')
        {
            size++;
        }
    }
    size++;
    array = new char* [size];
    int x = 0, k = 0;
    for (int i = 0; i <= len; ++i)
    {
        if (str[i] == ',' || str[i] == '\0')
        {
            int cl = i - x;
            array[k] = new char[cl + 1];
            for (int j = 0; j < cl; ++j)
            {
                array[k][j] = str[x + j];
            }
            array[k][cl] = '\0';
            x = i + 1;
            k++;
        }
    }
}

void txt_file_copies_function(const char* ch1, const char* ch2)// THIS FUNCTION CREATE FOLDER/DIRECTORY AND THEN
                                                              //  COPY ALL TEXT FILES FROM SOURCE FILE TO DESTINATION FILE
                                                             //   ALSO IT CHECKS IF SOURCE FOLDER NOT EXISTS THEN JUST RETURN
                                                            //    ALSO IT WILL NOT TRANSFER THE LOG/COMMAND HISTORY
{
    fs::path s1(ch1);
    fs::path d1(ch2);

    if (fs::exists(ch2))
    {
        cout << "\n\n\t\tERROR -> BRANCH ALREADY EXIST\n\t\t\t";
        system("pause");
        system("cls");
        return;
    }

    if (!fs::exists(ch1))
    {
        cout << "\n\n\t\tERROR -> SOURCE_FOLDER DOES NOT EXIST\n\t\t\t";
        system("pause");
        system("cls");
        return;
    }
    
    if (!fs::exists(s1))
    {
        return;
    }
    create_folder(ch2);
    for (const auto& val : fs::directory_iterator(s1))
    {
        if (val.is_regular_file() && val.path().extension() == ".txt" && val.path().filename() != "commit_history.txt")
        {
            fs::path destFilePath = d1 / val.path().filename();
            fs::copy(val.path(), destFilePath, fs::copy_options::overwrite_existing);
        }
    }
    cout << "\n\n\t\t\tBRANCH CREATED SUCCESSFULLY\n\t\t\t";
    system("pause");
    system("cls");
}

void merge_branches(const char* ch1, const char* ch2)// FUNCTION TO MERGE 2 DIRECTORIES OR FOLDERS 
                                                    //  WITHOUT COPYING THEIR LOG HISTORY
{
    fs::path obj1(ch1);
    fs::path obj2(ch2);
    if (!fs::exists(ch1) || !fs::is_directory(ch1))
    {
        cout << "\n\n\t\tERROR -> BRANCH_FOLDER OR SOURCE FOLDER DOES NOT EXIST\n\t\t\t";
        return;
    }
    for (const auto& val : fs::directory_iterator(obj1))
    {
        if (val.is_regular_file() && val.path().extension() == ".txt" && val.path().filename() != "commit_history.txt")
        {
            fs::path destFilePath = obj2 / val.path().filename();
            fs::copy(val.path(), destFilePath, fs::copy_options::overwrite_existing);
        }
    }
    cout << "\n\n\t\t\tMERGING FROM SOURCE FILE TO DESTINATION FILE HAS DONE\n\n ";
    return;
}

void delete_branch(const char* branch_name, const char* txt_file_branch, const char* txt_file_name)
{// FUNCTION TO DELETE THE BRANCH/FOLDER BY PASSING PARAMETERS OF BARANCH NAME WHICH YOU WANT TO DELETE,
//  ALSO AFTER DELETE THE BRANCH/FOLDER, IT UPDATES IN THE TEXT FILE IN WHICH THE NAME OF BRANCHES HAD STORED
//  SO TXT_FILE_BRANCH IS THE NAME OF FOLDER IN WHICH TEXT FILE IS STORED AND TXT_FILE_NAME IS NAME OF TEXT FILE
//  IN WHICH BRANCH NAMES ARE STORED
    if (compare_char_arrays_ascii(branch_name, "DSA_Project") || compare_char_arrays_ascii(branch_name, "Branches") || compare_char_arrays_ascii(branch_name, "x64") || compare_char_arrays_ascii(branch_name, "Main_Folder") || compare_char_arrays(branch_name, "saved_Repo"))
    {
        cout << "\n\t\tERROR -> BRANCH_FOLDER CANNOT BE DELETED\n\t\t\t";
        system("pause");
        system("cls");
        return;
    }
    if (!fs::exists(branch_name) || !fs::is_directory(branch_name))
    {
        cout << "\n\n\t\tERROR -> BRANCH_FOLDER DOES NOT EXIST\n\t\t\t";
        system("pause");
        system("cls");
        return;
    }
    fs::remove_all(branch_name);
    cout << "\n\t\t\tBRANCH DELETED SUCCESSFULLY\n\n";
    char array[256];
    int i = 0, j = 0;
    while (txt_file_branch[i] != '\0')
    {
        array[i] = txt_file_branch[i];
        i++;
    }
    if (txt_file_branch[i - 1] != '/' && txt_file_branch[i - 1] != '\\') 
    {
        array[i++] = '/';
    }
    while (txt_file_name[j] != '\0')
    {
        array[i++] = txt_file_name[j++];
    }
    array[i] = '\0'; 
    ifstream obj1(array);
    ofstream obj2("temp_branches.txt");
    char data[256];
    while (obj1.getline(data, 256)) 
    {
        if (compare_char_arrays(data, branch_name)) 
        {
            continue; 
        }
        obj2 << data << "\n"; 
    }
    obj1.close();
    obj2.close();
    fs::remove(array); 
    fs::rename("temp_branches.txt", array); 
    system("pause");
    system("cls");
}

void AVL_Main_Implementation(const char* file_name, int select_col, const char* folder_name)
// THIS FUNCTION HAS IMPLEMENTATION OF AVL TREE , TO CREATE OBJECT AND INSERT THE DATA IN AVL THAT READ FROM FILE
// ALSO IT CONVERTS THE ROW IN COLUMNS TO DIVIDE THE DATA TO INSERT IT IN THE TXT FILES
{
    AVL tree;
    create_folder(folder_name);
    ifstream obj1(file_name);
    char read_row[1000];
    obj1.getline(read_row, sizeof(read_row));
    while (obj1.getline(read_row, sizeof(read_row)))
    {
        char** columns;
        int size = 0;
        string_array_function(read_row, columns, size);
        tree.insert_in_AVL(columns[select_col - 1], read_row, folder_name);
        for (int i = 0; i < size; ++i)
        {
            delete[] columns[i];
        }
        delete[] columns;
    }
    system("cls");
    cout << "\n\n\n\t\t\tDATA IN AVL TREE HAS LOADED\n\n";
    tree.help_print();
    cout << "\n\n\t\t\t";
    system("pause");
    system("cls");
    obj1.close();
    return;
}

void copy_char_array(const char* ch1, char* ch2)
{// THIS FUNCTON COPIES THE CHARACTER ARRAYS OR CAN SAY THAT MERGING TWO CHARACTER ARRAYS OR CONCATINATION PERFORMING
    int i = 0;
    while (ch1[i] != '\0') 
    {
        ch2[i] = ch1[i];
        i++;
    }
    ch2[i] = '\0'; 
}

void add_node_in_AVL_TREE(const char* file_name, int select_col, const char* folder_name)
{//THIS FUNCTION ADD THE NEW_NODE TO THE AVL BY TAKING THE DATA INPUT FROM USER TO FILL DATA FIELDS, ALSO UPDATE THE 
// .CSV FILE AND ALSO UPDATE THE TEXT FILES.ALSO IF USER NOT ENTER ANY DATA FIELD ON CONSOLE SCREEN THEN IT'LL REMAIN
// THAT PARTICULAR DATA CELL EMPTY AND FILL OTHER DATA CELLS IF DATA IS ENTERED BY USER. BUT IF USER ENTERS THE DATA 
// DUPLICATE VALUE THEN IT WILL MAY ADD IN CSV FILE BUT NOT IN AVL TREE, DUE TO WHICH TXT FILE ALSO NOT UPDATED DUE 
// TO DUPLICATION
    ifstream obj1(file_name);
    char row_data[1024] = { 0 };
    if (!obj1.getline(row_data, sizeof(row_data)))
    {
        obj1.close();
        return;
    }
    obj1.close(); 
    char* col_names[50] = { 0 }; 
    int count = 0;
    char* ptr = row_data; 
    col_names[count++] = ptr;
    for (int i = 0; row_data[i] != '\0'; i++) 
    {
        if (row_data[i] == ',') 
        {
            row_data[i] = '\0'; 
            col_names[count++] = &row_data[i + 1]; 
        }
    }
    char field_values[50][256] = { {0} }; 
    cout << "\n\n\t\t\tINSERT THE DATA TO ADD A NEW_NODE\n\n\n";
    for (int i = 0; i < count; i++)
    {
        cout << "\n\n\t\t\t" << col_names[i] << ": ";
        cin.getline(field_values[i], sizeof(field_values[i]));
        if (field_values[i][0] == '\0') 
        {
            field_values[i][0] = '\0'; 
        }
    }
    ofstream obj2(file_name, ios::app);
    for (int i = 0; i < count; i++)
    {
        obj2 << field_values[i];
        if (i < count - 1) {
            obj2 << ","; 
        }
    }
    obj2 << "\n";
    obj2.close();
}

void save_repository(const char* branches_folder, const char* branches_file, const char* active_branch, const char* filename, int select_col)
{//THIS FUNCTION IS USED TO SAVE REPOSITORY IN WHICH INCLUDES, CURRENT DATE, FORMAT VERSION,BRANCHES DETAILS LIKE NAME
// OF BRANCHES , ACTIVE BRANCH,BRANCH DETAILS LIKE NODES DATA...ETC
    char array[256];
    int i = 0, j = 0;
    while (branches_folder[i] != '\0') 
    {
        array[i] = branches_folder[i];
        i++;
    }
    if (branches_folder[i - 1] != '/' && branches_folder[i - 1] != '\\')
    {
        array[i++] = '/';  
    }
    while (branches_file[j] != '\0')
    {
        array[i++] = branches_file[j++];
    }
    array[i] = '\0';
    ifstream x1(array);
    const char* ch1 = "saved_Repo";
    char file_name_repo[100];
    i = 0;
    while (ch1[i] != '\0') 
    {
        file_name_repo[i] = ch1[i];
        i++;
    }
    file_name_repo[i++] = '/';  
    const char* repo_data_file = "repo_data.txt";
    j = 0;
    while (repo_data_file[j] != '\0')
    {
        file_name_repo[i++] = repo_data_file[j++];
    }
    file_name_repo[i] = '\0';
    ofstream repo_out(file_name_repo);
    repo_out << "# Repository Save File\n";
    repo_out << "# Date--> " << __DATE__ << "\n";
    repo_out << "# Format Version--> 1.0\n\n";
    repo_out << "Branches:\n";
    char arr1[150];
    while (x1.getline(arr1, 256)) 
    {
        repo_out << "- " << arr1 << "\n";  
    }
    repo_out << "\nActive Branch: " << active_branch << "\n";
    repo_out << "\nBranch Details:\n";
    ifstream file(filename);
    char read_row[200];
    file.getline(read_row, sizeof(read_row));
    while (file.getline(read_row, sizeof(read_row)))
    {
        char** columns;
        int size = 0;
        string_array_function(read_row, columns, size);
        repo_out << columns[select_col - 1] << endl;
        for (int i = 0; i < size; ++i)
        {
            delete[] columns[i];
        }
        delete[] columns;
    }
    x1.close();  
    repo_out.close();
    file.close();
    cout << "\n\n\t\tREPOSITORY SAVED SUCCESSFULLY 'saved_Repo/repo_data.txt'.\n\n\t\t\t";
    system("pause");
    system("cls");
    cout << "\n\n\t\t\tDISPLAYING SAVED REPOSITORY DATA:\n\n";
    ifstream repo_in(file_name_repo);
    char o1[256];
    while (repo_in.getline(o1, sizeof(o1)))
    {
        cout << o1 << endl; 
    }
    repo_in.close();

    cout << "\n\n\t\t\tEND OF REPOSITORY DATA.\n\n\t\t\t";
    system("pause");
    system("cls");
}



int get_command(char* filename)  
{
    char array[50]; 
    while (true)
    {
        filename[0] = '\0'; 
        cout << "\n\n\n\n\t\t\tENTER THE COMMAND OR PRESS 0 FOR GO BACK\t\t";
        cin.getline(array, 200);
        if (compare_char_arrays(array, "0"))
        {
            cout << "\t\t\t";
            system("pause");
            system("cls");
            return 0;
        }
        const char* branch_str1 = "branch ";
        const char* checkout_str = "checkout ";
        const char* log_str = "log";
        const char* commit_str = "commit ";
        const char* add_node_str = "add";
        const char* update_node_str = "update";
        const char* delete_node_str = "delete";
        const char* branches_str = "branches";
        const char* delete_branch_str = "delete-branch ";
        const char* merge_str = "merge ";
        const char* visualize_tree_str = "visualize-tree ";
        const char* current_branch_str = "current-branch";
        const char* save_str = "save";
        const char* load_str = "load ";
        const char* help_str = "help";
        int i = 0;
        // DISPLAY THE NAME OF BRANCHES/FOLDERS BY OPENING THE DIRECTORY BRANCHES AND THEN OPEN TEXT FILE TO READ THE DATA 
        // IN WHICH THE NAME OF BRANCHES ARE STORED 
        if (compare_char_arrays(array, branches_str))
        {
            return 6;  
        }
        // DISPLAY THE CURRENT BRANCH NAME. IF USER DIDN'T SWITCH THE BRANCH, THE CURRENT BRANCH REMAIN MAIN_FOLDER,ALSO
        // BY DEFAULT THE CURRENT BRANCH IS MAIN_FOLDER TILL THE USER SWITCH IT.THEN USER CAN ALSO SWITCH TO MAIN_FOLDER AGAIN
        if (compare_char_arrays(array, current_branch_str))
        {
            cout << "\t\t\t";
            system("pause");
            system("cls");
            return 10; 
        }
        //SAVES THE REPOSITORY BY CREATING TEXT FILE IN THE SAVE_REPO FOLDER AND SAVE THE CURRENT AND ACTIVE DETAILS OF
       // REPOSITORY IN TEXT FILE BY OPENING THE SAVE_REPO FOLDER/BRANCH AND THEN TXT FILE
        if (compare_char_arrays(array, save_str))
        {
            return 11; 
        }
        if (compare_char_arrays(array, help_str))
        {
            return 14; 
        }
        //CREATING NEW BRANCH BY USING BRANCH KEYWORD AND THEN NAME OF BRANCH WHICH USER WRITE. IT NOT JUST CREATE A NEW 
        // BRANCH ALSO IT UPDATES THE NAME OF BRANCHES IN TXT FILE BY OPENING THE BRANCHES FOLDER AND OPEN THE TXT FILE.
        while (branch_str1[i] != '\0' && array[i] == branch_str1[i]) 
        {
            i++;
        }
        if (branch_str1[i] == '\0')
        {
            int j = 0;
            while (array[i + j] != '\0' && array[i + j] != ' ')
            {
                filename[j] = array[i + j];  
                j++;
            }
            filename[j] = '\0';  
            if (compare_char_arrays_ascii(filename, "DSA_Project") || compare_char_arrays_ascii(filename, "Branches") || compare_char_arrays_ascii(filename, "x64") || compare_char_arrays_ascii(filename, "Main_Folder") || compare_char_arrays_ascii(filename, "saved_Repo"))
            {
                cout << "\n\t\tERROR -> BRANCH_FOLDER CANNOT CREATED\n\t\t\t";
                system("pause");
                system("cls");
                continue;
            }
            if (array[i + j] == '\0' || array[i + j] == ' ')
            {
                return 1;  
            }
        }
        i = 0;
        while (checkout_str[i] != '\0' && array[i] == checkout_str[i]) 
        {
            i++;
        }
        if (checkout_str[i] == '\0')
        {
            int j = 0;
            while (array[i + j] != '\0' && array[i + j] != ' ') 
            {
                filename[j] = array[i + j];  
                j++;
            }
            filename[j] = '\0';  
            if (compare_char_arrays_ascii(filename, "DSA_Project") || compare_char_arrays_ascii(filename, "Branches") || compare_char_arrays_ascii(filename, "x64") || compare_char_arrays_ascii(filename, "saved_Repo"))
            {
                cout << "\n\t\tERROR -> BRANCH_FOLDER CANNOT SWITCH\n\t\t\t";
                system("pause");
                system("cls");
                continue;
            }
            if (fs::exists(filename) && fs::is_directory(filename)) 
            {
                cout << "\n\n\t\t\tSWITCH TO BRANCH SUCCESSFULLY\n\t\t\t";
                cout << "\t\t\t";
                system("pause");
                system("cls");
                return 2;  
            }
            else
            {
                cout << "\n\t\tERROR -> BRANCH_FOLDER DOESN'T EXIST\n\t\t\t";
                system("pause");
                system("cls");
                continue;
            }
        }
// COMMIT COMMAND IS USED TO ADD A NEW NODE BY TAKING INPUT ALL THE DATA FIELDS OF CSV FILE AND STORE IT IN THE CSV FILE
// AND ALSO UPDATE IT IN THE TREE AND ALSO UPDATE IT IN THE TXT FILES OF THE CURRENT BRANCH, DELETE A PREVIOUS NODE FIRST
// TAKES INPUT FROM USER TO DELETE THE PARTICULAR NODE .AFTER INPUT, IT CHECKS WHEATER THE INPUT IS MATCHING WITH THE NODE
// DATA OR NOT. IF NOT THEN IT TELLS THE USER THAT NODE NOT FOUND AND SIMPLY RETUNS OTHERWISE IT DELETES THE NODE FROM THE
// TREE AS WELL DELETES THE RESPECTIVE ROW_DATA OF THAT NODE FROM CSV FILE AND ALSO DELETES THE TXT FILE REGARDING THE 
// CURRENT BRANCH. THEN UPDATE FUNCTION TAKES INPUT FROM THE USER TO SELECT THE NODE YOU WANT TO EDIT AND THEN REGARDING
// TO THE RESPECTIVE NODE, ALL THE ROW_DATA WILL BE EDITED BY TAKING INPUTS FROM THE USER AND IF USER REMAIN ANY INPUT EMPTY
// THEN IT REMAIN EMPTY IN CSV
        i = 0;
        while (commit_str[i] != '\0' && array[i] == commit_str[i]) 
        {
            i++;
        }
        if (commit_str[i] == '\0') 
        {
            while (array[i] == ' ') 
            {
                i++;
            }
            if (compare_char_arrays(array + i, add_node_str))
            {
                i += strlen(add_node_str); 
                int j = 0;
                while (array[i + j] != '\0' && array[i + j] != '\n' && array[i + j] != ' ')
                {
                    filename[j] = array[i + j]; 
                    j++;
                }
                filename[j] = '\0'; 
                return 4; 
            }
            else if (compare_char_arrays(array + i, update_node_str))
            {
                i += strlen(update_node_str); 
                int j = 0;
                while (array[i + j] != '\0' && array[i + j] != '\n' && array[i + j] != ' ')
                {
                    filename[j] = array[i + j]; 
                    j++;
                }
                filename[j] = '\0'; 
                return 5; 
            }
            else if (compare_char_arrays(array + i, delete_node_str)) 
            {
                i += strlen(delete_node_str); 
                int j = 0;
                while (array[i + j] != '\0' && array[i + j] != '\n' && array[i + j] != ' ')
                {
                    filename[j] = array[i + j];
                    j++;
                }
                filename[j] = '\0'; 
                return 13; 
            }
            else {
                cout << "\n\t\tERROR -> INVALID COMMIT FORMAT. PLEASE USE 'commit add', 'commit update', OR 'commit delete'\n";
                system("pause");
                system("cls");
                continue;
            }
        }
// THIS WORKS WITH THE LOG HISTORY, IT DISPLAYS AND STORES THE DATA WHAT USER DID ON CONSOLE. LIKE IT STORES THE COMMANDS
// THAT USER USED ON CONSOLE AND ALSO STORES THE USER ACTIVITY FOR EACH BRANCH SEPRATELY.
        if (compare_char_arrays(array, log_str))
        {
            return 3; 
        }
        i = 0;
        while (delete_branch_str[i] != '\0' && array[i] == delete_branch_str[i])
        {
            i++;
        }
// THIS DELETES THE ENTIRE FOLDER/BRANCH BY TAKING INPUT FROM USER USING DELETE-BRANCH KEYWORD AND BRANCH NAME, THE FOLDER
// AFTER DELETION LOST ITS ALL CONTENTS AND TEXT FILES
        if (delete_branch_str[i] == '\0')
        {
            int j = 0;
            while (array[i + j] != '\0' && array[i + j] != ' ')
            {
                filename[j] = array[i + j];
                j++;
            }
            filename[j] = '\0'; 
            if (filename[0] != '\0')
            {
                return 7; 
            }
        }
// THIS CONTROLS THE MERGING OF FILES, TO MERGE TWO DIFFERENT FIES, AFTER MERGING, THE TXT FILES STORED IN THE SOURCE FOLDER
// WILL COPY TO DESTINATION FOLDER EXCEPT THE COMMIT_HISTORY FILE.
        i = 0;
        while (merge_str[i] != '\0' && array[i] == merge_str[i])
        {
            i++;
        }
        if (merge_str[i] == '\0')
        {
            int j = 0, k = 0;
            char arr1[50] = { 0 };
            char arr2[50] = { 0 };
            while (array[i + j] != '\0' && array[i + j] != ' ') 
            {
                arr1[j] = array[i + j];
                j++;
            }
            arr1[j] = '\0'; 
            if (array[i + j] == ' ') 
            {
                i = i + j + 1; 
                while (array[i + k] != '\0' && array[i + k] != ' ')
                {
                    arr2[k] = array[i + k];
                    k++;
                }
                arr2[k] = '\0'; 
            }
            if (arr1[0] != '\0' && arr2[0] != '\0' && compare_char_arrays(arr1, arr2) == false) 
            {
                int m = 0;
                while (arr1[m] != '\0') 
                {
                    filename[m] = arr1[m];
                    m++;
                }
                filename[m] = ' ';
                m++;
                int n = 0;
                while (arr2[n] != '\0') 
                {
                    filename[m + n] = arr2[n];
                    n++;
                }
                filename[m + n] = '\0'; 
                merge_branches(arr1, arr2);
                return 8; 
            }
            else 
            {
                cout << "\n\t\t\tERROR -> CAN'T MERGE FILES OF SAME NAME\n\t\t\t";
                system("pause");
                system("cls");
                continue;
            }
        }
// THIS DISPLAYS THE NODE DATA ALONG WITH ITS CHILD AND PARENT DATA, SO THIS IS THE VISUALIZATION BY READING DATA FROM THE 
// TEXT FILES OF THE CURRENT BRANCH
        i = 0;
        while (visualize_tree_str[i] != '\0' && array[i] == visualize_tree_str[i]) 
        {
            i++;
        }
        if (visualize_tree_str[i] == '\0')
        {
            int j = 0;
            while (array[i + j] != '\0' && array[i + j] != ' ')
            {
                filename[j] = array[i + j];
                j++;
            }
            filename[j] = '\0'; 
            if (filename[0] != '\0')
            {
                return 9; 
            }
        }
// THIS FUNCTION LOADS THE REPOSITORY, MEANS THE DATA IN THE CURRENT BRANCH TO DISPLAY ALL THE DATA IN THE TEXT FILES OF
// THE CURRENT BRANCH
        i = 0;
        while (load_str[i] != '\0' && array[i] == load_str[i])
        {
            i++;
        }

        if (load_str[i] == '\0')
        {
            int j = 0;
            while (array[i + j] != '\0' && array[i + j] != ' ')
            {
                filename[j] = array[i + j];
                j++;
            }
            filename[j] = '\0'; 
            if (filename[0] != '\0')
            {
                return 12; 
            }
        }
        cout << "\n\t\tERROR -> INVALID INPUT. PLEASE TRY AGAIN.\n\t\t\t";
        system("pause");
        system("cls");
    }
}

void append_text(const char* branch_file, const char* text, char* result) 
{                                                                        // THIS FUNCTION HELPS TO APPEND TWO CHARACTER
                                                                        //  ARRAYS AND STORE THEM IN ANOTHER CHARACTER ARRAY
    int len1 = str_len(branch_file);
    int len2 = str_len(text);
    int i = 0;
    for (; i < len1; ++i)
    {
        result[i] = branch_file[i];
    }
    for (int j = 0; j < len2; ++j) 
    {
        result[i + j] = text[j];
    }
    result[len1 + len2] = '\0';
}

bool delete_node_in_AVL_TREE(const char* file_name, int select_col, const char* folder_name)
{// THIS FUNCTION UPDATES THE TXT FILE IN THE CURRENT BRANCH AFTER DELETION , ALSO THIS FUNCTION UPDATES THE .CSV FILE
//  AFTER DELETION PERFORM IN AVL TREE
    char array[50] = { 0 };
    cout << "\n\n\t\t\tENTER THE NODE YOU WANT TO DELETE (FROM COLUMN " << select_col + 1 << ")       ";
    cin.getline(array, sizeof(array));
    ifstream obj2(file_name);
    char file_row[400] = { 0 };
    ofstream obj1("temp.csv");
    char ch[400] = { 0 };
    bool found = false;
    while (obj2.getline(ch, sizeof(ch)))
    {
        char* fields[50] = { 0 };
        int count = 0;
        fields[count++] = ch;
        for (int i = 0; ch[i] != '\0'; i++) 
        {
            if (ch[i] == ',')
            {
                ch[i] = '\0'; 
                fields[count++] = &ch[i + 1];
            }
        }
        if (compare_char_arrays(fields[select_col], array))
        {
            found = true;
            char txt_p[200] = { 0 };
            char result[80] = {0};
            int i = 0, j = 0;
            while (folder_name[i] != '\0')
            {
                result[i] = folder_name[i];
                i++;
            }
            if (result[i-1] != '/')
            {
                result[i++] = '/';
            }
            while (array[j] != '\0')
            {
                result[i++] = array[j++];
            }          
            const char* ch4 = ".txt";
            for (j = 0; ch4[j] != '\0'; j++)
            {
                result[i++] = ch4[j];
            }

            result[i] = '\0';
            if (fs::exists(result))
            {
                fs::remove(result);
            }
            continue; 
        }
        for (int i = 0; i < count; i++)
        {
            obj1 << fields[i];
            if (i < count - 1)
            {
                obj1 << ",";
            }
        }
        obj1 << "\n";
    }
    obj2.close();
    obj1.close();
    if (!found) 
    {
        cout << "\n\n\n\t\t\t NODE HAS NOT FOUND\n\n\t\t\t";
        remove("temp.csv"); 
        cout << "\t\t\t";
        system("pause");
        system("cls");
        return false;
    }
    if (found)
    {
        cout << "\n\n\n\t\t\t NODE HAS DELETED SUCCESSFULLY\n\n\t\t\t";
    }
    remove(file_name);
    rename("temp.csv", file_name);
    return true;
}

bool update_node_in_AVL_TREE(const char* file_name, int select_col, const char* folder_name)
{// THIS FUNCTION FIRST TAKES INPUT FROM USER TO MATCH THE NODE IN THE SELECTED COLUMN, IF THE NODE FOUND THEN IT JUST EDIT 
//  THE DATA IN .CSV FILE AND UPDATE IT THEN IT UPDATES TXT FILE IN RESPECTIVE FOLDER/BRANCH, THEN IT ALSO UPDATES THE AVL TREE
    char array[50] = { 0 };
    cout << "\n\n\t\t\tENTER THE NODE YOU WANT TO UPDATE (FROM COLUMN " << select_col + 1 << ")        ";
    cin.getline(array, sizeof(array));
    ifstream obj2(file_name);
    char file_row[400] = { 0 };
    ofstream obj1("temp.csv");
    char ch[400] = { 0 };
    bool found = false;
    while (obj2.getline(ch, sizeof(ch)))
    {
        char* fields[50] = { 0 };
        int count = 0;
        fields[count++] = ch;
        for (int i = 0; ch[i] != '\0'; i++)
        {
            if (ch[i] == ',')
            {
                ch[i] = '\0';
                fields[count++] = &ch[i + 1];
            }
        }
        if (compare_char_arrays(fields[select_col], array))
        {
            found = true;
            char txt_p[200] = { 0 };
            char result[80] = { 0 };
            int i = 0, j = 0;
            while (folder_name[i] != '\0')
            {
                result[i] = folder_name[i];
                i++;
            }
            if (result[i - 1] != '/')
            {
                result[i++] = '/';
            }
            while (array[j] != '\0')
            {
                result[i++] = array[j++];
            }
            const char* ch4 = ".txt";
            for (j = 0; ch4[j] != '\0'; j++)
            {
                result[i++] = ch4[j];
            }

            result[i] = '\0';
            if (fs::exists(result))
            {
                fs::remove(result);
            }
            continue;
        }
        for (int i = 0; i < count; i++)
        {
            obj1 << fields[i];
            if (i < count - 1)
            {
                obj1 << ",";
            }
        }
        obj1 << "\n";
    }
    obj2.close();
    obj1.close();
    if (!found)
    {
        cout << "\n\n\n\t\t\t NODE HAS NOT FOUND\n\n\t\t\t";
        remove("temp.csv");
        return false;
    }
    if (found)
    {
        cout << "\n\n\n\t\t\t NODE WILL BE UPDATED SUCCESSFULLY AFTER YOU INSERT DATA\n\n\t\t\t";
        system("pause");
        system("cls");
    }
    remove(file_name);
    rename("temp.csv", file_name);
    return true;
}

void RB_Main_Implementation(const char* file_name, int select_col, const char* folder_name)
// THIS FUNCTION HAS IMPLEMENTATION OF RED-BLACK TREE , TO CREATE OBJECT AND INSERT THE DATA IN RED-BLACK THAT READ FROM FILE
// ALSO IT CONVERTS THE ROW IN COLUMNS TO DIVIDE THE DATA TO INSERT IT IN THE TXT FILES
{
    red_black_tree tree(folder_name);
    create_folder(folder_name);
    ifstream obj1(file_name);
    char read_row[200];
    obj1.getline(read_row, sizeof(read_row));
    while (obj1.getline(read_row, sizeof(read_row)))
    {
        char** columns;
        int size = 0;
        string_array_function(read_row, columns, size);
        tree.insert(columns[select_col - 1], read_row);
        for (int i = 0; i < size; ++i)
        {
            delete[] columns[i];
        }
        delete[] columns;
    }
    system("cls");
    cout << "\n\n\n\t\t\tDATA IN RED-BLACK TREE HAS LOADED\n\n";
    tree.help_print();
    cout << "\t\t\t";
    system("pause");
    system("cls");
    obj1.close();
}

void add_node_in_RED_BLACK_TREE(const char* file_name, int select_col, const char* folder_name)
{//THIS FUNCTION ADD THE NEW_NODE TO THE RED-BLACK TREE BY TAKING THE DATA INPUT FROM USER TO FILL DATA FIELDS, ALSO 
//UPDATE THE .CSV FILE AND ALSO UPDATE THE TEXT FILES.ALSO IF USER NOT ENTER ANY DATA FIELD ON CONSOLE SCREEN THEN IT'LL
// REMAIN THAT PARTICULAR DATA CELL EMPTY AND FILL OTHER DATA CELLS IF DATA IS ENTERED BY USER. BUT IF USER ENTERS THE DATA 
// DUPLICATE VALUE THEN IT WILL MAY ADD IN CSV FILE BUT NOT IN AVL TREE, DUE TO WHICH TXT FILE ALSO NOT UPDATED DUE 
// TO DUPLICATION
    ifstream obj1(file_name);
    char row_data[1024] = { 0 };
    if (!obj1.getline(row_data, sizeof(row_data)))
    {
        obj1.close();
        return;
    }
    obj1.close();
    char* col_names[50] = { 0 };
    int count = 0;
    char* ptr = row_data;
    col_names[count++] = ptr;
    for (int i = 0; row_data[i] != '\0'; i++)
    {
        if (row_data[i] == ',')
        {
            row_data[i] = '\0';
            col_names[count++] = &row_data[i + 1];
        }
    }
    char field_values[50][256] = { {0} };
    cout << "\n\n\t\t\tINSERT THE DATA TO ADD A NEW_NODE\n\n\n";
    for (int i = 0; i < count; i++)
    {
        cout << "\n\n\t\t\t" << col_names[i] << ": ";
        cin.getline(field_values[i], sizeof(field_values[i]));
        if (field_values[i][0] == '\0')
        {
            field_values[i][0] = '\0';
        }
    }
    ofstream obj2(file_name, ios::app);
    for (int i = 0; i < count; i++)
    {
        obj2 << field_values[i];
        if (i < count - 1) {
            obj2 << ",";
        }
    }
    obj2 << "\n";
    obj2.close();
}

bool update_node_in_RED_BLACK_TREE(const char* file_name, int select_col, const char* folder_name)
{// THIS FUNCTION FIRST TAKES INPUT FROM USER TO MATCH THE NODE IN THE SELECTED COLUMN, IF THE NODE FOUND THEN IT JUST EDIT 
//  THE DATA IN .CSV FILE AND UPDATE IT THEN IT UPDATES TXT FILE IN RESPECTIVE FOLDER/BRANCH, THEN IT ALSO UPDATES THE AVL TREE
    char array[50] = { 0 };
    cout << "\n\n\t\t\tENTER THE NODE YOU WANT TO UPDATE (FROM COLUMN " << select_col + 1 << ")     ";
    cin.getline(array, sizeof(array));
    ifstream obj2(file_name);
    char file_row[400] = { 0 };
    ofstream obj1("temp.csv");
    obj1 << file_row << "\n";
    char ch[400] = { 0 };
    bool found = false;
    while (obj2.getline(ch, sizeof(ch)))
    {
        char* fields[50] = { 0 };
        int count = 0;
        fields[count++] = ch;
        for (int i = 0; ch[i] != '\0'; i++)
        {
            if (ch[i] == ',')
            {
                ch[i] = '\0';
                fields[count++] = &ch[i + 1];
            }
        }
        if (compare_char_arrays(fields[select_col], array))
        {
            found = true;
            char txt_p[200] = { 0 };
            char result[80] = { 0 };
            int i = 0, j = 0;
            while (folder_name[i] != '\0')
            {
                result[i] = folder_name[i];
                i++;
            }
            if (result[i - 1] != '/')
            {
                result[i++] = '/';
            }
            while (array[j] != '\0')
            {
                result[i++] = array[j++];
            }
            const char* ch4 = ".txt";
            for (j = 0; ch4[j] != '\0'; j++)
            {
                result[i++] = ch4[j];
            }

            result[i] = '\0';
            if (fs::exists(result))
            {
                fs::remove(result);
            }
            continue;
        }
        for (int i = 0; i < count; i++)
        {
            obj1 << fields[i];
            if (i < count - 1)
            {
                obj1 << ",";
            }
        }
        obj1 << "\n";
    }
    obj2.close();
    obj1.close();
    if (!found)
    {
        cout << "\n\n\n\t\t\t NODE HAS NOT FOUND\n\n\t\t\t";
        remove("temp.csv");
        return false;
    }
    if (found)
    {
        cout << "\n\n\n\t\t\t NODE WILL BE UPDATED SUCCESSFULLY AFTER YOU INSERT DATA\n\n\t\t\t";
        system("pause");
        system("cls");
    }
    remove(file_name);
    rename("temp.csv", file_name);
    return true;
}

bool delete_node_in_RED_BLACK_TREE(const char* file_name, int select_col, const char* folder_name)
{// THIS FUNCTION UPDATES THE TXT FILE IN THE CURRENT BRANCH AFTER DELETION , ALSO THIS FUNCTION UPDATES THE .CSV FILE
//  AFTER DELETION PERFORM IN AVL TREE
    char array[50] = { 0 };
    cout << "\n\n\t\t\tENTER THE NODE YOU WANT TO DELETE (FROM COLUMN " << select_col + 1 << ")     ";
    cin.getline(array, sizeof(array));
    ifstream obj2(file_name);
    char file_row[400] = { 0 };
    ofstream obj1("temp.csv");
    obj1 << file_row << "\n";
    char ch[400] = { 0 };
    bool found = false;
    while (obj2.getline(ch, sizeof(ch)))
    {
        char* fields[50] = { 0 };
        int count = 0;
        fields[count++] = ch;
        for (int i = 0; ch[i] != '\0'; i++)
        {
            if (ch[i] == ',')
            {
                ch[i] = '\0';
                fields[count++] = &ch[i + 1];
            }
        }
        if (compare_char_arrays(fields[select_col], array))
        {
            found = true;
            char txt_p[200] = { 0 };
            char result[80] = { 0 };
            int i = 0, j = 0;
            while (folder_name[i] != '\0')
            {
                result[i] = folder_name[i];
                i++;
            }
            if (result[i - 1] != '/')
            {
                result[i++] = '/';
            }
            while (array[j] != '\0')
            {
                result[i++] = array[j++];
            }
            const char* ch4 = ".txt";
            for (j = 0; ch4[j] != '\0'; j++)
            {
                result[i++] = ch4[j];
            }

            result[i] = '\0';
            if (fs::exists(result))
            {
                fs::remove(result);
            }
            continue;
        }
        for (int i = 0; i < count; i++)
        {
            obj1 << fields[i];
            if (i < count - 1)
            {
                obj1 << ",";
            }
        }
        obj1 << "\n";
    }
    obj2.close();
    obj1.close();
    if (!found)
    {
        cout << "\n\n\n\t\t\t NODE HAS NOT FOUND\n\n\t\t\t";
        remove("temp.csv");
        return false;
    }
    if (found)
    {
        cout << "\n\n\n\t\t\t NODE HAS DELETED SUCCESSFULLY\n\n\t\t\t";
        system("pause");
    }
    remove(file_name);
    rename("temp.csv", file_name);
    return true;
}

void display_commands_syntax()
{
    system("cls");
    cout << "\n\n\n\t\t\tTO CREATE REPOSITORY OR CHOOSE TREE--->  init <TREE_NAME IN GIVEN MENU>\n\n";
    cout << "\n\n\n\t\t\tTO CREATE BRANCH                   --->  branch <FOLDER_NAME/BRANCH_NAME>\n\n";
    cout << "\n\n\n\t\t\tTO SWITCH BRANCH                   --->  checkout <FOLDER_NAME/BRANCH_NAME>\n\n";
    cout << "\n\n\n\t\t\tTO ADD NEW_NODE                    --->  commit add\n\n";
    cout << "\n\n\n\t\t\tTO DELETE NODE                     --->  commit delete\n\n";
    cout << "\n\n\n\t\t\tTO UPDATE NODE                     --->  commit update\n\n";
    cout << "\n\n\n\t\t\tTO DISPLAY ALL BRANCHES/FOLDERS    --->  branches\n\n";
    cout << "\n\n\n\t\t\tTO DELETE A BRANCH/FOLDER          --->  delete-branch <FOLDER_NAME/BRANCH_NAME>\n\n";
    cout << "\n\n\n\t\t\tTO MERGE A BRANCH/FOLDER           --->  merge <SOURCE FOLDER_NAME/BRANCH_NAME DESTINATION' 'FOLDER_NAME/BRANCH_NAME>\n\n";
    cout << "\n\n\n\t\t\tTO VISUALIZE A TREE                --->  visualize-tree <FOLDER_NAME/BRANCH_NAME>\n\n";
    cout << "\n\n\n\t\t\tTO DISPLAY A COMMIT/COMMAND HISTORY--->  log\n\n";
    cout << "\n\n\n\t\t\tTO DISPLAY A CURRENT BRANCH/FOLDER --->  current-branch\n\n";
    cout << "\n\n\n\t\t\tTO SAVE A REPOSITORY               --->  save\n\n";
    cout << "\n\n\n\t\t\tTO LOAD A REPOSITORY FROM FILE     --->  load <FOLDER_NAME/BRANCH_NAME>\n\n";
    cout << "\n\n\n\t\t\tTO DISPLAY SYNTAX OF ALL COMMANDS  --->  help\n\n\t\t\t";
    system("pause");
    system("cls");
}
#endif