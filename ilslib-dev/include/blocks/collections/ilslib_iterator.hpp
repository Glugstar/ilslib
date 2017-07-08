/*----------------------------------------------------------------------------------
								ilslib_iterator.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_ITERATOR_HPP
#define ILSLIB_ITERATOR_HPP

#pragma once


#include "ilslib_block_collection.hpp"
#include "ilslib_filter.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	/*!---------------------------------------------------------------------------------
										iterator
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	template<class T>
	class BlockCollection<T>::iterator
	{
	public:
		// friends
		friend typename BlockCollection<T>::const_iterator;
		
		
		// constructors & destructor
		iterator();
		iterator(const iterator& it);
		iterator(const Filter& elementFilter);
		virtual ~iterator();
		
		
		// functions
			// control functions
		virtual void setBegin(const typename BlockCollection<T>::Type::iterator& collectionBegin);
		virtual void setEnd(const typename BlockCollection<T>::Type::iterator& collectionEnd);
		virtual int getCounter() const;
		virtual bool isFirst() const;
		virtual bool isLast() const;
		virtual bool isEnd() const;
		virtual typename BlockCollection<T>::Type::iterator getInternalIterator();
			// dereferencing operators
		virtual T*& operator*() const;
			// comparison operators
		virtual bool operator==(const iterator& it) const;
		virtual bool operator==(const const_iterator& it) const;
		virtual bool operator!=(const iterator& it) const;
		virtual bool operator!=(const const_iterator& it) const;
			// increment/decrement operators
		virtual iterator operator++();
		virtual iterator& operator++(int);
		virtual iterator operator--();
		virtual iterator& operator--(int);
			// assignment operators
		virtual iterator& operator=(const iterator& it);
		virtual void operator=(const typename BlockCollection<T>::Type::iterator& collectionCurrent);
	protected:
		// functions
		virtual iterator& navigate(bool forward,
									const typename BlockCollection<T>::Type::iterator& limit);
		
		
		// variables
		typename BlockCollection<T>::Type::iterator internalIterator;
		typename BlockCollection<T>::Type::iterator internalBegin;
		typename BlockCollection<T>::Type::iterator internalEnd;
		Filter filter;
		int counter;
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



// template implementations
#include "ilslib_iterator_template.hpp"



#endif // ILSLIB_ITERATOR_HPP





