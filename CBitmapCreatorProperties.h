#pragma once

#include "components/gfx/gfx.h"
#include "components/gfx/gfx_format.h"
#include "components/gfx/gfx_internal.h"


class CBitmapCreatorProperties
{
protected:
	bool m_PropOutputSingleFile;
	int m_PropOutputType;

	int m_PropSelBmpWidth;
	int m_PropSelBmpHeight;
	int m_PropSelBmpBpp;


public:
	~CBitmapCreatorProperties();
	CBitmapCreatorProperties();

	int getPropOutputType() const;
	void setPropOutputType(int type);

	bool getPropOutputSingleFile() const;
	void setPropOutputSingleFile(bool singleFile);

	int getPropSelBmpWidth() const;
	void setPropSelBmpWidth(int width);

	int getPropSelBmpHeight() const;
	void setPropSelBmpHeight(int height);

	int getPropSelBmpBpp() const;
	void setPropSelBmpBpp(int bpp);

};

