#include "../../include/listeners/ilslib_listener.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	Listener::Listener(const std::string& newID):
		id(newID),
		active(true),
		callbackFunction(nullptr)
	{
	}
	
	
	Listener::Listener(const Listener& listener, const std::string& newID):
		id(newID),
		active(true),
		callbackFunction(listener.callbackFunction)
	{
	}
	
	
	Listener::~Listener()
	{
	}
	
	
	std::string Listener::getID() const
	{
		return id;
	}
	
	
	bool Listener::isActive() const
	{
		return active;
	}
	
	
	Event::CallbackFunction Listener::getCallbackFunction() const
	{
		return callbackFunction;
	}
	
	
	void Listener::activate()
	{
		active = true;
	}
	
	
	void Listener::deactivate()
	{
		active = false;
	}
	
	
	void Listener::setCallbackFunction(Event::CallbackFunction func)
	{
		callbackFunction = func;
	}
	
	
	void Listener::runCallbackFunction(BasicBlock* block, const Event* eventInfo,
								BlockManager* blockManager, EventQueue* eventQueue)
	{
		if(callbackFunction != nullptr)
			callbackFunction(this, block, eventInfo, blockManager, eventQueue);
	}
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------




