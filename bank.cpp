#include <iostream>
#include <vector>
#include <string>
#include <limits>
 
using namespace std;

class Book
{
private:
	string title;
	string author;
	string isbn;
	bool available;

public:
	Book(string t, string a, string i) : title(t), author(a), isbn(i), available(true) {}

	// Getters
	string getTitle() const { return title; }
	string getAuthor() const { return author; }
	string getISBN() const { return isbn; }
	bool isAvailable() const { return available; }

	// Setters
	void setAvailable(bool status) { available = status; }
};

class Library
{
private:
	vector<Book> books;

public:
	void addBook()
	{
		string title, author, isbn;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Enter book title: ";
		getline(cin, title);
		cout << "Enter author name: ";
		getline(cin, author);
		cout << "Enter ISBN: ";
		getline(cin, isbn);

		books.emplace_back(title, author, isbn);
		cout << "Book added successfully!\n";
	}

	void displayAllBooks() const
	{
		if (books.empty())
		{
			cout << "No books in the library.\n";
			return;
		}

		cout << "\nLibrary Catalog:\n";
		for (const auto &book : books)
		{
			cout << "Title: " << book.getTitle()
				<< "\nAuthor: " << book.getAuthor()
				<< "\nISBN: " << book.getISBN()
				<< "\nStatus: " << (book.isAvailable() ? "Available" : "Borrowed")
				<< "\n------------------------\n";
		}
	}

	Book *findBook(const string &isbn)
	{
		for (auto &book : books)
		{
			if (book.getISBN() == isbn)
			{
				return &book;
			}
		}
		return nullptr;
	}

	void borrowBook()
	{
		string isbn;
		cout << "Enter ISBN of the book to borrow: ";
		cin >> isbn;

		Book *book = findBook(isbn);
		if (book)
		{
			if (book->isAvailable())
			{
				book->setAvailable(false);
				cout << "Book borrowed successfully!\n";
			}
			else
			{
				cout << "Book is already borrowed.\n";
			}
		}
		else
		{
			cout << "Book not found.\n";
		}
	}

	void returnBook()
	{
		string isbn;
		cout << "Enter ISBN of the book to return: ";
		cin >> isbn;

		Book *book = findBook(isbn);
		if (book)
		{
			if (!book->isAvailable())
			{
				book->setAvailable(true);
				cout << "Book returned successfully!\n";
			}
			else
			{
				cout << "Book was not borrowed.\n";
			}
		}
		else
		{
			cout << "Book not found.\n";
		}
	}
};

void displayMenu()
{
	cout << "\nLibrary Management System\n";
	cout << "1. Add Book\n";
	cout << "2. Display All Books\n";
	cout << "3. Borrow Book\n";
	cout << "4. Return Book\n";
	cout << "5. Exit\n";
	cout << "Enter your choice: ";
}

int main()
{
	Library library;
	int choice;

	do
	{
		displayMenu();
		cin >> choice;

		switch (choice)
		{
		case 1:
			library.addBook();
			break;
		case 2:
			library.displayAllBooks();
			break;
		case 3:
			library.borrowBook();
			break;
		case 4:
			library.returnBook();
			break;
		case 5:
			cout << "Exiting system...\n";
			break;
		default:
			cout << "Invalid choice. Please try again.\n";
		}
	} while (choice != 5);

	return 0;
}
