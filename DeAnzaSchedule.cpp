/*Programmed by Kaden Golda
E-Mail: kadengoldasteam@gmail.com
Lab 7 - Submission
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

// Function declarations
void getData(ifstream& inFile, double numWaitlist[], double crn[], double currentEnrol[], double maxEnrol[], double fillRate[], string name[]);
void output(ofstream& outFile, double crn[], string name[], double currentEnrol[], double maxEnrol[], double numWaitlist[], double fillRate[]);
void sortfillrate(double crn[], string name[], double currentEnrol[], double maxEnrol[], double numWaitlist[], double fillRate[], double minfillRate);
int sortArray(double fillRate[]);
int search(double crn[], double crnNum);

int main() {
	// Array declarations
	double fillRate[100], currentEnrol[100], maxEnrol[100], numWaitlist[100], crn[100];
	string name[100];

	double location, minfillRate;
	ifstream inFile; // create file for input
	inFile.open("Lab7FillRates.txt");
	if (inFile.fail() == 1)
	{
		cout << "No Such File" << endl;	// Send error if file doesn't exist.
		exit(100);
	}

	ofstream outFile; // create file for output
	outFile.open("ClassSchedule.txt");

	int searchValue;

	cout << "What's your desired fill rate? ";
	cin >> minfillRate;

	cout << "Please enter your CRN number: ";
	cin >> searchValue;

	getData(inFile, numWaitlist, crn, currentEnrol, maxEnrol, fillRate, name); // get data from inFile
	output(outFile, crn, name, currentEnrol, maxEnrol, numWaitlist, fillRate); // output formatted table of classes to outFile

	location = search(crn, searchValue); // return value to give location of class in the file

	sortfillrate(crn, name, currentEnrol, maxEnrol, numWaitlist, fillRate, minfillRate); // sort by fill rate
	sortArray(fillRate); // sort the array in ascending order

	output(outFile, crn, name, currentEnrol, maxEnrol, numWaitlist, fillRate); // output the newly-sorted array

	if (location != -1) // -1 acts as an error code since location will never be -1. 
	{
		cout << "Your class location is " << location;
		return 0;
	}
	else
	{
		cout << "NO SUCH CLASS!";
		return 0;
	}
}

void getData(ifstream& inFile, double numWaitlist[], double crn[], double currentEnrol[], double maxEnrol[], double fillRate[], string name[]) {
	for (int i = 0; i <= 99; i++)
	{
		inFile >> crn[i];
		if (crn[i] == 0)
		{
			break;
		}
		getline(inFile, name[i]);
		inFile >> currentEnrol[i];
		inFile >> maxEnrol[i];
		inFile >> numWaitlist[i];
		fillRate[i] = (currentEnrol[i] / maxEnrol[i]) * 100;
	}
}

void output(ofstream& outFile, double crn[], string name[], double currentEnrol[], double maxEnrol[], double numWaitlist[], double fillRate[]) {
	/*
	   Pre: outFile - reference to outFile
		    crn[] - class CRN number
			name[] - name of course
			currentEnrol[] - current amount of enrolled students
			maxEnrol[] - maximum amount of enrolled students
			numWaitlist[] - number of students on waitlist
			fillRate[] - fill rate for each class
	   Post: None
	   Purpose: Output the array to file.
	 */
	outFile << "CRN" << setw(20) << "Course" << setw(20) << " Current" << setw(20) << "Max"
		<< setw(20) << "Number on" << setw(20) << "Fill\n";
	outFile << right << setw(46) << "Enrollment" << setw(24) << "Enrollment"
		<< setw(13) << "Wait-list" << setw(21) << "Rate %" << endl;
	for (int i = 0; i <= 99; i++)
	{
		if (maxEnrol[i] == 0)
		{
			break;
		}
		outFile << fixed << setprecision(0) << left << crn[i] << setw(25) << setprecision(2) << name[i] << setw(13) << right << currentEnrol[i] << setw(25) << maxEnrol[i] << setw(14) << numWaitlist[i] << setw(23) << fillRate[i] << endl;
	}
}

