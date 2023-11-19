#pragma once
#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <string>
#include <iostream>
namespace sdds
{
	class Station
	{
		int m_id{};
		std::string m_name;
		std::string m_desc;
		size_t m_serial{};
		size_t m_stock{};
		static size_t m_widthField;
		static int m_id_generator;
	public:
		Station() = default;
		Station(const std::string& record);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};
	
}
#endif // !SDDS_STATION_H


