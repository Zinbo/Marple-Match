/*
 * (C) 2014 Search for a Star
 * 
 */

#if !defined(__GRIDITEM_H__)
#define __GRIDITEM_H__

#include "Iw2DSceneGraph.h"

namespace SFAS2014
{

/**
 * @class GridItem
 *
 * @brief Manages the GridItem items position and the state of the GridItem.
 *
 */
class GridItem 
{

public:	
	
	enum Shape
	{
		Circle,
		Square,
		Triangle,
		Star,

		NumberOfShapes
	};


    GridItem( float x, float y, Shape shape);
    ~GridItem();

    /**
     * @fn    const CSprite * GridItem::GetSprite();
     *
     * @brief Returns the sprite for this GridItem
     *
     */
	Iw2DSceneGraph::CSprite * GetSprite() { return mSprite; }

    /**
     * @fn    void GridItem::Highlight();
     *
     * @brief Highlights the gird item with the highlight colour
     *
     */
	void Highlight();

    /**
     * @fn    void GridItem::Reset();
     *
     * @brief Resets the grid item to it's normal colour
     *
     */
	void Reset();


private: 

	Iw2DSceneGraph::CSprite * mSprite;
	Shape mShape;
	
	static Iw2DSceneGraph::CColor mShapeColours[NumberOfShapes];
	static Iw2DSceneGraph::CColor mHighlightColour;
};
}

#endif  // __GRIDITEM_H__


