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
#include <vector>

int get_line_counts(const std::string& path) {
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

std::vector<data*> fill_database(const std::string& path, int length) {
	std::vector<data*> database;

	std::ifstream stream;
	stream.open(path);

	if (stream.is_open()) {
		std::string line, tracker = "Tracks";
		std::getline(stream, line);

		for (int i = 0; i < length; i++) {
			std::getline(stream, line, ',');
			if (line != tracker) {
				tracker = line;
				std::cout << line << " " << tracker << std::endl;
				std::getline(stream, line);
				std::getline(stream, line, ',');
			}

			if (tracker == "Tracks") {
				std::getline(stream, line, ',');
				std::string title = line;

				std::getline(stream, line, ',');
				std::string creator = line;

				std::getline(stream, line, ',');
				std::string album = line;

				std::getline(stream, line, ',');
				//make function to verify is int!
				int year = std::stoi(line);

				std::getline(stream, line, ',');
				//make function to verify double!
				double duration = std::stod(line);

				std::getline(stream, line);
				//make function to verify double!
				double rating = std::stod(line);

				database.push_back(new track(title, creator, album, year, duration, rating));
			}

			if (tracker == "Audio Books") {
				std::getline(stream, line, ',');
				std::string title = line;

				std::getline(stream, line, ',');
				std::string creator = line;

				std::getline(stream, line, ',');
				//make function to verify is int!
				int year = std::stoi(line);

				std::getline(stream, line, ',');
				//make function to verify double!
				double duration = std::stoi(line);

				std::getline(stream, line);
				double rating = std::stoi(line);

				database.push_back(new audio_book(title, creator, year, duration, rating));
			}

			if (tracker == "TV Episodes") {
				std::getline(stream, line, ',');
				std::string title = line;

				std::getline(stream, line, ',');
				std::string show_title = line;

				std::getline(stream, line, ',');
				std::string creator = line;

				std::getline(stream, line, ',');
				//make function to verify is int!
				int year = std::stoi(line);

				std::getline(stream, line, ',');
				//make function to verify is int!
				int season = std::stoi(line);

				std::getline(stream, line, ',');
				//make function to verify is int!
				int episode = std::stoi(line);

				std::getline(stream, line, ',');
				//make function to verify double!
				double duration = std::stod(line);

				std::getline(stream, line);
				//make function to verify double!
				double rating = std::stod(line);

				database.push_back(new tv_episode(title, show_title, creator, year, season, episode, duration, rating));
			}
		}
		stream.close();
	}
	return database;
}

void print(const std::vector<data*>& database, int length) {
	for (int i = 0; i < length; i++) {
		std::cout << i + 1 << ": ";
		if (track* t = dynamic_cast<track*>(database[i])) {
			t->print();
		}
		if (audio_book* b = dynamic_cast<audio_book*>(database[i])) {
			b->print();
		}
		if (tv_episode* e = dynamic_cast<tv_episode*>(database[i])) {
			e->print();
		}
	}
}

int main() {
	std::string path = "Data\\database.csv";
	
	int num_lines = get_line_counts(path) - 3;

	std::vector<data*> database = fill_database(path, num_lines);;

	print(database, num_lines);

	for (int i = 0; i < num_lines; i++) {
		delete database[i];
	}

	return 0;
}