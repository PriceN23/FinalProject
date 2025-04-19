#pragma once
#include "baseData.h"

class audio_book : public base_data {
private:
	double rating; //tumb up/thumb down, need to ask Brian if this is yes/no or quantity of like/dislikes

public:
	audio_book(const std::string& title,
		const std::string& creator,
		int year,
		double duration,
		double rating);

	double get_rating() const;

	void print() const override;
};