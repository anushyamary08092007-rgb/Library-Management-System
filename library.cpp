#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class Book
{
public:
    int bookID;
    char title[50];
    char author[50];
    bool issued;

    void addBook()
    {
        cout << "\nEnter Book ID: ";
        cin >> bookID;

        cin.ignore();

        cout << "Enter Book Title: ";
        cin.getline(title, 50);

        cout << "Enter Author Name: ";
        cin.getline(author, 50);

        issued = false;
    }

    void displayBook()
    {
        cout << "\n--------------------------------";
        cout << "\nBook ID      : " << bookID;
        cout << "\nTitle        : " << title;
        cout << "\nAuthor       : " << author;
        cout << "\nStatus       : ";

        if (issued)
            cout << "Issued";
        else
            cout << "Available";

        cout << "\n--------------------------------";
    }
};

void addBook()
{
    Book b;

    ofstream file("books.dat", ios::binary | ios::app);

    b.addBook();

    file.write((char*)&b, sizeof(b));

    file.close();

    cout << "\nBook Added Successfully!\n";
}

void displayBooks()
{
    Book b;

    ifstream file("books.dat", ios::binary);

    if (!file)
    {
        cout << "\nNo Books Found!\n";
        return;
    }

    while (file.read((char*)&b, sizeof(b)))
    {
        b.displayBook();
    }

    file.close();
}

void searchBook()
{
    Book b;
    char searchTitle[50];
    bool found = false;

    ifstream file("books.dat", ios::binary);

    cin.ignore();

    cout << "\nEnter Book Title: ";
    cin.getline(searchTitle, 50);

    while (file.read((char*)&b, sizeof(b)))
    {
        if (strcmp(b.title, searchTitle) == 0)
        {
            b.displayBook();
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "\nBook Not Found!\n";
    }

    file.close();
}

void issueBook()
{
    Book b;
    int id;
    bool found = false;

    fstream file("books.dat", ios::binary | ios::in | ios::out);

    cout << "\nEnter Book ID to Issue: ";
    cin >> id;

    while (file.read((char*)&b, sizeof(b)))
    {
        if (b.bookID == id)
        {
            if (b.issued)
            {
                cout << "\nBook Already Issued!\n";
            }
            else
            {
                b.issued = true;

                file.seekp(-sizeof(b), ios::cur);
                file.write((char*)&b, sizeof(b));

                cout << "\nBook Issued Successfully!\n";
            }

            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "\nBook Not Found!\n";
    }

    file.close();
}

void returnBook()
{
    Book b;
    int id;
    bool found = false;

    fstream file("books.dat", ios::binary | ios::in | ios::out);

    cout << "\nEnter Book ID to Return: ";
    cin >> id;

    while (file.read((char*)&b, sizeof(b)))
    {
        if (b.bookID == id)
        {
            if (!b.issued)
            {
                cout << "\nBook Already Available!\n";
            }
            else
            {
                b.issued = false;

                file.seekp(-sizeof(b), ios::cur);
                file.write((char*)&b, sizeof(b));

                cout << "\nBook Returned Successfully!\n";
            }

            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "\nBook Not Found!\n";
    }

    file.close();
}

int main()
{
    int choice;

    do
    {
        cout << "\n\n====== LIBRARY MANAGEMENT SYSTEM ======";
        cout << "\n1. Add Book";
        cout << "\n2. Display Books";
        cout << "\n3. Search Book";
        cout << "\n4. Issue Book";
        cout << "\n5. Return Book";
        cout << "\n6. Exit";

        cout << "\n\nEnter Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                addBook();
                break;

            case 2:
                displayBooks();
                break;

            case 3:
                searchBook();
                break;

            case 4:
                issueBook();
                break;

            case 5:
                returnBook();
                break;

            case 6:
                cout << "\nThank You!\n";
                break;

            default:
                cout << "\nInvalid Choice!\n";
        }

    } while(choice != 6);

    return 0;
}