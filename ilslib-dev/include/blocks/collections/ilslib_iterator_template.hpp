/*----------------------------------------------------------------------------------
							ilslib_iterator_template.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.

DO NOT INCLUDE THIS FILE DIRECTLY
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_ITERATOR_TEMPLATE_HPP
#define ILSLIB_ITERATOR_TEMPLATE_HPP



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	template<class T>
	BlockCollection<T>::iterator::iterator():
		internalIterator(),
		internalBegin(internalIterator),
		internalEnd(internalIterator),
		filter(),
		counter(0)
	{
	}
	
	
	template<class T>
	BlockCollection<T>::iterator::iterator(const iterator& it):
		internalIterator(it.internalIterator),
		internalBegin(it.internalBegin),
		internalEnd(it.internalEnd),
		filter(it.filter),
		counter(it.counter)
	{
	}
	
	
	template<class T>
	BlockCollection<T>::iterator::iterator(const Filter& elementFilter):
		internalIterator(),
		internalBegin(internalIterator),
		internalEnd(internalIterator),
		filter(elementFilter),
		counter(0)
	{
	}
	
	
	template<class T>
	BlockCollection<T>::iterator::~iterator()
	{
	}
	
	
	template<class T>
	void BlockCollection<T>::iterator::setBegin(const typename BlockCollection<T>::Type::iterator& collectionBegin)
	{
		internalBegin = collectionBegin;
		if(internalIterator == internalBegin)
			counter = 0;
	}
	
	
	template<class T>
	void BlockCollection<T>::iterator::setEnd(const typename BlockCollection<T>::Type::iterator& collectionEnd)
	{
		internalEnd = collectionEnd;
		if(internalIterator == internalBegin)
			counter = 0;
	}
	
	
	template<class T>
	int BlockCollection<T>::iterator::getCounter() const
	{
		if(internalIterator == internalEnd)
			return -1;
		return counter;
	}
	
	
	template<class T>
	bool BlockCollection<T>::iterator::isFirst() const
	{
		return internalIterator == internalBegin;
	}
	
	
	template<class T>
	bool BlockCollection<T>::iterator::isLast() const
	{
		if(internalIterator == internalEnd)
			return false;
		
		iterator itCopy = *this;
		++itCopy;
		
		return itCopy.isEnd();
	}
	
	
	template<class T>
	bool BlockCollection<T>::iterator::isEnd() const
	{
		return internalIterator == internalEnd;
	}
	
	
	template<class T>
	typename BlockCollection<T>::Type::iterator BlockCollection<T>::iterator::getInternalIterator()
	{
		return internalIterator;
	}
	
	
	template<class T>
	T*& BlockCollection<T>::iterator::operator*() const
	{
		return *internalIterator;
	}
	
	
	template<class T>
	bool BlockCollection<T>::iterator::operator==(const iterator& it) const
	{
		return internalIterator == it.internalIterator;
	}
	
	
	template<class T>
	bool BlockCollection<T>::iterator::operator==(const const_iterator& it) const
	{
		return internalIterator == it.internalIterator;
	}
	
	
	template<class T>
	bool BlockCollection<T>::iterator::operator!=(const iterator& it) const
	{
		return internalIterator != it.internalIterator;
	}
	
	
	template<class T>
	bool BlockCollection<T>::iterator::operator!=(const const_iterator& it) const
	{
		return internalIterator != it.internalIterator;
	}
	
	
	template<class T>
	typename BlockCollection<T>::iterator BlockCollection<T>::iterator::operator++()
	{
		iterator returnCopy = *this;
		
		return navigate(true, internalEnd);
		
		return returnCopy;
	}
	
	
	template<class T>
	typename BlockCollection<T>::iterator& BlockCollection<T>::iterator::operator++(int)
	{
		return navigate(true, internalBegin);
	}
	
	
	template<class T>
	typename BlockCollection<T>::iterator BlockCollection<T>::iterator::operator--()
	{
		iterator returnCopy = *this;
		
		return navigate(false, internalBegin);
		
		return returnCopy;
	}
	
	
	template<class T>
	typename BlockCollection<T>::iterator& BlockCollection<T>::iterator::operator--(int)
	{
		return navigate(false, internalBegin);
	}
	
	
	template<class T>
	typename BlockCollection<T>::iterator& BlockCollection<T>::iterator::operator=(const iterator& it)
	{
		internalIterator = it.internalIterator;
		internalBegin = it.internalBegin;
		internalEnd = it.internalEnd;
		filter = it.filter;
		counter = it.counter;
		
		return *this;
	}
	
	
	template<class T>
	void BlockCollection<T>::iterator::operator=(const typename BlockCollection<T>::Type::iterator& collectionCurrent)
	{
		internalIterator = collectionCurrent;
	}
	
	
	template<class T>
	typename BlockCollection<T>::iterator& BlockCollection<T>::iterator::navigate(bool forward,
									const typename BlockCollection<T>::Type::iterator& limit)
	{
		
		typename BlockCollection<T>::Type::iterator iteratorCopy = internalIterator;
		
		while(internalIterator != limit)
		{
			if(forward == true)
				++internalIterator;
			else
				--internalIterator;
			
			if(internalIterator == limit)
				break;
			
			if(filter.filterElement(*internalIterator) == true)
				break;
		}
		
		if(iteratorCopy != internalIterator)
		{
			if(forward == true)
				++counter;
			else
				--counter;
		}
		
		if(internalIterator == internalBegin)
			counter = 0;
		
		return *this;
	}
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_ITERATOR_TEMPLATE_HPP






