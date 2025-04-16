#include "track.h"

track::track(const std::string& title,
	const std::string& creator,
	const std::string& album,
	int year, int duraiton,
	double rating) 
	: data(title, creator, year, duration) {

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
		throw std::exception("Rating can not be empty");
	}
}

std::string track::get_album() const {
	return album;
}

double track::get_rating() const {
	return rating;
}