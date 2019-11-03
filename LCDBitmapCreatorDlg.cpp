
// LCDBitmapCreatorDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "LCDBitmapCreator.h"
#include "LCDBitmapCreatorDlg.h"
#include "afxdialogex.h"
#include <atlimage.h>

#include "components/gfx/gfx.h"
#include "components/gfx/gfx_format.h"
#include "components/gfx/gfx_internal.h"


extern "C" gfx_Color_t g_Pallete[];
extern "C" {
	extern void gfx_bmp_DeleteBitmap(gfx_Bitmap_t* pBitmap);
}
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLCDBitmapCreatorDlg dialog

CLCDBitmapCreatorDlg::CLCDBitmapCreatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LCDBITMAPCREATOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLCDBitmapCreatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_FILES, FilesToGenerateListCtrl);
	DDX_Control(pDX, IDC_DRAW_CTRL, BitmapCtrl);
	DDX_Control(pDX, IDC_MFCPROPERTYGRIDSELBMP, selectBmpPropGrid);
}

BEGIN_MESSAGE_MAP(CLCDBitmapCreatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CLCDBitmapCreatorDlg::OnBnClickedButtonOpen)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_FILES, &CLCDBitmapCreatorDlg::OnLvnItemchangedListFiles)
	ON_BN_CLICKED(IDC_BUTTON_EXPORT, &CLCDBitmapCreatorDlg::OnBnClickedButtonExport)
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, &CLCDBitmapCreatorDlg::OnAfxWmPropertyChanged)
END_MESSAGE_MAP()


// CLCDBitmapCreatorDlg message handlers

