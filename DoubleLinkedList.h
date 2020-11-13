
#ifndef DOUBLELINKEDLIST_H_
#define DOUBLELINKEDLIST_H_

/*/
* Manages the functions.
*
* @param head (WineBottle) to create interoperability for the other functions
* @param tail (WineBottle) to create interoperability for the other functions
*/
void Menu(WineBottle** head, WineBottle** tail);

/*
* Counts the wine bottles on the list.
*
* @param head (WineBottle) to access the content of the pointer
*
* @return count(int) amount of elements on the list 
* @return 0 if list is empty
*/
int Count(WineBottle** head);

/*
* Generates the code for the wine bottles on the list. 
*   
* HOW: by getting the lenght of the name and adds the position 
* its in on the list, if it happens to be the same as another code
* then it adds in x, x being the stockQuantity.
*    
* @params head (WineBottle) to access the content of the pointer
* @params name(char) receives the wine bottles name
* @params x(int) receives the wine bottles stockQuantity
*  
* @return y(int) being the sum of the above params
*/
int GenerateCode(WineBottle** head, char* name, int x);

/*
* Creates a wine bottle.
*
* @returns newWineBottle (WineBottle) that was created by user input
*/
WineBottle* CreateWineBottle();

/*
* Shows all the wine bottles on the list.
*
* @params head (WineBottle) to access the content of the pointer
*/
void ShowList(WineBottle** head);

/*
* Inserts the winebottle to the head or tail according to the its position.
*
* @params head (WineBottle) to insert on *head
* @params tail (WineBottle) to insert on *tail
*/
void Insert(WineBottle** head, WineBottle** tail);

/*
* Updates the winebottle with user input.
*
* @params head (WineBottle) to update on *head
*/
void Update(WineBottle** head);

/*
* Removes the winebottle the user picked.
*
* @params head (WineBottle) to remove on *head
* @params tail (WineBottle) to remove on *tail
*/
void Remove(WineBottle** head, WineBottle** tail);

/*
* Print report in the list in ascending order.
*
* @params head (WineBottle) to get the content from *head
*/
void GenerateReportAscending(WineBottle** head);

/*
* Print report in the list in descending order.
*
* @params tail (WineBottle) to get the content from *tail
*/
void GenerateReportDescending(WineBottle** tail);

/*
* Compute wine bottle stock average.
*
* @params head (WineBottle) to acess the list on *head
*/
void ComputeStockAverage(WineBottle** head);

/*
* Clears the console.
*/
void ClrScr();

/*
* Waits for the user to press a key.
*/
void WaitForKey();

/*
* Exits the console.
*/
void Exit();
#endif

