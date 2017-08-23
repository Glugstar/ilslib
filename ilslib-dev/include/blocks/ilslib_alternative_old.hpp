///*----------------------------------------------------------------------------------
//								ilslib_alternative.hpp
//------------------------------------------------------------------------------------
//Author: Alexandru Razvan Ghitu
//Last modification date: ???
//------------------------------------------------------------------------------------
//ILS (Interface Layout Scheme) library.
//----------------------------------------------------------------------------------*/
//#ifndef ILSLIB_ALTERNATIVE_HPP
//#define ILSLIB_ALTERNATIVE_HPP
//
//#pragma once
//
//#include "ilslib_layer.hpp"
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
//										Alternative
//	------------------------------------------------------------------------------------
//	@brief Fill in.
//	*//*------------------------------------------------------------------------------*/
//	class Alternative
//	{
//	public:
//		// friends
//		friend class BlockManager;
//		friend class Container;
//		friend class Transition;
//
//
//		// constructors & destructor
//		Alternative(const std::string& alternativeID, const std::string& layerID);
//		virtual ~Alternative();
//
//
//		// functions
//			// basic element functions
//		virtual const std::string& getID() const;
//		virtual std::string getPath() const;
//		virtual const Container* getParentContainer() const;
//		virtual Container* getParentContainer();
//		virtual void getBasicBlocks(std::list<BasicBlock*>& blockList);
//		virtual BasicBlock* findBasicBlock(const std::string& blockID);
//		virtual Layer* findLayer(const std::string& layerID);
//		virtual void addLayer(Layer* layer);
//		virtual void removeLayer(const std::string& id);
//		virtual void removeAllLayers();
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
//		virtual void step1A_minimize(const ContainerSettings* currentSettings);
//		virtual void step1B_adjust();
//		virtual void step1C_maximize(const ContainerSettings* currentSettings,
//									int availableWidth, int availableHeight);
//		virtual void step1D_reAdjust();
//			// step 2: drawable map generation
//		virtual void step2A_determinePositions(const ContainerSettings* currentSettings);
//		virtual void step2B_determineCutRectangles(const Rectangle& availableSpace);
//		virtual void step2C_addToDrawableMap(DrawableMap* drawables);
//	protected:
//		// functions
//		virtual PositionInfo* getPositionInfo();
//		virtual Vector getAvailableMaximization(Settings::IterationMode mode) const;
//		virtual void createLayer(const std::string& layerID);
//
//
//		// variables
//		std::string id;
//		Container* parentContainer;
//		std::list<Layer*> layers;
//		std::unordered_set<std::string> allKeyCodes;
//		DimensionsInfo dInfoStep1A;
//		DimensionsInfo dInfoStep1B;
//		DimensionsInfo dInfoStep1C;
//		DimensionsInfo dInfoStep1D;
//		PositionInfo pInfo;
//	};
//
//
//
//} // end namespace ILSLib
////----------------------------------------------------------------------------------
//
//
//
//#endif // ILSLIB_ALTERNATIVE_HPP
//
//
//
//
