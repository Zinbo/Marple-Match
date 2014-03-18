/*
 * (C) 2014 Search for a Star
 * 
 */

#include "GridItem.h"

#include "resources.h"

using namespace Iw2DSceneGraphCore;
using namespace Iw2DSceneGraph;
#define STAR_HEIGHT 65
#define SCREEN_WIDTH 320

using namespace SFAS2014;

GridItem::GridItem( float x, float y, Character c)
{
	mSprite = new CSprite();
	mSprite->m_X = x;
	mSprite->m_Y = y;

	mSprite->SetImage(g_pResources->getStar());
	mSprite->m_W = mSprite->GetImage()->GetWidth();
	mSprite->m_H = mSprite->GetImage()->GetHeight();
	mSprite->m_AnchorX = 0.0f;
	mSprite->m_AnchorY = 0.0f;
 
	// Fit grid to screen size
	float starScale = STAR_HEIGHT / mSprite->m_H;
	starScale = starScale * ((float) IwGxGetScreenWidth() / SCREEN_WIDTH);
	mSprite->m_ScaleX = starScale;
	mSprite->m_ScaleY = starScale;
	mSprite->m_AnchorX = 0.5f;
	mSprite->m_AnchorY = 0.5f;

	//Assign character sprite
	characterSprite = new CSprite();
	characterSprite->m_X = x;
	characterSprite->m_Y = y;
	AssignCharacterAndColour(c);
	characterSprite->m_W = characterSprite->GetImage()->GetWidth();
	characterSprite->m_H = characterSprite->GetImage()->GetHeight();
	characterSprite->m_AnchorX = 0.5f;
	characterSprite->m_AnchorY = 0.5f;
	float charScale = STAR_HEIGHT / characterSprite->m_H;
	charScale = charScale * ((float) IwGxGetScreenWidth() / SCREEN_WIDTH);
	characterSprite->m_ScaleX = charScale;
	characterSprite->m_ScaleY = charScale;
	characterSprite->m_IsVisible = false;

}

GridItem::~GridItem()
{
}

void GridItem::AssignCharacterAndColour(Character c)
{
	switch(c)
	{
	case char1Red:
		characterSprite->SetImage(g_pResources->getChar1Red());
		break;
	case char2Red:
		characterSprite->SetImage(g_pResources->getChar2Red());
		break;
	case char3Red:
		characterSprite->SetImage(g_pResources->getChar3Red());
		break;
	case char1Blue:
		characterSprite->SetImage(g_pResources->getChar1Blue());
		break;
	case char2Blue:
		characterSprite->SetImage(g_pResources->getChar2Blue());
		break;
	case char3Blue:
		characterSprite->SetImage(g_pResources->getChar3Blue());
		break;
	case char1Green:
		characterSprite->SetImage(g_pResources->getChar1Green());
		break;
	case char2Green:
		characterSprite->SetImage(g_pResources->getChar2Green());
		break;
	case char3Green:
		characterSprite->SetImage(g_pResources->getChar3Green());
		break;
	case char1Orange:
		characterSprite->SetImage(g_pResources->getChar1Orange());
		break;
	case char2Orange:
		characterSprite->SetImage(g_pResources->getChar2Orange());
		break;
	case char3Orange:
		characterSprite->SetImage(g_pResources->getChar3Orange());
		break;
		

	}
}

void GridItem::Reset()
{
}