BOOL CLCDBitmapCreatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}

	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	
	//Setup the properties control
	selectBmpPropGrid.EnableHeaderCtrl();
	selectBmpPropGrid.EnableDescriptionArea();
	selectBmpPropGrid.SetVSDotNetLook();
	selectBmpPropGrid.MarkModifiedProperties();
	selectBmpPropGrid.SetFont(::AfxGetApp()->GetMainWnd()->GetFont(), true);
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Selected Image"));
	CMFCPropertyGridProperty* pGroup2 = new CMFCPropertyGridProperty(_T("Output Settings"));
	// construct a COleVariant object.
	_variant_t varOneFile((short)VARIANT_FALSE, VT_BOOL);
	COleVariant varW(0L, VT_I4);
	pGroup1->SetData(SEL_IMG_GROUP);
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Width"), varW, _T("Image width in pixels"), SEL_IMG_WIDTH));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Height"), varW, _T("Image height in pixels"), SEL_IMG_HEIGHT));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Bit Depth"), varW, _T("Number of Bits Per Pixel"), SEL_IMG_BPP));
	pGroup1->GetSubItem(SEL_IMG_WIDTH_GRID_IDX)->AllowEdit(FALSE);
	pGroup1->GetSubItem(SEL_IMG_HEIGHT_GRID_IDX)->AllowEdit(FALSE);
	pGroup1->GetSubItem(SEL_IMG_BPP_GRID_IDX)->AllowEdit(FALSE);

	COleVariant outFmtStr(_T("Choose Format..."),VT_BSTR);
	CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(_T("Output Format"),	outFmtStr, 
		_T("One of: \nBITMAP_1BPP_IDEAL\nBITMAP_1BPP_VERTICAL\nBITMAP_8BPP_PALETTE\nBITMAP_16BPP_565\nBITMAP_18BPP_666\nBITMAP_24BPP_888\nBITMAP_32BPP_8888"), 
		OUTPUT_IMG_BPP);
	pProp->AddOption(_T("BITMAP_1BPP_IDEAL"));
	pProp->AddOption(_T("BITMAP_1BPP_VERTICAL"));
	pProp->AddOption(_T("BITMAP_8BPP_PALETTE"));
	pProp->AddOption(_T("BITMAP_16BPP_565"));
	pProp->AddOption(_T("BITMAP_18BPP_666"));
	pProp->AddOption(_T("BITMAP_24BPP_888"));
	pProp->AddOption(_T("BITMAP_32BPP_8888"));
	pProp->SetValue(_T("BITMAP_1BPP_VERTICAL"));	//Default choice
	pProp->AllowEdit();
	props.setPropOutputType(BITMAP_TYPE_1BPP_VERTICAL);
	
	pGroup2->SetData(OUTPUT_IMG_GROUP);
	pGroup2->AddSubItem(pProp);

	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("Single C File"), varOneFile, _T("Generate one file containing all data structures?\n\nTrue: Will prompt for file name\n\nFalse: Files named relative to input files"), OUTPUT_SINGLE_FILE));
	
	pGroup1->Expand();
	pGroup1->AllowEdit(TRUE);
	pGroup1->Enable();
	pGroup1->Show();
	pGroup1->Redraw();

	pGroup2->Expand();
	pGroup2->AllowEdit(TRUE);
	pGroup2->Enable();
	pGroup2->Show();
	pGroup2->Redraw();

	selectBmpPropGrid.AddProperty(pGroup1);
	selectBmpPropGrid.AddProperty(pGroup2);

	LOGFONT lf;
	CFont* font = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	font->GetLogFont(&lf);

	HDITEM hdItem;
	hdItem.mask = HDI_WIDTH; // indicating cxy is width
	hdItem.cxy = 170; // whatever you want the property name column width to be
	selectBmpPropGrid.GetHeaderCtrl().SetItem(0, &hdItem);

	// TODO: Add extra initialization here
	RECT rect;
	FilesToGenerateListCtrl.GetClientRect(&rect);
	FilesToGenerateListCtrl.InsertColumn(0, TEXT("Images to convert"), 0, rect.right - rect.left);

	//FileCreateProgress.SetMarquee(true, 500);
	UpdateData(false);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLCDBitmapCreatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CLCDBitmapCreatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CLCDBitmapCreatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CLCDBitmapCreatorDlg::OnBnClickedButtonOpen()
{
	// TODO: Add your control notification handler code here
	OPENFILENAME ofn;
	HRESULT hr = S_OK;

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = ::GetTopWindow(this->m_hWnd);
	ofn.lpstrFilter = TEXT("Image Files (.BMP, .JPG, .JPEG, .PNG, .ICO)\0*.BMP;*.JPG;*.JPEG;*.PNG;*.ICO\0")
					  TEXT("All Files (*.*)\0*.*\0\0");
	ofn.nFilterIndex = 1;
	ofn.lpstrFile = MultiFileList.BufferPtr();
	ofn.nMaxFile = MultiFileList.BufferSizeCch();
	ofn.lpstrTitle = TEXT("Select Image Files...");
	ofn.Flags = OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT | OFN_FILEMUSTEXIST | OFN_EXPLORER;
	ofn.lpstrDefExt = TEXT("BMP");

	// Launch the Open File dialog.
	DWORD result = GetOpenFileName(&ofn);

	// Check for errors.
	if (CommDlgExtendedError() != 0)
	{
		// NOTE: For mult-selection, CommDlgExtendedError can return FNERR_BUFFERTOOSMALL even when
		// GetOpenFileName returns TRUE.
		MessageBox(NULL, TEXT("Could not open files."), MB_OK | MB_ICONERROR);
		return;
	}
	else if (!result)
	{
		// The user cancelled. (No error occurred.)
		return;
	}

	FAIL_RET(hr = MultiFileList.ParseBuffer());

	// Add each file to the list of images to convert
	for (DWORD i = 0; i < MAX_IMAGE_STREAMS; i++)
	{
		TCHAR* pFileName = NULL;

		FAIL_RET(hr = MultiFileList.Next(&pFileName));
		if (hr == S_FALSE)
		{
			hr = S_OK;
			break;
		}

		FilesToGenerateListCtrl.InsertItem(0, pFileName, 0);

		CoTaskMemFree(pFileName);

		FAIL_RET(hr);
	}
	UpdateData(false);
}


void CLCDBitmapCreatorDlg::OnLvnItemchangedListFiles(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	CString filestr;
	static RECT imgRect;

	// TODO: Add your control notification handler code here
	if ((pNMLV->uChanged & LVIF_STATE) && (pNMLV->uNewState & LVIS_SELECTED)) {
		if (pNMLV->iItem >= 0) {
			if (!BitmapCtrl.CurrentImg.IsNull()) {
				BitmapCtrl.CurrentImg.Destroy();
			}
			filestr = FilesToGenerateListCtrl.GetItemText(pNMLV->iItem, 0);
			BitmapCtrl.CurrentImg.Load(filestr);
			BitmapCtrl.Invalidate();

			int bpp = BitmapCtrl.CurrentImg.GetBPP();
			int width = BitmapCtrl.CurrentImg.GetWidth();
			int height = BitmapCtrl.CurrentImg.GetHeight();

			COleVariant varW((long)width, VT_I4);
			COleVariant varH((long)height, VT_I4);
			COleVariant varBpp((long)bpp, VT_I4);
			
			props.setPropSelBmpWidth(width);
			props.setPropSelBmpHeight(height);
			props.setPropSelBmpBpp(bpp);
			
			setGridProp(SEL_IMG_WIDTH, varW);
			setGridProp(SEL_IMG_HEIGHT, varH);
			setGridProp(SEL_IMG_BPP, varBpp);
		}
	}

	*pResult = 0;
}


