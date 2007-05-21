// SamplesVisualizationDoc.cpp : implementation of the CSamplesVisualizationDoc class
//

#include "stdafx.h"
#include "SamplesVisualization.h"

#include "SamplesVisualizationDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSamplesVisualizationDoc

IMPLEMENT_DYNCREATE(CSamplesVisualizationDoc, CDocument)

BEGIN_MESSAGE_MAP(CSamplesVisualizationDoc, CDocument)
END_MESSAGE_MAP()


// CSamplesVisualizationDoc construction/destruction

CSamplesVisualizationDoc::CSamplesVisualizationDoc():pEqualiser(NULL)
{
	// TODO: add one-time construction code here

}

CSamplesVisualizationDoc::~CSamplesVisualizationDoc()
{
}

BOOL CSamplesVisualizationDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	
	

	pEqualiser=new CEqualiserModule(4,0);

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CSamplesVisualizationDoc serialization

void CSamplesVisualizationDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CSamplesVisualizationDoc diagnostics

#ifdef _DEBUG
void CSamplesVisualizationDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSamplesVisualizationDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSamplesVisualizationDoc commands
