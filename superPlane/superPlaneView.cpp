
// superPlaneView.cpp : implementation of the CsuperPlaneView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "superPlane.h"
#endif

#include "superPlaneDoc.h"
#include "superPlaneView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CsuperPlaneView

IMPLEMENT_DYNCREATE(CsuperPlaneView, CView)

BEGIN_MESSAGE_MAP(CsuperPlaneView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CsuperPlaneView construction/destruction

CsuperPlaneView::CsuperPlaneView()
{
	// TODO: add construction code here

}

CsuperPlaneView::~CsuperPlaneView()
{
}

BOOL CsuperPlaneView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CsuperPlaneView drawing

void CsuperPlaneView::OnDraw(CDC* pDC)
{
	CsuperPlaneDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	//TODO:
	
	CDC memoryDC;
	CBitmap memoryBitmap;
	CRect rectTemp;
	GetClientRect(&rectTemp);
	memoryDC.CreateCompatibleDC(pDC);
	memoryBitmap.CreateCompatibleBitmap(pDC, rectTemp.Width(), rectTemp.Height());
	CBitmap *pOldBitmap = memoryDC.SelectObject(&memoryBitmap);
	
	if (gameState == WELCOME)
	{
		welcomeUI(&memoryDC);
	}
	else if (gameState == GUIDE)
	{
		guideUI(&memoryDC);
	}
	else if (gameState == RUNNING1)
	{
		runningUI(&memoryDC);
	}
	else if (gameState == RUNNING2)
	{
		running2UI(&memoryDC);
	}
	else if (gameState == END1 || gameState == END2)
	{
		endUI(&memoryDC);
	}
	
	pDC->BitBlt(0, 0, rectTemp.Width(), rectTemp.Height(), &memoryDC, 0, 0, SRCCOPY); //  show to the screen

	memoryDC.SelectObject(pOldBitmap);
	memoryDC.DeleteDC();
	memoryBitmap.DeleteObject();
}

// CsuperPlaneView printing

BOOL CsuperPlaneView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CsuperPlaneView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CsuperPlaneView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

// CsuperPlaneView diagnostics

#ifdef _DEBUG
void CsuperPlaneView::AssertValid() const
{
	CView::AssertValid();
}

void CsuperPlaneView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CsuperPlaneDoc* CsuperPlaneView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CsuperPlaneDoc)));
	return (CsuperPlaneDoc*)m_pDocument;
}
#endif //_DEBUG

// CsuperPlaneView message handlers

int CsuperPlaneView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ÔÚ´ËÌí¼ÓÄú×¨ÓÃµÄ´´½¨´úÂë

	score = 0;
	superShoot = 3;
	superSuperShoot = 1;
	meBlood = 3;
	bossBlood = 100;
	backgroundY = 0;
	backgroundY2 = 0;
	gameState = WELCOME;
	srand((unsigned)time(NULL));
	beforeGame.Load(L"res/background.bmp");
	running.Load(L"res/running.bmp");
	running2.Load(L"res/running2.bmp");
	gameOver.Load(L"res/background.bmp");
	gameWin.Load(L"res/background.bmp");
	blood.Load(L"res/blood.bmp");
	s1.Load(L"res/superShoot.bmp");
	s2.Load(L"res/superSuperShoot.bmp");

	srand((unsigned)time(NULL));
	setTimers();
	return 0;
}
void CsuperPlaneView::setTimers()
{
	//	SetTimer(1, 500, 0);  //  redraw rectangle
	SetTimer(2, 20, 0);  //  mePlane move
//	SetTimer(3, 1000, 0);  //  ePlane appear
	//	SetTimer(4, 20, 0);  //  meBullet move
	//	SetTimer(5, 20, 0);  //  ePlane move
	SetTimer(6, 1000, 0);  //  ePlane shoot
	//	SetTimer(7, 20, 0);  //  enemyBullet move
	SetTimer(8, 100, 0);  //  background move
	//	SetTimer(9, 100, 0);  //   background2 move
	SetTimer(10, 1000, 0);  //  enemyBoss move
	//	SetTimer(11, 1000, 0);  //  enemyBoss shoot
	SetTimer(12, 15000, 0);
}
void CsuperPlaneView::killTimers()
{
	KillTimer(2);
//	KillTimer(3);
	KillTimer(6);
	KillTimer(8);
	KillTimer(10);
	KillTimer(12);
}
void CsuperPlaneView::removeElements()
{
	vector<MeBullet *>::iterator iter = meBullets.begin();
	for (; iter != meBullets.end();)
	{
		delete (*iter);
		iter = meBullets.erase(iter);
	}
	
	vector<EnemyBullet *>::iterator iter2 = enemyBullets.begin();
	for (; iter2 != enemyBullets.end();)
	{
		delete (*iter2);
		iter2 = enemyBullets.erase(iter2);
	}

	vector<EnemyPlane *>::iterator iter3 = enemyPlanes.begin();
	for (; iter3 != enemyPlanes.end();)
	{
		delete (*iter3);
		iter3 = enemyPlanes.erase(iter3);
	}

	vector<ExtraElement*>::iterator iter4 = extraElements.begin();
	for (; iter4 != extraElements.end();)
	{
		delete (*iter4);
		iter4 = extraElements.erase(iter4);
	}
}

