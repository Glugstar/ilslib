#include "../../include/listeners/ilslib_time_listener.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	TimeListener::TimeListener(const std::string& newID):
		Listener(newID),
		timerAccumulated(0),
		timerInterval(0),
		timerType(TimerType::None)
	{
	}
	
	
	TimeListener::TimeListener(const TimeListener& listener, const std::string& newID):
		Listener(listener, newID),
		timerAccumulated(0),
		timerInterval(listener.timerInterval),
		timerType(listener.timerType)
	{
	}
	
	
	TimeListener::~TimeListener()
	{
	}
	
	
	void TimeListener::setPeriodicTimer(TimerType type, int interval)
	{
		timerAccumulated = 0;
		timerInterval = interval;
		timerType = type;
	}
	
	
	void TimeListener::runCallbackFunction(BasicBlock* block, const Event* eventInfo,
								BlockManager* blockManager, EventQueue* eventQueue)
	{
		if(timerType != TimerType::None)
		{
			timerAccumulated += eventInfo->getElapsedTime();
			
			if(timerAccumulated < timerInterval)
				return;
			
			if(timerType == TimerType::Reset)
				timerAccumulated = 0;
			else
			{
				if(timerInterval > 0)
					timerAccumulated %= timerInterval;
				else
					timerAccumulated = 0;
			}
		}
		
		Listener::runCallbackFunction(block, eventInfo, blockManager, eventQueue);
	}
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------




