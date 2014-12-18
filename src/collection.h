#ifndef __SRC_COLLECTION_H__
#define __SRC_COLLECTION_H__

#include <vector>
#include <set>
#include "global.h"

namespace robot {


template <typename T, class A = std::allocator<T> >
class X {

	public:
		typedef A allocator_type;
		typedef typename A::value_type value_type; 
		typedef typename A::reference reference;
		typedef typename A::const_reference const_reference;
		typedef typename A::difference_type difference_type;
		typedef typename A::size_type size_type;

		class iterator { 
		public:
			typedef typename A::difference_type difference_type;
			typedef typename A::value_type value_type;
			typedef typename A::reference reference;
			typedef typename A::pointer pointer;
			typedef std::random_access_iterator_tag iterator_category; //or another tag

			iterator();
			iterator(const iterator&);
			~iterator();

			iterator& operator=(const iterator&);
			bool operator==(const iterator&) const;
			bool operator!=(const iterator&) const;
			bool operator<(const iterator&) const; //optional
			bool operator>(const iterator&) const; //optional
			bool operator<=(const iterator&) const; //optional
			bool operator>=(const iterator&) const; //optional

			iterator& operator++();
			iterator operator++(int); //optional
			iterator& operator--(); //optional
			iterator operator--(int); //optional
			iterator& operator+=(size_type); //optional
			iterator operator+(size_type) const; //optional
			iterator& operator-=(size_type); //optional            
			iterator operator-(size_type) const; //optional
			difference_type operator-(iterator) const; //optional

			reference operator*() const;
			pointer operator->() const;
			reference operator[](size_type) const; //optional
		};
		class const_iterator {
		public:
			typedef typename A::difference_type difference_type;
			typedef typename A::value_type value_type;
			typedef typename A::reference const_reference;
			typedef typename A::pointer const_pointer;
			typedef std::random_access_iterator_tag iterator_category; //or another tag

			const_iterator ();
			const_iterator (const const_iterator&);
			const_iterator (const iterator&);
			~const_iterator();

			const_iterator& operator=(const const_iterator&);
			bool operator==(const const_iterator&) const;
			bool operator!=(const const_iterator&) const;
			bool operator<(const const_iterator&) const; //optional
			bool operator>(const const_iterator&) const; //optional
			bool operator<=(const const_iterator&) const; //optional
			bool operator>=(const const_iterator&) const; //optional

			const_iterator& operator++();
			const_iterator operator++(int); //optional
			const_iterator& operator--(); //optional
			const_iterator operator--(int); //optional
			const_iterator& operator+=(size_type); //optional
			const_iterator operator+(size_type) const; //optional
			const_iterator& operator-=(size_type); //optional            
			const_iterator operator-(size_type) const; //optional
			difference_type operator-(const_iterator) const; //optional

			const_reference operator*() const;
			const_pointer operator->() const;
			const_reference operator[](size_type) const; //optional
		};

		typedef std::reverse_iterator<iterator> reverse_iterator; //optional
		typedef std::reverse_iterator<const_iterator> const_reverse_iterator; //optional

		X();
		X(const X&);
		~X();

		X& operator=(const X&);
		bool operator==(const X&) const;
		bool operator!=(const X&) const;
		bool operator<(const X&) const; //optional
		bool operator>(const X&) const; //optional
		bool operator<=(const X&) const; //optional
		bool operator>=(const X&) const; //optional

		iterator begin();
		const_iterator begin() const;
		const_iterator cbegin() const;
		iterator end();
		const_iterator end() const;
		const_iterator cend() const;
		reverse_iterator rbegin(); //optional
		const_reverse_iterator rbegin() const; //optional
		const_reverse_iterator crbegin() const; //optional
		reverse_iterator rend(); //optional
		const_reverse_iterator rend() const; //optional
		const_reverse_iterator crend() const; //optional

		reference front(); //optional
		const_reference front() const; //optional
		reference back(); //optional
		const_reference back() const; //optional
		template<class ...Args>
		void emplace_front(Args...); //optional
		template<class ...Args>
		void emplace_back(Args...); //optional
		void push_front(const T&); //optional
		void push_front(T&&); //optional
		void push_back(const T&); //optional
		void push_back(T&&); //optional
		void pop_front(); //optional
		void pop_back(); //optional
		reference operator[](size_type); //optional
		const_reference operator[](size_type) const; //optional
		reference at(size_type); //optional
		const_reference at(size_type) const; //optional

		template<class ...Args>
		iterator emplace(const_iterator, Args...); //optional
		iterator insert(const_iterator, const T&); //optional
		iterator insert(const_iterator, T&&); //optional
		iterator insert(const_iterator, size_type, T&); //optional
		template<class iter>
		iterator insert(const_iterator, iter, iter); //optional
		iterator insert(const_iterator, std::initializer_list<T>); //optional
		iterator erase(const_iterator); //optional
		iterator erase(const_iterator, const_iterator); //optional
		void clear(); //optional
		template<class iter>
		void assign(iter, iter); //optional
		void assign(std::initializer_list<T>); //optional
		void assign(size_type, const T&); //optional

		void swap(const X&);
		size_type size();
		size_type max_size();
		bool empty();

		A get_allocator(); //optional
};
template <class T, class A = std::allocator<T> >
void swap(X<T,A>&, X<T,A>&); //optional


#if 0
template<typename T>
class Collection {
	public:
		typedef typename std::multiset<T>::const_iterator tc_iter;
		typedef typename std::multiset<T>::const_reverse_iterator tcr_iter;
		typedef typename std::vector<T *>::const_iterator sc_iter;
		typedef typename std::vector<T *>::const_reverse_iterator scr_iter;

		tc_iter tcbegin() const { return t.cbegin();}
		tcr_iter tcrbegin() const { return t.crbegin();}
		tc_iter tcend() const { return t.cend();}
		tcr_iter tcrend() const { return t.crend();}

		sc_iter scbegin() const { return s.cbegin();}
		scr_iter scrbegin() const { return s.crbegin();}
		sc_iter scend() const { return s.cend();}
		scr_iter scrend() const { return s.crend();}

		void push_back(T const &t);
	
	private:
		std::vector<T *> s; 		//sequence
		std::multiset<T> t; 		//tree
};
#endif
}

#endif