/*----------------------------------------------------------------------------------
							ilslib_const_iterator_template.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.

DO NOT INCLUDE THIS FILE DIRECTLY
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_CONST_ITERATOR_TEMPLATE_HPP
#define ILSLIB_CONST_ITERATOR_TEMPLATE_HPP



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	template<class T>
	BlockCollection<T>::const_iterator::const_iterator():
		internalIterator(),
		internalBegin(internalIterator),
		internalEnd(internalIterator),
		filter(),
		counter(0)
	{
	}
	
	
	template<class T>
	BlockCollection<T>::const_iterator::const_iterator(const iterator& it):
		internalIterator(it.internalIterator),
		internalBegin(it.internalBegin),
		internalEnd(it.internalEnd),
		filter(it.filter),
		counter(it.counter)
	{
	}
	
	
	template<class T>
	BlockCollection<T>::const_iterator::const_iterator(const const_iterator& it):
		internalIterator(it.internalIterator),
		internalBegin(it.internalBegin),
		internalEnd(it.internalEnd),
		filter(it.filter),
		counter(it.counter)
	{
	}
	
	
	template<class T>
	BlockCollection<T>::const_iterator::const_iterator(const Filter& elementFilter):
		internalIterator(),
		internalBegin(internalIterator),
		internalEnd(internalIterator),
		filter(elementFilter),
		counter(0)
	{
	}
	
	
	template<class T>
	BlockCollection<T>::const_iterator::~const_iterator()
	{
	}
	
	
	template<class T>
	void BlockCollection<T>::const_iterator::setBegin(const typename BlockCollection<T>::Type::const_iterator& collectionBegin)
	{
		internalBegin = collectionBegin;
		if(internalIterator == internalBegin)
			counter = 0;
	}
	
	
	template<class T>
	void BlockCollection<T>::const_iterator::setEnd(const typename BlockCollection<T>::Type::const_iterator& collectionEnd)
	{
		internalEnd = collectionEnd;
		if(internalIterator == internalBegin)
			counter = 0;
	}
	
	
	template<class T>
	int BlockCollection<T>::const_iterator::getCounter() const
	{
		if(internalIterator == internalEnd)
			return -1;
		return counter;
	}
	
	
	template<class T>
	bool BlockCollection<T>::const_iterator::isFirst() const
	{
		return internalIterator == internalBegin;
	}
	
	
	template<class T>
	bool BlockCollection<T>::const_iterator::isLast() const
	{
		if(internalIterator == internalEnd)
			return false;
		
		const_iterator itCopy = *this;
		++itCopy;
		
		return itCopy.isEnd();
	}
	
	
	template<class T>
	bool BlockCollection<T>::const_iterator::isEnd() const
	{
		return internalIterator == internalEnd;
	}
	
	
	template<class T>
	const T* BlockCollection<T>::const_iterator::operator*() const
	{
		return *internalIterator;
	}
	
	
	template<class T>
	bool BlockCollection<T>::const_iterator::operator==(const iterator& it) const
	{
		return internalIterator == it.internalIterator;
	}


	template<class T>
	bool BlockCollection<T>::const_iterator::operator==(const const_iterator& it) const
	{
		return internalIterator == it.internalIterator;
	}
	
	
	template<class T>
	bool BlockCollection<T>::const_iterator::operator!=(const iterator& it) const
	{
		return internalIterator != it.internalIterator;
	}
	
	
	template<class T>
	bool BlockCollection<T>::const_iterator::operator!=(const const_iterator& it) const
	{
		return internalIterator != it.internalIterator;
	}
	
	
	template<class T>
	typename BlockCollection<T>::const_iterator BlockCollection<T>::const_iterator::operator++()
	{
		const_iterator returnCopy = *this;
		
		return navigate(true, internalEnd);
		
		return returnCopy;
	}
	
	
	template<class T>
	typename BlockCollection<T>::const_iterator& BlockCollection<T>::const_iterator::operator++(int)
	{
		return navigate(true, internalBegin);
	}
	
	
	template<class T>
	typename BlockCollection<T>::const_iterator BlockCollection<T>::const_iterator::operator--()
	{
		const_iterator returnCopy = *this;
		
		return navigate(false, internalBegin);
		
		return returnCopy;
	}
	
	
	template<class T>
	typename BlockCollection<T>::const_iterator& BlockCollection<T>::const_iterator::operator--(int)
	{
		return navigate(false, internalBegin);
	}
	
	
	template<class T>
	typename BlockCollection<T>::const_iterator& BlockCollection<T>::const_iterator::operator=(const const_iterator& it)
	{
		internalIterator = it.internalIterator;
		internalBegin = it.internalBegin;
		internalEnd = it.internalEnd;
		filter = it.filter;
		counter = it.counter;
		
		return *this;
	}
	
	
	template<class T>
	typename BlockCollection<T>::const_iterator& BlockCollection<T>::const_iterator::operator=(const iterator& it)
	{
		internalIterator = it.internalIterator;
		internalBegin = it.internalBegin;
		internalEnd = it.internalEnd;
		filter = it.filter;
		counter = it.counter;
		
		return *this;
	}
	
	
	template<class T>
	void BlockCollection<T>::const_iterator::operator=(const typename BlockCollection<T>::Type::iterator& collectionCurrent)
	{
		internalIterator = collectionCurrent;
	}
	
	
	template<class T>
	void BlockCollection<T>::const_iterator::operator=(const typename BlockCollection<T>::Type::const_iterator& collectionCurrent)
	{
		internalIterator = collectionCurrent;
	}
	
	
	template<class T>
	typename BlockCollection<T>::const_iterator& BlockCollection<T>::const_iterator::navigate(bool forward,
									const typename BlockCollection<T>::Type::const_iterator& limit)
	{
		typename BlockCollection<T>::Type::const_iterator iteratorCopy = internalIterator;
		
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



#endif // ILSLIB_CONST_ITERATOR_TEMPLATE_HPP






