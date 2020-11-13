#define _CRT_SECURE_NO_WARNINGS

#include "Structs.h"
#include "AVL.h"
#include <ctype.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	setlocale(LC_ALL, "Portuguese");

	Voter* voters;

	voters = NULL;

	Menu(voters);
}

void Menu(Voter* voters)
{
	//variables
	int option, n;

	option = 1;

	while (option != 0)
	{

		printf("=================================WELCOME TO THE TAX PAYER MANAGER==================================\n");
		printf("1.Add voters\n");
		printf("2.Update voters\n");
		printf("3.Remove voters\n");
		printf("4.Search voters by City\n");
		printf("5.Age average by City\n");
		printf("6.Show all voters\n");
		printf("0.Close\n");
		printf("===================================================================================================\n");

		scanf(" %d", &option);

		switch (option)
		{
			case 1:
				//adding the associates to the tree nodes
				voters = CreateNode(voters, 0, "Ana", "antropóloga", "Aveiro", 20);
				voters = CreateNode(voters, 2, "Catarina", "cozinheira", "Coimbra", 40);
				voters = CreateNode(voters, 1, "Bárbara", "baterista", "Braga", 30);
				voters = CreateNode(voters, 4, "Emma", "enfermeira", "Esposende", 60);
				voters = CreateNode(voters, 3, "Diana", "designer", "Viseu", 35);
				voters = CreateNode(voters, 5, "Flávia", "enfermeira", "Figueira da Foz", 40);

				//cleans the screen
				ClrScr();

				Show(voters);

				WaitForKey();

				ClrScr();
				break;

			case 2:
				ClrScr();
				Update(voters);

				WaitForKey();

				ClrScr();
				break;

			case 3:
				ClrScr();
				n = PickID(voters);

				Remove(voters, n);

				WaitForKey();

				ClrScr();
				break;

			case 4:
				ClrScr();
				PickCity(voters);

				WaitForKey();

				ClrScr();
				break;

			case 5:
				ClrScr();
				ComputeAgeAverageByCity(voters);

				WaitForKey();

				ClrScr();
				break;

			case 6:
				ClrScr();
				Show(voters);

				WaitForKey();

				ClrScr();
				break;

			case 0:
				return;
				break;
		}
	}
}

Voter* CreateNode(Voter* node, int code, char* name, char* job, char* city, int age)
{
	Voter* newvoter;
	int balance;

	//if its the first node
	if (node == NULL)
	{
		//filling in the node
		newvoter = (Voter*)malloc(sizeof(Voter));
		newvoter->right = NULL;
		newvoter->left = NULL;
		newvoter->code = code;
		newvoter->age = age;

		//height of the first element is 1
		newvoter->height = 1;

		strcpy(newvoter->name, name);
		strcpy(newvoter->job, job);
		strcpy(newvoter->city, city);

		//returns the new tax payer
		return newvoter;
	}

	//smaller numbers go on the left side
	if (code < node->code)
		//adds the node to the left
		node->left = CreateNode(node->left, code, name, job, city, age);

	//else if its higher then it goes to right
	else
		node->right = CreateNode(node->right, code, name, job, city, age);

	//calculates the tree height
	node->height = Max(GetHeight(node->left), GetHeight(node->right)) + 1;

	//calculates the balance
	balance = GetBalance(node);

	#pragma region Checking Balance

	//subtree is balanced if the values of the node weights are in between [-1; 1]
	if (balance >= -1 && balance <= 1)
		return node;

	//if its heavier on the left and the id is lower the the one on the left
	if (balance > 1 && code < node->left->code)
	{
		//right rotation
		newvoter = RightRotation(node);
		return newvoter;
	}

	//if the balance is negative than it's heavier on the right side and we have to do a left rotation
	else if (balance < -1 && code > node->right->code)
	{
		newvoter = LeftRotation(node);
		return newvoter;
	}

	//if the tree is heavier on the left side and the id is higher than the one on the left
	else if (balance > 1 && code > node->left->code)
	{
		//left rotation of the left element
		node->left = LeftRotation(node->left);

		//right rotation of the current node
		newvoter = RightRotation(node);
		return newvoter;
	}
	else if (balance < -1 && code < node->right->code)
	{
		node->right = RightRotation(node->right);
		newvoter = LeftRotation(node);
		return newvoter;
	}
	else
	{
		//if it doesn't fit any of these cases
		printf("ERROR");
		return node;
	}
	#pragma endregion

}

