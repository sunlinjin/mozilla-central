/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * The contents of this file are subject to the Netscape Public License
 * Version 1.0 (the "NPL"); you may not use this file except in
 * compliance with the NPL.  You may obtain a copy of the NPL at
 * http://www.mozilla.org/NPL/
 *
 * Software distributed under the NPL is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the NPL
 * for the specific language governing rights and limitations under the
 * NPL.
 *
 * The Initial Developer of this code under the NPL is Netscape
 * Communications Corporation.  Portions created by Netscape are
 * Copyright (C) 1998 Netscape Communications Corporation.  All Rights
 * Reserved.
 */

//
// Mike Pinkerton, Netscape Communications
//
// Interfaces for all the things that can go on a toolbar.
//
// CRDFToolbarItem - the base class for things that go on toolbars
// CRDFPushButton - a toolbar button
// CRDFSeparator - a separator bar
// CRDFURLBar - the url bar w/ proxy icon
//

#pragma once

#include "htrdf.h"
#include "CImageIconMixin.h"


//
// class CRDFToolbarItem
//
// The base class for things that go on toolbars. This is a virtual class
// and should never be instantiated by itself.
//
class CRDFToolbarItem : public LView
{
public:

protected:

	HT_Resource HTNode ( ) { return mNode; }
	const HT_Resource HTNode ( ) const { return mNode; }

	virtual void DrawSelf ( ) ;
	
private:

	HT_Resource mNode;
	
		// don't instantiate one of these
	CRDFToolbarItem ( HT_Resource inNode ) ;
	virtual ~CRDFToolbarItem ( ) ;

		// items cannot be passed by value because they exist in 1-to-1 
		// correspondance with UI elements
	CRDFToolbarItem( const CRDFToolbarItem& );				// DON'T IMPLEMENT
	CRDFToolbarItem& operator=( const CRDFToolbarItem& );	// DON'T IMPLEMENT
	
}; // CRDFToolbarItem


//
// class CRDFPushButton
//
// It's a button, it's a slicer, it's a mulcher, it's a ....
//
class CRDFPushButton : public CRDFToolbarItem, public CImageIconMixin
{
public:
	CRDFPushButton ( HT_Resource inNode ) ;
	virtual ~CRDFPushButton ( ) ;

	void SetTrackInside(bool inInside) { mTrackInside = inInside; }
	bool IsTrackInside() const { return mTrackInside; }

protected:

		// computations for drawing text and icon
	virtual void PrepareDrawButton ( ) ;
	virtual void CalcGraphicFrame ( ) ;
	virtual void CalcTitleFrame ( ) ;
	virtual void FinalizeDrawButton ( ) ;
	
		// handle actual drawing
	virtual void DrawSelf ( ) ;
	virtual void DrawButtonContent ( ) ;
	virtual void DrawButtonTitle ( ) ;
	virtual void DrawButtonGraphic ( ) ;
	virtual void DrawSelfDisabled ( ) ;
	virtual void DrawButtonOutline ( ) ;
	virtual void DrawButtonHilited ( ) ;

		// handle drawing icon as an image
	virtual void ImageIsReady ( ) ;
	virtual void DrawStandby ( const Point & inTopLeft, IconTransformType inTransform ) const ;

		// handle rollover feedback
	virtual void MouseEnter ( Point inPortPt, const EventRecord &inMacEvent) ;
	virtual void MouseWithin ( Point inPortPt, const EventRecord &inMacEvent);
	virtual void MouseLeave(void);

	bool IsMouseInFrame ( ) const { return mMouseInFrame; } ;
	
private:

	StRegion mButtonMask;
	Rect mCachedButtonFrame;
	Rect mCachedTitleFrame;
	Rect mCachedGraphicFrame;
	
	ResIDT mTitleTraitsID;
	UInt8 mCurrentMode;
	Int8 mGraphicPadPixels;
	Int8 mTitlePadPixels;
	Int8 mTitleAlignment;
	Int8 mGraphicAlignment;
	Uint8 mOvalWidth, mOvalHeight;

	bool mMouseInFrame;
	bool mTrackInside;
	
		// items cannot be passed by value because they exist in 1-to-1 
		// correspondance with UI elements
	CRDFPushButton( const CRDFPushButton& );				// DON'T IMPLEMENT
	CRDFPushButton& operator=( const CRDFPushButton& );		// DON'T IMPLEMENT
	
}; // CRDFToolbarItem


//
// class CRDFSeparator
//
// Draws a 3d-beveled vertical separator between portions of toolbars.
//
class CRDFSeparator : public CRDFToolbarItem
{
public:
	CRDFSeparator ( HT_Resource inNode ) ;
	virtual ~CRDFSeparator ( ) ;

private:
	// items cannot be passed by value because they exist in 1-to-1 correspondance
	// with UI elements
	CRDFSeparator( const CRDFSeparator& );				// DON'T IMPLEMENT
	CRDFSeparator& operator=( const CRDFSeparator& );	// DON'T IMPLEMENT
	
}; // CRDFToolbarItem


//
// class CRDFURLBar
//
// Our fabled url entry bar with page proxy icon.
//
class CRDFURLBar : public CRDFToolbarItem
{
public:
	CRDFURLBar ( HT_Resource inNode ) ;
	virtual ~CRDFURLBar ( ) ;

private:
	// items cannot be passed by value because they exist in 1-to-1 correspondance
	// with UI elements
	CRDFURLBar( const CRDFURLBar& );				// DON'T IMPLEMENT
	CRDFURLBar& operator=( const CRDFURLBar& );		// DON'T IMPLEMENT
	
}; // CRDFToolbarItem
