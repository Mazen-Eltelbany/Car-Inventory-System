#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include <fstream>
using namespace std;
#define e endl;
const string originalcarsfilename = "Data/orgcars.txt";
const string usedcarsfilename = "Data/Usedcars.txt";
enum enmainmenu {
	enshowallorginalcarsdetails = 1,
	enshowallusedcarsdetails = 2,
	enaddneworginalcars,
	enaddnewusedcars,
	endeleteorginalcar,
	endeleteusedcars,
	encomparebetweentwousedcars,
};
void showmainmenu();
void gobacktomainmenu() {
	cout << "\nPress any Key to return to main menu...\n";
	system("pause>0");
	showmainmenu();
}
enmainmenu readchoicefrommainmenu() {
	int n;
	do {
		cout << "Enter Your choice [1 to 8]? ";
		cin >> n;
	} while (1 > n || n > 8);
	return (enmainmenu)n;
}
class clscars {
	struct sorgcars {
		string brand;
		string model;
		int year = 0;
		int motorpower = 0;
		int moneyrangestart = 0;
		int moneyrangeend = 0;
		bool markfordelete = false;
	};
	struct susedcars {
		string brand;
		string model;
		int year = 0;
		int distance = 0;
		int price = 0;
		bool markfordelete = false;
	};

public:
	vector<string>splitstring(string s, string sep = "#//#") {
		vector<string>vs;
		string word = " ";
		int pos = 0;
		while (((pos = s.find(sep)) != string::npos)) {
			word = s.substr(0, pos);
			if (word != " ") {
				vs.push_back(word);
			}
			s.erase(0, pos + sep.length());
		}
		if (!s.empty()) {
			vs.push_back(s);
		}
		return vs;
	}
	bool findcarsbybrandandmodel(string carbrand, string carmodel, vector<susedcars>vc, susedcars& car) {
		for (susedcars& c : vc) {
			if (c.brand == carbrand && c.model == carmodel) {
				car = c;
				return true;
			}
		}
		return false;
	}
	string readcarbrand() {
		string carbrand;
		cout << "\nEnter Car Brand? ";
		cin >> carbrand;
		return carbrand;
	}
	string readcarmodel() {
		string carmodel;
		cout << "Enter Car Model? ";
		cin >> carmodel;
		return carmodel;
	}
	int readcaryear() {
		int year;
		cout << "Enter Car Year? ";
		cin >> year;
		return year;
	}
	int readcardistance() {
		int distance;
		cout << "Enter Car Distance? ";
		cin >> distance;
		return distance;
	}
	void adddatalinetofile(string filename, string dataline) {
		fstream file;
		file.open(filename, ios::app | ios::out);
		if (file.is_open()) {
			file << dataline << e;
		}
	}
	sorgcars linetorecordogcar(string line, string sep = "#//#") {
		sorgcars car;
		vector<string>vs = splitstring(line);
		if (vs.size() >= 6) {
			car.brand = vs[0];
			car.model = vs[1];
			car.year = stoi(vs[2]);
			car.motorpower = stoi(vs[3]);
			car.moneyrangestart = stoi(vs[4]);
			car.moneyrangeend = stoi(vs[5]);
		}
		return car;
	}
	vector<sorgcars> getcarsfromfileogcars(string filename) {
		vector<sorgcars>vc;
		fstream file(filename, ios::in);
		if (file.is_open()) {
			string line;
			while (getline(file, line)) {
				vc.push_back(linetorecordogcar(line));
			}
			file.close();
		}
		return vc;
	}
	int getmotorpower(string brandcar, string carmodel, int caryear) {
		vector<sorgcars>vc = getcarsfromfileogcars(originalcarsfilename);
		for (sorgcars& c : vc) {
			if (c.brand == brandcar && c.model == carmodel && c.year == caryear) {
				return c.motorpower;
			}
		}
	}
};
class clsusedcars :public clscars {
	struct susedcars {
		string brand;
		string model;
		int year = 0;
		int distance = 0;
		int price = 0;
		bool markfordelete = false;
	};
public:
	susedcars readnewusedcars(string carbrand, string carmodel, int caryear, int cardistance) {
		susedcars car;
		car.brand = carbrand;
		car.model = carmodel;
		car.year = caryear;
		car.distance = cardistance;
		cout << "Enter Car Price? ";
		cin >> car.price;

		return car;
	}
	susedcars linetorecordusedcar(string line, string sep = "#//#") {
		susedcars car;
		vector<string>vs = clscars::splitstring(line);
		if (vs.size() >= 5) {
			car.brand = vs[0];
			car.model = vs[1];
			car.year = stoi(vs[2]);
			car.distance = stoi(vs[3]);
			car.price = stoi(vs[4]);
		}

		return car;
	}
	string recordtolineusedcars(susedcars car, string sep = "#//#") {
		string s = car.brand + sep + car.model + sep + to_string(car.year)
			+ sep + to_string(car.distance) + sep + to_string(car.price) + sep;
		return s;
	}
	vector<susedcars> getcarsfromfileusedcars(string filename) {
		vector<susedcars>vc;
		fstream file;
		file.open(filename, ios::in);
		if (file.is_open()) {
			string line;
			while (getline(file, line)) {
				vc.push_back(linetorecordusedcar(line));
			}
			file.close();
		}
		return vc;
	}
	bool findcarsbybrandandmodelandyearanddistanceusedcars(string carbrand, string carmodel, int year, int distance, vector<susedcars>vc, susedcars& car) {
		for (susedcars& c : vc) {
			if (c.brand == carbrand && c.model == carmodel && c.year == year && c.distance == distance) {
				car = c;
				return true;
			}
		}
		return false;
	}
	bool markusedcarsfordelete(string carbrand, string carmodel, int year, int distance, vector<susedcars>& vc) {
		for (susedcars& c : vc) {
			if (c.brand == carbrand && c.model == carmodel && c.year == year && c.distance == distance) {
				c.markfordelete = true;
				return true;
			}
		}
		return false;
	}
	vector<susedcars>saveusedcarsdatatofile(string filename, vector<susedcars>vc) {
		fstream file;
		file.open(filename, ios::out);
		if (file.is_open()) {
			for (susedcars& c : vc) {
				if (!c.markfordelete) {
					file << recordtolineusedcars(c) << e;
				}
			}
		}
		return vc;
	}
	void printusedcarscard(susedcars car) {
		cout << "|" << setw(15) << left << car.brand;
		cout << "|" << setw(15) << left << car.model;
		cout << "|" << setw(15) << left << car.year;
		cout << "|" << setw(17) << left << to_string(car.distance) + "KM";
		cout << "|" << setw(16) << left << to_string(car.price) + " EGP";
	}
	void printusedcarsdetails(susedcars car) {
		cout << "\nThe following are the car details:\n";
		cout << "==========================================\n";
		cout << "Car Brand      : " << car.brand << e;
		cout << "Car Model      : " << car.model << e;
		cout << "Car Year       : " << car.year << e;
		cout << "Car Distance   :" << car.distance << "KM" << e;
		cout << "Car Price " << car.price << " EGP" << e;
		cout << "===========================================\n";
	}
	bool deleteusedcarbybrandandmodelandyearanddistance(vector<susedcars>vc) {
		susedcars car;
		string carbrand = clscars::readcarbrand();
		string carmodel = clscars::readcarmodel();
		int caryear = clscars::readcaryear();
		int cardistance = clscars::readcardistance();
		if (findcarsbybrandandmodelandyearanddistanceusedcars(carbrand, carmodel, caryear, cardistance, vc, car)) {
			printusedcarsdetails(car);
			char ans = 'y';
			cout << "Are you sure you want to delete this car?(y/n)? ";
			cin >> ans;
			ans = tolower(ans);
			if (ans == 'y') {
				markusedcarsfordelete(carbrand, carmodel, caryear, cardistance, vc);
				vc = saveusedcarsdatatofile(usedcarsfilename, vc);
				cout << "\nCar Deleted Successfully.\n";
				return true;
			}
		}
		else {
			cout << "Car with brand[" << carbrand << "] and model [" << carmodel << "] is not found!\n";
		}
		return false;
	}
	void printusedcardeletescreen() {
		system("cls");
		cout << "===================================\n";
		cout << "\tDelete Used Car Screen\n";
		cout << "===================================\n";
		deleteusedcarbybrandandmodelandyearanddistance
		(getcarsfromfileusedcars(usedcarsfilename));
	}
	void addnewusedcar(string carbrand, string carmodel, int caryear, int cardistance) {
		susedcars car = readnewusedcars(carbrand, carmodel, caryear, cardistance);
		clscars::adddatalinetofile(usedcarsfilename, recordtolineusedcars(car));
	}
	void addusedcars(vector<susedcars>vc) {
		char ans = 'y';
		do {
			susedcars car;
			string carbrand = clscars::readcarbrand();
			string carmodel = clscars::readcarmodel();
			int caryear = clscars::readcaryear();
			int cardistance = clscars::readcardistance();
			while (findcarsbybrandandmodelandyearanddistanceusedcars(carbrand, carmodel, caryear, cardistance, vc, car)) {
				cout << "Car with brand [" << carbrand << "] and model ["
					<< carmodel << "] is found Enter another brand and model\n";
				carbrand = clscars::readcarbrand();
				carmodel = clscars::readcarmodel();
				caryear = clscars::readcaryear();
				cardistance = clscars::readcardistance();
			}
			addnewusedcar(carbrand, carmodel, caryear, cardistance);
			cout << "The car is added successfully To (Used Cars File). Do you want to add more cars?(Y/N): ";
			cin >> ans;
			ans = tolower(ans);
			vc = getcarsfromfileusedcars(usedcarsfilename);
		} while (ans == 'y');
	}
	void printaddusedcarscreen() {
		system("cls");
		cout << "============================================\n";
		cout << "\tAdd New Used Car(s) Screen\n";
		cout << "============================================\n";
		addusedcars(getcarsfromfileusedcars(usedcarsfilename));
	}
	void preformcomprasionbetweencars(susedcars car1, susedcars car2, int car1motor, int car2motor) {
		int pointscar1 = 0, pointscar2 = 0;
		if (car1.year > car2.year) {
			pointscar1++;
		}
		else {
			pointscar2++;
		}
		if (car1.distance < car2.distance) {
			pointscar1++;
		}
		else {
			pointscar2++;
		}
		if (car1motor > car2motor) {
			pointscar1++;
		}
		else {
			pointscar2++;
		}
		if (pointscar1 > pointscar2) {
			cout << "\n" << car1.brand << " " << car1.model << " Is Better" << e;
		}
		else {
			cout << "\n" << car2.brand << " " << car2.model << " Is Better" << e;
		}
	}
	void printcomparebetweentwocarsscreen(susedcars car1, susedcars car2, int car1motorpower, int car2motorpower) {
		cout << "-----------------------------------------------------------------\n";
		cout << "Car Brand Name|" << car1.brand << "\t\t\t" << car2.brand << "\n";
		cout << "-----------------------------------------------------------------\n";
		cout << "Model" << setw(10) << right << "|" << car1.model << setw(22) << right << car2.model << "\n";
		cout << "Year" << setw(11) << right << "|" << car1.year << setw(25) << right << car2.year << "\n";
		cout << "Motor Power" << setw(4) << right << "|" << car1motorpower << " CC" << setw(22) << right << car2motorpower << " CC" << "\n";
		cout << "Distance" << setw(7) << right << "|" << car1.distance << " KM" << setw(22) << right << car2.distance << " KM" << "\n";
		cout << "Price" << setw(10) << right << "|" << car1.price << " EGP" << setw(21) << right << car2.price << " EGP" << e;
		cout << "-----------------------------------------------------------------\n";
	}
	bool compareusedcars(vector<susedcars>vc) {
		susedcars car1, car2;
		cout << "Car 1 Details:\n";
		string car1brand = clscars::readcarbrand();
		string car1model = clscars::readcarmodel();
		int car1year = clscars::readcaryear();
		int car1distance = clscars::readcardistance();
		int car1motor = clscars::getmotorpower(car1brand, car1model, car1year);
		while (!findcarsbybrandandmodelandyearanddistanceusedcars(car1brand, car1model, car1year, car1distance, vc, car1)) {
			cout << "This car is Not found in used car list Enter Another one?\n";
			car1brand = clscars::readcarbrand();
			car1model = clscars::readcarmodel();
			car1year = clscars::readcaryear();
			car1distance = clscars::readcardistance();
			car1motor = clscars::getmotorpower(car1brand, car1model, car1year);
		}
		cout << "Car 2 Details:\n";
		string car2brand = clscars::readcarbrand();
		string car2model = clscars::readcarmodel();
		int car2year = clscars::readcaryear();
		int car2distance = clscars::readcardistance();
		int car2motor = clscars::getmotorpower(car2brand, car2model, car2year);
		while (!findcarsbybrandandmodelandyearanddistanceusedcars(car2brand, car2model, car2year, car2distance, vc, car2)) {
			cout << "This car is Not found in used car list Enter Another one?\n";
			car2brand = clscars::readcarbrand();
			car2model = clscars::readcarmodel();
			car2year = clscars::readcaryear();
			car2distance = clscars::readcardistance();
			car2motor = clscars::getmotorpower(car2brand, car2model, car2year);
		}
		if (findcarsbybrandandmodelandyearanddistanceusedcars(car1brand, car1model, car1year, car1distance, vc, car1)
			&& findcarsbybrandandmodelandyearanddistanceusedcars(car2brand, car2model, car2year, car2distance, vc, car2)
			)
		{
			printcomparebetweentwocarsscreen(car1, car2, car1motor, car2motor);
			preformcomprasionbetweencars(car1, car2, car1motor, car2motor);
			return true;
		}
		else {
			cout << "\nThis two cars is not found in the cars list go back to main menu and add them " << e;
			return false;
		}
	}
	void printcomparescreen() {
		system("cls");
		cout << "================================================\n";
		cout << "\tCompare Between Two Cars\n";
		cout << "================================================\n";
		compareusedcars(getcarsfromfileusedcars(usedcarsfilename));
	}
	void showallusedcarslist() {
		system("cls");
		vector<susedcars>vc = getcarsfromfileusedcars(usedcarsfilename);
		cout << "=================================================================================\n";
		cout << "\t\t\tCars List (" << vc.size() << ") Car(s)\n";
		cout << "=================================================================================\n";
		cout << "\n|" << left << setw(15) << "Brand Name";
		cout << "|" << left << setw(15) << "Model Name";
		cout << "|" << left << setw(15) << "Year";
		cout << "|" << left << setw(15) << "Distance Achived ";
		cout << "|" << left << setw(15) << "Price";
		cout << "\n------------------------------------------------------------------------------------------------------\n\n";
		for (susedcars c : vc) {
			printusedcarscard(c);
			cout << e;
		}
		cout << "\n-------------------------------------------------------------------------------------------------------\n";
	}
};
class clsorginalcars :public clscars {
	struct sorgcars {
		string brand;
		string model;
		int year = 0;
		int motorpower = 0;
		int moneyrangestart = 0;
		int moneyrangeend = 0;
		bool markfordelete = false;
	};
public:

