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
	Bucket<V>* prev_bucket=nullptr;

	Bucket() : end(new Item<V>) { end->isEnd = true; first = end; last = end; }

	~Bucket()
	{
		Item<V>* ptr = first;
		while (!ptr->isEnd)
		{
			Item<V>* next = ptr->next;
			delete ptr;
			ptr = next;
		}
		delete ptr;
		size = 0;
	}

	bool isEmpty() { return first == end; }

	std::pair<Item<V>*, bool> push(V value)
	{
		std::pair<Item<V>*, bool> result;

		if (find(value) != end)
		{
			result.first = end;
			result.second = false;
			return result;
		}
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
		result.first = item;
		result.second = true;
		return result;
	}

	std::pair<Item<V>*, bool> push(Item<V>* item)
	{
		std::pair<Item<V>*, bool> result;

		if (find(item->value) != end)
		{
			result.first = end;
			result.second = false;
			return result;
		}
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
		result.first = item;
		result.second = true;
		return result;
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
		if (prev->next != end)
		{
			Item<V>* target = prev->next;
			prev->next = target->next;
			delete target;
			size--;
		}
	}
};

/*template<class Iter, class NodeType>
struct ReturnType
{
	Iter position;
	bool inserted;
	NodeType node;
};*/



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
public:	
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
	typedef std::pair<iterator, bool> insert_return_type;

	
	//MyUnorderedMap();
	// : bucket_size(DEFAULT_BUCKET_SIZE), buckets(new bucket_type[DEFAULT_BUCKET_SIZE]),
	MyUnorderedMap(size_type bucket_count=DEFAULT_BUCKET_COUNT, const hasher& hash = Hash(), const key_equal& equal = KeyEqual());

	MyUnorderedMap(iterator first, iterator last, size_type bucket_count=DEFAULT_BUCKET_COUNT, const hasher& hash=Hash(), const key_equal& equal=KeyEqual());

	MyUnorderedMap(const MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>& um);

	MyUnorderedMap(MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>&& um);

	MyUnorderedMap(std::initializer_list<value_type> il, size_type bucket_count = DEFAULT_BUCKET_COUNT, const hasher& hash = Hash(), const key_equal& equal = KeyEqual());

	~MyUnorderedMap();

	MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>& operator=(const MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>& um);
	MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>& operator=(MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>&& um);
	MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>& operator=(std::initializer_list<value_type> il);
	hasher hash_function() { return hasher(); }
	key_equal key_eq() { return key_equal(); }

	template<class... Args>
	insert_return_type emplace(Args&&... args) requires(std::constructible_from<T, Args...>);
	template<class... Args>
	iterator emplace_hint(const_iterator p, Args&&... args) requires(std::constructible_from<T, Args...>);
	template<class... Args>
	insert_return_type try_emplace(const key_type& key, Args&&... args) requires(std::constructible_from<T, Args...>) requires(std::constructible_from<T, Args...>);
	insert_return_type insert(const value_type& value);
	insert_return_type insert(value_type&& value);
	void insert(iterator first, iterator last);
	void insert(std::initializer_list<value_type> il); //insert(il.begin(), il.end());
	insert_return_type insert(node_type&& nh);
	insert_return_type insert_or_assign(const key_type& key, mapped_type&& obj);
	node_type* extract(key_type& key);
	node_type* extract(const_iterator itr);
	//template<std::default_initializable Key, std::default_initializable T, class Hash, class KeyEqual, class Allocator>
	void merge(MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>& other);
	size_type erase(key_type& key);
	iterator erase(iterator itr);
	iterator erase(iterator it1, iterator it2);
	void clear() noexcept;
	iterator find(key_type& key);
	const_iterator find(key_type& key) const;
	bool contains(key_type& key); //find(key)!=end()
	size_type bucket_count() { return bc; }
	size_type max_bucket_count() { return mbc; }
	size_type bucket(key_type& key) { return Hash(key); }
	size_type bucket_size(size_type n) { return buckets[n].size; }

	iterator begin(size_type n) { return iterator(buckets[n].first); }
	const_iterator begin(size_type n) const { return iterator(buckets[n].first); }
	iterator end(size_type n) { return iterator(buckets[n].end); }
	const_iterator end(size_type n) const { return iterator(buckets[n].end); }
	const_iterator cbegin(size_type n) const { return iterator(buckets[n].first); }
	const_iterator cend(size_type n) const { return iterator(buckets[n].end); }
	float load_factor() { return lf; }
	float max_load_factor() { return max_lf; }
	void max_load_factor(float nmlf) { max_lf = nmlf; }
	void rehash(size_type new_count);
	void reserve(size_type new_count);

	allocator_type get_allocator() const noexcept;
	
	iterator begin() noexcept;
	const_iterator cbegin() const noexcept;

	iterator end() noexcept;
	const_iterator cend() const noexcept;

	bool empty() const noexcept;
	size_type max_size() const noexcept;
	size_type size() const noexcept;

	//template<std::default_initializable Key, std::default_initializable T, class Hash, class KeyEqual, class Allocator>
	void swap(MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>& other);
	
	mapped_type& at(const key_type& key);
	mapped_type& operator[](const key_type& key);
	mapped_type& operator[](key_type&& key);
	const mapped_type& at(const key_type& key) const;
