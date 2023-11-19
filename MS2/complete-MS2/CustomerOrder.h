#pragma once
#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H
#include <string>
namespace sdds
{
	
	class Station;
	class Utilities;
	struct Item
	{
		std::string m_itemName;
		size_t m_serialNumber{ 0 };
		bool m_isFilled{ false };

		Item(const std::string& src) : m_itemName(src) {};
	};
	class CustomerOrder
	{
		std::string m_name;
		std::string m_product;
		size_t m_cntItem{};
		Item** m_lstItem{};
		static size_t m_widthField;
	public:
		CustomerOrder() = default;
		CustomerOrder(const std::string& str);
		CustomerOrder(const CustomerOrder&) { throw "Copy construction not allowed"; }
		CustomerOrder& operator=(const CustomerOrder&) = delete;
		CustomerOrder(CustomerOrder&&) noexcept;
		CustomerOrder& operator=(CustomerOrder&&) noexcept;
		~CustomerOrder();
		bool isOrderFilled() const;
		bool isItemFilled(const std::string& itemName) const;
		void fillItem(Station& station, std::ostream& out);
		void display(std::ostream& out);
	};
	
}
#endif // !SDDS_CUSTOMERORDER_H


