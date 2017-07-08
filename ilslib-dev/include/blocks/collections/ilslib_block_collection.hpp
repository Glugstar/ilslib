/*----------------------------------------------------------------------------------
								ilslib_block_collection.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_BLOCK_COLLECTION_HPP
#define ILSLIB_BLOCK_COLLECTION_HPP

#pragma once


#include "../../other/ilslib_drawable_map.hpp"
#include "../settings/ilslib_settings.hpp"
#include "../dpinfo/ilslib_dimensions_mapper.hpp"
#include "../dpinfo/ilslib_position_mapper.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	/*!---------------------------------------------------------------------------------
										BlockCollection
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	template<class T>
	class BlockCollection
	{
	public:
		// typedefs
		typedef std::list<T*> Type;
		
		
		// classes
		class const_iterator;
		class iterator;
		
		
		// constructors & destructor
		explicit BlockCollection();
		virtual ~BlockCollection();
		
		
		// functions
			// basic element functions
		virtual const T* operator[](const std::string& id) const;
		virtual T* operator[](const std::string& id);
		
		virtual void push_back(T* element);
		virtual void push_front(T* element);
		
		virtual void move_one_back(const std::string& id);
		virtual void move_one_back(iterator& element);
		virtual void move_one_front(const std::string& id);
		virtual void move_one_front(iterator& element);
		
		virtual T* detatch(const std::string& id);
		virtual T* detatch(iterator& element);
		virtual void detatchAll();
		
		virtual void erase(const std::string& id);
		virtual void erase(iterator& element);
		virtual void clear();
		
			// iterator functions
		virtual const_iterator begin(Settings::IterationMode itMode = Settings::IterationMode::All,
									bool tMode = false) const;
		virtual iterator begin(Settings::IterationMode itMode = Settings::IterationMode::All,
									bool tMode = false);
		
		virtual const_iterator end(Settings::IterationMode itMode = Settings::IterationMode::All,
									bool tMode = false) const;
		virtual iterator end(Settings::IterationMode itMode = Settings::IterationMode::All,
									bool tMode = false);
	protected:
		// variables
		Type elements;
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



// template implementations
#include "ilslib_block_collection_template.hpp"



#endif // ILSLIB_BLOCK_COLLECTION_HPP





