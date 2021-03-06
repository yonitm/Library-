#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BOOK_NUM 4
#define NAME_LENGTH 200
#define AVAILABLE 10
#define NOT_AVAILABLE 20

typedef struct book {
	char name[NAME_LENGTH];
	char author[NAME_LENGTH];
	int available;
	int times_borrowed;
} Book;

int check_where_is_empty(Book **books);
void  free_memoery(Book **books);


int init_book(Book **books)
{
	int i;
	for (i = 0; i < BOOK_NUM; i++) {
		if (books[i]->name == 0) {
			books[i] = (Book**)calloc(1, sizeof(Book));
			if (books[i] == NULL) {
				free_memoery(books);
				printf("Memory allocation failed!\n");
				exit(1);
			}

			break;
		}

	}
	return i;
}


int check_book_exist(char *book_name, Book **books) {
	int i;

	for (i = 0; i < BOOK_NUM; i++) {
		if (books[i]->name != NULL) {

			if (!strcmp(books[i]->name, book_name))
				return i;
		}
	}

	return -1;

}


/*Inputs: pointer to array of pinters-books
Return parameter:None
Function functionality: the function adds a book to books or returns the book.
The function checkes if the book allready exists.
If the book exists-the book will be returned to the system.
If not-the function checkes if it didn't reached its maximum books number. add the book only if hasnwt reached.*/


void add_or_return_book(Book **books) {
	char book_name[NAME_LENGTH], book_author[NAME_LENGTH];
	int available, times_borrowed, index;
	const char *books_name = "Please enter book name: ";
	const char *authors_name = "Please enter author name: ";
	const char *book_exists = "This book is already in the library :)";
	const char *return_book = "Thank you for returning the book!";
	const char *no_space = "Can't add more books, not enough space!";

	printf("%s", books_name);
	scanf("\n%[^\n]s", book_name);

	index = check_book_exist(book_name, books);

	if (index != -1)
	{
		if (books[index]->times_borrowed > 0) {
			printf("%s", return_book);
			books[index]->available = AVAILABLE;
		}
		else
			printf("%s", book_exists);
	}


	else
	{
		if (books[BOOK_NUM - 1] != NULL) {

			printf("%s", no_space);
			return;
		}
		else {
			printf("%s", authors_name);
			scanf("\n%[^\n]s", book_author);

			index = init_book(books);
			strcpy(books[index]->name, book_name);
			strcpy(books[index]->author, book_author);
			books[index]->available = AVAILABLE;
			printf("The book %s was successfully added!", books[index]->name);

		}
	}


}


/*Inputs: pointer to array of pinters-books
Return parameter:None
Function functionality: the function allows to borrow the book only if it has been added.*/


void take_a_book(Book **books) {
	char book_name[NAME_LENGTH];
	int index;
	const char *you_borrow_book = "Enjoy the book!";//?????????? ???? ?????????? ?????? ??????
	const char *allready_borrowed = "I am sorry someone was quicker than you :(";
	const char *not_in_library = "I am sorry we don't have this book";
	const char *books_name = "Please enter book name: ";

	printf("%s", books_name);
	scanf("\n%[^\n]s", book_name);
	index = check_book_exist(book_name, books);

	if (index != -1) {
		if (books[index]->available == NOT_AVAILABLE)
			printf("%s", allready_borrowed);
		else
			printf("%s", you_borrow_book);
		books[index]->available = NOT_AVAILABLE;
		books[index]->times_borrowed++;
	}

	else {
		printf("%s", not_in_library);


	}

}
int check_where_is_empty(Book **books) {
	int i;
	for (i = 0; i < BOOK_NUM; i++) {
		if (books[i] == NULL)
			return i;
	}
}


/*Inputs: pointer to array of pinters-books
Return parameter:None
Function functionality: the function rearrangements the books by field "times_borrowed".*/


void sort_by_times_borrowed(Book **books) {
	int i, j, empty, max = 0;
	Book *temp;
	empty = check_where_is_empty(books);
	for (i = 0; i < empty - 1; i++)
	{
		for (j = i + 1; j < empty; j++)
		{
			if ((books[j]->times_borrowed) >= (books[max]->times_borrowed))
				max = j;
		}
		if (max != i) {
			temp = books[i];
			books[i] = books[max];
			books[max] = temp;

		}
	}
}


/*Inputs: pointer to array of pinters-books
Return parameter:None
Function functionality: the function prints book's names and authors
by descending order of fielsd"times_borrowed" .*/


void print_books(Book **books) {

	int i, empty;
	const char * print_all_books = "Books available";
	const char * print_books = "-------------------------------------";
	const char * print_book_author = "Author: ";
	const char * print_book_name = "Name: ";

	printf("\n%s", print_all_books);
	printf("\n%s", print_books);
	sort_by_times_borrowed(books);
	empty = check_where_is_empty(books);
	for (i = 0; i < empty; i++) {
		if (books[i]->available == AVAILABLE) {
			printf("\n%s%s", print_book_name, books[i]->name);
			printf("\n%s%s", print_book_author, books[i]->author);
			printf("\n-------------------------------------");
		}
	}

}
void  free_memoery(Book **books) {
	int i, empty;
	empty = check_where_is_empty(books);
	if (empty == 0)
		return;

	else {
		for (i = 0; i < empty; i++)
			free(books[i]);
	}
}
void exit_library(Book **books) {

	const char * exitProgram = "\nleaving so soon?";
	printf("%s", exitProgram);
	free_memoery(books);

}

/*Inputs:pointer to array of pinters-books
Return parameter:None
Function functionality: this function is the menu of the system, the user chooses the option that he would like to
conduct in the store and the function calls the suitable function. if the user chooses option 4 the menu function wont
appear again*/


void menu(Book **books)
{
	int option;
	const char * main_interface = "-------------------------------------\n"\
		"Welcome to the library\n"\
		"-------------------------------------\n"\
		"Library menu:\n"\
		"1. Add a book/Return a book\n"\
		"2. Take a book\n"\
		"3. Print books by times borrowed from the library\n"\
		"4. Quit\n"\
		"Please choose the desired option [1-4]: ";


	do
	{
		printf("\n%s", main_interface);
		scanf("%d", &option);

		switch (option)
		{
		case 1:
		{
			add_or_return_book(books);
			break;
		}
		case 2:
		{
			take_a_book(books);
			break;
		}
		case 3:
		{
			print_books(books);
			break;
		}
		case 4:
		{
			exit_library(books);
			break;
		}

		}
	} while (option != 4);
}

main() {

	Book *books[BOOK_NUM] = { 0 };
	menu(books);
	return 0;
}
