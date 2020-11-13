#define _CRT_SECURE_NO_WARNINGS
#define HASHTABLE_SIZE 23

#include "Structs.h"
#include "LinearProbingHashTable.h"
#include <ctype.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	Client clients[HASHTABLE_SIZE];

	InitHashTable(clients);

	Menu(clients);
}

void Menu(Client* clients)
{
	int option;

	option = 1;

	while (option != 0)
	{
		printf("1.Add Client\n");
		printf("2.Update Client\n");
		printf("3.Remove Client\n");
		printf("4.Search Client by field\n");
		printf("5.Report on all Clients\n");
		printf("0.Close\n");
		scanf(" %d", &option);

		switch (option)
		{
			case 1:
				ClrScr();
	
				Add(clients);

				//waits for the user key
				WaitForKey();

				//cleans the screen
				ClrScr();
				break;

			case 2:
				ClrScr();

				Update(clients);

				WaitForKey();

				ClrScr();
				break;

			case 3:
				ClrScr();

				Remove(clients);

				WaitForKey();

				ClrScr();
				break;

			case 4:
				ClrScr();

				SearchClientByField(clients);

				WaitForKey();

				ClrScr();
				break;

			case 5:
				ClrScr();

				GenerateReportOnClients(clients);

				WaitForKey();

				ClrScr();
				break;

			case 0:
				return;
				break;
		}
	}
}

int GenerateCode(Client* clients, char* name, char* phoneNumber)
{
	//variables
	Client* current;
	int x, nameLength, phoneNumberLenght;

	current = clients;

	x = Count(clients);
	nameLength = strlen(name);
	phoneNumberLenght = strlen(phoneNumber);

	x += nameLength;

	//if there is a code that's repeated (unlikely) it adds the phone number to the value obtained in n
	if (current->idCode == x)
		//phoneNumberLenght is the size of the phone number of the client
		x += phoneNumberLenght;

	return x;
}

int Count(Client* clients)
{
	//variables
	int i, count;

	count = 0;

	for (i = 0; i < HASHTABLE_SIZE; i++)
	{
		if (clients[i].isActive) count++;
	}

	return count;
}

void InitHashTable(Client* clients)
{
	int i;

	//initializing the elements in the array
	for (i = 0; i < HASHTABLE_SIZE; i++)
	{
		clients[i] = EMPTY;
		clients[i].idCode = 0;
		clients[i].isActive = false;
	}
}

int Hash(int x)
{
	return x % HASHTABLE_SIZE;
}

Client CreateClient()
{
	//variables
	Client newClient;
	int age;
	char name[70];
	char phoneNumber[10];

	/*prints*/
	printf("\n********Please fill the fields bellow********\n");
	printf("\nName:\n");
	scanf("%s", name);

	printf("\nAge:\n");
	scanf("%d", &age);

	printf("\nPhone Number:\n");
	scanf("%s", phoneNumber);

	/*filling in the variables on the new Client*/
	strcpy(newClient.name, name);
	newClient.age = age;
	strcpy(newClient.phoneNumber, phoneNumber);
	newClient.isActive = true;

	return newClient;
}

void Add(Client* clients)
{
	/*variables*/
	Client currentClient;

	//i corresponds to the hashcode and count corresponds to the number of attempts the user has tried to add a new element to the hastable
	int i, hashCode, count, nameLen;

	//the currentClient is the same that is being created (input by user)
	currentClient = CreateClient();
	count = 0;

	//creates the code for the user by calling the function generate code
	currentClient.idCode = GenerateCode(clients, currentClient.name, currentClient.phoneNumber);

	//gets name lenght
	nameLen = strlen(currentClient.name);
	hashCode = Hash(nameLen);
	i = hashCode;

	//while the Clients are active and the number of attempts is lower than the table size
	while (clients[i].isActive && count < HASHTABLE_SIZE)
	{
		i = (i % HASHTABLE_SIZE) + 1;
		count++;
	}

	if (count == HASHTABLE_SIZE)
	{
		printf("\nHashtable is full\n");
		return;
	}

	//adds to the hashcode place on the clients array the currentClient 
	clients[i] = currentClient;

	ClrScr();

	printf("\nRegistration sucessfully added!\n");
	printf("\n[%d] %s Phone Number: %s Age: %d", currentClient.idCode, currentClient.name, currentClient.phoneNumber, currentClient.age);
	printf("\n>>>>Probing Process: h(x)= h(%d) = %d; INDEX: %d; COLISIONS: %d<<<<\n", nameLen, hashCode, i, count);
}

void Update(Client* clients)
{
	//variables
	int index;
	char option;

	index = SearchIndex(clients, 0);

	if (index == -1) 
		printf("\nClient doesn't exist\n");

	UpdateInfoMenu(clients, 0, index);
	scanf(" %c", &option);

	//menu of options to update the profile
	switch (option)
	{
		case '1':
			UpdateInfoMenu(clients, 1, index);
			break;

		case '2':		
			UpdateInfoMenu(clients, 2, index);		
			break;

		case '3':
			if (clients[index].isActive)
				clients[index].isActive = false;

			else
				clients[index].isActive = true;
			break;
	}

	if (!clients[index].isActive)
	{
		UpdateInfoMenu(clients, 3, index);
		scanf(" %c", &option);

		option = toupper(option);

		switch (option)
		{
			case 'Y':
				Add(clients);			
				break;
			
			case 'N':			
				Menu(clients, HASHTABLE_SIZE);			
				break;
		}
	}

}

