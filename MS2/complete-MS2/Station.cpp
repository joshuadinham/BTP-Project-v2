#include "Station.h"
#include "Utilities.h"
#include <sstream>
#include <iomanip>

size_t sdds::Station::m_widthField = 0;
int sdds::Station::m_id_generator = 1;
sdds::Station::Station(const std::string& record)
{
	Utilities util;
	std::string name{};
	std::string serial{};
	std::string qty{};
	std::string desc{};
	size_t pos{};
	bool more = true;
	

		try
		{
			name = util.extractToken(record, pos, more);
			serial = util.extractToken(record, pos, more);
			qty = util.extractToken(record, pos, more);
			if (Station::m_widthField < util.getFieldWidth())
				Station::m_widthField = util.getFieldWidth();
			desc = util.extractToken(record, pos, more);
		}
		catch (...)
		{
			std::string err;
			err = "No good\n";
			std::cerr << err;
		}
		m_name = name;
		m_serial = std::stoi(serial);
		m_stock = std::stoi(qty);
		m_desc = desc;
		m_id = m_id_generator;
		m_id_generator++;
}

const std::string& sdds::Station::getItemName() const
{
	return m_name;
}

size_t sdds::Station::getNextSerialNumber()
{
	return m_serial++;
}

size_t sdds::Station::getQuantity() const
{
	return m_stock;
}

void sdds::Station::updateQuantity()
{
	if (m_stock > 0)
	{
		m_stock--;
	}
}

void sdds::Station::display(std::ostream& os, bool full) const
{
	os << std::right << std::setfill('0') << std::setw(3) << m_id << " | "
		<< std::left << std::setfill(' ') << std::setw(m_widthField) << m_name << " | "
		<< std::setw(6) << std::setfill('0') <<std::right << m_serial << " | ";

	if (full)
	{
		os << std::setfill(' ') << std::setw(4) << m_stock << " | "
			<< std::left<< m_desc;
	}
	os << std::endl;
}
