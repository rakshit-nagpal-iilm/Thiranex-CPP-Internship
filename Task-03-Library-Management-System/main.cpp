#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

class Book
{
private:
    int bookId;
    string title;
    string author;
    bool issued;
    int issuedTo;

public:
    Book()
    {
        bookId = 0;
        issued = false;
        issuedTo = 0;
    }

    Book(int id, string bookTitle, string bookAuthor)
    {
        bookId = id;
        title = bookTitle;
        author = bookAuthor;
        issued = false;
        issuedTo = 0;
    }

    int getBookId() const
    {
        return bookId;
    }

    string getTitle() const
    {
        return title;
    }

    string getAuthor() const
    {
        return author;
    }

    bool isIssued() const
    {
        return issued;
    }

    int getIssuedTo() const
    {
        return issuedTo;
    }

    void setIssued(bool status, int memberId)
    {
        issued = status;
        issuedTo = memberId;
    }

    void display() const
    {
        cout << "\n-------------------------------\n";
        cout << "Book ID       : " << bookId << endl;
        cout << "Title         : " << title << endl;
        cout << "Author        : " << author << endl;
        cout << "Status        : " << (issued ? "Issued" : "Available") << endl;

        if (issued)
            cout << "Issued To ID  : " << issuedTo << endl;

        cout << "-------------------------------\n";
    }
};


class Member
{
private:
    int memberId;
    string name;

public:
    Member()
    {
        memberId = 0;
    }

    Member(int id, string memberName)
    {
        memberId = id;
        name = memberName;
    }

    int getMemberId() const
    {
        return memberId;
    }

    string getName() const
    {
        return name;
    }

    void display() const
    {
        cout << "\n-------------------------------\n";
        cout << "Member ID : " << memberId << endl;
        cout << "Name      : " << name << endl;
        cout << "-------------------------------\n";
    }
};


class LibrarySystem
{
private:
    string booksFile = "books.txt";
    string membersFile = "members.txt";

    bool bookExists(int id)
    {
        ifstream file(booksFile);
        string line;

        while (getline(file, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);

            string bookId;
            getline(ss, bookId, '|');

            if (stoi(bookId) == id)
                return true;
        }

        return false;
    }

    bool memberExists(int id)
    {
        ifstream file(membersFile);
        string line;

        while (getline(file, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);

            string memberId;
            getline(ss, memberId, '|');

            if (stoi(memberId) == id)
                return true;
        }

        return false;
    }

    string toLowerCase(string text)
    {
        transform(text.begin(), text.end(), text.begin(),
                  [](unsigned char c)
                  {
                      return tolower(c);
                  });

        return text;
    }


public:

    void addBook()
    {
        int id;
        string title;
        string author;

        cout << "\n===== ADD BOOK =====\n";

        cout << "Enter Book ID: ";
        cin >> id;

        if (bookExists(id))
        {
            cout << "\nBook with this ID already exists.\n";
            return;
        }

        cin.ignore();

        cout << "Enter Book Title: ";
        getline(cin, title);

        cout << "Enter Author Name: ";
        getline(cin, author);

        ofstream file(booksFile, ios::app);

        file << id << "|"
             << title << "|"
             << author << "|"
             << 0 << "|"
             << 0 << endl;

        file.close();

        cout << "\nBook added successfully.\n";
    }


    void addMember()
    {
        int id;
        string name;

        cout << "\n===== ADD MEMBER =====\n";

        cout << "Enter Member ID: ";
        cin >> id;

        if (memberExists(id))
        {
            cout << "\nMember with this ID already exists.\n";
            return;
        }

        cin.ignore();

        cout << "Enter Member Name: ";
        getline(cin, name);

        ofstream file(membersFile, ios::app);

        file << id << "|"
             << name << endl;

        file.close();

        cout << "\nMember added successfully.\n";
    }


    void displayAllBooks()
    {
        ifstream file(booksFile);

        if (!file)
        {
            cout << "\nNo books found.\n";
            return;
        }

        string line;
        bool found = false;

        cout << "\n===== ALL BOOKS =====\n";

        while (getline(file, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);

            string id;
            string title;
            string author;
            string issued;
            string issuedTo;

            getline(ss, id, '|');
            getline(ss, title, '|');
            getline(ss, author, '|');
            getline(ss, issued, '|');
            getline(ss, issuedTo);

            Book book(stoi(id), title, author);

            if (stoi(issued) == 1)
                book.setIssued(true, stoi(issuedTo));

            book.display();

            found = true;
        }

        if (!found)
            cout << "\nNo books available.\n";

        file.close();
    }


    void displayMembers()
    {
        ifstream file(membersFile);

        if (!file)
        {
            cout << "\nNo members found.\n";
            return;
        }

        string line;
        bool found = false;

        cout << "\n===== LIBRARY MEMBERS =====\n";

        while (getline(file, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);

            string id;
            string name;

            getline(ss, id, '|');
            getline(ss, name);

            Member member(stoi(id), name);

            member.display();

            found = true;
        }

        if (!found)
            cout << "\nNo members available.\n";

        file.close();
    }


