#include "Container.h"

Container::Container() {
	this->size_x = 0;
	this->size_y = 0;
	this->size_z = 0;
	coord temp = { 0,0,0 };
	add_possible_dot_to_put(temp);
}

Container::Container(int size_x, int size_y, int size_z) {
	this->size_x = size_x;
	this->size_y = size_y;
	this->size_z = size_z;
	coord temp = { 0,0,0 };
	add_possible_dot_to_put(temp);
}

void Container::set_id(const int &id) {
	this->id = id;
}

void Container::set_x(const int &size_x) {
	this->size_x = size_x;
}

void Container::set_y(const int &size_y) {
	this->size_y = size_y;
}

void Container::set_z(const int &size_z) {
	this->size_z = size_z;
}

void Container::set_start_parametrs(const int &id, const int &size_x, const int &size_y, const int &size_z) {
	this->id = id;
	this->size_x = size_x;
	this->size_y = size_y;
	this->size_z = size_z;
}

void Container::add_boxes(Box &in) {
	this->in_this.push_back(in);
}

void Container::add_possible_dot_to_put(coord & dot) {
	this->possible_dots_to_put.push_back(dot);
}

void Container::sorting_dots() {
	bool done;
	do {
		done = true;
		for (size_t i{ 0 }; i < this->possible_dots_to_put.size() - 1; i++) {
			bool need_to_swap{ false };
			size_t to_swap_with_this{ 0 };
			for (size_t j{ i + 1 }; j < this->possible_dots_to_put.size(); j++) {
				if (this->possible_dots_to_put.at(j).coord_z <= this->possible_dots_to_put.at(i).coord_z) {
					if (this->possible_dots_to_put.at(j).coord_z == this->possible_dots_to_put.at(i).coord_z) {
						if (this->possible_dots_to_put.at(j).coord_y <= this->possible_dots_to_put.at(i).coord_y) {
							if (this->possible_dots_to_put.at(j).coord_y == this->possible_dots_to_put.at(i).coord_y) {
								if (this->possible_dots_to_put.at(j).coord_x < this->possible_dots_to_put.at(i).coord_x) {
									need_to_swap = true;
									to_swap_with_this = j;
								}
							}
							else {
								need_to_swap = true;
								to_swap_with_this = j;
							}
						}
					}
					else {
						need_to_swap = true;
						to_swap_with_this = j;
					}
				}
			}
			if (need_to_swap) {
				done = false;
				coord temp = this->possible_dots_to_put.at(i);
				this->possible_dots_to_put.at(i) = this->possible_dots_to_put.at(to_swap_with_this);
				this->possible_dots_to_put.at(to_swap_with_this) = temp;
			}
		}
	} while (!done);
}

void Container::set_all_dots_from_this_box(size_t coord_what_you_choose, Box &box) {
	coord dot_to_put;
	this->possible_dots_to_put.erase(possible_dots_to_put.begin() + coord_what_you_choose);
	dot_to_put.coord_x = box.get_coordinate(0).coord_x;						//
	dot_to_put.coord_y = box.get_coordinate(0).coord_y;						//   up corner
	dot_to_put.coord_z = box.get_coordinate(0).coord_z + box.get_z();		//
	add_possible_dot_to_put(dot_to_put);
	dot_to_put.coord_x = box.get_coordinate(0).coord_x;						//
	dot_to_put.coord_y = box.get_coordinate(0).coord_y + box.get_y();		//   left down
	dot_to_put.coord_z = box.get_coordinate(0).coord_z;						//
	add_possible_dot_to_put(dot_to_put);
	dot_to_put.coord_x = box.get_coordinate(1).coord_x;						//
	dot_to_put.coord_y = box.get_coordinate(1).coord_y;						//   far right down
	dot_to_put.coord_z = box.get_coordinate(1).coord_z - box.get_z();		//
	add_possible_dot_to_put(dot_to_put);
	dot_to_put.coord_x = box.get_coordinate(0).coord_x + box.get_x();		//
	dot_to_put.coord_y = box.get_coordinate(0).coord_y;						//   close right down
	dot_to_put.coord_z = box.get_coordinate(0).coord_z;						//
	add_possible_dot_to_put(dot_to_put);
	sorting_dots();
}

int Container::get_id() {
	return this->id;
}

int Container::get_x() {
	int temp = this->size_x;
	return temp;
}

int Container::get_y() {
	return this->size_y;
}

int Container::get_z() {
	return this->size_z;
}

