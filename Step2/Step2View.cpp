
// Step2View.cpp : implementation of the CStep2View class
//

#include "pch.h"

#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Step2.h"
#endif

#include "Step2Doc.h"
#include "Step2View.h"
#include "mmsystem.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStep2View

IMPLEMENT_DYNCREATE(CStep2View, CView)

BEGIN_MESSAGE_MAP(CStep2View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	
	
	ON_WM_TIMER()
	ON_COMMAND(ID_RESET_RESE, &CStep2View::OnResetRese)
END_MESSAGE_MAP()

// CStep2View construction/destruction

CStep2View::CStep2View() noexcept
{
	
	m_auditorium.LoadBitmap(IDB_AUDITORIUM);
	BITMAP map;

	m_auditorium.GetBitmap(&map);
	
	
	m_firstdraw = true;
	m_timer = 0;// TODO: add construction code here
	m_state = Start;      // our initial state

}

CStep2View::~CStep2View()
{
}

BOOL CStep2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CStep2View drawing

void CStep2View::OnDraw(CDC* pDC)
{
	if (m_firstdraw) 
	{
		m_firstdraw = false;
		OnFirstDraw();
	}
	CStep2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CPaintDC dc(this);
	CDC bmpDC;
	
	switch (m_state)
	{
	case Start:
	case Applause:

		break;
	case MyName:
		
		break;


	case Auditorium:
		// Define the coordinates for the square
		
		
		// Draw the square using four lines
		pDC->MoveTo(x1, y1);
		pDC->LineTo(250, 100);              // Top side
		pDC->LineTo(250, 200);       // Right side
		pDC->LineTo(100, 200);              // Bottom side
		pDC->LineTo(100, 100);
		
		pDC->LineTo(100, 150);
		pDC->TextOut(150, 140, L"My Step 2 by Mannan Dhillon");
		break;
		
	case Caption:
		bmpDC.CreateCompatibleDC(pDC);
		bmpDC.SelectObject(&m_auditorium);
		pDC->BitBlt(0, 0, 640, 480, &bmpDC, 0, 0, SRCCOPY);
		break;
	case Bicycle:
		bmpDC.CreateCompatibleDC(pDC);
		bmpDC.SelectObject(&m_auditorium);
		pDC->BitBlt(0, 0, 640, 480, &bmpDC, 0, 0, SRCCOPY);
		pDC->TextOut(200, 140, L"Mannan");
		break;



		

	default:
		// Display nothing
		break;
	}
}


// CStep2View printing

BOOL CStep2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CStep2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CStep2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CStep2View diagnostics

#ifdef _DEBUG
void CStep2View::AssertValid() const
{
	CView::AssertValid();
}

void CStep2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CStep2Doc* CStep2View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStep2Doc)));
	return (CStep2Doc*)m_pDocument;
}
#endif //_DEBUG

void CStep2View::OnFirstDraw()
{
	m_starttime = timeGetTime();
	OnTimer(1);
}


void CStep2View::OnTimer(UINT_PTR nIDEvent)
{
	// Kill any existing timer
	if (m_timer)
	{
		KillTimer(m_timer);
		m_timer = 0;
	}

	// Force redraw whenever the timer fires
	Invalidate();

	// This will keep track of the relative time
	// to the next state.
	DWORD nexteventtime = 0;

	switch (m_state)
	{
	case Start:
		// If we are in the state state, just move directly
		// to the Smith state
	
		
		m_state = Applause;
		nexteventtime = 5000;
		break;

	case Applause:
		// The Smith state is ending, we are changing to the HearThat state
		PlaySound(MAKEINTRESOURCE(IDR_APPLAUSE), AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
		m_state = MyName;

		// What we do at the end of state Smith, entering state HearThat
		
		nexteventtime = 8000;
		break;
	case MyName:
		m_state = Auditorium;
		nexteventtime = 12000;
		break;
	case Auditorium:
		m_state = Caption;
		nexteventtime = 15000;
		break;
	case Caption:
		m_state = Bicycle;
		nexteventtime = 28000;
		PlaySound(MAKEINTRESOURCE(IDR_BICYCLE), AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
		break;
	case Bicycle:
		m_state = Done;
		
		break;



	case Done:
		break;
	}
	

	// Only reset the timer if we are not done
	if (m_state != Done)
	{
		DWORD currenttime = timeGetTime();
		DWORD nexttime = m_starttime + nexteventtime;
		DWORD tillnext = nexttime > currenttime ? nexttime - currenttime : 0;

		m_timer = SetTimer(1, tillnext, NULL);
	}
}


void CStep2View::OnResetRese()
{
	m_firstdraw = true;
	m_timer = 0;
	m_state = Start;// TODO: Add your command handler code here
	
}
