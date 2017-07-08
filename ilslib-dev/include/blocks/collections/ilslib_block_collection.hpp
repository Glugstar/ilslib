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


#include "../../base/ilslib_support.hpp"



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
		class Filter;
		class const_iterator;
		class iterator;
		
		
		// constructors & destructor
		explicit BlockCollection();
		virtual ~BlockCollection();
		
		
		// functions
			// basic element functions
		virtual const T* operator[](const std::string& id) const;
		virtual T* operator[](const std::string& id);
		
		virtual bool push_back(T* element);
		virtual bool push_front(T* element);
		
		virtual void move_one_back(const std::string& id);
		virtual void move_one_back(iterator& element);
		virtual void move_one_front(const std::string& id);
		virtual void move_one_front(iterator& element);
		
		virtual T* detatch(const std::string& id);
		virtual T* detatch(iterator& element);
		virtual void detatchAll();
		
		virtual bool erase(const std::string& id);
		virtual bool erase(iterator& element);
		virtual void clear();
		
			// iterator functions
		virtual const_iterator begin(const Filter* filter = nullptr) const;
		virtual iterator begin(const Filter* filter = nullptr);
		virtual const_iterator end(const Filter* filter = nullptr) const;
		virtual iterator end(const Filter* filter = nullptr);
	protected:
		// variables
		Type elements;
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



// template implementations
#include "ilslib_block_collection_template.hpp"



#endif // ILSLIB_BLOCK_COLLECTION_HPP





