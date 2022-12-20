#include <exception>
#include <iterator>
using std::exception;
#include <iostream>
using namespace std;

template<class T>
class Iterator {
private:
	T* it;
public:
	using difference_type = std::ptrdiff_t;
	using value_type = T;
	using pointer = T*;
	using reference = T&;
	using iterator_category = std::random_access_iterator_tag;
	Iterator(T* first) : it(first) {};
	Iterator() {};//test

	bool operator< (Iterator t) {//test
		return (it < t.it);
	}

	bool operator<= (Iterator t) {//test
		return (it <= t.it);
	}

	Iterator operator+ (int n) {//test
		Iterator it1;
		it1.it = it + n;
		return it1;
	}

	Iterator operator- (int n) {//test
		Iterator it1;
		it1.it = it - n;
		return it1;
	}

	Iterator& operator++() noexcept {//test
		it = it + 1;
		return *this;
	}

	Iterator operator++(int d) noexcept {//test
		Iterator it1 = *this;
		it = it + 1;
		return it1;
	}

	Iterator& operator--() noexcept {//test
		it = it - 1;
		return *this;
	}

	Iterator operator--(int d) noexcept {//test
		Iterator it1 = *this;
		it = it - 1;
		return it1;
	}

	bool operator ==(const Iterator& iter) const {//test
		return (it == iter.it);
	}

	bool operator !=(const Iterator& iter) const {//test
		return (it != iter.it);
	}

	T& operator*() {//test
		return *it;
	}
};

template<class T>
class Vector {
private:
	T* arr;
	int size_ = 0;
	int capacity_ = 10;
public:
	Vector() noexcept {//test
		arr = new T[capacity_];
	};

	Vector(int s, const T& val = T()) {//test
		if (s < 0) {
			throw exception("invalid size of Vector\n");
		}
		if (s > capacity_) {
			capacity_ += 10;
		}
		arr = new T[capacity_];
		size_ = s;
		for (int i = 0; i < size_; i++) {
			arr[i] = val;
		}
	}

	Vector(const Vector& other) {
		if (this != &other) {
			delete[] arr;
			arr = new T[other.capacity_];
			for (size_t i = 0; i < other.size_; ++i)
				arr[i] = other.arr[i];
			size_ = other.size_;
			capacity_ = other.capacity_;
		}
	}
	Vector(Vector&& other)  noexcept {
		if (this != &other) {
			delete[] arr;
			arr = other.arr;
			size_ = other.size_;
			capacity_ = other.capacity_;
			other.arr = nullptr;
			other.size_ = other.capacity_ = 0;
		}
	}

	~Vector() noexcept {//test
		delete[] arr;
	}

	const T operator [](int s) const {//test
		if (s >= size_) {
			throw exception("The size of vector is smaller, than value");
		}
		return arr[s];
	}

	T& operator [](int s) {//test
		if (s >= size_) {
			throw exception("The size of vector is smaller, than value");
		}
		return arr[s];
	}

	Vector& operator=(const Vector& other) {
		if (this != &other) {
			delete[] arr;
			arr = new T[other.capacity_];
			for (int i = 0; i < other.size_; ++i)
				arr[i] = other.arr[i];
			size_ = other.size_;
			capacity_ = other.capacity_;
		}
		return *this;
	}

	Vector& operator=(Vector&& other) noexcept {
		if (this != &other) {
			delete[] arr;
			arr = other.arr;
			size_ = other.size_;
			capacity_ = other.capacity_;
			other.arr = nullptr;
			other.size_ = other.capacity_ = 0;
		}
		return *this;
	}

	class Iteartor;

	Iterator<T> begin() {//test
		return arr;
	}

	const Iterator<T> cbegin() const {//test
		return arr;
	}

	Iterator<T> end() {//end
		return arr + size_;
	}

	const Iterator<T> cend() const {
		return arr + size_;
	}

	T& at(int i) {
		return arr[i];
	}

	int capacity() const noexcept {//test
		return capacity_;
	}

	void clear() noexcept {//test
		capacity_ = 10;
		size_ = 0;
		delete[] arr;
		arr = new T[capacity_];
	}

	bool empty() const {//test
		if (size_ == 0) {
			return true;
		}
		else {
			return false;
		}
	}

	Iterator<T> erase(Iterator<T> j) {//test
		for (auto i = j; i < end(); i++) {
			*i = *(i + 1);
		}
		size_--;
		return j;
	}

	Iterator<T> erase(Iterator<T> j, int k) {//test
		for (auto i = j; i < end() - k; i++) {
			*i = *(i + k);
		}
		size_ = size_ - k;
		return j;
	}

	Iterator<T> insert(int p, const T& v) {//test
		if ((p > size_) || (p < 0)) {
			throw exception("Incorrect place");
		}
		if (size_ == capacity_) {
			capacity_ += 10;
			T* arr1 = arr;
			arr = new T[capacity_];
			for (int i = 0; i < p; i++) {
				arr[i] = arr1[i];
			}
			arr[p] = v;
			for (int i = p + 1; i < size_ + 1; i++) {
				arr[i] = arr1[i - 1];
			}
			delete[] arr1;
		}
		else {
			T t2 = v;
			for (int i = p; i < size_ + 1; i++) {
				T t1 = arr[i];
				arr[i] = t2;
				t2 = t1;
			}
		}
		size_++;
		return arr + p;
	}
	/*
		void insert(int p, int c, const T& v) {
			if (size_ + c > capacity_) {
				while (size_ + c > capacity_) {
					capacity_ += 10;
				}
				T* arr1 = arr;
				arr = new T[capacity_];
				for (int i = 0; i < p; i++) {
					arr[i] = arr1[i];
				}
				for (int i = p; i < p + c; i++) {
					arr[i] = v;
				}
				for (int i = p + c; i < size_ + c; i++) {
					arr[i] = arr1[i - c];
				}
				delete[] arr1;
			}
			else {
				T t1[size_ - p - c];
				for (int i = 0; i < size_ - p - c; i++) {
					t1[i] = arr[i + p];
				}
				for (int i = p; i < p + c; i++) {
					arr[i] = v;
				}
				for (int i = p + c, j = 0; i < size_ + c; i++, j++) {
					arr[i] = arr1[j];
				}
			}
			size_ += c;
		}*/

	void pop_back() noexcept {//test
		if (size_ > 0) {
			size_--;
		}
	}

	void push_back(const T v) noexcept {//test
		if (size_ == capacity_) {
			capacity_ += 10;
			T* tmp = arr;
			arr = new T[capacity_];
			for (int i = 0; i < size_; ++i) 
				arr[i] = tmp[i];
			arr[size_] = v;
			delete[] tmp;
		}
		else {
			arr[size_] = v;
			size_++;
		}
	}

	void reserve(int s) noexcept {
		if (size_ != 0) {
			if (s > capacity_) {
				while (s > capacity_) {
					capacity_ += 10;
				}
				T* arr1 = arr;
				arr = new T[capacity_];
				for (int i = 0; i < size_; i++) {
					arr[i] = arr1[i];
				}
				delete[] arr1;
			}
		}
		else {
			if (s > capacity_) {
				while (s > capacity_) {
					capacity_ += 10;
				}
				delete[] arr;
				arr = new T[capacity_];
			}
		}
	}

	int size() const noexcept {//test
		return size_;
	}
};

template<typename T>
Iterator<T> find(Iterator<T> i, Iterator<T> j, T& e) {
	for (auto k = i; k < j; k++) {
		if (*k == e) {
			return k;
		}
	}
	return j;
}
