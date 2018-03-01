#ifndef SIGNALS_INCLUDED
#define SIGNALS_INCLUDED

#include <Signals/Signal.h>

#include <Object.hpp>
#include <ObjectCollection.hpp>


namespace prx
{


	namespace Sig
	{


		Gallant::Signal0<void> Tick;
		Gallant::Signal0<void> Quit;
		Gallant::Signal1<ObjectCollection&> Collision;
		Gallant::Signal1<enum Direction> PlayerMove;


	}


}


#endif
