#ifndef KEYBOARD_INCLUDED
#define KEYBOARD_INCLUDED

#include <Signals/Signal.h>

#include <Object.hpp>


namespace prx
{


	class Keyboard
	{
		public:
			Keyboard() { }
			Gallant::Signal0<void> SigQuit;
			Gallant::Signal1<enum DIRECTION> SigPlayerMove;
			void dispatchLastMoves();
	};


}


#endif
