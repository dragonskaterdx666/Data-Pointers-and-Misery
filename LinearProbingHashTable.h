
#ifndef LINEARPROBINGHASHTABLE_H_
#define LINEARPROBINGHASHTABLE_H_

/*/
* Manages the functions.
*
* @param clients (Client) to create interoperability for the other functions
*/
void Menu(Client* clients);

/*
* Inicializes the hashtable components.
*
* @params client (Client) to access the clients
*/
void InitHashTable(Client* clients);

/*
* Counts the clients on the list.
*
* @param clients (Client) to acess the clients
*
* @return count(int) amount of elements
* @return 0 if empty 
*/
int Count(Client* clients);

/*
* Generates the code for the clients on the list.
*
* HOW: by getting the lenght of the name and adds the position
* its in on the list, if it happens to be the same as another code
* then it adds in the phone number.
*
* @params clients (Client) to access the content of the pointer
* @params name(char) receives the clients name
* @params phoneNumber(char) receives to count its lenght
*
* @return x(int) being the sum of the above params
*/
int GenerateCode(Client* clients, char* name, char* phoneNumber);

/*
* Creates hash for the number given.
* 
* @params x(int) creates hash based on the lenght of the client's name
*/
int Hash(int x);

/*
* Creates a client of type Client by user input.
*
* @return the client (Client)
*/
Client CreateClient();

/*
* Adds the client to the hashtable.
*
* @params clients (Client) to acess to the array clients
*/
void Add(Client* clients);

/*
* Updates the client on the hashtable using user input.
*
* @params clients (Client) to acess to the array clients
*/
void Update(Client* clients);

/*
* Removes the client on the hashtable picked by the user.
*
* @params clients (Client) to acess to the array clients
*/
void Remove(Client* clients);

/*
* Searches the hashcode on the hashtable.
*
* @params clients (Client) to acess to the array clients
* @params x(int) that receives a command to print the right menu [0] being DEFAULT and [1] being SPECIAL case for SearchClientbyField
*
* @return the index of the hashcode 
* @return -1 if outside the bounds of the hashtable
*/
int SearchIndex(Client* clients, int x);

/*
* Searches the clients by ID.
*
* @params clients (Client) to acess to the array clients
*/
void SearchClientByField(Client* clients);

/*
* Prints report on all clients.
*
* @params clients (Client) to acess to the array clients
*/
void GenerateReportOnClients(Client* clients);

/*
* Shows report on all clients.
*
* @params clients (Client) to acess to the array clients
*/
void ShowActiveClients(Client* clients);

/*
* Manages options on the update function.
*
* @params clients (Client) to acess to the array clients
* @params x (int) receives a key to call on a different option
* @params index(int) receives the hashcode of pos of the client
*/
void UpdateInfoMenu(Client* clients, int x, int index);

/*
* Clears the console.
*/
void ClrScr();

/*
* Waits for the user to press a key.
*/
void WaitForKey();
#endif