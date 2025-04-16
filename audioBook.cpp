#include "audioBook.h"

audio_book::audio_book(const std::string& title,
	const std::string& creator, int year, 
	int duration, bool rating) 
	: data(title, creator, year, duration) {

	if (rating == true || rating == false) {
		this->rating = rating;
	}
	else {
		throw std::exception("Audio book rating must be true or false");
	}
}

bool audio_book::get_rating() const {
	return rating;
}