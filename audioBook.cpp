#include "audioBook.h"

audio_book::audio_book(const std::string& title,
	const std::string& creator, int year, 
	double duration, double rating)
	: base_data(title, creator, year, duration) {

	if (rating >= 0 && rating <= 1) {
		this->rating = rating;
	}
	else {
		throw std::exception("Audio book rating must be true or false");
	}
}

double audio_book::get_rating() const {
	return rating;
}

void audio_book::print() const {
	std::cout << "Audio Book: " << title
		<< " [" << creator
		<< ", " << year
		<< "] (" << duration
		<< " min) " << rating << std::endl;
}