void CLCDBitmapCreatorDlg::OnBnClickedButtonExport()
{
	// TODO: Add your control notification handler code here
	CImage img;
	int ret = 0;
	CString arrName = TEXT("");
	gfx_Bitmap_t* outbmp = NULL;
	//UINT nCheck = SingleCFileCheckBox.GetState();
	SHORT numFiles = FilesToGenerateListCtrl.GetItemCount();

	gfx_BitmapTypeEnum_t outputFormat = (gfx_BitmapTypeEnum_t) props.getPropOutputType();
	//selectBmpPropGrid.GetProperty(OUTPUT_GRID_GROUP_IDX)->GetSubItem(OUTPUT_BPP_GRID_IDX);//pGroup1->GetSubItem(0)->AllowEdit(FALSE);
	if (outputFormat == BITMAP_TYPE_INVALID) {
		MessageBox(
			_T("You must select an output format\nfor the generated C code!"),
			_T("User Input Required"),
			MB_ICONERROR | MB_OK);

		return;
	}

	if (FilesToGenerateListCtrl.GetItemCount() <= 0) {
		MessageBox(
			_T("Add at least one file to the list\nof images to be converted to code!"),
			_T("Nothing To Do"),
			MB_ICONERROR | MB_OK);

		return;
	}



	bool nCheck = props.getPropOutputSingleFile();
	int width = 0;
	int height = 0;
	CString outfilename = L"";
	WCHAR outname[MAX_PATH + 1];
	while (numFiles > 0) {
		numFiles--;
		
		CString inputfilename = FilesToGenerateListCtrl.GetItemText(0, 0);
		int dotPos = inputfilename.ReverseFind('.');
		
		if (nCheck == BST_CHECKED) {
			//We want to output all bitmaps to the same C file, so prompt user for a file name
			if (outfilename == L"") {
				//Prompt the user to choose a file to save to
				OPENFILENAME ofn;
				HRESULT hr = S_OK;

				ZeroMemory(&ofn, sizeof(ofn));
				ofn.lStructSize = sizeof(OPENFILENAME);
				ofn.hwndOwner = ::GetTopWindow(this->m_hWnd);
				ofn.lpstrFilter = TEXT("C Source Files (.C, .CPP, .H, .HPP)\0*.C;*.CPP;*.H;*.HPP\0")
					TEXT("All Files (*.*)\0*.*\0\0");
				ofn.nFilterIndex = 1;
				ofn.lpstrFile = outname;
				ofn.nMaxFile = MAX_PATH + 1;
				ofn.lpstrTitle = TEXT("Save File");
				ofn.Flags = OFN_HIDEREADONLY | OFN_EXPLORER;
				ofn.lpstrDefExt = TEXT("C");

				// Launch the Open File dialog.
				DWORD result = GetSaveFileName(&ofn);
				if (!result) {
					return;
				}
				else {
					outfilename = outname;
				}
				//set variable to indicate opening file in append mode.
			}
		}
		else {
			//Each imput image will create its own C file, named the same as the image file, but with a .c extenstion
			outfilename = inputfilename;
			outfilename.Truncate(dotPos);
			outfilename.Append(TEXT(".c"));
		}

		//Generate the array name
		arrName = PathFindFileName(inputfilename);
		dotPos = arrName.ReverseFind('.');
		arrName.Truncate(dotPos);

		if (!img.IsNull()) {
			img.Destroy();
		}
		
		img.Load(inputfilename);
		width = img.GetWidth();
		height = img.GetHeight();

		ret = LoadBitmapFromFile(inputfilename, outputFormat, &outbmp);
		if (0 == ret) {
			WriteBitmapToCFile(inputfilename, outfilename, arrName, outbmp, true, true);
			if (outbmp != NULL) {
				gfx_bmp_DeleteBitmap(outbmp);
			}
		}
		FilesToGenerateListCtrl.DeleteItem(0);
		UpdateData(false);
	}
}


