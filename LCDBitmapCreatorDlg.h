
// LCDBitmapCreatorDlg.h : header file
//

#pragma once
#include "MultiSelectFileList.h"
#include "CMyStatic.h"
#include "components/gfx/gfx.h"
#include "components/gfx/gfx_format.h"
#include "components/gfx/gfx_internal.h"
#include "CBitmapCreatorProperties.h"


#define MAX_LOADSTRING 100
#define MAX_IMAGE_STREAMS 20

//Grid Idx
#define SEL_IMG_GRID_GROUP_IDX 0
#define SEL_IMG_WIDTH_GRID_IDX 0
#define SEL_IMG_HEIGHT_GRID_IDX 1
#define SEL_IMG_BPP_GRID_IDX 2

#define OUTPUT_GRID_GROUP_IDX 1
#define OUTPUT_BPP_GRID_IDX 0
#define OUTPUT_SINGLE_FILE_GRID_IDX 1

//Unique Property IDs
#define FIRST_GROUP_ID 0x1000
#define SEL_IMG_GROUP FIRST_GROUP_ID
#define SEL_IMG_WIDTH (SEL_IMG_GROUP+1)
#define SEL_IMG_HEIGHT (SEL_IMG_GROUP+2)
#define SEL_IMG_BPP (SEL_IMG_GROUP+3)
#define SEL_IMG_LAST_ID (SEL_IMG_BPP)

#define OUTPUT_IMG_GROUP (SEL_IMG_LAST_ID+1)
#define OUTPUT_IMG_BPP (OUTPUT_IMG_GROUP+1)
#define OUTPUT_SINGLE_FILE (OUTPUT_IMG_GROUP+2)

#define NUM_PROP_IDS (OUTPUT_SINGLE_FILE - FIRST_GROUP_ID +1)

#define GET_PROP_IDX(x)


// CLCDBitmapCreatorDlg dialog
class CLCDBitmapCreatorDlg : public CDialogEx
{
// Construction
public:
	CLCDBitmapCreatorDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LCDBITMAPCREATOR_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnInitDialog();
public:
	CMyStatic BitmapCtrl;
	CMFCPropertyGridCtrl selectBmpPropGrid;
	CListCtrl FilesToGenerateListCtrl;
	MultiSelectFileList<MAX_PATH * MAX_IMAGE_STREAMS> MultiFileList;
	CImage CurrentImg;

	gfx_BitmapTypeEnum_t getBmpTypeFromProp(CString& prop);
	CString getBmpPropStrFromEnum(gfx_BitmapTypeEnum_t type);
	
	bool WriteBitmapToCFile(CString& InputFilename, CString& OutputFilename, CString& ArrayName, gfx_Bitmap_t* pBitmap, bool bAddBitmapHeader, bool bConst, bool singleOutputFile = false);
	bool LoadBitmapFromFile(CString& inputFile, gfx_BitmapTypeEnum_t eOutputBitmapType, gfx_Bitmap_t** pBitmap);

	COleVariant* getGridProp(int propId) const;
	void setGridProp(int propId, COleVariant &prop);

	typedef struct _PropIdStruct_t {
		int id;		//unique amongst groups
		int idx;	//unique within a group
		int grp;	//which grp foes this belong to
		bool isGrp;	//is this a group itself?
	} PropIdStruct_t;
	
	const PropIdStruct_t propTable[NUM_PROP_IDS + 1] = {
		{SEL_IMG_GROUP,		SEL_IMG_GRID_GROUP_IDX,		SEL_IMG_GRID_GROUP_IDX, true},
		{SEL_IMG_WIDTH,		SEL_IMG_WIDTH_GRID_IDX,		SEL_IMG_GRID_GROUP_IDX, false},
		{SEL_IMG_HEIGHT,	SEL_IMG_HEIGHT_GRID_IDX,	SEL_IMG_GRID_GROUP_IDX, false},
		{SEL_IMG_BPP,		SEL_IMG_BPP_GRID_IDX,		SEL_IMG_GRID_GROUP_IDX, false},
		{OUTPUT_IMG_GROUP,	OUTPUT_GRID_GROUP_IDX,		OUTPUT_GRID_GROUP_IDX,	true},
		{OUTPUT_IMG_BPP,	OUTPUT_BPP_GRID_IDX,		OUTPUT_GRID_GROUP_IDX,	false},
		{OUTPUT_SINGLE_FILE,OUTPUT_SINGLE_FILE_GRID_IDX,OUTPUT_GRID_GROUP_IDX,	false},
		{0,0,0,false}
	};

// Implementation
protected:
	HICON m_hIcon;
	CBitmapCreatorProperties props;
	CSimpleMap<CString, gfx_BitmapTypeEnum_t> bmpTypesMap;


	// Generated message map functions

	DECLARE_MESSAGE_MAP()

	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//afx_msg LRESULT OnPropertyChanged(__in WPARAM wparam, __in LPARAM lParam);
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonExport();
	afx_msg void OnLvnItemchangedListFiles(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg LRESULT OnAfxWmPropertyChanged(WPARAM wParam, LPARAM lParam);
};
