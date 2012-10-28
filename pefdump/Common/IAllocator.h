//
//  IAllocator.h
//  pefdump
//
//  Created by Félix on 2012-10-24.
//  Copyright (c) 2012 Félix. All rights reserved.
//

#ifndef __pefdump__IAllocator__
#define __pefdump__IAllocator__

#include <cstdint>
#include <cstddef>

namespace Common
{
	// we're not using C++ allocators because we're really more interested in creating big flat memory zones
	// than actualy creating objects; and besides, we don't want to virally add templates to anything that needs
	// to allocate memory.
	class IAllocator
	{
	public:
		virtual const uint8_t* GetBaseAddress() = 0;
		virtual uint8_t* Allocate(size_t size) = 0;
		virtual void Deallocate(void* address) = 0;
		virtual ~IAllocator();
	};
}

#endif /* defined(__pefdump__IAllocator__) */