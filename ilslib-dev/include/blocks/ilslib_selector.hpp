/*----------------------------------------------------------------------------------
							ilslib_selector.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_SELECTOR_HPP
#define ILSLIB_SELECTOR_HPP

#pragma once

#include "ilslib_container_style.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	/*!---------------------------------------------------------------------------------
										Selector
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	class ContainerStyle::Selector
	{
	public:
		// constructors & destructor
		Selector();
		virtual ~Selector();
		
		
		// functions
		virtual unsigned int getModelBorderIndexFirst(unsigned int numberOfModels) const;
		virtual unsigned int getModelBorderIndexLast(unsigned int numberOfModels) const;
		virtual float getModelBorderRatio() const;
		virtual unsigned int getModelBGIndexFirst(unsigned int numberOfModels) const;
		virtual unsigned int getModelBGIndexLast(unsigned int numberOfModels) const;
		virtual float getModelBGRatio() const;
		
		
		// variables
		unsigned int modelBorderIndexFirst;
		unsigned int modelBorderIndexLast;
		float modelBorderIndexRatio;
		unsigned int modelBGIndexFirst;
		unsigned int modelBGIndexLast;
		float modelBGIndexRatio;
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_SELECTOR_HPP




