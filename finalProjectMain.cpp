/*
Final Project: Default Proposal
CompSci 222-01 04/18/2025
Troy Poniewaz & Nicholas Price

Files: 
	finalProjectMain.cpp, data.h, data.cpp, track.h, track.cpp, 
	audioBook.h, audioBook.cpp, tvEpisode.h, tvEpisode.cpp

Stretch Goals:
1. Implemented allowing the user to add a new entry to the database. Also updates the orignal database file.
2. Implemented allowing the user to remove an entry from the database. Also updates the original databse file. 
3. 
*/

#include "track.h"
#include "audioBook.h"
#include "tvEpisode.h"
#include <fstream>
#include <algorithm> //we can use this for std::swap in the sort functions

int get_line_count(const std::string& path) {
	std::ifstream stream;
	stream.open(path);

	int count = 0;

	if (stream.is_open()) {
		std::string line;
		while (std::getline(stream, line)) {
			count++;
		}
		stream.close();
	}
	return count;
}

data* fill_database(const std::string& path, int length) {
	data* database = new data[length];

	return;
}
//funtion to get line counts

//function to build array

//function to write to csv

int main() {
	std::string path = "Data\\database.csv";
	
	int num_lines = get_line_count(path) - 3;

	data* database = fill_database(path, num_lines);

	//std::cout << "Line count: " << num_lines << std::endl;

	return 0;
}