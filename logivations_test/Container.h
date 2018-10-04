#pragma once
#include "Box.h"

class Container {
private:
	int id;

	int size_x;
	int size_y;
	int size_z;

	std::vector<Box> in_this;
	std::vector<coord> possible_dots_to_put;

public:
	Container();

	Container(int size_x, int size_y, int size_z);

	void set_id(const int &id);

	void set_x(const int &size_x);

	void set_y(const int &size_y);

	void set_z(const int &size_z);

	void set_start_parametrs(const int &id, const int &size_x, const int &size_y, const int &size_z);

	void add_boxes(Box &in);

	void add_possible_dot_to_put(coord & dot);

	void sorting_dots();

	void set_all_dots_from_this_box(size_t coord_what_you_choose, Box &box);

	int get_id();

	int get_x();

	int get_y();

	int get_z();

	int get_container_volume();

	int get_count_of_boxes_inside();

	size_t how_much_dots();

	coord get_possible_dot_to_put(size_t i);

	std::vector<coord> get_all_dots_to_put();

	std::vector<Box> get_in_this();

	Box get_box(size_t i);

	int volume_all_boxes();

	bool if_this_box_on_the_floor_or_on_the_area_of_other_boxes(Box &box);

	bool if_this_box_intersect_with_other_boxes(Box &box);

	bool if_this_box_can_be_in_this_container(Box &box);

};

const bool operator== (Container &container_two, Container &container_one);