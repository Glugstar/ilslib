#include "../../include/resources/ilslib_resource.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	Resource::Resource(const std::string& uniqueID, void* uniqueRealResource):
		id(uniqueID),
		realResource(uniqueRealResource)
	{
	}
	
	
	Resource::~Resource()
	{
	}
	
	
	const std::string& Resource::getID() const
	{
		return id;
	}
	
	
	void* Resource::getResource()
	{
		return realResource;
	}
	
	
	void Resource::removeResource()
	{
		realResource = nullptr;
	}
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------




