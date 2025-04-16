#include "data.h"

data::data(const std::string& title, 
	const std::string& creator, 
	int year, int duration) {

	if (title.length() > 0) {
		this->title = title;
	}
	else {
		throw std::exception("Title can not be empty");
	}

	if (creator.length() > 0) {
		this->creator = creator;
	}
	else {
		throw std::exception("Creator can not be empty");
	}

	if (year >= 1800 && year <= 2025) {
		this->year = year;
	}
	else {
		throw std::exception("Year must be between 1800 and 2025 (inlcusive)");
	}

	if (duration >= 0 && duration <= 1440) {
		this->duration = duration;
	}
	else {
		throw std::exception("Duration can not be negative or greater than 1440 minutes (24 hours)");
	}
}

std::string data::get_title() const {
	return title;
}

std::string data::get_creator() const {
	return creator;
}

int data::get_year() const {
	return year;
}

int data::get_duration() const {
	return duration;
}

