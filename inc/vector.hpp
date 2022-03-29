#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <string>
#include <stdexcept>
#include "iterator.hpp"
#include "type_traits.hpp"
#include "algorithm.hpp"

namespace ft
{

    template <
        class T,
        class Alloc = std::allocator<T> >
    class vector
    {
        /* ************************************** Member types ********************************** */

    public:
        // https://www.cplusplus.com/reference/vector/vector/?kw=vector

        typedef T value_type;                                             // T
        typedef Alloc allocator_type;                                     // Alloc
        typedef typename allocator_type::const_reference const_reference; // const T&
        typedef typename allocator_type::reference reference;             // T&
        typedef typename allocator_type::const_pointer const_pointer;     // const T*
        typedef typename allocator_type::pointer pointer;                 // T*
        typedef typename allocator_type::difference_type difference_type; // std::ptrdiff_t
        typedef typename allocator_type::size_type size_type;             // std::size_t
        typedef random_access_iterator<const value_type> const_iterator;
        typedef random_access_iterator<value_type> iterator;
        typedef reverse_iterator<const_iterator> const_reverse_iterator;
        typedef reverse_iterator<iterator> reverse_iterator;

        /* ************************************ Constructors ************************************ */

        // (1)	empty container constructor (default constructor)
        // Constructs an empty container, with no elements.
        explicit vector(const allocator_type &alloc = allocator_type()) : _alloc(alloc),
                                                                          _size(0),
                                                                          _start(NULL),
                                                                          _capacity(0) {}

        // (2)	fill constructor
        // Constructs a container with n elements. Each element is a copy of val.
        explicit vector(size_type n, const value_type &val = value_type(),
                        const allocator_type &alloc = allocator_type()) : _alloc(alloc),
                                                                          _size(n),
                                                                          _start(_alloc.allocate(n)),
                                                                          _capacity(n)
        {
            for (size_type i = 0; i < n; i++)
            {
                _alloc.construct(_start + i, val);
            }
        }

        // (3)	range constructor
        // Constructs a container with as many elements as the range [ first, last [
        // with each element constructed from its corresponding element in that range,
        // in the same order.
        //
        // If Cond is true, enable_if has a public member typedef type, equal to T;
        // otherwise, there is no member typedef
        template <class InputIterator>
        vector(typename ft::enable_if<
                   !ft::is_integral<InputIterator>::value, // Cond
                   InputIterator                           // T
                   >::type first,
               InputIterator last,
               const allocator_type &alloc = allocator_type()) : _alloc(alloc),
                                                                 _size(last - first),
                                                                 _start(_alloc.allocate(last - first)),
                                                                 _capacity(last - first)
        {
            for (size_type i = 0; i < _size; i++)
            {
                _alloc.construct(_start + i, *(first + i));
            }
        }

        // (4)	copy constructor
        // Constructs a container with a copy of each of the elements in x, in the same order.
        vector(const vector &other) : _alloc(other._alloc),
                                      _size(0),
                                      _start(NULL),
                                      _capacity(0)
        {
            *this = other;
        }

        ~vector()
        {
            destruct_all();
            _alloc.deallocate(_start, _capacity);
        }

        // Assignment operator
        vector &operator=(const vector &other)
        {
            if (this == &other)
            {
                return (*this);
            }

            if (_capacity < other._size)
            {
                this->~vector();
                _start = _alloc.allocate(other._size);
                _capacity = other._size;
            }
            else
            {
                destruct_all();
            }

            for (size_type i = 0; i < other._size; i++)
            {
                copy_construct(_start, other[i], i);
            }
            _size = other._size;
            return (*this);
        }

        /* ************************************** Iterator ************************************** */

        iterator begin() { return (iterator(_start)); }

        const_iterator begin() const { return (const_iterator(_start)); }

        iterator end() { return (iterator(_start + _size)); }

        const_iterator end() const { return (const_iterator(_start + _size)); }

        reverse_iterator rbegin() { return (reverse_iterator(end())); }

        const_reverse_iterator rbegin() const { return (const_reverse_iterator(end())); }

        reverse_iterator rend() { return (reverse_iterator(begin())); }

        const_reverse_iterator rend() const { return (const_reverse_iterator(begin())); }

        /* ************************************** Capacity ************************************** */

        size_type size() const { return (_size); }

        size_type max_size() const { return (_alloc.max_size()); }

        void resize(size_type n, const value_type &val = value_type())
        {
            if (n < _size)
            {
                for (size_type i = n; i < _size; i++)
                {
                    _alloc.destroy(_start + i);
                }
            }
            else if (n > _capacity)
            {
                (n / 2 < _size) ? reserve(_size * 2) : reserve(n);
            }

            for (size_type i = _size; i < n; i++)
            {
                _alloc.construct(_start + i, val);
            }
            _size = n;
        }

        size_type capacity() const { return (_capacity); }

