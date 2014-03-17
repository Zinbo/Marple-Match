/*
 * (C) 2014 Search for a Star
 * 
 */

#include "GridItem.h"

#include "resources.h"

using namespace Iw2DSceneGraphCore;
using namespace Iw2DSceneGraph;
#define STAR_WIDTH 65
#define SCREEN_WIDTH 320

using namespace SFAS2014;

GridItem::GridItem( float x, float y)
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
	float starScale = STAR_WIDTH / mSprite->m_W;
	starScale = starScale * ((float) IwGxGetScreenWidth() / SCREEN_WIDTH);
	mSprite->m_ScaleX = starScale;
	mSprite->m_ScaleY = starScale;
}

GridItem::~GridItem()
{
}


void GridItem::Reset()
{
}
