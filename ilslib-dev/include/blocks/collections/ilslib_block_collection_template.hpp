/*----------------------------------------------------------------------------------
							ilslib_block_collection_template.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.

DO NOT INCLUDE THIS FILE DIRECTLY
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_BLOCK_COLLECTION_TEMPLATE_HPP
#define ILSLIB_BLOCK_COLLECTION_TEMPLATE_HPP

#include "ilslib_const_iterator.hpp"
#include "ilslib_iterator.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	template<class T>
	BlockCollection<T>::BlockCollection():
		elements()
	{
	}
	
	
	template<class T>
	BlockCollection<T>::~BlockCollection()
	{
		clear();
	}
	
	
	template<class T>
	const T* BlockCollection<T>::operator[](const std::string& id) const
	{
		for(const_iterator i=begin(); !i.isEnd(); ++i)
			if((*i)->getID() == id)
				return *i;
		return nullptr;
	}
	
	
	template<class T>
	T* BlockCollection<T>::operator[](const std::string& id)
	{
		for(iterator i=begin(); i!=end(); ++i)
			if((*i)->getID() == id)
				return *i;
		return nullptr;
	}
	
	
	template<class T>
	bool BlockCollection<T>::push_back(T* element)
	{
		if(element == nullptr)
			return false;
		
		const BlockCollection<T>& ref = *this;
		const T* oldElement = ref[element->getID()];
		if(oldElement != nullptr)
			return false;
		
		elements.push_back(element);
		
		return true;
	}
	
	
	template<class T>
	bool BlockCollection<T>::push_front(T* element)
	{
		if(element == nullptr)
			return false;
		
		const BlockCollection<T>& ref = *this;
		const T* oldElement = ref[element->getID()];
		if(oldElement != nullptr)
			return false;
		
		elements.push_front(element);
		
		return true;
	}
	
	
	template<class T>
	void BlockCollection<T>::move_one_back(const std::string& id)
	{
		for(iterator i=begin(); i!=end(); ++i)
			if((*i)->getID() == id)
				move_one_back(i);
	}
	
	
	template<class T>
	void BlockCollection<T>::move_one_back(BlockCollection<T>::iterator& element)
	{
		if(element.isEnd() == true)
			return;
		if(element.isFirst() == true)
			return;
		
		iterator previous = element;
		--previous;
		
		T* elemValue = *previous;
		*previous = *element;
		**element = *elemValue;
		
		element = previous;
	}
	
	
	template<class T>
	void BlockCollection<T>::move_one_front(const std::string& id)
	{
		for(iterator i=begin(); i!=end(); ++i)
			if((*i)->getID() == id)
				move_one_front(i);
	}
	
	
	template<class T>
	void BlockCollection<T>::move_one_front(BlockCollection<T>::iterator& element)
	{
		if(element.isEnd() == true)
			return;
		if(element.isLast() == true)
			return;
		
		iterator next = element;
		++next;
		
		T* elemValue = *next;
		*next = *element;
		**element = *elemValue;
		
		element = next;
	}
	
	
	template<class T>
	T* BlockCollection<T>::detatch(const std::string& id)
	{
		for(iterator i=begin(); i!=end(); ++i)
			if((*i)->getID() == id)
				return detatch(i);
		return nullptr;
	}
	
	
	template<class T>
	T* BlockCollection<T>::detatch(BlockCollection<T>::iterator& element)
	{
		T* oldElement = *element;
		typename Type::iterator iterator = element.getInternalIterator();
		elements.erase(iterator);
		return oldElement;
	}
	
	
	template<class T>
	void BlockCollection<T>::detatchAll()
	{
		for(iterator i=begin(); i!=end(); ++i)
			*i = nullptr;
		elements.clear();
	}
	
	
	template<class T>
	bool BlockCollection<T>::erase(const std::string& id)
	{
		for(iterator i=begin(); i!=end(); ++i)
		{
			if((*i)->getID() == id)
			{
				erase(i);
				return true;
			}
		}
		
		return false;
	}
	
	
	template<class T>
	bool BlockCollection<T>::erase(BlockCollection<T>::iterator& element)
	{
		delete *element;
		typename Type::iterator iterator = element.getInternalIterator();
		elements.erase(iterator);
		++element;
		
		return true;
	}
	
	
	template<class T>
	void BlockCollection<T>::clear()
	{
		for(iterator i=begin(); i!=end(); ++i)
			if(*i != nullptr)
				delete *i;
		elements.clear();
	}
	
	
	template<class T>
	typename BlockCollection<T>::const_iterator BlockCollection<T>::begin(const Filter* filter) const
	{
		Filter emptyFilter;
		if(filter == nullptr)
			filter = &emptyFilter;
		
		const_iterator it(*filter);
		
		it.setBegin(elements.begin());
		it.setEnd(elements.end());
		it = elements.begin();
		
		return it;
	}
	
	
	template<class T>
	typename BlockCollection<T>::iterator BlockCollection<T>::begin(const Filter* filter)
	{
		Filter emptyFilter;
		if(filter == nullptr)
			filter = &emptyFilter;
		
		iterator it(*filter);
		
		it.setBegin(elements.begin());
		it.setEnd(elements.end());
		it = elements.begin();
		
		return it;
	}
	
	
	template<class T>
	typename BlockCollection<T>::const_iterator BlockCollection<T>::end(const Filter* filter) const
	{
		Filter emptyFilter;
		if(filter == nullptr)
			filter = &emptyFilter;
		
		const_iterator it(*filter);
		
		it.setBegin(elements.begin());
		it.setEnd(elements.end());
		it = elements.end();
		
		return it;
	}
	
	
	template<class T>
	typename BlockCollection<T>::iterator BlockCollection<T>::end(const Filter* filter)
	{
		Filter emptyFilter;
		if(filter == nullptr)
			filter = &emptyFilter;
		
		iterator it(*filter);
		
		it.setBegin(elements.begin());
		it.setEnd(elements.end());
		it = elements.end();
		
		return it;
	}
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_BLOCK_COLLECTION_TEMPLATE_HPP






