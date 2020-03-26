#include <stdio.h>
#include <stdlib.h>

char nameArray[10][255] = { "Bob", "John", "Jerry", "Tom", "Rekcle", "Rararamanara", "Yours truly", "Aestheticname", "Hardcodedname", "Yeet" };
int idNumberArray[10] = { 8, 5, 4, 7, 6, 10, 2, 9, 3, 1 };
int markArray[10] = { 51, 75, 12, 93, 84, 14, 49, 72, 99, 71 };

typedef struct studentDetails
{
	char* name;
	int idNumber;
	int grade;
	//link pointer to build linked list
	struct studentDetails* next;
}studentDetails;

typedef struct studentDetails* ptr;

ptr CreateNode(char* name, int idNumber, int grade)
{
	ptr node = (ptr)malloc(sizeof(studentDetails));
	if (!node)
	{
		fprintf(stderr, "memory allocation error");
		exit(EXIT_FAILURE);
	}

	//Assign node details
	node->name = name;
	node->idNumber = idNumber;
	node->grade = grade;

	return node;
}

ptr HeadInsert(ptr listHead, ptr nextNode)
{
	nextNode->next = listHead;
	listHead = nextNode;
	return listHead;
}

void TailInsert(ptr listTail, ptr nextNode)
{
	nextNode->name = NULL;
	listTail->next = nextNode;
}

void LocationInsert(ptr location, ptr nextNode)
{
	nextNode->next = location->next;
	location->next = nextNode;
}

void Display(ptr list)
{
	for (int x = 0; x < 10; x++)
	{
		printf("Name: %s\nID: %d\nGrade: %d\n\n", list->name, list->idNumber, list->grade);
		list = list->next;
	}
}

void DisplayID(ptr list, int ID)
{
	for (int x = 0; x < 10; x++)
	{
		if (list->idNumber == ID)
		{
			printf("Name: %s\nID: %d\nGrade: %d\n\n", list->name, list->idNumber, list->grade);
		}

		list = list->next;
	}
}

void DisplayThresHold(ptr list, int threshold)
{
	for (int x = 0; x < 10; x++)
	{
		if (list->grade > threshold)
		{
			printf("Name: %s\nID: %d\nGrade: %d\n\n", list->name, list->idNumber, list->grade);
		}

		list = list->next;
	}
}

int Menu(ptr idList, ptr gradeList)
{
	int menuResult = 0;

	do
	{
		printf("1. Display list in order of Id's\n2. Display list in decending order of Marks\n3. Display the names, marks and rank of a person given the ID(ID must be input)\n4. Display the names and marks of all person above a thresthold marks value (threshhold input required)\n5. Exit\n\nYour selection: ");

		scanf_s("%d", &menuResult);

		printf("\n");

		if (menuResult != 1 && menuResult != 2 && menuResult != 3 && menuResult != 4 && menuResult != 5)
			printf("Please enter a valid values from 1-5!\n\n");
	} while (menuResult != 1 && menuResult != 2 && menuResult != 3 && menuResult != 4 && menuResult != 5);


	if (menuResult == 1)
		Display(idList);

	else if (menuResult == 2)
		Display(gradeList);

	else if (menuResult == 3)
	{
		int idNumber;
		printf("What ID?: ");
		scanf_s("%d", &idNumber);
		printf("\n");

		DisplayID(idList, idNumber);
	}

	else if (menuResult == 4)
	{
		int grade;
		printf("What Threshold?: ");
		scanf_s("%d", &grade);
		printf("\n");

		DisplayThresHold(idList, grade);
	}

	else if (menuResult == 5)
		exit(EXIT_SUCCESS);

	return 1;
}

int main(int argc, char** argv)
{
	int runAgain;
	do
	{
		ptr idHead = NULL;
		ptr gradeHead = NULL;
		ptr nextNode;
		ptr lastNode;

		//Create list
		for (int x = 0; x < 10; x++)
		{
			nextNode = CreateNode(nameArray[x], idNumberArray[x], markArray[x]);

			//If first set as idHead
			if (x == 0)
				idHead = nextNode;

			else if (x > 0)
			{
				lastNode = idHead;

				//Update lastNode pointer
				for (int y = 0; y < x - 1; y++)
					lastNode = lastNode->next;

				//Finds first node
				if (nextNode->idNumber < idHead->idNumber)
					idHead = HeadInsert(idHead, nextNode);

				//Finds last node
				else if (nextNode->idNumber > lastNode->idNumber)
					TailInsert(lastNode, nextNode);

				//If in middle of idHead and tail
				else if (nextNode->idNumber > idHead->idNumber&& nextNode->idNumber < lastNode->idNumber)
				{
					ptr temp = idHead;

					while (temp != NULL)
					{
						if (nextNode->idNumber > temp->idNumber&& nextNode->idNumber < temp->next->idNumber)
						{
							LocationInsert(temp, nextNode);
							break;
						}

						//Check next node
						else
							temp = temp->next;
					}
				}
			}
		}

		//Create list
		for (int x = 0; x < 10; x++)
		{
			nextNode = CreateNode(nameArray[x], idNumberArray[x], markArray[x]);

			//If first set as head
			if (x == 0)
				gradeHead = nextNode;

			else if (x > 0)
			{
				lastNode = gradeHead;

				//Update lastNode pointer
				for (int y = 0; y < x - 1; y++)
					lastNode = lastNode->next;

				//Finds first node
				if (nextNode->grade > gradeHead->grade)
					gradeHead = HeadInsert(gradeHead, nextNode);

				//Finds last node
				else if (nextNode->grade < lastNode->grade)
					TailInsert(lastNode, nextNode);

				//If in middle of head and tail
				else if (nextNode->grade < gradeHead->grade && nextNode->grade > lastNode->grade)
				{
					ptr temp = gradeHead;

					while (temp != NULL)
					{
						if (nextNode->grade < temp->grade && nextNode->grade > temp->next->grade)
						{
							LocationInsert(temp, nextNode);
							break;
						}

						//Check next node
						else
							temp = temp->next;
					}
				}
			}
		}


		runAgain = Menu(idHead, gradeHead);
	}while (runAgain == 1);

	exit(EXIT_SUCCESS);
}