private:
	static const size_type DEFAULT_BUCKET_COUNT = 73;
	const hasher hash=Hash();
	const key_equal equal = KeyEqual();
	size_type bc=0;
	size_type mbc=DEFAULT_BUCKET_COUNT;
	bucket_type* buckets=nullptr;
	node_type* before_begin=nullptr;
	node_type* past_the_last=nullptr;
	size_type last_added_bucket=0;
	float max_lf = 1;
	float lf = 0;

	size_type getInd(const key_type& key) {size_type img=hash(key); return (img>0)? img%mbc : (-img)%mbc;}
	size_type getInd(value_type& val) {return getInd(val.first);}
	size_type getInd(node_type* item) {return getInd(item->value);}

	void alloc_bucket_array(size_type size)
	{
		buckets = new bucket_type[size];
		bc = 0;
		mbc = size;
	}

	template<class... Args>
	node_type* alloc_node(Args&&... args)
	{
		node_type* node=new node_type;
		node_type.value=value_type(std::forward<Args>(args)...);
		return node;
	}

	void release_bucket_array()
	{
		delete[] buckets;
		bc = 0;
		mbc = 0;
	}

	iterator find_item(const key_type& key)
	{
		size_type position = getInd(key);
		iterator itr = iterator(buckets[position].first);
		while (!equal(itr.it->value.first, key) && !itr.it->isEnd) ++itr;
		return itr;
	}

	template<class Insert>
	insert_return_type insert_item(Insert nitem)
	{
		size_type position = getInd(nitem);
		auto result=buckets[position].push(nitem);
		if (result.first == buckets[position].first)
		{
			bc++;
			if(bc==1)
			{
				before_begin->next=buckets[position].first;
			}
			buckets[last_added_bucket].end->next=bucket[position].first;
			bucket[position].prev_bucket=buckets[last_added_bucket];
			last_added_bucket=position;
			bucket[position].end->next=past_the_last;
		}
		return result;
	}

	
	iterator erase_item(key_type key)
	{
		size_type position = getInd(key);
		iterator itr = iterator(buckets[position].first);
		while (!equal(itr.it->next->value.first, key) && !itr.it->next->isEnd) ++itr;
		buckets[position].erase(itr.it);
		if (buckets[position].size == 0) 
		{
			bc--;
			if(buckets[position].prev_bucket==nullptr)
			{
				before_begin->next=buckets[position].end->next;
				
				if(buckets[position].end->next==past_the_last)
				{
					buckets[position].prev_bucket->end->next=past_the_last;
				}
			}
			else if(buckets[position].end->next==past_the_last)
			{
				buckets[position].prev_bucket->end->next=past_the_last;
			}
			else
			{
				buckets[position].prev_bucket->end->next=buckets[position].end->next;
			}
			
		}
		return itr;
	}
};


