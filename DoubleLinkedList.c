#define _CRT_SECURE_NO_WARNINGS

#include "Structs.h"
#include "DoubleLinkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main()
{
	WineBottle* head;
	WineBottle* tail;

	head = NULL;
	tail = NULL;

	Menu(&head, &tail);
}

void Menu(WineBottle** head, WineBottle** tail)
{
	int option;

	option = 1;

	while (option != 0)
	{
		printf("****WELCOME TO THE PHARMACY'S WINE BOTTLE'S MANAGER***** \n");
		printf("1.Add wine bottle\n");
		printf("2.Update wine bottle\n");
		printf("3.Remove wine bottle\n");
		printf("4.Report ascending by wine bottle code\n");
		printf("5.Report descending by wine bottle code\n");
		printf("6.Stock average\n");
		printf("0.Close\n");
		scanf(" %d", &option);

		switch (option)
		{
			case 1:
				ClrScr();

				Insert(head, tail);
				break;

			case 2:
				Update(head);
				break;

			case 3:
				ClrScr();

				Remove(head, tail);
				break;

			case 4:
				ClrScr();

				GenerateReportAscending(head);
				break;

			case 5:
				ClrScr();

				GenerateReportDescending(tail);
				break;

			case 6:
				ClrScr();

				ComputeStockAverage(head, tail);
				break;

			case 0:
				Exit();
				break;
		}
	}
}

int Count(WineBottle** head)
{
	WineBottle* currentWineBottle;	
	int count;

	//initializing variables
	count = 0;

	currentWineBottle = *head;

	while (currentWineBottle != NULL)
	{
		//counts the elements on the list
		count++;

		//moves on to the next wine bottle
		currentWineBottle = currentWineBottle->next;
	}

	//returns the number of elements counted
	return count;
}

int GenerateCode(WineBottle** head, char* name, int x)
{
	WineBottle* currentWineBottle;
	int y, nameLength;

	currentWineBottle = *head;

	//the id is the same as the number of elements on the list
	y = Count(head);
	nameLength = strlen(name);
	y += nameLength;

	while (currentWineBottle != NULL && currentWineBottle->code != y)
		currentWineBottle = currentWineBottle->next;

	if (currentWineBottle == NULL)
		return y;

	if (currentWineBottle->code == y)
		y += x;

	return y;
}

WineBottle* CreateWineBottle()
{
	//variables
	WineBottle* newWineBottle;
	int code;
	char name[60 + 1];
	int stockQuantity;

	//alocating memory
	newWineBottle = (WineBottle*)malloc(sizeof(WineBottle));

	//filling in the fields
	printf("\nInsert the wine bottle name:\n");
	scanf("%s", name);

	printf("\nInsert the wine bottle's stock quantity:\n");
	scanf("%d", &stockQuantity);

	strcpy(newWineBottle->name, name);
	newWineBottle->inStoreStockQuantity = stockQuantity;

	//returning the user input wineBottle
	return newWineBottle;
}

void ShowList(WineBottle** head)
{
	WineBottle* currentWineBottle;

	currentWineBottle = *head;

	printf("Which wine bottle do you wish to change?");

	//printing all the meds
	while (currentWineBottle != NULL)
	{
		printf("\n[%d] %s | Stock: %d\n", currentWineBottle->code, currentWineBottle->name, currentWineBottle->inStoreStockQuantity);

		currentWineBottle = currentWineBottle->next;
	}
}

