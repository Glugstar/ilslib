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
			// basic element functions
		virtual const DimensionsInfo* getDimensionsInfo(const Settings::Step step) const;
		virtual const PositionInfo* getPositionInfo() const;
			// step 0: clear previous data (strict order)
		virtual void step0A_clear();
		virtual void step0B_applyTransformations();
			// step 1: dimensions and position computations (strict order)
		virtual void step1A_minimize();
		virtual void step1B_adjust();
		virtual void step1C_maximize(int availableWidth, int availableHeight);
		virtual void step1D_reAdjust();
			// step 2: drawable map generation
		virtual void step2A_determinePositions();
		virtual void step2C_addToDrawableMap(DrawableMap* drawables) = 0;
	protected:
		// functions
		virtual PositionInfo* getPositionInfo();
		
		
		// variables
		DimensionsInfo dInfoStep1A;
		DimensionsInfo dInfoStep1B;
		DimensionsInfo dInfoStep1C;
		DimensionsInfo dInfoStep1D;
		PositionInfo pInfo;
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_COMPONENT_HPP




