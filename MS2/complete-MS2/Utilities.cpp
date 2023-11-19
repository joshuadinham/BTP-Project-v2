#include "Utilities.h"
#include <sstream>

char sdds::Utilities::m_delimiter = ',';

void sdds::reduce(std::string& str, const std::string& whitespace)
{
	size_t begin = str.find_first_not_of(whitespace);
	size_t end = str.find_last_not_of(whitespace);
	str = str.substr(begin, (end - begin)+1);
}

void sdds::reduce(std::string& str, const size_t& begin, const size_t end)
{
	str = str.erase(begin, end);
	
}
//sets the field width of the current objec tto the value of parameter newWidth
void sdds::Utilities::setFieldWidth(size_t newWidth)
{
	m_widthField = newWidth;
}

//returns the field width of the current object
size_t sdds::Utilities::getFieldWidth() const
{
	return m_widthField;
}

//extracts a token from string str reffered to by the first parameter;
std::string sdds::Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
{
	std::string temp = str;
	size_t begin = 0u;
	reduce(temp, 0u, next_pos);
	if (temp[begin] == m_delimiter)
	{
		more = false;
		throw "ERROR: no token\n";
	}

	size_t end = temp.find_first_of(m_delimiter);
	bool found = false;
	found = end != std::string::npos;
	if (found == false)
	{
		end = temp.find_last_of(temp) +1;
	}

	//use delimiter to extract next token starting at position next_pos
	std::string token = temp.substr(begin, (end-begin));
		reduce(token);
		if (found == true)
		{
			next_pos += end + 1;
			more = true;
		}
		else
		{
			more = false;
		}
		
	

	if (m_widthField < token.length())
	{
		setFieldWidth(token.length());
	}

	return token;

	
			//if success
				//return copy of extracted token (no trailing, leading spaces
				//update next_pos and set more to true
			//else
				//more = false
	//reports an exception if delimiter is found at next_pos
	
	//updates the current object's m_widthField datamember if current value less than size of token extracted
	
}

void sdds::Utilities::setDelimiter(char newDelimiter)
{
	m_delimiter = newDelimiter;

}

char sdds::Utilities::getDelimiter()
{
	return m_delimiter;
}


