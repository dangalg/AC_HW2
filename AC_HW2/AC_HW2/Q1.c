#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define HEB_YEAR_LENGTH 6
#define NAME_SIZE 21


// structs
typedef struct Worker 
{
	long unsigned ID;
	char* Name;
	double Salary;
	union StartYear{
		char StartYearHeb[HEB_YEAR_LENGTH];
		unsigned int StartYearReg;
	};
	int YearType;
} Worker;

typedef struct WorkerList
{
	Worker* data;
	struct WorkerList* next;
} WorkerList;

// functions
Worker* CreateWorkerFromUser();
Worker* CreateWorker(long unsigned id, char* name, double salary, char startYearHeb[], unsigned int startYearReg, int yearType);
void PrintWorker(Worker* _worker, int _yearType);
WorkerList* addWorker(WorkerList* head, Worker* w);
int index(WorkerList* head, long unsigned id);
int indexRec(WorkerList* head, long unsigned id, int index);
WorkerList* deleteWorstWorker(WorkerList* head);
void update_worker(WorkerList* head, float percent);
WorkerList* reverse(WorkerList* head);
void freeWorker(WorkerList* wl);
void freeWorkers(WorkerList* head);
void PrintWorkers(WorkerList* head);

void main()
{
	// Add workers to list
	WorkerList* head = addWorker(NULL, CreateWorker(12345, "dan", 5000.0, "sdfd", 2022, 0));
	head = addWorker(head, CreateWorker(234567, "neev", 20000, "sdfd", 2021, 1));
	head = addWorker(head, CreateWorker(345678, "ben", 3000, "dfdf", 2020, 1));
	head = addWorker(head, CreateWorker(456789, "lior", 9000, "dfgg", 1999, 0));
	head = addWorker(head, CreateWorker(567890, "sapir", 5500.6, "gere", 2004, 1));

	// Reveal this to Create worker from user data
	// and hide the creation from parameters
	/*int numberOfWorkers = 0;

	while (numberOfWorkers <= 0)
	{
		printf("How many workers do you want to add?\n");
		scanf("%d", &numberOfWorkers);
	}

	printf("\nEnter worker number 1\n");
	WorkerList* head = addWorker(NULL, CreateWorkerFromUser());

	for (int i = 0; i < numberOfWorkers-1; i++)
	{
		printf("\nEnter worker number %d\n", i+2);
		head = addWorker(head, CreateWorkerFromUser());
	}*/

	// print workers list
	printf("regular workers\n");
	PrintWorkers(head);

	// delete the worker with lowest income
	head = deleteWorstWorker(head);
	printf("\ndeleted worker\n");
	PrintWorkers(head);

	// update workers salary
	int salaryUpdatePercent = 15;
	update_worker(head, salaryUpdatePercent);
	printf("\nupdated workers salary by %d percent\n", salaryUpdatePercent);
	PrintWorkers(head);

	// reverse the workers list
	head = reverse(head);
	printf("\nreverse workers\n");
	PrintWorkers(head);

	// get index for specific id
	int workerIndex = 234567;
	printf("\nindex for %d\n", workerIndex);
	printf("%d", index(head, workerIndex));

	// get index for specific id recusively
	workerIndex = 456789;
	printf("\nindex rec %d\n", workerIndex);
	printf("%d", indexRec(head, workerIndex, 0));

	// free workers from memory
	freeWorkers(head);
}

/// <summary>
/// Print workers
/// </summary>
/// <param name="head">The head of the linked list</param>
void PrintWorkers(WorkerList* head)
{
	//print all workers
	WorkerList* tmp = head;
	while (tmp != NULL)
	{
		PrintWorker(tmp->data, 1);
		tmp = tmp->next;
	}
}

/// <summary>
/// Create a worker from data
/// </summary>
/// <param name="id">workers id</param>
/// <param name="name">workers name</param>
/// <param name="salary">workers salary</param>
/// <param name="startYearHeb">hebrew start year</param>
/// <param name="startYearReg">regular start year</param>
/// <param name="yearType">0 for hebrew year, 1 for regular year</param>
/// <returns>Worker from parameters</returns>
Worker* CreateWorker(long unsigned id, char* name, double salary, char startYearHeb[], unsigned int startYearReg, int yearType)
{
	// allocate memory for worker
	Worker* worker = (Worker*)malloc(sizeof(Worker));
	if (!worker) { printf("Allocation Error!"); exit(1); }

	// insert data into worker
	worker->ID = id;
	// allocate memory for name
	worker->Name = (char*)malloc((strlen(name) + 1) * sizeof(char));
	if (!worker->Name) { printf("Allocation Error!"); exit(1); }
	strcpy(worker->Name, name);
	worker->Salary = salary;
	worker->YearType = yearType;
	if (yearType)
	{
		worker->StartYearReg = startYearReg;
	}
	else
	{
		strcpy(worker->StartYearHeb, startYearHeb);
	}
	

	return worker;
}


