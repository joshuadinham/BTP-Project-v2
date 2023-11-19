#include "CustomerOrder.h"
#include "Utilities.h"
#include "Station.h"
#include <iomanip>
#include <memory>
size_t sdds::CustomerOrder::m_widthField{};

sdds::CustomerOrder& sdds::CustomerOrder::operator=(CustomerOrder&& order) noexcept
{
	if (this != &order) {
		m_name = order.m_name;
		order.m_name = "";
		m_product = order.m_product;
		order.m_product = "";
		
		for (size_t i = 0; i < m_cntItem; i++)
		{
			delete m_lstItem[i];
		}
		delete[] m_lstItem;

		m_lstItem = new Item * [order.m_cntItem];
		for (size_t i = 0; i < order.m_cntItem; i++)
		{

			if (order.m_lstItem[i])
			{
				m_lstItem[i] = new Item(*order.m_lstItem[i]);
				delete order.m_lstItem[i];
				order.m_lstItem[i] = nullptr;
			}

		}
		delete[] order.m_lstItem;
		order.m_lstItem = nullptr;
		m_cntItem = order.m_cntItem;
		order.m_cntItem = 0;
	}
	return *this;
}

sdds::CustomerOrder::CustomerOrder(const std::string& str)
{
	Utilities util;
	std::string name;
	std::string product;
	Item** item{};
	Item** temp{};
	bool more = true;
	size_t next_pos = 0;
	name = util.extractToken(str, next_pos, more);
	product = util.extractToken(str, next_pos, more);
	size_t num = 0;
	item = new Item * [num + 1];
	item[num] = new Item(util.extractToken(str, next_pos, more));
	num++;
	do
	{
		temp = new Item * [num + 1];
		for (size_t i = 0; i < num; i++)
		{
			if (item[i])
			{
				temp[i] = item[i];
			}
		}
		temp[num] = new Item(util.extractToken(str, next_pos, more));
		if (item)
		{
			delete[] item;
		}
		item = temp;
		num++;
	} while (more);

	m_name = name;
	m_product = product;
	m_lstItem = new Item * [num];
	for (size_t i = 0; i < num; i++)
	{
		m_lstItem[i] = new Item(*item[i]);
		delete item[i];
	}
	delete[] item;
	m_cntItem = num;
	if (CustomerOrder::m_widthField < util.getFieldWidth())
	{
		CustomerOrder::m_widthField = util.getFieldWidth();
	}

}

sdds::CustomerOrder::CustomerOrder(CustomerOrder&& order) noexcept
{
	if (this != &order)
	{
		*this = std::move(order);
	}
}

sdds::CustomerOrder::~CustomerOrder()
{
	for (size_t i = 0; i < m_cntItem; i++)
	{
		if (m_lstItem[i])
		{
			delete m_lstItem[i];
			m_lstItem[i] = nullptr;
		}
	}
	if (m_lstItem)
	{
		delete[] m_lstItem;
		m_lstItem = nullptr;
	}
}

bool sdds::CustomerOrder::isOrderFilled() const
{
	bool filled = true;
	for (size_t i = 0; i < m_cntItem && filled; i++)
	{
		filled = m_lstItem[i]->m_isFilled == true;
	}
	return filled;
}

bool sdds::CustomerOrder::isItemFilled(const std::string& itemName) const
{
	bool filled = true;
	for (size_t i = 0; i < m_cntItem && filled; i++)
	{
		if (m_lstItem[i]->m_itemName == itemName)
		{
			filled = m_lstItem[i]->m_isFilled;
		}
	}
	return filled;
}

void sdds::CustomerOrder::fillItem(Station& station, std::ostream& out)
{
	std::string itemName = station.getItemName();
	bool found = false;
	bool exists = false;
	bool inventory = false;
	bool notFilled = false;
	size_t num = 0;

	for (size_t i = 0; i < m_cntItem; i++)
	{
		found = m_lstItem[i]->m_itemName == itemName;
		if (found)
		{
			exists = true;
			notFilled = m_lstItem[i]->m_isFilled == false;
			if (notFilled)
			{
				num = i;
			}

				
		}
	}
	inventory = station.getQuantity() > 0;
	if (exists)
	{
		
			if (inventory && notFilled)
			{
				
				m_lstItem[num]->m_serialNumber = station.getNextSerialNumber();
				station.updateQuantity();
				m_lstItem[num]->m_isFilled = true;

			
			}
		
		if (inventory)
		{
			out << "    Filled " << m_name << ", " << m_product << " [" << itemName << "]";
		}
		else
		{
			out << "    Unable to fill " << m_name << ", " << m_product << " [" << itemName << "]";
		}
		out << std::endl;
	}

	
}

void sdds::CustomerOrder::display(std::ostream& out)
{
	out << std::left<< m_name << " - " << m_product << "\n";
	for (size_t i = 0; i < m_cntItem; i++)
	{
		out << "[" <<std::right<< std::setfill('0') << std::setw(6) << m_lstItem[i]->m_serialNumber << "] " <<
			std::setfill(' ') << std::left << std::setw(CustomerOrder::m_widthField) << m_lstItem[i]->m_itemName << " - ";
		if (m_lstItem[i]->m_isFilled)
		{
			out << "FIlLED";
		}
		else
		{
			out << "TO BE FILLED";
		}
		out << std::endl;
	}

}
