// SamplesVisualizationDoc.h : interface of the CSamplesVisualizationDoc class
//
#include "EqualiserModule.h"

#pragma once

class CSamplesVisualizationDoc : public CDocument
{
protected: // create from serialization only
	CSamplesVisualizationDoc();
	DECLARE_DYNCREATE(CSamplesVisualizationDoc)

// Attributes
public:

	CEqualiserModule* pEqualiser;
	
	

// Operations
public:

// Overrides
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CSamplesVisualizationDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


