#pragma once
#include "data.h"

class tv_episode : public data {
private:
	std::string show_title;
	int season_number;
	int episode_number;
	int rating; //whole numbers from 1-10

public:
	tv_episode(const std::string& title,
		const std::string& show_title,
		const std::string& creator,
		int year,
		int season_number,
		int episode_number,
		int duration,
		bool rating);

	std::string get_show_title() const;
	int get_season_number() const;
	int get_episode_number() const;
	int get_rating() const;

	void print() const override;
};