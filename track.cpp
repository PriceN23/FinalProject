#include "track.h"

track::track(const std::string& title,
	const std::string& creator,
	const std::string& album, int year, 
	double duration, double rating) 
	: base_data(title, creator, year, duration) {
	
	if (album.length() > 0) {
		this->album = album;
	}
	else {
		throw std::exception("Album can not be empty");
	}

	if (rating >= 0.0 && rating <= 5.0) {
		this->rating = rating;
	}
	else {
		throw std::exception("Track rating must be decimal between 0 and 5 (inclusive)");
	}
}

std::string track::get_album() const {
	return album;
}

double track::get_rating() const {
	return rating;
}

void track::print() const {
	std::cout << "Track: " << title
		<< ", by " << creator
		<< " [" << album
		<< ", " << year
		<< "] (" << duration
		<< " min) " << rating
		<< "/5" << std::endl;
}