void sortfillrate(double crn[], string name[], double currentEnrol[], double maxEnrol[], double numWaitlist[], double fillRate[], double minfillRate) {
	/*
	Pre: minfillRate - minimum fill rate for classes
	crn[] - class CRN number
	name[] - name of course
	currentEnrol[] - current amount of enrolled students
	maxEnrol[] - maximum amount of enrolled students
	numWaitlist[] - number of students on waitlist
	fillRate[] - fill rate for each class
	Post: None
	Purpose: Output classes with fill rates below given value.
	*/
	ofstream outFile;
	outFile.open("Classes with minimum fill rate.txt");

	for (int i = 0; i <= 99; i++)
	{
		if (maxEnrol[i] == 0)
		{
			break;
		}
		else if (fillRate[i] <= minfillRate)
		{
			outFile << fixed << setprecision(0) << left << crn[i] << setw(25) << setprecision(2) << name[i] << setw(13) << right << currentEnrol[i] << setw(25) << maxEnrol[i] << setw(14) << numWaitlist[i] << setw(23) << fillRate[i] << endl;
		}
	}
	cout << "No classes with fill rate below " << minfillRate << endl;
}

int search(double crn[], double searchValue) {
	/*
	   Pre: crn[] - array for the crn of each class
	   searchValue - the value to search for
	   Post: i - array location
	   Purpose: Search the array for the crn number that is inputted by the user.
	 */

	for (int i = 0; i < 99; i++)
	{
		if (searchValue == crn[i])
		{
			return i;
		}
		else
		{
			return -1;
		}
	}
}

int sortArray(double fillRate[]) {
	/*
	   Pre: fillRate - reference to fillRate[]
	   Post: None
	   Purpose: Sort array in ascending order.
	 */
	double temp, swapped = 0;

	for (int i = 0; i < 99 - 1; i++)
	{
		if (fillRate[i] > fillRate[i + 1])
		{
			temp = fillRate[i];
			fillRate[i] = fillRate[i + 1];
			fillRate[i + 1] = temp;
			swapped = 1;
		}
	}
	return 0;
}

