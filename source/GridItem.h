/*
 * (C) 2014 Search for a Star
 * 
 */

#if !defined(__GRIDITEM_H__)
#define __GRIDITEM_H__

#include "Iw2DSceneGraph.h"
#include "IwGx.h"
#include "CharacterBuilder.h"
#include "resources.h"

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
	Iw2DSceneGraph::CSprite * GetStarSprite() const { return m_StarSprite; }
	Iw2DSceneGraph::CSprite * GetCharacterSprite() const { return m_CharacterSprite; }
	int GetCharacterIndex() const { return m_CharacterIndex; }
	bool IsGold() const { return m_IsGold;}
	bool IsSilver() const { return m_IsSilver;}

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

	enum dimensions 
	{
		feStarHeight = 60,
		feScreenHeight = 480,
		feScreenWidth = 320
	};

	enum characterProperties
	{
		feGoldCharIndex = 12,
		feSilverCharIndex = 13
	};
};
}

#endif  // __GRIDITEM_H__


