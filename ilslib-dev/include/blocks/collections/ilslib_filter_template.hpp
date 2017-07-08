/*----------------------------------------------------------------------------------
							ilslib_filter_template.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.

DO NOT INCLUDE THIS FILE DIRECTLY
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_FILTER_TEMPLATE_HPP
#define ILSLIB_FILTER_TEMPLATE_HPP



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	template<class T>
	BlockCollection<T>::Filter::Filter():
		filterFunctions()
	{
	}
	
	
	template<class T>
	BlockCollection<T>::Filter::~Filter()
	{
	}
	
	
	template<class T>
	void BlockCollection<T>::Filter::clearFilterFuntions()
	{
		filterFunctions.clear();
	}
	
	
	template<class T>
	void BlockCollection<T>::Filter::addFilterFuntion(filterFunction filterFunc)
	{
		if(filterFunc != nullptr)
			filterFunctions.push_back(filterFunc);
	}
	
	
	template<class T>
	bool BlockCollection<T>::Filter::filterElement(const T* element) const
	{
		if(element == nullptr)
			return false;
		if(filterFunctions.size() == 0)
			return true;
		
		typename std::list<filterFunction>::const_iterator i;
		for(i=filterFunctions.begin(); i!=filterFunctions.end(); ++i)
			if((*i)(element) == false)
				return false;
		
		return true;
	}
	
	
	template<class T>
	typename BlockCollection<T>::Filter& BlockCollection<T>::Filter::operator=(const Filter& filter)
	{
		filterFunctions = filter.filterFunctions;
		
		return *this;
	}
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_FILTER_TEMPLATE_HPP