/// <summary>
/// Create worker from user data
/// </summary>
/// <returns>Worker from user data</returns>
Worker* CreateWorkerFromUser()
{
	// allocate memory for user
	Worker* worker = (Worker*)malloc(sizeof(Worker));
	if (!worker) { printf("Allocation Error!"); exit(1); }

	// get worker data from user

	worker->ID = 0;
	while (worker->ID <= 0)
	{
		printf("Enter Worker ID: ");
		scanf("%d", &worker->ID);
	}

	char workerName[NAME_SIZE] = "\0";
	while (strlen(workerName) <= 0 || strlen(workerName) > NAME_SIZE - 1)
	{
		printf("Enter Worker Name (%d char max): ", NAME_SIZE - 1);
		fseek(stdin, 0, SEEK_END);
		scanf("%s", workerName);
	}
	worker->Name = (char*)malloc((strlen(workerName)+1) * sizeof(char));
	if (!(worker->Name)) { printf("Allocation Error!"); exit(1); }
	strcpy(worker->Name, workerName);

	printf("Enter Worker Salary: ");
	scanf("%lf", &worker->Salary);

	if (worker->Salary < 0)
	{
		worker->Salary *= -1;
	}

	int yearType = -1;
	while (yearType < 0 || yearType > 1)
	{
		printf("Please select 0 for Hebrew Year, 1 for regular year: ");
		scanf("%d", &yearType);

		if (yearType < 0 || yearType > 1)
		{
			printf("Please select only 0 or 1!\n");
		}
	}

	worker->YearType = yearType;

	switch (yearType)
	{
	case 0:
		printf("Enter Worker Hebrew Start Year: ");
		fseek(stdin, 0, SEEK_END);
		scanf("%s", worker->StartYearHeb);
		break;
	case 1:
		printf("Enter Worker Regular Start Year: ");
		scanf("%d", &worker->StartYearReg);
		break;
	}
	
	return worker;
}

/// <summary>
/// Print all workers data
/// </summary>
/// <param name="_worker">Worker to print</param>
void PrintWorker(Worker* _worker)
{
	printf("ID: %d ", _worker->ID);
	printf("Name: %s ", _worker->Name);
	printf("Salary: %.2lf ", _worker->Salary);

	switch (_worker->YearType)
	{
	case 0:
		printf("Hebrew Year: %s", _worker->StartYearHeb);
		break;
	case 1:
		printf("Regular Year: %d", _worker->StartYearReg);
		break;
	}
	printf("\n");
}

/// <summary>
/// Add worker to the list by order of lowest salary first
/// </summary>
/// <param name="head">Head of linked list</param>
/// <param name="w">Worker to add</param>
/// <returns>Head of linked list</returns>
WorkerList* addWorker(WorkerList* head, Worker* w)
{
	// if list is empty
	if (head == NULL)
	{
		// create a new head for the list and return it
		head = (WorkerList*)malloc(sizeof(WorkerList));
		if (head) 
		{
			head->data = w;
			head->next = NULL;
			return head;
		}
		else 
		{
			printf("Allocation Error!"); exit(1);
		}
	}
	// if list is not empty
	else 
	{
		// use workers to go through list
		WorkerList* tmp = head;
		WorkerList* lastWorker = NULL;
		// allocate memory for list item
		WorkerList* wl = (WorkerList*)malloc(sizeof(WorkerList));
		if (!(wl)) { printf("Allocation Error!"); exit(1); }
		// add worker data to list item
		wl->data = w;

		// if the salary is lower than the head, enter worker before the head and return it as new head
		if (w->Salary <= tmp->data->Salary)
		{
			wl->next = head;
			return wl;
		}
		// else insert the worker in the correct place in the list according to its salary, by order of lowest salary first
		else
		{
			// store last worker
			lastWorker = tmp;
			// move to next worker
			tmp = tmp->next;
			int foundPlaceToInsert = 0;
			// run until either found a place to insert or reached end of list
			while (tmp != NULL && foundPlaceToInsert == 0)
			{
				// if salary is smaller then item salary, insert worker before this item
				if (w->Salary <= tmp->data->Salary)
				{
					foundPlaceToInsert = 1;
				}
				else
				{
					// advance worker
					lastWorker = tmp;
					tmp = tmp->next;
				}
			}
			// connect worker to next worker
			wl->next = lastWorker->next;
			// connect last worker to this worker
			lastWorker->next = wl;

			// return original head
			return head;
		}
	}
}

