#include<iostream>
#include<fstream>
#include <chrono>
#include<omp.h>
#include<sstream>
#include<cstring>
#include <windows.h>
#include"Bubble.h"

using namespace std::chrono;
using namespace std;


class ThreadResult {
	int tid;
	Employee* A;
public:
	ThreadResult(){}
	void Setter(int id, Employee *B,int l,int u,string type) {
		this->tid = id;
		int j = 0;
		int size = u - l;
		A = new Employee[size];
		stringstream ss;
		ss << id;
		string s;
		ss >> s;
		string file = "File" +type+s +".txt";
		for (int i = l; i < u; i++) {
			A[j] = B[i];
			j++;
		}
		fstream fp;
		
		fp.open(file.c_str(), ios::out | ios::app);
		
		fp << tid<<endl;
		for (int i = 0; i < size; i++) {
			fp<< A[i].id << " " << A[i].name<< " " << A[i].annual_salary << " " << A[i].gender << " " << A[i].location << " " << A[i].department << " " << A[i].tenure << endl;
		}
		fp << "\nSorted Data\n";
		fp.close();
	}
};
int main()
{
	fstream st;
	st.open("SortingTime.txt",ios::out);
	cout << endl;
	int id, age;
	string name, gender, department, location;
	double tenure, annual_salary;
	int count = 0;
	Employee e1[50000];
	Employee e2[50000];
	fstream in;
	int ch;
	cout << "Choose File to Sort\n1. Data --> 2000\n2. Data --> 4000\n3. Data --> 6000\n4. Data --> 8000\n5. Data --> 10000\nEnter Data Choice -->> ";
	cin >> ch;
	if (ch == 1)
	{
		in.open("Text2000.txt");
		in.seekg(0, ios::beg);
		st << 2000<<endl;
	}
	if (ch == 2)
	{
		in.open("Text4000.txt");
		in.seekg(0, ios::beg);
		st << 4000<<endl;
	}
	if (ch == 3)
	{
		in.open("Text6000.txt");
		in.seekg(0, ios::beg);
		st << 6000<<endl;
	}
	if (ch == 4)
	{
		in.open("Text8000.txt");
		in.seekg(0, ios::beg);
		st << 8000<<endl;
	}
	if (ch == 5)
	{
		in.open("Text10000.txt");
		in.seekg(0, ios::beg);
		st << 10000<<endl;
	}
	while (in >> id >> name >> gender >> department >> annual_salary >> location >> tenure)
	{
		e1[count] = Employee(id, name, gender, department, annual_salary, location, tenure);
		count++;
	}
	in.close();
	for (int z = 0; z < count; z++)
	{
		//e1[z].getter();
		e2[z] = e1[z];
	}
	int c;
	cout << "Sort using -->\n1. ID\n2. Name\n3. Gender\n4. Department\n5. Salary\n6. Location\n7. Tenure\nEnter Choice: ";
	cin >> c;
	int nothreads;
	if(c==1)
	{
		/// <summary>
		/// Parallel Sorting Phase Start
		/// </summary>
		/// <returns></returns>
		cout << "Enter No of Threads: ";
		cin >> nothreads;
		int subarraylength = count / nothreads;
		//omp_set_num_threads(nothreads);
		Employee* result = new Employee[count];
		double start = omp_get_wtime();
		double t1, t2, t3, t4;
#pragma omp parallel num_threads(nothreads)
		{
			int tid = omp_get_thread_num();
			int l = tid * subarraylength;
			int r = l + subarraylength;
			if (tid < nothreads - 1) {
				ThreadResult t;
				double st = omp_get_wtime();
				t.Setter(tid, e1, l, r, "id");
				double en = omp_get_wtime();
				t1 = en - st;
				BubbleSort_Id(e1, l, r, tid);
				double st1 = omp_get_wtime();
				t.Setter(tid, e1, l, r, "id");
				double en1 = omp_get_wtime();
				t2 = en1 - st1;
			}
			else {
				double st2 = omp_get_wtime();
				ThreadResult t;
				t.Setter(tid, e1, l, r, "id");
				double en2 = omp_get_wtime();
				t3 = en2 - st2;
				BubbleSort_Id(e1, l, count, tid);
				double st3 = omp_get_wtime();
				t.Setter(tid, e1, l, r, "id");
				double en3 = omp_get_wtime();
				t4 = en3 - st3;
			}
#pragma omp barrier
		}
		for (int i = 1; i < nothreads - 1; i++) {
			int mid = i * subarraylength;
			merge_Id(e1, result, 0, mid, mid + subarraylength - 1);
		}
		merge_Id(e1, result, 0, (nothreads - 1) * subarraylength, count - 1);
		double end = omp_get_wtime();
		fstream pf;
		pf.open("ParallelResultOfID.txt", ios::out);
		for (int z = 0; z < count; z++) {
			pf << e1[z].id << " " << e1[z].name << " " << e1[z].annual_salary << " " << e1[z].gender << " " << e1[z].location << " " << e1[z].department << " " << e1[z].tenure << endl;
		}
		pf.close();
		cout << "\nParallel Time:  " << end - start<< endl;
		/// <summary>
		/// Parallel Sorting Phase End
		/// </summary>
		/// <returns></returns>
		double ss = omp_get_wtime();
		for (int i = 0; i < count; i++)
		{
			for (int j = i + 1; j < count; j++)
			{
				if (e2[i].id > e2[j].id)
				{
					Employee temp2;
					temp2 = e2[i];
					e2[i] = e2[j];
					e2[j] = temp2;
				}
			}
		}
		double es = omp_get_wtime();
		fstream fp;
		fp.open("SerialResultOfID.txt", ios::out);
		for (int z = 0; z < count; z++)
		{
			fp << e2[z].id << " " << e2[z].name << " " << e2[z].annual_salary << " " << e2[z].gender << " " << e2[z].location << " " << e2[z].department << " " << e2[z].tenure << endl;
		}
		cout << "\nSequential Time:  " << es - ss << endl;
		st << end - start << endl;
		st<< es - ss;
		st.close();
	}
	if (c == 2) {
		/// <summary>
		/// Parallel Sorting Phase Start
		/// </summary>
		/// <returns></returns>
		cout << "Enter No of Threads: ";
		cin >> nothreads;
		int subarraylength = count / nothreads;
		//omp_set_num_threads(nothreads);
		Employee* result = new Employee[count];
		double start = omp_get_wtime();
		double t1, t2, t3, t4;
#pragma omp parallel num_threads(nothreads)
		{
			int tid = omp_get_thread_num();
			int l = tid * subarraylength;
			int r = l + subarraylength;
			if (tid < nothreads - 1) {
				ThreadResult t;
				double st = omp_get_wtime();
				t.Setter(tid, e1, l, r, "id");
				double en = omp_get_wtime();
				t1 = en - st;
				BubbleSort_Name(e1, l, r, tid);
				double st1 = omp_get_wtime();
				t.Setter(tid, e1, l, r, "id");
				double en1 = omp_get_wtime();
				t2 = en1 - st1;
			}
			else {
				double st2 = omp_get_wtime();
				ThreadResult t;
				t.Setter(tid, e1, l, r, "id");
				double en2 = omp_get_wtime();
				t3 = en2 - st2;
				BubbleSort_Name(e1, l, count, tid);
				double st3 = omp_get_wtime();
				t.Setter(tid, e1, l, r, "id");
				double en3 = omp_get_wtime();
				t4 = en3 - st3;
			}
#pragma omp barrier
		}
		for (int i = 1; i < nothreads - 1; i++) {
			int mid = i * subarraylength;
			merge_name(e1, result, 0, mid, mid + subarraylength - 1);
		}
		merge_name(e1, result, 0, (nothreads - 1) * subarraylength, count - 1);
		double end = omp_get_wtime();
		fstream pf;
		pf.open("ParallelResultOfName.txt", ios::out);
		for (int z = 0; z < count; z++) {
			pf << e1[z].id << " " << e1[z].name << " " << e1[z].annual_salary << " " << e1[z].gender << " " << e1[z].location << " " << e1[z].department << " " << e1[z].tenure << endl;
		}
		pf.close();
		cout << "\nParallel Time:  " << end - start<< endl;
		/// <summary>
		/// Parallel Sorting Phase End
		/// </summary>
		/// <returns></returns>
		double ss = omp_get_wtime();
		for (int i = 0; i < count; i++)
		{
			for (int j = i + 1; j < count; j++)
			{
				if (e2[i].name > e2[j].name)
				{
					Employee temp2;
					temp2 = e2[i];
					e2[i] = e2[j];
					e2[j] = temp2;
				}
			}
		}
		double es = omp_get_wtime();
		fstream fp;
		fp.open("SerialResultOfName.txt", ios::out);
		for (int z = 0; z < count; z++)
		{
			fp << e2[z].id << " " << e2[z].name << " " << e2[z].annual_salary << " " << e2[z].gender << " " << e2[z].location << " " << e2[z].department << " " << e2[z].tenure << endl;
		}
		cout << "\nSequential Time:  " << es - ss << endl;
		st << end - start << endl;
		st << es - ss;
		st.close();
	}
	if(c==3)
	{
		/// <summary>
		/// Parallel Sorting Phase Start
		/// </summary>
		/// <returns></returns>
		cout << "Enter No of Threads: ";
		cin >> nothreads;
		int subarraylength = count / nothreads;
		//omp_set_num_threads(nothreads);
		Employee* result = new Employee[count];
		double start = omp_get_wtime();
		double t1, t2, t3, t4;
#pragma omp parallel num_threads(nothreads)
		{
			int tid = omp_get_thread_num();
			int l = tid * subarraylength;
			int r = l + subarraylength;
			if (tid < nothreads - 1) {
				ThreadResult t;
				double st = omp_get_wtime();
				t.Setter(tid, e1, l, r, "id");
				double en = omp_get_wtime();
				t1 = en - st;
				BubbleSort_Gender(e1, l, r, tid);
				double st1 = omp_get_wtime();
				t.Setter(tid, e1, l, r, "id");
				double en1 = omp_get_wtime();
				t2 = en1 - st1;
			}
			else {
				double st2 = omp_get_wtime();
				ThreadResult t;
				t.Setter(tid, e1, l, r, "id");
				double en2 = omp_get_wtime();
				t3 = en2 - st2;
				BubbleSort_Gender(e1, l, count, tid);
				double st3 = omp_get_wtime();
				t.Setter(tid, e1, l, r, "id");
				double en3 = omp_get_wtime();
				t4 = en3 - st3;
			}
#pragma omp barrier
		}
		for (int i = 1; i < nothreads - 1; i++) {
			int mid = i * subarraylength;
			merge_Gender(e1, result, 0, mid, mid + subarraylength - 1);
		}
		merge_Gender(e1, result, 0, (nothreads - 1) * subarraylength, count - 1);
		double end = omp_get_wtime();
		fstream pf;
		pf.open("ParallelResultOfGender.txt", ios::out);
		for (int z = 0; z < count; z++) {
			pf << e1[z].id << " " << e1[z].name << " " << e1[z].annual_salary << " " << e1[z].gender << " " << e1[z].location << " " << e1[z].department << " " << e1[z].tenure << endl;
		}
		pf.close();
		cout << "\nParallel Time:  " << end - start<< endl;
		/// <summary>
		/// Parallel Sorting Phase End
		/// </summary>
		/// <returns></returns>
		double ss = omp_get_wtime();
		for (int i = 0; i < count; i++)
		{
			for (int j = i + 1; j < count; j++)
			{
				if (e2[i].gender > e2[j].gender)
				{
					Employee temp2;
					temp2 = e2[i];
					e2[i] = e2[j];
					e2[j] = temp2;
				}
			}
		}
		fstream fp;
		fp.open("SerialResultOfGender.txt", ios::out);
		for (int z = 0; z < count; z++)
		{
			fp << e2[z].id << " " << e2[z].name << " " << e2[z].annual_salary << " " << e2[z].gender << " " << e2[z].location << " " << e2[z].department << " " << e2[z].tenure << endl;
		}
		double es = omp_get_wtime();
		cout << "\nSequential Time:  " << es - ss << endl;
		st << end - start << endl;
		st << es - ss;
		st.close();
	}
	if(c==4)
	{
		/// <summary>
		/// Parallel Sorting Phase Start
		/// </summary>
		/// <returns></returns>
		cout << "Enter No of Threads: ";
		cin >> nothreads;
		int subarraylength = count / nothreads;
		//omp_set_num_threads(nothreads);
		Employee* result = new Employee[count];
		double start = omp_get_wtime();
		double t1, t2, t3, t4;
#pragma omp parallel num_threads(nothreads)
		{
			int tid = omp_get_thread_num();
			int l = tid * subarraylength;
			int r = l + subarraylength;
			if (tid < nothreads - 1) {
				ThreadResult t;
				double st = omp_get_wtime();
				t.Setter(tid, e1, l, r, "id");
				double en = omp_get_wtime();
				t1 = en - st;
				BubbleSort_Department(e1, l, r, tid);
				double st1 = omp_get_wtime();
				t.Setter(tid, e1, l, r, "id");
				double en1 = omp_get_wtime();
				t2 = en1 - st1;
			}
			else {
				double st2 = omp_get_wtime();
				ThreadResult t;
				t.Setter(tid, e1, l, r, "id");
				double en2 = omp_get_wtime();
				t3 = en2 - st2;
				BubbleSort_Department(e1, l, count, tid);
				double st3 = omp_get_wtime();
				t.Setter(tid, e1, l, r, "id");
				double en3 = omp_get_wtime();
				t4 = en3 - st3;
			}
#pragma omp barrier
		}
		for (int i = 1; i < nothreads - 1; i++) {
			int mid = i * subarraylength;
			merge_Department(e1, result, 0, mid, mid + subarraylength - 1);
		}
		merge_Department(e1, result, 0, (nothreads - 1) * subarraylength, count - 1);
		double end = omp_get_wtime();
		fstream pf;
		pf.open("ParallelResultOfDepartment.txt", ios::out);
		for (int z = 0; z < count; z++) {
			pf << e1[z].id << " " << e1[z].name << " " << e1[z].annual_salary << " " << e1[z].gender << " " << e1[z].location << " " << e1[z].department << " " << e1[z].tenure << endl;
		}
		pf.close();
		cout << "\nParallel Time:  " << end - start<< endl;
		/// <summary>
		/// Parallel Sorting Phase End
		/// </summary>
		/// <returns></returns>
		double ss = omp_get_wtime();
		for (int i = 0; i < count; i++)
		{
			for (int j = i + 1; j < count; j++)
			{
				if (e2[i].department > e2[j].department)
				{
					Employee temp2;
					temp2 = e2[i];
					e2[i] = e2[j];
					e2[j] = temp2;
				}
			}
		}
		double es = omp_get_wtime();
		fstream fp;
		fp.open("SerialResultOfDepartment.txt", ios::out);
		for (int z = 0; z < count; z++)
		{
			fp << e2[z].id << " " << e2[z].name << " " << e2[z].annual_salary << " " << e2[z].gender << " " << e2[z].location << " " << e2[z].department << " " << e2[z].tenure << endl;
		}
		cout << "\nSequential Time:  " << es - ss << endl;
		st << end - start << endl;
		st << es - ss;
		st.close();
	}
	if(c==5)
	{
		/// <summary>
		/// Parallel Sorting Phase Start
		/// </summary>
		/// <returns></returns>
		cout << "Enter No of Threads: ";
		cin >> nothreads;
		int subarraylength = count / nothreads;
		//omp_set_num_threads(nothreads);
		Employee* result = new Employee[count];
		double start = omp_get_wtime();
		double t1, t2, t3, t4;
#pragma omp parallel num_threads(nothreads)
		{
			int tid = omp_get_thread_num();
			int l = tid * subarraylength;
			int r = l + subarraylength;
			if (tid < nothreads - 1) {
				ThreadResult t;
				double st = omp_get_wtime();
				t.Setter(tid, e1, l, r, "id");
				double en = omp_get_wtime();
				t1 = en - st;
				BubbleSort_Sal(e1, l, r, tid);
				double st1 = omp_get_wtime();
				t.Setter(tid, e1, l, r, "id");
				double en1 = omp_get_wtime();
				t2 = en1 - st1;
			}
			else {
				double st2 = omp_get_wtime();
				ThreadResult t;
				t.Setter(tid, e1, l, r, "id");
				double en2 = omp_get_wtime();
				t3 = en2 - st2;
				BubbleSort_Sal(e1, l, count, tid);
				double st3 = omp_get_wtime();
				t.Setter(tid, e1, l, r, "id");
				double en3 = omp_get_wtime();
				t4 = en3 - st3;
			}
#pragma omp barrier
		}
		for (int i = 1; i < nothreads - 1; i++) {
			int mid = i * subarraylength;
			merge_Sal(e1, result, 0, mid, mid + subarraylength - 1);
		}
		merge_Sal(e1, result, 0, (nothreads - 1) * subarraylength, count - 1);
		double end = omp_get_wtime();
		fstream pf;
		pf.open("ParallelResultOfSalary.txt", ios::out);
		for (int z = 0; z < count; z++) {
			pf << e1[z].id << " " << e1[z].name << " " << e1[z].annual_salary << " " << e1[z].gender << " " << e1[z].location << " " << e1[z].department << " " << e1[z].tenure << endl;
		}
		pf.close();
		cout << "\nParallel Time:  " << end - start << endl;
		/// <summary>
		/// Parallel Sorting Phase End
		/// </summary>
		/// <returns></returns>
		double ss = omp_get_wtime();
		for (int i = 0; i < count; i++)
		{
			for (int j = i + 1; j < count; j++)
			{
				if (e2[i].annual_salary > e2[j].annual_salary)
				{
					Employee temp2;
					temp2 = e2[i];
					e2[i] = e2[j];
					e2[j] = temp2;
				}
			}
		}
		double es = omp_get_wtime();
		fstream fp;
		fp.open("SerialResultOfSalary.txt", ios::out);
		for (int z = 0; z < count; z++)
		{
			fp << e2[z].id << " " << e2[z].name << " " << e2[z].annual_salary << " " << e2[z].gender << " " << e2[z].location << " " << e2[z].department << " " << e2[z].tenure << endl;
		}
		cout << "\nSequential Time:  " << es - ss << endl;
		st << end - start << endl;
		st << es - ss;
		st.close();
	}
	if (c == 6)
	{
		/// <summary>
		/// Parallel Sorting Phase Start
		/// </summary>
		/// <returns></returns>
		cout << "Enter No of Threads: ";
		cin >> nothreads;
		int subarraylength = count / nothreads;
		//omp_set_num_threads(nothreads);
		Employee* result = new Employee[count];
		double start = omp_get_wtime();
		double t1, t2, t3, t4;
#pragma omp parallel num_threads(nothreads)
		{
			int tid = omp_get_thread_num();
			int l = tid * subarraylength;
			int r = l + subarraylength;
			if (tid < nothreads - 1) {
				ThreadResult t;
				double st = omp_get_wtime();
				t.Setter(tid, e1, l, r, "id");
				double en = omp_get_wtime();
				t1 = en - st;
				BubbleSort_Loc(e1, l, r, tid);
				double st1 = omp_get_wtime();
				t.Setter(tid, e1, l, r, "id");
				double en1 = omp_get_wtime();
				t2 = en1 - st1;
			}
			else {
				double st2 = omp_get_wtime();
				ThreadResult t;
				t.Setter(tid, e1, l, r, "id");
				double en2 = omp_get_wtime();
				t3 = en2 - st2;
				BubbleSort_Loc(e1, l, count, tid);
				double st3 = omp_get_wtime();
				t.Setter(tid, e1, l, r, "id");
				double en3 = omp_get_wtime();
				t4 = en3 - st3;
			}
#pragma omp barrier
		}
		for (int i = 1; i < nothreads - 1; i++) {
			int mid = i * subarraylength;
			merge_Loc(e1, result, 0, mid, mid + subarraylength - 1);
		}
		merge_Loc(e1, result, 0, (nothreads - 1) * subarraylength, count - 1);
		double end = omp_get_wtime();
		fstream pf;
		pf.open("ParallelResultOfLocations.txt", ios::out);
		for (int z = 0; z < count; z++) {
			pf << e1[z].id << " " << e1[z].name << " " << e1[z].annual_salary << " " << e1[z].gender << " " << e1[z].location << " " << e1[z].department << " " << e1[z].tenure << endl;
		}
		pf.close();
		cout << "\nParallel Time:  " << end - start << endl;
		/// <summary>
		/// Parallel Sorting Phase End
		/// </summary>
		/// <returns></returns>
		double ss = omp_get_wtime();
		for (int i = 0; i < count; i++)
		{
			for (int j = i + 1; j < count; j++)
			{
				if (e2[i].location > e2[j].location)
				{
					Employee temp2;
					temp2 = e2[i];
					e2[i] = e2[j];
					e2[j] = temp2;
				}
			}
		}
		double es = omp_get_wtime();
		fstream fp;
		fp.open("SerialResultOfLocation.txt", ios::out);
		for (int z = 0; z < count; z++)
		{
			fp << e2[z].id << " " << e2[z].name << " " << e2[z].annual_salary << " " << e2[z].gender << " " << e2[z].location << " " << e2[z].department << " " << e2[z].tenure << endl;
		}
		cout << "\nSequential Time:  " << es - ss << endl;
		fp.close();
		st << end - start << endl;
		st << es - ss;
		st.close();
	}
	if (c == 7) 
	{ 
		/// <summary>
		/// Parallel Sorting Phase Start
		/// </summary>
		/// <returns></returns>
		cout << "Enter No of Threads: ";
		cin >> nothreads;
		int subarraylength = count / nothreads;
		//omp_set_num_threads(nothreads);
		Employee* result = new Employee[count];
		double start = omp_get_wtime();
		double t1, t2, t3, t4;
#pragma omp parallel num_threads(nothreads)
		{
			int tid = omp_get_thread_num();
			int l = tid * subarraylength;
			int r = l + subarraylength;
			if (tid < nothreads - 1) {
				ThreadResult t;
				double st = omp_get_wtime();
				t.Setter(tid, e1, l, r, "id");
				double en = omp_get_wtime();
				t1 = en - st;
				BubbleSort_tenure(e1, l, r, tid);
				double st1 = omp_get_wtime();
				t.Setter(tid, e1, l, r, "id");
				double en1 = omp_get_wtime();
 				t2 = en1 - st1;
			}
			else {
				double st2 = omp_get_wtime();
				ThreadResult t;
				t.Setter(tid, e1, l, r, "id");
				double en2 = omp_get_wtime();
				t3 = en2 - st2;
				BubbleSort_tenure(e1, l, count, tid);
				double st3 = omp_get_wtime();
				t.Setter(tid, e1, l, r, "id");
				double en3 = omp_get_wtime();
				t4 = en3 - st3;
			}
#pragma omp barrier
		}
		for (int i = 1; i < nothreads - 1; i++) {
			int mid = i * subarraylength;
			merge_Tenure(e1, result, 0, mid, mid + subarraylength - 1);
		}
		merge_Tenure(e1, result, 0, (nothreads - 1) * subarraylength, count - 1);
		double end = omp_get_wtime();
		fstream pf;
		pf.open("ParallelResultOfTenure.txt", ios::out);
		for (int z = 0; z < count; z++) {
			pf << e1[z].id << " " << e1[z].name << " " << e1[z].annual_salary << " " << e1[z].gender << " " << e1[z].location << " " << e1[z].department << " " << e1[z].tenure << endl;
		}
		pf.close();
		cout << "\nParallel Time:  " << end - start<< endl;
		/// <summary>
		/// Parallel Sorting Phase End
		/// </summary>
		/// <returns></returns>
		double ss = omp_get_wtime();
		for (int i = 0; i < count; i++)
		{
			for (int j = i + 1; j < count; j++)
			{
				if (e2[i].tenure > e2[j].tenure)
				{
					Employee temp2;
					temp2 = e2[i];
					e2[i] = e2[j];
					e2[j] = temp2;
				}
			}
		}
		fstream fp;
		fp.open("SerialResultOfTenure.txt", ios::out);
		double es = omp_get_wtime();
		for (int z = 0; z < count; z++)
		{
			fp << e2[z].id << " " << e2[z].name << " " << e2[z].annual_salary << " " << e2[z].gender << " " << e2[z].location << " " << e2[z].department << " " << e2[z].tenure << endl;
		}
		cout << "\nSequential Time:  " << es - ss << endl;
		fp.close();
		st << end - start << endl;
		st << es - ss;
		st.close();
	}
}