void Insert(WineBottle** head, WineBottle** tail)
{
	//variables
	WineBottle* newWineBottle;
	WineBottle* currentWineBottle;
	int code;

	//new wine bottle to be inserted
	newWineBottle = CreateWineBottle();
	code = GenerateCode(head, newWineBottle->name, newWineBottle->inStoreStockQuantity);
	newWineBottle->code;

	if (*head == NULL)
	{
		//first element has no previous and no next
		newWineBottle->next = NULL;
		newWineBottle->previous = NULL;

		//if this is the first element then the tail and the head are the same
		*head = newWineBottle;
		*tail = newWineBottle;
	}

	//if its not the first element
	else
	{
		currentWineBottle = *head;

		while (currentWineBottle->next != NULL && newWineBottle->code > currentWineBottle->code)
			currentWineBottle = currentWineBottle->next;

		//if the previous wine bottle is null and the wine bottle input code is higher than the currentwine bottle
		if (currentWineBottle->previous == NULL && newWineBottle->code <= currentWineBottle->code)
		{
			//the next wine bottle is the currentwine bottle
			newWineBottle->next = currentWineBottle;

			//there is no previous
			newWineBottle->previous = NULL;

			//the empty wine bottle spot is now the new wine bottle
			currentWineBottle->previous = newWineBottle;

			//inserts in head the new wine bottle
			*head = newWineBottle;
		}
		else if (currentWineBottle->previous != NULL && newWineBottle->code <= currentWineBottle->code)
		{
			//next wine bottle is the head
			newWineBottle->next = currentWineBottle;

			//previous wine bottle is the same as the previest one 
			newWineBottle->previous = currentWineBottle->previous;

			//current wine bottle is the new wine bottle
			currentWineBottle->previous->next = newWineBottle;

			//inserts on the middle of the list
			currentWineBottle->previous = newWineBottle;
		}
		else
		{
			//previous wine bottle is the current wine bottle
			newWineBottle->previous = currentWineBottle;

			//next is null because it's the last element
			newWineBottle->next = NULL;

			//current wine bottle next is the wine bottle created
			currentWineBottle->next = newWineBottle;

			//inserts on the tail
			*tail = newWineBottle;
		}
	}

	WaitForKey();

	ClrScr();

	printf("\nWine Bottle sucessfully added!\n");
	printf("\n[%d] %s [STOCK] %d\n", newWineBottle->code, newWineBottle->name, newWineBottle->inStoreStockQuantity);

	WaitForKey();

	ClrScr();
}

void Update(WineBottle** head)
{
	//variables	
	WineBottle* currentWineBottle;
	int newStock, option;
	char name[50 + 1];
	char key;

	currentWineBottle = *head;

	ClrScr();

	ShowList(head);

	scanf("%d", &option);

	//while the there are elements on the list
	while (currentWineBottle != NULL)
	{
		ClrScr();

		//checks if the user option is the same as the id on the current med
		if (currentWineBottle->code == option)
		{
			printf("\n[%d] %s | Stock: %d\n", currentWineBottle->code, currentWineBottle->name, currentWineBottle->inStoreStockQuantity);
			printf("\nChange the name or stock or both?(N/S/B)\n");
			scanf(" %c", &key);

			key = toupper(key);

			switch (key)
			{
				case 'N':
					ClrScr();

					//updates the new name
					printf("\nEnter the new name:\n");
					scanf("%s", name);

					strcpy(currentWineBottle->name, name);

					printf("\nSuccessfully updated to %s\n", currentWineBottle->name);

					WaitForKey();

					ClrScr();
					break;

				case 'S':
					//updates the stock
					printf("\nEnter the updated stock:\n");
					scanf("%d", &newStock);

					currentWineBottle->inStoreStockQuantity = newStock;

					printf("\nSuccessfully updated to %d\n", currentWineBottle->inStoreStockQuantity);

					WaitForKey();

					ClrScr();
					break;

				case 'B':
					//allows to update both
					printf("\nEnter the new name:\n");
					scanf("%s", name);

					strcpy(currentWineBottle->name, name);

					printf("\nEnter the updated stock:\n");
					scanf("%d", &newStock);

					currentWineBottle->inStoreStockQuantity = newStock;

					printf("\nSuccessfully updated the %s the stock to %d\n", currentWineBottle->name, currentWineBottle->inStoreStockQuantity);

					WaitForKey();

					ClrScr();
					break;
			}
		}
		//if the condition is not met, it moves on to the next med
		currentWineBottle = currentWineBottle->next;
	}

}

