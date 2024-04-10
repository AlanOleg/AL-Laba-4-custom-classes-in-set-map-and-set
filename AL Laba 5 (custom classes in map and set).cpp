#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <unordered_set>
using namespace std;

class Credit {
private:
	string name;
	int sum;
	string currency;
	int annual_rate;
public:
	Credit();
	Credit(string name, int sum, string currency, int annual_rate);
	Credit(const Credit& Credit_copied);
	bool operator<(const Credit& Credit2) const {
		return annual_rate < Credit2.annual_rate;
	};
	bool operator==(const Credit& Credit2) const {
		return name == Credit2.name && sum == Credit2.sum && currency == Credit2.currency && annual_rate == Credit2.annual_rate;
	};
	friend ostream& operator<<(ostream& os, const Credit& Credit);
	friend istream& operator>>(istream& is, Credit& Credit);
	friend struct Credit_Hasher;
};

Credit::Credit() {
	this->name = "";
	this->sum = 0;
	this->currency = "";
	this->annual_rate = 0;
};

Credit::Credit(string name, int sum, string currency, int annual_rate) {
	this->name = name;
	this->sum = sum;
	this->currency = currency;
	this->annual_rate = annual_rate;
};

Credit::Credit(const Credit& Credit_copied) {
	this->name = Credit_copied.name;
	this->sum = Credit_copied.sum;
	this->currency = Credit_copied.currency;
	this->annual_rate = Credit_copied.annual_rate;
};

ostream& operator<<(ostream& os, const Credit& Credit) {
	fstream file("output.txt", fstream::app);
	if (file.is_open()) {
		file << Credit.name << ' ' << Credit.sum << ' ' << Credit.currency << ' ' << Credit.annual_rate << endl;
	}
	else {
		cout << "Output file didn't open." << endl;
	}
	os << Credit.name << ' ' << Credit.sum << ' ' << Credit.currency << ' ' << Credit.annual_rate << '%' << endl;
	return os;
};

istream& operator>>(istream& is, Credit& Credit) {
	is >> Credit.name;
	is >> Credit.sum;
	is >> Credit.currency;
	is >> Credit.annual_rate;
	return is;
};

struct Credit_Hasher {
	hash<string> shash1;
	hash<int> ihash1;
	hash<string> shash2;
	hash<int> ihash2;
	size_t operator()(const Credit& ob) const
	{
		const size_t coef = 2'946'901;
		return (
			coef * coef * coef * shash1(ob.name) +
			coef * coef * ihash1(ob.sum) +
			coef * shash2(ob.currency) +
			ihash2(ob.annual_rate)
			);
	}
};

int main() {
	ofstream file_output("output.txt");
	file_output.close();
	ifstream file_input("input.txt");

	vector<Credit> Credits_vector;
	string line;
	while (getline(file_input, line)) {
		istringstream ss(line);
		Credit to_vector;
		ss >> to_vector;
		Credits_vector.push_back(to_vector);
	}

	cout << "Vector before sorting: " << endl;
	for (int i = 0; i < Credits_vector.size(); ++i) {
		cout << Credits_vector[i];
	}cout << endl;

	cout << "Set copied from vector: " << endl;
	set<Credit> Credits_set;
	for (int i = 0; i < Credits_vector.size(); ++i) {
		Credits_set.insert(Credits_vector[i]);
	}
	for (const auto &i: Credits_set) {
		cout << i;
	}cout << endl;

	cout << "Unordered_set copied from vector: " << endl;
	unordered_set<Credit, Credit_Hasher> Credits_unordered_set;
	for (int i = 0; i < Credits_vector.size(); ++i) {
		Credits_unordered_set.insert(Credits_vector[i]);
	}
	for (const auto &i: Credits_unordered_set) {
		cout << i;
	}cout << endl;
}