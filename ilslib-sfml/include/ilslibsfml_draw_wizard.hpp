/*----------------------------------------------------------------------------------
							ilslibsfml_draw_wizard.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library - SFML Adapter.
----------------------------------------------------------------------------------*/
#ifndef ILSLIBSFML_DRAW_WIZARD_HPP
#define ILSLIBSFML_DRAW_WIZARD_HPP

#pragma once

#include <SFML/Graphics.hpp>
#include "../../ilslib-dev/include/other/ilslib_draw_wizard.hpp"



/*----------------------------------------------------------------------------------
									ILSLibSFML
----------------------------------------------------------------------------------*/
namespace ILSLibSFML
{



	/*!---------------------------------------------------------------------------------
										DrawWizard
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	class DrawWizard : public ILSLib::DrawWizard
	{
	public:
		// constructors & destructor
		DrawWizard();
		virtual ~DrawWizard();


		// functions
		void draw(ILSLib::Drawable* nextDrawable, ILSLib::ResourceManager* resourceManager, void* renderSurface);
	protected:
		// functions
		virtual void drawGradient(ILSLib::Gradient* gradient,
								ILSLib::ResourceManager* resourceManager, void* renderSurface);
		virtual void drawImage(ILSLib::Image* image,
								ILSLib::ResourceManager* resourceManager, void* renderSurface);
		virtual void drawRectangleColor(ILSLib::RectangleColor* rectangleColor,
								ILSLib::ResourceManager* resourceManager, void* renderSurface);
		virtual void drawText(ILSLib::Text* text,
								ILSLib::ResourceManager* resourceManager, void* renderSurface);
		virtual sf::View limitView(sf::RenderWindow* renderWindow,
									const ILSLib::Rectangle& cutRectangle);
		virtual void restoreView(sf::RenderWindow* renderWindow,
								 const sf::View& oldView);
	};



} // end namespace ILSLibSFML
//----------------------------------------------------------------------------------



#endif // ILSLIBSFML_DRAW_WIZARD_HPP




