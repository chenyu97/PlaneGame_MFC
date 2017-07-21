
// superPlaneView.h : interface of the CsuperPlaneView class
//

#pragma once
#include "MePlane.h"
#include "MeBullet.h"
#include "EnemyPlane.h"
#include "EnemyBoss.h"
#include "ExtraElement.h"

enum GAMESTATE{ WELCOME, GUIDE, RUNNING1, RUNNING2, PAUSE1, PAUSE2, END1,END2};

class CsuperPlaneView : public CView
{
protected: // create from serialization only
	CsuperPlaneView();
	DECLARE_DYNCREATE(CsuperPlaneView)

// Attributes
public:
	CsuperPlaneDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CsuperPlaneView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

private:
	CImage beforeGame;
	CImage running;
	CImage running2;
	CImage gameOver;
	CImage gameWin;
	CImage blood;
	CImage s1;
	CImage s2;
	
	MePlane mePlane;
	EnemyBoss enemyBoss;
	int backgroundY;
	int backgroundY2;
	int meBlood;
	int bossBlood;
	int superShoot;
	int superSuperShoot;
public:
	GAMESTATE gameState;
	int score;
	vector <ExtraElement*> extraElements;
	vector <EnemyPlane*> enemyPlanes;
	vector<MeBullet *> meBullets;
	vector<EnemyBullet *> enemyBullets;

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	void welcomeUI(CDC *pDC);
	void guideUI(CDC *pDC);
	void runningUI(CDC *pDC);
	void running2UI(CDC *pDC);
	void endUI(CDC *pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void mBulletMove();
	void ePlaneAppear();
	void ePlaneMove();
	void ePlaneShoot();
	void eBulletMove();
	void removeElements();
	void extraElementAppear();
	void extraElementMove();
	void mPlaneMove();
	void killTimers();
	void setTimers();
};

#ifndef _DEBUG  // debug version in superPlaneView.cpp
inline CsuperPlaneDoc* CsuperPlaneView::GetDocument() const
   { return reinterpret_cast<CsuperPlaneDoc*>(m_pDocument); }
#endif

