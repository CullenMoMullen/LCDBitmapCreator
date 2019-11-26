
// LCDBitmapCreatorDlg.h : header file
//

#pragma once

class CLCDBitmapCreatorDlgAutoProxy;


#include "MultiSelectFileList.h"
#include "CMyStatic.h"
#include "components/gfx/gfx.h"
#include "components/gfx/gfx_format.h"
#include "components/gfx/gfx_internal.h"
#include "CBitmapCreatorProperties.h"


#define MAX_LOADSTRING 100
#define MAX_IMAGE_STREAMS 20

//Grid Idx
#define SELECTED_IMG_GRID_GROUP_IDX		(0)	//Should be unique per group/sub-group
#define SELECTED_IMG_WIDTH_GRID_IDX		(0)
#define SELECTED_IMG_HEIGHT_GRID_IDX	(1)
#define SELECTED_IMG_BPP_GRID_IDX		(2)
#define SELECTED_IMG_FILE_PATH_GRID_IDX	(3)

#define OUTPUT_IMG_GRID_GROUP_IDX		(1)	//should per unique per group
#define OUTPUT_IMG_BPP_GRID_IDX			(0)	//should be unique within a group or subgroup
#define OUTPUT_IMG_SINGLE_FILE_GRID_IDX	(1)

//-----------------------------------------------------------------------------------------------------------------
//Unique Property IDs
//Format for property IDs is that each should be 100% unique.  Whether a group, sub-group, or property, a unique ID
//is required
#define INVALID_PROP_ID					(0)	//No Group, sub-group, or property should have an Id of 0
#define FIRST_GROUP_PROP_ID				(0x1000)
//-----------------------------------------------------------------------------------------------------------------
// PropertyGrid Group 0
//-----------------------------------------------------------------------------------------------------------------
#define SELECTED_IMG_GROUP_PROP_ID		(FIRST_GROUP_PROP_ID)
//-----------------------------------------------------------------------------------------------------------------
#define SELECTED_IMG_WIDTH_PROP_ID		(SELECTED_IMG_GROUP_PROP_ID + 1)
#define SELECTED_IMG_HEIGHT_PROP_ID		(SELECTED_IMG_GROUP_PROP_ID + 2)
#define SELECTED_IMG_BPP_PROP_ID		(SELECTED_IMG_GROUP_PROP_ID + 3)
#define SELECTED_IMG_FILE_PATH_PROP_ID	(SELECTED_IMG_GROUP_PROP_ID + 4)
//-----------------------------------------------------------------------------------------------------------------
#define SELECTED_IMG_GROUP_NUM_PROPS	(SELECTED_IMG_FILE_PATH_PROP_ID - SELECTED_IMG_WIDTH_PROP_ID + 1)

//-----------------------------------------------------------------------------------------------------------------
// PropertyGrid Group 1
//-----------------------------------------------------------------------------------------------------------------
#define OUTPUT_IMG_GROUP_PROP_ID		(SELECTED_IMG_GROUP_PROP_ID + SELECTED_IMG_GROUP_NUM_PROPS + 1)
//-----------------------------------------------------------------------------------------------------------------
#define OUTPUT_IMG_BPP_PROP_ID			(OUTPUT_IMG_GROUP_PROP_ID + 1)
#define OUTPUT_IMG_SINGLE_FILE_PROP_ID	(OUTPUT_IMG_GROUP_PROP_ID + 2)
//-----------------------------------------------------------------------------------------------------------------
#define OUTPUT_IMG_GROUP_NUM_PROPS		(OUTPUT_IMG_SINGLE_FILE_PROP_ID - OUTPUT_IMG_BPP_PROP_ID + 1)
//-----------------------------------------------------------------------------------------------------------------
#define NUM_PROP_GROUPS					(2)
#define NUM_PROPS_IN_GROUPS				(OUTPUT_IMG_GROUP_NUM_PROPS + SELECTED_IMG_GROUP_NUM_PROPS)
//-----------------------------------------------------------------------------------------------------------------
#define NUM_PROP_IDS_IN_LUT				(OUTPUT_IMG_SINGLE_FILE_PROP_ID - FIRST_GROUP_PROP_ID + 1)



