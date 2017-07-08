/*----------------------------------------------------------------------------------
								ilslib_resource.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_RESOURCE_HPP
#define ILSLIB_RESOURCE_HPP

#pragma once

#include "../base/ilslib_support.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	/*!---------------------------------------------------------------------------------
											Resource
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	class Resource
	{
	public:
		// constructors & destructor
		Resource(const std::string& uniqueID, void* uniqueRealResource);
		virtual ~Resource();
		
		
		// functions
		virtual const std::string& getID() const;
		virtual void* getResource();
		virtual void removeResource();
	protected:
		// variables
		std::string id;
		void* realResource;
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_RESOURCE_HPP




