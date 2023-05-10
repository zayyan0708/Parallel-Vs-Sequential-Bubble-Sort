using namespace std;
class Employee
{
public:
	int id;
	string name, gender, department, location;
	double tenure;
	int annual_salary;
	Employee() {};
	Employee(int i, string n, string g, string d, int as, string l, double t) : id(i), name(n), gender(g), department(d), location(l), tenure(t), annual_salary(as) {};
	void getter() {
		cout << " " << id << " " << name << " " << gender << " " << department << " " << location << " " << " " << tenure << " " << annual_salary << endl;
	}
	Employee(const Employee& e) {
		id = e.id;
		name = e.name;
		gender = e.gender;
		department = e.department;
		location = e.location;
		tenure = e.tenure;
		annual_salary = e.annual_salary;
	}

};
