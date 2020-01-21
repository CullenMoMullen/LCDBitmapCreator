

#include "pch.h"

#include "CBitmapCreatorProperties.h"
CBitmapCreatorProperties::~CBitmapCreatorProperties()
{

}

CBitmapCreatorProperties::CBitmapCreatorProperties()
{
	m_PropOutputSingleFile = false;
	m_PropOutputType = BMP_TYPE_INVALID;
	m_PropSelBmpBpp = 0;
	m_PropSelBmpHeight = 0;
	m_PropSelBmpWidth = 0;
	m_PropSelBmpFilePath = TEXT("");
}

int CBitmapCreatorProperties::getPropOutputType() const
{
	return m_PropOutputType;
}

void CBitmapCreatorProperties::setPropOutputType(int type)
{
	m_PropOutputType = type;
}

bool CBitmapCreatorProperties::getPropOutputSingleFile() const
{
	return m_PropOutputSingleFile;
}

void CBitmapCreatorProperties::setPropOutputSingleFile(bool singleFile)
{
	m_PropOutputSingleFile = singleFile;
}

int CBitmapCreatorProperties::getPropSelBmpWidth() const
{
	return m_PropSelBmpWidth;
}

void CBitmapCreatorProperties::setPropSelBmpWidth(int width)
{
	m_PropSelBmpWidth = width;
}

int CBitmapCreatorProperties::getPropSelBmpHeight() const
{
	return m_PropSelBmpHeight;
}

void CBitmapCreatorProperties::setPropSelBmpHeight(int height)
{
	m_PropSelBmpHeight = height;
}

int CBitmapCreatorProperties::getPropSelBmpBpp() const
{
	return m_PropSelBmpBpp;
}

void CBitmapCreatorProperties::setPropSelBmpBpp(int bpp)
{
	m_PropSelBmpBpp = bpp;
}

CString CBitmapCreatorProperties::getPropSelBmpFilePath() const
{
	return m_PropSelBmpFilePath;
}

void CBitmapCreatorProperties::setPropSelBmpFilePath(CString filePath)
{
	if (!filePath.IsEmpty()) {
		m_PropSelBmpFilePath = filePath;
	}
}