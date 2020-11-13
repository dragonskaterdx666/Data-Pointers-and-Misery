#define _CRT_SECURE_NO_WARNINGS
#define HASHTABLE_SIZE 19

#include "Structs.h"
#include "ColisionHashTable.h"
#include <ctype.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	setlocale(LC_ALL, "Portuguese");

	Player* players[HASHTABLE_SIZE];

	InitHashTable(players);

	Menu(players, HASHTABLE_SIZE);
}

void Menu(Player* players[])
{
	//variables
	int option;

	option = 1;

	while (option != 0)
	{
		printf("****WELCOME TO THE \"ESTES SOFREM DA BOLA\" TOURNAMENT***** \n");
		printf("1.Enroll player\n");
		printf("2.Update player\n");
		printf("3.Remove player\n");
		printf("4.Compute Age Average\n");
		printf("5.Report on all players\n");
		printf("6.Sort players by gender\n");
		printf("0.Close\n");
		scanf(" %d", &option);

		switch (option)
		{
			case 1:
				ClrScr();

				Add(players);
				//cleans the screen
				ClrScr();
				break;

			case 2:
				ClrScr();

				Update(players);

				ClrScr();
				break;

			case 3:
				ClrScr();

				Remove(players);

				ClrScr();
				break;

			case 4:
				ClrScr();

				ComputeAgeAverage(players);

				ClrScr();
				break;

			case 5:
				ClrScr();

				GenerateReport(players);

				ClrScr();
				break;

			case 6:
				ClrScr();

				ShowByGender(players);

				ClrScr();
				break;

			case 0:
				return;
				break;
		}
	}
}

void InitHashTable(Player* players[])
{
	int i;

	for (i = 0; i < HASHTABLE_SIZE; i++)
	{
		players[i] = NULL;
	}
}

int Hash(int x)
{
	return x % HASHTABLE_SIZE;
}

int GenerateCode(Player* players[], char* name, int number)
{
	Player* currentPlayer;
	int n, nameLen, i;

	n = Count(players);
	nameLen = strlen(name);
	n += nameLen;

	for (i = 0; i < HASHTABLE_SIZE; i++)
	{
		currentPlayer = players[i];

		while (currentPlayer != NULL)
		{
			//if the ids are the same then it adds the number
			if (n == currentPlayer->id)
				return n += number;

			//passes on to the next player
			currentPlayer = currentPlayer->next;
		}
	}

	return n;
}

int Count(Player* players[])
{
	//variables
	Player* currentPlayer;
	int i, count;

	/*filling in VARIABLE*/
	count = 0;

	for (i = 0; i < HASHTABLE_SIZE; i++)
	{
		currentPlayer = players[i];

		while (currentPlayer != NULL)
		{
			count++;

			currentPlayer = currentPlayer->next;
		}
	}

	return count;
}

bool CheckIfNumberExists(Player* players[], int number)
{
	Player* currentPlayer;
	int i;

	for (i = 0; i < HASHTABLE_SIZE; i++)
	{
		currentPlayer = players[i];

		while (currentPlayer != NULL)
		{
			//if the strings are the same then
			if (number == currentPlayer->number)
			{
				printf("\nThat number already exists, please pick another one!\n");
				return false;
			}

			//passes on to the next player
			currentPlayer = currentPlayer->next;
		}
	}

	return true;
}

Player* CreatePlayer(Player* players[])
{
	//variables
	Player* newPlayer;
	bool isNumberAvailable = true;
	int age, id, gender, number;
	char name[70];

	//Allocating variables
	newPlayer = (Player*)malloc(sizeof(Player));

	printf("\n********Please fill the fields bellow********\n");
	printf("\nName:\n");
	scanf(" %s", &name);

	printf("\nAge:\n");
	scanf("%d", &age);

	printf("\nGender:\n[1]Female\n[2]Male\n");
	scanf("%d", &gender);

	if (gender == 1) newPlayer->gender = female;

	else if (gender == 2) newPlayer->gender = male;

	else
	{
		printf("\nGender:\n[1]Female\n[2]Male\n");
		scanf("%d", &gender);
	}

	do
	{
		printf("\nNumber:\n");
		scanf(" %d", &number);

		//checks if number is available
		isNumberAvailable = CheckIfNumberExists(players, number);

	} while (!isNumberAvailable);

	id = GenerateCode(players, name, number);

	//filling in the variables on the new associate
	strcpy(newPlayer->name, name);
	newPlayer->number = number;
	newPlayer->age = age;
	newPlayer->id = id;
	newPlayer->isActive = true;
	newPlayer->gender = gender;

	return newPlayer;
}

