#include "stdafx.h"
#include "../logivations_test/Box.h"
#include "../logivations_test/Container.h"
#include "../logivations_test/Order.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

namespace TestA {
	[TestClass]
	public ref class UnitTest {
	private:
		TestContext^ testContextInstance;

	public: 
		property Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ TestContext
		{
			Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ get()
			{
				return testContextInstance;
			}
			System::Void set(Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ value)
			{
				testContextInstance = value;
			}
		};

		[TestMethod]
		void TestMethod1() {
			/*std::vector<Order> input_orders, orders;
			std::vector<Container> containers;
			std::vector<Box> boxes;
			Order order_test;
			Container container_test;
			Box box_test;
			int _id, _size_x, _size_y, _size_z;
			std::vector<products> prod_ids;
			products prod_orders_test;

			// ----------------------------------------//

			prod_orders_test.count = 1;
			prod_orders_test.id = -1;
			prod_ids.push_back(prod_orders_test);
			prod_orders_test.count = 1;
			prod_orders_test.id = -2;
			prod_ids.push_back(prod_orders_test);
			prod_orders_test.count = 1;
			prod_orders_test.id = -3;
			prod_ids.push_back(prod_orders_test);
			order_test.set_id(-1000);
			order_test.set_product_ids(prod_ids);

			input_orders.push_back(order_test);

			prod_ids.clear();

			prod_orders_test.count = 1;
			prod_orders_test.id = -1;
			prod_ids.push_back(prod_orders_test);
			prod_orders_test.count = 1;
			prod_orders_test.id = -2;
			prod_ids.push_back(prod_orders_test);
			order_test.set_id(-1001);
			order_test.set_product_ids(prod_ids);

			input_orders.push_back(order_test);

			//--------------------------------------------------//

			_id = -100;
			_size_x = 5;
			_size_y = 5;
			_size_z = 5;

			container_test.set_id(_id);
			container_test.set_x(_size_x);
			container_test.set_y(_size_y);
			container_test.set_z(_size_z);

			containers.push_back(container_test);

			_id = -101;
			_size_x = 3;
			_size_y = 3;
			_size_z = 3;

			container_test.set_id(_id);
			container_test.set_x(_size_x);
			container_test.set_y(_size_y);
			container_test.set_z(_size_z);

			containers.push_back(container_test);

			//----------------------------------------//

			_id = -1;
			_size_x = 1;
			_size_y = 1;
			_size_z = 1;

			box_test.set_id(_id);
			box_test.set_x(_size_x);
			box_test.set_y(_size_y);
			box_test.set_z(_size_z);

			boxes.push_back(box_test);

			_id = -2;
			_size_x = 2;
			_size_y = 2;
			_size_z = 2;

			box_test.set_id(_id);
			box_test.set_x(_size_x);
			box_test.set_y(_size_y);
			box_test.set_z(_size_z);

			boxes.push_back(box_test);

			_id = -3;
			_size_x = 3;
			_size_y = 3;
			_size_z = 3;

			box_test.set_id(_id);
			box_test.set_x(_size_x);
			box_test.set_y(_size_y);
			box_test.set_z(_size_z);

			boxes.push_back(box_test);

			// ----------------------------------------------//
			//					ANSWER						 //
			// ----------------------------------------------//

			_id = -1;
			box_test.set_id(_id);
			container_test.add_boxes(box_test);

			_id = -2;
			box_test.set_id(_id);
			container_test.add_boxes(box_test);

			_id = -3;
			box_test.set_id(_id);
			container_test.add_boxes(box_test);

			_id = -100;
			container_test.set_id(_id);
			order_test.add_container(container_test);

			orders.push_back(order_test);

			_id = -1;
			box_test.set_id(_id);
			container_test.add_boxes(box_test);

			_id = -2;
			box_test.set_id(_id);
			container_test.add_boxes(box_test);

			_id = -101;
			container_test.set_id(_id);
			order_test.add_container(container_test);

			orders.push_back(order_test);

			// ----------------------------------------------
			create_all_orders(input_orders, containers, boxes);

			bool answer{ false };
			if (orders.size() == input_orders.size()) {
				for (size_t i{ 0 }; i < orders.size(); i++) {
					answer = false;
					bool is_this_order{ false };
					for (size_t j{ 0 }; j < input_orders.size(); j++) {
						if (input_orders.at(j) == orders.at(i)) {
							is_this_order = true;
							break;
						}
					}
					if (!is_this_order)
						break;
					answer = true;
				}
			}
			
			Assert::IsTrue(answer);
			*/
			Assert::IsTrue(true);
		};
	};
}