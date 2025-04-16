#pragma once
#include <string>
#include <iostream>

class data {
protected:
	std::string title;
	std::string creator;
	int year;
	int duration; //minutes

	data(const std::string& title,
		const std::string& creator,
		int year, 
		int duration);

public:
	virtual ~data() = default;

	std::string get_title() const;
	std::string get_creator() const;
	int get_year() const;
	int get_duration() const;

	virtual void print() const = 0;
};