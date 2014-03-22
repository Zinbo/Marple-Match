/*
 * (C) 2014 Search for a Star
 * 
 */

#include "GridItem.h"

#include "resources.h"

using namespace Iw2DSceneGraphCore;
using namespace Iw2DSceneGraph;
#define STAR_HEIGHT 60
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 480
#define GOLD_CHAR_INDEX 12
#define SILVER_CHAR_INDEX 13

using namespace SFAS2014;

GridItem::GridItem(float x, float y, CharacterBuilder charToMake)
{
	CreateStarSprite(x, y);
	m_CharacterIndex = charToMake.GetCharacterIndex();
	CreateCharacterSprite(x, y, charToMake);
}

GridItem::~GridItem()
{
}

void GridItem::SetCharacterImage(CharacterBuilder charToMake)
{
	//Update the character index and make the sprite invisible
	m_CharacterIndex = charToMake.GetCharacterIndex();
	m_CharacterSprite->m_IsVisible = false;

	//If the char is gold, set iamge to gold character, and update bool flags.
	if(charToMake.IsGold())
	{
		m_IsGold = true;
		m_IsSilver = false;
		m_CharacterSprite->SetImage(g_pResources->GetCharacter(GOLD_CHAR_INDEX));
	}
	//Else if the char is silver, set image to silver character, and update bool flags.
	else if(charToMake.IsSilver())
	{
		m_IsGold = false;
		m_IsSilver = true;
		m_CharacterSprite->SetImage(g_pResources->GetCharacter(SILVER_CHAR_INDEX));
	}
	//Else the character should just be set to the character identified by the character index.
	else
	{
		m_IsGold = false;
		m_IsSilver = false;
		m_CharacterSprite->SetImage(g_pResources->GetCharacter(m_CharacterIndex));
	}

}

void GridItem::CreateCharacterSprite(float x, float y, CharacterBuilder charToMake)
{
	//Create character sprite and make it invisible
	m_CharacterSprite = new CSprite();
	m_CharacterSprite->m_X = x;
	m_CharacterSprite->m_Y = y;
	SetCharacterImage(charToMake);
	m_CharacterSprite->m_AnchorX = 0.5f;
	m_CharacterSprite->m_AnchorY = 0.5f;
	m_CharacterSprite->m_W = m_CharacterSprite->GetImage()->GetWidth();
	m_CharacterSprite->m_H = m_CharacterSprite->GetImage()->GetHeight();

	//Scale the character to STAR_HEIGHT, then scale to the resolution of the screen.
	float charScale = STAR_HEIGHT / m_CharacterSprite->m_H;
	float charXScale = charScale * ((float) IwGxGetScreenWidth() / SCREEN_WIDTH);
	float charYScale = charScale * ((float) IwGxGetScreenHeight() / SCREEN_HEIGHT);
	m_CharacterSprite->m_ScaleX = charXScale;
	m_CharacterSprite->m_ScaleY = charYScale;
}

void GridItem::CreateStarSprite(float x, float y)
{
	//Create star sprite
	m_StarSprite = new CSprite();
	m_StarSprite->m_X = x;
	m_StarSprite->m_Y = y;
	m_StarSprite->m_AnchorX = 0.5f;
	m_StarSprite->m_AnchorY = 0.5f;
	m_StarSprite->SetImage(g_pResources->getStar());
	m_StarSprite->m_W = m_StarSprite->GetImage()->GetWidth();
	m_StarSprite->m_H = m_StarSprite->GetImage()->GetHeight();
 
	//Scale the star to STAR_HEIGHT, then scale to the resolution of the screen.
	float starScale = STAR_HEIGHT / m_StarSprite->m_H;
	float starXScale = starScale * ((float) IwGxGetScreenWidth() / SCREEN_WIDTH);
	float starYScale = starScale * ((float) IwGxGetScreenHeight() / SCREEN_HEIGHT);
	m_StarSprite->m_ScaleX = starXScale;
	m_StarSprite->m_ScaleY = starYScale;
	
}

void GridItem::RemovePowerup()
{
	m_CharacterSprite->SetImage(g_pResources->GetCharacter(m_CharacterIndex));
	m_IsGold = false;
	m_IsSilver = false;
}