	int readcarmotorpower() {
		int motorpower;
		cout << "Enter Car Motor Power? ";
		cin >> motorpower;
		return motorpower;
	}
	sorgcars readneworginalcars(string carbrand, string carmodel, int caryear, int carmotorpower) {
		sorgcars car;
		car.brand = carbrand;
		car.model = carmodel;
		car.year = caryear;
		car.motorpower = carmotorpower;
		cout << "Enter Car Money Strat? " << endl;
		cin >> car.moneyrangestart;
		cout << "Enter Car Money End? " << endl;
		cin >> car.moneyrangeend;
		return car;
	}
	sorgcars linetorecordogcar(string line, string sep = "#//#") {
		sorgcars car;
		vector<string>vs = clscars::splitstring(line);
		if (vs.size() >= 6) {
			car.brand = vs[0];
			car.model = vs[1];
			car.year = stoi(vs[2]);
			car.motorpower = stoi(vs[3]);
			car.moneyrangestart = stoi(vs[4]);
			car.moneyrangeend = stoi(vs[5]);
		}
		return car;
	}
	string recordtolineogcars(sorgcars car, string sep = "#//#") {
		string s = car.brand + sep + car.model + sep + to_string(car.year)
			+ sep + to_string(car.motorpower) + sep
			+ to_string(car.moneyrangestart) +
			sep + to_string(car.moneyrangeend) + sep;
		return s;

	}
	vector<sorgcars> getcarsfromfileogcars(string filename) {
		vector<sorgcars>vc;
		fstream file(filename, ios::in);
		if (file.is_open()) {
			string line;
			while (getline(file, line)) {
				vc.push_back(linetorecordogcar(line));
			}
			file.close();
		}
		return vc;
	}
	bool findcarsbybrandandmodelandyearandmotorpowerorgcars(string carbrand, string carmodel, int year, int motorpower, vector<sorgcars>vc, sorgcars& car) {
		for (sorgcars& c : vc) {
			if (c.brand == carbrand && c.model == carmodel && c.year == year && c.motorpower == motorpower) {
				car = c;
				return true;
			}
		}
		return false;
	}
	bool markorgcarsfordelete(string carbrand, string carmodel, int year, int motorpower, vector<sorgcars>& vc) {
		for (sorgcars& c : vc) {
			if (c.brand == carbrand && c.model == carmodel && c.year == year && c.motorpower == motorpower) {
				c.markfordelete = true;
				return true;
			}
		}
		return false;
	}
	vector<sorgcars>saveorgcarsdatatofile(string filename, vector<sorgcars>vc) {
		fstream file;
		file.open(filename, ios::out);
		if (file.is_open()) {
			for (sorgcars& c : vc) {
				if (!c.markfordelete) {
					file << recordtolineogcars(c) << e;
				}
			}
		}
		return vc;
	}
	int getmotorpower(string brandcar, string carmodel, int caryear) {
		vector<sorgcars>vc = getcarsfromfileogcars(originalcarsfilename);
		for (sorgcars& c : vc) {
			if (c.brand == brandcar && c.model == carmodel && c.year == caryear) {
				return c.motorpower;
			}
		}
	}
	void printogcarscard(sorgcars car) {
		cout << "|" << setw(15) << left << car.brand;
		cout << "|" << setw(15) << left << car.model;
		cout << "|" << setw(15) << left << car.year;
		cout << "|" << setw(17) << left << to_string(car.motorpower) + "CC";
		cout << "|" << setw(16) << left << to_string(car.moneyrangestart) + "-" + to_string(car.moneyrangeend) + " EGP";
	}
	void printogcarsdetails(sorgcars car) {
		cout << "\nThe following are the car details:\n";
		cout << "==========================================\n";
		cout << "Car Brand      : " << car.brand << e;
		cout << "Car Model      : " << car.model << e;
		cout << "Car Year       : " << car.year << e;
		cout << "Car Motor Power: " << car.motorpower << "CC" << e;
		cout << "Car Money Range: " << car.moneyrangestart << "-" << car.moneyrangeend << e;
		cout << "===========================================\n";
	}
	bool deleteorgcarsbybrandandmodelandyearandmotorpower(vector<sorgcars>vc) {
		sorgcars car;
		string carbrand = clscars::readcarbrand();
		string carmodel = clscars::readcarmodel();
		int caryear = clscars::readcaryear();
		int carmotorpower = readcarmotorpower();
		if (findcarsbybrandandmodelandyearandmotorpowerorgcars(carbrand, carmodel, caryear, carmotorpower, vc, car)) {
			printogcarsdetails(car);
			char ans = 'y';
			cout << "Are you sure you want to delete this car?(y/n)? ";
			cin >> ans;
			ans = tolower(ans);
			if (ans == 'y') {
				markorgcarsfordelete(carbrand, carmodel, caryear, carmotorpower, vc);
				vc = saveorgcarsdatatofile(originalcarsfilename, vc);
				cout << "\nCar Deleted Successfully.\n";
				return true;
			}
		}
		else {
			cout << "Car with brand[" << carbrand << "] and model [" << carmodel << "] is not found!\n";
		}
		return false;
	}
	void printorgcardeletescreen() {
		system("cls");
		cout << "===================================\n";
		cout << "\tDelete Orginal Car Screen\n";
		cout << "===================================\n";
		deleteorgcarsbybrandandmodelandyearandmotorpower
		(getcarsfromfileogcars(originalcarsfilename));
	}
	void addnewogcar(string carbrand, string carmodel, int caryear, int carmotorpower) {
		sorgcars car = readneworginalcars(carbrand, carmodel, caryear, carmotorpower);
		clscars::adddatalinetofile(originalcarsfilename, recordtolineogcars(car));
	}
	void addogcars(vector<sorgcars>vc) {
		char ans = 'y';
		do {
			sorgcars car;
			string carbrand = clscars::readcarbrand();
			string carmodel = clscars::readcarmodel();
			int caryear = clscars::readcaryear();
			int cardmotorpower = readcarmotorpower();
			while (findcarsbybrandandmodelandyearandmotorpowerorgcars(carbrand, carmodel, caryear, cardmotorpower, vc, car)) {
				cout << "Car with brand [" << carbrand << "] and model ["
					<< carmodel << "] is found Enter another brand and model\n";
				carbrand = clscars::readcarbrand();
				carmodel = clscars::readcarmodel();
				caryear = clscars::readcaryear();
				cardmotorpower = readcarmotorpower();
			}
			addnewogcar(carbrand, carmodel, caryear, cardmotorpower);
			cout << "The car is added successfully To (Orginial Cars File). Do you want to add more cars?(Y/N): ";
			cin >> ans;
			ans = tolower(ans);
			vc = getcarsfromfileogcars(originalcarsfilename);
		} while (ans == 'y');
	}
	void printaddorgcarscreen() {
		system("cls");
		cout << "============================================\n";
		cout << "\tAdd New Orginal Car(s) Screen\n";
		cout << "============================================\n";
		addogcars(getcarsfromfileogcars(originalcarsfilename));
	}
	void showallorgcarslist() {
		system("cls");
		vector<sorgcars>vc = getcarsfromfileogcars(originalcarsfilename);
		cout << "=================================================================================\n";
		cout << "\t\t\tOrginal Cars List (" << vc.size() << ") Car(s)\n";
		cout << "=================================================================================\n";
		cout << "\n|" << left << setw(15) << "Brand Name";
		cout << "|" << left << setw(15) << "Model Name";
		cout << "|" << left << setw(15) << "Year";
		cout << "|" << left << setw(15) << "Motor Power";
		cout << "|" << left << setw(15) << "Distance Achived ";
		cout << "|" << left << setw(15) << "Money Range";
		cout << "\n------------------------------------------------------------------------------------------------------\n\n";
		for (sorgcars& c : vc) {
			printogcarscard(c);
			cout << e;
		}
		cout << "\n-------------------------------------------------------------------------------------------------------\n";
	}
};
void preformoperationonmainmenu(enmainmenu n) {
	clsusedcars usedcar;
	clsorginalcars orgcar;
	switch (n)
	{
	case enmainmenu::enshowallorginalcarsdetails:
		orgcar.showallorgcarslist();
		gobacktomainmenu();
		break;
	case enmainmenu::enshowallusedcarsdetails:
		usedcar.showallusedcarslist();
		gobacktomainmenu();
		break;
	case enmainmenu::enaddneworginalcars:
		orgcar.printaddorgcarscreen();
		gobacktomainmenu();
		break;
	case enmainmenu::enaddnewusedcars:
		usedcar.printaddusedcarscreen();
		gobacktomainmenu();
		break;
	case enmainmenu::endeleteorginalcar:
		orgcar.printorgcardeletescreen();
		gobacktomainmenu();
		break;
	case enmainmenu::endeleteusedcars:
		usedcar.printusedcardeletescreen();
		gobacktomainmenu();
		break;
	case enmainmenu::encomparebetweentwousedcars:
		usedcar.printcomparescreen();
		gobacktomainmenu();
	default:
		cout << "GoodBye :-) :" << e;
		return;
	}
}
void showmainmenu() {
	system("cls");
	cout << "==============================================\n";
	cout << "\t[1] Show all Orginal Cars List" << e;
	cout << "\t[2] Show all Used Cars List" << e;
	cout << "\t[3] Add a new orginal Car" << e;
	cout << "\t[4] Add a new Used Car" << e;
	cout << "\t[5] Delete a orginal Car" << e;
	cout << "\t[6] Delete a Used Car" << e;
	cout << "\t[7] Compare between two used cars\n";
	cout << "\t[8] Exit" << e;
	cout << "==============================================\n";
	preformoperationonmainmenu(readchoicefrommainmenu());
}
int main()
{
	showmainmenu();
	return 0;
}