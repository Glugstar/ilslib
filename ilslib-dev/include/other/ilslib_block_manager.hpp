/*----------------------------------------------------------------------------------
								ilslib_block_manager.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_BLOCK_MANAGER_HPP
#define ILSLIB_BLOCK_MANAGER_HPP

#pragma once


#include "../blocks/ilslib_container.hpp"
#include "../components/ilslib_text_component.hpp"
#include "../components/ilslib_image_component.hpp"
#include "ilslib_event_queue.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	/*!---------------------------------------------------------------------------------
										BlockManager
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	class BlockManager
	{
	public:
		// constructors & destructor
		BlockManager();
		virtual ~BlockManager();
		
		
		// functions
		virtual void addContainerStyle(ContainerStyle* style);
		virtual const ContainerStyle* getContainerStyle(const std::string& id) const;
		virtual void setRoot(Container* newRoot);
		virtual void calculateDPInfo(DrawableMap* drawables, const int windowWidth, const int windowHeight);
		virtual void transitionToAlternative(const std::string& path);
			// events
		virtual void parseMouseEvent(const MouseEvent& event, EventQueue& queue);
		virtual void parseKeyboardEvent(const KeyboardEvent& event, EventQueue& queue);
		virtual void parseTimeEvent(const TimeEvent& event, EventQueue& queue);
		virtual void parseWindowEvent(const WindowEvent& event, EventQueue& eventQueue);
			// find elements
		virtual BasicBlock* findBasicBlock(const std::string& path);
		virtual Alternative* findAlternative(const std::string& path);
		virtual Layer* findLayer(const std::string& path);
			// add elements
		virtual void addBasicBlock(const std::string& path, BasicBlock* newBasicBlock);
		virtual void addAlternative(const std::string& path, Alternative* newAlternative);
		virtual void addLayer(const std::string& path, Layer* newLayer);
	protected:
		// structs
		struct PathInfo
		{
			PathInfo();
			
			std::string blockName;
			std::string alternativeName;
			std::string layerName;
			int layerNumber;
		};
		
		
		// functions
		static void pathParse(const std::string& path, std::list<PathInfo>& pathInfo);
		static BasicBlock* findBasicBlock(const std::list<PathInfo>& pathInfo, BasicBlock* root);
		static BasicBlock* findBasicBlockBFS(std::list<BasicBlock*> blocksList, const std::string& blockID);
		
		static Alternative* getAlternative(Container* container, const PathInfo& pathInfo);
		static Layer* getLayer(Container* container, const PathInfo& pathInfo);
		static BasicBlock* getBasicBlock(Container* container, const PathInfo& pathInfo);
		
		
		// variables
		Container* root;
		EventQueue queue;
		std::vector<ContainerStyle*> containerStyles;
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_BLOCK_MANAGER_HPP





