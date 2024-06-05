

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "Utilities.h"
namespace seneca
{
	char Utilities::m_delimiter;
	std::string trim(std::string& src) {
		bool valid = false;
		while (!valid)
		{
			if (src[0] == ' ')
			{
				src.erase(0, src.find_first_not_of(' '));
			}
			else if (src[src.length() - 1] == ' ')
			{
				src.erase(src.find_last_not_of(' ') + 1);
			}
			else
			{
				valid = true;
			}
		}
		return src;
	}
	void Utilities::setFieldWidth(size_t newWidth)
	{

		m_widthField = newWidth;
	
	}
	size_t Utilities::getFieldWidth() const
	{
		
		return m_widthField;
	
	}
	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) 
	{

		std::string string = "";
		static size_t nWidth = 0; 
		size_t index = 0;
		more = false;

		if (str.find(m_delimiter, next_pos) == next_pos)
		{
			more = false;
			nWidth = 0;
			throw "   ERROR: No token.";
		}
		else
		{
			if (str.find(m_delimiter, next_pos) >= str.length())
			{

				index = str.length();
			
			}
			else
			{

				index = str.find(m_delimiter, next_pos);
			
			}
			string = str.substr(next_pos, index - next_pos + 1);
			next_pos += string.length();
			if (next_pos >= str.length())
			{

				more = false;
			
			}
			else
			{

				string.erase(string.find(m_delimiter));
				more = true;
		
			}
		
			string = trim(string);
			if (nWidth < string.size())
			{

				nWidth = string.size();
				m_widthField = nWidth;
			
			}
			//sets newWidth back to zero once all values are read.
			if (more == false)
			{

				nWidth = 0;
			
			}
		
		
		}

		return string;


	}
	void Utilities::setDelimiter(char newDelimiter)
	{



		m_delimiter = newDelimiter;
	
	
	}
	char Utilities::getDelimiter() 
	{


		return m_delimiter;
	
	
	}
}
