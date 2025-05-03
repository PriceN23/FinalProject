#pragma once
#include "baseData.h"

class audio_book : public base_data {
private:
	bool rating; //tumb up/thumb down

public:
	audio_book(const std::string& title,
		const std::string& creator,
		int year,
		double duration,
		bool rating);

	bool get_rating() const;

	void print() const override;
};