bool CLCDBitmapCreatorDlg::WriteBitmapToCFile(CString& InputFilename, CString& OutputFilename, CString& ArrayName, gfx_Bitmap_t* pBitmap, bool bAddBitmapHeader, bool bConst)
{
	FILE* pFile;
	errno_t ret;
	if (OutputFilename == "stdout")
		pFile = stdout;
	else
		ret = _wfopen_s(&pFile, OutputFilename.GetBuffer(), L"wt+");

	if (!pFile) {
		wprintf(L"%s :: %s ::fopen(\"%s\") failed.\r\n", __FILEW__, __FUNCTIONW__, InputFilename.GetString());
		//cout << __FILE__ "::" __FUNCTION__ "::fopen(\""<<InputFilename<<"\") failed.\r\n";
		return true;
	}

	fwprintf(pFile, L"// %s (%d,%d)\n", InputFilename.GetString(), pBitmap->uWidth, pBitmap->uHeight);
	if (!ArrayName.IsEmpty()) {
		fwprintf(pFile,L"// %s\n",InputFilename.GetString());
		fwprintf(pFile,L"#include <types.h>\n");
		if (bConst)
			fwprintf(pFile, L"const gfx_Bitmap_t %s = {\n", ArrayName.GetString());
		else
			fwprintf(pFile, L"gfx_Bitmap_t %s = {\n", ArrayName.GetString());
	}
	fwprintf(pFile, L"{\n");
	int iSize = 0;

	switch (pBitmap->uType)
	{
	case BITMAP_TYPE_1BPP_IDEAL:
	case BITMAP_TYPE_1BPP_VERTICAL:
	case BITMAP_TYPE_16BPP_565:
	case BITMAP_TYPE_18BPP_666:
	case BITMAP_TYPE_24BPP_888:
	case BITMAP_TYPE_32BPP_8888:
	case BITMAP_TYPE_8BPP_PALETTE:
		iSize = 4 + gfx_format_GetDataSize(pBitmap->uType)(pBitmap->uWidth, pBitmap->uHeight);
		break;
	default:
		iSize = 0;
		break;
	}

	if (bAddBitmapHeader)
	{

		fwprintf(pFile, L"    // First 32-bits is meta-data packed logically as in gfx_Bitmap_t:\n");
		fwprintf(pFile, L"    // type(8)width(12)height(12), reversed in memory due to endian-ness\n");


		fwprintf(pFile, L"    %s,\n", GetBmpEnumStr( (gfx_BitmapTypeEnum_t)((pBitmap->uType) & 0xff)).GetString());
		fwprintf(pFile, L"    %u, ", (pBitmap->uWidth) & 0xfff);
		fwprintf(pFile, L"%u,\n    {\n", (pBitmap->uHeight) & 0xfff);
	}

	for (int i = 1; i < (iSize + 3) / 4; i++)
	{
		if (pBitmap->uType == BITMAP_TYPE_18BPP_666)
		{
			// Special case for 18bpp 666 format
			// Right justify the 6 most significant bits per octet
			fwprintf(pFile, L"        0x%02X", (((uint32_t*)pBitmap)[i] >> 26) & 0xff);
			fwprintf(pFile, L"%02X", (((uint32_t*)pBitmap)[i] >> 18) & 0xff);
			fwprintf(pFile, L"%02X", ((((uint32_t*)pBitmap)[i]) >> 10) & 0xff);
			fwprintf(pFile, L"%02X,\n", (((uint32_t*)pBitmap)[i] >> 2) & 0xff);
		}
		else
		{
			fwprintf(pFile, L"        0x%02X, ", (((uint32_t*)pBitmap)[i]) & 0xff);
			fwprintf(pFile, L"0x%02X, ", (((uint32_t*)pBitmap)[i] >> 8) & 0xff);
			fwprintf(pFile, L"0x%02X, ", (((uint32_t*)pBitmap)[i] >> 16) & 0xff);
			fwprintf(pFile, L"0x%02X,\n", (((uint32_t*)pBitmap)[i] >> 24) & 0xff);

		}
	}

	fwprintf(pFile, L"    },\n");

	fwprintf(pFile, L"};\n");

	fclose(pFile);

	return false;
}

