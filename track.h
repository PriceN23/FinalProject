#pragma once
#include "data.h"

class track : public data {
private:
	std::string album;
	double rating; //decimal values from 0-5

public:
	track(const std::string& title,
		const std::string& creator, 
		const std::string& album,
		int year, 
		int duraiton,
		double rating);

	std::string get_album() const;
	double get_rating() const;

	void print() const override;
};
