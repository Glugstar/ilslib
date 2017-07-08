#include "../../include/blocks/ilslib_selector.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	ContainerStyle::Selector::Selector():
		modelBorderIndexFirst(0),
		modelBorderIndexLast(0),
		modelBorderIndexRatio(0.0f),
		modelBGIndexFirst(0),
		modelBGIndexLast(0),
		modelBGIndexRatio(0.0f)
	{
	}
	
	
	ContainerStyle::Selector::~Selector()
	{
	}
	
	
	unsigned int ContainerStyle::Selector::getModelBorderIndexFirst(unsigned int numberOfModels) const
	{
		if(numberOfModels == 0)
			return 0;
		return modelBorderIndexFirst % numberOfModels;
	}
	
	
	unsigned int ContainerStyle::Selector::getModelBorderIndexLast(unsigned int numberOfModels) const
	{
		if(numberOfModels == 0)
			return 0;
		return modelBorderIndexLast % numberOfModels;
	}
	
	
	float ContainerStyle::Selector::getModelBorderRatio() const
	{
		return modelBorderIndexRatio;
	}
	
	
	unsigned int ContainerStyle::Selector::getModelBGIndexFirst(unsigned int numberOfModels) const
	{
		if(numberOfModels == 0)
			return 0;
		return modelBGIndexFirst % numberOfModels;
	}
	
	
	unsigned int ContainerStyle::Selector::getModelBGIndexLast(unsigned int numberOfModels) const
	{
		if(numberOfModels == 0)
			return 0;
		return modelBGIndexLast % numberOfModels;
	}
	
	
	float ContainerStyle::Selector::getModelBGRatio() const
	{
		return modelBGIndexRatio;
	}
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------





