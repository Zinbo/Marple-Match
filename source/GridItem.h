/*
 * (C) 2014 Search for a Star
 * 
 */

#if !defined(__GRIDITEM_H__)
#define __GRIDITEM_H__

#include "Iw2DSceneGraph.h"
#include "IwGx.h"
#include "CharacterBuilder.h"

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

    GridItem(float x, float y, CharacterBuilder charToMake);
    ~GridItem();

    //Getters
	Iw2DSceneGraph::CSprite * GetStarSprite() { return m_StarSprite; }
	Iw2DSceneGraph::CSprite * GetCharacterSprite() { return m_CharacterSprite; }
	int GetCharacterIndex() { return m_CharacterIndex; }
	bool IsGold() { return m_IsGold;}
	bool IsSilver() { return m_IsSilver;}

	void SetCharacterImage(CharacterBuilder charToMake);

	void RemovePowerup();

private: 
	//Sprites
	Iw2DSceneGraph::CSprite * m_StarSprite;
	Iw2DSceneGraph::CSprite * m_CharacterSprite;

	//Flags
	bool m_IsGold;
	bool m_IsSilver;

	int m_CharacterIndex;

	//Helper methods
	void CreateStarSprite(float x, float y);
	void AssignCorrectCharImage(CharacterBuilder charToMake);
	void CreateCharacterSprite(float x, float y, CharacterBuilder charToMake);
};
}

#endif  // __GRIDITEM_H__