void Remove(Client* clients)
{
	int index;
	index = SearchIndex(clients, 0);

	//if it's outside the boundaries then it does not exist 
	if (index == -1) 
		printf("\nClient doesn't exist\n");

	//desactivates the Client
	clients[index].isActive = false;

	//removed message
	printf("\nSucessfully removed\n");
	printf("\nClient removed: [%d] %s\n", clients[index].idCode, clients[index].name);
}

int SearchIndex(Client* clients, int x)
{
	//variables
	int i, hash, userId, count, nameLen;

	userId = 0;
	count = 0;

	if (x == 0)
	{
		ShowActiveClients(clients);
		scanf("%d", &userId);
	}
	else if (x == 1)
	{
		printf("Please pick and id:");

		for (i = 0; i < HASHTABLE_SIZE; i++)
		{
			if (clients[i].isActive)
				printf("\n[ID:%d]\n", clients[i].idCode);
		}
		scanf("%d", &userId);
	}

	for (i = 0; i < HASHTABLE_SIZE; i++)
	{
		if (clients[i].idCode == userId) 
			nameLen = strlen(clients[i].name);
	}
	
	hash = Hash(nameLen);
	i = hash;

	//searching the Client that has this id code while its inside the hashtable size
	while (((clients[i].idCode != userId && clients[i].isActive) || !clients[i].isActive) && count < HASHTABLE_SIZE)
	{
		i = (i % HASHTABLE_SIZE) + 1;
		count++;
	}

	//last person on the hashtable
	if (count == HASHTABLE_SIZE) return -1;

	return i;
}

//Allows the user to find a report of a user by entering a field
void SearchClientByField(Client* clients)
{
	Client currentClient;
	int i, userId, count, index;

	count = 0;

	index = SearchIndex(clients, 1);

	//if it's outside the boundaries then it does not exist 
	if (index == -1)
		printf("\nClient doesn't exist\n");

	currentClient = clients[index];

	printf("**********************Client REPORT**********************");
	printf("\n[ID:%d]\nName:%s\nAge:%d\nPhone Number:%s\n", currentClient.idCode, currentClient.name, currentClient.age, currentClient.phoneNumber);
}

void GenerateReportOnClients(Client* clients)
{
	int i;

	printf("\n***************************REGISTRATIONS***************************\n");

	for (i = 0; i < HASHTABLE_SIZE; i++)
	{
		if (clients[i].isActive)
			printf("\n[%02d]\n[ID:%d]\nName:%s\nAge:%d\nPhone Number:%s\nACTIVE\n", i, clients[i].idCode, clients[i].name, clients[i].age, clients[i].phoneNumber);

		else if (!clients[i].isActive && clients[i].idCode != 0)
			printf("\n[%02d]\n INACTIVE\n", i);

		else
			printf("\n[%02d]\n UNUSED\n", i);
	}
}

void ShowActiveClients(Client* clients)
{
	int i;

	printf("Please pick an id:");

	for (i = 0; i < HASHTABLE_SIZE; i++)
	{
		if (clients[i].isActive)
			printf("\n[ID:%d]\nName:%s\nAge:%d\nPhone Number:%s\n", clients[i].idCode, clients[i].name, clients[i].age, clients[i].phoneNumber);
	}
}

void UpdateInfoMenu(Client* clients, int x, int index)
{
	int age;
	char phoneNumber[10];
	char option = ' ';
	
	if (x == 0)
	{
		ClrScr();

		printf("************************************Update info**************************************");
		printf("\n[ID:%d]\nName:%s\nAge:%d\nPhone Number:%s\n", clients[index].idCode, clients[index].name, clients[index].age, clients[index].phoneNumber);
		printf("\nWhich info would you like to update?\n[1]Age\n[2]Phone Number\n[3]Status\n");

	}
	if (x == 1)
	{
		ClrScr();

		printf("\nUpdate age:\n");
		scanf("%d", &age);

		clients[index].age = age;

		printf("\nAge sucessfully updated to %d\n", clients[index].age);
	}
	if (x == 2)
	{
		ClrScr();

		printf("\n Update Phone number:\n");
		scanf("%s", phoneNumber);

		strcpy(clients[index].phoneNumber, phoneNumber);

		printf("\nPhone number sucessfully updated to %s\n", clients[index].phoneNumber);
	}
	if (x == 3)
	{
		ClrScr();

		//if the user id doesnt match the position on the array then the user is allowed the chance to create a new instance
		printf("\nThat Client seems to not exist. Wish to add a new registration? [Y]es/[N]o\n");
	}

}

void ClrScr()
{
	system("cls");
}

void WaitForKey()
{
	system("pause");
}