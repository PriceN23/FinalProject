/*
Final Project: Default Proposal
CompSci 222-01 05/01/2025
Troy Poniewaz & Nicholas Price

Files: 
	finalProjectMain.cpp, data.h, data.cpp, track.h, track.cpp, 
	audioBook.h, audioBook.cpp, tvEpisode.h, tvEpisode.cpp, Data\database.csv

Stretch Goals:
1. (Inprogress) Implemented allowing the user to add a new entry to the database. Also updates the orignal database file.
2. (Inprogress) Implemented allowing the user to remove an entry from the database. Also updates the original databse file.
3. (Inprogress)
*/
#include "track.h"
#include "audioBook.h"
#include "tvEpisode.h"
#include <fstream>
#include <algorithm> //we can use this for std::swap in the sort functions
#include <vector>

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

std::vector<data*> fill_database(const std::string& path, int length) {
	std::vector<data*> database;

	std::ifstream stream;
	stream.open(path);

	if (stream.is_open()) {
		std::string line, tracker = "Track";
		std::getline(stream, line);

		for (int i = 0; i < length; i++) {
			std::getline(stream, line, ',');
			if (line != tracker) {
				tracker = line;
				std::cout << line << " " << tracker << std::endl;
				std::getline(stream, line);
				std::getline(stream, line, ',');
			}

			if (tracker == "Track") {
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

			if (tracker == "Audio Book") {
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

			if (tracker == "TV Episode") {
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

void print_database(const std::vector<data*>& database, int length) {
	std::cout << std::endl 
		<< "Database: " << std::endl;

	for (int i = 0; i < length; i++) {
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
	std::cout << std::endl;
}

void print_tracks(const std::vector<data*>& database, int length) {
	std::cout << std::endl 
		<< "Tracks: " << std::endl;

	for (int i = 0; i < length; i++) {
		if (track* t = dynamic_cast<track*>(database[i])) {
			t->print();
		}
	}
	std::cout << std::endl;
}

void print_audio_books(const std::vector<data*>& database, int length) {
	std::cout << std::endl 
		<< "Audio Books: " << std::endl;

	for (int i = 0; i < length; i++) {
		if (audio_book* b = dynamic_cast<audio_book*>(database[i])) {
			b->print();
		}
	}
	std::cout << std::endl;
}

void print_tv_episodes(const std::vector<data*>& database, int length) {
	std::cout << std::endl 
		<< "TV Episodes: " << std::endl;

	for (int i = 0; i < length; i++) {
		if (tv_episode* e = dynamic_cast<tv_episode*>(database[i])) {
			e->print();
		}
	}
	std::cout << std::endl;
}

void invalid_input() {
	std::cout << "Invalid entry, please make another seleciton: ";
}

bool verify_integer(const std::string& input) {
	for (int i = 0; i < input.length(); i++) {
		if (!std::isdigit(input[i])) {
			return false;
		}
	}
	return true;
}

bool within_range(const std::string& input, int range) {
	if (input >= "0" && std::stoi(input) <= range) {
		return true;
	}
	return false;
}

int get_input(int range) {
	int selected = 0;
	bool end = false;
	std::string input;

	do {
		std::getline(std::cin, input);

		if (input.length() > 0 && verify_integer(input) == true && within_range(input, range) == true) {
			selected = std::stoi(input);
			end = true;
		}
		else {
			invalid_input();
		}
	} while (end == false);

	return selected;
}

std::string get_input() {
	std::string input = "Unknown";
	bool end = false;

	do {
		std::getline(std::cin, input);

		if (input.length() > 0) {
			end = true;
		}
		else {
			invalid_input();
		}
	} while (end == false);

	return input;
}

void print_by_creator(const std::vector<data*>& database, int length) {
	std::string creator = "Unknown";
	int counter = 0;

	std::cout << std::endl << "Note: Search is case and space sensitive" << std::endl;
	std::cout << "Enter creator: ";

	creator = get_input();
	std::cout << std::endl;

	for (int i = 0; i < length; i++) {
		if (base_data* d = dynamic_cast<base_data*>(database[i])) {
			if (d->get_creator() == creator) {
				if (track* t = dynamic_cast<track*>(database[i])) {
					t->print();
					counter++;
				}
				else if (audio_book* b = dynamic_cast<audio_book*>(database[i])) {
					b->print();
					counter++;
				}
				else if (tv_episode* e = dynamic_cast<tv_episode*>(database[i])) {
					e->print();
					counter++;
				}
			}
		}
	}
	if (counter == 0) {
		std::cout << "Not entries in database match creator: " << creator << std::endl;
	}
	std::cout << std::endl;
}

void print_by_year(const std::vector<data*>& database, int length) {
	int year = 0, counter = 0;

	std::cout << std::endl << "Note: Space sensitive" << std::endl;
	std::cout << "Enter year: ";

	year = get_input(2025);
	std::cout << std::endl;

	for (int i = 0; i < length; i++) {
		if (base_data* d = dynamic_cast<base_data*>(database[i])) {
			if (d->get_year() >= year) {
				if (track* t = dynamic_cast<track*>(database[i])) {
					t->print();
					counter++;
				}
				else if (audio_book* b = dynamic_cast<audio_book*>(database[i])) {
					b->print();
					counter++;
				}
				else if (tv_episode* e = dynamic_cast<tv_episode*>(database[i])) {
					e->print();
					counter++;
				}
			}
		}
	}
	if (counter == 0) {
		std::cout << "Not entries in database released on or after: " << year << std::endl;
	}
	std::cout << std::endl;
}

void sort_successful() {
	std::cout << std::endl << "Sort successful" << std::endl;
}

void sort_for_csv(std::vector<data*>& database, int length) {
	//moves all tracks to top of list, followed by moving all audio book after tracks leaving tv episodes at end of list
	int index = 0;
	for (int i = 0; i < length; i++) { 
		if (track* e = dynamic_cast<track*>(database[i])) {
			std::swap(database[i], database[index]);
			index++;
		}
	}
	for (int i = index; i < length; i++) {
		if (audio_book* e = dynamic_cast<audio_book*>(database[i])) {
			std::swap(database[i], database[index]);
			index++;
		}
	}
}

void update_csv(std::vector<data*>& database, int length, const std::string& path) {
	std::cout << std::endl << "Updating database..." << std::endl;
	sort_for_csv(database, length);

	std::ofstream stream;
	int counter = 0;

	stream.open(path);
	if (stream.is_open()) {
		stream << "Track,Title,Creator,Album,Year,Duration,Rating" << std::endl;
		for (int i = 0; i < length; i++) {
			if (track* t = dynamic_cast<track*>(database[i])) {
				stream << "Track,"
					<< t->get_title() << ","
					<< t->get_creator() << ","
					<< t->get_album() << ","
					<< t->get_year() << ","
					<< t->get_duration() << ","
					<< t->get_rating() << std::endl;
				counter++;
			}
		}
		stream << "Audio Book,Title,Creator,Year,Duration,Rating" << std::endl;
		for (int i = counter; i < length; i++) {
			if (audio_book* t = dynamic_cast<audio_book*>(database[i])) {
				stream << "Audio Book,"
					<< t->get_title() << ","
					<< t->get_creator() << ","
					<< t->get_year() << ","
					<< t->get_duration() << ","
					<< t->get_rating() << std::endl;
				counter++;
			}
		}
		stream << "TV Episode,Title,Show Title,Creator,Year,Season Number,Episode Number,Duration,Rating" << std::endl;
		for (int i = counter; i < length; i++) {
			if (tv_episode* t = dynamic_cast<tv_episode*>(database[i])) {
				stream << "TV Episode,"
					<< t->get_title() << ","
					<< t->get_show_title() << ","
					<< t->get_creator() << ","
					<< t->get_year() << ","
					<< t->get_season_num() << ","
					<< t->get_episode_num() << ","
					<< t->get_duration() << ","
					<< t->get_rating() << std::endl;
			}
		}
	}
	stream.close();
	std::cout << "Update Successful" << std::endl;
}

//This would be a good spot to build the sorting functions.

void back_to_menu() {
	std::cout << "Press 0 to return back to main menu: ";
	get_input(0);
	std::cout << std::endl;
}

int print_menu_prompt() {
	std::cout << std::endl
		<< "Print Menu" << std::endl
		<< "1 Print all entries in database" << std::endl
		<< "2 Print all Tracks in database" << std::endl
		<< "3 Print all Audio Books in database" << std::endl
		<< "4 Print all TV Episodes in database" << std::endl
		<< "5 Print all entries with a given creator" << std::endl
		<< "6 Print all entries released on or after a given year" << std::endl
		<< "0 Return to previous menu" << std::endl;

	std::cout << "Make a selection: ";

	int selected = -1;
	selected = get_input(6);

	return selected;
}

void print_menu(const std::vector<data*>& database, int length) {
	int selected = 0;
	selected = print_menu_prompt();

	switch (selected) {
	case 0:
		//return 
		break;
	case 1:
		print_database(database, length);
		back_to_menu();
		break;
	case 2:
		print_tracks(database, length);
		back_to_menu();
		break;
	case 3:
		print_audio_books(database, length);
		back_to_menu();
		break;
	case 4:
		print_tv_episodes(database, length);
		back_to_menu();
		break;
	case 5:
		print_by_creator(database, length);
		back_to_menu();
		break;
	case 6:
		print_by_year(database, length);
		back_to_menu();
		break;
	default:
		break;
	}
}

int sort_menu_prompt() {
	std::cout << std::endl
		<< "Sort Menu" << std::endl
		<< "1 Sort all entries by their rating in ascending order" << std::endl
		<< "2 Sort all entries by their rating in descending order" << std::endl
		<< "3 Sort all entries in ascending order based on their year" << std::endl
		<< "4 Sort all entries in descending order based on their year" << std::endl
		<< "5 Sort all entries by the lexicographical order of their title" << std::endl
		<< "0 Return to previous menu" << std::endl;

	std::cout << "Make a selection: ";

	int selected = -1;
	selected = get_input(5);

	return selected;
}

//menu for sorting functions - call sorting functions here in sort_menu switch statement
void sort_menu(std::vector<data*>& database, int length) {
	int selected = 0;
	selected = sort_menu_prompt();

	switch (selected) {
	case 0:
		//return 
		break;
	case 1:
		//Optional: Add "sort all entries by their rating in ascending order" fucntion here
		sort_successful();
		back_to_menu();
		break;
	case 2:
		//Needed: Add "sort all entries by their rating in descending order" fucntion here
		sort_successful();
		back_to_menu();
		break;
	case 3:
		//Needed: Add "sort all entries in ascending order based on their year" fucntion here
		sort_successful();
		back_to_menu();
		break;
	case 4:
		//Optional: Add "sort all entries in descending order based on their year" fucntion here
		sort_successful();
		back_to_menu();
		break;
	case 5:
		//Needed: Add "sort all entries by the lexicographical order of their title" fucntion here
		sort_successful();
		back_to_menu();
		break;
	default:
		break;
	}
}

int menu_prompt() {
	std::cout << std::endl
		<< "Main Menu" << std::endl
		<< "1 Print options" << std::endl
		<< "2 Sort options" << std::endl
		<< "3 Add new entry to database" << std::endl
		<< "4 Remove an entry from database" << std::endl
		<< "5 Yet to be added Stretch Goal" << std::endl
		<< "0 Quit" << std::endl;

	std::cout << "Make a selection: ";

	int selected = -1;
	selected = get_input(5);

	return selected;
}

bool menu(std::vector<data*>& database, int length, const std::string& path) {
	int selected = 0;
	selected = menu_prompt();

	switch (selected) {
	case 1:
		print_menu(database, length);
		break;
	case 2:
		sort_menu(database, length);
		break;
	case 3:
		//add_entry(database, length);
		back_to_menu();
		break;
	case 4:
		//remove_entry(database, length);
		back_to_menu();
		break;
	case 5:
		//Yet to be added Stretch Goal
		back_to_menu();
		break;
	case 0:
		return true;
		break;
	default:
		break;
	}
	return false;
}

int main() {
	const std::string path = "Data\\database.csv";
	
	int length = get_line_count(path) - 3;

	std::vector<data*> database = fill_database(path, length);
	
	bool quit = false;

	do {
		quit = menu(database, length, path);
	} while (quit == false);

	update_csv(database, length, path);

	for (int i = 0; i < length; i++) {
		delete database[i];
	}

	return 0;
}