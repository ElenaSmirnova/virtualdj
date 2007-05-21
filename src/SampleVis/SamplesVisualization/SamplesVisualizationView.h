// SamplesVisualizationView.h : interface of the CSamplesVisualizationView class
//


#pragma once


class CSamplesVisualizationView : public CView
{
protected: // create from serialization only
	CSamplesVisualizationView();
	DECLARE_DYNCREATE(CSamplesVisualizationView)

// Attributes
public:
	CSamplesVisualizationDoc* GetDocument() const;

// Operations
public:

// Overrides
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* PInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* PInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* PInfo);

// Implementation
public:
	virtual ~CSamplesVisualizationView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNullfilter();
};

#ifndef _DEBUG  // debug version in SamplesVisualizationView.cpp
inline CSamplesVisualizationDoc* CSamplesVisualizationView::GetDocument() const
   { return reinterpret_cast<CSamplesVisualizationDoc*>(m_pDocument); }
#endif

