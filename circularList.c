#include <stdio.h>
#include <malloc.h>

typedef int Datatype;

typedef struct Node {
	Datatype Data;
	struct Node* next;
	struct Node* previous;
}Node;

typedef struct {
	int NumofData;
	Node* Head;
	Node* Curr;
}CircularLinkedList;

void Initlist(CircularLinkedList* list);
void Insert(CircularLinkedList* list, Datatype data);
Datatype PosHead(CircularLinkedList* list);
Datatype PosNext(CircularLinkedList* list);
Datatype Delete(CircularLinkedList* list, Datatype data);
int RetNumofData(CircularLinkedList* list);

int main() {
	int count;
	CircularLinkedList list;
	Initlist(&list);

	Insert(&list, 1);
	Insert(&list, 2);
	Insert(&list, 3);
	Insert(&list, 4);
	Insert(&list, 5);

	count = RetNumofData(&list);

	printf("%d\n", PosHead(&list));

	for (int i = 0; i < count - 1; i++) {
		printf("%d\n", PosNext(&list));
	}

	Datatype deleted = Delete(&list, 5);
	printf("%d\n", deleted);

	count = RetNumofData(&list);

	printf("%d\n", PosHead(&list));

	for (int i = 0; i < count - 1; i++) {
		printf("%d\n", PosNext(&list));
	}

	return 0;
}

void Initlist(CircularLinkedList* list) {
	list->Head = (Node*)malloc(sizeof(Node));
	list->NumofData = 0;
	list->Head = NULL;
	list->Curr = NULL;
}

void Insert(CircularLinkedList* list, Datatype data) {
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->Data = data;
	if (list->Head == NULL) {
		list->Head = temp;
		list->Head->next = list->Head;
		list->Head->previous = list->Head;
		list->Curr = list->Head;
	}
	else {
		temp->previous = list->Curr;
		temp->next = list->Head;
		list->Curr->next = temp;
		list->Head->previous = temp;
		list->Curr = temp;
	}
	list->NumofData++;
}

Datatype PosHead(CircularLinkedList* list) {
	list->Curr = list->Head;
	Node* temp = list->Head;
	return temp->Data;
}

Datatype PosNext(CircularLinkedList* list) {
	list->Curr = list->Curr->next;
	Node* temp = list->Curr;
	return temp->Data;
}

Datatype Delete(CircularLinkedList* list, Datatype data) {

	if (list->Head == NULL) {
		return;
	}
	else {
		Datatype datum;
		int count = 0;
		while (1) {
			if (PosHead(list) == data) {
				list->Head->previous->next = list->Head->next;
				list->Head->next->previous = list->Head->previous;
				list->Head = list->Head->next;
				list->NumofData--;
				return data;
			}
			else {
				count++;
				while (PosNext(list) != data) {
					count++;
					if (count >= list->NumofData) {
						return 0;
					}
				}
				list->Curr->previous->next = list->Curr->next;
				list->Curr->next->previous = list->Curr->previous;
				list->Curr = list->Curr->next;
				list->NumofData--;
				return data;
			}
		}
	}
}

int RetNumofData(CircularLinkedList* list) {
	return list->NumofData;
}