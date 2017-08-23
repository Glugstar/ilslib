///*----------------------------------------------------------------------------------
//								ilslib_transition.hpp
//------------------------------------------------------------------------------------
//Author: Alexandru Razvan Ghitu
//Last modification date: ???
//------------------------------------------------------------------------------------
//ILS (Interface Layout Scheme) library.
//----------------------------------------------------------------------------------*/
//#ifndef ILSLIB_TRANSITION_HPP
//#define ILSLIB_TRANSITION_HPP
//
//#pragma once
//
//#include "ilslib_alternative.hpp"
//
//
//
///*----------------------------------------------------------------------------------
//										ILSLib
//----------------------------------------------------------------------------------*/
//namespace ILSLib
//{
//
//
//
//	/*!---------------------------------------------------------------------------------
//										Transition
//	------------------------------------------------------------------------------------
//	@brief Fill in.
//	*//*------------------------------------------------------------------------------*/
//	class Transition
//	{
//	public:
//		// friends
//		friend class Container;
//
//
//		// constructors & destructor
//		Transition(Container* parent);
//		virtual ~Transition();
//
//
//		// functions
//			// basic element functions
//		virtual Alternative* getCurrentAlternative();
//		virtual void transitionTo(Alternative* alt);
//		virtual const std::unordered_set<std::string>& getAllKeyCodes() const;
//		virtual const DimensionsInfo* getDimensionsInfo(const Settings::Step step) const;
//		virtual const PositionInfo* getPositionInfo() const;
//			// events
//		virtual bool parseMouseEvent(const MouseEvent& event, BlockManager* blockManager, EventQueue& eventQueue, bool multiLayer);
//		virtual bool parseKeyboardEvent(const KeyboardEvent& event, BlockManager* blockManager, EventQueue& eventQueue);
//		virtual bool parseTimeEvent(const TimeEvent& event, BlockManager* blockManager, EventQueue& eventQueue);
//		virtual bool parseWindowEvent(const WindowEvent& event, BlockManager* blockManager, EventQueue& eventQueue);
//			// step 0: clear previous data (strict order)
//		virtual void step0A_clear();
//		virtual void step0B_applyTransformations();
//		virtual void step0C_findAllKeyCodes();
//			// step 1: dimensions and position computations (strict order)
//		virtual void step1A_minimize();
//		virtual void step1B_adjust();
//		virtual void step1C_maximize(int availableWidth, int availableHeight);
//		virtual void step1D_reAdjust();
//			// step 2: drawable map generation
//		virtual void step2A_determinePositions();
//		virtual void step2B_determineCutRectangles();
//		virtual void step2C_addToDrawableMap(DrawableMap* drawables);
//	protected:
//		// functions
//		virtual PositionInfo* getPositionInfo();
//		virtual Vector getAvailableMaximization(Settings::IterationMode mode) const;
//
//
//		// variables
//		Container* parentContainer;
//		Alternative* currentAlternative;
//	};
//
//
//
//} // end namespace ILSLib
////----------------------------------------------------------------------------------
//
//
//
//#endif // ILSLIB_TRANSITION_HPP
//
//
//
//
