#include <functional>
#include <concepts>
#include <stdexcept>
#include <cmath>
//structs
#pragma once
template<std::default_initializable Key, std::default_initializable T, class Hash = std::hash<Key>, class KeyEqual = std::equal_to<Key>, class Allocator = std::allocator<std::pair<const Key, T>>>
class MyUnorderedMap;

template<class V>
struct Item
{
	bool isEnd = false;
	V value;
	Item* next=nullptr; //last in bucket points to next bucket or nullptr if this is the last bucket
	Item(V value = V(), Item* next=nullptr) : value(value), next(next) {}
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
		Item<V>* item = new Item<V>(value);
		/*item->value.first.first = value.first.first;
		item->value.first.second = value.first.second;
		item->value.second = value.second;*/
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
			while (!ptr->isEnd && ptr->value.first!=value.first)
			{
				ptr = ptr->next;
			}
			return ptr;
		}
		return end;
	}

	void erase(Item<V>* prev)
	{
		Item<V>* target = prev->next;
		prev->next = target->next;
		if (last == target)
		{
			last = prev;
			prev->next = end;
		}
		delete target;
		size -= 1;
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
	UnorderedMapIterator<V, is_const>& operator~() noexcept;
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
UnorderedMapIterator<V, is_const>::UnorderedMapIterator(UnorderedMapIterator<V, other>&& umit) : it(new Item<V>(umit.it->value, umit.it->next)) //requires (other==false)
{
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
	it->value.first.first=it2.it->value.first.first;
	it->value.first.second=it2.it->value.first.second;
	it->value.second=it2.it->value.second;
	it->next=it2.it->next;
	it2.it=nullptr;
	return *this;
}

template<class V, bool is_const>
template<bool other>
bool UnorderedMapIterator<V, is_const>::operator==(const UnorderedMapIterator<V, other>& it2) const
{
	return (it->value==it2.it->value)&&(it->next==it2.it->next);
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
	if (it != nullptr)
	{
		if (it->isEnd) it = it->next;
	}
	return *this;
}

//floating map iterator. float over end of buckets
template<class V, bool is_const>
UnorderedMapIterator<V, is_const>& UnorderedMapIterator<V, is_const>::operator~() noexcept
{
	it = it->next;
	/*if (it != nullptr)
	{
		if (it->isEnd) it = it->next;
	}*/
	return *this;
}

template<class V, bool is_const>
UnorderedMapIterator<V, is_const> UnorderedMapIterator<V, is_const>::operator++(int) noexcept
{
	UnorderedMapIterator tmp(it);
	it=it->next;
	if (it != nullptr)
	{
		if (it->isEnd) it = it->next;
	}
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
	hasher hash_function() const { return hasher(); }
	key_equal key_eq() const { return key_equal(); }

	template<class... Args>
	insert_return_type emplace(Args&&... args) requires(std::constructible_from<value_type, Args...>);
	template<class... Args>
	iterator emplace_hint(const_iterator p, Args&&... args) requires(std::constructible_from<value_type, Args...>);
	template<class... Args>
	insert_return_type try_emplace(const key_type& key, Args&&... args) requires(std::constructible_from<T, Args...>);

	insert_return_type insert(const value_type& value);
	insert_return_type insert(value_type&& value);
	void insert(iterator first, iterator last);
	void insert(std::initializer_list<value_type> il); //insert(il.begin(), il.end());
	insert_return_type insert(node_type&& nh);
	insert_return_type insert_or_assign(const key_type& key, mapped_type&& obj);

	node_type* extract(const key_type& key);
	node_type* extract(iterator itr);
	//template<std::default_initializable Key, std::default_initializable T, class Hash, class KeyEqual, class Allocator>
	
	//void merge(MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>& other);
	
	size_type erase(const key_type& key);
	iterator erase(iterator itr);
	iterator erase(iterator it1, iterator it2);
	void clear() noexcept;
	
	iterator find(const key_type& key, bool prev=false);
	const_iterator find(const key_type& key, bool prev=false) const;
	bool contains(const key_type& key) const; //find(key)!=end()
	
	size_type bucket_count() const { return bc; }
	size_type max_bucket_count() const { return mbc; }
	size_type bucket(const key_type& key) const { return getInd(key); }
	size_type bucket_size(size_type n) const { return buckets[n].size; }

	iterator begin(size_type n) { return iterator(buckets[n].first); }
	const_iterator begin(size_type n) const { return iterator(buckets[n].first); }
	iterator end(size_type n) { return iterator(buckets[n].end); }
	const_iterator end(size_type n) const { return iterator(buckets[n].end); }
	const_iterator cbegin(size_type n) const { return iterator(buckets[n].first); }
	const_iterator cend(size_type n) const { return iterator(buckets[n].end); }
	
	iterator begin() noexcept {return iterator(before_begin->next);}
	const_iterator cbegin() const noexcept {return const_iterator(before_begin->next);}

	iterator end() noexcept {return iterator(past_the_last);}
	const_iterator cend() const noexcept {return const_iterator(past_the_last);}

	float load_factor() const {return lf; }
	float max_load_factor() const { return max_lf; }
	void max_load_factor(float nmlf) { max_lf = nmlf; }
	
	//void rehash(size_type new_count);
	//void reserve(size_type new_count);
	//void swap(MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>& other);
	
	allocator_type get_allocator() const noexcept {return Allocator();}

	bool empty() const noexcept {return bc==0;}
	size_type max_size() const noexcept {return 100;}
	size_type size() const noexcept 
	{
		size_type sum=0;
		iterator itr=cbegin();
		while(itr!=cend())
		{
			sum+=buckets[getInd(itr)].size;
			itr=buckets[getInd(itr)].end->next;
		}
		return sum;
	}

	//template<std::default_initializable Key, std::default_initializable T, class Hash, class KeyEqual, class Allocator>
	
	mapped_type& at(const key_type& key)
	{
		iterator result=find_item(std::forward<const key_type&>(key));
		if(result.it->isEnd) throw std::invalid_argument("Error. No element with such key");
		return result.it->value.second;
	}
	mapped_type& operator[](const key_type& key) {return at(key);}
	mapped_type& operator[](key_type&& key) {return at(std::move(key));}
	const mapped_type& at(const key_type& key) const
	{
		const_iterator result=find_item(std::forward<key_type>(key));
		if(result.it->isEnd) throw std::invalid_argument("Error. No element with such key");
		return result.it->value.second;
	}

	static const size_type DEFAULT_BUCKET_COUNT = 7;
	hasher hash=Hash();
	key_equal equal = KeyEqual();
	size_type bc=0;
	size_type mbc=DEFAULT_BUCKET_COUNT;
	bucket_type* buckets=nullptr;
	node_type* before_begin=nullptr;
	node_type* past_the_last=nullptr;
	size_type last_added_bucket=-1;
	float max_lf = 3;
	float lf = 0;
private:
	size_type getInd(const key_type& key) const 
	{
		size_type img=hash(key);
		if (img < 0) img = -img;
		return img%mbc; 
	}
	size_type getInd(value_type& val) const {return getInd(val.first);}
	size_type getInd(node_type* item) const {return getInd(item->value);}
	size_type getInd(iterator itr) const {return getInd(itr.it);}

	void alloc_bucket_array(size_type size)
	{
		buckets = new bucket_type[size];
		bc = 0;
		mbc = size;
	}

	template<class... Args>
	node_type* alloc_node(Args&&... args)
	{
		node_type* node=new node_type(value_type(std::forward<Args>(args)...));
		return node;
	}

	void release_bucket_array()
	{
		delete[] buckets;
		bc = 0;
		mbc = 0;
	}

	iterator find_item(const key_type& key, bool prev=false) const
	{
		//std::cout << key.first << " " << key.second << std::endl;
		size_type position = getInd(key);
		iterator itr = iterator(buckets[position].first);
		if (!prev)
		{
			while (!equal(itr.it->value.first, key) && !itr.it->isEnd)
			{
				~itr;
				//if (itr.it==buckets[position].end) break;
			}
		}
		else
		{
			while (!equal(itr.it->next->value.first, key) && !itr.it->next->isEnd)
			{
				~itr;
				//if (itr.it->next== buckets[position].end) break;
			}
		}
		if (itr.it->isEnd) return cend();
		return itr;
	}

	template<class Insert>
	insert_return_type insert_item(Insert nitem)
	{
		size_type position = getInd(nitem);
		auto result=buckets[position].push(nitem);
		if(result.second && result.first == buckets[position].first)
		{
			bc++;
			if(bc==1)
			{
				before_begin->next=buckets[position].first;
			}
			if (last_added_bucket != -1)
			{
				buckets[last_added_bucket].end->next = buckets[position].first;
				buckets[position].prev_bucket = buckets + last_added_bucket;
			}
			buckets[position].end->next = past_the_last;
			last_added_bucket = position;
		}
		/*update_lf();
		if(lf>max_lf)
		{
			rehash(mbc+DEFAULT_BUCKET_COUNT);
		}*/
		return insert_return_type(iterator(result.first), result.second);
	}

	
	iterator erase_item(const key_type& key)
	{
		size_type position = getInd(key);
		iterator itr = iterator(buckets[position].first);
		iterator prev = itr;
		while (!equal(itr.it->value.first, key) && !itr.it->isEnd)
		{
			prev = itr;
			~itr;
		}

		if (itr.it->isEnd) return end();
		else if (prev == itr)
		{
			node_type* target = buckets[position].first;
			buckets[position].first = buckets[position].first->next;
			if (buckets[position].prev_bucket != nullptr) buckets[position].prev_bucket->end->next = buckets[position].first;
			buckets[position].size -= 1;
			if (before_begin->next == target)
			{
				before_begin->next = target->next;
				if (target->next->isEnd)
				{
					before_begin->next = target->next->next;
				}
			}
			//target->next = nullptr;
			delete target;
			/*if (buckets[position].size == 0)
			{
				buckets[position].first = buckets[position].end;
				buckets[position].last = buckets[position].end;
			}*/
		}
		//if(itr.it->next->isEnd && !equal(itr.it->value.first, key)) return end();
		else
		{
			buckets[position].erase(prev.it);
			if (last_added_bucket == position) buckets[position].end->next = past_the_last;
		}

		if (buckets[position].size == 0)
		{
			bc--;
			if(buckets[position].prev_bucket==nullptr)
			{
				before_begin->next=buckets[position].end->next;
				
				/*if (buckets[position].end->next == past_the_last)
				{
					buckets[position].prev_bucket->end->next=past_the_last;
				}*/
			}
			else if(buckets[position].end->next==past_the_last)
			{
				buckets[position].prev_bucket->end->next=past_the_last;
			}
			else
			{
				buckets[position].prev_bucket->end->next=buckets[position].end->next;
				buckets[getInd(buckets[position].end->next)].prev_bucket = buckets[position].prev_bucket;
			}
			buckets[position].first = buckets[position].end;
			buckets[position].last = buckets[position].end;
		}
		//update_lf();
		return itr;
	}
	
	void update_lf() {if(bc!=0) lf=size()/bc;}
};


template<std::default_initializable Key, std::default_initializable T, class Hash, class KeyEqual, class Allocator>
MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::MyUnorderedMap(size_type bucket_count, const hasher& hash, const key_equal& equal) : hash(hash), equal(equal)
{
	before_begin = new node_type;
	past_the_last = new node_type;
	past_the_last->next = nullptr;
	before_begin->next=past_the_last;
	alloc_bucket_array(bucket_count);
}


template<std::default_initializable Key, std::default_initializable T, class Hash, class KeyEqual, class Allocator>
MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::MyUnorderedMap(UnorderedMapIterator<std::pair<const Key, T>, false> first, UnorderedMapIterator<std::pair<const Key, T>, false> last, size_type bucket_count, const hasher& hash, const key_equal& equal) : hash(hash), equal(equal)
{
	before_begin = new node_type;
	past_the_last = new node_type;
	before_begin->next=past_the_last;
	alloc_bucket_array(bucket_count);
	//std::cout << "iterator constructor" << std::endl;
	insert(first, last);
}


template<std::default_initializable Key, std::default_initializable T, class Hash, class KeyEqual, class Allocator>
MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::MyUnorderedMap(const MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>& um) : hash(um.hash), equal(um.equal), bc(um.bc), mbc(um.mbc) 
{
	alloc_bucket_array(mbc);
	before_begin=new node_type;
	past_the_last=new node_type;
	before_begin->next=past_the_last;
	insert(um.cbegin(), um.cend());
	max_lf=um.max_lf;
	lf=um.lf;
}


template<std::default_initializable Key, std::default_initializable T, class Hash, class KeyEqual, class Allocator>
MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::MyUnorderedMap(MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>&& um) : hash(um.hash), equal(um.equal), bc(um.bc), mbc(um.mbc)
{
	before_begin=um.before_begin;
	past_the_last = um.past_the_last;
	buckets=um.buckets;
	max_lf=um.max_lf;
	lf=um.lf;
	last_added_bucket=um.last_added_bucket;
	um.buckets=nullptr;
	um.before_begin=nullptr;
	um.past_the_last=nullptr;
	um.bc = 0;
	um.mbc = 0;
	um.last_added_bucket = -1;
}

template<std::default_initializable Key, std::default_initializable T, class Hash, class KeyEqual, class Allocator>
MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::MyUnorderedMap(std::initializer_list<value_type> il, size_type bucket_count, const hasher& hash, const key_equal& equal) : hash(hash), equal(equal)
{
	before_begin = new node_type;
	past_the_last = new node_type;
	before_begin->next=past_the_last;
	alloc_bucket_array(bucket_count);
	for(auto itr: il)
	{
		insert(itr);
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
	if(this!=&um)
	{
		hash=um.hash;
		equal=um.equal;
		release_bucket_array();
		alloc_bucket_array(um.mbc);
		insert(um.begin(), um.end());
		max_lf=um.max_lf;
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
	max_lf=um.max_lf;
	lf=um.lf;
	last_added_bucket=um.last_added_bucket;
	um.buckets=nullptr;
	um.before_begin=nullptr;
	um.past_the_last=nullptr;
	return *this;
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
MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::insert_return_type MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::emplace(Args&&... args) requires(std::constructible_from<MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::value_type, Args...>)
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
MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::iterator MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::emplace_hint(const_iterator p, Args&&... args) requires(std::constructible_from<MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::value_type, Args...>)
{
	node_type* node=alloc_node(std::forward<Args>(args)...);
	if(equal(p.it->value.first, node->value.first))
	{
		return end();
		/*node_type* next = p.it->next;
		p.it->next=node;
		node->next=next;
		return iterator(node);*/
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
MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::insert_return_type MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::try_emplace(const key_type& key, Args&&... args) requires(std::constructible_from<T, Args...>)
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
MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::insert_return_type MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::insert(const value_type& value)
{
	return insert_item<value_type>(value);
}

template<std::default_initializable Key, std::default_initializable T, class Hash, class KeyEqual, class Allocator>
MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::insert_return_type MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::insert(value_type&& value)
{
	return insert_item<value_type>(value);	
}

template<std::default_initializable Key, std::default_initializable T, class Hash, class KeyEqual, class Allocator>
void MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::insert(UnorderedMapIterator<std::pair<const Key, T>, false> first, UnorderedMapIterator<std::pair<const Key, T>, false> last)
{
	iterator itr=first;
	while(itr!=last)
	{
		insert(itr.it->value);
		~itr;
	}
}

template<std::default_initializable Key, std::default_initializable T, class Hash, class KeyEqual, class Allocator>
void MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::insert(std::initializer_list<value_type> il)
{
	for(auto it: il)
	{
		insert(it);
	}
}

template<std::default_initializable Key, std::default_initializable T, class Hash, class KeyEqual, class Allocator>
MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::insert_return_type MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::insert(node_type&& nh)
{
	return insert(nh.value);
}

template<std::default_initializable Key, std::default_initializable T, class Hash, class KeyEqual, class Allocator>
MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::insert_return_type MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::insert_or_assign(const key_type& key, mapped_type&& obj)
{
	size_type position=getInd(key);
	iterator result=iterator(buckets[position].find(value_type(key, obj)));
	if(result.it->isEnd)
	{
		//can be some problems with moving, but it's gonna be tested later
		return insert(value_type(key, obj));
	}
	result.it->value.second=std::move(obj);
	return insert_return_type(result, true);
}

template<std::default_initializable Key, std::default_initializable T, class Hash, class KeyEqual, class Allocator>
MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::node_type* MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::extract(const key_type& key)
{
	iterator prev=find_item(key, true);
	if (prev.it->next->isEnd)
	{
		if (equal(prev.it->value.first, key))
		{
			node_type* extr = new node_type(prev.it->value);
			erase_item(key);
			//std::cout << "here" << std::endl;
			//size_type pos = getInd(key);
			//buckets[pos].first = buckets[pos].end;
			//buckets[pos].last = buckets[pos].end;
			//buckets[pos].size -= 1;
			return extr;
		}
		else
		{
			return nullptr;
		}
	}
	node_type* extr=prev.it->next;
	prev.it->next=extr->next;
	buckets[getInd(key)].size-=1;
	return extr;
}

template<std::default_initializable Key, std::default_initializable T, class Hash, class KeyEqual, class Allocator>
MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::node_type* MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::extract(iterator itr)
{
	node_type* extr = new node_type(itr.it->next->value);
	buckets[getInd(extr->value.first)].erase(itr.it);
	/*node_type* extr = itr.it->next;
	itr.it->next=extr->next;
	buckets[getInd(itr)].size-=1;*/
	return extr;
}

/*template<std::default_initializable Key, std::default_initializable T, class Hash, class KeyEqual, class Allocator>
void MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::merge(MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>& other)
{
	for(auto itr: other)
	{
		iterator search=find_item(itr.it->value.first);
		if(search.it->isEnd)
		{
			insert<node_type*>(other.extract(search));
		}
	}
}*/

template<std::default_initializable Key, std::default_initializable T, class Hash, class KeyEqual, class Allocator>
MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::size_type MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::erase(const key_type& key)
{
	iterator itr=erase_item(key);
	if(itr.it->isEnd) return 0;
	else return 1;
}

template<std::default_initializable Key, std::default_initializable T, class Hash, class KeyEqual, class Allocator>
MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::iterator MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::erase(MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::iterator itr)
{
	if (itr == end()) throw std::invalid_argument("Error. Cnat erase end iterator.");
	iterator next=iterator(itr.it->next);
	erase(itr.it->value.first);
	return next;
}

template<std::default_initializable Key, std::default_initializable T, class Hash, class KeyEqual, class Allocator>
MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::iterator MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::erase(MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::iterator it1, MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::iterator it2)
{
	iterator itr=it1;
	iterator last_removed=itr;
	//if (it2 == end()) it2 = buckets[last_added_buckets].end;
	while(itr!=it2)
	{
		
		iterator next = iterator(itr.it->next);
		size_type result=erase(itr.it->value.first);
		if (result) 
		{
			//std::cout << "removed" << std::endl;
			last_removed = itr;
		}
		itr=next;
		if (itr.it == nullptr) break;
		if (itr.it->isEnd)
		{
			++itr;
		}
	}
	return last_removed;
}

template<std::default_initializable Key, std::default_initializable T, class Hash, class KeyEqual, class Allocator>
void MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::clear() noexcept
{
	erase(begin(), end());
	/*iterator itr = iterator(before_begin->next);
	while (itr != end())
	{
		erase(itr);
		itr = iterator(before_begin->next);
	}*/
}

template<std::default_initializable Key, std::default_initializable T, class Hash, class KeyEqual, class Allocator>
MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::iterator MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::find(const key_type& key, bool prev)
{
	return find_item(key, prev);	
}

template<std::default_initializable Key, std::default_initializable T, class Hash, class KeyEqual, class Allocator>
MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::const_iterator MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::find(const key_type& key, bool prev) const
{
	return const_iterator(find_item(key, prev));
}

template<std::default_initializable Key, std::default_initializable T, class Hash, class KeyEqual, class Allocator>
bool MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::contains(const key_type& key) const
{
	return find(key)!=cend();
}


/*template<std::default_initializable Key, std::default_initializable T, class Hash, class KeyEqual, class Allocator>
void MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::rehash(size_type new_count)
{
	if(new_count<=mbc) throw std::invalid_argument("Error. You cant rehash to the smaller size.");

	MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator> nmap(begin(), end(), new_count);
	*this=std::move(nmap);
	
	size_type nmbc=new_count;
	mbc=nmbc;
	size_type nbc=0;
	bucket_type* nbuckets=new bucket_type[new_count];
	iterator itr=begin();
	while(itr!=end())
	{
		node_type* nnode=new node_type;
		*nnode=*itr.it;
		size_type position=getInd(itr);
		auto result=nbuckets[position].push(nnode);		
		//if(nbuckets[position].size==1) nbc++;
		if(result.first == buckets[position].first)
		{
			nbc++;
			if(nbc==1)
			{
				before_begin->next=buckets[position].first;
			}
			buckets[last_added_bucket].end->next=bucket[position].first;
			bucket[position].prev_bucket=buckets[last_added_bucket];
			last_added_bucket=position;
			bucket[position].end->next=past_the_last;
		}
		++itr;
	}
	release_bucket_array();
	mbc=nmbc;
	bc=nbc;
	
}
//void reserve(size_type new_count);
template<std::default_initializable Key, std::default_initializable T, class Hash, class KeyEqual, class Allocator>
void MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>::swap(MyUnorderedMap<Key, T, Hash, KeyEqual, Allocator>& other)
{
	if(mbc!=other.mbc) throw std::invalid_argument("Error. unordered maps must be equal size to perform swap.");
	for(int i=0; i<mbc; i++)
	{
		bucket_type tmp=buckets[i];
		buckets[i]=other.buckets[i];
		other.buckets[i]=tmp;
	}
	std::swap(hash, other.hash);
	std::swap(equal, other.equal);
	std::swap(bc, other.bc);
	std::swap(before_begin, other.before_begin);
	std::swap(past_the_last, other.past_the_last);
	std::swap(last_added_bucket, other.last_added_bucket);
	std::swap(max_lf, other.max_lf);
	std::swap(lf, other.lf);
}*/