/* Output
CRN              Course             Current                 Max           Number on           Fill
									Enrollment              Enrollment    Wait-list           Rate %
469      	CIS D002.-62Z           27                       40              0                   67.5
471      	CIS D003.-02Y           22                       40              0                     55
472      	CIS D003.-03Y           14                       40              0                     35
2638      	CIS D003.-04Y        32                       40              0                     80
20371      	CIS D003.-62Z        40                       40             12                    100
22477      	CIS D003.-61Y         8                       40              0                     20
22326      	CIS D004.-62Y         7                       40              0                   17.5
22333      	CIS D004.-62Z        40                       40              2                    100
22582      	CIS D004.-65Z        23                       40              0                   57.5
21790      	CIS D014A-62Z        24                       40              0                     60
479      	CIS D018A-62Y        20                       40              0                     50
2639      	CIS D018A-01Y        40                       40              7                    100
21713      	CIS D022A-02Y        39                       40              0                   97.5
21714      	CIS D022A-03Y        22                       40              0                     55
21715      	CIS D022A-04Y        31                       40              0                   77.5
21716      	CIS D022A-05Y        40                       40              2                    100
21717      	CIS D022A-61Y         6                       40              0                     15
21718      	CIS D022A-62Y         7                       40              0                   17.5
22006      	CIS D022A-06Y        40                       40             10                    100
22027      	CIS D022A-63Y         5                       40              0                   12.5
22329      	CIS D022A-07Y        40                       40              8                    100
22569      	CIS D022A-08Y        16                       40              0                     40
22584      	CIS D022A-09Y        40                       40              7                    100
23868      	CIS D022A-62Z        35                       40              0                   87.5
21719      	CIS D022B-62Z        40                       40             15                    100
21720      	CIS D022B-02Y        40                       40              1                    100
21721      	CIS D022B-61Y        25                       40              0                   62.5
22325      	CIS D022B-03Y        39                       40              3                   97.5
22583      	CIS D022B-04Y        40                       40             15                    100
22320      	CIS D022C-61Y        35                       40              0                   87.5
22327      	CIS D022C-01Y        40                       40             15                    100
22855      	CIS D022C-02Y        40                       40              0                    100
23078      	CIS D022C-62Z        40                       40             15                    100
23076      	CIS D028.-61Y        39                       40              0                   97.5
22958      	CIS D029.-61Y        30                       40              0                     75
484      	CIS D035A-01Y        26                       40              0                     65
485      	CIS D035A-61Y        40                       40              5                    100
23382      	CIS D035A-62Z        40                       40             15                    100
487      	CIS D035B-61Y        28                       40              0                     70
22856      	CIS D036A-01Y        40                       40             15                    100
23412      	CIS D036A-61Y        17                       40              0                   42.5
22957      	CIS D036B-61Y        34                       40              0                     85
23383   	CIS D040.-01Y40	     40                       40              8                    100
24578   	CIS D040.-61Y40	     40                       40              7                    100
23384      	CIS D041A-01Y        33                       40              0                   82.5
24090      	CIS D041A-02Y        40                       40             15                    100
24666      	CIS D041B-02Y        40                       40             13                    100
24539      	CIS D056.-62Z        33                       60              0                     55
24101      	CIS D064A-62Z        25                       40              0                   62.5
22859      	CIS D064C-62Z        28                       40              0                     70
24683      	CIS D064F-62Z        27                       40              0                   67.5
491      	CIS D066.-62Z        40                       40              0                    100
24920      	CIS D074.-62Y         5                       40              0                   12.5
494      	CIS D089A-62Z        31                       40              0                   77.5
495      	CIS D089C-62Z        14                       40              0                     35
24684      	CIS D095C-55L         8                       40              0                     20
24685      	CIS D095D-55L         8                       40              0                     20
25067      	CIS D095E-55L         5                       40              0                   12.5
21723      	CIS D098.-62Z        13                       40              0                   32.5
23077      	CIS D099.-62Z        26                       40              0                     65
24252      	CIS D102.-62Z        27                       40              0                   67.5
21722      	CIS D108.-62Z        17                       60              0                   28.3
2644      	CIS D21JA-01Y        40                       40              5                    100
22853      	CIS D21JA-02Y        40                       40             12                    100
23989      	CIS D21JA-62Y        36                       40              0                     90

CRN              Course             Current                 Max           Number on           Fill
									Enrollment              Enrollment    Wait-list           Rate %
469      	CIS D002.-62Z           27                       40              0                   67.5
471      	CIS D003.-02Y           22                       40              0                     55
472      	CIS D003.-03Y           14                       40              0                     35
2638      	CIS D003.-04Y        32                       40              0                     80
20371      	CIS D003.-62Z        40                       40             12                    100
22477      	CIS D003.-61Y         8                       40              0                     20
22326      	CIS D004.-62Y         7                       40              0                   17.5
22333      	CIS D004.-62Z        40                       40              2                    100
22582      	CIS D004.-65Z        23                       40              0                   57.5
21790      	CIS D014A-62Z        24                       40              0                     60
479      	CIS D018A-62Y        20                       40              0                     50
2639      	CIS D018A-01Y        40                       40              7                    100
21713      	CIS D022A-02Y        39                       40              0                   97.5
21714      	CIS D022A-03Y        22                       40              0                     55
21715      	CIS D022A-04Y        31                       40              0                   77.5
21716      	CIS D022A-05Y        40                       40              2                    100
21717      	CIS D022A-61Y         6                       40              0                     15
21718      	CIS D022A-62Y         7                       40              0                   17.5
22006      	CIS D022A-06Y        40                       40             10                    100
22027      	CIS D022A-63Y         5                       40              0                   12.5
22329      	CIS D022A-07Y        40                       40              8                    100
22569      	CIS D022A-08Y        16                       40              0                     40
22584      	CIS D022A-09Y        40                       40              7                    100
23868      	CIS D022A-62Z        35                       40              0                   87.5
21719      	CIS D022B-62Z        40                       40             15                    100
21720      	CIS D022B-02Y        40                       40              1                    100
21721      	CIS D022B-61Y        25                       40              0                   62.5
22325      	CIS D022B-03Y        39                       40              3                   97.5
22583      	CIS D022B-04Y        40                       40             15                    100
22320      	CIS D022C-61Y        35                       40              0                   87.5
22327      	CIS D022C-01Y        40                       40             15                    100
22855      	CIS D022C-02Y        40                       40              0                    100
23078      	CIS D022C-62Z        40                       40             15                    100
23076      	CIS D028.-61Y        39                       40              0                   97.5
22958      	CIS D029.-61Y        30                       40              0                     75
484      	CIS D035A-01Y        26                       40              0                     65
485      	CIS D035A-61Y        40                       40              5                    100
23382      	CIS D035A-62Z        40                       40             15                    100
487      	CIS D035B-61Y        28                       40              0                     70
22856      	CIS D036A-01Y        40                       40             15                    100
23412      	CIS D036A-61Y        17                       40              0                   42.5
22957      	CIS D036B-61Y        34                       40              0                     85
23383   	CIS D040.-01Y40	     40                       40              8                    100
24578   	CIS D040.-61Y40	     40                       40              7                    100
23384      	CIS D041A-01Y        33                       40              0                   82.5
24090      	CIS D041A-02Y        40                       40             15                    100
24666      	CIS D041B-02Y        40                       40             13                    100
24539      	CIS D056.-62Z        33                       60              0                     55
24101      	CIS D064A-62Z        25                       40              0                   62.5
22859      	CIS D064C-62Z        28                       40              0                     70
24683      	CIS D064F-62Z        27                       40              0                   67.5
491      	CIS D066.-62Z        40                       40              0                    100
24920      	CIS D074.-62Y         5                       40              0                   12.5
494      	CIS D089A-62Z        31                       40              0                   77.5
495      	CIS D089C-62Z        14                       40              0                     35
24684      	CIS D095C-55L         8                       40              0                     20
24685      	CIS D095D-55L         8                       40              0                     20
25067      	CIS D095E-55L         5                       40              0                   12.5
21723      	CIS D098.-62Z        13                       40              0                   32.5
23077      	CIS D099.-62Z        26                       40              0                     65
24252      	CIS D102.-62Z        27                       40              0                   67.5
21722      	CIS D108.-62Z        17                       60              0                   28.3
2644      	CIS D21JA-01Y        40                       40              5                    100
22853      	CIS D21JA-02Y        40                       40             12                    100
23989      	CIS D21JA-62Y        36                       40              0                     90

for Classes with minimum fill rate.txt

472	    CIS D003.-03Y                   14.00                    40.00          0.00                  35.00
22477	CIS D003.-61Y                    8.00                    40.00          0.00                  20.00
22326	CIS D004.-62Y                    7.00                    40.00          0.00                  17.50
21717	CIS D022A-61Y                    6.00                    40.00          0.00                  15.00
21718	CIS D022A-62Y                    7.00                    40.00          0.00                  17.50
22027	CIS D022A-63Y                    5.00                    40.00          0.00                  12.50
22569	CIS D022A-08Y                   16.00                    40.00          0.00                  40.00
24920	CIS D074.-62Y                    5.00                    40.00          0.00                  12.50
495	CIS D089C-62Z                       14.00                    40.00          0.00                  35.00
24684	CIS D095C-55L                    8.00                    40.00          0.00                  20.00
24685	CIS D095D-55L                    8.00                    40.00          0.00                  20.00
25067	CIS D095E-55L                    5.00                    40.00          0.00                  12.50
21723	CIS D098.-62Z                   13.00                    40.00          0.00                  32.50
21722	CIS D108.-62Z                   17.00                    60.00          0.00                  28.33


*/