/// <summary>
/// return index of worker in list by id
/// </summary>
/// <param name="head">head of linked list</param>
/// <param name="id">workers id</param>
/// <returns>index of worker in list, else return -1</returns>
int index(WorkerList* head, long unsigned id)
{
	WorkerList* tmp;
	tmp = head;
	int index = 0;
	// run through list
	while (tmp != NULL)
	{
		// if found correct id, return worker
		if (tmp->data->ID == id)
		{
			return index;
		}
		index++;
		tmp = tmp->next;
	}

	// if not found return -1
	return -1;
}

/// <summary>
/// return index of worker in list by id recursive function
/// </summary>
/// <param name="head">head of linked list</param>
/// <param name="id">workers id</param>
/// <param name="index">index parameter to return</param>
/// <returns>index of worker in list, else return -1</returns>
int indexRec(WorkerList* head, long unsigned id, int index)
{
	//run through list recursively 
	if (head == NULL) { return -1; }
	if (head->data->ID == id) {
		// return index
		return index;
	}
	//check next item
	indexRec(head->next, id, index + 1);
}

/// <summary>
/// Delete worker with lowest salary
/// </summary>
/// <param name="head">head of linked list</param>
/// <returns>Head of linked list</returns>
WorkerList* deleteWorstWorker(WorkerList* head)
{
	// create workers to run through
	WorkerList* tmp;
	WorkerList* beforelowestSalaryWorker = NULL;
	WorkerList* lowestSalaryWorker = NULL;
	tmp = head;
	int index = 0;
	int lowestSalaryIndex = 0;

	// save first worker and salary
	double minSalary = tmp->data->Salary;
	lowestSalaryWorker = tmp;

	while (tmp != NULL)
	{
		// if salary is smaller than minimum salary, save worker as worker to delete
		if (tmp->data->Salary < minSalary)
		{
			minSalary = tmp->data->Salary;
			lowestSalaryIndex = index;
			lowestSalaryWorker = beforelowestSalaryWorker;
		}
		beforelowestSalaryWorker = tmp;
		index++;
		tmp = tmp->next;
	}

	// if worker to delete is first in the list
	if (lowestSalaryIndex == 0)
	{
		// return next worker as new head
		WorkerList* result = lowestSalaryWorker->next;
		// free old head
		freeWorker(lowestSalaryWorker);
		return result;
	}
	else 
	{
		// connect next worker to worker before worker to delete
		WorkerList* result = lowestSalaryWorker->next;
		lowestSalaryWorker->next = result->next;
		// free worker to delete
		freeWorker(result);
		// return original head
		return head;
	}
}

/// <summary>
/// update workers salary by percent
/// </summary>
/// <param name="head">head of linked list</param>
/// <param name="percent">percent to raise by</param>
void update_worker(WorkerList* head, float percent)
{
	WorkerList* tmp;
	tmp = head;
	// run though list
	while (tmp != NULL)
	{
		// update workers salary by said percent
		tmp->data->Salary = tmp->data->Salary + tmp->data->Salary * (percent/100);
		tmp = tmp->next;
	}
}

/// <summary>
/// reverse workers list
/// </summary>
/// <param name="head">head of linked list</param>
/// <returns>head of linked list</returns>
WorkerList* reverse(WorkerList* head)
{
	WorkerList* tmp;
	WorkerList* previousWorker;
	WorkerList* nextWorker;
	tmp = head;
	previousWorker = NULL;

	// run through workers
	while (tmp != NULL)
	{
		// save next worker
		nextWorker = tmp->next;
		// connect current worker to previous worker
		tmp->next = previousWorker;
		// save previous worker
		previousWorker = tmp;
		// save current worker
		tmp = nextWorker;
	}

	return previousWorker;
}

/// <summary>
/// free all workers
/// </summary>
/// <param name="head">head of linked list</param>
void freeWorkers(WorkerList* head) 
{
	WorkerList* tmp;
	WorkerList* releaseWorker;
	tmp = head;
	while (tmp != NULL)
	{
		// save worker to free
		releaseWorker = tmp;
		// move to next worker
		tmp = tmp->next;
		// free saved worker
		freeWorker(releaseWorker);
	}
}

/// <summary>
/// free one workerList item
/// </summary>
/// <param name="wl"></param>
void freeWorker(WorkerList* wl)
{
	free(wl->data->Name);
	free(wl->data);
	free(wl);
}


