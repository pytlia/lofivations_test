#include <fstream>
#include "Order.h"

void sort_containers_by_max_volume(std::vector<Container> &containers, int left, int right) {
	int i{ left }, j{ right }, pivot{ containers.at((left + right) / 2).get_container_volume() };
	Container temp;
	while (i <= j) {
		while (containers.at(i).get_container_volume() > pivot)
			i++;
		while (containers.at(j).get_container_volume() < pivot)
			j--;
		if (i <= j) {
			temp = containers.at(i);
			containers.at(i) = containers.at(j);
			containers.at(j) = temp;
			i++;
			j--;
		}
	};
	if (left < j)
		sort_containers_by_max_volume(containers, left, j);
	if (i < right)
		sort_containers_by_max_volume(containers, i, right);
}

void sort_boxes_by_min_surface_area(std::vector<Box> &boxes, int left, int right) {
	int i{ left }, j{ right }, pivot{ boxes.at((left + right) / 2).get_max_of_surface_area() };
	Box temp;
	while (i <= j) {
		while (boxes.at(i).get_max_of_surface_area() < pivot)
			i++;
		while (boxes.at(j).get_max_of_surface_area() > pivot)
			j--;
		if (i <= j) {
			temp = boxes.at(i);
			boxes.at(i) = boxes.at(j);
			boxes.at(j) = temp;
			i++;
			j--;
		}
	};
	if (left < j)
		sort_boxes_by_min_surface_area(boxes, left, j);
	if (i < right)
		sort_boxes_by_min_surface_area(boxes, i, right);
}

Container get_the_best_three_dimensions_bin_packing(Order &order, Container &our_container, std::vector<Box> &boxes, Container &best, double &target_function) {
	Container temp(our_container), container_for_save = our_container;
	Order order_for_save = order;
	bool if_container_full{ true };
	if (!order.if_order_complete_by_used_boxes()) {
		for (size_t j{ 0 }; j < boxes.size(); j++) {
			if (order.if_this_box_in_order(boxes.at(j).get_id())) {
				for (size_t k{ 0 }; k < temp.how_much_dots(); k++) {
					for (int l{ 0 }; l < boxes.at(j).get_number_of_orientations(); l++) {
						Box __temp__(boxes.at(j));
						__temp__.change_orientation(l);
						coord coord_temp = temp.get_possible_dot_to_put(k);
						double this_fulling_space;
						__temp__.add_coordinates(coord_temp);
						coord_temp.coord_x += __temp__.get_x();
						coord_temp.coord_y += __temp__.get_y();
						coord_temp.coord_z += __temp__.get_z();
						__temp__.add_coordinates(coord_temp);
						if (temp.if_this_box_can_be_in_this_container(__temp__)) {
							if_container_full = false;
							temp.add_boxes(__temp__);
							temp.set_all_dots_from_this_box(k, __temp__);
							order.set_this_box_used(__temp__.get_id());
							our_container = temp;
							temp = get_the_best_three_dimensions_bin_packing(order, our_container, boxes, best, target_function);
							this_fulling_space = (double)temp.volume_all_boxes() / (double)temp.get_container_volume();
							if (this_fulling_space > target_function) {
								target_function = this_fulling_space;
								best = temp;
							}
							order = order_for_save;
							our_container = container_for_save;
							temp = container_for_save;
						}
					}
				}
			}
		}
	}
	else {
		double this_fulling_space = (double)our_container.volume_all_boxes() / (double)our_container.get_container_volume();
		if (this_fulling_space > target_function) {
			target_function = this_fulling_space;
			best = our_container;
		}
	}
	if (if_container_full) {
		double this_fulling_space = (double)our_container.volume_all_boxes() / (double)our_container.get_container_volume();
		if (this_fulling_space > target_function) {
			target_function = this_fulling_space;
			best = our_container;
		}
	}
	return best;
}

void create_all_orders(std::vector<Order> &orders, std::vector<Container> &containers, std::vector<Box> &boxes) {
	std::vector<Order> best_orders;
	for (size_t i{ 0 }; i < orders.size(); i++) {
		Container best_container;
		Order best_order;
		std::vector<Container> to_save_containers = containers;
		std::vector<Box> to_save_boxes = boxes;
		std::vector<bool> containers_used(to_save_containers.size(), false);
		bool need_to_change_container{ false };
		int best_count_of_containers{ INT_MAX };
		double best_target{ 0.0 };
		for (size_t j{ 0 }; j < to_save_containers.size(); j++) {
			Order order_temp = orders.at(i);
			do {
				double target_function{ 0.0 };
				best_container = get_the_best_three_dimensions_bin_packing(order_temp, to_save_containers.at(j), to_save_boxes, best_container, target_function);
				if (best_container.get_count_of_boxes_inside()) {
					order_temp.add_container(best_container);
					for (size_t k{ 0 }; k < order_temp.get_products().size(); k++) {
						for (size_t l{ 0 }; l < (size_t)order_temp.get_count_of_containers(); l++) {
							for (size_t p{ 0 }; p < (size_t)order_temp.get_container(l).get_count_of_boxes_inside(); p++) {
								if (order_temp.get_product_id(k) == order_temp.get_container(l).get_box(p).get_id())
									order_temp.decrement_this_product(k);
							}
						}
					}
				}
				else {
					need_to_change_container = true;
					break;
				}
			} while (!order_temp.if_order_complete_by_used_boxes());
			if (need_to_change_container)
				continue;
			else {
				if (order_temp.get_count_of_containers() <= best_count_of_containers) {
					double temp_target{ 0.0 };
					for (int k{ 0 }; k < order_temp.get_count_of_containers(); k++)
						temp_target += (double)order_temp.get_container(k).volume_all_boxes() / (double)order_temp.get_container(k).get_container_volume();
					if (temp_target > best_target) {
						best_order = order_temp;
						best_target = temp_target;
						best_count_of_containers = order_temp.get_count_of_containers();
					}
				}
			}
		}
		if (best_count_of_containers == INT_MAX)
			best_order.set_cant_be_completed();
		best_orders.push_back(best_order);
	}
	orders = best_orders;
}

