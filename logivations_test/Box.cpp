#pragma once
#include "Box.h"

Box::Box() {
	this->size_x = 0;
	this->size_y = 0;
	this->size_z = 0;
	this->max_of_surface_area = 0;
	set_number_of_orientations();
}

Box::Box(int size_x, int size_y, int size_z) {
	this->size_x = size_x;
	this->size_y = size_y;
	this->size_z = size_z;
	set_max_of_surface_area();
	set_number_of_orientations();
}

void Box::set_id(const int &id) {
	this->id = id;
}

void Box::set_x(const int &size_x) {
	this->size_x = size_x;
}

void Box::set_y(const int &size_y) {
	this->size_y = size_y;
}

void Box::set_z(const int &size_z) {
	this->size_z = size_z;
}

void Box::set_start_parametrs(const int &id, const int &size_x, const int &size_y, const int &size_z) {
	this->id = id;
	this->size_x = size_x;
	this->size_y = size_y;
	this->size_z = size_z;
}

void Box::set_max_of_surface_area() {
	int area_one{ this->size_x * this->size_y }, area_two{ this->size_y * this->size_z }, area_three{ this->size_x * this->size_z };
	this->max_of_surface_area = std::max(std::max(area_one, area_two), area_three);
}

void Box::add_coordinates(const coord &coordinate) {
	this->coordinates.push_back(coordinate);
}

void Box::change_orientation_number(int &orientation) {
	this->orientation = orientation;
}

void Box::set_number_of_orientations() {
	if (this->size_x == this->size_y && this->size_x == this->size_z)
		this->number_of_orientations = 1;
	else
		this->number_of_orientations = 6;
}

void Box::change_orientation(int &orientation) {
	switch (orientation) {
	case 0:
		break;
	case 1: {
		int temp = this->size_x;
		this->size_x = this->size_y;
		this->size_y = temp;
		break;
	}
	case 2: {
		int temp = this->size_y;
		this->size_y = this->size_z;
		this->size_z = temp;
		break;
	}
	case 3: {
		int temp_x{ this->size_x }, temp_y{ this->size_y }, temp_z{ this->size_z };
		this->size_x = temp_z;
		this->size_y = temp_x;
		this->size_z = temp_y;
		break;
	}
	case 4: {
		int temp_x{ this->size_x }, temp_y{ this->size_y }, temp_z{ this->size_z };
		this->size_x = temp_y;
		this->size_y = temp_z;
		this->size_z = temp_x;
		break;
	}
	case 5: {
		int temp = this->size_x;
		this->size_x = this->size_y;
		this->size_y = temp;
		break;
	}
	}
	change_orientation_number(orientation);
}

void Box::set_use(bool use) {
	this->use = use;
}

int Box::get_id() {
	return this->id;
}

int Box::get_x() {
	return this->size_x;
}

int Box::get_y() {
	return this->size_y;
}

int Box::get_z() {
	return this->size_z;
}

bool Box::get_use() {
	return this->use;
}

int Box::get_max_of_surface_area() {
	return this->max_of_surface_area;
}

int Box::get_orientation() {
	return this->orientation;
}

int Box::get_volume() {
	return this->size_x * this->size_y * this->size_z;
}

int Box::get_number_of_orientations() {
	return this->number_of_orientations;
}

coord Box::get_coordinate(const size_t i) {
	if (i >= this->coordinates.size())
		return{ -1, -1, -1 };
	return this->coordinates.at(i); // (0) - left_down, closest to (0;0;0); (1) - right_up, furthest to (0;0;0);
}

std::vector<coord> Box::get_coordinates() {
	std::vector<coord> temp = this->coordinates;
	return temp;
}

size_t Box::get_coordinates_size() {
	return this->coordinates.size();
}

Box Box::operator=(Box &box) {
	this->id = box.get_id();
	this->size_x = box.get_x();
	this->size_y = box.get_y();
	this->size_z = box.get_z();
	this->orientation = box.get_orientation();
	this->max_of_surface_area = box.get_max_of_surface_area();
	this->coordinates = box.get_coordinates();
	return *this;
}

const bool operator!= (Box &box_two, Box &box_one) {										// this boxes isn't cross each other
	return  (((box_two.get_coordinate(0).coord_x >= box_one.get_coordinate(1).coord_x) &&
		(box_two.get_coordinate(0).coord_y >= box_one.get_coordinate(1).coord_y) &&
		(box_two.get_coordinate(0).coord_z >= box_one.get_coordinate(1).coord_z)) ||
		((box_two.get_coordinate(0).coord_x <= box_one.get_coordinate(1).coord_x) &&
			(box_two.get_coordinate(0).coord_y >= box_one.get_coordinate(1).coord_y) &&
			(box_two.get_coordinate(0).coord_z >= box_one.get_coordinate(1).coord_z)) ||
		((box_two.get_coordinate(0).coord_x >= box_one.get_coordinate(1).coord_x) &&
			(box_two.get_coordinate(0).coord_y <= box_one.get_coordinate(1).coord_y) &&
			(box_two.get_coordinate(0).coord_z >= box_one.get_coordinate(1).coord_z)) ||
		((box_two.get_coordinate(0).coord_x <= box_one.get_coordinate(1).coord_x) &&
			(box_two.get_coordinate(0).coord_y <= box_one.get_coordinate(1).coord_y) &&
			(box_two.get_coordinate(0).coord_z >= box_one.get_coordinate(1).coord_z)) ||
		((box_two.get_coordinate(0).coord_x <= box_one.get_coordinate(1).coord_x) &&
			(box_two.get_coordinate(0).coord_y <= box_one.get_coordinate(1).coord_y) &&
			(box_two.get_coordinate(0).coord_z >= box_one.get_coordinate(1).coord_z)) ||
		((box_two.get_coordinate(0).coord_x >= box_one.get_coordinate(1).coord_x) &&
			(box_two.get_coordinate(0).coord_y <= box_one.get_coordinate(1).coord_y) &&
			(box_two.get_coordinate(0).coord_z <= box_one.get_coordinate(1).coord_z)) ||
		((box_two.get_coordinate(0).coord_x <= box_one.get_coordinate(1).coord_x) &&
			(box_two.get_coordinate(0).coord_y >= box_one.get_coordinate(1).coord_y) &&
			(box_two.get_coordinate(0).coord_z <= box_one.get_coordinate(1).coord_z)));
}

const bool operator== (Box &box_two, Box &box_one) {
	return (box_one.get_id() == box_two.get_id());
}