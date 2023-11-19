#pragma once
#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H
#include <string>
namespace sdds
{
	void reduce(std::string& str, const std::string& whitespace = " \t\n\v");
	void reduce(std::string& str, const size_t& begin, const size_t end);
	class Utilities
	{
		size_t m_widthField{ 1 };
		static char m_delimiter;
	public:
		void setFieldWidth(size_t newWidth);
		size_t getFieldWidth() const;
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
		static void setDelimiter(char newDelimiter);
		static char getDelimiter();
	};
	
}
#endif // !SDDS_UTILITIES_H


