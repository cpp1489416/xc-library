#pragma once

#include "RBTree.h"
#include "../Functors/Functors.h"

XC_BEGIN_NAMESPACE_2(XC, Containers)
{
	template <typename TKey, typename TCompare = Functors::Less<TKey>, class TAllocator = DefaultAllocator<TKey> >
	class Set
	{
	public:
		using KeyType = TKey;
		using ValueType = TKey;
		using KeyCompare = TCompare;
		using ValueCompare = TCompare;
		using TreeType = Details::RBTree<KeyType, ValueType, Functors::Identity<ValueType>, KeyCompare, TAllocator>;
		using ConstantPointer = typename TreeType::ConstantPointer;
		using Pointer = typename TreeType::ConstantPointer;
		using ConstantReference = typename TreeType::ConstantReference;
		using Reference = typename TreeType::Reference;
		using SizeType = typename TreeType::SizeType;
		using DifferenceType = typename TreeType::DifferenceType;

	public:
		Set() : mTree(TCompare())
		{
			
		}

	public:
		TreeType mTree;
	};

} XC_END_NAMESPACE_2;

XC_TEST_CASE(afhofefjoeapjepajpae)
{
	using namespace XC::Containers;
	Set<int, XC::Functors::Greater<int> > set;
}