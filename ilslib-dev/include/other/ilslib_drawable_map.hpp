/*----------------------------------------------------------------------------------
								ilslib_drawable_map.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_DRAWABLE_MAP_HPP
#define ILSLIB_DRAWABLE_MAP_HPP

#pragma once

#include "ilslib_draw_wizard.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	/*!---------------------------------------------------------------------------------
										DrawableMap
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	class DrawableMap
	{
	public:
		// constructors & destructor
		DrawableMap();
		virtual ~DrawableMap();
		
		
		// functions
		virtual void clear();
		virtual void addDrawable(Drawable* nextDrawable);
		virtual void drawAll(DrawWizard* wizard, ResourceManager* resourceManager, void* renderSurface);
	protected:
		// variables
		std::list<Drawable*> drawables;
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_DRAWABLE_MAP_HPP