        bool empty() const { return (_size == 0); };

        void reserve(size_type n)
        {
            if (n <= _capacity)
            {
                return;
            }
            else if (n > max_size())
            {
                throw std::length_error("vector::reserve");
            }

            pointer tmp = _alloc.allocate(n);
            for (size_type i = 0; i < _size; i++)
            {
                _alloc.construct(tmp + i, _start[i]);
            }
            this->~vector();
            _start = tmp;
            _capacity = n;
        }

        /* *********************************** Element access *********************************** */

        reference operator[](size_type n) { return (_start[n]); }

        const_reference operator[](size_type n) const { return (_start[n]); }

        reference at(size_type n)
        {
            _M_range_check(n);
            return (_start[n]);
        }

        const_reference at(size_type n) const
        {
            _M_range_check(n);
            return (_start[n]);
        }

        reference front() { return (*_start); }

        const_reference front() const { return (*_start); }

        reference back() { return (*(_start + _size - 1)); }

        const_reference back() const { return (*(_start + _size - 1)); }

        /* ************************************* Modifiers ************************************** */

        template <class InputIterator>
        void assign(typename ft::enable_if<
                        !ft::is_integral<InputIterator>::value, // Cond
                        InputIterator                           // T
                        >::type first,
                    InputIterator last)
        {
            destruct_all();
            _size = 0;
            reserve(last - first);
            copy_construct(_start, first, last);
            _size = last - first;
        }

        void assign(size_type n, const value_type &val)
        {
            destruct_all();
            _size = 0;
            reserve(n);
            for (size_type i = 0; i < n; i++)
            {
                copy_construct(_start, val, i);
            }
            _size = n;
        }

        void push_back(const value_type &val)
        {
            if (empty())
            {
                reserve(1);
            }
            else if (_size == _capacity)
            {
                (_size * 2 < max_size()) ? reserve(_size * 2) : reserve(max_size());
            }
            copy_construct(_start, val, _size++);
        }

        void pop_back()
        {
            destruct(_start, --_size);
        }

        iterator insert(iterator position, const value_type &val)
        {
            if (empty())
            {
                if (position == begin())
                {
                    reserve(1);
                    copy_construct(_start, val);
                    position = iterator(_start);
                }
            }
            else if (_size == _capacity)
            {
                size_type new_cap;
                pointer tmp;
                size_type pos;

                (_size * 2 < max_size()) ? (new_cap = _capacity * 2) : (new_cap = max_size());
                tmp = _alloc.allocate(new_cap);
                pos = position - begin();

                copy_construct(tmp, begin(), position);
                copy_construct(tmp + pos, val);
                copy_construct(tmp + pos + 1, position, end());

                this->~vector();
                _capacity = new_cap;
                _start = tmp;
                position = iterator(_start + pos);
            }
            else
            {
                iterator end(this->end());
                size_type i = _size;

                do
                {
                    copy_construct(_start + i, _start[i - 1]);
                    destruct(_start, --i);
                } while (position != --end);
                copy_construct(_start + (position - begin()), val);
            }
            _size++;
            return (position);
        }

        void insert(iterator position, size_type n, const value_type &val)
        {
            if (!n)
            {
                return;
            }
            else if (empty())
            {
                if (position == begin())
                {
                    reserve(n);
                    for (size_type i = 0; i < n; i++)
                    {
                        copy_construct(_start, val, i);
                    }
                }
            }
            else if (_size + n > _capacity)
            {
                size_type pos = position - begin();
                size_type new_cap;
                pointer tmp;

                // correct capacity
                if (_size * 2 > max_size() && _size + n <= max_size())
                {
                    new_cap = max_size();
                }
                else
                {
                    (_size + n < _size * 2) ? (new_cap = _capacity * 2) : (new_cap = _size + n);
                }
                tmp = _alloc.allocate(new_cap);

                // copy construct content
                copy_construct(tmp, begin(), position);
                for (size_type i = 0; i < n; i++)
                {
                    copy_construct(tmp, val, pos + i);
                }
                copy_construct(tmp + pos + n, position, end());

                // replace ptr for new ptr
                this->~vector();
                _capacity = new_cap;
                _start = tmp;
            }
            else
            {
                iterator ite(end());
                size_type last_index = _size - 1;
                size_type pos = position - begin();

                do
                {
                    copy_construct(_start + last_index + n, _start[last_index]);
                    destruct(_start, last_index--);
                } while (position != --ite);
                for (size_type i = 0; i < n; i++)
                {
                    copy_construct(_start + pos++, val);
                }
            }
            _size += n;
        }

