
// Step2View.h : interface of the CStep2View class
//

#pragma once


class CStep2View : public CView
{
protected: // create from serialization only
	CStep2View() noexcept;
	DECLARE_DYNCREATE(CStep2View)

// Attributes
public:
	CStep2Doc* GetDocument() const;

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
	virtual ~CStep2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
private:
	CBitmap m_splash;
	int m_splashwid;
	int m_splashhit;
	UINT_PTR m_timer;
	bool m_firstdraw;
	
	CBitmap m_smith;
	CBitmap m_chill;
public:
	afx_msg void OnPlaysmithPlaysmith();
	afx_msg void OnStepstuffPlay();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void OnFirstDraw();
};

#ifndef _DEBUG  // debug version in Step2View.cpp
inline CStep2Doc* CStep2View::GetDocument() const
   { return reinterpret_cast<CStep2Doc*>(m_pDocument); }
#endif

