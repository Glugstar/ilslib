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
		static void tokenize(const std::string& str, ContainerT& tokens,
							const std::string& delimiters = " ", bool trimEmpty = true);
		
		template<class T>
		static std::string NumberToString(T Number);
		
		
		
	} // end namespace Support
} // end namespace ILSLib
//----------------------------------------------------------------------------------



// template implementations
#include "ilslib_support_template.hpp"



#endif // ILSLIB_SUPPORT_HPP





