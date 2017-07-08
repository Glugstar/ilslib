/*----------------------------------------------------------------------------------
						ilslib_flow_container_settings.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_FLOW_CONTAINER_SETTINGS_HPP
#define ILSLIB_FLOW_CONTAINER_SETTINGS_HPP

#pragma once

#include "ilslib_container_settings.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	/*!---------------------------------------------------------------------------------
									FlowContainerSettings
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	class FlowContainerSettings : public ContainerSettings
	{
	public:
		// constructors & destructor
		FlowContainerSettings();
		virtual ~FlowContainerSettings();
		
		
		// functions
		virtual bool tableMode() const;
		
		
		// variables
			// minimum empty space between elements
		unsigned int cellSpacingWidth;
		unsigned int cellSpacingHeight;
			// axis priority and flow
		AxisPriority axisPriority;
		Flow horizontalFlow;
		Flow verticalFlow;
			// other stuff
		bool autoLineWrap; // allow sub-component newline if they don't fit the container
		int tableNumberOfCells; // enabled only with autoLineWrap == true
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_FLOW_CONTAINER_SETTINGS_HPP