//Removes the winebottle from the list
void Remove(WineBottle** head, WineBottle** tail)
{
	WineBottle* currentWineBottle;
	int currentCode, option;

	currentWineBottle = *head;

	ShowList(head);

	scanf("%d", &option);

	currentWineBottle = *head;
	currentCode = option;

	//when the user option is found it leaves the while
	while (currentWineBottle != NULL && currentWineBottle->code != currentCode)
		currentWineBottle = currentWineBottle->next;

	if (currentWineBottle == NULL)
	{
		printf("\nNot found\n");
		return;
	}

	if (currentWineBottle->previous == NULL && currentWineBottle->next == NULL)
	{
		*head = NULL;
		*tail = NULL;
	}

	//if the previous is null than its the head of the list(first element)
	else if (currentWineBottle->previous == NULL && currentWineBottle->next != NULL)
	{
		//current med is null
		currentWineBottle->next->previous = NULL;

		//head is now the next element
		*head = currentWineBottle->next;
	}

	//if the next of the current med is NULL than its the tail of the list (last element)
	else if (currentWineBottle->previous != NULL && currentWineBottle->next == NULL)
	{
		//current med is null
		currentWineBottle->previous->next = NULL;

		//tail is now the previous element to the current med (deletes the current)
		*tail = currentWineBottle->previous;
	}

	//in case its not the first or last element(its on the middle)
	else
	{
		//current med is passed to the next
		currentWineBottle->previous->next = currentWineBottle->next;

		//current med is passed to the previous
		currentWineBottle->next->previous = currentWineBottle->previous;
	}

	//releases the current med variable
	free(currentWineBottle);

	printf("\nSucccessfully removed the element!\n");

	WaitForKey();

	ClrScr();
}

void GenerateReportAscending(WineBottle** head)
{
	WineBottle* currentWineBottle;

	currentWineBottle = *head;

	printf("\nSort by - Ascending\n");

	//since the list is ordered it just prints it out normally from the head
	while (currentWineBottle != NULL)
	{
		printf("\n[%d] %s Stock:%d\n", currentWineBottle->code, currentWineBottle->name, currentWineBottle->inStoreStockQuantity);

		currentWineBottle = currentWineBottle->next;
	}

	WaitForKey();

	ClrScr();
}

void GenerateReportDescending(WineBottle** tail)
{
	WineBottle* currentWineBottle;

	currentWineBottle = *tail;

	printf("\nSort by - Descending\n");

	//since the list is ordered, if its called by the tail then it prints out descending
	while (currentWineBottle != NULL)
	{
		printf("\n[%d] %s Stock: %d \n", currentWineBottle->code, currentWineBottle->name, currentWineBottle->inStoreStockQuantity);

		currentWineBottle = currentWineBottle->previous;
	}

	WaitForKey();

	ClrScr();
}

void ComputeStockAverage(WineBottle** head)
{
	//variables
	WineBottle* currentWineBottle;
	int count = 0;
	float stockAverage, stockSum;

	//initializing variables
	currentWineBottle = *head;

	stockAverage = 0;
	stockSum = 0;

	//checks if the list is empty
	if (currentWineBottle == NULL)
	{
		printf("The list is empty");
		return;
	}

	//while there are meds in the list
	while (currentWineBottle != NULL)
	{
		printf("Stock: %d", currentWineBottle->inStoreStockQuantity);

		//adds the stock to the variable sum
		stockSum += currentWineBottle->inStoreStockQuantity;

		//counts the amount of bottles on the list
		count++;

		//goes to the next bottle on the list
		currentWineBottle = currentWineBottle->next;
	}

	//calculates the average
	stockAverage = (float)stockSum / (float)count;

	printf("\nMedication average:\n%0.2f\n", stockAverage);

	WaitForKey();

	ClrScr();
}

void ClrScr()
{
	system("cls");
}

void WaitForKey()
{
	system("pause");
}

void Exit()
{
	system("Exit");
}