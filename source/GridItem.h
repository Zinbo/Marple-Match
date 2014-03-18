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

    GridItem( float x, float y, int characterIndex);
    ~GridItem();

    /**
     * @fn    const CSprite * GridItem::GetSprite();
     *
     * @brief Returns the sprite for this GridItem
     *
     */
	Iw2DSceneGraph::CSprite * GetStarSprite() { return mSprite; }

	Iw2DSceneGraph::CSprite * GetCharacterSprite() { return characterSprite; }

    /**
     * @fn    void GridItem::Reset();
     *
     * @brief Resets the grid item to it's normal colour
     *
     */
	void Reset();


private: 

	Iw2DSceneGraph::CSprite * mSprite;
	Iw2DSceneGraph::CSprite * characterSprite;
};
}

#endif  // __GRIDITEM_H__