CString CLCDBitmapCreatorDlg::GetBmpEnumStr(gfx_BitmapTypeEnum_t type) {

	CString str = _T("");
	switch (type)
	{
		case BITMAP_TYPE_1BPP_IDEAL:
			str = _T("BITMAP_TYPE_1BPP_IDEAL");
			break;
		default:
		case BITMAP_TYPE_1BPP_VERTICAL:
			str = _T("BITMAP_TYPE_1BPP_VERTICAL");
			break;
		case BITMAP_TYPE_16BPP_565:
			str = _T("BITMAP_TYPE_16BPP_565");
			break;
		case BITMAP_TYPE_18BPP_666:
			str = _T("BITMAP_TYPE_18BPP_666");
			break;
		case BITMAP_TYPE_24BPP_888:
			str = _T("BITMAP_TYPE_24BPP_888");
			break;
		case BITMAP_TYPE_32BPP_8888:
			str = _T("BITMAP_TYPE_32BPP_8888");
			break;
		case BITMAP_TYPE_8BPP_PALETTE:
			str = _T("BITMAP_TYPE_8BPP_PALETTE");
			break;
	}
	return str;
}

bool CLCDBitmapCreatorDlg::LoadBitmapFromFile(CString& inputFile, gfx_BitmapTypeEnum_t eOutputBitmapType, gfx_Bitmap_t** pBitmap)
{
	CImage image;

	if (image.Load(inputFile) != S_OK)
	{
		wprintf(L"%Ts :: LoadBitmapFromFile :: image.Load(\"%s\") failed.\r\n", TEXT(__FILE__), inputFile.GetString());
		//cout << __FILE__ "::LoadBitmapFromFile::image.Load(\""<<inputFile<<"\") failed.\r\n";
		return true;
	}
	if (eOutputBitmapType == -1)
	{
		// Let's guess that it's 16BPP 565 always...
		eOutputBitmapType = BITMAP_TYPE_1BPP_VERTICAL;
	}
	int size;
	switch (eOutputBitmapType)
	{
	case BITMAP_TYPE_1BPP_IDEAL:
	case BITMAP_TYPE_1BPP_VERTICAL:
	case BITMAP_TYPE_16BPP_565:
	case BITMAP_TYPE_18BPP_666:
	case BITMAP_TYPE_24BPP_888:
	case BITMAP_TYPE_32BPP_8888:
	case BITMAP_TYPE_8BPP_PALETTE:
		*pBitmap = gfx_bmp_CreateBitmap(eOutputBitmapType, image.GetWidth(), image.GetHeight());
		//size = 4 + gfx_format_GetDataSize(eOutputBitmapType)(image.GetHeight(), image.GetWidth());
		break;
	default:
		//size = 0;
		*pBitmap = NULL;
		break;
	}

	if (*pBitmap == NULL) {
		wprintf(L"%Ts :: LoadBitmapFromFile :: unsupported Bitmap type.\r\n", TEXT(__FILE__));
		return true;
	}

	//(*pBitmap)->uType = eOutputBitmapType;
	//(*pBitmap)->uHeight = image.GetHeight();
	//(*pBitmap)->uWidth = image.GetWidth();

	COLORREF color;
	COLORREF* pcolor;
	uint32_t* pOutput = (uint32_t*)(*pBitmap)->pData;
	for (int y = 0; y < image.GetHeight(); y++)
	{
		for (int x = 0; x < image.GetWidth(); x++)
		{
			if ((eOutputBitmapType == BITMAP_TYPE_32BPP_8888) && (image.GetBPP() == 32)) {
				//get the address of the 32 bit pixel because we need to read it out.  GetPixel only return RGB data.
				pcolor = (COLORREF*)image.GetPixelAddress(x, y);
				color = RGBA((*pcolor & 0x00FF0000) >> 16, (*pcolor & 0x0000FF00) >> 8, (*pcolor & 0x000000FF), (*pcolor & 0xFF000000) >> 24);
				*pOutput = color;
				pOutput++;
			}
			else {
				color = image.GetPixel(x, y);    //get 24-bit pixel data RGB
				gfx_bmp_PutPixel(g_Pallete, *pBitmap, x, y, RGB(GetRValue(color), GetGValue(color), GetBValue(color)));
			}
		}
	}
	return false;
}

COleVariant* CLCDBitmapCreatorDlg::getGridProp(int propId) const
{
	PropIdStruct_t const * prop = propTable;
	COleVariant *GridProp = NULL;
	int group = -1;
	int propIdx = -1;
	bool isGrp = true;
	while (prop->id != 0) {
		if (propId == prop->id) {
			group = prop->grp;
			propIdx = prop->idx;
			isGrp = prop->isGrp;

			if (isGrp == true) {
				*GridProp = selectBmpPropGrid.GetProperty(propIdx)->GetValue();
			}
			else {
				*GridProp = selectBmpPropGrid.GetProperty(group)->GetSubItem(propIdx)->GetValue();
			}
			break;
		}
		prop++;
	}

	return GridProp;
}

