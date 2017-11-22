// main test driver for BST
// Created by Frank M. Carrano and Tim Henry.
// modified by

#include "BinarySearchTree.h"  // BST ADT
#include "Employee.h"
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

const char inputFileName[] = "employees.txt";

void displayTitle();
void readEmployee(BinarySearchTree<Employee>*);

void functionS(BinarySearchTree<Employee>*); //Search by unique key
void functionD(BinarySearchTree<Employee>*); //Recursive Depth-First Traversals
void functionB(BinarySearchTree<Employee>*); //Tree Breadth-First Traversal
void functionT(BinarySearchTree<Employee>*); //Print tree as an indented list
void functionL(BinarySearchTree<Employee>*); //Print the smallest key
void functionH(BinarySearchTree<Employee>*); //Print the largest key
void functionA(); //Hidden option. When chosen, display the name of the developer
void functionM(); //Show Menu

void functionI(BinarySearchTree<Employee>*); // EC option, Iterative Depth-First Traversals (DFT) using Stacks.

void chooseMenu(char&); // get the menu option on switch
void display(Employee &); // display function to pass to BST traverse functions
void displayIndented(Employee & , int&); //overloading function


int main()
{
    BinarySearchTree<Employee>* treePtr = new BinarySearchTree<Employee>();
    char menu = '0';
    readEmployee(treePtr);
    displayTitle();
    while (menu!='q' && menu!='Q')
    {
        chooseMenu(menu);
        switch(menu)
        {
            case 's':;
            case 'S':
                functionS(treePtr);
                break;
            case 'd':;
            case 'D':
                functionD(treePtr);
                break;
            case 'b':;
            case 'B':
                functionB(treePtr);
                break;
            case 't':;
            case 'T':
                functionT(treePtr);
                break;
            case 'l':;
            case 'L':
                functionL(treePtr);
                break;
            case 'h':;
            case 'H':
                functionH(treePtr);
                break;
            case 'a':;
            case 'A':
                functionA();
                break;
            case 'i':;
            case 'I':
                functionI(treePtr);
                    break;
            case 'm':;
            case 'M':
                functionM();
                break;
            case 'q':;
            case 'Q':
                break;
            default:
                cout << "The option " << menu << " does not exist. . . (Enter M to see the menu)\n";
        }
    }

    return 0;
}

void readEmployee(BinarySearchTree<Employee>* treePtr)
{
    ifstream input;
    int number;
    string word;

    input.open(inputFileName);
    while(!input)
    {
        cout << "Error opening " << inputFileName << "for reading\n";
        cin >> word;
        //exit(111); // My vision does not allow it
    }
    Employee dataIn;
    while (input>>number)
    {
        input.ignore();
        getline(input, word);
        dataIn.setEmployee(number,word);
        treePtr->insert(dataIn);
    }
    input.close();
}

void displayTitle()
{
    cout << "      +-------------------------------------------+\n";
    cout << "      |                                           |\n";
    cout << "      |        Employee Binary Search Trees       |\n";
    cout << "      |                                           |\n";
    cout << "      +-------------------------------------------+\n";
    functionM();
}

void functionS(BinarySearchTree<Employee>* treePtr) //Search by unique key
{
    int employeeId;
    Employee keyEmployee;
    Employee returnEmployee;

    do{
        cout << "Enter the employee ID you wants to search (Enter 0 to back menu): ";
        if (cin >> employeeId)
        {
            if (employeeId != 0)
            {
                keyEmployee.setId(employeeId);
                if (treePtr->getEntry(keyEmployee,returnEmployee))
                {
                    cout << "\n Employee information\n"
                        << "+----------------------+\n"
                        << " ID  \tName              "<< endl;
                        display(returnEmployee);
                    cout << "+---------------------+\n\n";
                }
                else
                    cout << "Does not found the Employee. . . " << endl;
            }
        }
        else
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Employee ID has to be a number . . . ";
            employeeId = 1;
        }
    } while (employeeId != 0);
}