#define LOG_ERROR_COLOR		RGB()
#define LOG_WARNING_COLOR	RGB()








// CLCDBitmapCreatorDlg dialog
class CLCDBitmapCreatorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLCDBitmapCreatorDlg);
	friend class CLCDBitmapCreatorDlgAutoProxy;

// Construction
public:
	CLCDBitmapCreatorDlg(CWnd* pParent = nullptr);	// standard constructor
	virtual ~CLCDBitmapCreatorDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LCDBITMAPCREATOR_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	CLCDBitmapCreatorDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	int AppendToLog(CString str, COLORREF color);
	int AppendToLogAndScroll(CString str, COLORREF color);
	int GetNumVisibleLines(CRichEditCtrl* pCtrl);

	CMyStatic BitmapCtrl;
	CMFCPropertyGridCtrl selectBmpPropGrid;
	CListCtrl FilesToGenerateListCtrl;
	MultiSelectFileList<MAX_PATH * MAX_IMAGE_STREAMS> MultiFileList;
	CImage CurrentImg;
	BOOL includedAlready = false;

	bool WriteBitmapToCFile(CString& InputFilename, CString& OutputFilename, CString& ArrayName, gfx_Bitmap_t* pBitmap, bool bAddBitmapHeader, bool bConst, bool singleOutputFile = false);
	bool LoadBitmapFromFile(CString& inputFile, gfx_BitmapTypeEnum_t eOutputBitmapType, gfx_Bitmap_t** pBitmap);

	CBitmapCreatorProperties props;
	CSimpleMap<CString, gfx_BitmapTypeEnum_t> bmpTypesMap;

	void InitBmpStrEnumMap(void);
	gfx_BitmapTypeEnum_t getBmpTypeFromProp(CString& prop);
	CString getBmpPropStrFromEnum(gfx_BitmapTypeEnum_t type);
	
	void InitBmpPropGrid(void);

	COleVariant* getGridProp(int propId) const;
	void setGridProp(int propId, COleVariant& prop);

	typedef struct _PropIdStruct_t {
		int id;		//unique amongst groups
		int idx;	//unique within a group
		int grp;	//which grp does this belong to
		bool isGrp;	//is this a group itself?
	} PropIdStruct_t;

	//Maps Unique Property IDs to Grid Proprty Index
	const PropIdStruct_t propTable[NUM_PROP_IDS_IN_LUT + 1] = {
		{SELECTED_IMG_GROUP_PROP_ID,		SELECTED_IMG_GRID_GROUP_IDX,		SELECTED_IMG_GRID_GROUP_IDX,	true},
		{SELECTED_IMG_WIDTH_PROP_ID,		SELECTED_IMG_WIDTH_GRID_IDX,		SELECTED_IMG_GRID_GROUP_IDX,	false},
		{SELECTED_IMG_HEIGHT_PROP_ID,		SELECTED_IMG_HEIGHT_GRID_IDX,		SELECTED_IMG_GRID_GROUP_IDX,	false},
		{SELECTED_IMG_BPP_PROP_ID,			SELECTED_IMG_BPP_GRID_IDX,			SELECTED_IMG_GRID_GROUP_IDX,	false},
		{SELECTED_IMG_FILE_PATH_PROP_ID,	SELECTED_IMG_FILE_PATH_GRID_IDX,	SELECTED_IMG_GRID_GROUP_IDX,	false},
		{OUTPUT_IMG_GROUP_PROP_ID,			OUTPUT_IMG_GRID_GROUP_IDX,			OUTPUT_IMG_GRID_GROUP_IDX,		true},
		{OUTPUT_IMG_BPP_PROP_ID,			OUTPUT_IMG_BPP_GRID_IDX,			OUTPUT_IMG_GRID_GROUP_IDX,		false},
		{OUTPUT_IMG_SINGLE_FILE_PROP_ID,	OUTPUT_IMG_SINGLE_FILE_GRID_IDX,	OUTPUT_IMG_GRID_GROUP_IDX,		false},
		//Add more groups and properties before the below line
		{0,0,0,false}
	};

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLvnItemchangedListFiles(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg LRESULT OnAfxWmPropertyChanged(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	CRichEditCtrl m_ctrlLog;
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonExport();

	afx_msg void OnBnClickedCancel();
};
