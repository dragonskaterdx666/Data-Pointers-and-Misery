#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Structs.h"
#include "LinkedList.h"

int main()
{
	Dog* head;
	Dog* tail;	
	bool isEmpty = true;
	int ticketNumber;

	head = NULL;
	tail = NULL;

	ticketNumber = 0;

	Menu(head, tail, isEmpty, ticketNumber);
}

void Menu(Dog* head, Dog* tail, bool isEmpty, int ticketNumber)
{
	//dogs to dequeue
	Dog n1, n2, n3, n4, firstDog;
	int currentTicket;
	int option = 1, n = 0;

	while (option != 0)
	{

		printf("****WELCOME TO THE VETS QUEUE MANAGER***** \n");
		printf("1.Enqueue\n");
		printf("2.Dequeue\n");
		printf("3.Peek\n");
		printf("4.Calculate Age Average\n");
		printf("5.Report on all dogs in queue\n");
		printf("0.Close\n");

		scanf(" %d", &option);


		switch (option)
		{
			case 1:
				ClrScr();

				//Queueing dogs
				Enqueue(&head, &tail, &isEmpty, ticketNumber, "Luna", 1, 2);
				ticketNumber++;

				Enqueue(&head, &tail, &isEmpty, ticketNumber, "Apollo", 2, 5);
				ticketNumber++;

				Enqueue(&head, &tail, &isEmpty, ticketNumber, "Dog", 3, 14);
				ticketNumber++;

				Enqueue(&head, &tail, &isEmpty, ticketNumber, "God", 4, 12);
				ticketNumber++;

				currentTicket = ticketNumber;

				Show("****People Enqueued****", head, isEmpty);
	
				WaitForKey();

				ClrScr();
				break;

			case 2:
				ClrScr();

				if (n == 0)
				{
					n1 = Dequeue(&head, &isEmpty);
					n++;

					printf("\n>>>>>>>Removed from queue: [%d]\n", n1.ticketNumber);
					Show("\n1st Dequeue:\n", head, isEmpty);
				}

				else if (n == 1)
				{
					n2 = Dequeue(&head, &isEmpty);
					n++;

					printf("\n>>>>>>>Removed from queue: [%d]\n", n2.ticketNumber);
					Show("\n2nd Dequeue:\n", head, isEmpty);
				}

				else if (n == 2)
				{
					n3 = Dequeue(&head, &isEmpty);
					n++;

					printf("\n>>>>>>>Removed from queue: [%d]\n", n3.ticketNumber);
					Show("\n3rd Dequeue:\n", head, isEmpty);
				}

				else if (n == 3)
				{
					n4 = Dequeue(&head, &isEmpty);
					n++;

					printf("\n>>>>>>>Removed from queue: [%d]\n", n4.ticketNumber);
					Show("\n4th Dequeue:\n", head, isEmpty);
				}

				WaitForKey();

				ClrScr();
				break;

			case 3:
				ClrScr();

				firstDog = Peek(&head, &isEmpty);

				if (!isEmpty)
					printf("\nHead: [%d] %s\n", firstDog.ticketNumber, firstDog.name);

				WaitForKey();

				ClrScr();
				break;

			case 4:
				ClrScr();

				if (!isEmpty)
					CalculateAgeAverageInQueue(head, isEmpty);

				WaitForKey();

				ClrScr();
				break;

			case 5:
				ClrScr();

				GenerateReport(&head, isEmpty);
				break;

			case '0':
				Exit();
				break;
		}
	}
}

void Enqueue(Dog** head, Dog** tail, bool* isEmpty, int queueNumber, char* dogName, int chip, int age)
{
	Dog* newDog;

	//dinamically allocating the pointer currentPerson;
	newDog = (Dog*)malloc(sizeof(Dog));
	newDog->ticketNumber = queueNumber;
	newDog->age = age;
	newDog->chip = chip;

	strcpy(newDog->name, dogName);

	newDog->next = NULL;

	if (*isEmpty)
	{
		//if these are empty, they're being filled in right now
		*head = newDog;
		*tail = newDog;

		//after filling with the new dog, the list is no longer empty
		*isEmpty = false;
	}
	else
	{
		//replaces the content of the tail
		(**tail).next = newDog;
		(*tail) = newDog;
	}
}

Dog Dequeue(Dog** head, bool* isEmpty)
{
	Dog dog;

	if (*isEmpty)
	{
		printf("\nQueue is empty\n");
		return EMPTY_QUEUE;
	}

	//dog is now the same as the content within the pointer head
	dog = **head;

	//the address of the head changes to the next dog
	*head = (**head).next;

	//if it's the last dog then the head is null
	*isEmpty = (*head == NULL);

	return dog;
}

int Count(Dog* head, bool isEmpty)
{
	Dog* currentDog;

	int count = 0;

	if (isEmpty)
		return 0;

	currentDog = head;

	//while the queue isn't empty
	while (currentDog != NULL)
	{
		count++;

		currentDog = currentDog->next;
	}

	return count;
}

float CalculateAgeAverageInQueue(Dog* head, bool isEmpty)
{
	Dog* currentDog;
	int count = Count(head, isEmpty);
	float ageAverage, ageSum;
	
	ageAverage = 0;
	ageSum = 0;
	currentDog = head;

	//checks if the list is empty
	if (currentDog == NULL)
	{
		printf("\nThe list is empty\n");
		return 0.0f;
	}

	while (currentDog != NULL)
	{
		printf("\n[%d] Age:%d\n", currentDog->chip, currentDog->age);

		//adds the age of dog in queue
		ageSum += currentDog->age;

		//setting the current dog to the next dog in queue
		currentDog = currentDog->next;
	}

	ageAverage = (float)ageSum / (float)count;

	printf("\nAge average in queue:\n%0.2f\n", ageAverage);
	return ageAverage;
}

void Show(char* title, Dog* head, bool isEmpty)
{
	Dog* currentDog;
	int showOrder = -1;

	printf("\n%s\n", title);
	printf("\n[%d in queue]\n", Count(head, isEmpty));

	if (isEmpty)
	{
		printf("\nQueue is empty\n");
		return;
	}

	currentDog = head;

	while (currentDog != NULL)
	{
		showOrder++;

		printf("\n[%d], %05d, %s, %d anos\n", currentDog->ticketNumber, currentDog->chip, currentDog->name, currentDog->age);

		currentDog = currentDog->next;
	}
}

Dog Peek(Dog** head, bool* isEmpty)
{
	Dog currentDog;

	if (*isEmpty)
	{
		printf("Queue is empty");
		return EMPTY_QUEUE;
	}

	//currentPerson is the same as the content in the head (first in queue)
	currentDog = **head;
	return currentDog;
}


void GenerateReport(Dog** head, bool isEmpty)
{
	Dog* currentDog;

	currentDog = *head;

	if (isEmpty)
	{
		printf("\nThe queue is empty\n");

		WaitForKey();

		ClrScr();
		return;
	}

	printf("\nPeople in queue:\n");

	while (currentDog != NULL)
	{
		printf("\n[%d] %s CHIP:%d AGE:%d\n", currentDog->ticketNumber, currentDog->name, currentDog->chip, currentDog->age);

		currentDog = currentDog->next;
	}

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