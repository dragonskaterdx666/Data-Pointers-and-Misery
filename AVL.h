
#ifndef AVL_H_
#define AVL_H_

/*/
* Manages the functions.
*
* @params voter (Voter) to create interoperability for the other functions
*/
void Menu(Voter* voter);

/*
* Creates and adds the new node.
*
* @params node (Voter) to insert on the tree
* @params code(int) to receive the voter ID
* @params name(char) to receive the voters name
* @params job(char) to receive the voters job
* @params city(char) to receive the voters city
* @params age(int) to receive the voters age
*
* @return  [node] if unsuccessful insert or [newVoter] if successful
*/
Voter* CreateNode(Voter* node, int code, char* name, char* job, char* city, int age);

/*
* Updates node picked by user.
* 
* @params node (Voter) to search through the tree
*/
void Update(Voter* node);

/**
«auxiliary function of Update»
 * Prints update menu options.
 *
 * @params node (Voter) to get through the tree.
 */
void UpdateMenu(Voter* node);

/*
* Rebalances tree in case of unbalanced left side.
*
* @params x (Voter) problematic node
*
* @return a (Voter) node
*/
Voter* RightRotation(Voter* x);

/*
* Rebalances tree in case of unbalanced right side.
*
* @params x (Voter) problematic node
*
* @return a (Voter) node
*/
Voter* LeftRotation(Voter* x);

/*
* Removes node from tree.
*
* @params x (Voter) problematic node
*
* @return Node if unsuccessful removal of the node 
* @return currentNode if sucessful removal
*/
Voter* Remove(Voter* node, int code);

/**
 * Checks the node with the lowest value.
 *
 * @params node (Voter) to get lowest value node.
 *
 * @return current with the lowest value.
 * @return NULL if tree is empty.
 */
Voter* Min(Voter* node);

/**
 * Allows the user to filter through a city.
 *
 * @params node (Voter) to get through the tree.
 */
void PickCity(Voter* node);

/**
 * Prints all the nodes on the tree.
 *
 * @params node (Voter) to get through the tree.
 */
void Show(Voter* node);

/**
 * Prints all the voters who live in the same city.
 *
 * @params node (Voter) to get through the tree.
 * @params city (char) to filter the city
 */
void ShowPeopleByCity(Voter* node, char* city);

/**
 * Computes the age average of the voters on the city.
 *
 * @params node (Voter) to get through the tree.
 */
void ComputeAgeAverageByCity(Voter* node);

/**
 * Compares the ages of all voters to the city's age average, being the city picked by the user.
 *
 * @params node (Voter) to pass through to other functions
 * @params y (int) receives the city's age average
 */
void CompareAge(Voter* node, int y);

/**
 * Compares the ages of all voters to the city's age average, being the city picked by the user.
 *
 * @params node (Voter) to pass through to other functions
 *
 * @return count (int) of all people on the node
 */
int Count(Voter* node);

/**
 * Counts the amount of voters on that city.
 *
 * @params node (Voter) to get through the tree.
 * @params job (char) to compare and count the amount of nodes with the same job
 *
 * @return count (int) amount of voters
 */
int CountPeopleByCity(Voter* node, char* job);

/**
 * Sums the age of all voters.
 *
 * @params node (Voter) to get through the tree.
 *
 * @return ageSum (int) amount of voters
 */
int GetSumAge(Voter* node);

/**
 * Sums the age of voters on that city.
 *
 * @params node (Voter) to get through the tree.
 * @params job (char) to compare and add ages of nodes with the same job
 *
 * @return ageSum (int) amount of voters
 */
int GetSumAgeByCity(Voter* node, char* city);

/**
 * Calculate the height of a tree.
 *
 * @params node (Voter) to calculate height
 */
int GetHeight(Voter* node);

/**
«auxiliary function of GetHeight»
 * Returns the highest value between two integers.
 *
 * @params x (int) receives a number usually from GetHeight
 * @params y (int) receives a number usually from GetHeight
 * 
 * @return x if x > y
 * @return y if y > x
 */
int Max(int x, int y);

/**
«auxiliary function»
 * Prints menu to pick ID. 
 *
 * @params node (Voter) to get through the tree.
 */
int PickID(Voter* node);

/*
* Checks if the tree is balanced by subtracting the left side with the right.
* 
* @params node (Voter) to get through the tree.
*
* @return NULL if height is 0
* @return th value of subtraction
*/
int GetBalance(Voter* node);

/*
* Clears the console.
*/
void ClrScr();

/*
* Waits for the user to press a key.
*/
void WaitForKey();

#endif
