#pragma once

#include "../SyntaxSugars/SyntaxSugars.h"
#include "../Iterators/Iterators.h"
#include "../Memories/Allocators.h"
#include "Pair.h"
#include "../Iterators/Iterators.h"

XC_BEGIN_NAMESPACE_3(XC, Containers, Details)
{
	enum class RBTreeColorType : bool
	{
		Red = false, Black = true,
	};

	template <typename T>
	class RBTreeNode
	{
	public:
		using LinkType = RBTreeNode<T> *;
		using ColorType = RBTreeColorType;
		using BasePointer = RBTreeNode *;

	public:
		RBTreeNode * GetMinimum()
		{
			RBTreeNode * node = this;
			while (node->mLeft != nullptr)
			{
				node = node->mLeft;
			}

			return node;
		}

		RBTreeNode * GetMaximum()
		{
			RBTreeNode * node = this;
			while (node->mRight != nullptr)
			{
				node = node->mRight;
			}

			return node;
		}

	public:
		RBTreeNode * mParent;
		RBTreeNode * mLeft;
		RBTreeNode * mRight;
		RBTreeColorType mColor;
		T mValue;
	};

	template <typename T, typename TReference, typename TPointer>
	class RBTreeIterator
	{
	public:
		using ValueType = T;
		using Reference = TReference;
		using Pointer = TPointer;
		using Self = RBTreeIterator<T, TReference, TPointer>;
		using Iterator = RBTreeIterator<T, T &, T *>;
		using ConstantIterator = RBTreeIterator<T, const T &, const T *>;
		using LinkType = RBTreeNode<T> *;
		using IteratorCategory = Iterators::BidirectionalIteratorTag;
		using DifferenceType = xptrdiff;
		using Node = RBTreeNode<T>;

	public:
		RBTreeIterator() = default;

		RBTreeIterator(RBTreeNode<T> * node)
		{
			mNode = node;
		}

		RBTreeIterator(const Iterator & iterator)
		{
			mNode = iterator.mNode;
		}

		Self& operator = (const Self&) = default;

	public:
		void Increment()
		{
			if (mNode->mRight != nullptr)
			{
				mNode = mNode->mRight;
				while (mNode->mLeft != nullptr)
				{
					mNode = mNode->mLeft;
				}
			}
			else
			{
				Node * parent = mNode->mParent;
				while (mNode == parent->mRight)
				{
					mNode = parent;
					parent = parent->mParent;
				}

				if (mNode->mRight != parent) // header
				{
					mNode = parent;
				}
			}
		}

		void Decrement()
		{
			if (mNode->mColor == RBTreeColorType::Red && mNode->mParent->mParent == mNode)
			{
				mNode = mNode->mRight; // header 
			}
			else if (mNode->mLeft != nullptr)
			{
				Node * y = mNode->mLeft;
				while (y->mRight != nullptr)
				{
					y = y->mRight;
				}
				mNode = y;
			}
			else
			{
				Node * y = mNode->mParent;
				while (mNode == y->mLeft)
				{
					mNode = y;
					y = y->mParent;
				}
				mNode = y;
			}
		}

	public:
		Reference operator * () const
		{
			return mNode->mValue;
		}

		Pointer operator -> () const
		{
			return &(operator *());
		}

		Self & operator ++ ()
		{
			Increment();
			return *this;
		}

		Self & operator ++ (int)
		{
			Self ans = *this;
			++(*this);
			return ans;
		}

		Self & operator -- ()
		{
			Decrement();
			return *this;
		}

		Self & operator -- (int)
		{
			Self ans = *this;
			--(*this);
			return ans;
		}

		bool operator == (const Self& rhs) const
		{
			return mNode == rhs.mNode;
		}

		bool operator != (const Self& rhs) const
		{
			return !(*this == rhs);
		}

	public:
		Node* mNode;
	};

	template <typename TKey, typename TValue, typename TKeyOfValue, typename TCompare, typename TAllocator = XC::DefaultAllocator<TValue>>
	class RBTree // TKeyOfValue is a functor
	{
	public:
		using KeyType = TKey;
		using ValueType = TValue;
		using Pointer = TValue *;
		using ConstantPointer = const ValueType *;
		using Reference = ValueType &;
		using ConstantReference = const ValueType &;
		using SizeType = xsize;
		using DifferenceType = xptrdiff;
		using VoidPointer = void *;
		using Node = RBTreeNode<ValueType>;
		using LinkType = Node *;
		using ConstantIterator = RBTreeIterator<ValueType, ConstantReference, ConstantPointer>;
		using Iterator = RBTreeIterator<ValueType, Reference, Pointer>;
		using Self = RBTree<TKey, TValue, TKeyOfValue, TCompare, TAllocator>;

		// allocators :
		using RBTreeNodeAllocator = DefaultAllocator<Node>;

	public:
		RBTree(const TCompare & compare = TCompare()) :
			mCountNodes(0), mKeyCompare(compare)
		{
			Initialize();
		}

		RBTree(const typename Self&) = delete;

		virtual ~RBTree()
		{
			Clear();
			PutNode(mHeader);
		}

		Self& operator = (const Self & rhs)
		{
			return *this;
		}

	public:
		ConstantIterator begin() const
		{
			return GetBegin();
		}

		Iterator begin()
		{
			return GetBegin();
		}

		ConstantIterator end() const
		{
			return GetEnd();
		}

		Iterator end()
		{
			return GetEnd();
		}

	public:
		ConstantIterator GetBegin() const
		{
			return GetMostLeft();
		}

		Iterator GetBegin()
		{
			return GetMostLeft();
		}

		ConstantIterator GetEnd() const
		{
			return mHeader;
		}

		Iterator GetEnd()
		{
			return mHeader;
		}

		xsize GetSize() const
		{
			return mCountNodes;
		}

		bool IsEmpty() const
		{
			return GetSize() == 0;
		}

	protected:
		Node* GetNode()
		{
			return RBTreeNodeAllocator::Allocate();
		}

		void PutNode(Node* node)
		{
			RBTreeNodeAllocator::Deallocate(node);
		}

		Node* CreateNode(const TValue & value)
		{
			LinkType ans = GetNode();
			Memories::Construct(&ans->mValue, value);
			return ans;
		}

		Node* CloneNode(Node* node)
		{
			Node* ans = CreateNode(node->mValue);
			ans->mColor = node->mColor;
			ans->mLeft = nullptr;
			ans->mRight = nullptr;
			return ans;
		}

		void DestroyNode(Node* node)
		{
			Memories::Destroy(&node->mValue);
			PutNode(node);
		}

		// node functions, static like
		TValue& GetValue(Node* node) const
		{
			return node->mValue;
		}

		Node* & GetLeft(Node* node) const
		{
			return node->mLeft;
		}

		Node* & GetRight(Node* node) const
		{
			return node->mRight;
		}

		const TKey& GetKey(Node* node) const
		{
			return TKeyOfValue()(GetValue(node));
		}

		Node* & GetParent(Node* node) const
		{
			return node->mParent;
		}

		RBTreeColorType& GetColor(Node* node) const
		{
			return node->mColor;
		}

		// global functions
		Node* & GetRoot() const
		{
			return mHeader->mParent;
		}

		Node* & GetMostLeft() const
		{
			return mHeader->mLeft;
		}

		Node* & GetMostRight() const
		{
			return mHeader->mRight;
		}

		Node* GetMaximum(Node* node) const
		{
			return node->GetMaximum();
		}

		Node* GetMinimum(Node* node) const
		{
			return node->GetMinimum();
		}

	private: public:
		void Initialize()
		{
			mHeader = GetNode();
			mHeader->mColor = RBTreeColorType::Red;
			GetRoot() = nullptr;
			GetMostLeft() = mHeader;
			GetMostRight() = mHeader;
		}

		void Clear()
		{

		}

		// insert functions
		Iterator InsertEqual(const TValue& value)
		{
			Node* y = mHeader;
			Node* x = GetRoot();
			while (x != nullptr)
			{
				y = x;
				x = mKeyCompare(TKeyOfValue()(value), GetKey(x)) ? GetLeft(x) : GetRight(x);
			}
			return Insert(x, y, value);
		}

		// bool claims if it is inserted success
		Pair<Iterator, bool> InsertUnique(const TValue& value)
		{
			Node* y = mHeader;
			Node* x = GetRoot();
			bool comp = true;
			while (x != nullptr)
			{
				y = x;
				comp = mKeyCompare(TKeyOfValue()(value), GetKey(x));
				x = comp ? GetLeft(x) : GetRight(x);
			}

			Iterator j = Iterator(y);
			if (comp)
			{
				if (j == GetBegin())
				{
					return Pair<Iterator, bool>(Insert(x, y, value), true);
				}
				else
				{
					--j;
				}
			}
			if (mKeyCompare(GetKey(j.mNode), TKeyOfValue()(value)))
			{
				return Pair<Iterator, bool>(Insert(x, y, value), true);
			}
			else
			{
				return Pair<Iterator, bool>(j, false);
			}
		}

		void Erase(Iterator position)
		{

		}

		Iterator Insert(Node* x, Node* y, const TValue& value)
		{
			Node* z = nullptr;
			if (y == mHeader || x != nullptr || mKeyCompare(TKeyOfValue()(value), GetKey(y)))
			{
				z = CreateNode(value);
				GetLeft(y) = z;
				if (y == mHeader)
				{
					GetRoot() = z;
					GetMostRight() = z;
				}
				else if (y == GetMostLeft())
				{
					GetMostLeft() = z;
				}
			}
			else
			{
				z = CreateNode(value);
				GetRight(y) = z;
				if (y == GetMostRight())
				{
					GetMostRight() = z;
				}
			}

			GetParent(z) = y;
			GetLeft(z) = nullptr;
			GetRight(z) = nullptr;

			Rebalance(z, mHeader->mParent);
			++mCountNodes;
			return Iterator(z);
		}

		ConstantIterator Find(const TKey& key) const
		{
			Node* y = mHeader; // y is greaterequal than key
			Node* x = GetRoot();
			while (x != nullptr)
			{
				if (!mKeyCompare(GetKey(x), key))
				{
					y = x;
					x = GetLeft(x);
				}
				else
				{
					x = GetRight(x);
				}
			}

			ConstantIterator j = ConstantIterator(y);
			return j == GetEnd() || mKeyCompare(key, GetKey(j.mNode)) ? GetEnd() : j; // key cannot greater than node's key
		}

		Iterator Find(const TKey& key)
		{
			Node* y = mHeader; // y is greaterequal than key
			Node* x = GetRoot();
			while (x != nullptr)
			{
				if (!mKeyCompare(GetKey(x), key))
				{
					y = x;
					x = GetLeft(x);
				}
				else
				{
					x = GetRight(x);
				}
			}

			Iterator j = Iterator(y);
			return j == GetEnd() || mKeyCompare(key, GetKey(j.mNode)) ? GetEnd() : j; // key cannot greater than node's key
		}

		ConstantIterator GetLowerBoound(const TKey& key) const
		{
			Node* y = mHeader; // y is greaterequal than key
			Node* x = GetRoot();
			while (x != nullptr)
			{
				if (!mKeyCompare(GetKey(x), key))
				{
					y = x;
					x = GetLeft(x);
				}
				else
				{
					x = GetRight(x);
				}
			}

			return ConstantIterator(x);
		}

		Iterator GetLowerBound(const TKey& key)
		{
			Node* y = mHeader; // y is greaterequal than key
			Node* x = GetRoot();
			while (x != nullptr)
			{
				if (!mKeyCompare(GetKey(x), key))
				{
					y = x;
					x = GetLeft(x);
				}
				else
				{
					x = GetRight(x);
				}
			}

			return Iterator(x);
		}

		ConstantIterator GetUpperBound(const TKey& key) const
		{
			Node* y = mHeader; // y is less than key
			Node* x = GetRoot();
			while (x != nullptr)
			{
				if (!mKeyCompare(GetKey(x), key))
				{
					x = GetLeft(x);
				}
				else
				{
					y = x;
					x = GetRight();
				}
			}

			return ConstantIterator(x);
		}

		Iterator GetUpperBound(const TKey& key)
		{
			Node* y = mHeader; // y is less than key
			Node* x = GetRoot();
			while (x != nullptr)
			{
				if (!mKeyCompare(GetKey(x), key))
				{
					x = GetLeft(x);
				}
				else
				{
					y = x;
					x = GetRight();
				}
			}

			return Iterator(x);
		}

		Pair<ConstantIterator, ConstantIterator> GetEqualRange(const TKey& key) const
		{
			return Pair<ConstantIterator, ConstantIterator>(GetLowerBound(key), GetUpperBound(key));
		}

		Pair<Iterator, Iterator> GetEqualRange(const TKey& key)
		{
			return Pair<Iterator, Iterator>(GetLowerBound(key), GetUpperBound(key));
		}

		xsize GetCount(const TKey& key) const
		{
			Pair<ConstantIterator, ConstantIterator> p = GetEqualRange(key);
			xsize n = 0;
			n = Iterators::GetDistance(p.mFirst, p.mSecond);
			return n;
		}

		bool Contains(const TKey& key) const
		{
			return Find(key) != GetEnd();
		}

	protected:
		void Rebalance(Node* x, Node* & root)
		{
			x->mColor = RBTreeColorType::Red;
			while (x != root && x->mParent->mColor == RBTreeColorType::Red)
			{
				if (x->mParent == x->mParent->mParent->mLeft)
				{
					Node* y = x->mParent->mParent->mRight;
					if (y != nullptr && y->mColor == RBTreeColorType::Red)
					{
						x->mParent->mColor = RBTreeColorType::Black;
						y->mColor = RBTreeColorType::Black;
						x->mParent->mParent->mColor = RBTreeColorType::Red;
						x = x->mParent->mParent;
					}
					else
					{
						if (x == x->mParent->mRight)
						{
							x = x->mParent;
							LeftRotate(x, root);
						}
						x->mParent->mColor = RBTreeColorType::Black;
						x->mParent->mParent->mColor = RBTreeColorType::Red;
						RightRotate(x->mParent->mParent, root);
					}
				}
				else
				{
					Node* y = x->mParent->mParent->mLeft;
					if (y != nullptr && y->mColor == RBTreeColorType::Red)
					{
						x->mParent->mColor = RBTreeColorType::Black;
						y->mColor = RBTreeColorType::Black;
						x->mParent->mParent->mColor = RBTreeColorType::Red;
						x = x->mParent->mParent;
					}
					else
					{
						if (x == x->mParent->mLeft)
						{
							x = x->mParent;
							RightRotate(x, root);
						}
						x->mParent->mColor = RBTreeColorType::Black;
						x->mParent->mParent->mColor = RBTreeColorType::Red;
						LeftRotate(x->mParent->mParent, root);
					}
				}
			}
			root->mColor = RBTreeColorType::Black;
		}

		Node* EraseRebalance(Node* node, Node* & root, Node* & mostLeft, Node* & mostRight)
		{
			Node* z = node;
			Node* y = z;
			Node* x = nullptr;
			Node* xParent = nullptr;
			if (y->mLeft == nullptr)
			{
				x = y->mRight;
			}
			else
			{
				if (y->mRight == nullptr)
				{
					x = y->mLeft;
				}
				else
				{
					y = y->mRight;
					while (y->mLeft != nullptr)
					{
						y = y->mLeft;
					}
					x = y->mRight;
				}
			}

			if (y != z)
			{
				z->mLeft->mParent = y;
				y->mLeft = z->mLeft;
				if (y != z->mRight)
				{
					xParent = y->mParent;
					if (x != nullptr)
					{
						x->mParent = y->mParent;
					}
					y->mParent->mLeft = x;
					y->mRight = z->mRight;
					z->mRight->mParent = y;
				}
				else
				{
					xParent = y;
				}

				if (root == z)
				{
					root = y;
				}
				else if (z->mParent->mLeft == z)
				{
					z->mParent->mLeft = y;
				}
				else
				{
					z->mParent->mRight = y;
				}

				y->mParent = z->mParent;
				Algorithms::Swap(y->mColor, z->mColor);
				y = z;
			}
			else
			{
				xParent = y->mParent;
				if (x != nullptr)
				{
					x->mParent = y->mParent;
				}

				if (root == z)
				{
					root = x;
				}
				else
				{
					if (z->mParent->mLeft == z)
					{
						z->mParent->mLeft = x;
					}
					else
					{
						z->mParent->mRight = x;
					}
				}

				if (mostLeft == z)
				{
					if (z->mRight == nullptr)
					{
						mostLeft = z->mParent;
					}
					else
					{
						mostLeft = x->GetMinimum();
					}
				}

				if (mostRight == z)
				{
					if (z->mLeft == nullptr)
					{
						mostRight = z->mParent;
					}
					else
					{
						mostRight = x->GetMaximum();
					}
				}
			}

			if (y->mColor != RBTreeColorType::Red)
			{
				while (x != root && (x == nullptr || x->mColor == RBTreeColorType::Black))
				{
					if (x == xParent->mLeft)
					{
						Node* w = xParent->mRight;
						if (w->mColor == RBTreeColorType::Red)
						{
							w->mColor = RBTreeColorType::Black;
							xParent->mColor = RBTreeColorType::Red;
							LeftRotate(xParent, root);
							w = xParent->mRight;
						}

						if ((w->mLeft == nullptr || w->mLeft->mColor == RBTreeColorType::Black)
							&& (w->mRight == 0 || w->mRight->mColor == RBTreeColorType::Black)
							)
						{
							w->mColor = RBTreeColorType::Red;
							x = xParent;
							xParent = xParent->mParent;
						}
						else
						{
							if (w->mRight == nullptr || w->mRight->mColor == RBTreeColorType::Black)
							{
								if (w->mLeft != nullptr)
								{
									w->mLeft->mColor = RBTreeColorType::Black;
								}
								w->mColor = RBTreeColorType::Red;
								RightRotate(w, root);
								w = xParent->mRight;
							}
							w->mColor = xParent->mColor;
							xParent->mColor = RBTreeColorType::Black;
							if (w->mRight != nullptr)
							{
								w->mRight->mColor = RBTreeColorType::Black;
							}
							LeftRotate(xParent, root);
							break;
						}
					}
					else
					{
						Node* w = xParent->mLeft;
						if (w->mColor == RBTreeColorType::Red)
						{
							w->mColor = RBTreeColorType::Black;
							xParent->mColor = RBTreeColorType::Red;
							RightRotate(xParent, root);
							w = xParent->mLeft;
						}

						if ((w->mRight == nullptr || w->mRight->mColor == RBTreeColorType::Black) &&
							(w->mLeft == nullptr || w->mLeft->mColor == RBTreeColorType::Black)
							)
						{
							w->mColor = RBTreeColorType::Red;
							x = xParent;
							xParent = xParent->mParent;
						}
						else
						{
							if (w->mLeft == nullptr
								|| w->mLeft->mColor = RBTreeColorType::Black
								)
							{
								if (w->mRight != nullptr)
								{
									w->mRight->mColor = RBTreeColorType::Black;
								}
								w->mColor = RBTreeColorType::Red;
								LeftRotate(w, root);
								w = xParent->mLeft;
							}
							w->mColor = xParent->mColor;
							xParent->mColor = RBTreeColorType::Black;
							if (w->mLeft != nullptr)
							{
								w->mLeft->mColor = RBTreeColorType::Black;
							}
							RightRotate(xParent, root);
							break;
						}
					}
				}

				if (x != nullptr)
				{
					x->mColor = RBTreeColorType::Black;
				}
			}
			return y;
		}

		void LeftRotate(Node* x, Node* & root)
		{
			Node* y = x->mRight;
			x->mRight = y->mLeft;
			if (y->mLeft != nullptr)
			{
				y->mLeft->mParent = x;
			}
			y->mParent = x->mParent;
			if (x == root)
			{
				root = y;
			}
			else if (x == x->mParent->mLeft)
			{
				x->mParent->mLeft = y;
			}
			else
			{
				x->mParent->mRight = y;
			}
			y->mLeft = x;
			x->mParent = y;
		}

		void RightRotate(Node* x, Node* & root)
		{
			Node* y = x->mLeft;
			x->mLeft = y->mRight;
			if (x->mRight != nullptr)
			{
				y->mRight->mParent = x;
			}
			y->mParent = x->mParent;
			if (x == root)
			{
				root = y;
			}
			else if (x == x->mParent->mRight)
			{
				x->mParent->mRight = y;
			}
			else
			{
				x->mParent->mLeft = y;
			}
			y->mRight = x;
			x->mParent = y;
		}

	private: public:
		xsize mCountNodes;
		Node* mHeader;
		TCompare mKeyCompare;
	};

} XC_END_NAMESPACE_3;