template<std::default_initializable Key, std::default_initializable T, class Hash, class KeyEqual, class Allocator>
MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::MyUnorderedMap(size_type bucket_count=DEFAULT_BUCKET_COUNT, const hasher& hash = Hash(), const key_equal& equal = KeyEqual()) : hash(hash), equal(equal)
{
	before_begin = new node_type;
	past_the_last = new node_type;
	alloc_bucket_array(bucket_count);
}


template<std::default_initializable Key, std::default_initializable T, class Hash, class KeyEqual, class Allocator>
MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::MyUnorderedMap(UnorderedMapIterator<std::pair<const Key, T>, false> first, UnorderedMapIterator<std::pair<const Key, T>, false> last, size_type bucket_count=DEFAULT_BUCKET_COUNT, const hasher& hash=Hash(), const key_equal& equal=KeyEqual()) : hash(hash), equal(equal)
{
	before_begin = new node_type;
	past_the_last = new node_type;
	alloc_bucket_array(bucket_count);
	insert(first, last);
}


template<std::default_initializable Key, std::default_initializable T, class Hash, class KeyEqual, class Allocator>
MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::MyUnorderedMap(const MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>& um) : hash(um.hash), equal(um.equal), bc(um.bc), mbc(um.mbc) 
{
	alloc_bucket_array(mbc);
	before_begin=new node_type;
	past_the_last=new node_type;
	insert(um.begin(), um.end());
	mlf=um.mlf;
	lf=um.lf;
}


template<std::default_initializable Key, std::default_initializable T, class Hash, class KeyEqual, class Allocator>
MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::MyUnorderedMap(MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>&& um) : hash(um.hash), equal(um.equal), bc(um.bc), mbc(um.mbc)
{
	before_begin=um.before_begin;
	past_the_last = um.past_the_last;
	buckets=um.buckets;
	mlf=um.mlf;
	lf=um.lf;
	last_added_bucket=um.last_added_bucket;
	um.buckets=nullptr;
	um.before_begin=nullptr;
	um.past_the_last=nullptr;
}

template<std::default_initializable Key, std::default_initializable T, class Hash, class KeyEqual, class Allocator>
MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::MyUnorderedMap(std::initializer_list<value_type> il, size_type bucket_count = DEFAULT_BUCKET_COUNT, const hasher& hash = Hash(), const key_equal& equal = KeyEqual()) : hash(um.hash), equal(um.equal)
{
	before_begin = new node_type;
	past_the_last = new node_type;
	alloc_bucket_array(bucket_count);
	for(auto itr: il)
	{
		insert(*itr);
	}
}

template<std::default_initializable Key, std::default_initializable T, class Hash, class KeyEqual, class Allocator>
MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::~MyUnorderedMap()
{
	release_bucket_array();
	delete before_begin;
	delete past_the_last;
}


template<std::default_initializable Key, std::default_initializable T, class Hash, class KeyEqual, class Allocator>
MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>& MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::operator=(const MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>& um)
{
	if(this!=&um2)
	{
		hash=um.hash;
		equal=um.equal;
		release_bucket_array();
		alloc_bucket_array(um.mbc);
		insert(um.begin(), um.end());
		mlf=um.mlf;
		lf=um.lf;
	}
	return *this;

}
template<std::default_initializable Key, std::default_initializable T, class Hash, class KeyEqual, class Allocator>
MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>& MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::operator=(MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>&& um)
{
	release_bucket_array();
	hash=um.hash;
	equal=um.equal;
	bc=um.bc;
	mbc=um.mbc;
	buckets=um.buckets;
	before_begin=um.before_begin;
	past_the_last=um.past_the_last;
	mlf=um.mlf;
	lf=um.lf;
	last_added_bucket=um.last_added_bucket;
	um.buckets=nullptr;
	um.before_begin=nullptr;
	um.past_the_last=nullptr;
}

