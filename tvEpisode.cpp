#include "tvEpisode.h"

tv_episode::tv_episode(const std::string& title,
	const std::string& show_title,
	const std::string& creator, int year, 
	int season_num, int episode_num,
	double duration, int rating)
	: data(title, creator, year, duration) {\

	if (show_title.length() > 0) {
		this->show_title = show_title;
	}
	else {
		throw std::exception("Show title can not be empty");
	}

	if (season_num > 0 && season_num <= 1000) {
		this->season_num = season_num;
	}
	else {
		throw std::exception("Season number must be between 1 and 1000 (inclusive)");
	}

	if (episode_num > 0 && episode_num <= 10000) {
		this->episode_num = episode_num;
	}
	else {
		throw std::exception("Episode number must be between 1 and 10000 (inclusive)");
	}

	if (rating >= 0 && rating <= 10) {
		this->rating = rating;
	}
	else {
		throw std::exception("TV episode rating must be between 0 and 10 (inlcusive)");
	}
}

std::string tv_episode::get_show_title() const {
	return show_title;
}

int tv_episode::get_season_num() const {
	return season_num;
}

int tv_episode::get_episode_num() const {
	return episode_num;
}

int tv_episode::get_rating() const {
	return rating;
}