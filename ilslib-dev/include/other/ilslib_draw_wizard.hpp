/*----------------------------------------------------------------------------------
								ilslib_draw_wizard.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_DRAW_WIZARD_HPP
#define ILSLIB_DRAW_WIZARD_HPP

#pragma once

#include "ilslib_resource_manager.hpp"
#include "../drawables/ilslib_gradient.hpp"
#include "../drawables/ilslib_image.hpp"
#include "../drawables/ilslib_rectangle_color.hpp"
#include "../drawables/ilslib_text.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	/*!---------------------------------------------------------------------------------
										DrawWizard
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	class DrawWizard
	{
	public:
		// constructors & destructor
		DrawWizard();
		virtual ~DrawWizard();
		
		
		// functions
		virtual void draw(Drawable* nextDrawable, ResourceManager* resourceManager, void* renderSurface) = 0;
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_DRAW_WIZARD_HPP






