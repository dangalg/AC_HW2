#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

typedef struct Worker 
{
	long unsigned ID;
	char* Name;
	double Salary;
	union StartYear{
		char StartYearHeb[6];
		unsigned int StartYearReg;
	};
} Worker;

typedef struct WorkerList
{
	Worker* data;
	struct WorkerList* next;
} WorkerList;

Worker* CreateWorker();
void PrintWorker(Worker* _worker, int _yearType);

void main()
{
	Worker* worker = CreateWorker();
}

Worker* CreateWorker()
{
	Worker* worker = (Worker*)malloc(sizeof(Worker));
	if (!worker) { printf("Allocation Error!"); exit(1); }

	printf("Enter Worker ID: ");
	scanf("%d", &worker->ID);

	printf("Enter Worker Name: ");
	char workerName[20];
	fseek(stdin, 0, SEEK_END);
	scanf("%s", workerName);
	worker->Name = (char*)malloc(strlen(workerName) * sizeof(char));
	if (!(worker->Name)) { printf("Allocation Error!"); exit(1); }

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
		scanf("%s", &worker->StartYearHeb);
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

