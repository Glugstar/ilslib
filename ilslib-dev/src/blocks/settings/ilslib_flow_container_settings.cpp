#include "../../../include/blocks/settings/ilslib_flow_container_settings.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{



	FlowContainerSettings::FlowContainerSettings():
		ContainerSettings(),
		cellSpacingWidth(0),
		cellSpacingHeight(0),
		axisPriority(HorizontalFirst),
		horizontalFlow(LeftToRightFlow),
		verticalFlow(TopToBottomFlow),
		autoLineWrap(false)
	{
	}


	FlowContainerSettings::~FlowContainerSettings()
	{
	}



} // end namespace ILSLib
//----------------------------------------------------------------------------------




