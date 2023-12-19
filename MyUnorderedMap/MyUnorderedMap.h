#include <functional>
#include <concepts>
//structs

template<std::default_initializable Key, std::default_initializable T, class Hash = std::hash<Key>, class KeyEqual = std::equal_to<Key>, class Allocator = std::allocator<std::pair<const Key, T>>>
class MyUnorderedMap;

template<class V>
struct Item
{
	bool isEnd = false;
	V value;
	Item* next; //last in bucket points to next bucket or nullptr if this is the last bucket
};

template<class V>
struct Bucket
{
	int size=0;
	Item<V>* first=nullptr;
	Item<V>* last=nullptr;
	Item<V>* end=nullptr;

	Bucket() : end(new Item<V>) { end->isEnd = true; }

	bool isEmpty() { return first == nullptr; }

	Item<V>* push(V value)
	{
		Item<V>* item = new Item<V>;
		item->value = value;
		if (isEmpty())
		{
			first = item;
			last = item;
			item->next = end;
		}
		else
		{
			last->next = item;
			item->next = end;
			last = item;
		}
		size++;
		item->isEnd = false;
		return item;
	}

	Item<V>* find(V value)
	{
		if (!isEmpty())
		{
			Item<V>* ptr = first;
			while (!ptr->isEnd && ptr->value!=value)
			{
				ptr = ptr->next;
			}
			return ptr;
		}
		return end;
	}

	void erase(Item<V>* prev)
	{
		if (prev != end)
		{
			Item<V>* target = prev->next;
			prev->next = target->next;
			delete target;
		}
	}
};

template<class Iter, class NodeType>
struct ReturnType
{
	Iter position;
	bool inserted;
	NodeType node;
};



template<class V, bool is_const>
class UnorderedMapIterator
{
public:
	typedef std::ptrdiff_t difference_type;
	typedef V value_type;
	typedef std::conditional_t<is_const, const V, V>* pointer;
	typedef std::conditional_t<is_const, const V, V>& reference;
	typedef std::forward_iterator_tag iterator_category;

	typedef std::conditional_t<is_const, const Item<V>, Item<V>>* item_ptr;

	item_ptr it;

	friend UnorderedMapIterator<V, !is_const>;

	UnorderedMapIterator() :it(nullptr) {}
	UnorderedMapIterator(item_ptr it) : it(it) {}

	template<bool other>
	UnorderedMapIterator(const UnorderedMapIterator<V, other>& umit) noexcept requires (is_const >= other);
	template<bool other>
	UnorderedMapIterator(UnorderedMapIterator<V, other>&& umit);//requires (other==false)
	~UnorderedMapIterator() { it = nullptr; }

	template<bool other>
	UnorderedMapIterator<V, is_const>& operator=(const UnorderedMapIterator<V, other>& it2) requires (is_const>=other);
	template<bool other>
	UnorderedMapIterator<V, is_const>& operator=(UnorderedMapIterator<V, other>&& it2); //requires (other==false)
	template<bool other>
	bool operator==(const UnorderedMapIterator<V, other>& it2) const;

	reference operator*() const noexcept;
	pointer operator->() const noexcept;
	
	UnorderedMapIterator<V, is_const>& operator++() noexcept;
	UnorderedMapIterator<V, is_const> operator++(int) noexcept;
};

//iterator methods
template<class V, bool is_const>
template<bool other>
UnorderedMapIterator<V, is_const>::UnorderedMapIterator(const UnorderedMapIterator<V, other>& umit) noexcept 
requires (is_const >= other) : it(Item<V>())
{
	it->value=umit.it->value;
	it->next=umit.it->next;
}

template<class V, bool is_const>
template<bool other>
UnorderedMapIterator<V, is_const>::UnorderedMapIterator(UnorderedMapIterator<V, other>&& umit) : it(Item<V>()) //requires (other==false)
{
	it->value=umit.it->value;
	it->next=umit.it->next;
	umit.it=nullptr;
}

template<class V, bool is_const>
template<bool other>
UnorderedMapIterator<V, is_const>& UnorderedMapIterator<V, is_const>::operator=(const UnorderedMapIterator<V, other>& it2) requires (is_const>=other)
{
	if(&it2!=this)
	{
		it->value=it2.it->value;
		it->next=it2.it->next;
	}
	return *this;
}

template<class V, bool is_const>
template<bool other>
UnorderedMapIterator<V, is_const>& UnorderedMapIterator<V, is_const>::operator=(UnorderedMapIterator<V, other>&& it2) //requires (other==false)
{	
	it->value=it2.it->value;
	it->next=it2.it->next;
	it2.it=nullptr;
	return *this;
}

