
#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

/*/
* Manages the functions.
*
* @param head (Dog) to create interoperability for the other functions
* @param tail (Dog) to create interoperability for the other functions
* @param isEmpty (boolean) to create interoperability for the other functions
* @param ticketNumber(int) to manage the dequeues
*/
void Menu(Dog* head, Dog* tail, bool isEmpty, int ticketNumber);

/*
* Enqueues dogs starting on the tail.
*
* @param head (Dog) where the first element is filled
* @param tail (Dog) where the queue is filled
* @param isEmpty (boolean) that checks if the queue is empty (true) or not (false)
* @param queueNumber (int) that determines the position of the queued dog to be called when dequeueing
* @param dogName (char) receives the dog name to be queued
* @param chip(int) receives the dog's id
* @param age(int) receives the dog's age
*
*/
void Enqueue(Dog** head, Dog** tail, bool* isEmpty, int queueNumber, char* dogName, int chip, int age);

/*
* Dequeues from the top to the bottom of the list (FIFO).
*
* @param head (Dog) to access the content of head when dequeueing
* @param isEmpty(bool) when the last element is removed to return the isEmpty as true
*
* @return dog to be dequeued
*/
Dog Dequeue(Dog** head, bool* isEmpty);

/*/
* Counts the amount of people queue.
*
* @param head (Dog) to count the amount of people in queue
* @param isEmpty (boolean) to check and set the emptiness of the queue
*
* @return count(int) if there's any element on the list
* @return 0 if it's empty
*/
int Count(Dog* head, bool isEmpty);

/*
* Calculates the average age of the dogs in queue.
*
* @param head (Dog) to count the amount of people in queue
* @param isEmpty (boolean) to check and set the emptiness of the queue
*
* @return 0.0f if queue is empty
* @return ageAverage(float)
*/
float CalculateAgeAverageInQueue(Dog* head, bool isEmpty);

/*
* Shows the dogs in queue.
*
* @param title (char) receives the text to display before showing the queue
* @param head (Dog) to count the amount of people in queue
* @param isEmpty (boolean) to check and set the emptiness of the queue
*/
void Show(char* title, Dog* head, bool isEmpty);

/*
* Peeks the next element to be dequeued.
*
* @param head (Dog) to count the amount of people in queue
* @param isEmpty (boolean) to check and set the emptiness of the queue
*
* @return dog(Dog) head of the list
*/
Dog Peek(Dog** head, bool* isEmpty);

/*
* Generates report on the dogs in queue.
*
* @param head (Dog) to count the amount of people in queue
* @param isEmpty (boolean) to check and set the emptiness of the queue
*/
void GenerateReport(Dog** head, bool isEmpty);

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