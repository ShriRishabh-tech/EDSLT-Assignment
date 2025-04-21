//Name:S Shri Rishabh
//Roll No:ME24B1012
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 10
// PART A
// Queue (Array Implementation)
char partQueue[SIZE][20];
int front = -1, rear = -1;
void enqueue(char part[])
{
	if (rear == SIZE - 1) {
		printf("Queue full. Can't enqueue %s\n", part);
		return;
	}
	if (front == -1) front = 0;
	rear++;
	strcpy(partQueue[rear], part);
}
char* dequeue() {
	if (front == -1 || front > rear) {
		return NULL;
	}
	return partQueue[front++];
}
// Stack
char stack[SIZE][20];
int top = -1;
void push(char part[])
{
	if (top == SIZE - 1) {
		printf("Stack full. Can't push %s\n", part);
		return;
	}
	top++;
	strcpy(stack[top], part);
}
char* pop()
{
	if (top == -1) return NULL;
	return stack[top--];
}
//  PART B
char roverStorage[5][10];
int storageCount = 0;
void storeRover(char rover[])
{
	if (storageCount < 5) {
		strcpy(roverStorage[storageCount], rover);
		storageCount++;
	} else {
		printf("Storage full. Deploying %s to make space for %s\n", roverStorage[0], rover);
		// Shift all left
		for (int i = 1; i < 5; i++) {
			strcpy(roverStorage[i - 1], roverStorage[i]);
		}
		strcpy(roverStorage[4], rover);
	}
}
void printStorage()
{
	printf("\nRovers in Storage:\n");
	for (int i = 0; i < storageCount; i++) {
		printf("- %s\n", roverStorage[i]);
	}
}
// PART C
// Singly Linked List (Faulty Rovers)
struct SNode {
	char name[10];
	struct SNode* next;
};
typedef struct SNode SNode;
SNode* faultyHead = NULL;
void insertFaulty(char rover[])
{
	SNode* temp = (SNode*)malloc(sizeof(SNode));
	strcpy(temp->name, rover);
	temp->next = faultyHead;
	faultyHead = temp;
}
void deleteFaulty(char rover[])
{
	SNode *curr = faultyHead, *prev = NULL;
	while (curr != NULL) {
		if (strcmp(curr->name, rover) == 0) {
			if (prev == NULL)
				faultyHead = curr->next;
			else
				prev->next = curr->next;
			free(curr);
			return;
		}
		prev = curr;
		curr = curr->next;
	}
}
// Doubly Linked List (Repaired Rovers)
struct DNode {
	char name[10];
	struct DNode *prev, *next;
};
typedef struct DNode DNode;
DNode* repairedHead = NULL;
DNode* repairedTail = NULL;
void insertRepaired(char rover[])
{
	DNode* temp = (DNode*)malloc(sizeof(DNode));
	strcpy(temp->name, rover);
	temp->prev = repairedTail;
	temp->next = NULL;
	if (repairedTail != NULL)
		repairedTail->next = temp;
	else
		repairedHead = temp;
	repairedTail = temp;
}
void traverseForward()
{
	DNode* curr = repairedHead;
	printf("\nRepaired Rovers (Forward):\n");
	while (curr != NULL) {
		printf("- %s\n", curr->name);
		curr = curr->next;
	}
}
void traverseBackward()
{
	DNode* curr = repairedTail;
	printf("\nRepaired Rovers (Backward):\n");
	while (curr != NULL) {
		printf("- %s\n", curr->name);
		curr = curr->prev;
	}
}
//  PART D
// Circular Linked List (Priority Upgrade)
struct CNode {
	char name[10];
	struct CNode* next;
};
typedef struct CNode CNode;
CNode* upgradeTail = NULL;
void insertUpgrade(char rover[])
{
	CNode* temp = (CNode*)malloc(sizeof(CNode));
	strcpy(temp->name, rover);
	if (upgradeTail == NULL) {
		temp->next = temp;
		upgradeTail = temp;
	} else {
		temp->next = upgradeTail->next;
		upgradeTail->next = temp;
		upgradeTail = temp;
	}
}
void traverseCircular(int times)
{
	if (upgradeTail == NULL) return;
	CNode* curr = upgradeTail->next;
	printf("\nPriority Upgrade Rovers:\n");
	for (int i = 0; i < times; i++) {
		printf("- %s\n", curr->name);
		curr = curr->next;
		if (curr == NULL) break;
	}
}
void main() //Main Function
{
	// Part A
	char parts[6][20] = {"Drill", "Wheel", "Camera", "Arm", "Battery", "Sonar"};
	for (int i = 0; i < 6; i++) {
		enqueue(parts[i]);
	}
	printf("Processing Parts:\n");
	char* p;
	while ((p = dequeue()) != NULL) {
		push(p);
	}
	printf("Repair Order:\n");
	while ((p = pop()) != NULL) {
		printf("- %s repaired\n", p);
	}
	// Part B
	char rovers[7][10] = {"Rov1", "Rov2", "Rov3", "Rov4", "Rov5", "Rov6", "Rov7"};
	for (int i = 0; i < 7; i++) {
		storeRover(rovers[i]);
	}
	printStorage();
	// Part C
	insertFaulty("Rov3");
	insertFaulty("Rov6");
	deleteFaulty("Rov3");
	insertRepaired("Rov3");
	traverseForward();
	traverseBackward();
	// Part D
	insertUpgrade("Rov1");
	insertUpgrade("Rov4");
	traverseCircular(4);
}