void CLCDBitmapCreatorDlg::setGridProp(int propId, COleVariant &prop)
{
	PropIdStruct_t const* property = propTable;
	COleVariant* GridProp = NULL;
	int group = -1;
	int propIdx = -1;
	bool isGrp = true;
	while (property->id != 0) {
		if (propId == property->id) {
			group = property->grp;
			propIdx = property->idx;
			isGrp = property->isGrp;

			if (isGrp == true) {
				selectBmpPropGrid.GetProperty(propIdx)->SetValue(prop);
			}
			else {
				selectBmpPropGrid.GetProperty(group)->GetSubItem(propIdx)->SetValue(prop);
			}
			break;
		}
		property++;
	}
}

afx_msg LRESULT CLCDBitmapCreatorDlg::OnAfxWmPropertyChanged(WPARAM wParam, LPARAM lParam)
{
	// pProp will have all the variables and info of the active or change property
	CMFCPropertyGridProperty* pProp = (CMFCPropertyGridProperty*)lParam;
	int pID = pProp->GetData();

	CString str = pProp->GetName(); // get the change property name.
	COleVariant i = pProp->GetValue();// get the change value.

	//below is the code to change COleVariant to other variable type
	LPVARIANT pVar = (LPVARIANT)i;
	int x;
	short y;
	double d;
	float f;
	bool status;
	CString str1;
	switch (pVar->vt)
	{
	case VT_I2:    // short
		y = pVar->iVal;
		break;
	case VT_I4:     // int
		x = pVar->lVal;
		break;
	case VT_R4:    // float
		f = pVar->fltVal;
		break;
	case VT_R8:    // double
		d = pVar->dblVal;
		break;
	case VT_INT:
		x = pVar->lVal;
		break;
	case VT_BOOL:
		status = pVar->boolVal;
		break;
	case VT_BSTR:
		str1 = pVar->bstrVal;
		break;
		// etc.
	}
	
	switch (pID) {
		case SEL_IMG_GROUP:
		case SEL_IMG_WIDTH:
		case SEL_IMG_HEIGHT:
		case SEL_IMG_BPP:
		case OUTPUT_IMG_GROUP:
			break;
		case OUTPUT_IMG_BPP:
			if (str1 == _T("BITMAP_1BPP_IDEAL")) {
				props.setPropOutputType(BITMAP_TYPE_1BPP_IDEAL);
				m_OutputType = BITMAP_TYPE_1BPP_IDEAL;
			}
			else if(str1 == _T("BITMAP_1BPP_VERTICAL")){
				props.setPropOutputType(BITMAP_TYPE_1BPP_VERTICAL);
				m_OutputType = BITMAP_TYPE_1BPP_VERTICAL;
			}
			else if (str1 == _T("BITMAP_8BPP_PALETTE")) {
				props.setPropOutputType(BITMAP_TYPE_8BPP_PALETTE);
				m_OutputType = BITMAP_TYPE_8BPP_PALETTE;
			}
			else if (str1 == _T("BITMAP_16BPP_565")) {
				props.setPropOutputType(BITMAP_TYPE_16BPP_565);
				m_OutputType = BITMAP_TYPE_16BPP_565;
			}
			else if (str1 == _T("BITMAP_18BPP_666")) {
				props.setPropOutputType(BITMAP_TYPE_18BPP_666);
				m_OutputType = BITMAP_TYPE_18BPP_666;
			}
			else if (str1 == _T("BITMAP_24BPP_888")) {
				props.setPropOutputType(BITMAP_TYPE_24BPP_888);
				m_OutputType = BITMAP_TYPE_24BPP_888;
			}
			else if (str1 == _T("BITMAP_32BPP_8888")) {
				props.setPropOutputType(BITMAP_TYPE_32BPP_8888);
				m_OutputType = BITMAP_TYPE_32BPP_8888;
			}
			else {
				//assume 1BPP Vertical
				props.setPropOutputType(BITMAP_TYPE_1BPP_VERTICAL);
				m_OutputType = BITMAP_TYPE_1BPP_VERTICAL;
			}
			break;
		case OUTPUT_SINGLE_FILE:
			m_OutputSingleFile = pVar->boolVal;
			break;
	}

	return 0;
}


void CLCDBitmapCreatorDlg::OnOptionsSinglecfile()
{
	// TODO: Add your command handler code here
	//::AfxGetApp()->GetMainWnd()->GetMenu()->


}