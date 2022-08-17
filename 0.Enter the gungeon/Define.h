#pragma once

#ifndef __DEFINE_H__
#define __DEFINE_H__

#define WINCX	1200
#define WINCY	800

#define SAFE_DELETE(p) if(p) { delete p; p = nullptr; }

#define OBJ_NOEVENT		0
#define OBJ_DEAD		1
#define OBJ_NOTSUMMON   2

#define PI	3.141592f


#define VK_ONE		0x31
#define VK_TWO		0x32
#define VK_THREE	0x33
#define VK_FOUR		0x34
#define VK_FIVE		0x35
#define VK_SIX		0x36
#define VK_SEVEN	0x37
#define VK_EIGHT	0x38
#define VK_NINE		0x39


#define TILECX		48
#define TILECY		48

#define TILEX	274
#define TILEY	255



#define MAPCX  9846
#define MAPCY  9177




#endif // !__DEFINE_H__
