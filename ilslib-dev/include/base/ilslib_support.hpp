/*----------------------------------------------------------------------------------
								ilslib_support.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_SUPPORT_HPP
#define ILSLIB_SUPPORT_HPP

#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <vector>
#include <tuple>
#include <set>
#include <unordered_set>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

#include "ilslib_color.hpp"
#include "ilslib_rectangle.hpp"
#include "ilslib_vector.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	/*----------------------------------------------------------------------------------
											Support
	----------------------------------------------------------------------------------*/
	namespace Support
	{
		
		
		
		template<class ContainerT>
		void tokenize(const std::string& str, ContainerT& tokens,
							const std::string& delimiters = " ", bool trimEmpty = true);
		
		
		template<class T>
		std::string NumberToString(T Number);
		
		
		std::string& leftTrim(std::string& s);
		
		
		std::string& rightTrim(std::string& s);
		
		
		std::string& trim(std::string& s);
		
		
		
	} // end namespace Support
} // end namespace ILSLib
//----------------------------------------------------------------------------------



// template implementations
#include "ilslib_support_template.hpp"



#endif // ILSLIB_SUPPORT_HPP





