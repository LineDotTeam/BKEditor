#ifndef _SCROLL_DEFINES_H_
#define _SCROLL_DEFINES_H_

#include <windows.h>
#include <tchar.h>

class IScrollView
{
public:
	/*
	* 描述：通知纵向区域滚动。
	* 参数：nPos（新的滚动位置），nHeight（纵向的总的滚动长度）。
	*/
	virtual void NotifyVerticalScrollPosChanged( INT nPos, INT nHeight ) = 0;

	/*
	* 描述：通知横向区域滚动。
	* 参数：nPos（新的滚动位置），nWidth（横向的总的滚动长度）。
	*/
	virtual void NotifyHorizontalScrollPosChanged( INT nPos, INT nWidth ) = 0;
};

enum enumScrollArea
{ 
	Area_Null			= 0x00000000,			//不包括任何区域
	Area_LineL			= 0x00000001,			//垂直LineUp，水平LineLeft
	Area_PageL			= 0x00000002,			//垂直PageUp，水平PageLeft
	Area_Bg				= 0x00000004,			//背景
	Area_Bar			= 0x00000008,			//滚动条部分
	Area_PageW			= 0x00000010,			//垂直PageDown，水平PageRight
	Area_LineW			= 0x00000020,			//垂直LineDown，水平LineRight
	Area_All			= 0xFFFFFFFF,			//包括所有区域
};

class IScrollBar
{
public:
	/*
	* 描述：初始化滚动条。
	* 参数：
	*      dwArea（滚动条包括哪些区域，具体包括6个部分）。
	*      hBitmap（滚动条的资源）。
	*/
	virtual void Init( DWORD dwArea, HBITMAP hBitmap ) = 0;

	/*
	* 描述：初始化滚动条。
	* 参数：
	*      dwArea（滚动条包括哪些区域，具体包括6个部分）。
	*      hBitmap（滚动条的资源）。
	*      nMinSize（滑块最小长度）。
	*      nBarTop（滑块的上部分固定区域长度）。
	*      nBarBottom（滑块的下部分固定区域长度）。
	*      nBgTop（背景上部分固定区域长度）。
	*      nBgBottom（背景下部分固定区域长度）。
	*/
	virtual void Init( DWORD dwArea, HBITMAP hBitmap, INT nMinSize, INT nBarTop, INT nBarBottom, INT nBgTop, INT nBgBottom ){}

	/*
	* 描述：设置需要滚动的窗口。
	* 参数：pScrollView（需要滚动的窗口指针）。
	*/
	virtual void SetScrollView( IScrollView * pScrollView ) = 0;

	/*
	* 描述：通知纵向滚动区域大小变化。
	* 参数：nSize（可视区域大小），nViewSize（能滚动的最大长度）。
	*/
	virtual void NotifyScrollSizeChanged( INT nSize, INT nViewSize ) = 0;

	/*
	* 描述：通知纵向区域滚动位置变化。
	* 参数：nPos（新的滚动位置），nViewSize（能滚动的最大长度）。
	*/
	virtual void NotifyScrollPosChanged( INT nPos, INT nViewSize ) = 0;
};

class IDrawItem
{
public:
	/*
	* 描述：计算每一个Item的上下左右的位置，存储在m_rect中。
	* 参数：hDC（用于计算），xPos（起点x坐标），yPos（起点y坐标），width（限制宽度），height（限制高度）。
	* 返回：每一个Item实际的尺寸。
	*/
	virtual RECT CalcRect( HDC hDC, INT xPos, INT yPos, INT width = -1, INT height = -1 ) = 0;

	/*
	* 描述：绘制每一个Item。
	* 参数：hDC（用于绘制），xOffset（x轴的偏移），yOffset（y轴的偏移）。
	*/
	virtual void Draw( HDC hDC, INT xOffset, INT yOffset, INT viewWidth, INT viewHeight ) = 0;

	/*
	* 描述：销毁每一个Item。
	*/
	virtual void Destroy() = 0;
protected:
	RECT m_rect;
};

#endif