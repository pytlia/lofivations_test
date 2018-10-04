#include "Order.h"

Order::Order() {
	this->id = 0;
}

Order::Order(const int id, std::vector<products> &product_id) {
	this->id = id;
	this->product_id = product_id;
}

void Order::set_id(const int &id) {
	this->id = id;
}

void Order::add_product_id(const int &id) {
	products temp;
	temp.id = id;
	this->product_id.push_back(temp);
}

void Order::set_product_ids(std::vector<products> &ids) {
	this->product_id = ids;
}

void Order::set_all(const int id, std::vector<products> &product_id) {
	this->id = id;
	this->product_id = product_id;
}

void Order::add_container(Container &container) {
	this->best_containers_for_this_order.push_back(container);
}

void Order::set_cant_be_completed() {
	this->can_be_complete = false;
}

void Order::decrement_this_product(const int &i) {
	this->product_id.at(i).count--;
	if (!this->product_id.at(i).count)
		this->product_id.at(i).in_order = true;
}

int Order::get_id() {
	return this->id;
}

int Order::get_product_id(size_t i) {
	return this->product_id.at(i).id;
}

std::vector<products> Order::get_products() {
	return this->product_id;
}

Container Order::get_container(size_t i) {
	return this->best_containers_for_this_order.at(i);
}

bool Order::if_this_box_in_order(const int &id) {
	for (size_t i{ 0 }; i < this->product_id.size(); i++) {
		if (id == this->product_id.at(i).id && this->product_id.at(i).count != 0)
			return true;
	}
	return false;
}

bool Order::if_order_complete_by_used_boxes() {
	for (size_t i{ 0 }; i < this->product_id.size(); i++) {
		if (!this->product_id.at(i).in_order)
			return false;
	}
	return true;
}

bool Order::if_order_complete_by_boxes_in_containers() {
	for (size_t i{ 0 }; i < this->product_id.size(); i++) {
		int count{ 0 };
		for (size_t j{ 0 }; j < this->best_containers_for_this_order.size(); j++) {
			for (size_t k{ 0 }; k < (size_t)best_containers_for_this_order.at(j).get_count_of_boxes_inside(); k++) {
				if (this->best_containers_for_this_order.at(j).get_box(k).get_id() == this->product_id.at(i).id)
					count++;
			}
		}
		if (this->product_id.at(i).count != count)
			return false;
	}
	return true;
}

void Order::set_this_box_used(const int &id) {
	for (size_t i{ 0 }; i < this->product_id.size(); i++) {
		if (this->product_id.at(i).id == id) {
			this->product_id.at(i).count--;
			if (!this->product_id.at(i).count)
				this->product_id.at(i).in_order = true;
			break;
		}
	}
}

int Order::get_count_of_containers() {
	return (int)this->best_containers_for_this_order.size();
}

int Order::get_count_of_product(const int &i) {
	return this->product_id.at(i).count;
}

bool Order::if_can_be_complete() {
	return this->can_be_complete;
}

const bool operator== (Order &order_two, Order &order_one) {
	if (order_one.get_count_of_containers() == order_two.get_count_of_containers()) {
		for (int i{ 0 }; i < order_one.get_count_of_containers(); i++) {
			bool is_this_container_there{ false };
			for (int j{ 0 }; j < order_two.get_count_of_containers(); j++) {
				if (order_one.get_container(i) == order_two.get_container(j)) {
					is_this_container_there = true;
					break;
				}
			}
			if (!is_this_container_there)
				return false;
		}
	}
	return true;
}