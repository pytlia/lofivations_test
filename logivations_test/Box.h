#pragma once
#include <vector>
#include <string>
#include <algorithm>

struct coord {
	int coord_x = 0;
	int coord_y = 0;
	int coord_z = 0;

	coord() {};

	coord(int x, int y, int z) {
		this->coord_x = x;
		this->coord_y = y;
		this->coord_z = z;
	}
};

struct products {
	int id;
	int count;
	bool in_order = false;
};

class Box {
private:
	int id;

	int size_x;
	int size_y;
	int size_z;

	bool use{ false };

	int number_of_orientations{ 6 };

	int orientation{ 0 };

	std::vector<coord> coordinates; // (0) first - left_down, (1) last - right_up

	int max_of_surface_area;
public:
	Box();

	Box(int size_x, int size_y, int size_z);

	void set_id(const int &id);

	void set_x(const int &size_x);

	void set_y(const int &size_y);

	void set_z(const int &size_z);

	void set_start_parametrs(const int &id, const int &size_x, const int &size_y, const int &size_z);

	void set_max_of_surface_area();

	void add_coordinates(const coord &coordinate);

	void change_orientation_number(int &orientation);

	void set_number_of_orientations();

	void change_orientation(int &orientation);

	void set_use(bool use);

	int get_id();

	int get_x();

	int get_y();

	int get_z();

	bool get_use();

	int get_max_of_surface_area();

	int get_orientation();

	int get_volume();

	int get_number_of_orientations();

	coord get_coordinate(const size_t i);

	std::vector<coord> get_coordinates();

	size_t get_coordinates_size();

	Box operator=(Box &box);
};

const bool operator!= (Box &box_two, Box &box_one);

const bool operator== (Box &box_two, Box &box_one);