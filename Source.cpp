﻿// wat a shame..... (i don't care)
// am i a bad engineer ? (go fkk uself :) )


#pragma warning( disable : 4715 )
#pragma warning( disable : 28182 )
#pragma warning( disable : 4244 )
#pragma warning( disable : 6308 )
#pragma warning( disable : 6011 )


#include <iostream>
#include <string>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <cstdlib>


#define DEBUG_LIMIT 9


using namespace std;


struct Node {
	int element;		// current value of the element in the node
	Node* lower_node;		// pointer to the lower element
};


void push(int value, Node** head_node);
int pop(Node** head_node);
int view(Node* head_node);
long long int number_input(int limit);
int linked_array_length(Node* head_node);
int individual_task(Node* head_node);


int main()
{
	srand(time(0));

	short amount_choice;	// Amount of elements in the stack
	short menu_choice;			
	Node* SP = NULL;	// First node of the linked list

	cout << "Welcome to the stack program. Here you" 
		<< "\ncan do some stuff with it. The stack is" 
		<< "\nimplemented through linked lists.";

	cout << "\n\nPress ENTER to continue...";
	cin.get();

	for (;;)		// Main menu loop
	{
		system("CLS");

		cout << "Stack control panel: "
			<< "\n\n1. Push" 
			<< "\n2. Pop" 
			<< "\n3. View" 
			<< "\n4. Individual Task"
			<< "\nELSE. Exit" 
			<< "\n\nType here: ";

		menu_choice = number_input(DEBUG_LIMIT);

		switch (menu_choice)
		{
		case 1:		// push
		{
			system("CLS");

			cout << "Choose the way how you would"
				<< "\nlike to fill the stack: "
				<< "\n\n0. Fill with random numbers."
				<< "\nELSE. Fill by hand."
				<< "\n\nType here: ";

			short push_type_choice = number_input(DEBUG_LIMIT);

			system("CLS");

			cout << "Choose how many numbers you"
				<< "\nwould to see in the stack."
				<< "\n\nType here: ";

			while ((amount_choice = number_input(DEBUG_LIMIT)) < 1)
			{
				system("CLS");
				cout << "Incorrect value. Try again: ";
			}

			if (push_type_choice == 0) {
				int low_boundary;
				int top_boundary;
				int random_number;

				system("CLS");

				cout << "Set the top boundary for the random algorithm: ";
				top_boundary = number_input(DEBUG_LIMIT);
				cout << "\nSet the low boundary for the random algorith: ";

				// Boundaries could not be the same
				while ((low_boundary = number_input(DEBUG_LIMIT)) >= top_boundary)
				{
					system("CLS");
					cout << "Low boundary could not be the same as top boundary or greater. Try again: ";
				}
				
				system("CLS");
				cout << "Top boundary: " << top_boundary;
				cout << "\nLow boundary: " << low_boundary;
				cout << "\n\nGenerating random numbers...\n";

				for (int i = 0; i < amount_choice; i++)
				{
					random_number = rand() % (top_boundary - low_boundary + 1) + low_boundary;
					push(random_number, &SP);
					cout << endl << random_number << " was successfully pushed onto the stack.";
				}
				cout << "\n\nStack filling was successful.\n";
			}
			else {
				cout << endl;
				for (int i = 0; i < amount_choice; i++)
				{
					cout << "\nEnter a number: ";
					int user_input = number_input(DEBUG_LIMIT);
					push(user_input, &SP);
					cout << endl << user_input << " was successfully pushed onto the stack.";
				}
			}

			cout << "\n\nPress ENTER to continue...";
			cin.get();
			break;
		}
		case 2:
		{
			int popped_element = pop(&SP);
			
			system("CLS");

			if (popped_element == NULL) {
				cout << "Pop error. Stack underflow.";
			} else {
				cout << "Element " << popped_element << " was successfully popped from the stack.";
			}

			cout << "\n\nPress ENTER to continue...";
			cin.get();
			break;
		}
		case 3:
			system("CLS");
			if (view(SP) == NULL) {
				cout << "Error with view. Stack is empty!";
			}

			cout << "\n\nPress ENTER to continue...";
			cin.get();
			break;
		case 4:
			system("CLS");

			if (individual_task(SP) == NULL) {
				cout << "Stack is empty.";
			}

			cout << "\n\nPress ENTER to continue...";
			cin.get();
			break;
		default:
			system("CLS");
			cout << "See you!\n";
			return 0;
		}
	}
}


