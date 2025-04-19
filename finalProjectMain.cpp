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

//data** fill_database(const std::string& path, int length) {
//	data** database = new data*[length];
//
//	std::ifstream stream;
//	stream.open(path);
//
//	if (stream.is_open()) {
//		std::string line, tracker = "New";
//		std::getline(stream, line);
//
//		for (int i = 0; i < length; i++) {
//			std::getline(stream, line, ',');
//			if (line != tracker) {
//				tracker = line;
//				std::getline(stream, line);
//				std::getline(stream, line, ',');
//			}
//
//			if (tracker == "Tracks") {
//				std::getline(stream, line, ',');
//				std::string title = line;
//				std::cout << title << std::endl;
//
//				std::getline(stream, line, ',');
//				std::string creator = line;
//				std::cout << creator << std::endl;
//
//				std::getline(stream, line, ',');
//				std::string album = line;
//				std::cout << album << std::endl;
//
//				std::getline(stream, line, ',');
//				//make function to verify is int!
//				int year = std::stoi(line);
//				std::cout << year << std::endl;
//
//				std::getline(stream, line, ',');
//				//make function to verify double!
//				double duration = std::stod(line);
//				std::cout << duration << std::endl;
//
//				std::getline(stream, line);
//				//make function to verify double!
//				double rating = std::stod(line);
//				std::cout << rating << std::endl;
//
//				database[i] = new track(title, creator, album, year, duration, rating);
//
//				/*if (track* t = dynamic_cast<track*>(database[i])) {
//					t->print();
//				}*/
//			}
//
//			//else if (tracker == "Audio Books") {
//			//	std::getline(stream, line, ',');
//			//	std::string title = line;
//
//			//	std::getline(stream, line, ',');
//			//	std::string creator = line;
//
//			//	std::getline(stream, line, ',');
//			//	//make function to verify is int!
//			//	int year = std::stoi(line);
//
//			//	std::getline(stream, line, ',');
//			//	//make function to verify double!
//			//	double duration = std::stoi(line);
//
//			//	std::getline(stream, line);
//			//	//int rating =std::stoi(line);
//
//			//	database[i] = new audio_book(title, creator, year, duration, true);
//			//}
//
//			//else if (tracker == "TV Episodes") {
//			//	std::getline(stream, line, ',');
//			//	std::string title = line;
//
//			//	std::getline(stream, line, ',');
//			//	std::string show_title = line;
//
//			//	std::getline(stream, line, ',');
//			//	std::string creator = line;
//
//			//	std::getline(stream, line, ',');
//			//	//make function to verify is int!
//			//	int year = std::stoi(line);
//
//			//	std::getline(stream, line, ',');
//			//	//make function to verify is int!
//			//	int season = std::stoi(line);
//
//			//	std::getline(stream, line, ',');
//			//	//make function to verify is int!
//			//	int episode = std::stoi(line);
//
//			//	std::getline(stream, line, ',');
//			//	//make function to verify double!
//			//	double duration = std::stod(line);
//
//			//	std::getline(stream, line);
//			//	//make function to verify double!
//			//	double rating = std::stod(line);
//
//			//	database[i] = new tv_episode(title, show_title, creator, year, season, episode, duration, rating);
//			//}
//		}
//		stream.close();
//	}
//	return database;
//}

std::vector<data*> fill_database(const std::string& path, int length) {
	std::vector<data*> database;

	std::ifstream stream;
	stream.open(path);

	if (stream.is_open()) {
		std::string line, tracker = "New";
		std::getline(stream, line);

		for (int i = 0; i < 6; i++) {
			std::getline(stream, line, ',');
			if (line != tracker) {
				tracker = line;
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

				if (track* b = dynamic_cast<track*>(database[i])) {
					b->print();
				}
			}

			else if (tracker == "Audio Books") {
				std::getline(stream, line, ',');
				std::string title = line;
				std::cout << "Title: " << title << std::endl;

				std::getline(stream, line, ',');
				std::string creator = line;
				std::cout << "Creator: " << creator << std::endl;

				std::getline(stream, line, ',');
				//make function to verify is int!
				int year = std::stoi(line);
				std::cout << "Year: " << year << std::endl;

				std::getline(stream, line, ',');
				//make function to verify double!
				double duration = std::stoi(line);
				std::cout << "Duration: " << duration << std::endl;

				std::getline(stream, line);
				double rating = std::stoi(line);
				std::cout << "Rating: " << rating << std::endl;

				database.push_back(new audio_book(title, creator, year, duration, rating));

				//if (audio_book* b = dynamic_cast<audio_book*>(database[i])) {
				//	b->print();
				//}
			}

			else if (tracker == "TV Episodes") {
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

int main() {
	std::string path = "Data\\database.csv";
	
	int num_lines = get_line_counts(path) - 3;

	std::vector<data*> database = fill_database(path, num_lines);;

	//data** database = fill_database(path, num_lines);

	/*for (int i = 0; i < num_lines; i++) {
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

	for (int i = 0; i < num_lines; i++) {
		delete database[i];
	}*/
	//delete[] database;

	return 0;
}