void Update(Voter* node)
{
	//variables
	int userOption = PickID(node);

	if (userOption == node->code)
		UpdateMenu(node);

	//if we havent found the match we go into subtrees
	else if (userOption > node->code)
	{
		//right subtree is the id is higher than the current node id
		node = node->right;

		Update(node);
	}
	else if (userOption < node->code)
	{
		//left if its lower
		node = node->left;

		Update(node);
	}

}

void UpdateMenu(Voter* node)
{
	int option;
	char city[30];
	char job[30];

	printf("=================================Update info=================================");
	printf("\n[ID:%d]\nName:%s\nJob:%s\nCity:%s\n", node->code, node->name, node->job, node->city);
	printf("\nWhich info would you like to update?\n[1]Job\n[2]City\n");
	scanf("%d", &option);

	switch (option)
	{
		case 1:
			printf("\nUpdate Job:\n");
			scanf(" %s", job);

			strcpy(node->job, job);

			printf("\nJob sucessfully updated to %s\n", node->job);
			break;

		case 2:
			printf("\n Update City\n");
			scanf("%s", city);

			strcpy(node->city, city);

			printf("\nCity sucessfully updated to %s\n", node->city);
			break;
	}
}

Voter* RightRotation(Voter* x)
{
	Voter* a, * b;

	//initialization
	a = x->left;
	b = a->right;

	//updating the node positions
	a->right = x;
	x->left = b;

	//calculating the height of the updated nodes
	x->height = Max(GetHeight(x->left), GetHeight(x->right)) + 1;
	a->height = Max(GetHeight(a->left), GetHeight(a->right)) + 1;

	return a;
}

Voter* LeftRotation(Voter* x)
{
	Voter* a, * b;

	//initialization
	a = x->right;
	b = a->left;

	//updating the node positions
	a->left = x;
	x->right = b;

	//calculating the height of the updated nodes
	x->height = Max(GetHeight(x->left), GetHeight(x->right)) + 1;
	a->height = Max(GetHeight(a->left), GetHeight(a->right)) + 1;

	return a;
}

Voter* Remove(Voter* node, int code)
{
	//Variables
	Voter* temp;
	int balance;

	//The case in which the tree is empty
	if (node == NULL) return node;
	
	//Search the node to be deleted
	if (code < node->code)
		node->left = Remove(node->left, code);

	else if (code > node->code)
		node->right = Remove(node->right, code);

	else
	{
		//The node was found
		if (node->left == NULL && node->right == NULL)
		{
			//there's only one element in the tree
			temp = node;
			node = NULL;
			free(node);
		}
		else if (node->left == NULL || node->right == NULL)
		{
			//only one child or no childs
			temp = node->left != NULL ? node->left : node->right;
			node = temp;
			free(temp);
		}
		else
		{
			//the node has two children
			temp = Min(node->right);
			node->code = temp->code;
			node->right = Remove(node->right, temp->code);
		}
	}
	//Case in which the subtree is empty
	if (node == NULL) return node;

	//Compute the height of the node
	node->height = Max(GetHeight(node->left), GetHeight(node->right)) + 1;

	//Check the balancement after removal
	balance = GetBalance(node);

	//Subtree is unbalanced
	//Simple Right rotation
	if (balance > 1 && GetBalance(node->left) >= 0)
	{
		temp = RightRotation(node);

		//return the node after the rotation
		return temp;
	}
	//left then right rotation
	else if (balance > 1 && GetBalance(node->left) < 0)
	{
		node->left = LeftRotation(node->left);
		temp = RightRotation(node);

		return temp;
	}
	//simple left rotation
	else if (balance < -1 && GetBalance(node->right) <= 0)
	{
		temp = LeftRotation(node);

		return temp;
	}
	//Double Rotation (right and left)
	else if (balance < -1 && GetBalance(node->right) > 0)
	{
		node->right = RightRotation(node->right);
		temp = LeftRotation(node);

		return temp;
	}
	else
	{
		return node;
	}
}


