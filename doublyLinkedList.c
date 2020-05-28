#include <stdio.h>

typedef int Datatype;

typedef struct Node{
	Datatype Data;
	struct Node* next;
	struct Node* previous;
}Node;

typedef struct {
	int NumofData;
	Node* Head;
	Node* Curr;
	Node* Tail;
}DoublyLinkedList;

void Initlist(DoublyLinkedList* list);
void Insert(DoublyLinkedList* list, Datatype data);
int PosHead(DoublyLinkedList* list, Datatype* data);
int PosNext(DoublyLinkedList* list, Datatype* data);
Datatype Delete(DoublyLinkedList* list, Datatype data);

int main() {
	int data;
	DoublyLinkedList list;
	Initlist(&list);

	Insert(&list, 1);
	Insert(&list, 2);
	Insert(&list, 3);
	Insert(&list, 4);
	Insert(&list, 5);

	if (PosHead(&list, &data)) {
		printf("%d\n", data);

		while (PosNext(&list, &data)) {
			printf("%d\n", data);
		}
	}

	Datatype deleted = Delete(&list, 5);
	printf("%d\n", deleted);

	if (PosHead(&list, &data)) {
		printf("%d\n", data);

		while (PosNext(&list, &data)) {
			printf("%d\n", data);
		}
	}
	return 0;
}

void Initlist(DoublyLinkedList* list) {
	list->Head = (Node*)malloc(sizeof(Node));
	list->NumofData = 0;
	list->Head = NULL;
	list->Curr = NULL;
	list->Tail = NULL;
}

void Insert(DoublyLinkedList* list, Datatype data) {
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->Data = data;
	if (list->Head == NULL) {
		list->Head = temp;
		list->Head->next = list->Head;
		list->Head->previous = NULL;
		list->Curr = list->Head;
	}
	else {
		temp->previous = list->Curr;
		temp->next = NULL;
		list->Curr->next = temp;
		list->Curr = temp;
	}
	list->NumofData++;
}

int PosHead(DoublyLinkedList* list, Datatype* data) {
	if (list->Head == NULL) {
		return 0;
	}
	else {
		list->Tail = list->Head;
		list->Curr = list->Head;
		*data = list->Curr->Data;
		return 1;
	}
 }

int PosNext(DoublyLinkedList* list, Datatype* data) {
	if (list->Curr->next == NULL) {
		return 0;
	}
	else {
		list->Tail = list->Curr;
		list->Curr = list->Curr->next;
		*data = list->Curr->Data;
		return 1;
	}
}


Datatype Delete(DoublyLinkedList* list, Datatype data) {

	if (list->Head == NULL) {
		return;
	}
	else {
		Datatype datum;
		if (PosHead(list, &datum)) {
			if (datum == data) {
				Node* temp = list->Curr;
				Datatype answer = temp->Data;
				list->Head = list->Curr->next;
				list->Curr->next = NULL;
				list->Curr->previous = NULL;
				list->Curr = list->Head;
				free(temp);
				list->NumofData--;
				return answer;
			}
			else {
				while (PosNext(list, &datum)) {
					if (datum == data && list->Curr->next != NULL) {
						Node* temp = list->Curr;
						Datatype answer = temp->Data;
						list->Curr->next->previous = list->Curr->previous;
						list->Curr->previous->next = list->Curr->next;
						list->Curr->next = NULL;
						list->Curr->previous = NULL;
						free(temp);
						list->NumofData--;
						return answer;
					}
					else if (datum == data && list->Curr->next == NULL) {
						Node* temp = list->Curr;
						Datatype answer = temp->Data;
						list->Curr = list->Curr->previous;
						list->Curr->next = NULL;
						free(temp);
						list->NumofData--;
						return answer;

					}
				}
			}
		}
	}
}
