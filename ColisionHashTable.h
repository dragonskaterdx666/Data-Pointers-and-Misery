
#ifndef COLISIONHASHTABLE_H_
#define COLISIONHASHTABLE_H_

/*/
* Manages the functions.
*
* @param array players (Player) to create interoperability for the other functions
*/
void Menu(Player* players[]);

/*
* Inicializes the hashtable components.
*
* @params players (Player) to access the players[]
*/
void InitHashTable(Player* players[]);

/*
* Creates hash for the number given.
*
* @params x(int) creates hash based on the ID
*/
int Hash(int x);

/*
* Generates the code for the clients on the list.
*
* HOW: by getting the lenght of the name and adds the position
* its in on the list, if it happens to be the same as another code
* then it adds in the number of the player.
*
* @params players (Player) to access the array
* @params name(char) receives the players name
* @params number(int) receives the players number
*
* @return x(int) being the sum of the above params
*/
int GenerateCode(Player* players[], char* name, int number);

/*
* Counts the players on the list.
*
* @param players (Player) to acess the players[]
*
* @return count(int) amount of elements on the list
* @return 0 if its empty
*/
int Count(Player* players[]);

/*
* Checks if the number the user picked is available.
* [its called on Create function to fill isNumberAvailable(boolean)] 
*
* @params players (Player) to acess players[]
* @params number(int) that receives the players number
*
* @return isNumberAvailable = false if the number = an existent number |
* @return isNumberAvailable = true if number does not exist
*/
bool CheckIfNumberExists(Player* players[], int number);

/*
* Creates a player of type Player by user input.
*
* @return the player (Player)
*/
Player* CreatePlayer(Player* players[]);

/*
* Adds the player to the hashtable.
*
* @params players (Player) to acess players[]
*/
void Add(Player* players[]);

/*
* Update the player using user input.
*
* @params players (Player) to acess players[]
*/
void Update(Player* players[]);

/*
* Removes the player from the hashtable.
*
* @params players (Player) to acess players[]
*/
void Remove(Player* players[]);

/*
* Searches for a specific player.
*
* @params players (Player) to acess to players[]
* @params playerNumber(int) to search the player
*
* @return player (Player) 
*/
Player* SearchPlayer(Player* players[], int playerNumber);

/*
* Computes age average of the players.
*
* @params players (Player) to acess to players[]
*/
void ComputeAgeAverage(Player* players[]);

/*
* Prints all the active players.
*
* @params players (Player) to acess to players[]
*/
void ShowActivePlayers(Player* players[]);

/*
* Prints report on all players.
*
* @params players (Player) to acess to players[]
*/
void GenerateReport(Player* players[]);

/*
* Displays players according to gender picked by the user.
*
* @params players (Player) to acess to players[]
*/
void ShowByGender(Player* players[]);

/*
* Clears the console.
*/
void ClrScr();

/*
* Waits for the user to press a key.
*/
void WaitForKey();

#endif
