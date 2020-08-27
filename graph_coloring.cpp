#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#define MST 100 // bir dersi alan maksimum öðrenci sayýsý
using namespace std;
																					//text dosyalarý program ile ayný klasörde olmalýdýr.
int getlinecount(ifstream& file) {
	int line_count = 0;
	string notused;
	while (getline(file, notused)) {
		++line_count;
	}
	file.clear();
	file.seekg(0, ios::beg);
	return line_count;
}


int intersection(const vector<string>& x, int a, int b) {
	int i, j;
	for (i = 0; i < MST; i++) {
		for (j = 0; j < MST; j++) {
			if ((x[i + a * MST] == x[j + b * MST]) && (x[i + a * MST] != "") && (x[j + b * MST] != "")) {
				return 1;
			}
		}
	}
	return 0;
}


void create_adj(int line_count, const vector<string>& students, vector<int>& adj) {
	int i, j;
	for (i = 0; i < line_count; i++) {
		for (j = i + 1; j < line_count; j++) {
			if (intersection(students, i, j)) {
				adj[j + i * line_count] = 1;
			}
		}
	}
}

void assign_colors(int line_count, const vector<int>& adj, vector<int>& colors) {
	int i, j;
	for (i = 0; i < line_count; i++) {
		for (j = 0; j < line_count; j++) {
			if (adj[i + j * line_count] == 1) {
				colors[i]++;
			}
		}
	}
}

void fillstudents(int line_count, vector<string>& course_list,  vector<string>& students, ifstream& courses) {
	int i = 0, j;
	string buffer;
	ifstream course_file;
	char course_name[15];
	for (j = 0; j < line_count; j++) {
		courses >> course_name;
		course_list[j] = course_name;
		strcat(course_name, ".txt");
		course_file.open(course_name);
		while (getline(course_file, buffer)) {
			students[i + j * MST] = buffer;
			i++;
		}
		i = 0;
		course_file.close();
	}
}

int main()
{
	int i = 0, j = 0;
	ifstream courses;
	
	courses.open("dersler.txt");
	int line_count = getlinecount(courses);

	vector<string> students;
	students.resize(line_count * MST);
	vector<string> course_list;
	course_list.resize(line_count * 10);
	vector<int> adj;
	adj.resize(line_count * line_count);
	vector<int> colors;
	colors.resize(line_count);

	fillstudents(line_count, course_list, students, courses);
	create_adj(line_count, students, adj);
	assign_colors(line_count, adj, colors);

	for (i = 0; i < line_count; i++) {
		cout << "Colour of " << course_list[i] << ": " << colors[i] << endl;;
	}
	cout << "Minimum color count to fill the courses: " << *max_element(colors.begin(), colors.end())+1 << endl;
	system("pause");
	return 0;
}

