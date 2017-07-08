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


#include "../blocks/ilslib_flow_container.hpp"
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
			// general operations
		virtual void clear();
		virtual void calculateDPInfo(const std::string& root, DrawableMap* drawables, const Vector& windowSize);
			// style operations
		virtual const ContainerStyle* getContainerStyle(const std::string& id) const;
		virtual bool addContainerStyle(ContainerStyle* style);
			// events functions
		virtual void parseEvent(const std::string& root, const MouseEvent& event, EventQueue& queue);
		virtual void parseEvent(const std::string& root, const KeyboardEvent& event, EventQueue& queue);
		virtual void parseEvent(const std::string& root, const TimeEvent& event, EventQueue& queue);
		virtual void parseEvent(const std::string& root, const WindowEvent& event, EventQueue& eventQueue);
			// elements functions
		virtual const BasicBlock* operator[](const std::string& path) const;
		virtual BasicBlock* operator[](const std::string& path);
		virtual bool addBasicBlock(const std::string& path, BasicBlock* newBasicBlock);
		virtual bool addRoot(BasicBlock* newBasicBlock);
	protected:
		// typedefs
		typedef std::list<std::string> PathInfo;
		
		
		// functions
		static void pathParse(const std::string& path, PathInfo& pathInfo);
		static void expandOneLevel(std::list<const BasicBlock*>& blocksList);
		static void expandBFS(std::list<const BasicBlock*>& blocksList, const std::string& blockID);
		const Container* getRoot(const std::string& path) const;
		Container* getRoot(const std::string& path);
		const BasicBlock* findBasicBlock(const PathInfo& pathInfo) const;
		
		
		// variables
		std::vector<ContainerStyle*> containerStyles;
		std::vector<Container*> roots;
		EventQueue eventQueue;
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_BLOCK_MANAGER_HPP





