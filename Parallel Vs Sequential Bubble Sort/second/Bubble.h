#include"Employee.h"
using namespace std;
void BubbleSort_Id(Employee* e2,int left, int right, int tid)
{

	for (int i = left; i < right; ++i)
	{

		for (int j = left + 1; j < right; j += 2)
		{
			if (e2[j].id < e2[j - 1].id)
			{
				Employee temp3 = e2[j];
				e2[j] = e2[j - 1];
				e2[j - 1] = temp3;
			}
		}
		for (int j = left + 2; j < right; j += 2)
		{
			if (e2[j].id < e2[j - 1].id)
			{
				Employee temp4 = e2[j];
				e2[j] = e2[j - 1];
				e2[j - 1] = temp4;
			}
		}
	}
}
void BubbleSort_Name(Employee* e2, int left, int right, int tid)
{

	for (int i = left; i < right; ++i)
	{

		for (int j = left + 1; j < right; j += 2)
		{
			if (e2[j].name < e2[j - 1].name)
			{
				Employee temp3 = e2[j];
				e2[j] = e2[j - 1];
				e2[j - 1] = temp3;
			}
		}
		for (int j = left + 2; j < right; j += 2)
		{
			if (e2[j].name < e2[j - 1].name)
			{
				Employee temp4 = e2[j];
				e2[j] = e2[j - 1];
				e2[j - 1] = temp4;
			}
		}
	}

}
void BubbleSort_Gender(Employee* e2, int left, int right, int tid)
{

	for (int i = left; i < right; ++i)
	{

		for (int j = left + 1; j < right; j += 2)
		{
			if (e2[j].gender < e2[j - 1].gender)
			{
				Employee temp3 = e2[j];
				e2[j] = e2[j - 1];
				e2[j - 1] = temp3;
			}
		}
		for (int j = left + 2; j < right; j += 2)
		{
			if (e2[j].gender < e2[j - 1].gender)
			{
				Employee temp4 = e2[j];
				e2[j] = e2[j - 1];
				e2[j - 1] = temp4;
			}
		}
	}

}
void BubbleSort_Department(Employee* e2, int left, int right, int tid)
{

	for (int i = left; i < right; ++i)
	{

		for (int j = left + 1; j < right; j += 2)
		{
			if (e2[j].department < e2[j - 1].department)
			{
				Employee temp3 = e2[j];
				e2[j] = e2[j - 1];
				e2[j - 1] = temp3;
			}
		}
		for (int j = left + 2; j < right; j += 2)
		{
			if (e2[j].department < e2[j - 1].department)
			{
				Employee temp4 = e2[j];
				e2[j] = e2[j - 1];
				e2[j - 1] = temp4;
			}
		}
	}

}
void BubbleSort_Sal(Employee* e2, int left, int right, int tid)
{

	for (int i = left; i < right; ++i)
	{

		for (int j = left + 1; j < right; j += 2)
		{
			if (e2[j].annual_salary < e2[j - 1].annual_salary)
			{
				Employee temp3 = e2[j];
				e2[j] = e2[j - 1];
				e2[j - 1] = temp3;
			}
		}
		for (int j = left + 2; j < right; j += 2)
		{
			if (e2[j].annual_salary < e2[j - 1].annual_salary)
			{
				Employee temp4 = e2[j];
				e2[j] = e2[j - 1];
				e2[j - 1] = temp4;
			}
		}
	}

}
void BubbleSort_Loc(Employee* e2, int left, int right, int tid)
{

	for (int i = left; i < right; ++i)
	{

		for (int j = left + 1; j < right; j += 2)
		{
			if (e2[j].location < e2[j - 1].location)
			{
				Employee temp3 = e2[j];
				e2[j] = e2[j - 1];
				e2[j - 1] = temp3;
			}
		}
		for (int j = left + 2; j < right; j += 2)
		{
			if (e2[j].location < e2[j - 1].location)
			{
				Employee temp4 = e2[j];
				e2[j] = e2[j - 1];
				e2[j - 1] = temp4;
			}
		}
	}

}
void BubbleSort_tenure(Employee* e2, int left, int right, int tid)
{

	for (int i = left; i < right; ++i)
	{

		for (int j = left + 1; j < right; j += 2)
		{
			if (e2[j].tenure < e2[j - 1].tenure)
			{
				Employee temp3 = e2[j];
				e2[j] = e2[j - 1];
				e2[j - 1] = temp3;
			}
		}
		for (int j = left + 2; j < right; j += 2)
		{
			if (e2[j].tenure < e2[j - 1].tenure)
			{
				Employee temp4 = e2[j];
				e2[j] = e2[j - 1];
				e2[j - 1] = temp4;
			}
		}
	}

}
void merge_Id(Employee* a, Employee* b, int l, int mid, int r) {
	int i, left_end, count, tmp_pos;
	left_end = mid - 1;
	tmp_pos = l;
	count = r - l + 1;

	// Main merge
	while ((l <= left_end) && (mid <= r)) {
		if (a[l].id <= a[mid].id) {
			b[tmp_pos] = a[l];
			tmp_pos++;
			l++;
		}
		else {
			b[tmp_pos] = a[mid];
			tmp_pos++;
			mid++;
		}
	}

	// Copy remainder of left
	while (l <= left_end) {
		b[tmp_pos] = a[l];
		l++;
		tmp_pos++;
	}

	// Copy remainder of right
	while (mid <= r) {
		b[tmp_pos] = a[mid];
		mid++;
		tmp_pos++;
	}

	// Copy temp array back to original
	for (i = 0; i < count; i++) {
		// for (i = 0; i <= count; i++) {
		a[r] = b[r];
		r--;
	}
}
void merge_name(Employee* a, Employee* b, int l, int mid, int r) {
	int i, left_end, count, tmp_pos;
	left_end = mid - 1;
	tmp_pos = l;
	count = r - l + 1;

	// Main merge
	while ((l <= left_end) && (mid <= r)) {
		if (a[l].name <= a[mid].name) {
			b[tmp_pos] = a[l];
			tmp_pos++;
			l++;
		}
		else {
			b[tmp_pos] = a[mid];
			tmp_pos++;
			mid++;
		}
	}

	// Copy remainder of left
	while (l <= left_end) {
		b[tmp_pos] = a[l];
		l++;
		tmp_pos++;
	}

	// Copy remainder of right
	while (mid <= r) {
		b[tmp_pos] = a[mid];
		mid++;
		tmp_pos++;
	}

	// Copy temp array back to original
	for (i = 0; i < count; i++) {
		// for (i = 0; i <= count; i++) {
		a[r] = b[r];
		r--;
	}
}
void merge_Gender(Employee* a, Employee* b, int l, int mid, int r) {
	int i, left_end, count, tmp_pos;
	left_end = mid - 1;
	tmp_pos = l;
	count = r - l + 1;

	// Main merge
	while ((l <= left_end) && (mid <= r)) {
		if (a[l].gender <= a[mid].gender) {
			b[tmp_pos] = a[l];
			tmp_pos++;
			l++;
		}
		else {
			b[tmp_pos] = a[mid];
			tmp_pos++;
			mid++;
		}
	}

	// Copy remainder of left
	while (l <= left_end) {
		b[tmp_pos] = a[l];
		l++;
		tmp_pos++;
	}

	// Copy remainder of right
	while (mid <= r) {
		b[tmp_pos] = a[mid];
		mid++;
		tmp_pos++;
	}

	// Copy temp array back to original
	for (i = 0; i < count; i++) {
		// for (i = 0; i <= count; i++) {
		a[r] = b[r];
		r--;
	}
}
void merge_Department(Employee* a, Employee* b, int l, int mid, int r) {
	int i, left_end, count, tmp_pos;
	left_end = mid - 1;
	tmp_pos = l;
	count = r - l + 1;

	// Main merge
	while ((l <= left_end) && (mid <= r)) {
		if (a[l].department <= a[mid].department) {
			b[tmp_pos] = a[l];
			tmp_pos++;
			l++;
		}
		else {
			b[tmp_pos] = a[mid];
			tmp_pos++;
			mid++;
		}
	}

	// Copy remainder of left
	while (l <= left_end) {
		b[tmp_pos] = a[l];
		l++;
		tmp_pos++;
	}

	// Copy remainder of right
	while (mid <= r) {
		b[tmp_pos] = a[mid];
		mid++;
		tmp_pos++;
	}

	// Copy temp array back to original
	for (i = 0; i < count; i++) {
		// for (i = 0; i <= count; i++) {
		a[r] = b[r];
		r--;
	}
}
void merge_Loc(Employee* a, Employee* b, int l, int mid, int r) {
	int i, left_end, count, tmp_pos;
	left_end = mid - 1;
	tmp_pos = l;
	count = r - l + 1;

	// Main merge
	while ((l <= left_end) && (mid <= r)) {
		if (a[l].location <= a[mid].location) {
			b[tmp_pos] = a[l];
			tmp_pos++;
			l++;
		}
		else {
			b[tmp_pos] = a[mid];
			tmp_pos++;
			mid++;
		}
	}

	// Copy remainder of left
	while (l <= left_end) {
		b[tmp_pos] = a[l];
		l++;
		tmp_pos++;
	}

	// Copy remainder of right
	while (mid <= r) {
		b[tmp_pos] = a[mid];
		mid++;
		tmp_pos++;
	}

	// Copy temp array back to original
	for (i = 0; i < count; i++) {
		// for (i = 0; i <= count; i++) {
		a[r] = b[r];
		r--;
	}
}
void merge_Sal(Employee* a, Employee* b, int l, int mid, int r) {
	int i, left_end, count, tmp_pos;
	left_end = mid - 1;
	tmp_pos = l;
	count = r - l + 1;

	// Main merge
	while ((l <= left_end) && (mid <= r)) {
		if (a[l].annual_salary <= a[mid].annual_salary) {
			b[tmp_pos] = a[l];
			tmp_pos++;
			l++;
		}
		else {
			b[tmp_pos] = a[mid];
			tmp_pos++;
			mid++;
		}
	}

	// Copy remainder of left
	while (l <= left_end) {
		b[tmp_pos] = a[l];
		l++;
		tmp_pos++;
	}

	// Copy remainder of right
	while (mid <= r) {
		b[tmp_pos] = a[mid];
		mid++;
		tmp_pos++;
	}

	// Copy temp array back to original
	for (i = 0; i < count; i++) {
		// for (i = 0; i <= count; i++) {
		a[r] = b[r];
		r--;
	}
}

void merge_Tenure(Employee* a, Employee* b, int l, int mid, int r) {
	int i, left_end, count, tmp_pos;
	left_end = mid - 1;
	tmp_pos = l;
	count = r - l + 1;

	// Main merge
	while ((l <= left_end) && (mid <= r)) {
		if (a[l].tenure <= a[mid].tenure) {
			b[tmp_pos] = a[l];
			tmp_pos++;
			l++;
		}
		else {
			b[tmp_pos] = a[mid];
			tmp_pos++;
			mid++;
		}
	}

	// Copy remainder of left
	while (l <= left_end) {
		b[tmp_pos] = a[l];
		l++;
		tmp_pos++;
	}

	// Copy remainder of right
	while (mid <= r) {
		b[tmp_pos] = a[mid];
		mid++;
		tmp_pos++;
	}

	// Copy temp array back to original
	for (i = 0; i < count; i++) {
		// for (i = 0; i <= count; i++) {
		a[r] = b[r];
		r--;
	}
}