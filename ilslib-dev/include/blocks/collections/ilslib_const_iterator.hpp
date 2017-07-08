/*----------------------------------------------------------------------------------
								ilslib_const_iterator.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_CONST_ITERATOR_HPP
#define ILSLIB_CONST_ITERATOR_HPP

#pragma once


#include "ilslib_block_collection.hpp"
#include "ilslib_filter.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	/*!---------------------------------------------------------------------------------
										const_iterator
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	template<class T>
	class BlockCollection<T>::const_iterator
	{
	public:
		// friends
		friend typename BlockCollection<T>::iterator;
		
		
		// constructors & destructor
		const_iterator();
		const_iterator(const iterator& it);
		const_iterator(const const_iterator& it);
		const_iterator(const Filter& elementFilter);
		virtual ~const_iterator();
		
		
		// functions
			// control functions
		virtual void setBegin(const typename BlockCollection<T>::Type::const_iterator& collectionBegin);
		virtual void setEnd(const typename BlockCollection<T>::Type::const_iterator& collectionEnd);
		virtual int getCounter() const;
		virtual bool isFirst() const;
		virtual bool isLast() const;
		virtual bool isEnd() const;
			// dereferencing operators
		virtual const T* operator*() const;
			// comparison operators
		virtual bool operator==(const iterator& it) const;
		virtual bool operator==(const const_iterator& it) const;
		virtual bool operator!=(const iterator& it) const;
		virtual bool operator!=(const const_iterator& it) const;
			// increment/decrement operators
		virtual const_iterator operator++();
		virtual const_iterator& operator++(int);
		virtual const_iterator operator--();
		virtual const_iterator& operator--(int);
			// assignment operators
		virtual const_iterator& operator=(const iterator& it);
		virtual const_iterator& operator=(const const_iterator& it);
		virtual void operator=(const typename BlockCollection<T>::Type::iterator& collectionCurrent);
		virtual void operator=(const typename BlockCollection<T>::Type::const_iterator& collectionCurrent);
	protected:
		// functions
		virtual const_iterator& navigate(bool forward,
									const typename BlockCollection<T>::Type::const_iterator& limit);
		
		
		// variables
		typename BlockCollection<T>::Type::const_iterator internalIterator;
		typename BlockCollection<T>::Type::const_iterator internalBegin;
		typename BlockCollection<T>::Type::const_iterator internalEnd;
		Filter filter;
		int counter;
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



// template implementations
#include "ilslib_const_iterator_template.hpp"



#endif // ILSLIB_CONST_ITERATOR_HPP





