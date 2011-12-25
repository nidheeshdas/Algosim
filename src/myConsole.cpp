#include <iterator>
#include <mgrx.h>
#include <mgrxkeys.h>
#include <fstream>
#include <sstream>
#include "LibAlgoSim.h"
using namespace std;

void myConsole::Init(int x, int y)
{
	console_width = x;
	console_height = y;

	GrSetMode(GR_width_height_graphics, console_width, console_height);

	gto.txo_font = &GrFont_PC8x16;//&GrDefaultFont;
	gto.txo_fgcolor.v = GrWhite();
	gto.txo_bgcolor.v = GrNOCOLOR;
	//gto.txo_bgcolor.v = GrBlack();
	gto.txo_direct = GR_TEXT_RIGHT;
	gto.txo_xalign = GR_ALIGN_LEFT;
	gto.txo_yalign = GR_ALIGN_TOP;
	gto.txo_chrtype = GR_BYTE_TEXT;
	GrEventInit();
}
myConsole::~myConsole()
{
	GrEventUnInit();
}
myConsole::myConsole(myConsole& cpy)
{
	console_width = cpy.console_width;
	console_height = cpy.console_height;
	gto = cpy.gto;
}
void myConsole::setXY(int x, int y)
{
	curx = x;
	cury = y;
	currXY.x = x;
	currXY.y = y;
}
void myConsole::print(int x, int y)
{
	pt::scopelock sp1(gcsetxy);
	curx = x;
	cury = y;
	PTYPES_NAMESPACE::scopelock sp(xcomm);
	printf(str());
	clear();
	clean();
}
void myConsole::print()
{
	pt::scopelock sp1(gcsetxy);
	PTYPES_NAMESPACE::scopelock sp(xcomm);
	printf(str());
	clear();
	clean();
}

void myConsole::printf(string buf)
{
	for (unsigned int i = 0; i < buf.length(); i++)
		printchar(buf[i]);
}
void myConsole::printAtXY(string buf, int x, int y)
{
	GrDrawString(static_cast<void*> (const_cast<char*> (buf.c_str())), buf.length(), x, y, &gto);

	/*point temp(curx, cury);
	 setXY(x, y);
	 printf(buf);
	 setXY(temp.x, temp.y);
	 */
}
void myConsole::printchar(int c)
{
	if ((curx + GrCharWidth(c, &gto)) > GrMaxX())
	{
		curx = 0;
		cury += GrCharHeight(c, &gto);
	}
	else
	{
		if (c == '\n' || c == '\r')
		{
			curx = 0;
			cury += GrCharHeight(c, &gto);
		}
		else if (c == '\r')
		{
		}
		else
		{

			GrDrawChar(c, curx, cury, &gto);
			curx += GrCharWidth(c, &gto);
		}
	}
}
void myConsole::DrawImage(int ltx, int lty, int rbx, int rby, int i_type, const char * addr)
{
	GrContext *subContext = GrCreateSubContext(ltx, lty, rbx, rby, NULL, NULL);
	if (i_type == I_JPG)
		GrLoadContextFromJpeg(subContext, const_cast<char*> (addr), 1);
	else if (i_type == I_PNM_BUFFER)
		GrLoadContextFromPnmBuffer(subContext, addr);
	else if (i_type == I_PNM)
		GrLoadContextFromPnm(subContext, const_cast<char*> (addr));
}
void myConsole::clrscr()
{
	gc.clean();
	GrSetContext(NULL);
	GrFilledBox(0, 0, console_width, console_height, GrBlack());
	GrClearScreen(GrBlack());
}
void myConsole::clearArea(int x1, int y1, int x2, int y2)
{
	GrSetContext(NULL);
	GrFilledBox(x1, y1, x2, y2, GrBlack());
}
void myConsole::clean()
{
	str("");
}
unsigned short int myConsole::KeyRead()
{
	do
	{
		xcomm.lock();
		GrEventWaitKeyOrClick(&ev);
		xcomm.unlock();
	} while (ev.type != 1);
	return ev.p1;
}
string myConsole::scan()
{
	string s;
	do
	{
		xcomm.lock();
		GrEventWaitKeyOrClick(&ev);
		xcomm.unlock();
		if (ev.type == 1)
		{
			printchar(ev.p1);
			s += ev.p1;
		}
	} while (!(ev.type == 1 && ev.p1 == 13));
	string::iterator it = s.end();
	--it;
	s.erase(it);
	return s;
}
void myConsole::EventFlush()
{
	GrEventFlush();
}
