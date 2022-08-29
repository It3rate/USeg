#pragma once
#include <vector>
#include <memory>
#include <complex>

#include "Segment.h"
#include "Trait.h"


namespace umath
{
	class Library
	{
	private:
		std::vector<std::unique_ptr<Segment>> segments_{};
		std::vector<std::shared_ptr<Trait>> traits_{};
		
		Library() = default;
		~Library() = default;
	public:
		//Library(Library const&) = delete;
		//void operator=(Library const&) = delete;
		
		static Library& GetInstance() {
			static Library instance;
			return instance;
		}
		
		int AddSegment(double unit, double unot, int trait_index = 0);
		Trait* AddTrait(const LL ticks_per_unit, const LL min, const LL max);
	};
}

