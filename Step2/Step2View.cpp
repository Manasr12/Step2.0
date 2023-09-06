
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
	
	ON_COMMAND(ID_STEPSTUFF_PLAY, &CStep2View::OnStepstuffPlay)
END_MESSAGE_MAP()

// CStep2View construction/destruction

CStep2View::CStep2View() noexcept
{
	m_splash.LoadBitmap(IDB_SPLASH);

	BITMAP map;
	m_splash.GetBitmap(&map);
	m_splashwid = map.bmWidth;
	m_splashhit = map.bmHeight;// TODO: add construction code here

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
	CStep2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CPaintDC dc(this);
	CDC bmpDC;

	bmpDC.CreateCompatibleDC(pDC);
	bmpDC.SelectObject(&m_splash);
	pDC->BitBlt(0, 0, m_splashwid, m_splashhit, &bmpDC, 0, 0, SRCCOPY);
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


// CStep2View message handlers


void CStep2View::OnPlaysmithPlaysmith()
{
	
}


void CStep2View::OnStepstuffPlay()
{
	PlaySound(MAKEINTRESOURCE(IDR_HEARTHAT), AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);// TODO: Add your command handler code here
}