#include <cstdlib>
#include <iostream>
#include <ctime>
#include "../Functors/Functors.h"

XC_BEGIN_NAMESPACE_1(XC_RBTREE_TEST)
{
	using namespace std;
	using namespace XC::Containers::Details;
	using namespace XC::Functors;

	class KeyOfValue
	{
	public:
		const int& operator () (const int& value) const
		{
			return value;
		}
	};

	class Compare
	{
	public:
		bool operator () (const int& lhs, const int& rhs) const
		{
			return lhs > rhs;
		}
	};

	using Tree = RBTree<int, int, KeyOfValue, Less<int> >;

	template <typename T>
	void Print(T & t)
	{
		std::cout << "gerg ";
		for (auto itr = t.begin(); itr != t.end(); ++itr)// : t)// : t)
		{
			std::cout << *itr << " ";
		}
		std::cout << std::endl;
	}

	XC_TEST_CASE(FSGEIWEG)
	{
		srand(time(nullptr));
		std::cout << std::endl;
		std::cout << "Begin RBTree test" << std::endl;

		// Less compare;
		Tree tree;
		Tree::Iterator begin = tree.GetBegin();
		for (int i = 0; i < 100; ++i)
		{
			tree.InsertUnique(rand() % 100);
		}
		Print(tree);
		std::cout << "end RBTree test" << std::endl;
	}

} XC_END_NAMESPACE_1;