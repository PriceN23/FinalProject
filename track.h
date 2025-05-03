#pragma once
#include "baseData.h"

class track : public base_data {
private:
	std::string album;
	double rating;

public:
	track(const std::string& title,
		const std::string& creator, 
		const std::string& album,
		int year,
		double duraiton,
		double rating);

	std::string get_album() const;
	double get_rating() const;

	void print() const override;
};
