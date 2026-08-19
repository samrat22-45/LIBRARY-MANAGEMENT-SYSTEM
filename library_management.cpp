#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// =====================================================
// BOOK CLASS
// =====================================================
class Book
{
public:
    int bookID;
    string title;
    string author;
    bool issued;

    Book()
    {
        bookID = 0;
        title = "";
        author = "";
        issued = false;
    }

    Book(int id, string t, string a)
    {
        bookID = id;
        title = t;
        author = a;
        issued = false;
    }
};


// =====================================================
// MEMBER CLASS
// =====================================================
class Member
{
public:
    int memberID;
    string name;

    Member()
    {
        memberID = 0;
        name = "";
    }

    Member(int id, string n)
    {
        memberID = id;
        name = n;
    }
};


// =====================================================
// LIBRARY CLASS
// =====================================================
class Library
{
private:
    Book books[100];
    Member members[100];

    int bookCount;
    int memberCount;

public:

    // Constructor
    Library()
    {
        bookCount = 0;
        memberCount = 0;

        loadBooks();
        loadMembers();
    }


    // =================================================
    // ADD BOOK
    // =================================================
    void addBook()
    {
        if (bookCount >= 100)
        {
            cout << "\nLibrary is full. Cannot add more books.\n";
            return;
        }

        int id;
        string title;
        string author;

        cout << "\nEnter Book ID: ";
        cin >> id;

        // Check duplicate Book ID
        for (int i = 0; i < bookCount; i++)
        {
            if (books[i].bookID == id)
            {
                cout << "\nBook ID already exists!\n";
                return;
            }
        }

        cin.ignore();

        cout << "Enter Book Title: ";
        getline(cin, title);

        cout << "Enter Author Name: ";
        getline(cin, author);

        books[bookCount] = Book(id, title, author);

        bookCount++;

        saveBooks();

        cout << "\nBook added successfully!\n";
    }


    // =================================================
    // DISPLAY ALL BOOKS
    // =================================================
    void displayBooks()
    {
        if (bookCount == 0)
        {
            cout << "\nNo books available.\n";
            return;
        }

        cout << "\n";
        cout << "============================================================\n";
        cout << "                    ALL BOOKS\n";
        cout << "============================================================\n";

        cout << left
             << setw(10) << "ID"
             << setw(30) << "TITLE"
             << setw(25) << "AUTHOR"
             << setw(15) << "STATUS"
             << endl;

        cout << "------------------------------------------------------------\n";

        for (int i = 0; i < bookCount; i++)
        {
            cout << left
                 << setw(10) << books[i].bookID
                 << setw(30) << books[i].title
                 << setw(25) << books[i].author;

            if (books[i].issued)
            {
                cout << setw(15) << "Issued";
            }
            else
            {
                cout << setw(15) << "Available";
            }

            cout << endl;
        }

        cout << "============================================================\n";
    }


    // =================================================
    // ADD MEMBER
    // =================================================
    void addMember()
    {
        if (memberCount >= 100)
        {
            cout << "\nMember limit reached.\n";
            return;
        }

        int id;
        string name;

        cout << "\nEnter Member ID: ";
        cin >> id;

        // Check duplicate Member ID
        for (int i = 0; i < memberCount; i++)
        {
            if (members[i].memberID == id)
            {
                cout << "\nMember ID already exists!\n";
                return;
            }
        }

        cin.ignore();

        cout << "Enter Member Name: ";
        getline(cin, name);

        members[memberCount] = Member(id, name);

        memberCount++;

        saveMembers();

        cout << "\nMember added successfully!\n";
    }


    // =================================================
    // DISPLAY ALL MEMBERS
    // =================================================
    void displayMembers()
    {
        if (memberCount == 0)
        {
            cout << "\nNo members registered.\n";
            return;
        }

        cout << "\n";
        cout << "=============================================\n";
        cout << "                 ALL MEMBERS\n";
        cout << "=============================================\n";

        cout << left
             << setw(15) << "MEMBER ID"
             << setw(30) << "MEMBER NAME"
             << endl;

        cout << "---------------------------------------------\n";

        for (int i = 0; i < memberCount; i++)
        {
            cout << left
                 << setw(15) << members[i].memberID
                 << setw(30) << members[i].name
                 << endl;
        }

        cout << "=============================================\n";
    }


    // =================================================
    // ISSUE BOOK
    // =================================================
    void issueBook()
    {
        if (bookCount == 0)
        {
            cout << "\nNo books available.\n";
            return;
        }

        int bookID;
        int memberID;

        cout << "\nEnter Book ID: ";
        cin >> bookID;

        int bookIndex = -1;

        // Find book
        for (int i = 0; i < bookCount; i++)
        {
            if (books[i].bookID == bookID)
            {
                bookIndex = i;
                break;
            }
        }

        if (bookIndex == -1)
        {
            cout << "\nBook not found!\n";
            return;
        }

        // Check whether book is already issued
        if (books[bookIndex].issued)
        {
            cout << "\nThis book is already issued!\n";
            return;
        }

        cout << "Enter Member ID: ";
        cin >> memberID;

        bool memberFound = false;

        // Find member
        for (int i = 0; i < memberCount; i++)
        {
            if (members[i].memberID == memberID)
            {
                memberFound = true;
                break;
            }
        }

        if (!memberFound)
        {
            cout << "\nMember not found!\n";
            return;
        }

        books[bookIndex].issued = true;

        saveBooks();

        cout << "\nBook issued successfully!\n";
        cout << "Book: " << books[bookIndex].title << endl;
    }


