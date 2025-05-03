// See README for details
#include "track.h"
#include "audioBook.h"
#include "tvEpisode.h"
#include <fstream>
#include <algorithm>
#include <vector>
#include <set>

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
				int year = std::stoi(line);

				std::getline(stream, line, ',');
				double duration = std::stod(line);

				std::getline(stream, line);
				double rating = std::stod(line);

				database.push_back(new track(title, creator, album, year, duration, rating));
			}

			if (tracker == "Audio Book") {
				std::getline(stream, line, ',');
				std::string title = line;

				std::getline(stream, line, ',');
				std::string creator = line;

				std::getline(stream, line, ',');
				int year = std::stoi(line);

				std::getline(stream, line, ',');
				double duration = std::stoi(line);

				std::getline(stream, line);
				bool rating = std::stoi(line);

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
				int year = std::stoi(line);

				std::getline(stream, line, ',');
				int season = std::stoi(line);

				std::getline(stream, line, ',');
				int episode = std::stoi(line);

				std::getline(stream, line, ',');
				double duration = std::stod(line);

				std::getline(stream, line);
				double rating = std::stod(line);

				database.push_back(new tv_episode(title, show_title, creator, year, season, episode, duration, rating));
			}
		}
		stream.close();
	}
	return database;
}

void print_database(const std::vector<data*>& database) {
	std::cout << std::endl 
		<< "Database: " << std::endl;

	for (int i = 0; i < database.size(); i++) {
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

void print_tracks(const std::vector<data*>& database) {
	std::cout << std::endl 
		<< "Tracks: " << std::endl;

	for (int i = 0; i < database.size(); i++) {
		if (track* t = dynamic_cast<track*>(database[i])) {
			t->print();
		}
	}
	std::cout << std::endl;
}

void print_audio_books(const std::vector<data*>& database) {
	std::cout << std::endl 
		<< "Audio Books: " << std::endl;

	for (int i = 0; i < database.size(); i++) {
		if (audio_book* b = dynamic_cast<audio_book*>(database[i])) {
			b->print();
		}
	}
	std::cout << std::endl;
}

void print_tv_episodes(const std::vector<data*>& database) {
	std::cout << std::endl 
		<< "TV Episodes: " << std::endl;

	for (int i = 0; i < database.size(); i++) {
		if (tv_episode* e = dynamic_cast<tv_episode*>(database[i])) {
			e->print();
		}
	}
	std::cout << std::endl;
}

void invalid_input() {
	std::cout << "Invalid entry, please make another seleciton: ";
}

bool verify_num(const std::string& input, bool decimal) {
	for (int i = 0; i < input.length(); i++) {
		if (!std::isdigit(input[i])) {
			if (decimal == true && input[i] == '.') {
				//pass value
			}
			else {
				return false;
			}
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

		if (input.length() > 0 && verify_num(input, false) == true && within_range(input, range) == true) {
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

void creators(const std::vector<data*>& database) {
	std::set<std::string> creators;

	std::cout << std::endl << "List of creators in databse: " << std::endl;

	for (int i = 0; i < database.size(); i++) {
		if (base_data* d = dynamic_cast<base_data*>(database[i])) {
			creators.insert(d->get_creator());
		}
	}

	for (std::string i : creators) {
		std::cout << i << std::endl;
	}
}

void print_by_creator(const std::vector<data*>& database) {
	std::string creator = "Unknown";
	int counter = 0;

	creators(database);

	std::cout << "Note: Search is case and space sensitive" << std::endl;
	std::cout << "Enter creator: ";

	creator = get_input();
	std::cout << std::endl;

	for (int i = 0; i < database.size(); i++) {
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
		std::cout << "No entries in database match creator: " << creator << std::endl;
	}
	std::cout << std::endl;
}

void years(const std::vector<data*>& database) {
	int dates[2] = {1991, 1991};

	for (int i = 0; i < database.size(); i++) {
		if (base_data* d = dynamic_cast<base_data*>(database[i])) {
			if (d->get_year() < dates[0]) {
				dates[0] = d->get_year();
			}
			if (d->get_year() > dates[1]) {
				dates[1] = d->get_year();
			}
		}
	}

	std::cout << std::endl << "Oldest entry: " << dates[0] << " Newest entry: " << dates[1] << std::endl;
}

void print_by_year(const std::vector<data*>& database) {
	int year = 0, counter = 0;

	years(database);

	std::cout << "Note: Space sensitive" << std::endl;
	std::cout << "Enter year: ";

	year = get_input(2025);
	std::cout << std::endl;

	for (int i = 0; i < database.size(); i++) {
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

void back_to_menu() {
	std::cout << "Press 0 to return back to main menu: ";
	get_input(0);
	std::cout << std::endl;
}

void sort_successful() {
	std::cout << std::endl << "Sort successful" << std::endl;
}

void sort_for_csv(std::vector<data*>& database) {
	//moves all tracks to top of list, followed by moving all audio book after tracks leaving tv episodes at end of list
	int index = 0;
	for (int i = 0; i < database.size(); i++) {
		if (track* e = dynamic_cast<track*>(database[i])) {
			std::swap(database[i], database[index]);
			index++;
		}
	}
	for (int i = index; i < database.size(); i++) {
		if (audio_book* e = dynamic_cast<audio_book*>(database[i])) {
			std::swap(database[i], database[index]);
			index++;
		}
	}
}

//This would be a good spot to build the sorting functions.
void sort_by_rating(std::vector<data*>& database) {
	// Sort by rating in descending order

	sort_successful();
}

void sort_by_year(std::vector<data*>& database) {
	// Sort by rating in ascending order

	sort_successful();
}

void sort_lexicographical(std::vector<data*>& database) {
	// sort by numberical / alphebetical order (as would be in dictionary)

	sort_successful();
}

void shuffle(const std::vector<data*>& database) {
	
}

void update_csv(std::vector<data*>& database, const std::string& path) {
	std::cout << std::endl << "Updating database..." << std::endl;
	sort_for_csv(database);

	std::ofstream stream;
	int counter = 0;

	stream.open(path);
	if (stream.is_open()) {
		stream << "Track,Title,Creator,Album,Year,Duration,Rating" << std::endl;
		for (int i = 0; i < database.size(); i++) {
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
		for (int i = counter; i < database.size(); i++) {
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
		for (int i = counter; i < database.size(); i++) {
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
	std::cout << "Update Successful" << std::endl << std::endl;
}

bool verify_title(const std::vector<data*>& database, std::string& title) {
	for (int i = 0; i < database.size(); i++) {
		if (base_data* b = dynamic_cast<base_data*>(database[i])) {
			if (b->get_title() == title) {
				return true;
			}
		}
	}

	return false;
}

void add_track(std::vector<data*>& database, const std::string& path) {
	sort_for_csv(database);

	std::string line;
	bool next = false;

	std::cout << std::endl << "Title: ";
	std::string title = "";
	do {
		std::getline(std::cin, line);

		if (line.length() > 0) {
			title = line;
			next = true;
		}
		else {
			invalid_input();
		}
	} while (next == false);

	next = false;
	std::cout << "Creator: ";
	std::string creator = "";
	do {
		std::getline(std::cin, line);

		if (line.length() > 0) {
			creator = line;
			next = true;
		}
		else {
			invalid_input();
		}
	} while (next == false);

	next = false;
	std::cout << "Album: ";
	std::string album = "";
	do {
		std::getline(std::cin, line);

		if (line.length() > 0) {
			album = line;
			next = true;
		}
		else {
			invalid_input();
		}
	} while (next == false);

	next = false;
	std::cout << "Year (integer 1800-2025 inlcusive): ";
	int year = 0;
	do {
		std::getline(std::cin, line);

		if (line.length() > 0 && verify_num(line, false) && within_range(line, 2025) == true) {
			year = std::stoi(line);
			next = true;
		}
		else {
			invalid_input();
		}
	} while (next == false);

	next = false;
	std::cout << "Duration in minutes (decimal 0-100000 inlcusive): ";
	double duration = 0;
	do {
		std::getline(std::cin, line);

		if (line.length() > 0 && verify_num(line, true) && within_range(line, 100000) == true) {
			duration = std::stod(line);
			next = true;
		}
		else {
			invalid_input();
		}
	} while (next == false);

	next = false;
	std::cout << "Rating (decimal 0-5 inlcusive): ";
	double rating = 0;
	do {
		std::getline(std::cin, line);

		if (line.length() > 0 && verify_num(line, true) && within_range(line, 5) == true) {
			rating = std::stod(line);
			next = true;
		}
		else {
			invalid_input();
		}
	} while (next == false);
	
	bool in_database = verify_title(database, title);

	if (in_database == false) {
		database.push_back(new track(title, creator, album, year, duration, rating));
		update_csv(database, path);
	}
	else {
		std::cout << std::endl << "Track already in database" << std::endl;
	}
}

void add_audio_book(std::vector<data*>& database, const std::string& path) {
	sort_for_csv(database);
	
	std::string line;
	bool next = false;

	std::cout << std::endl << "Title: ";
	std::string title = "";
	do {
		std::getline(std::cin, line);

		if (line.length() > 0) {
			title = line;
			next = true;
		}
		else {
			invalid_input();
		}
	} while (next == false);

	next = false;
	std::cout << "Creator: ";
	std::string creator = "";
	do {
		std::getline(std::cin, line);

		if (line.length() > 0) {
			creator = line;
			next = true;
		}
		else {
			invalid_input();
		}
	} while (next == false);

	next = false;
	std::cout << "Year (integer 1800-2025 inlcusive): ";
	int year = 0;
	do {
		std::getline(std::cin, line);

		if (line.length() > 0 && verify_num(line, false) && within_range(line, 2025) == true) {
			year = std::stoi(line);
			next = true;
		}
		else {
			invalid_input();
		}
	} while (next == false);

	next = false;
	std::cout << "Duration in minutes (decimal 0-100000 inlcusive): ";
	double duration = 0;
	do {
		std::getline(std::cin, line);

		if (line.length() > 0 && verify_num(line, true) && within_range(line, 100000) == true) {
			duration = std::stod(line);
			next = true;
		}
		else {
			invalid_input();
		}
	} while (next == false);

	next = false;
	std::cout << "Rating, type 1 for thumbs up or 0 for thumbs down: ";
	bool rating = true;
	do {
		std::getline(std::cin, line);

		if (line.length() > 0 && verify_num(line, false) && (line == "0" || line == "1")) {
			rating = std::stoi(line);
			next = true;
		}
		else {
			invalid_input();
		}
	} while (next == false);

	bool in_database = verify_title(database, title);

	if (in_database == false) {
		database.push_back(new audio_book(title, creator, year, duration, rating));
		update_csv(database, path);
	}
	else {
		std::cout << std::endl << "Audio Book already in database" << std::endl;
	}
}

void add_tv_episode(std::vector<data*>& database, const std::string& path) {
	sort_for_csv(database);
	
	std::string line;
	bool next = false;

	std::cout << std::endl << "Title: ";
	std::string title = "";
	do {
		std::getline(std::cin, line);

		if (line.length() > 0) {
			title = line;
			next = true;
		}
		else {
			invalid_input();
		}
	} while (next == false);

	next = false;
	std::cout << "Show title: ";
	std::string show_title = "";
	do {
		std::getline(std::cin, line);

		if (line.length() > 0) {
			show_title = line;
			next = true;
		}
		else {
			invalid_input();
		}
	} while (next == false);

	next = false;
	std::cout << "Creator: ";
	std::string creator = "";
	do {
		std::getline(std::cin, line);

		if (line.length() > 0) {
			creator = line;
			next = true;
		}
		else {
			invalid_input();
		}
	} while (next == false);

	next = false;
	std::cout << "Year (integer 1800-2025 inlcusive): ";
	int year = 0;
	do {
		std::getline(std::cin, line);

		if (line.length() > 0 && verify_num(line, false) && within_range(line, 2025) == true) {
			year = std::stoi(line);
			next = true;
		}
		else {
			invalid_input();
		}
	} while (next == false);

	next = false;
	std::cout << "Season number (integer 0-1000 inlcusive): ";
	int season_num = 0;
	do {
		std::getline(std::cin, line);

		if (line.length() > 0 && verify_num(line, false) && within_range(line, 1000) == true) {
			season_num = std::stoi(line);
			next = true;
		}
		else {
			invalid_input();
		}
	} while (next == false);

	next = false;
	std::cout << "Episode number (integer 0-100000 inlcusive): ";
	int episode_num = 0;
	do {
		std::getline(std::cin, line);

		if (line.length() > 0 && verify_num(line, false) && within_range(line, 100000) == true) {
			episode_num = std::stoi(line);
			next = true;
		}
		else {
			invalid_input();
		}
	} while (next == false);

	next = false;
	std::cout << "Duration in minutes (decimal 0-100000 inlcusive): ";
	double duration = 0;
	do {
		std::getline(std::cin, line);

		if (line.length() > 0 && verify_num(line, true) && within_range(line, 100000) == true) {
			duration = std::stod(line);
			next = true;
		}
		else {
			invalid_input();
		}
	} while (next == false);

	next = false;
	std::cout << "Rating (decimal 0-10 inlcusive): ";
	double rating = 0;
	do {
		std::getline(std::cin, line);

		if (line.length() > 0 && verify_num(line, true) && within_range(line, 10) == true) {
			rating = std::stod(line);
			next = true;
		}
		else {
			invalid_input();
		}
	} while (next == false);

	bool in_database = verify_title(database, title);

	if (in_database == false) {
		database.push_back(new tv_episode(title, show_title, creator, year, season_num, episode_num, duration, rating));
		update_csv(database, path);
	}
	else {
		std::cout << std::endl << "TV Episode already in database" << std::endl;
	}
}

int add_entry_prompt() {
	std::cout << std::endl
		<< "Add entry" << std::endl
		<< "1 Track" << std::endl
		<< "2 Audio Book" << std::endl
		<< "3 TV Episode" << std::endl
		<< "0 Return to previous menu" << std::endl;

	std::cout << "Make a selection: ";

	int selected = 0;
	selected = get_input(3);

	return selected;
}

void add_entry_menu(std::vector<data*>& database, const std::string& path) {
	int selected = 0;
	selected = add_entry_prompt();

	switch (selected) {
	case 1:
		add_track(database, path);
		back_to_menu();
		break;
	case 2:
		add_audio_book(database, path);
		back_to_menu();
		break;
	case 3:
		add_tv_episode(database, path);
		back_to_menu();
		break;
	case 0:
		//return
		std::cout << std::endl;
		break;
	default:
		break;
	}
}

void remove_entry(std::vector<data*>& database, const std::string& path) {
	std::string title;
	bool match = false;

	std::cout << std::endl << "Note: Case and space sensitive" << std::endl;
	std::cout << "Enter title name to remove from database: ";

	title = get_input();

	for (int i = 0; i < database.size(); i ++) {
		if (base_data* d = dynamic_cast<base_data*>(database[i])) {
			if (d->get_title() == title) {
				std::cout << std::endl << title << " matches title in database" << std::endl;
				match = true;

				database.erase(database.begin() + i);
				update_csv(database, path);
			}
		}
	}
	if (match == false) {
		std::cout << std::endl << "No matches found in database for " << title << std::endl;
	}
}

void remove_entry_tv_episode(std::vector<data*>& database, const std::string& path) {
	std::string title;
	bool match = false;

	std::cout << std::endl << "Note: Case and space sensitive" << std::endl;
	std::cout << "Enter show title name to remove from database: ";

	title = get_input();

	for (int i = 0; i < database.size(); i++) {
		if (tv_episode* e = dynamic_cast<tv_episode*>(database[i])) {
			if (e->get_show_title() == title) {
				std::cout << std::endl << title << " matches show title in database" << std::endl;
				match = true;

				database.erase(database.begin() + i);
				update_csv(database, path);
			}
		}
	}
	if (match == false) {
		std::cout << std::endl << "No matches found in database for " << title << std::endl;
	}
}

int remove_entry_prompt() {
	std::cout << std::endl
		<< "Remove Entry Menu" << std::endl
		<< "1 Remove track" << std::endl
		<< "2 Remove audio book" << std::endl
		<< "3 Remove tv episode" << std::endl
		<< "0 Return to previous menu" << std::endl;

	std::cout << "Make a selection: ";

	int selected = 0;
	selected = get_input(3);

	return selected;
}

void remove_entry_menu(std::vector<data*>& database, const std::string& path) {
	int selected = 0;
	selected = remove_entry_prompt();

	switch (selected) {
	case 1:
		remove_entry(database, path);
		break;
	case 2:
		remove_entry(database, path);
		break;
	case 3:
		remove_entry_tv_episode(database, path);
		break;
	case 0:
		//return 
		std::cout << std::endl;
		break;
	default:
		break;
	}
}

int menu_prompt() {
	std::cout << "Main Menu" << std::endl
		<< "1 Print all entries in database" << std::endl
		<< "2 Print all Tracks in database" << std::endl
		<< "3 Print all Audio Books in database" << std::endl
		<< "4 Print all TV Episodes in database" << std::endl
		<< "5 Print all entries with a given creator" << std::endl
		<< "6 Print all entries released on or after a given year" << std::endl
		<< "7 Sort all entries by their rating in descending order" << std::endl
		<< "8 Sort all entries in ascending order based on their year" << std::endl
		<< "9 Sort all entries by the lexicographical order of their title" << std::endl
		<< "10 Add new entry to database" << std::endl
		<< "11 Remove an entry from database" << std::endl
		<< "12 Print shuffled colleciton of music tracks" << std::endl
		<< "0 Quit" << std::endl;

	std::cout << "Make a selection: ";

	int selected = 0;
	selected = get_input(12);

	return selected;
}

bool menu(std::vector<data*>& database, const std::string& path) {
	int selected = 0;
	selected = menu_prompt();

	switch (selected) {
	case 1:
		print_database(database);
		back_to_menu();
		return false;
	case 2:
		print_tracks(database);
		back_to_menu();
		return false;
	case 3:
		print_audio_books(database);
		back_to_menu();
		return false;
	case 4:
		print_tv_episodes(database);
		back_to_menu();
		return false;
	case 5:
		print_by_creator(database);
		back_to_menu();
		return false;
	case 6:
		print_by_year(database);
		back_to_menu();
		return false;
	case 7:
		sort_by_rating(database);
		back_to_menu();
		return false;
	case 8:
		sort_by_year(database);
		back_to_menu();
		return false;
	case 9:
		sort_lexicographical(database);
		back_to_menu();
		return false;
	case 10:
		add_entry_menu(database, path);
		return false;
	case 11:
		remove_entry_menu(database, path);
		return false;
	case 12:
		shuffle(database);
		back_to_menu();
		return false;
	case 0:
		return true;
	default:
		return false;
	}
}

void starting_message() {
	std::cout << "Final Project: Default Proposal \nBy: Troy Poniewaz & Nicholas Price" << std::endl << std::endl;
}

void end_message() {
	std::cout << "Thank you for using our program, have a great day" << std::endl;
}

int main() {
	const std::string path = "Data\\database.csv";
	
	int length = get_line_count(path) - 3;

	std::vector<data*> database = fill_database(path, length);
	
	starting_message();

	bool quit = false;

	do {
		quit = menu(database, path);
	} while (quit == false);

	update_csv(database, path);

	for (int i = 0; i < database.size(); i++) {
		delete database[i];
	}

	end_message();

	return 0;
}