//
// DummySymbolResolver.h
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

#ifndef __Classix__DummySymbolResolver__
#define __Classix__DummySymbolResolver__

#include "SymbolResolver.h"
#include <stdint.h>

namespace CFM
{
	class DummySymbolResolver : public SymbolResolver
	{
		uint32_t resolveTo;
		std::string fakePath;
		
	public:
		DummySymbolResolver(uint32_t resolveTo, const std::string& fakePath);
		
		virtual const std::string* FilePath() const override;
		virtual std::vector<std::string> CodeSymbolList() const override;
		virtual std::vector<std::string> DataSymbolList() const override;
		
		virtual ResolvedSymbol ResolveSymbol(const std::string& name) override;
		virtual std::vector<ResolvedSymbol> GetEntryPoints() override;
		
		virtual ~DummySymbolResolver() override;
	};
}

#endif /* defined(__Classix__DummySymbolResolver__) */
