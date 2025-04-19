#pragma once
#include "data.h"
#include <string>
#include <iostream>

class base_data : public data {
protected:
	std::string title;
	std::string creator;
	int year;
	double duration;

	base_data(const std::string& title,
		const std::string& creator,
		int year, 
		double duration);

public:
	std::string get_title() const;
	std::string get_creator() const;
	int get_year() const;
	double get_duration() const;

	virtual void print() const = 0;
};