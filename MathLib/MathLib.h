//
// MathLib.h
// Classix
//
// Copyright (C) 2012 Félix Cloutier
//
// This file is part of Classix.
//
// Classix is free software: you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.
//
// Classix is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
// A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with
// Classix. If not, see http://www.gnu.org/licenses/.
//

#ifndef __Classix__MathLib__
#define __Classix__MathLib__

#include "IAllocator.h"
#include "MachineState.h"
#include "SymbolType.h"

extern "C"
{
	namespace MathLib
	{
		struct Globals;
	}
	
	MathLib::Globals* LibraryLoad(Common::IAllocator* allocator);
	SymbolType LibraryLookup(MathLib::Globals* globals, const char* symbolName, void** symbol);
	void LibraryUnload(MathLib::Globals* globals);
	
	extern const char* LibrarySymbolNames[];
}

#endif /* defined(__Classix__MathLib__) */