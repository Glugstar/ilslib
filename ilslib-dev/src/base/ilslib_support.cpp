#include "../../include/base/ilslib_support.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	/*----------------------------------------------------------------------------------
											Support
	----------------------------------------------------------------------------------*/
	namespace Support
	{
		
		
		
		std::string& leftTrim(std::string& s)
		{
			s.erase(s.begin(), std::find_if(s.begin(), s.end(),
					std::not1(std::ptr_fun<int, int>(std::isspace))));
			return s;
		}
		
		
		std::string& rightTrim(std::string& s)
		{
			s.erase(std::find_if(s.rbegin(), s.rend(),
					std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
			return s;
		}
		
		
		std::string& trim(std::string& s)
		{
			rightTrim(s);
			return leftTrim(s);
		}
		
		
		
	} // end namespace Support
} // end namespace ILSLib
//----------------------------------------------------------------------------------




