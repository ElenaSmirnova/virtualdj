// SamplesVisualizationView.cpp : implementation of the CSamplesVisualizationView class
//

#include "stdafx.h"
#include "SamplesVisualization.h"

#include "SamplesVisualizationDoc.h"
#include "SamplesVisualizationView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSamplesVisualizationView

IMPLEMENT_DYNCREATE(CSamplesVisualizationView, CView)

BEGIN_MESSAGE_MAP(CSamplesVisualizationView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_COMMAND(ID_NULLFilter, &CSamplesVisualizationView::OnNullfilter)
END_MESSAGE_MAP()

// CSamplesVisualizationView construction/destruction

CSamplesVisualizationView::CSamplesVisualizationView()
{
	// TODO: add construction code here

}

CSamplesVisualizationView::~CSamplesVisualizationView()
{
}

BOOL CSamplesVisualizationView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CSamplesVisualizationView drawing

void CSamplesVisualizationView::OnDraw(CDC* pDC)
{
	CSamplesVisualizationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	if (pDoc->pEqualiser)
	{

	
		CBrush* pBorderBrush=new CBrush;
		CBrush* PInnerBrush=new CBrush;
			
		COLORREF crBorderClr=RGB(0,0,0);
		COLORREF crInnerClr=RGB(240,230,240);
	

		pBorderBrush->CreateSolidBrush(crBorderClr);
		PInnerBrush->CreateSolidBrush(crInnerClr);
	
	
		CRect rectBorder;
		rectBorder.bottom=305;
		rectBorder.left=5;
		rectBorder.right=645;
		rectBorder.top=5;

		pDC->FillRect(rectBorder,PInnerBrush);
		pDC->FrameRect(rectBorder,pBorderBrush);
/*
		rectBorder.bottom=620;
		rectBorder.top=320;
	
		pDC->FillRect(rectBorder,PInnerBrush);
		pDC->FrameRect(rectBorder,pBorderBrush);
*/
		pDoc->pEqualiser->PaintSample(pDC);
//		pDoc->pEqualiser->PaintFreq(pDC);
	}
	// TODO: add draw code for native data here
}


// CSamplesVisualizationView printing

BOOL CSamplesVisualizationView::OnPreparePrinting(CPrintInfo* PInfo)
{
	// default preparation
	return DoPreparePrinting(PInfo);
}

void CSamplesVisualizationView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*PInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSamplesVisualizationView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*PInfo*/)
{
	// TODO: add cleanup after printing
}


// CSamplesVisualizationView diagnostics

#ifdef _DEBUG
void CSamplesVisualizationView::AssertValid() const
{
	CView::AssertValid();
}

void CSamplesVisualizationView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSamplesVisualizationDoc* CSamplesVisualizationView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSamplesVisualizationDoc)));
	return (CSamplesVisualizationDoc*)m_pDocument;
}
#endif //_DEBUG


// CSamplesVisualizationView message handlers

void CSamplesVisualizationView::OnNullfilter()
{
	CSamplesVisualizationDoc* pDocument=GetDocument();
	pDocument->pEqualiser->Filter(NULL,0);
	Invalidate();
}
