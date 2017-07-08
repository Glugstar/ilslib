#include "../../../include/blocks/settings/ilslib_flow_container_settings.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	FlowContainerSettings::FlowContainerSettings():
		ContainerSettings(),
		cellSpacingHeight(0),
		axisPriority(HorizontalFirst),
		horizontalFlow(RightOrLowerFlow),
		verticalFlow(RightOrLowerFlow),
		autoLineWrap(false),
		tableNumberOfCells(0)
	{
	}
	
	
	FlowContainerSettings::~FlowContainerSettings()
	{
	}
	
	
	bool FlowContainerSettings::tableMode() const
	{
		return autoLineWrap == true && tableNumberOfCells > 0;
	}
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------




