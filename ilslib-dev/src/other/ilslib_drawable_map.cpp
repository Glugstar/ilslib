#include "../../include/other/ilslib_drawable_map.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	DrawableMap::DrawableMap():
		drawables()
	{
	}
	
	
	DrawableMap::~DrawableMap()
	{
		clear();
	}
	
	
	void DrawableMap::clear()
	{
		std::list<Drawable*>::iterator i;
		for(i=drawables.begin(); i!=drawables.end(); ++i)
			delete *i;
		
		drawables.clear();
	}
	
	
	void DrawableMap::addDrawable(Drawable* nextDrawable)
	{
		if(nextDrawable == nullptr)
			throw std::exception();
		drawables.push_back(nextDrawable);
	}
	
	
	void DrawableMap::drawAll(DrawWizard* wizard, ResourceManager* resourceManager, void* renderSurface)
	{
		std::list<Drawable*>::iterator i;
		for(i=drawables.begin(); i!=drawables.end(); ++i)
			wizard->draw(*i, resourceManager, renderSurface);
	}
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------