Voter* Min(Voter* node)
{
	Voter* current = node;

	//smaller node ids are on the left so it checks until it finds the last left node
	while (current->left != NULL)
		current = current->left;

	return current;
}

void PickCity(Voter* node)
{
	char city[30];

	if (node == NULL)
		return;

	Show(node);

	printf("\nFilter by a city:[start with a capital letter]\n");
	scanf(" %s", city);

	ClrScr();

	printf("\n[%s]\n", city);

	ShowPeopleByCity(node, city);
}

void Show(Voter* node)
{
	if (node == NULL)
		return;

	Show(node->left);

	printf("\n[%d] - %s - %s - %s - age: %d\n", node->code, node->name, node->job, node->city, node->age);

	Show(node->right);
}

void ShowPeopleByCity(Voter* node, char* city)
{
	if (node == NULL)
		return;

	ShowPeopleByCity(node->left, city);

	if (strcmp(city, node->city) == 0)
		printf("\n%s\n", node->name);

	ShowPeopleByCity(node->right, city);
}

void ComputeAgeAverageByCity(Voter* node)
{
	int age, count;
	float ageAverage;
	char city[30];

	printf("\nPick a city:\n");

	Show(node);

	scanf(" %s", city);

	count = CountPeopleByCity(node, city);
	age = GetSumAgeByCity(node, city);

	ageAverage = (float)age / (float)count;

	printf("\nAge average:\n");
	printf("\n%0.0f\n", ageAverage);

	CompareAge(node, ageAverage);
}

void CompareAge(Voter* node, int y)
{
	int ageSum, count, x;

	count = Count(node);
	ageSum = GetSumAge(node);

	x = (float)ageSum / (float)count;

	printf("\nAge average of all voters:\n");
	printf("\n%0.0f\n", x);

	printf("\nAge average of this city:\n");
	printf("\n%0.0f\n", y);

	if (x > y)
		printf("\nThe voters in this city are aged bellow average\n");

	else
		printf("\nThe voters in this city are aged above average\n");

}

int Count(Voter* node)
{
	int count = 0;

	if (node == NULL) return count;

	count += Count(node->left);
	count += Count(node->right);

	return count;
}

int CountPeopleByCity(Voter* node, char* city)
{
	int count = 0;

	if (node == NULL) return count;	

	if (strcmp(node->city, city) == 0)	count++;

	count += CountPeopleByCity(node->left, city);
	count += CountPeopleByCity(node->right, city);

	return count;
}

int GetSumAge(Voter* node)
{
	int ageSum = 0;

	if (node == NULL) return ageSum;

	do { ageSum += node->age;} while (node != NULL);

	return ageSum;
}

int GetSumAgeByCity(Voter* node, char* city)
{
	int ageSum = 0;

	if (node == NULL) return ageSum;
	
	if (strcmp(node->city, city) == 0) ageSum += node->age;
	
	ageSum += GetSumAgeByCity(node->left, city);
	ageSum += GetSumAgeByCity(node->right, city);

	return ageSum;
}

int GetHeight(Voter* node)
{
	if (node != NULL)
		return node->height;
	else
		return 0;
}

int Max(int x, int y)
{
	return (x > y) ? x : y;
}

int PickID(Voter* node)
{
	int id = 0;

	printf("\nPick and id:\n");

	Show(node);

	scanf(" %d", &id);

	WaitForKey();

	ClrScr();

	return id;
}

int GetBalance(Voter* node)
{
	return (node == NULL) ? 0 : GetHeight(node->left) - GetHeight(node->right);
}

void ClrScr()
{
	system("cls");
}

void WaitForKey()
{
	system("pause");
}