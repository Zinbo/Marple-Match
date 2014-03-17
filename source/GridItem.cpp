/*
 * (C) 2014 Search for a Star
 * 
 */

#include "GridItem.h"

#include "resources.h"

using namespace Iw2DSceneGraphCore;
using namespace Iw2DSceneGraph;

using namespace SFAS2014;
//
//
// GridItem class
//
//
CColor GridItem::mShapeColours[GridItem::NumberOfShapes] = 
{
		CColor( 128, 255, 154, 255 ),
		CColor( 255, 181, 255, 255 ),
		CColor( 128, 255, 232, 255 ),
		CColor( 240, 255, 140, 255 )
};

CColor GridItem::mHighlightColour = CColor( 255, 128, 128, 255 );

GridItem::GridItem( float x, float y, Shape shape)
{
	mSprite = new CSprite();
	mSprite->m_X = x;
	mSprite->m_Y = y;
	
	mShape = shape;

	if( mShape == Circle )
	{
		mSprite->SetImage(g_pResources->getCircle());
	}
	else if( mShape == Square )
	{
		mSprite->SetImage(g_pResources->getSquare());
	}
	else if( mShape == Triangle )
	{
		mSprite->SetImage(g_pResources->getTriangle());
	}
	else if( mShape == Star )
	{
		mSprite->SetImage(g_pResources->getStar());
	}

	mSprite->m_Color = mShapeColours[mShape];

	mSprite->m_W = mSprite->GetImage()->GetWidth();
	mSprite->m_H = mSprite->GetImage()->GetHeight();
	mSprite->m_AnchorX = 0.0f;
	mSprite->m_AnchorY = 0.0f;
 
	// Fit grid to screen size
	mSprite->m_ScaleX = 1.0f;
	mSprite->m_ScaleY = 1.0f;
}

GridItem::~GridItem()
{
}

void GridItem::Highlight()
{
	mSprite->m_Color = mHighlightColour;
}

void GridItem::Reset()
{
	mSprite->m_Color = mShapeColours[mShape];
}
