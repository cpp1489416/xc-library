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
		using Iterator = typename TreeType::Iterator;

	public:
		Set() : mTree(TCompare())
		{

		}

	public:
		Iterator begin() { return GetBegin(); }
		Iterator end() { return GetEnd(); }

	public:
		Iterator GetBegin()
		{
			return mTree.GetBegin();
		}

		Iterator GetEnd()
		{
			return mTree.GetEnd();
		}

		SizeType GetSize() const
		{
			return mTree.GetSize();
		}

		bool IsEmpty() const
		{
			return mTree.IsEmpty();
		}

		void Clear()
		{
			mTree.Clear();
		}

		Iterator Insert(const TKey& value)
		{
			Pair<Iterator, bool> ans = mTree.InsertUnique(value);
			return ans.mFirst;
		}		

		bool Contains(const TKey& key) const
		{
			return mTree.Contains(key);
		}



	public:
		TreeType mTree;
	};

} XC_END_NAMESPACE_2;

#include <cstdlib>
#include <ctime>
#include <iostream>

XC_TEST_CASE(XC_SET_TEST)
{
	using namespace std;
	using namespace XC::Containers;

	std::cout << "begin set test" << std::endl;
	Set<int> set;
	for (int i = 0; i < 35; ++i)
	{
		set.Insert(rand() % 100);
	}

	//for (Set<int>::Iterator itr = set.GetBegin(); itr != set.GetEnd(); ++itr)
	for (auto itr = set.begin(); itr != set.end(); ++itr)//: set)
	{
		std::cout << *itr << " ";
	} 

	set.Insert(0);
	std::cout << "containss 0: "<<set.Contains(0) << std::endl;

	for (int i = 0; i < 100; ++i)
	{
		std::cout << set.Contains(i);
	}
	std::cout << std::endl;

	std::cout << "end set teset" << std::endl;
}