template<std::default_initializable Key, std::default_initializable T, class Hash, class KeyEqual, class Allocator>
MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>& MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::operator=(std::initializer_list<value_type> il)
{
	release_bucket_array();
	alloc_bucket_array(il.size());
	for(auto it: il) insert(*it);
	return *this;
}


template<std::default_initializable Key, std::default_initializable T, class Hash, class KeyEqual, class Allocator>
template<class... Args>
insert_return_type MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::emplace(Args&&... args) requires(std::constructible_from<T, Args...>)
{	
	node_type* node=alloc_node(std::forward<Args>(args)...);
	auto result=insert_item<node_type*>(node);
	if(!result.second)
	{
		delete node;
	}
	return result;
}

template<std::default_initializable Key, std::default_initializable T, class Hash, class KeyEqual, class Allocator>
template<class... Args>
iterator MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::emplace_hint(const_iterator p, Args&&... args) requires(std::constructible_from<T, Args...>)
{
	node_type* node=alloc_node(std::forward<Args>(args)...);
	if(getInd(p.it->value.first)==getInd(node->value.first))
	{
		//NO WARRANTY THAT DUPLICATE KEY WONT BE INSERTED
		node_type* next=p.it->next;
		p.it->next=node;
		node->next=next;
		return iterator(node);
	}
	else
	{
		auto result=emplace(std::forward<Args>(args)...);
		if(!result.second)
		{
			delete node;
			return end();
		}
		return iterator(result.first);
	}
}

template<std::default_initializable Key, std::default_initializable T, class Hash, class KeyEqual, class Allocator>
template<class... Args>
insert_return_type MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::try_emplace(const key_type& key, Args&&... args) requires(std::constructible_from<T, Args...>)
{
	node_type* node=alloc_node(key, std::forward<Args>(args)...);
	auto result=insert_item<node_type*>(node);
	if(!result.second)
	{
		delete node;
	}
	return result;
}


template<std::default_initializable Key, std::default_initializable T, class Hash, class KeyEqual, class Allocator>
insert_return_type MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::insert(const value_type& value)
{
	return insert_item<value_type>(value);
}

template<std::default_initializable Key, std::default_initializable T, class Hash, class KeyEqual, class Allocator>
insert_return_type MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::insert(value_type&& value)
{
	return insert_item<value_type&&>(value);	
}

template<std::default_initializable Key, std::default_initializable T, class Hash, class KeyEqual, class Allocator>
void MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::insert(UnorderedMapIterator<std::pair<const Key, T>, false> first, UnorderedMapIterator<std::pair<const Key, T>, false> last)
{
	iterator itr=first;
	while(itr!=last)
	{
		insert(itr.it->value);
		++itr;
	}
}

template<std::default_initializable Key, std::default_initializable T, class Hash, class KeyEqual, class Allocator>
void MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::insert(std::initializer_list<value_type> il)
{
	for(auto it: il)
	{
		insert(*it);
	}
}

template<std::default_initializable Key, std::default_initializable T, class Hash, class KeyEqual, class Allocator>
insert_return_type MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::insert(node_type&& nh)
{
	return insert(nh.value);
}

insert_return_type insert_or_assign(const key_type& key, mapped_type&& obj)
{
	size_type position=hash(key);
	iterator result=iterator(buckets[position].find(value_type(key, obj)));
	if(result.it->isEnd)
	{
		//can be some problems with moving, but it's gonna be tested later
		return insert(value_type(key, obj));
	}
	result.it->value.second=std::move(obj);
	return insert_return_type(result, true);
}








