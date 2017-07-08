#include "../../include/drawables/ilslib_text.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	Text::Text(const std::string& newFontID, const std::string& newMessage):
		Drawable(),
		fontID(newFontID),
		message(newMessage)
	{
		adjustments = new TextAR();
	}
	
	
	Text::~Text()
	{
	}
	
	
	TextAR* Text::getTextAR()
	{
		return (TextAR*)adjustments;
	}
	
	
	const std::string& Text::getFontID() const
	{
		return fontID;
	}
	
	
	const std::string& Text::getMessage() const
	{
		return message;
	}
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------