    // =================================================
    // RETURN BOOK
    // =================================================
    void returnBook()
    {
        int bookID;

        cout << "\nEnter Book ID: ";
        cin >> bookID;

        for (int i = 0; i < bookCount; i++)
        {
            if (books[i].bookID == bookID)
            {
                if (!books[i].issued)
                {
                    cout << "\nThis book is already available.\n";
                    return;
                }

                books[i].issued = false;

                saveBooks();

                cout << "\nBook returned successfully!\n";
                cout << "Book: " << books[i].title << endl;

                return;
            }
        }

        cout << "\nBook not found!\n";
    }


    // =================================================
    // SEARCH BOOK BY TITLE
    // =================================================
    void searchByTitle()
    {
        string searchTitle;

        cin.ignore();

        cout << "\nEnter title to search: ";
        getline(cin, searchTitle);

        bool found = false;

        for (int i = 0; i < bookCount; i++)
        {
            if (books[i].title.find(searchTitle) != string::npos)
            {
                cout << "\nBook Found\n";
                cout << "----------------------------\n";
                cout << "Book ID : " << books[i].bookID << endl;
                cout << "Title   : " << books[i].title << endl;
                cout << "Author  : " << books[i].author << endl;

                if (books[i].issued)
                {
                    cout << "Status  : Issued\n";
                }
                else
                {
                    cout << "Status  : Available\n";
                }

                found = true;
            }
        }

        if (!found)
        {
            cout << "\nNo book found with that title.\n";
        }
    }


    // =================================================
    // SEARCH BOOK BY AUTHOR
    // =================================================
    void searchByAuthor()
    {
        string searchAuthor;

        cin.ignore();

        cout << "\nEnter author name to search: ";
        getline(cin, searchAuthor);

        bool found = false;

        for (int i = 0; i < bookCount; i++)
        {
            if (books[i].author.find(searchAuthor) != string::npos)
            {
                cout << "\nBook Found\n";
                cout << "----------------------------\n";
                cout << "Book ID : " << books[i].bookID << endl;
                cout << "Title   : " << books[i].title << endl;
                cout << "Author  : " << books[i].author << endl;

                if (books[i].issued)
                {
                    cout << "Status  : Issued\n";
                }
                else
                {
                    cout << "Status  : Available\n";
                }

                found = true;
            }
        }

        if (!found)
        {
            cout << "\nNo book found by that author.\n";
        }
    }


    // =================================================
    // SAVE BOOK DATA
    // =================================================
    void saveBooks()
    {
        ofstream file("books.txt");

        if (!file)
        {
            cout << "\nError opening books.txt\n";
            return;
        }

        for (int i = 0; i < bookCount; i++)
        {
            file << books[i].bookID << endl;
            file << books[i].title << endl;
            file << books[i].author << endl;
            file << books[i].issued << endl;
        }

        file.close();
    }


    // =================================================
    // LOAD BOOK DATA
    // =================================================
    void loadBooks()
    {
        ifstream file("books.txt");

        if (!file)
        {
            return;
        }

        while (bookCount < 100)
        {
            Book b;

            if (!(file >> b.bookID))
            {
                break;
            }

            file.ignore();

            getline(file, b.title);
            getline(file, b.author);

            file >> b.issued;

            books[bookCount] = b;

            bookCount++;
        }

        file.close();
    }


    // =================================================
    // SAVE MEMBER DATA
    // =================================================
    void saveMembers()
    {
        ofstream file("members.txt");

        if (!file)
        {
            cout << "\nError opening members.txt\n";
            return;
        }

        for (int i = 0; i < memberCount; i++)
        {
            file << members[i].memberID << endl;
            file << members[i].name << endl;
        }

        file.close();
    }


    // =================================================
    // LOAD MEMBER DATA
    // =================================================
    void loadMembers()
    {
        ifstream file("members.txt");

        if (!file)
        {
            return;
        }

        while (memberCount < 100)
        {
            Member m;

            if (!(file >> m.memberID))
            {
                break;
            }

            file.ignore();

            getline(file, m.name);

            members[memberCount] = m;

            memberCount++;
        }

        file.close();
    }
};


// =====================================================
// MAIN FUNCTION
// =====================================================
int main()
{
    Library library;

    int choice;

    do
    {
        cout << "\n\n";
        cout << "=================================================\n";
        cout << "          LIBRARY MANAGEMENT SYSTEM\n";
        cout << "=================================================\n";
        cout << "1. Add Book\n";
        cout << "2. Display All Books\n";
        cout << "3. Add Member\n";
        cout << "4. Display All Members\n";
        cout << "5. Issue Book\n";
        cout << "6. Return Book\n";
        cout << "7. Search Book by Title\n";
        cout << "8. Search Book by Author\n";
        cout << "9. Exit\n";
        cout << "=================================================\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            library.addBook();
            break;

        case 2:
            library.displayBooks();
            break;

        case 3:
            library.addMember();
            break;

        case 4:
            library.displayMembers();
            break;

        case 5:
            library.issueBook();
            break;

        case 6:
            library.returnBook();
            break;

        case 7:
            library.searchByTitle();
            break;

        case 8:
            library.searchByAuthor();
            break;

        case 9:
            cout << "\nThank you for using Library Management System!\n";
            break;

        default:
            cout << "\nInvalid choice! Please enter 1-9.\n";
        }

    } while (choice != 9);

    return 0;
}