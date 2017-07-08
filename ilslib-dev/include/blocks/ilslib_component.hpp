/*----------------------------------------------------------------------------------
								ilslib_component.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_COMPONENT_HPP
#define ILSLIB_COMPONENT_HPP

#pragma once

#include "ilslib_basic_block.hpp"
#include "settings/ilslib_component_settings.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	/*!---------------------------------------------------------------------------------
										Component
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	class Component : public BasicBlock
	{
	public:
		// constructors & destructor
		Component(const std::string& uniqueID);
		virtual ~Component();
		
		
		// functions
			// step 1: dimensions and position computations (strict order)
		virtual void step1A_minimize();
		virtual void step1B_adjust();
		virtual void step1C_maximize(const Vector& availableSize);
		virtual void step1D_reAdjust();
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_COMPONENT_HPP




