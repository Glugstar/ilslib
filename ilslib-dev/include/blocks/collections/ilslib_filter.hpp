/*----------------------------------------------------------------------------------
								ilslib_filter.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_FILTER_HPP
#define ILSLIB_FILTER_HPP

#pragma once


#include "ilslib_block_collection.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	/*!---------------------------------------------------------------------------------
											Filter
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	template<class T>
	class BlockCollection<T>::Filter
	{
	public:
		// typdefs
		typedef bool (*filterFunction) (const T* element);
		
		
		// constructors & destructor
		Filter();
		virtual ~Filter();
		
		
		// functions
			// filter functions
		virtual void clearFilterFuntions();
		virtual void addFilterFuntion(filterFunction filterFunc);
		virtual bool filterElement(const T* element) const;
			// assignment operators
		virtual Filter& operator=(const Filter& filter);
	protected:
		// variables
		std::list<filterFunction> filterFunctions;
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



// template implementations
#include "ilslib_filter_template.hpp"



#endif // ILSLIB_FILTER_HPP