template<class V, bool is_const>
template<bool other>
bool UnorderedMapIterator<V, is_const>::operator==(const UnorderedMapIterator<V, other>& it2) const
{
	return (it->value==it2.it->value) && (it->next==it2.it->next);
}

template<class V, bool is_const>
UnorderedMapIterator<V, is_const>::reference UnorderedMapIterator<V, is_const>::operator*() const noexcept
{
	return it->value;
}

template<class V, bool is_const>
UnorderedMapIterator<V, is_const>::pointer UnorderedMapIterator<V, is_const>::operator->() const noexcept
{
	return &it->value;
}

template<class V, bool is_const>
UnorderedMapIterator<V, is_const>& UnorderedMapIterator<V, is_const>::operator++() noexcept
{
	it=it->next;
	return *this;
}

template<class V, bool is_const>
UnorderedMapIterator<V, is_const> UnorderedMapIterator<V, is_const>::operator++(int) noexcept
{
	UnorderedMapIterator tmp(it);
	it=it->next;
	return tmp;
}

static_assert(std::forward_iterator<UnorderedMapIterator<int, true>>);
static_assert(std::forward_iterator<UnorderedMapIterator<int, false>>);

template<std::default_initializable Key, std::default_initializable T, class Hash, class KeyEqual, class Allocator>
class MyUnorderedMap
{
	
	typedef Key key_type;
	typedef T mapped_type;
	typedef std::pair<const Key, T> value_type;
	typedef std::size_t size_type;
	typedef std::ptrdiff_t difference_type;
	typedef Hash hasher;
	typedef KeyEqual key_equal;
	typedef Allocator allocator_type;
	typedef value_type& refference;
	typedef const value_type& const_refference;
	typedef std::allocator_traits<Allocator>::pointer pointer;
	typedef std::allocator_traits<Allocator>::const_pointer const_pointer;

	typedef UnorderedMapIterator<value_type, false> iterator;
	typedef UnorderedMapIterator<value_type, true> const_iterator;

	typedef Item<value_type> node_type;
	typedef Bucket<value_type> bucket_type;
	typedef ReturnType<iterator, node_type> insert_return_type;

	static const size_type DEFAULT_BUCKET_COUNT = 7;
	size_type buckets_size=0;
	bucket_type* buckets=nullptr;
	node_type* before_begin=nullptr;
	node_type* past_the_last=nullptr;
	float max_load_factor = 1;

	void alloc_bucket_array(size_type size)
	{
		buckets = new bucket_type[size];
		buckets_size = size;
	}

	void release_bucket_array()
	{
		delete[] buckets;
		buckets_size = 0;
	}

	iterator find_item(key_type key)
	{
		size_type position = Hash(key);
		iterator itr = iterator(buckets[position].first);
		while (itr.it->value.first != key && !itr.it->isEnd) ++itr;
		return itr;
	}

	iterator insert_item(value_type nitem)
	{
		size_type position = Hash(nitem.first);
		iterator itr=iterator(buckets[position].push(nitem));
		return itr;
	}

	iterator erase_item(key_type key)
	{
		size_type position = Hash(key);
		iterator itr = iterator(buckets[position].first);
		while (itr.it->next->value.first != key && !itr.it->next->isEnd) ++itr;
		buckets[position].erase(itr.it);
		return itr;
	}
	
	MyUnorderedMap();// : bucket_size(DEFAULT_BUCKET_SIZE), buckets(new bucket_type[DEFAULT_BUCKET_SIZE]),
	
	template<class Iter>
	MyUnorderedMap(Iter first, Iter last, size_type bucket_count=DEFAULT_BUCKET_COUNT, const hasher& hash=Hash(), const key_equal& equal=KeyEqual(), const allocator_type& alloc=Allocator());

	MyUnorderedMap(const MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>& um);

	MyUnorderedMap(MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>&& um);

	MyUnorderedMap(std::initializer_list<value_type> il, size_type bucket_count = DEFAULT_BUCKET_COUNT, const hasher& hash = Hash(), const key_equal& equal = KeyEqual(), const allocator_type& alloc = Allocator());

	~MyUnorderedMap();

	MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>& operator=(const MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>& um2);
	MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>& operator=(MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>&& um2);
	MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>& operator=(std::initializer_list<value_type> il);
	allocator_type get_allocator() const noexcept;
	
};
