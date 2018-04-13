#include "TextWindow.h"
#include "HelperFunctions.h"

TextWindow::TextWindow()
{
}


TextWindow::~TextWindow()
{
}

void TextWindow::draw()
{
	Window::draw();// es una funcion conn override, la llama del padre. hay ocasiones q	ue si te sirve usar lo qe tu padre hizo. Ese es el formato.
	//early out (salida rapida, si no tengo anda que hacer, no ejecuto lo demas)
	if (!_isActive) return;
	COORD pos;
	DWORD nonImportant;
	HANDLE console = getConsoleHandle();
	int linesToDraw = (_currentLetter / _maxLineWidth) + 1;//division +1 * residuo
	pos.X = _x + 1;//te vas a parar para escribir en pos del objeto +1 en x
	for (int j = _scrollLine * _maxLineWidth, i = 0; j < _currentLetter; ++j)
	{
		if (!(j%_maxLineWidth) && j != _scrollLine * _maxLineWidth)
		{
			++i;
			pos.X = _x + 1;
		}
		if (i >= _maxScrollLines - 1) break;
		pos.Y = _y + 1 + i;
		++pos.X;
		SetConsoleCursorPosition(console, pos);
		//TODO : Terminar de entender
		WriteConsole(console, &_string.at(j), 1, &nonImportant, NULL);
	}
	if (!(_currentLetter % (_maxLineWidth)) && _autoScroll && _currentLetter)
	{
		++_scrollLine;
		Sleep(1000);
	}
	_currentLetter += _speed;
	if (_currentLetter >= _string.length()) _currentLetter = _string.length();
}

void TextWindow::update()
{
	DWORD numInputRead;//Bits bytes words 8bytes dword 16bytes
	GetNumberOfConsoleInputEvents(GetStdHandle(STD_INPUT_HANDLE), &numInputRead);
	if (numInputRead)//el nuemro de inputs
	{
		ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), _input, 32, &numInputRead);//agarra std input handle, va a ver cuantos inputs lee, almacena ciert numero,almacena los inputs, no el numerod e inpuits
		for (DWORD i = 0; i < numInputRead; ++i)
		{
			if (_input[i].EventType == KEY_EVENT)//ve el key que est[a apretado y hasce algo 
			{
				WORD keyC = _input[i].Event.KeyEvent.wVirtualKeyCode;
				bool keypressed = _input[i].Event.KeyEvent.bKeyDown;
				if (keyC == _scrollKey && !keypressed)
					++_scrollLine;
				if (keyC == _closeKey && !keypressed)
					_isActive = false;
				if (keyC == _upScroll && !keypressed)
					--_scrollLine;
				if (keyC == _downScroll && !keypressed)
					++_scrollLine;
			}
		}
	}
	if (_scrollLine == _maxScrollLines + 1 && _closeOnScrollEnd)
		_isActive = false;
}

void TextWindow::SetTextSpeed(const unsigned short & speed)//CONST Y & NO LVAS AMMODOFOCAR SU VALOR, LA COMPU LO PROCESA MAS RAPIDO
{
	_speed = speed;
}

void TextWindow::SetText(const std::string & text)
{
	_string = text;
	_currentLetter = 0;
	_scrollLine = 0;
	_maxLineWidth = _width - 3;//cuantos caracteres por linea. Tamanio de ventana menos margenes
	_maxScrollLines = (((_string.length() / _maxLineWidth) + 1) / _height) + 1;
}

void TextWindow::SetAutoScroll(const bool & val)
{
	_autoScroll = val;
}

void TextWindow::CloseOnScrollEnd(const bool & val)
{
	_closeOnScrollEnd = val;
}

void TextWindow::SetScrollKey(const Key & val)
{
	_scrollKey = val;
}

void TextWindow::SetCloseKey(const Key & val)
{
	_closeKey = val;
}

void TextWindow::SetUpScrollKey(const Key & val)
{
	_upScroll = val;
}

void TextWindow::SetDownScrollKey(const Key & val)
{
	_downScroll = val;
}