void input(std::vector<Order> &orders, std::vector<Container> &containers, std::vector<Box> &boxes) {
	std::ifstream fin("input_orders.txt");
	Order order_temp;
	Container container_temp;
	Box box_temp;
	std::string names_of_columns;
	std::getline(fin, names_of_columns);
	while (!fin.eof()) {
		int _id;
		char cp;
		std::vector<products> _products_id;
		fin >> _id;
		do {
			products for_read;
			fin >> for_read.count >> for_read.id;
			_products_id.push_back(for_read);
			if (fin.eof())
				break;
			fin >> cp;
			fin.putback(cp);
			if (cp == '-')
				break;
		} while (true);
		order_temp.set_all(_id, _products_id);
		orders.push_back(order_temp);
	}
	fin.close();
	fin.clear();
	fin.open("input_containers.txt");
	std::getline(fin, names_of_columns);
	while (!fin.eof()) {
		int _id, _x, _y, _z;
		fin >> _id;
		fin >> _x >> _y >> _z;
		container_temp.set_start_parametrs(_id, _x, _y, _z);
		containers.push_back(container_temp);
	}
	fin.close();
	fin.clear();
	fin.open("input_boxes.txt");
	std::getline(fin, names_of_columns);
	while (!fin.eof()) {
		int _id, _x, _y, _z;
		fin >> _id;
		fin >> _x >> _y >> _z;
		box_temp.set_start_parametrs(_id, _x, _y, _z);
		boxes.push_back(box_temp);
	}
	sort_boxes_by_min_surface_area(boxes, 0, boxes.size() - 1);
}

void output(std::vector<Order> &orders) {
	std::ofstream fout("output.txt");
	for (size_t i{ 0 }; i < orders.size(); i++) {
		fout << "For order # " << orders.at(i).get_id() << " : \n" << std::endl;
		if ((!orders.at(i).if_order_complete_by_used_boxes() && orders.at(i).get_count_of_containers()) || orders.at(i).if_order_complete_by_used_boxes()) {
			if (!orders.at(i).if_order_complete_by_used_boxes()) {
				fout << "\tThis order couldn't be complete!!!" << std::endl;
				fout << "\tBut there are this maximum possible contain :\n" << std::endl;
			}
			for (size_t k{ 0 }; k < (size_t)orders.at(i).get_count_of_containers(); k++) {
				fout << "\t\tBest container # " << orders.at(i).get_container(k).get_id() << " :\n\t\tLength = " << orders.at(i).get_container(k).get_x() << "\n\t\tWidth = " << orders.at(i).get_container(k).get_y() << "\n\t\tHeight = " << orders.at(i).get_container(k).get_z() << std::endl;
				fout << "\n\t\tBoxes in container :\n";
				for (size_t j{ 0 }; j < (size_t)orders.at(i).get_container(k).get_count_of_boxes_inside(); j++) {
					fout << "\n\t\t\tBox # " << orders.at(i).get_container(k).get_box(j).get_id() << " :\n" << "\t\t\tLength = " << orders.at(i).get_container(k).get_box(j).get_x() << "\n\t\t\tWidth = " << orders.at(i).get_container(k).get_box(j).get_y() << "\n\t\t\tHeight = " << orders.at(i).get_container(k).get_box(j).get_z() << std::endl;
					fout << "\t\t\tCoordinate of left_down dot of box # " << orders.at(i).get_container(k).get_box(j).get_id() << " is : x = " << orders.at(i).get_container(k).get_box(j).get_coordinate(0).coord_x << ", y = " << orders.at(i).get_container(k).get_box(j).get_coordinate(0).coord_y << ", z = " << orders.at(i).get_container(k).get_box(j).get_coordinate(0).coord_z << std::endl;
					fout << "\t\t\tCoordinate of right_up dot of box # " << orders.at(i).get_container(k).get_box(j).get_id() << " is : x = " << orders.at(i).get_container(k).get_box(j).get_coordinate(1).coord_x << ", y = " << orders.at(i).get_container(k).get_box(j).get_coordinate(1).coord_y << ", z = " << orders.at(i).get_container(k).get_box(j).get_coordinate(1).coord_z << std::endl;
				}
				fout << "\n\t\tTarget function = " << ((double)orders.at(i).get_container(k).volume_all_boxes() / (double)orders.at(i).get_container(k).get_container_volume()) * 100 << "%\n\n\n" << std::endl;
			}
		}
		else {
			fout << "\tThis order couldn't be complete!!!\n\n\n" << std::endl;
		}
	}
}

int main() {
	std::vector<Order> orders;
	std::vector<Container> containers;
	std::vector<Box> boxes;
	input(orders, containers, boxes);
	create_all_orders(orders, containers, boxes);
	output(orders);
	return 0;
}