    void searchBook()
    {
        cin.ignore();

        string keyword;

        cout << "\n===== SEARCH BOOK =====\n";
        cout << "Enter title or author: ";
        getline(cin, keyword);

        keyword = toLowerCase(keyword);

        ifstream file(booksFile);

        string line;
        bool found = false;

        while (getline(file, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);

            string id;
            string title;
            string author;
            string issued;
            string issuedTo;

            getline(ss, id, '|');
            getline(ss, title, '|');
            getline(ss, author, '|');
            getline(ss, issued, '|');
            getline(ss, issuedTo);

            string titleLower = toLowerCase(title);
            string authorLower = toLowerCase(author);

            if (titleLower.find(keyword) != string::npos ||
                authorLower.find(keyword) != string::npos)
            {
                Book book(stoi(id), title, author);

                if (stoi(issued) == 1)
                    book.setIssued(true, stoi(issuedTo));

                book.display();

                found = true;
            }
        }

        file.close();

        if (!found)
            cout << "\nNo matching book found.\n";
    }


    void issueBook()
    {
        int bookId;
        int memberId;

        cout << "\n===== ISSUE BOOK =====\n";

        cout << "Enter Book ID: ";
        cin >> bookId;

        if (!bookExists(bookId))
        {
            cout << "\nBook not found.\n";
            return;
        }

        cout << "Enter Member ID: ";
        cin >> memberId;

        if (!memberExists(memberId))
        {
            cout << "\nMember not found.\n";
            return;
        }

        ifstream file(booksFile);
        ofstream temp("temp-books.txt");

        string line;
        bool alreadyIssued = false;

        while (getline(file, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);

            string id;
            string title;
            string author;
            string issued;
            string issuedTo;

            getline(ss, id, '|');
            getline(ss, title, '|');
            getline(ss, author, '|');
            getline(ss, issued, '|');
            getline(ss, issuedTo);

            if (stoi(id) == bookId)
            {
                if (stoi(issued) == 1)
                {
                    alreadyIssued = true;
                    temp << line << endl;
                }
                else
                {
                    temp << id << "|"
                         << title << "|"
                         << author << "|"
                         << 1 << "|"
                         << memberId << endl;
                }
            }
            else
            {
                temp << line << endl;
            }
        }

        file.close();
        temp.close();

        remove(booksFile.c_str());
        rename("temp-books.txt", booksFile.c_str());

        if (alreadyIssued)
            cout << "\nThis book is already issued.\n";
        else
            cout << "\nBook issued successfully.\n";
    }


    void returnBook()
    {
        int bookId;

        cout << "\n===== RETURN BOOK =====\n";

        cout << "Enter Book ID: ";
        cin >> bookId;

        if (!bookExists(bookId))
        {
            cout << "\nBook not found.\n";
            return;
        }

        ifstream file(booksFile);
        ofstream temp("temp-books.txt");

        string line;
        bool wasIssued = false;

        while (getline(file, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);

            string id;
            string title;
            string author;
            string issued;
            string issuedTo;

            getline(ss, id, '|');
            getline(ss, title, '|');
            getline(ss, author, '|');
            getline(ss, issued, '|');
            getline(ss, issuedTo);

            if (stoi(id) == bookId)
            {
                if (stoi(issued) == 1)
                {
                    wasIssued = true;

                    temp << id << "|"
                         << title << "|"
                         << author << "|"
                         << 0 << "|"
                         << 0 << endl;
                }
                else
                {
                    temp << line << endl;
                }
            }
            else
            {
                temp << line << endl;
            }
        }

        file.close();
        temp.close();

        remove(booksFile.c_str());
        rename("temp-books.txt", booksFile.c_str());

        if (wasIssued)
            cout << "\nBook returned successfully.\n";
        else
            cout << "\nThis book was not issued.\n";
    }


    void menu()
    {
        int choice;

        do
        {
            cout << "\n=====================================\n";
            cout << "       LIBRARY MANAGEMENT SYSTEM\n";
            cout << "=====================================\n";

            cout << "1. Add Book\n";
            cout << "2. Add Member\n";
            cout << "3. Display All Books\n";
            cout << "4. Search Book\n";
            cout << "5. Issue Book\n";
            cout << "6. Return Book\n";
            cout << "7. Display Members\n";
            cout << "8. Exit\n";

            cout << "=====================================\n";

            cout << "Enter your choice: ";
            cin >> choice;


            switch (choice)
            {
                case 1:
                    addBook();
                    break;

                case 2:
                    addMember();
                    break;

                case 3:
                    displayAllBooks();
                    break;

                case 4:
                    searchBook();
                    break;

                case 5:
                    issueBook();
                    break;

                case 6:
                    returnBook();
                    break;

                case 7:
                    displayMembers();
                    break;

                case 8:
                    cout << "\nExiting Library Management System...\n";
                    break;

                default:
                    cout << "\nInvalid choice. Try again.\n";
            }

        } while (choice != 8);
    }
};


int main()
{
    LibrarySystem library;

    library.menu();

    return 0;
}