void Add(Player* players[])
{
	//variables
	Player* player;
	Player* playerList;
	int hashCode, id;

	//creating the player using an auxiliary function
	player = CreatePlayer(players);

	id = player->id;

	//initializing the hashcode
	hashCode = Hash(id);

	//playerlist is equivalent to the slot created within players on the position hashcode
	playerList = players[hashCode];

	//the next player is the one on the list (Slot spot)
	player->next = playerList;

	//adds the new player to the slot created 
	players[hashCode] = player;

	WaitForKey();

	ClrScr();

	printf("\nRegistration sucessfully added!\n");
	printf("\n[%d] %s Number: %d Age: %d", player->id, player->name, player->number, player->age);
	printf("\n>>>>Process: h(x)= h(%d) = %d<<<<\n", id, hashCode);

	WaitForKey();
}

void Update(Player* players[])
{
	//variables
	Player* currentPlayer, * previous;
	bool isNumberAvailable = true;
	int userOption, hashCode, i, option, age, number;

	currentPlayer = NULL;
	userOption = 0;
	option = 0;

	ShowActivePlayers(players);

	//gets the ID the user picked 
	scanf("%d", &userOption);

	ClrScr();

	hashCode = Hash(userOption);
	//user 3 ele ta no hashcode 5
	currentPlayer = players[hashCode];

	ClrScr();

	if (currentPlayer == NULL)
	{
		printf("\nPlayer doesn't exist\n");
		
		WaitForKey();
		return;
	}

	printf("************************************Update info**************************************");
	printf("\n[ID:%d]\nName:%s\nnumber:%d\nAge:%d\n", currentPlayer->id, currentPlayer->name, currentPlayer->number, currentPlayer->age);
	printf("\nWhich info would you like to update?\n[1]Age\n[2]number\n");
	//scans the user option
	scanf(" %d", &option);

	switch (option)
	{
		case 1:
			ClrScr();

			printf("\nUpdate age:\n");
			scanf("%d", &age);

			//updates the age of the desired id
			currentPlayer->age = age;

			printf("\nAge sucessfully updated to %d\n", currentPlayer->age);

			WaitForKey();
			break;

		case 2:
			ClrScr();

			do
			{
				printf("\n Update number:\n");
			} while (!isNumberAvailable);

			//updates the phone number of the desired id
			scanf(" %d", &number);

			currentPlayer->number = number;

			printf("\nPlayer's number sucessfully updated to %d\n", currentPlayer->number);

			WaitForKey();
			break;
	}

}

void Remove(Player* players[])
{
	//variables
	Player* currentPlayer, * temp, * previous;
	bool isRemoved = false;
	int userOption, hashCode;

	//initializing
	previous = NULL;

	ShowActivePlayers(players);

	//gets the ID the user picked 
	scanf("%d", &userOption);

	//get hashcode
	hashCode = Hash(userOption);

	//checks if there is that option within the hashtable slots
	if (players[hashCode] == NULL)
	{
		printf("\nElement does not exist\n");
		WaitForKey();
		return;
	}

	//removes the user
	if (players[hashCode]->id == userOption)
	{
		//temp is the current player option
		temp = players[hashCode];

		//the current option passes down to the next (removes the current one)
		players[hashCode] = players[hashCode]->next;

		//frees the current player option
		free(temp);

		isRemoved = true;
	}

	currentPlayer = players[hashCode];

	while (currentPlayer != NULL && currentPlayer->id != userOption)
	{
		//goes to next element
		previous = currentPlayer;
		currentPlayer = currentPlayer->next;
	}

	if (currentPlayer == NULL)
	{
		printf("\nPlayer doesn't exist\n");
		return;
	}

	if (previous != NULL) previous->next = currentPlayer->next;

	free(currentPlayer);

	if (isRemoved)
	{
		printf("\nPlayer sucessfully removed\n");

		WaitForKey();
	}
		
	ClrScr();
}

