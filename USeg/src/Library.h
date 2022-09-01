#pragma once
#include <vector>
#include <memory>
#include <complex>
#include <unordered_map>
#include "Trait.h"


namespace umath
{
	class Library
	{
	private:
		inline static int traitCounter_ = 1;
		std::unordered_map<int, std::unique_ptr<Trait>> traitMap_;
		
		Library() = default;
		~Library() = default;
	public:
		Library(const Library&) = delete;
		Library(Library&&) = delete; 
		
		static Library& GetInstance() {
			static Library instance;
			return instance;
		}
		
		Trait* AddTrait(const LL ticks_per_unit, const LL positive_extent);
	};
}