        template <class InputIterator>
        void insert(iterator position,
                    typename ft::enable_if<
                        !ft::is_integral<InputIterator>::value, // Cond
                        InputIterator                           // T
                        >::type first,
                    InputIterator last)
        {
            size_type range = last - first;
            size_type pos = position - begin();

            if (empty())
            {
                if (position == begin())
                {
                    reserve(range);
                    copy_construct(_start, first, last);
                }
            }
            else if (_size + range > _capacity)
            {
                size_type new_cap;
                pointer tmp;

                // correct capacity
                if (_size * 2 > max_size() && _size + range <= max_size())
                {
                    new_cap = max_size();
                }
                else
                {
                    (_size + range < _size * 2) ? (new_cap = _capacity * 2) : (new_cap = _size + range);
                }
                tmp = _alloc.allocate(new_cap);

                // copy construct content
                copy_construct(tmp, begin(), position);
                copy_construct(tmp + pos, first, last);
                copy_construct(tmp + pos + range, position, end());

                // replace ptr for new ptr
                this->~vector();
                _capacity = new_cap;
                _start = tmp;
            }
            else
            {
                iterator ite(end());
                size_type last_index = _size - 1;
                size_type pos = position - begin();

                do
                {
                    copy_construct(_start + last_index + range, _start[last_index]);
                    destruct(_start, last_index--);
                } while (position != --ite);
                copy_construct(_start + pos, first, last);
            }
            _size += range;
        }

        iterator erase(iterator position)
        {
            size_type pos = position - begin();

            if (size() == 1 && !pos)
            {
                destruct(_start, 0);
            }
            else
            {
                for (size_type i = pos; i < _size; i++)
                {
                    destruct(_start, i);
                    copy_construct(_start, _start[i + 1], i);
                }
            }
            _size--;
            return (position);
        }

        iterator erase(iterator first, iterator last)
        {
            size_type range = last - first;
            size_type pos = first - begin();
            size_type remaining = end() - last;

            for (size_type i = pos; i < range; i++)
            {
                destruct(_start, i);
            }
            for (size_type i = pos; i < remaining; i++)
            {
                copy_construct(_start, _start[range + i], i);
                destruct(_start, range + i);
            }
            _size -= range;
            return (first);
        }

        void swap(vector &other)
        {
            allocator_type tmp_alloc = _alloc;
            size_type tmp_size = _size;
            pointer tmp_start = _start;
            size_type tmp_capacity = _capacity;

            _alloc = other._alloc;
            _size = other._size;
            _start = other._start;
            _capacity = other._capacity;

            other._alloc = tmp_alloc;
            other._size = tmp_size;
            other._start = tmp_start;
            other._capacity = tmp_capacity;
        }

        void clear() { erase(begin(), end()); }

        /* ************************************** Allocator ************************************* */

        allocator_type get_allocator() const { return (allocator_type()); }

        /* ********************************** Helper functions ********************************** */

    private:
        // Destroy objects in range (0, size), doesn't free memory
        void destruct_all()
        {
            for (size_type i = 0; i < _size; i++)
            {
                destruct(_start, i);
            }
        }

        void destruct(pointer ptr, size_type index)
        {
            _alloc.destroy(ptr + index);
        }

        void copy_construct(pointer dst, iterator start, iterator end)
        {
            for (; start != end; ++start)
            {
                _alloc.construct(dst++, *start);
            }
        }

        void copy_construct(pointer dst, const value_type &val, size_type i = 0)
        {
            _alloc.construct(dst + i, val);
        }

        static std::string atol(size_type rhs)
        {
            std::string str;
            int n = 0;

            for (size_type i = rhs; i != 0; i /= 10)
            {
                n++;
            }

            for (; rhs != 0; rhs /= 10)
            {
                str.insert(0, 1, (rhs % 10) + '0');
            }
            return (str);
        }

        void _M_range_check(size_type __n)
        {
            if (__n >= _size)
            {
                std::string buffer;

                buffer = "vector::_M_range_check: __n (which is " + atol(__n) + ") >= this->size() (which is " + atol(_size) + ")";

                throw std::out_of_range(buffer);
            }
        }

        /* ********************************** Private data members ****************************** */

        allocator_type _alloc;
        size_type _size;
        pointer _start;
        size_type _capacity;
    };

    /* ********************************** Non-member functions ********************************** */

    template <class T, class Alloc>
    bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    {
        if (lhs.size() == rhs.size())
        {
            return (equal(lhs.begin(), lhs.end(), rhs.begin()));
        }
        return (false);
    }

    template <class T, class Alloc>
    bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    {
        return (!(lhs == rhs));
    }

    template <class T, class Alloc>
    bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    {
        return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }

    template <class T, class Alloc>
    bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    {
        return (rhs < lhs);
    }

    template <class T, class Alloc>
    bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    {
        return (!(rhs < lhs));
    }

    template <class T, class Alloc>
    bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    {
        return (!(lhs < rhs));
    }

    template <class T, class Alloc>
    void swap(vector<T, Alloc> &x, vector<T, Alloc> &y)
    {
        x.swap(y);
    }
};

#endif // VECTOR_HPP
