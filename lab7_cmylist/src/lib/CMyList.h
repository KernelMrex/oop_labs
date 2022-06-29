#ifndef CMYLIST_H
#define CMYLIST_H

#include <memory>
#include "CMyListException.h"

template <typename T>
class CMyList
{
	class BaseNode
	{
		friend class CMyList;
	public:
		BaseNode() noexcept
			: m_prev(nullptr)
			, m_next(nullptr)
		{}

		virtual T GetValue() const
		{
			throw CMyListException::CannotGetValueFromBaseNode();
		}

		virtual ~BaseNode() = default;

	protected:
		BaseNode* m_prev;
		BaseNode* m_next;
	};

	class Node : public BaseNode
	{
	public:
		explicit Node(const T& value) noexcept
			: m_value(value)
			, BaseNode()
		{
		}

		virtual T GetValue() const final
		{
			return m_value;
		}

	private:
		T m_value;
	};

	class Iterator
	{
		friend class CMyList;
		friend class Node;

	public:
		using iterator_category = std::random_access_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = BaseNode;
		using pointer = value_type*;
		using reference = value_type&;

		explicit Iterator(pointer ptr, bool final = false)
			: m_ptr(ptr)
			, m_final(final)
		{
		}

		reference operator*()
		{
			return *m_ptr;
		}

		pointer operator->()
		{
			return m_ptr;
		}

		Iterator& operator++()
		{
			if (m_ptr == nullptr || m_ptr->m_next == nullptr)
			{
				throw CMyListException::IteratorCannotBeChanged();
			}

			m_ptr = m_ptr->m_next;

			return *this;
		}

		Iterator operator++(T)
		{
			auto tmp = *this;
			++(*this);
			return tmp;
		}

		Iterator& operator--()
		{
			if (m_ptr == nullptr || m_ptr->m_prev == nullptr || m_ptr->m_prev->m_prev == nullptr)
			{
				throw CMyListException::IteratorCannotBeChanged();
			}

			m_ptr = m_ptr->m_prev;

			return *this;
		}

		Iterator operator--(T)
		{
			auto tmp = *this;
			--(*this);
			return tmp;
		}

		friend bool operator==(const Iterator& a, const Iterator& b)
		{
			return a.m_ptr == b.m_ptr;
		};

		friend bool operator!=(const Iterator& a, const Iterator& b)
		{
			return a.m_ptr != b.m_ptr;
		};

	private:
		pointer m_ptr;
		bool m_final;
	};

public:
	CMyList()
	try
		: m_head(nullptr)
		, m_tail(nullptr)
		, m_size(0)
	{
		m_head = new BaseNode();
		m_tail = new BaseNode();
		m_head->m_next = m_tail;
	}
	catch (...)
	{
		delete m_head;
		delete m_tail;
	}

	using iterator = Iterator;

	iterator begin()
	{
		return Iterator(m_head->m_next);
	}

	iterator end()
	{
		return Iterator(m_tail);
	}

	std::reverse_iterator<iterator> rbegin()
	{
		return std::reverse_iterator<iterator>(end());
	}

	std::reverse_iterator<iterator> rend()
	{
		return std::reverse_iterator<iterator>(begin());
	}

	void Insert(const iterator& it, T value)
	{
		Node* pNewNode = new Node(value);

		m_size++;

		auto pCurrNode = it.m_ptr;

		if (m_head->m_next == m_tail)
		{
			pNewNode->m_prev = m_head;
			pNewNode->m_next = m_tail;
			m_head->m_next = pNewNode;
			m_tail->m_prev = pNewNode;
			return;
		}

		pNewNode->m_next = pCurrNode;
		pNewNode->m_prev = pCurrNode->m_prev;

		pCurrNode->m_prev->m_next = pNewNode;
		pCurrNode->m_prev = pNewNode;
	}

	void Delete(const iterator& it)
	{
		if (it.m_ptr == nullptr)
		{
			throw CMyListException::IteratorCannotBeChanged();
		}

		m_size--;

		auto pCurrNode = it.m_ptr;
		auto pPrevNode = pCurrNode->m_prev;
		auto pNextNode = pCurrNode->m_next;

		if (pPrevNode != nullptr)
		{
			pPrevNode->m_next = pNextNode;
		}
		else
		{
			m_head = pNextNode;
		}

		if (pNextNode != nullptr)
		{
			pNextNode->m_prev = pPrevNode;
		}
		else
		{
			m_tail = pPrevNode;
		}

		delete pCurrNode;
	}

	void PushFront(T value)
	{
		Insert(begin(), value);
	}

	void PushBack(T value)
	{
		Insert(end(), value);
	}

	std::size_t GetSize()
	{
		return m_size;
	}

	bool IsEmpty()
	{
		return m_head->m_next == m_tail;
	}

private:
	BaseNode* m_head;
	BaseNode* m_tail;
	std::size_t m_size;
};

#endif // CMYLIST_H
