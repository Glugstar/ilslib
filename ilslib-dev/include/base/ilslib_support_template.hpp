/*----------------------------------------------------------------------------------
								ilslib_support_template.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.

DO NOT INCLUDE THIS FILE DIRECTLY
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_SUPPORT_TEMPLATE_HPP
#define ILSLIB_SUPPORT_TEMPLATE_HPP



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
		
		
		
		template<class ContainerT>
		void tokenize(const std::string& str, ContainerT& tokens,
					const std::string& delimiters, bool trimEmpty)
		{
			if(str.length() == 0)
				return;
			tokens.clear();
			
			std::string::size_type pos, lastPos = 0;
			using value_type = typename ContainerT::value_type;
			using size_type = typename ContainerT::size_type;
			
			while(true)
			{
				pos = str.find_first_of(delimiters, lastPos);
				
				if(pos == std::string::npos)
				{
					pos = str.length();
					
					if(pos != lastPos || !trimEmpty)
					{
						tokens.push_back(value_type(str.data() + lastPos,
										(size_type)pos - lastPos));
					}
					
					break;
				}
				
				if(pos != lastPos || !trimEmpty)
				{
					tokens.push_back(value_type(str.data() + lastPos,
									(size_type)pos - lastPos));
				}
				
				lastPos = pos + 1;
			}
		}
		
		
		template<class T>
		std::string NumberToString(T Number)
		{
			std::ostringstream ss;
			ss << Number;
			return ss.str();
		}
		
		
		
	} // end namespace Support
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_SUPPORT_TEMPLATE_HPP