Player* SearchPlayer(Player* players[], int playerId)
{
	Player* currentPlayer;

	int hash;

	hash = Hash(playerId);

	currentPlayer = players[hash];

	while ((currentPlayer != NULL) && (currentPlayer->number != playerId))
		currentPlayer = currentPlayer->next;

	return currentPlayer;
}

void ComputeAgeAverage(Player* players[])
{
	//variables
	Player* currentPlayer;
	int count = Count(players);
	float ageAverage, ageSum;

	//initializing variables
	ageAverage = 0;

	ageSum = 0;

	for (int i = 0; i < HASHTABLE_SIZE; i++)
	{
		currentPlayer = players[i];

		while (currentPlayer != NULL)
		{
			printf("\n[%d] Age: %d\n", currentPlayer->id, currentPlayer->age);

			//adds the age of players
			ageSum += currentPlayer->age;

			currentPlayer = currentPlayer->next;

		}

	}

	//computes the age average
	ageAverage = (float)ageSum / (float)count;

	printf("\nAge average on the list is:\n%0.2f\n", ageAverage);

	WaitForKey();

}

void ShowActivePlayers(Player* players[])
{
	Player* currentPlayer;
	int i;

	printf("Please pick an id:");

	//shows all the enrolled players
	for (i = 0; i < HASHTABLE_SIZE; i++)
	{
		currentPlayer = players[i];

		while (currentPlayer != NULL)
		{
			if(currentPlayer->isActive)
				printf("\n[ID:%d]\nName:%s\nnumber:%d\nAge:%d\n", currentPlayer->id, currentPlayer->name, currentPlayer->number, currentPlayer->age);

			currentPlayer = currentPlayer->next;
		}
	}
}

void ShowByGender(Player* players[])
{
	Player* currentPlayer;
	Gender g = female;
	int i, gender;
	
	gender = 0;

	printf("\nPlease a Gender:\n[1]Female\n[2]Male\n");
	scanf("%d", &gender);

	if (gender == 1)
	{
		for (i = 0; i < HASHTABLE_SIZE; i++)
		{
			currentPlayer = players[i];

			while (currentPlayer != NULL)
			{
				if (currentPlayer->gender == g)
					printf("\n|| FEMALE PLAYERS ||\n[ID:%d] - Name:%s - number:%d - age:%d\n", currentPlayer->id, currentPlayer->name, currentPlayer->number, currentPlayer->age);

				currentPlayer = currentPlayer->next;
			}
		}

		WaitForKey();
	}
	else
	{
		for (i = 0; i < HASHTABLE_SIZE; i++)
		{
			currentPlayer = players[i];

			while (currentPlayer != NULL)
			{
				if (currentPlayer->gender != g)
					printf("\n|| MALE PLAYERS ||\n[ID:%d] - Name:%s - number:%d - age:%d\n", currentPlayer->id, currentPlayer->name, currentPlayer->number, currentPlayer->age);

				currentPlayer = currentPlayer->next;
			}
		}

		WaitForKey();
	}

}

void GenerateReport(Player* players[])
{
	//variables
	int i;

	Player* currentPlayer;

	printf("\n***************************REGISTRATIONS***************************\n");

	//the for iterates the hashtables
	for (i = 0; i < HASHTABLE_SIZE; i++)
	{
		currentPlayer = players[i];

		printf("\n[%02d] SLOT\n", i);

		//this while allows to iterate within the array players
		while (currentPlayer != NULL)
		{
			printf("\n[ID:%d] | Name:%s | Age:%d | Number:%d [ENROLLED]\n", currentPlayer->id, currentPlayer->name, currentPlayer->age, currentPlayer->number);

			currentPlayer = currentPlayer->next;
		}
	}

	WaitForKey();
}

void ClrScr()
{
	system("cls");
}

void WaitForKey()
{
	system("pause");
}