void CsuperPlaneView::welcomeUI(CDC *pDC)
{
	beforeGame.Draw(pDC->m_hDC, 0, 0);

	pDC->SetTextColor(RGB(255, 255, 255));
	pDC->SetBkMode(TRANSPARENT);
	
	CString str;
	CFont *old_font;

	CFont font1;
	font1.CreatePointFont(450, _T("Î¢ÈíÑÅºÚ"));
	old_font = pDC->SelectObject(&font1);       
	str.Format(_T("Super Plane"));
	pDC->TextOutW(150, 100, str);
	
	CFont font2;
	font2.CreatePointFont(100, _T("Î¢ÈíÑÅºÚ"));
	pDC->SelectObject(&font2);
	str.Format(_T("¡ª¡ª Designed by Roy Chan"));
	pDC->TextOutW(400, 225, str);
	
	CFont font3;
	font3.CreatePointFont(150, _T("Î¢ÈíÑÅºÚ"));
	pDC->SelectObject(&font3);
	str.Format(_T("Press the key 'w'"));
	pDC->TextOutW(250, 350, str);
	str.Format(_T("to Watch the Guide"));
	pDC->TextOutW(250, 400, str);
	str.Format(_T("Press the key 's'"));
	pDC->TextOutW(250, 500, str);
	str.Format(_T("to Start the Game"));
	pDC->TextOutW(250, 550, str);
	str.Format(_T("Press the key 'q'"));
	pDC->TextOutW(250, 650, str);
	str.Format(_T("to Quit the Game"));
	pDC->TextOutW(250, 700, str);

	pDC->SetTextColor(RGB(255, 255, 255));
	CFont font4;
	font4.CreateFont(100, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Î¢ÈíÑÅºÚ"));
	pDC->SelectObject(&font4);
	str.Format(_T("["));
	pDC->TextOutW(180, 335, str);
	pDC->TextOutW(180, 485, str);
	pDC->TextOutW(180, 635, str);
	str.Format(_T("]"));
	pDC->TextOutW(500, 335, str);
	pDC->TextOutW(500, 485, str);
	pDC->TextOutW(500, 635, str);

	pDC->SelectObject(old_font);
	return;
}
void CsuperPlaneView::guideUI(CDC *pDC)
{
	beforeGame.Draw(pDC->m_hDC, 0, 0);

	pDC->SetTextColor(RGB(255, 255, 255));
	pDC->SetBkMode(TRANSPARENT);

	CString str;
	CFont *old_font;

	CFont font1;
	font1.CreatePointFont(200, _T("Î¢ÈíÑÅºÚ"));
	old_font = pDC->SelectObject(&font1);
	str.Format(_T("Game Goal:"));
	pDC->TextOutW(100, 100, str);
	str.Format(_T("Game Instruction:"));
	pDC->TextOutW(100, 320, str);
	str.Format(_T("Game Initialization:"));
	pDC->TextOutW(100, 630, str);

	CFont font3;
	font3.CreatePointFont(125, _T("Î¢ÈíÑÅºÚ"));
	pDC->SelectObject(&font3);
	str.Format(_T("Stage 1:  Get at least 100 marks, to meet the boss !"));
	pDC->TextOutW(120, 175, str);
//	str.Format(_T("You should get at least 100 marks, to meet the boss !"));
//	pDC->TextOutW(120, 225, str);
	str.Format(_T("Stage 2:  Decrease boss blood to 0 !"));
	pDC->TextOutW(120, 225, str);
//	str.Format(_T("You should decrease boss blood to 0 !"));
//	pDC->TextOutW(120, 325, str);
	str.Format(_T("Up: 'w'"));
	pDC->TextOutW(120, 395, str);
	str.Format(_T("Down: 's'"));
	pDC->TextOutW(120, 445, str);
	str.Format(_T("Left: 'a'"));
	pDC->TextOutW(120, 495, str);
	str.Format(_T("Right: 'd'"));
	pDC->TextOutW(120, 545, str);
	str.Format(_T("Shoot: 'j'"));
	pDC->TextOutW(300, 395, str);
	str.Format(_T("SuperShoot: 'k'"));
	pDC->TextOutW(480, 395, str);
	str.Format(_T("SuperSuperShoot: 'l'"));
	pDC->TextOutW(300, 445, str);

	str.Format(_T("Pause/Continue: 'p'"));
	pDC->TextOutW(300, 495, str);
	str.Format(_T("Quit: 'q'"));
	pDC->TextOutW(300, 545, str);
	str.Format(_T("At the beginning, your blood is 3,"));
	pDC->TextOutW(120, 705, str);
	str.Format(_T("your superShoot chances left are 3,"));
	pDC->TextOutW(120, 755, str);
	str.Format(_T("and your superSuperShoot chances left are 1."));
	pDC->TextOutW(120, 805, str);

	pDC->SetTextColor(RGB(255, 255, 255));
	CFont font2;
	font2.CreateFont(40, 0, 0, 0, FW_HEAVY, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Î¢ÈíÑÅºÚ"));
	pDC->SelectObject(&font2);
	str.Format(_T("<Press 'b' Back>"));
	pDC->TextOutW(425, 870, str);
	
	pDC->SelectObject(old_font);

	blood.Draw(pDC->m_hDC, 600, 700);
	s1.Draw(pDC->m_hDC, 600, 750);
	s2.Draw(pDC->m_hDC, 600, 800);

	return;
}
void CsuperPlaneView::runningUI(CDC *pDC)
{
	running.Draw(pDC->m_hDC, 0, backgroundY);
	running.Draw(pDC->m_hDC, 0, backgroundY - running.GetHeight());
//	backgroundY += 1;
	if (backgroundY - running.GetHeight() >= 0)
		backgroundY = 0;
	
	mePlane.draw(pDC);
	for (unsigned int i = 0; i < meBullets.size(); i++)
		meBullets[i]->draw(pDC);
	for (unsigned int i = 0; i < enemyPlanes.size(); i++)
		enemyPlanes[i]->draw(pDC);
	for (unsigned int i = 0; i < enemyBullets.size(); i++)
		enemyBullets[i]->draw(pDC);
	for (unsigned int i = 0; i < extraElements.size(); i++)
		extraElements[i]->draw(pDC);

	pDC->SetTextColor(RGB(255, 255, 255));
	pDC->SetBkMode(TRANSPARENT);
	CString str;
	CFont *old_font;

	CFont font1;
	font1.CreateFont(32, 0, 0, 0, FW_HEAVY, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Î¢ÈíÑÅºÚ"));

//	font1.CreatePointFont(150, _T("Î¢ÈíÑÅºÚ"));
	old_font = pDC->SelectObject(&font1);
	str.Format(_T("Score:"));
	pDC->TextOutW(5, 0, str);
	str.Format(_T("%d"), score);
	pDC->TextOutW(85, 0, str);
	str.Format(_T("My Blood:"));
	pDC->TextOutW(5, 850, str);
	str.Format(_T("%d"), meBlood);
	pDC->TextOutW(135, 850, str);
	str.Format(_T("SuperShoot:"));
	pDC->TextOutW(5, 880, str);
	str.Format(_T("%d"), superShoot);
	pDC->TextOutW(160, 880, str);
	str.Format(_T("SuperSuperShoot:"));
	pDC->TextOutW(5, 910, str);
	str.Format(_T("%d"), superSuperShoot);
	pDC->TextOutW(230, 910, str);

	pDC->SelectObject(old_font);
}
void CsuperPlaneView::running2UI(CDC *pDC)
{
	running2.Draw(pDC->m_hDC, 0, backgroundY2);
	running2.Draw(pDC->m_hDC, 0, backgroundY2 - running2.GetHeight());
	//	backgroundY += 1;
	if (backgroundY2 - running2.GetHeight() >= 0)
		backgroundY2 = 0;

	mePlane.draw(pDC);
	for (unsigned int i = 0; i < meBullets.size(); i++)
		meBullets[i]->draw(pDC);
	for (unsigned int i = 0; i < enemyBullets.size(); i++)
		enemyBullets[i]->draw(pDC);
	enemyBoss.draw(pDC);

	pDC->SetTextColor(RGB(255, 255, 255));
	pDC->SetBkMode(TRANSPARENT);
	CString str;
	CFont *old_font;

	CFont font1;
	font1.CreateFont(32, 0, 0, 0, FW_HEAVY, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Î¢ÈíÑÅºÚ"));

	//	font1.CreatePointFont(150, _T("Î¢ÈíÑÅºÚ"));
	old_font = pDC->SelectObject(&font1);
	str.Format(_T("Boss Blood:"));
	pDC->TextOutW(5, 0, str);
	str.Format(_T("%d"), bossBlood);
	pDC->TextOutW(152, 0, str);
	str.Format(_T("My Blood:"));
	pDC->TextOutW(5, 850, str);
	str.Format(_T("%d"), meBlood);
	pDC->TextOutW(135, 850, str);
	str.Format(_T("SuperShoot:"));
	pDC->TextOutW(5, 880, str);
	str.Format(_T("%d"), superShoot);
	pDC->TextOutW(160, 880, str);
	str.Format(_T("SuperSuperShoot:"));
	pDC->TextOutW(5, 910, str);
	str.Format(_T("%d"), superSuperShoot);
	pDC->TextOutW(230, 910, str);

	pDC->SelectObject(old_font);
}
void CsuperPlaneView::endUI(CDC *pDC)
{
	if (gameState == END1)
	{
		gameWin.Draw(pDC->m_hDC, 0, 0);

		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkMode(TRANSPARENT);
		CString str;
		CFont *old_font;

		CFont font1;
		font1.CreateFont(120, 0, 0, 0, FW_HEAVY, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Î¢ÈíÑÅºÚ"));

		//	font1.CreatePointFont(150, _T("Î¢ÈíÑÅºÚ"));
		old_font = pDC->SelectObject(&font1);
		str.Format(_T("GAME"));
		pDC->TextOutW(210, 180, str);
		str.Format(_T("WIN"));
		pDC->TextOutW(240, 300, str);

		CFont font3;
		font3.CreatePointFont(150, _T("Î¢ÈíÑÅºÚ"));
		pDC->SelectObject(&font3);

		str.Format(_T("Press the key 'r'"));
		pDC->TextOutW(250, 500, str);
		str.Format(_T("to Restart the Game"));
		pDC->TextOutW(250, 550, str);

		str.Format(_T("Press the key 'q'"));
		pDC->TextOutW(250, 650, str);
		str.Format(_T("to Quit the Game"));
		pDC->TextOutW(250, 700, str);


		pDC->SetTextColor(RGB(255, 255, 255));
		CFont font4;
		font4.CreateFont(100, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Î¢ÈíÑÅºÚ"));
		pDC->SelectObject(&font4);
		str.Format(_T("["));
//		pDC->TextOutW(180, 335, str);
		pDC->TextOutW(180, 485, str);
		pDC->TextOutW(180, 635, str);
		str.Format(_T("]"));
//		pDC->TextOutW(500, 335, str);
		pDC->TextOutW(500, 485, str);
		pDC->TextOutW(500, 635, str);


		pDC->SelectObject(old_font);
	}
	if (gameState == END2)
	{
		gameOver.Draw(pDC->m_hDC, 0, 0);

		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkMode(TRANSPARENT);
		CString str;
		CFont *old_font;

		CFont font1;
		font1.CreateFont(120, 0, 0, 0, FW_HEAVY, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Î¢ÈíÑÅºÚ"));

		//	font1.CreatePointFont(150, _T("Î¢ÈíÑÅºÚ"));
		old_font = pDC->SelectObject(&font1);
		str.Format(_T("GAME"));
		pDC->TextOutW(210, 180, str);
		str.Format(_T("OVER"));
		pDC->TextOutW(225, 300, str);

		CFont font3;
		font3.CreatePointFont(150, _T("Î¢ÈíÑÅºÚ"));
		pDC->SelectObject(&font3);

		str.Format(_T("Press the key 'r'"));
		pDC->TextOutW(250, 500, str);
		str.Format(_T("to Restart the Game"));
		pDC->TextOutW(250, 550, str);

		str.Format(_T("Press the key 'q'"));
		pDC->TextOutW(250, 650, str);
		str.Format(_T("to Quit the Game"));
		pDC->TextOutW(250, 700, str);
		
		pDC->SetTextColor(RGB(255, 255, 255));
		CFont font4;
		font4.CreateFont(100, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Î¢ÈíÑÅºÚ"));
		pDC->SelectObject(&font4);
		str.Format(_T("["));
		//		pDC->TextOutW(180, 335, str);
		pDC->TextOutW(180, 485, str);
		pDC->TextOutW(180, 635, str);
		str.Format(_T("]"));
		//		pDC->TextOutW(500, 335, str);
		pDC->TextOutW(500, 485, str);
		pDC->TextOutW(500, 635, str);


		pDC->SelectObject(old_font);
	}

}

void CsuperPlaneView::mBulletMove()
{
	vector<MeBullet *>::iterator iter = meBullets.begin();
	for (int flag; iter != meBullets.end();)
	{
		bool disappear = 0;
		(*iter)->move(disappear);
		if (disappear)
		{
			delete (*iter);
			iter = meBullets.erase(iter);
		}
		else
		{
			flag = 0;
			if (gameState == RUNNING1)
			{
				vector<EnemyPlane*>::iterator iter2 = enemyPlanes.begin();
				for (; iter2 != enemyPlanes.end(); iter2++)
				{
					if (((*iter)->getX() >= (*iter2)->getX() && (*iter)->getX() <= (*iter2)->getX() + (*iter2)->getIW() &&
						(*iter)->getY() >= (*iter2)->getY() && (*iter)->getY() <= (*iter2)->getY() + (*iter2)->getIH()) ||
						((*iter)->getX() + (*iter)->getIW() >= (*iter2)->getX() && (*iter)->getX() + (*iter)->getIW() <= (*iter2)->getX() + (*iter2)->getIW() &&
						(*iter)->getY() + (*iter)->getIH() >= (*iter2)->getY() && (*iter)->getY() + (*iter)->getIH() <= (*iter2)->getY() + (*iter2)->getIH()) ||
						((*iter)->getX() + (*iter)->getIW() >= (*iter2)->getX() && (*iter)->getX() + (*iter)->getIW() <= (*iter2)->getX() + (*iter2)->getIW() &&
						(*iter)->getY() >= (*iter2)->getY() && (*iter)->getY() <= (*iter2)->getY() + (*iter2)->getIH()) ||
						((*iter)->getX() >= (*iter2)->getX() && (*iter)->getX() <= (*iter2)->getX() + (*iter2)->getIW() &&
						(*iter)->getY() + (*iter)->getIH() >= (*iter2)->getY() && (*iter)->getY() + (*iter)->getIH() <= (*iter2)->getY() + (*iter2)->getIH()))
					{
						delete (*iter2);
						iter2 = enemyPlanes.erase(iter2);
						score++;
						delete (*iter);
						iter = meBullets.erase(iter);
						flag = 1;
						if (score >= 100)
						{
							removeElements();
							gameState = RUNNING2;
							return;
						}
						break;
					}
				}
			}
			else if (gameState == RUNNING2)
			{
				if (((*iter)->getX() >= enemyBoss.getX() && (*iter)->getX() <= enemyBoss.getX() + enemyBoss.getIW() &&
					(*iter)->getY() >= enemyBoss.getY() && (*iter)->getY() <= enemyBoss.getY() + enemyBoss.getIH()) || 
					((*iter)->getX() + (*iter)->getIW() >= enemyBoss.getX() && (*iter)->getX() + (*iter)->getIW() <= enemyBoss.getX() + enemyBoss.getIW() &&
					(*iter)->getY() + (*iter)->getIH() >= enemyBoss.getY() && (*iter)->getY() + (*iter)->getIH() <= enemyBoss.getY() + enemyBoss.getIH()) || 
					((*iter)->getX() + (*iter)->getIW() >= enemyBoss.getX() && (*iter)->getX() + (*iter)->getIW() <= enemyBoss.getX() + enemyBoss.getIW() &&
					(*iter)->getY() >= enemyBoss.getY() && (*iter)->getY() <= enemyBoss.getY() + enemyBoss.getIH()) || 
					((*iter)->getX() >= enemyBoss.getX() && (*iter)->getX() <= enemyBoss.getX() + enemyBoss.getIW() &&
					(*iter)->getY() + (*iter)->getIH() >= enemyBoss.getY() && (*iter)->getY() + (*iter)->getIH() <= enemyBoss.getY() + enemyBoss.getIH()))
				{
					bossBlood--;
					delete (*iter);
					iter = meBullets.erase(iter);
					flag = 1;
					if (bossBlood <= 0)
					{
						removeElements();
						killTimers();
						gameState = END1;
						return;
					}
				}
			}
			if (!flag)
				iter++;
		}
	}
}
void CsuperPlaneView::extraElementAppear()
{
	ExtraElement *extraElement = new ExtraElement();
	this->extraElements.push_back(extraElement);
}
void CsuperPlaneView::extraElementMove()
{
	vector< ExtraElement*>::iterator iter = extraElements.begin();
	for (int flag; iter != extraElements.end();)
	{
		bool disappear = 0;
		(*iter)->move(disappear);
		if (disappear)
		{
			delete (*iter);
			iter = extraElements.erase(iter);
		}
		else
		{
			flag = 0;
			if (((*iter)->getX() >= mePlane.getX() && (*iter)->getX() <= mePlane.getX() + mePlane.getIW() &&
				(*iter)->getY() >= mePlane.getY() && (*iter)->getY() <= mePlane.getY() + mePlane.getIH()) ||
				((*iter)->getX() + (*iter)->getIW() >= mePlane.getX() && (*iter)->getX() + (*iter)->getIW() <= mePlane.getX() + mePlane.getIW() &&
				(*iter)->getY() + (*iter)->getIH() >= mePlane.getY() && (*iter)->getY() + (*iter)->getIH() <= mePlane.getY() + mePlane.getIH()) ||
				((*iter)->getX() + (*iter)->getIW() >= mePlane.getX() && (*iter)->getX() + (*iter)->getIW() <= mePlane.getX() + mePlane.getIW() &&
				(*iter)->getY() >= mePlane.getY() && (*iter)->getY() <= mePlane.getY() + mePlane.getIH()) ||
				((*iter)->getX() >= mePlane.getX() && (*iter)->getX() <= mePlane.getX() + mePlane.getIW() &&
				(*iter)->getY() + (*iter)->getIH() >= mePlane.getY() && (*iter)->getY() + (*iter)->getIH() <= mePlane.getY() + mePlane.getIH()))
			{
				int type = (*iter)->extraElementType;
				delete (*iter);
				iter = extraElements.erase(iter);
				if (type == 1)
					meBlood = (meBlood >= 3) ? 3 : (meBlood + 1);
				else if (type == 2)
					superShoot = (superShoot >= 3) ? 3 : (superShoot + 1);
				else if (type == 3)
					superSuperShoot = (superSuperShoot >= 1) ? 1 : (superSuperShoot + 1);

				/*
				meBlood -= 1;
				if (meBlood <= 0)
				{
					removeElements();
					killTimers();
					gameState = END2;
					return;
				}
				*/
				flag = 1;
			}
			if (!flag)
				iter++;
		}
	}
}

void CsuperPlaneView::ePlaneAppear()
{
	EnemyPlane *ePlane = new EnemyPlane();
	this->enemyPlanes.push_back(ePlane);
}


void CsuperPlaneView::ePlaneMove()
{
	vector< EnemyPlane*>::iterator iter = enemyPlanes.begin();
	for (int flag; iter != enemyPlanes.end();)
	{
		bool disappear = 0;
		(*iter)->move(disappear);
		if (disappear)
		{
			delete (*iter);
			iter = enemyPlanes.erase(iter);
		}
		else
		{
			flag = 0;
			if (((*iter)->getX() >= mePlane.getX() && (*iter)->getX() <= mePlane.getX() + mePlane.getIW() &&
				(*iter)->getY() >= mePlane.getY() && (*iter)->getY() <= mePlane.getY() + mePlane.getIH()) ||
				((*iter)->getX() + (*iter)->getIW() >= mePlane.getX() && (*iter)->getX() + (*iter)->getIW() <= mePlane.getX() + mePlane.getIW() &&
				(*iter)->getY() + (*iter)->getIH() >= mePlane.getY() && (*iter)->getY() + (*iter)->getIH() <= mePlane.getY() + mePlane.getIH()) ||
				((*iter)->getX() + (*iter)->getIW() >= mePlane.getX() && (*iter)->getX() + (*iter)->getIW() <= mePlane.getX() + mePlane.getIW() &&
				(*iter)->getY() >= mePlane.getY() && (*iter)->getY() <= mePlane.getY() + mePlane.getIH()) ||
				((*iter)->getX() >= mePlane.getX() && (*iter)->getX() <= mePlane.getX() + mePlane.getIW() &&
				(*iter)->getY() + (*iter)->getIH() >= mePlane.getY() && (*iter)->getY() + (*iter)->getIH() <= mePlane.getY() + mePlane.getIH()))
			{
				delete (*iter);
				iter = enemyPlanes.erase(iter);
				meBlood -= 1;
				if (meBlood <= 0)
				{
					removeElements();
					killTimers();
					gameState = END2;
					return;
				}
				flag = 1;
			}
			if (!flag)
				iter++;
		}
	}
}
void CsuperPlaneView::ePlaneShoot()
{
	unsigned int i = 0;
	for (; i < enemyPlanes.size(); i += 2)
	{
		enemyPlanes[i]->shoot();
	}
}
void CsuperPlaneView::eBulletMove()
{
	vector<EnemyBullet *>::iterator iter = enemyBullets.begin();
	for (int flag; iter != enemyBullets.end();)
	{
		bool disappear = 0;
		(*iter)->move(disappear);
		if (disappear)
		{
			delete (*iter);
			iter = enemyBullets.erase(iter);
		}
		else
		{
			flag = 0;
			if (((*iter)->getX() >= mePlane.getX() && (*iter)->getX() <= mePlane.getX() + mePlane.getIW() &&
				(*iter)->getY() >= mePlane.getY() && (*iter)->getY() <= mePlane.getY() + mePlane.getIH()) ||
				((*iter)->getX() + (*iter)->getIW() >= mePlane.getX() && (*iter)->getX() + (*iter)->getIW() <= mePlane.getX() + mePlane.getIW() &&
				(*iter)->getY() + (*iter)->getIH() >= mePlane.getY() && (*iter)->getY() + (*iter)->getIH() <= mePlane.getY() + mePlane.getIH()) ||
				((*iter)->getX() + (*iter)->getIW() >= mePlane.getX() && (*iter)->getX() + (*iter)->getIW() <= mePlane.getX() + mePlane.getIW() &&
				(*iter)->getY() >= mePlane.getY() && (*iter)->getY() <= mePlane.getY() + mePlane.getIH()) ||
				((*iter)->getX() >= mePlane.getX() && (*iter)->getX() <= mePlane.getX() + mePlane.getIW() &&
				(*iter)->getY() + (*iter)->getIH() >= mePlane.getY() && (*iter)->getY() + (*iter)->getIH() <= mePlane.getY() + mePlane.getIH()))
			{
				delete (*iter);
				iter = enemyBullets.erase(iter);
				meBlood -= 1;
				if (meBlood <= 0)
				{
					removeElements();
					killTimers();
					gameState = END2;
					return;
				}
				flag = 1;
			}
			if (!flag)
				iter++;
		}
	}
}
void CsuperPlaneView::mPlaneMove()
{
	mePlane.move();
	if ((mePlane.getX() >= enemyBoss.getX() && mePlane.getX() <= enemyBoss.getX() + enemyBoss.getIW() &&
		mePlane.getY() >= enemyBoss.getY() && mePlane.getY() <= enemyBoss.getY() + enemyBoss.getIH()) ||
		(mePlane.getX() + mePlane.getIW() >= enemyBoss.getX() && mePlane.getX() + mePlane.getIW() <= enemyBoss.getX() + enemyBoss.getIW() &&
		mePlane.getY() + mePlane.getIH() >= enemyBoss.getY() && mePlane.getY() + mePlane.getIH() <= enemyBoss.getY() + enemyBoss.getIH()) ||
		(mePlane.getX() + mePlane.getIW() >= enemyBoss.getX() && mePlane.getX() + mePlane.getIW() <= enemyBoss.getX() + enemyBoss.getIW() &&
		mePlane.getY() >= enemyBoss.getY() && mePlane.getY() <= enemyBoss.getY() + enemyBoss.getIH()) ||
		(mePlane.getX() >= enemyBoss.getX() && mePlane.getX() <= enemyBoss.getX() + enemyBoss.getIW() &&
		mePlane.getY() + mePlane.getIH() >= enemyBoss.getY() && mePlane.getY() + mePlane.getIH() <= enemyBoss.getY() + enemyBoss.getIH()))
	{
		meBlood -= 1;
		if (meBlood <= 0)
		{
			removeElements();
			killTimers();
			gameState = END2;
		}
	}
}

void CsuperPlaneView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  ÔÚ´ËÌí¼ÓÏûÏ¢´¦Àí³ÌÐò´úÂëºÍ/»òµ÷ÓÃÄ¬ÈÏÖµ
	if (gameState == RUNNING1)
	{
		if (nIDEvent == 2)
		{
			mePlane.move();
			mBulletMove();
			ePlaneMove();
			eBulletMove();
			extraElementMove();
		}
/*		else if (nIDEvent == 3)
		{
			ePlaneAppear();
		}
*//*	else if (nIDEvent == 4)
		{
			mBulletMove();
		}
		else if (nIDEvent == 5)
		{
			ePlaneMove();
		}
*/
		else if (nIDEvent == 6)
		{
			ePlaneShoot();
			ePlaneAppear();
		}
/*
		else if (nIDEvent == 7)
		{
			eBulletMove();
		}
*/
		else if (nIDEvent == 8)
		{
			backgroundY += 1;
		}
		else if (nIDEvent == 12)
		{
			extraElementAppear();
		}
		Invalidate(FALSE);
		UpdateWindow();
	}
	else if (gameState == RUNNING2)
	{
		if (nIDEvent == 2)
		{
			mPlaneMove();
			mBulletMove();
			eBulletMove();
		}
/*		else if (nIDEvent == 4)
		{
			mBulletMove();
		}
*/		else if (nIDEvent == 8)
		{
			backgroundY2 += 1;
		}
		else if (nIDEvent == 10)
		{
			enemyBoss.move();
			enemyBoss.shoot();
		}
//		else if (nIDEvent == 11)
//		{
//			enemyBoss.shoot();
//		}
/*		else if (nIDEvent == 7)
		{
			eBulletMove();
		}
*/		Invalidate(FALSE);
		UpdateWindow();
	}
		

//	InvalidateRect(NULL, FALSE);//TRUE means removing and redrawing.
	CView::OnTimer(nIDEvent);
}
void CsuperPlaneView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  ÔÚ´ËÌí¼ÓÏûÏ¢´¦Àí³ÌÐò´úÂëºÍ/»òµ÷ÓÃÄ¬ÈÏÖµ
	if (gameState == WELCOME)
	{
		if (nChar == 's' || nChar == 'S')
			gameState = RUNNING1;
		else if (nChar == 'w' || nChar == 'W')
			gameState = GUIDE;
		else if (nChar == 'q' || nChar == 'Q')
		{
			exit(0);
		}
	}
	else if (gameState == GUIDE)
	{
		if (nChar == 'b' || nChar == 'B')
			gameState = WELCOME;
	}
	else if (gameState == RUNNING1 || gameState == RUNNING2)
	{
		if (nChar == 'k' || nChar == 'K')
		{
			if (superShoot > 0)
			{
				mePlane.superShoot();
				superShoot--;
			}
		}
		else if (nChar == 'l' || nChar == 'L')
		{
			if (superSuperShoot > 0)
			{
				mePlane.superSuperShoot();
				superSuperShoot--;
			}
		}
		else if (nChar == 'j' || nChar == 'J')
			mePlane.shoot();
		else if (nChar == 'p' || nChar == 'P')
		{
			if (gameState == RUNNING1)
			{
				gameState = PAUSE1;
				killTimers();
			}
			else if (gameState == RUNNING2)
			{
				gameState = PAUSE2;
				killTimers();
			}
		}
		else if (nChar == 'q' || nChar == 'Q')
		{
			removeElements();
			killTimers();
			gameState = END2;
		}
	}
	else if (gameState == PAUSE1)
	{
		if (nChar == 'p' || nChar == 'P')
		{
			gameState = RUNNING1;
			setTimers();
		}
	}
	else if (gameState == PAUSE2)
	{
		if (nChar == 'p' || nChar == 'P')
		{
			gameState = RUNNING2;
			setTimers();
		}
	}
	
	else if (gameState == END1 || gameState == END2)
	{
		if (nChar == 'q' || nChar == 'Q')
		{
			exit(0);
		}
		else if (nChar == 'r' || nChar == 'R')
		{
			score = 0;
			superShoot = 3;
			superSuperShoot = 1;
			meBlood = 3;
			bossBlood = 100;
			backgroundY = 0;
			backgroundY2 = 0;
			mePlane.setPosition((mePlane.getWW() - mePlane.getIW()) / 2, mePlane.getWH() - mePlane.getIH());
			enemyBoss.setPosition(enemyBoss.getWW() / 3, 0 - enemyBoss.getIH());
			setTimers();
			gameState = RUNNING1;
		}
	}
	if (gameState != PAUSE1 && gameState != PAUSE2)
	{
		Invalidate(FALSE);
		UpdateWindow();
//		InvalidateRect(NULL, FALSE);//TRUE means removing and redrawing.
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