int Container::get_container_volume() {
	return this->size_x * this->size_y * this->size_z;
}

int Container::get_count_of_boxes_inside() {
	return (int)this->in_this.size();
}

size_t Container::how_much_dots() {
	return this->possible_dots_to_put.size();
}

coord Container::get_possible_dot_to_put(size_t i) {
	return this->possible_dots_to_put.at(i);
}

std::vector<coord> Container::get_all_dots_to_put() {
	return this->possible_dots_to_put;
}

std::vector<Box> Container::get_in_this() {
	return this->in_this;
}

Box Container::get_box(size_t i) {
	return this->in_this.at(i);
}

int Container::volume_all_boxes() {
	int volume{ 0 };
	for (int i{ 0 }; i < (int)this->in_this.size(); volume += this->in_this.at(i).get_x() *
		this->in_this.at(i).get_y() *
		this->in_this.at(i).get_z(), i++)
		continue;
	return volume;
}

bool Container::if_this_box_on_the_floor_or_on_the_area_of_other_boxes(Box &box) {
	bool if_this_box_on_other{ false };
	std::vector<bool> points_on_area(4, false); /* is all boottom points of this box are on other boxes up areas:
												(0) - left_down
												(1) - left_up
												(2) - right_up
												(3) - right_down

												(1) -------------- (2)			___
												|					|		   /   \
												|					|		  /     |
												|					|		 |  	V     they are recorded clockwise
												|					|		  \	   __
												|					|		   \____|
												(0) -------------- (3)
												*/
	for (size_t i{ 0 }; i < this->in_this.size(); i++) {
		Box temp = this->in_this.at(i);
		int not_on_area{ 0 };
		for (size_t j{ 0 }; j < points_on_area.size(); j++)
			if (!points_on_area.at(j))
				not_on_area++;
		if (box.get_coordinate(0).coord_z == temp.get_coordinate(1).coord_z) {
			for (size_t j{ 0 }; j < points_on_area.size(); j++) {
				if (!points_on_area.at(j)) {
					if ((box.get_coordinate(0).coord_y <= temp.get_coordinate(1).coord_y &&
						box.get_coordinate(0).coord_y >= temp.get_coordinate(1).coord_y - temp.get_y()) &&
						(box.get_coordinate(0).coord_x <= temp.get_coordinate(1).coord_x &&
							box.get_coordinate(0).coord_x >= temp.get_coordinate(1).coord_x - temp.get_x())) {
						points_on_area.at(j) = true;
						not_on_area--;
					}

				}
			}
		}
		if (!not_on_area) {
			if_this_box_on_other = true;
			return if_this_box_on_other;
		}
	}
	return (box.get_coordinate(0).coord_z == 0);
}

bool Container::if_this_box_intersect_with_other_boxes(Box &box) {
	for (size_t i{ 0 }; i < this->in_this.size(); i++) {
		Box temp = this->in_this.at(i);
		if (!(box != temp))
			return false;
	}
	return true;
}

bool Container::if_this_box_can_be_in_this_container(Box &box) {
	return ((if_this_box_on_the_floor_or_on_the_area_of_other_boxes(box)) &&	// if this box on the floor or on the area of other boxes
		((box.get_coordinate(0).coord_x >= 0									//-------
			&& box.get_coordinate(0).coord_y >= 0								//
			&& box.get_coordinate(0).coord_z >= 0) &&							// box int container, not in otherside
			(box.get_coordinate(1).coord_x <= this->size_x						//
				&& box.get_coordinate(1).coord_y <= this->size_y				//
				&& box.get_coordinate(1).coord_z <= this->size_z)) &&	//-------
		(volume_all_boxes() + box.get_volume() <= get_container_volume()) &&	// sum of all boxes volume (for all over in container) must not be greater of container's volume
		(if_this_box_intersect_with_other_boxes(box)));							// if this box intersect with other boxes
}

const bool operator== (Container &container_two, Container &container_one) {
	if (container_one.get_count_of_boxes_inside() == container_two.get_count_of_boxes_inside()) {
		for (int i{ 0 }; i < container_one.get_count_of_boxes_inside(); i++) {
			bool is_this_box_there{ false };
			for (int j{ 0 }; j < container_two.get_count_of_boxes_inside(); j++) {
				if (container_one.get_box(i) == container_two.get_box(j)) {
					is_this_box_there = true;
					break;
				}
			}
			if (!is_this_box_there)
				return false;
		}
	}
	return true;
}