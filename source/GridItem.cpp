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
#define SCREEN_HEIGHT 480

using namespace SFAS2014;

GridItem::GridItem( float x, float y, int characterIndex)
{
	mSprite = new CSprite();
	mSprite->m_X = x;
	mSprite->m_Y = y;

	mSprite->SetImage(g_pResources->getStar());
	mSprite->m_W = mSprite->GetImage()->GetWidth();
	mSprite->m_H = mSprite->GetImage()->GetHeight();
 
	// Fit grid to screen size
	float starScale = STAR_HEIGHT / mSprite->m_H;
	float starXScale = starScale * ((float) IwGxGetScreenWidth() / SCREEN_WIDTH);
	float starYScale = starScale * ((float) IwGxGetScreenHeight() / SCREEN_HEIGHT);
	mSprite->m_ScaleX = starXScale;
	mSprite->m_ScaleY = starYScale;
	mSprite->m_AnchorX = 0.5f;
	mSprite->m_AnchorY = 0.5f;

	mCharacterIndex = characterIndex;

	//Assign character sprite
	characterSprite = new CSprite();
	characterSprite->m_X = x;
	characterSprite->m_Y = y;
	characterSprite->SetImage(g_pResources->GetCharacter(characterIndex));
	characterSprite->m_W = characterSprite->GetImage()->GetWidth();
	characterSprite->m_H = characterSprite->GetImage()->GetHeight();
	characterSprite->m_AnchorX = 0.5f;
	characterSprite->m_AnchorY = 0.5f;
	float charScale = STAR_HEIGHT / characterSprite->m_H;
	float charXScale = charScale * ((float) IwGxGetScreenWidth() / SCREEN_WIDTH);
	float charYScale = charScale * ((float) IwGxGetScreenHeight() / SCREEN_HEIGHT);
	characterSprite->m_ScaleX = charXScale;
	characterSprite->m_ScaleY = charYScale;
	characterSprite->m_IsVisible = false;

}

GridItem::~GridItem()
{
}

void GridItem::Reset()
{
}

void GridItem::SetCharacterImage(int characterIndex)
{
	characterSprite->SetImage(g_pResources->GetCharacter(characterIndex));
	characterSprite->m_IsVisible = false;
	mCharacterIndex = characterIndex;
}
