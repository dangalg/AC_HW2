#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define HEB_YEAR_LENGTH 6

typedef struct Worker 
{
	long unsigned ID;
	char* Name;
	double Salary;
	union StartYear{
		char StartYearHeb[HEB_YEAR_LENGTH];
		unsigned int StartYearReg;
	};
} Worker;

typedef struct WorkerList
{
	Worker* data;
	struct WorkerList* next;
} WorkerList;

Worker* CreateWorker(long unsigned id, char* name, double salary, char startYearHeb[], unsigned int StartYearReg);
Worker* CreateWorker();
void PrintWorker(Worker* _worker, int _yearType);
WorkerList* addWorker(WorkerList* head, Worker* w);
int index(WorkerList* head, long unsigned id);
int indexRec(WorkerList* head, long unsigned id);
WorkerList* deleteWorstWorker(WorkerList* head);
void update_worker(WorkerList* head, float percent);


void main()
{
	//Worker* worker = CreateWorker();
}

Worker* CreateWorker(long unsigned id, char* name, double salary, char startYearHeb[], unsigned int startYearReg)
{
	Worker* worker = (Worker*)malloc(sizeof(Worker));
	worker->ID = id;
	strcpy(worker->Name, name);
	worker->Salary = salary;
	strcpy(worker->StartYearHeb, startYearHeb);
	worker->StartYearReg = startYearReg;

	return worker;
}

Worker* CreateWorker()
{
	Worker* worker = (Worker*)malloc(sizeof(Worker));
	if (!worker) { printf("Allocation Error!"); exit(1); }

	while (worker->ID <= 0)
	{
		printf("Enter Worker ID: ");
		scanf("%d", &worker->ID);
	}

	char workerName[21];
	while (strlen(workerName) <= 0 && strlen(workerName) > 20)
	{
		printf("Enter Worker Name (20 char max): ");
		fseek(stdin, 0, SEEK_END);
		scanf("%s", workerName);
	}
	worker->Name = (char*)malloc(strlen(workerName) * sizeof(char));
	if (!(worker->Name)) { printf("Allocation Error!"); exit(1); }
	strcpy(worker->Name, workerName);

	printf("Enter Worker Salary: ");
	scanf("%d", &worker->Salary);

	if (worker->Salary < 0)
	{
		worker->Salary *= -1;
	}

	int yearType = -1;
	while (yearType == 0 || yearType == 1)
	{
		printf("Please select 0 for Hebrew Year, 1 for regular year: ");
		scanf("%d", &yearType);

		if (yearType != 0 && yearType != 1)
		{
			printf("Please select only 0 or 1!\n");
		}
	}

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

void PrintWorker(Worker* _worker, int _yearType)
{
	printf("ID: %d\n", _worker->ID);
	printf("Name: %s\n", _worker->Name);
	printf("Salary: %lf\n", _worker->Salary);

	switch (_yearType)
	{
	case 0:
		printf("Hebrew Year: %s\n", _worker->StartYearHeb);
		break;
	case 1:
		printf("Regular Year: %d\n", _worker->StartYearReg);
		break;
	}
}

WorkerList* addWorker(WorkerList* head, Worker* w)
{
	WorkerList* wl = (WorkerList*)malloc(sizeof(WorkerList));
	if (!(wl)) { printf("Allocation Error!"); exit(1); }
	wl->data = w;
	wl->next = head;
	return wl;
}

int index(WorkerList* head, long unsigned id)
{
	WorkerList* tmp;
	tmp = head;
	int index = 0;
	while (tmp != NULL)
	{
		if (tmp->data->ID == id)
		{
			return index;
		}
		index++;
		tmp = tmp->next;
	}

	return -1;
}

int indexRec(WorkerList* head, long unsigned id, int index)
{
	if (head == NULL) { return -1; }
	if (head->data->ID == id) {
		return index;
	}
	indexRec(head->next, id, index + 1);
}

WorkerList* deleteWorstWorker(WorkerList* head)
{
	WorkerList* tmp;
	WorkerList* beforelowestSalaryWorker = NULL;
	WorkerList* lowestSalaryWorker = NULL;
	tmp = head;
	int index = 0;
	int lowestSalaryIndex = 0;
	double minSalary = tmp->data->Salary;
	while (tmp != NULL)
	{
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

	if (lowestSalaryIndex == 0)
	{
		WorkerList* result = lowestSalaryWorker->next;
		free(lowestSalaryWorker->data->Name);
		free(lowestSalaryWorker->data);
		free(lowestSalaryWorker);
		return result;
	}
	else 
	{
		WorkerList* result = lowestSalaryWorker->next;
		lowestSalaryWorker->next = result->next;
		free(lowestSalaryWorker->next->data->Name);
		free(lowestSalaryWorker->next->data);
		free(lowestSalaryWorker->next);
		return head;
	}
}

void update_worker(WorkerList* head, float percent)
{
	WorkerList* tmp;
	tmp = head;
	while (tmp != NULL)
	{
		tmp->data->Salary = tmp->data->Salary + tmp->data->Salary * (percent/100);
		tmp = tmp->next;
	}
}