void functionD(BinarySearchTree<Employee>* treePtr) //Recursive Depth-First Traversals
{
    cout << "\n Employee information preOrder\n"
         << "+--------------------------------+\n"
         << " ID  \tName                  "<< endl;
         treePtr->preOrder(display);
    cout << "+--------------------------------+\n\n";

    cout << "\n Employee information inOrder\n"
         << "+--------------------------------+\n"
         << " ID  \tName                  "<< endl;
         treePtr->inOrder(display);
    cout << "+--------------------------------+\n\n";

    cout << "\n Employee information postOrder\n"
         << "+--------------------------------+\n"
         << " ID  \tName                  "<< endl;
         treePtr->postOrder(display);
    cout << "+--------------------------------+\n\n";
}

void functionB(BinarySearchTree<Employee>* treePtr) //Tree Breadth-First Traversal
{
    cout << "\n Employee information breadthFirst Order\n"
         << "+----------------------------------------+\n"
         << " ID  \tName              "<< endl;
         treePtr->breadthFirstOrder(display);
    cout << "+----------------------------------------+\n\n";
}

void functionT(BinarySearchTree<Employee>* treePtr) //Print tree as an indented list
{
     treePtr->printIndented(displayIndented);
}

void functionL(BinarySearchTree<Employee>* treePtr) //Print the smallest key
{
    Employee smallest;
    if (treePtr->findSmallest(smallest))
    {
        cout << "\n Employee information\n"
             << "+---------------------+\n"
             << " ID  \tName              "<< endl;
             display(smallest);
             cout << "+---------------------+\n\n";
    }
    else
        cout << "The employee list is empty. . . " << endl;
}

void functionH(BinarySearchTree<Employee>* treePtr) //Print the largest key
{
    Employee largest;
    if (treePtr->findLargest(largest))
    {
        cout << "\n Employee information\n"
             << "+---------------------+\n"
             << " ID  \tName              "<< endl;
             display(largest);
             cout << "+---------------------+\n\n";
    }
    else
        cout << "The employee list is empty. . . " << endl;
}

void functionA() //Hidden option. When chosen, display the name of the developer
{
    cout << "+------------------------+\n"
         << "| Current Version: 1.00  |\n"
         << "| Developed by Yunyi Ren |\n"
         << "| 11/07/2017             |\n"
         << "+------------------------+\n";
}
void functionM() //menu
{
    cout << "\n               - Employee BST Menu -                    \n";
    cout << "---------------------------------------------------------\n";
    cout << "S - Search by employee identification number\n";
    cout << "D - Recursive Depth-First Traversals: inorder, preorder, postorder\n";
    cout << "B - Tree Breadth-First Traversal: Print by level\n";
    cout << "T - Print tree as an indented list\n";
    cout << "L - Print the smallest key.\n";
    cout << "H - Print the largest key.\n";
    cout << "I - Iterative DFT.\n";
    cout << "M - Show Menu\n";
    cout << "Q - Quit.\n";
    cout << "----------------------------------------------------------\n";
}

void functionI(BinarySearchTree<Employee>* treePtr)
{
    cout << "\n Employee information Preorder With Iterative\n"
         << "+---------------------------------------------+\n"
         << " ID  \tName                  "<< endl;
         treePtr->iterativePreorder(display);
    cout << "+---------------------------------------------+\n\n";

    cout << "\n Employee information Inorder With Iterative\n"
         << "+---------------------------------------------+\n"
         << " ID  \tName                  "<< endl;
         treePtr->iterativeInorder(display);
    cout << "+---------------------------------------------+\n\n";
}

void chooseMenu(char& menu)
{
    string word;
    cout << "Enter your option: ";
    cin >> word;
    while (word.size()>1)
    {
        cout << "Option must be one letter! ";
        cout << "Enter your option again: \n";
        cin >> word;
    }
    menu = word[0];
}

// display function to pass to BST traverse functions
void display(Employee &anItem)
{
   cout << " " << anItem.getId() << "\t" << anItem.getName() << endl;
}

void displayIndented(Employee& anItem, int& indent)
{
   cout << setw(indent*7) << indent << ". " << anItem.getId() << " " << anItem.getName() << endl;
}

