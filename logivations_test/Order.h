#pragma once
#include "Container.h"

class Order {
private:
	int id;

	std::vector<products> product_id;

	std::vector<Container> best_containers_for_this_order;

	bool can_be_complete{ true };

public:

	Order();

	Order(const int id, std::vector<products> &product_id);

	void set_id(const int &id);

	void add_product_id(const int &id);

	void set_product_ids(std::vector<products> &ids);

	void set_all(const int id, std::vector<products> &product_id);

	void add_container(Container &container);

	void set_cant_be_completed();

	void decrement_this_product(const int &i);

	int get_id();

	int get_product_id(size_t i);

	std::vector<products> get_products();

	Container get_container(size_t i);

	bool if_this_box_in_order(const int &id);

	bool if_order_complete_by_used_boxes();

	bool if_order_complete_by_boxes_in_containers();

	void set_this_box_used(const int &id);

	int get_count_of_containers();

	int get_count_of_product(const int &i);

	bool if_can_be_complete();
};

const bool operator== (Order &order_two, Order &order_one);

void create_all_orders(std::vector<Order> &orders, std::vector<Container> &containers, std::vector<Box> &boxes);