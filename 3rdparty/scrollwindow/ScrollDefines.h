#ifndef _SCROLL_DEFINES_H_
#define _SCROLL_DEFINES_H_

#include <windows.h>
#include <tchar.h>

class IScrollView
{
public:
	/*
	* ������֪ͨ�������������
	* ������nPos���µĹ���λ�ã���nHeight��������ܵĹ������ȣ���
	*/
	virtual void NotifyVerticalScrollPosChanged( INT nPos, INT nHeight ) = 0;

	/*
	* ������֪ͨ�������������
	* ������nPos���µĹ���λ�ã���nWidth��������ܵĹ������ȣ���
	*/
	virtual void NotifyHorizontalScrollPosChanged( INT nPos, INT nWidth ) = 0;
};

enum enumScrollArea
{ 
	Area_Null			= 0x00000000,			//�������κ�����
	Area_LineL			= 0x00000001,			//��ֱLineUp��ˮƽLineLeft
	Area_PageL			= 0x00000002,			//��ֱPageUp��ˮƽPageLeft
	Area_Bg				= 0x00000004,			//����
	Area_Bar			= 0x00000008,			//����������
	Area_PageW			= 0x00000010,			//��ֱPageDown��ˮƽPageRight
	Area_LineW			= 0x00000020,			//��ֱLineDown��ˮƽLineRight
	Area_All			= 0xFFFFFFFF,			//������������
};

class IScrollBar
{
public:
	/*
	* ��������ʼ����������
	* ������
	*      dwArea��������������Щ���򣬾������6�����֣���
	*      hBitmap������������Դ����
	*/
	virtual void Init( DWORD dwArea, HBITMAP hBitmap ) = 0;

	/*
	* ��������ʼ����������
	* ������
	*      dwArea��������������Щ���򣬾������6�����֣���
	*      hBitmap������������Դ����
	*      nMinSize��������С���ȣ���
	*      nBarTop��������ϲ��̶ֹ����򳤶ȣ���
	*      nBarBottom��������²��̶ֹ����򳤶ȣ���
	*      nBgTop�������ϲ��̶ֹ����򳤶ȣ���
	*      nBgBottom�������²��̶ֹ����򳤶ȣ���
	*/
	virtual void Init( DWORD dwArea, HBITMAP hBitmap, INT nMinSize, INT nBarTop, INT nBarBottom, INT nBgTop, INT nBgBottom ){}

	/*
	* ������������Ҫ�����Ĵ��ڡ�
	* ������pScrollView����Ҫ�����Ĵ���ָ�룩��
	*/
	virtual void SetScrollView( IScrollView * pScrollView ) = 0;

	/*
	* ������֪ͨ������������С�仯��
	* ������nSize�����������С����nViewSize���ܹ�������󳤶ȣ���
	*/
	virtual void NotifyScrollSizeChanged( INT nSize, INT nViewSize ) = 0;

	/*
	* ������֪ͨ�����������λ�ñ仯��
	* ������nPos���µĹ���λ�ã���nViewSize���ܹ�������󳤶ȣ���
	*/
	virtual void NotifyScrollPosChanged( INT nPos, INT nViewSize ) = 0;
};

class IDrawItem
{
public:
	/*
	* ����������ÿһ��Item���������ҵ�λ�ã��洢��m_rect�С�
	* ������hDC�����ڼ��㣩��xPos�����x���꣩��yPos�����y���꣩��width�����ƿ�ȣ���height�����Ƹ߶ȣ���
	* ���أ�ÿһ��Itemʵ�ʵĳߴ硣
	*/
	virtual RECT CalcRect( HDC hDC, INT xPos, INT yPos, INT width = -1, INT height = -1 ) = 0;

	/*
	* ����������ÿһ��Item��
	* ������hDC�����ڻ��ƣ���xOffset��x���ƫ�ƣ���yOffset��y���ƫ�ƣ���
	*/
	virtual void Draw( HDC hDC, INT xOffset, INT yOffset, INT viewWidth, INT viewHeight ) = 0;

	/*
	* ����������ÿһ��Item��
	*/
	virtual void Destroy() = 0;
protected:
	RECT m_rect;
};

#endif