int individual_task(Node* head_node)
{
	Node* negative_stack = NULL;
	Node* positive_stack = NULL;

	int elements_amount = linked_array_length(head_node);
	int max_sub_amount;		// the biggest stack after division
	int positive_amount;
	int negative_amount;

	if (head_node == NULL) { return NULL; }

	cout << "\n\n\n+---------+-----------------------+\t\t+---------+-----------------------+"
		<< "\n|    #    |    NEGATIVE STACK     |\t\t|    #    |     POSITIVE STACK    |"
		<< "\n+---------+-----------------------+\t\t+---------+-----------------------+";
	
	// 0 should not be in the stack
	while (head_node != NULL)
	{
		if (head_node->element < 0) {
			push(head_node->element, &negative_stack);
		} else if (head_node->element > 0) {
			push(head_node->element, &positive_stack);
		}
		head_node = head_node->lower_node;
	}

	negative_amount = linked_array_length(negative_stack);
	positive_amount = linked_array_length(positive_stack);
	max_sub_amount = positive_amount > negative_amount ? positive_amount : negative_amount;

	for (int i = max_sub_amount; i > 0; i--)
	{
		if (i > positive_amount) {
			printf("\n| %7d |      %6d           |\t\t|         |                       |", i, negative_stack->element);
			negative_stack = negative_stack->lower_node;
		} else if (i > negative_amount) {
			printf("\n|         |                       |\t\t| %7d |      %6d           |", i, positive_stack->element);
			positive_stack = positive_stack->lower_node;
		} else {
			printf("\n| %7d |      %6d           |\t\t| %7d |      %6.d           |", i, negative_stack->element, i, positive_stack->element);
			negative_stack = negative_stack->lower_node;
			positive_stack = positive_stack->lower_node;
		}
	}

	cout << "\n+---------+-----------------------+\t\t+---------+-----------------------+\n\n\n";
}


int linked_array_length(Node* head_node)
{
	if (head_node == NULL) { return 0; }

	int length = 0;

	while (head_node != NULL) {
		head_node = head_node->lower_node;
		length++;
	}
	return length;
}


int view(Node* head_node)
{
	if (head_node == NULL) { return NULL; }

	cout << endl << endl;

	cout << "\n+---------+-----------------------+"
		<< "\n|    #    |         STACK         |"
		<< "\n+---------+-----------------------+";
	
	int elements_amount = linked_array_length(head_node);

	while (head_node != NULL) {
		if (head_node->element == 0) {
			printf("\n| %7d |           0           |", elements_amount--);
		} else {
			printf("\n| %7d |      %6d           |", elements_amount--, head_node->element);
		}
		head_node = head_node->lower_node; 
	}
	cout << "\n+---------+-----------------------+\n";

	cout << endl << endl;
}


void push(int value, Node** head_node)
{
	Node *new_node = new Node;
	new_node->element = value;
	new_node->lower_node = *head_node;
	*head_node = new_node;
}


int pop(Node** head_node)
{
	int element_to_return; 

	if (*head_node != NULL) { 
		element_to_return = (*head_node)->element;
		Node* temp_node = (*head_node)->lower_node;
		delete *head_node; 
		*head_node = temp_node;
		return element_to_return;
	} else {
		return NULL;
	}
}


long long int number_input(int limit)
{
	// Limit set the number of digits in the number

	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// I have no idea why is that happening 
	// 2.147.483.647 = 2147483647
	// 2.147.483.648 = -2147483648
	// -2.147.483.648 = -2147483648
	// -2.147.483.649 = -2147483647

	char c;				// current entered symbol 	
	int length = 0;		// length of number (digit capacity, minus included), but index for digits is length - 1
	char* number_array_pointer;
	long long int number_array_integer = 0;
	int index;		// index for converting string to integer


	if ((number_array_pointer = (char*)malloc(sizeof(char) * length)) == NULL) {
		cout << "Fatal: failed to allocate " << sizeof(char) * length << " bytes.\n";
		abort();
	}

	for (;;) {
		c = _getch();
		if (c == 13 && length != 0) {		// Enter breaks down the loop
			if (number_array_pointer[0] == '-' && length < 2) {
				continue;
			} else {
				break;
			}
		} else if (c == '\b' && length != 0) {	// Backspace
			cout << "\b \b";
			length--;
			if (length == 0)
			{
				if ((number_array_pointer = (char*)malloc(sizeof(char) * length)) == NULL) {
					cout << "Fatal: failed to allocate " << sizeof(char) * length << " bytes.\n";
					abort();
				}
			}		// We cannot realloc 0 bytes
			else if ((number_array_pointer = (char*)realloc(number_array_pointer, sizeof(char) * length)) == NULL) {
				cout << "Fatal: failed to reallocate " << sizeof(char) * length << " bytes.\n";
				abort();
			}
		} else if (c == 45 && length == 0) {		// Minus for negative number
			length++;
			if ((number_array_pointer = (char*)realloc(number_array_pointer, sizeof(char) * length)) == NULL) {
				cout << "Fatal: failed to reallocate " << sizeof(char) * length << " bytes.\n";
				abort();
			}
			number_array_pointer[length - 1] = c;
			cout << c;
		} else if (c > 47 && c < 58 && length < limit) {		//	Allow to enter only digits
			length++;
			if ((number_array_pointer = (char*)realloc(number_array_pointer, sizeof(char) * length)) == NULL) {
				cout << "Fatal: failed to reallocate " << sizeof(char) * length << " bytes.\n";
				abort();
			}
			number_array_pointer[length - 1] = c;
			cout << c;
		} else {
			continue;
		}
	} 
	
	if (number_array_pointer[0] == '-') {
		index = 1;
	} else {
		index = 0;
	}

	for (index; index < length; index++)
	{	
		number_array_integer *= 10;
		number_array_integer += (long long int)number_array_pointer[index] - 48;
	}

	if (number_array_pointer[0] == '-') { 
		number_array_integer *= -1; 
	}

	// Return without free 'cause the calling code must take responsibility for freeing it (and the function must not free it)
	return number_array_integer;
}

