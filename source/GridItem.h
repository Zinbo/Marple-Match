/*
 * (C) 2014 Search for a Star
 * 
 */

#if !defined(__GRIDITEM_H__)
#define __GRIDITEM_H__

#include "Iw2DSceneGraph.h"
#include "IwGx.h"

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


    GridItem( float x, float y);
    ~GridItem();

    /**
     * @fn    const CSprite * GridItem::GetSprite();
     *
     * @brief Returns the sprite for this GridItem
     *
     */
	Iw2DSceneGraph::CSprite * GetSprite() { return mSprite; }

    /**
     * @fn    void GridItem::Reset();
     *
     * @brief Resets the grid item to it's normal colour
     *
     */
	void Reset();


private: 

	Iw2DSceneGraph::CSprite * mSprite;
};
}

#endif  // __GRIDITEM_H__


