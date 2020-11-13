#ifndef STRUCTS_H_
#define STRUCTS_H_

#include <stdio.h>

typedef enum boolean
{
	false, true
} bool;

typedef struct dog
{
	int chip, age, ticketNumber;
	char name[70];
	struct dog* next;

} Dog;

const Dog EMPTY_QUEUE;
#endif
#pragma once
