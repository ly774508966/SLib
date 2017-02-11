#ifndef CHECKHEADER_SLIB_CORE_REF
#define CHECKHEADER_SLIB_CORE_REF

#include "definition.h"

#include "base.h"
#include "atomic.h"
#include "macro.h"

#ifdef SLIB_DEBUG
#define SLIB_DEBUG_REFERENCE
#endif

typedef const void* sl_object_type;

SLIB_NAMESPACE_BEGIN

class CWeakRef;

class SLIB_EXPORT Referable
{
public:
	Referable();
	
	Referable(const Referable& other);
	
	virtual ~Referable();
	
public:
	sl_reg increaseReference();
	
	sl_reg decreaseReference();
	
	sl_reg decreaseReferenceNoFree();
	
	void makeNeverFree();
	
public:
	virtual sl_object_type getObjectType() const;
	
	virtual sl_bool isInstanceOf(sl_object_type type) const;
	
private:
	void _clearWeak();
	
public:
	SLIB_INLINE sl_bool _isWeakRef() const
	{
		return m_flagWeakRef;
	}
	
	CWeakRef* _getWeakObject();
	
	void _free();
	
private:
	sl_reg m_signature;
#if defined(SLIB_DEBUG_REFERENCE)
	void _checkValid();
#endif
	
private:
	sl_reg m_nRefCount;
	sl_bool m_flagWeakRef;
	CWeakRef* m_weak;
	SpinLock m_lockWeak;
	
	friend class CWeakRef;
};


template <class T>
class Ref;

template <class T>
class WeakRef;

template <class T>
using AtomicRef = Atomic< Ref<T> >;

template <class T>
using AtomicWeakRef = Atomic< WeakRef<T> >;

struct _Ref_Const;
extern const _Ref_Const _Ref_Null;

template <class T>
class SLIB_EXPORT Ref
{
public:
	constexpr Ref() : _ptr(sl_null) {}
	
	constexpr Ref(sl_null_t) : _ptr(sl_null) {}
	
	Ref(T* _other);
	
	Ref(Ref<T>&& other);
	
	Ref(const Ref<T>& other);
	
	template <class _T>
	Ref(Ref<_T>&& other);
	
	template <class _T>
	Ref(const Ref<_T>& other);
	
	Ref(AtomicRef<T>&& other);
	
	Ref(const AtomicRef<T>& other);
	
	template <class _T>
	Ref(AtomicRef<_T>&& other);
	
	template <class _T>
	Ref(const AtomicRef<_T>& other);
	
	Ref(const WeakRef<T>& other);
	
	template <class _T>
	Ref(const WeakRef<_T>& other);
	
	Ref(const AtomicWeakRef<T>& other);
	
	template <class _T>
	Ref(const AtomicWeakRef<_T>& other);
	
	~Ref();

public:
	static const Ref<T>& null();
	
	sl_bool isNull() const;

	sl_bool isNotNull() const;

	void setNull();
	
	T* get() const&;
	
	const Ref<Referable>& getReference() const;
	
	template <class _T>
	static const Ref<T>& from(const Ref<_T>& other);
	
	template <class _T>
	static Ref<T>& from(Ref<_T>& other);
	
	template <class _T>
	static Ref<T>&& from(Ref<_T>&& other);
	
public:
	Ref<T>& operator=(sl_null_t);
	
	Ref<T>& operator=(T* other);

	Ref<T>& operator=(Ref<T>&& other);
	
	Ref<T>& operator=(const Ref<T>& other);
	
	template <class _T>
	Ref<T>& operator=(Ref<_T>&& other);
	
	template <class _T>
	Ref<T>& operator=(const Ref<_T>& other);
	
	Ref<T>& operator=(AtomicRef<T>&& other);
	
	Ref<T>& operator=(const AtomicRef<T>& other);
	
	template <class _T>
	Ref<T>& operator=(AtomicRef<_T>&& other);
	
	template <class _T>
	Ref<T>& operator=(const AtomicRef<_T>& other);
	
	Ref<T>& operator=(const WeakRef<T>& other);
	
	template <class _T>
	Ref<T>& operator=(const WeakRef<_T>& other);
	
	Ref<T>& operator=(const AtomicWeakRef<T>& other);
	
	template <class _T>
	Ref<T>& operator=(const AtomicWeakRef<_T>& other);

public:
	sl_bool operator==(sl_null_t) const;
	
	sl_bool operator==(T* other) const;
	
	sl_bool operator==(const Ref<T>& other) const;

	template <class _T>
	sl_bool operator==(const Ref<_T>& other) const;
	
	sl_bool operator==(const AtomicRef<T>& other) const;
	
	template <class _T>
	sl_bool operator==(const AtomicRef<_T>& other) const;
	
	sl_bool operator!=(sl_null_t) const;

	sl_bool operator!=(T* other) const;
	
	sl_bool operator!=(const Ref<T>& other) const;

	template <class _T>
	sl_bool operator!=(const Ref<_T>& other) const;
	
	sl_bool operator!=(const AtomicRef<T>& other) const;
	
	template <class _T>
	sl_bool operator!=(const AtomicRef<_T>& other) const;

public:
	T& operator*() const&;

	T* operator->() const&;

public:
	void _replaceObject(T* other);
	
	void _move_init(void* other);

	void _move_assign(void* other);
	
public:
	T* _ptr;
	
};

template <class T>
class Atomic< Ref<T> >
{
public:
	constexpr Atomic() : _ptr(sl_null) {}
	
	constexpr Atomic(sl_null_t) : _ptr(sl_null) {}
	
	Atomic(T* other);
	
	Atomic(AtomicRef<T>&& other);

	Atomic(const AtomicRef<T>& other);
	
	template <class _T>
	Atomic(AtomicRef<_T>&& other);

	template <class _T>
	Atomic(const AtomicRef<_T>& other);
	
	Atomic(Ref<T>&& other);
	
	Atomic(const Ref<T>& other);
	
	template <class _T>
	Atomic(Ref<_T>&& other);

	template <class _T>
	Atomic(const Ref<_T>& other);
	
	Atomic(const WeakRef<T>& other);
	
	template <class _T>
	Atomic(const WeakRef<_T>& other);
	
	Atomic(const AtomicWeakRef<T>& other);
	
	template <class _T>
	Atomic(const AtomicWeakRef<_T>& other);

	~Atomic();

public:
	static const AtomicRef<T>& null();

	sl_bool isNull() const;

	sl_bool isNotNull() const;

	void setNull();

	template <class _T>
	static const AtomicRef<T>& from(const AtomicRef<_T>& other);
	
	template <class _T>
	static AtomicRef<T>& from(AtomicRef<_T>& other);
	
	template <class _T>
	static AtomicRef<T>&& from(AtomicRef<_T>&& other);

public:
	AtomicRef<T>& operator=(sl_null_t);
	
	AtomicRef<T>& operator=(T* other);
	
	AtomicRef<T>& operator=(AtomicRef<T>&& other);
	
	AtomicRef<T>& operator=(const AtomicRef<T>& other);
	
	template <class _T>
	AtomicRef<T>& operator=(AtomicRef<_T>&& other);

	template <class _T>
	AtomicRef<T>& operator=(const AtomicRef<_T>& other);
	
	AtomicRef<T>& operator=(Ref<T>&& other);

	AtomicRef<T>& operator=(const Ref<T>& other);
	
	template <class _T>
	AtomicRef<T>& operator=(Ref<_T>&& other);

	template <class _T>
	AtomicRef<T>& operator=(const Ref<_T>& other);
	
	AtomicRef<T>& operator=(const WeakRef<T>& other);
	
	template <class _T>
	AtomicRef<T>& operator=(const WeakRef<_T>& other);
	
	AtomicRef<T>& operator=(const AtomicWeakRef<T>& other);
	
	template <class _T>
	AtomicRef<T>& operator=(const AtomicWeakRef<_T>& other);

public:
	sl_bool operator==(sl_null_t) const;
	
	sl_bool operator==(T* other) const;
	
	sl_bool operator==(const AtomicRef<T>& other) const;
	
	template <class _T>
	sl_bool operator==(const AtomicRef<_T>& other) const;
	
	sl_bool operator==(const Ref<T>& other) const;
	
	template <class _T>
	sl_bool operator==(const Ref<_T>& other) const;
	
	sl_bool operator!=(sl_null_t) const;
	
	sl_bool operator!=(T* other) const;
	
	sl_bool operator!=(const AtomicRef<T>& other) const;
	
	template <class _T>
	sl_bool operator!=(const AtomicRef<_T>& other) const;
	
	sl_bool operator!=(const Ref<T>& other) const;
	
	template <class _T>
	sl_bool operator!=(const Ref<_T>& other) const;
	
public:
	Ref<T> operator*() const;

public:
	T* _retainObject() const;
	
	void _replaceObject(T* other);
	
	void _move_init(void* other);
	
	void _move_assign(void* other);
	
public:
	T* _ptr;
private:
	SpinLock m_lock;

};


template <class T>
class SLIB_EXPORT WeakRef
{
public:
	SLIB_INLINE WeakRef() = default;
	
	SLIB_INLINE WeakRef(sl_null_t) {}
	
	WeakRef(T* other);

	WeakRef(WeakRef<T>&& other);
	
	WeakRef(const WeakRef<T>& other);
	
	template <class _T>
	WeakRef(WeakRef<_T>&& other);

	template <class _T>
	WeakRef(const WeakRef<_T>& other);
	
	WeakRef(AtomicWeakRef<T>&& other);

	WeakRef(const AtomicWeakRef<T>& other);
	
	template <class _T>
	WeakRef(AtomicWeakRef<_T>&& other);
	
	template <class _T>
	WeakRef(const AtomicWeakRef<_T>& other);
	
	WeakRef(const Ref<T>& other);

	template <class _T>
	WeakRef(const Ref<_T>& other);

	WeakRef(const AtomicRef<T>& other);
	
	template <class _T>
	WeakRef(const AtomicRef<_T>& other);
	
	~WeakRef();
	
public:
	static const WeakRef<T>& null();
	
	sl_bool isNull() const;
	
	sl_bool isNotNull() const;
	
	void setNull();
	
	template <class _T>
	static const WeakRef<T>& from(const WeakRef<_T>& other);
	
	template <class _T>
	static WeakRef<T>& from(WeakRef<_T>& other);
	
	template <class _T>
	static WeakRef<T>&& from(WeakRef<_T>&& other);
	
	Ref<T> lock() const;
	
	static WeakRef<T> fromReferable(Referable* referable);
	
public:
	WeakRef<T>& operator=(sl_null_t);
	
	WeakRef<T>& operator=(T* other);

	WeakRef<T>& operator=(WeakRef<T>&& other);
	
	WeakRef<T>& operator=(const WeakRef<T>& other);
	
	template <class _T>
	WeakRef<T>& operator=(WeakRef<_T>&& other);

	template <class _T>
	WeakRef<T>& operator=(const WeakRef<_T>& other);
	
	WeakRef<T>& operator=(AtomicWeakRef<T>&& other);
	
	WeakRef<T>& operator=(const AtomicWeakRef<T>& other);
	
	template <class _T>
	WeakRef<T>& operator=(AtomicWeakRef<_T>&& other);
	
	template <class _T>
	WeakRef<T>& operator=(const AtomicWeakRef<_T>& other);

	WeakRef<T>& operator=(const Ref<T>& other);

	template <class _T>
	WeakRef<T>& operator=(const Ref<_T>& other);

	WeakRef<T>& operator=(const AtomicRef<T>& other);
	
	template <class _T>
	WeakRef<T>& operator=(const AtomicRef<_T>& other);
	
public:
	sl_bool operator==(const WeakRef<T>& other) const;
	
	template <class _T>
	sl_bool operator==(const WeakRef<_T>& other) const;
	
	sl_bool operator==(const AtomicWeakRef<T>& other) const;

	template <class _T>
	sl_bool operator==(const AtomicWeakRef<_T>& other) const;

	sl_bool operator!=(const WeakRef<T>& other) const;
	
	template <class _T>
	sl_bool operator!=(const WeakRef<_T>& other) const;
	
	sl_bool operator!=(const AtomicWeakRef<T>& other) const;
	
	template <class _T>
	sl_bool operator!=(const AtomicWeakRef<_T>& other) const;

private:
	void _set(T* other);
	
public:
	Ref<CWeakRef> _weak;
	
};

template <class T>
class SLIB_EXPORT Atomic< WeakRef<T> >
{
public:
	SLIB_INLINE Atomic() = default;
	
	SLIB_INLINE Atomic(sl_null_t) {}
	
	Atomic(T* other);
	
	Atomic(AtomicWeakRef<T>&& other);
	
	Atomic(const AtomicWeakRef<T>& other);
	
	template <class _T>
	Atomic(AtomicWeakRef<_T>&& other);
	
	template <class _T>
	Atomic(const AtomicWeakRef<_T>& other);
	
	Atomic(WeakRef<T>&& other);
	
	Atomic(const WeakRef<T>& other);
	
	template <class _T>
	Atomic(WeakRef<_T>&& other);
	
	template <class _T>
	Atomic(const WeakRef<_T>& other);
	
	Atomic(const Ref<T>& other);
	
	template <class _T>
	Atomic(const Ref<_T>& other);
	
	Atomic(const AtomicRef<T>& other);
	
	template <class _T>
	Atomic(const AtomicRef<_T>& other);
	
	~Atomic();
	
public:
	static const AtomicWeakRef<T>& null();
	
	sl_bool isNull() const;
	
	sl_bool isNotNull() const;
	
	void setNull();
	
	template <class _T>
	static const AtomicWeakRef<T>& from(const AtomicWeakRef<_T>& other);
	
	template <class _T>
	static AtomicWeakRef<T>& from(AtomicWeakRef<_T>& other);
	
	template <class _T>
	static AtomicWeakRef<T>&& from(AtomicWeakRef<_T>&& other);

	Ref<T> lock() const;

public:
	AtomicWeakRef<T>& operator=(sl_null_t);
	
	AtomicWeakRef<T>& operator=(T* other);

	AtomicWeakRef<T>& operator=(AtomicWeakRef<T>&& other);
	
	AtomicWeakRef<T>& operator=(const AtomicWeakRef<T>& other);
	
	template <class _T>
	AtomicWeakRef<T>& operator=(AtomicWeakRef<_T>&& other);
	
	template <class _T>
	AtomicWeakRef<T>& operator=(const AtomicWeakRef<_T>& other);
	
	AtomicWeakRef<T>& operator=(WeakRef<T>&& other);
	
	AtomicWeakRef<T>& operator=(const WeakRef<T>& other);
	
	template <class _T>
	AtomicWeakRef<T>& operator=(WeakRef<_T>&& other);
	
	template <class _T>
	AtomicWeakRef<T>& operator=(const WeakRef<_T>& other);
	
	AtomicWeakRef<T>& operator=(const Ref<T>& other);
	
	template <class _T>
	AtomicWeakRef<T>& operator=(const Ref<_T>& other);
	
	AtomicWeakRef<T>& operator=(const AtomicRef<T>& other);
	
	template <class _T>
	AtomicWeakRef<T>& operator=(const AtomicRef<_T>& other);
	
public:
	sl_bool operator==(const AtomicWeakRef<T>& other) const;
	
	template <class _T>
	sl_bool operator==(const AtomicWeakRef<_T>& other) const;
	
	sl_bool operator==(const WeakRef<T>& other) const;
	
	template <class _T>
	sl_bool operator==(const WeakRef<_T>& other) const;
	
	sl_bool operator!=(const AtomicWeakRef<T>& other) const;
	
	template <class _T>
	sl_bool operator!=(const AtomicWeakRef<_T>& other) const;
	
	sl_bool operator!=(const WeakRef<T>& other) const;
	
	template <class _T>
	sl_bool operator!=(const WeakRef<_T>& other) const;
	
public:
	WeakRef<T> operator*() const;

private:
	void _set(T* other);
	
public:
	AtomicRef<CWeakRef> _weak;

};

template <class T>
struct PropertyTypeHelper< WeakRef<T> >
{
	typedef Ref<T> const& ArgType;
	typedef Ref<T> RetType;
};


class SLIB_EXPORT CWeakRef : public Referable
{
	SLIB_DECLARE_OBJECT
public:
	CWeakRef();
	
public:
	Referable* m_object;
	SpinLock m_lock;
	
public:
	static CWeakRef* create(Referable* object);
	
public:
	Ref<Referable> lock();
	
	void release();
};

class SLIB_EXPORT ReferableKeeper
{
public:
	ReferableKeeper(Referable* object);
	
	~ReferableKeeper();
	
private:
	Referable* m_object;
	
};

template <class T, class... ARGS>
SLIB_INLINE Ref<T> New(ARGS&&... args)
{
	return new T(Forward<ARGS>(args)...);
}

template <class REF, class T>
struct _InitHelper
{
	template <class... ARGS>
	SLIB_INLINE static void init(REF* o, ARGS&&... args) { (*o) = (*o)->init(Forward<ARGS>(args)...); }
};

template <class REF>
struct _InitHelper<REF, void>
{
	template <class... ARGS>
	SLIB_INLINE static void init(REF* o, ARGS&&... args) { (*o)->init(Forward<ARGS>(args)...); }
};

template <class T, class... ARGS>
SLIB_INLINE Ref<T> Init(ARGS&&... args)
{
	Ref<T> o = new T;
	if (o.isNotNull()) {
		_InitHelper<Ref<T>, decltype(o->init(args...))>::init(&o, Forward<ARGS>(args)...);
		return o;
	}
	return sl_null;
}

template <class T, class _T>
SLIB_INLINE sl_bool IsInstanceOf(_T* object)
{
	SLIB_TRY_CONVERT_TYPE(_T*, Referable*)
	if (object) {
		return object->isInstanceOf(T::ObjectType());
	}
	return sl_false;
}

template <class T, class _T>
SLIB_INLINE sl_bool IsInstanceOf(const Ref<_T>& object)
{
	SLIB_TRY_CONVERT_TYPE(_T*, Referable*)
	if (object.isNotNull()) {
		return object->isInstanceOf(T::ObjectType());
	}
	return sl_false;
}

template <class T, class _T>
SLIB_INLINE T* CastInstance(_T* object)
{
	SLIB_TRY_CONVERT_TYPE(_T*, Referable*)
	if (object) {
		if (object->isInstanceOf(T::ObjectType())) {
			return static_cast<T*>(object);
		}
	}
	return sl_null;
}

template <class T, class _T>
SLIB_INLINE const Ref<T>& CastRef(const Ref<_T>& object)
{
	SLIB_TRY_CONVERT_TYPE(_T*, Referable*)
	if (object.isNotNull()) {
		if (object->isInstanceOf(T::ObjectType())) {
			return *(reinterpret_cast<Ref<T> const*>(&object));
		}
	}
	return Ref<T>::null();
}

template <class T, class _T>
SLIB_INLINE const Ref<T>& CastRef(const Ref<_T>& object, const Ref<T>& def)
{
	SLIB_TRY_CONVERT_TYPE(_T*, Referable*)
	if (object.isNotNull()) {
		if (object->isInstanceOf(T::ObjectType())) {
			return *(reinterpret_cast<Ref<T> const*>(&object));
		}
	}
	return def;
}

SLIB_NAMESPACE_END


SLIB_NAMESPACE_BEGIN

template <class T>
SLIB_INLINE Ref<T>::Ref(T* other)
{
	if (other) {
		other->increaseReference();
	}
	_ptr = other;
}

template <class T>
SLIB_INLINE Ref<T>::Ref(Ref<T>&& other)
{
	_move_init(&other);
}

template <class T>
SLIB_INLINE Ref<T>::Ref(const Ref<T>& other)
{
	T* o = other._ptr;
	if (o) {
		o->increaseReference();
	}
	_ptr = o;
}

template <class T>
template <class _T>
SLIB_INLINE Ref<T>::Ref(Ref<_T>&& other)
{
	SLIB_TRY_CONVERT_TYPE(_T*, T*)
	_move_init(&other);
}

template <class T>
template <class _T>
SLIB_INLINE Ref<T>::Ref(const Ref<_T>& other)
{
	SLIB_TRY_CONVERT_TYPE(_T*, T*)
	T* o = other._ptr;
	if (o) {
		o->increaseReference();
	}
	_ptr = o;
}

template <class T>
Ref<T>::Ref(AtomicRef<T>&& other)
{
	_move_init(&other);
}

template <class T>
Ref<T>::Ref(const AtomicRef<T>& other)
{
	T* o = other._retainObject();
	_ptr = o;
}

template <class T>
template <class _T>
Ref<T>::Ref(AtomicRef<_T>&& other)
{
	SLIB_TRY_CONVERT_TYPE(_T*, T*)
	_move_init(&other);
}

template <class T>
template <class _T>
Ref<T>::Ref(const AtomicRef<_T>& other)
{
	SLIB_TRY_CONVERT_TYPE(_T*, T*)
	T* o = other._retainObject();
	_ptr = o;
}

template <class T>
Ref<T>::Ref(const WeakRef<T>& _other)
{
	Ref<T> other(_other.lock());
	T* o = other._ptr;
	if (o) {
		o->increaseReference();
	}
	_ptr = o;
}

template <class T>
template <class _T>
Ref<T>::Ref(const WeakRef<_T>& _other)
{
	SLIB_TRY_CONVERT_TYPE(_T*, T*)
	Ref<_T> other(_other.lock());
	T* o = other._ptr;
	if (o) {
		o->increaseReference();
	}
	_ptr = o;
}

template <class T>
Ref<T>::Ref(const AtomicWeakRef<T>& _other)
{
	Ref<T> other(_other.lock());
	T* o = other._ptr;
	if (o) {
		o->increaseReference();
	}
	_ptr = o;
}

template <class T>
template <class _T>
Ref<T>::Ref(const AtomicWeakRef<_T>& _other)
{
	SLIB_TRY_CONVERT_TYPE(_T*, T*)
	Ref<_T> other(_other.lock());
	T* o = other._ptr;
	if (o) {
		o->increaseReference();
	}
	_ptr = o;
}

template <class T>
SLIB_INLINE Ref<T>::~Ref()
{
	SLIB_TRY_CONVERT_TYPE(T*, Referable*)
	if (_ptr) {
		_ptr->decreaseReference();
	}
}

template <class T>
SLIB_INLINE const Ref<T>& Ref<T>::null()
{
	return *(reinterpret_cast<Ref<T> const*>(&_Ref_Null));
}

template <class T>
SLIB_INLINE sl_bool Ref<T>::isNull() const
{
	return (_ptr == sl_null);
}

template <class T>
SLIB_INLINE sl_bool Ref<T>::isNotNull() const
{
	return (_ptr != sl_null);
}

template <class T>
void Ref<T>::setNull()
{
	_replaceObject(sl_null);
}

template <class T>
template <class _T>
SLIB_INLINE const Ref<T>& Ref<T>::from(const Ref<_T>& other)
{
	return *(reinterpret_cast<Ref<T> const*>(&other));
}

template <class T>
template <class _T>
SLIB_INLINE Ref<T>& Ref<T>::from(Ref<_T>& other)
{
	return *(reinterpret_cast<Ref<T>*>(&other));
}

template <class T>
template <class _T>
SLIB_INLINE Ref<T>&& Ref<T>::from(Ref<_T>&& other)
{
	return static_cast<Ref<T>&&>(*(reinterpret_cast<Ref<T>*>(&other)));
}

template <class T>
SLIB_INLINE T* Ref<T>::get() const&
{
	return _ptr;
}

template <class T>
const Ref<Referable>& Ref<T>::getReference() const
{
	return *(reinterpret_cast<Ref<Referable> const*>(this));
}

template <class T>
Ref<T>& Ref<T>::operator=(sl_null_t)
{
	_replaceObject(sl_null);
	return *this;
}

template <class T>
Ref<T>& Ref<T>::operator=(T* other)
{
	if (_ptr != other) {
		if (other) {
			other->increaseReference();
		}
		_replaceObject(other);
	}
	return *this;
}

template <class T>
Ref<T>& Ref<T>::operator=(Ref<T>&& other)
{
	_move_assign(&other);
	return *this;
}

template <class T>
Ref<T>& Ref<T>::operator=(const Ref<T>& other)
{
	T* o = other._ptr;
	if (_ptr != o) {
		if (o) {
			o->increaseReference();
		}
		_replaceObject(o);
	}
	return *this;
}

template <class T>
template <class _T>
Ref<T>& Ref<T>::operator=(Ref<_T>&& other)
{
	SLIB_TRY_CONVERT_TYPE(_T*, T*)
	_move_assign(&other);
	return *this;
}

template <class T>
template <class _T>
Ref<T>& Ref<T>::operator=(const Ref<_T>& other)
{
	SLIB_TRY_CONVERT_TYPE(_T*, T*)
	T* o = other._ptr;
	if (_ptr != o) {
		if (o) {
			o->increaseReference();
		}
		_replaceObject(o);
	}
	return *this;
}

template <class T>
Ref<T>& Ref<T>::operator=(AtomicRef<T>&& other)
{
	_move_assign(&other);
	return *this;
}

template <class T>
Ref<T>& Ref<T>::operator=(const AtomicRef<T>& other)
{
	T* o = other._retainObject();
	_replaceObject(o);
	return *this;
}

template <class T>
template <class _T>
Ref<T>& Ref<T>::operator=(AtomicRef<_T>&& other)
{
	SLIB_TRY_CONVERT_TYPE(_T*, T*)
	_move_assign(&other);
	return *this;
}


template <class T>
template <class _T>
Ref<T>& Ref<T>::operator=(const AtomicRef<_T>& other)
{
	SLIB_TRY_CONVERT_TYPE(_T*, T*)
	T* o = other._retainObject();
	_replaceObject(o);
	return *this;
}

template <class T>
Ref<T>& Ref<T>::operator=(const WeakRef<T>& _other)
{
	Ref<T> other(_other.lock());
	T* o = other._ptr;
	if (o) {
		o->increaseReference();
	}
	_replaceObject(o);
	return *this;
}

template <class T>
template <class _T>
Ref<T>& Ref<T>::operator=(const WeakRef<_T>& _other)
{
	SLIB_TRY_CONVERT_TYPE(_T*, T*)
	Ref<_T> other(_other.lock());
	T* o = other._ptr;
	if (o) {
		o->increaseReference();
	}
	_replaceObject(o);
	return *this;
}

template <class T>
Ref<T>& Ref<T>::operator=(const AtomicWeakRef<T>& _other)
{
	Ref<T> other(_other.lock());
	T* o = other._ptr;
	if (o) {
		o->increaseReference();
	}
	_replaceObject(o);
	return *this;
}

template <class T>
template <class _T>
Ref<T>& Ref<T>::operator=(const AtomicWeakRef<_T>& _other)
{
	SLIB_TRY_CONVERT_TYPE(_T*, T*)
	Ref<_T> other(_other.lock());
	T* o = other._ptr;
	if (o) {
		o->increaseReference();
	}
	_replaceObject(o);
	return *this;
}

template <class T>
sl_bool Ref<T>::operator==(sl_null_t) const
{
	return _ptr == sl_null;
}

template <class T>
sl_bool Ref<T>::operator==(T* other) const
{
	return _ptr == other;
}

template <class T>
sl_bool operator==(sl_null_t, const Ref<T>& b)
{
	return sl_null == b._ptr;
}

template <class T>
sl_bool operator==(T* a, const Ref<T>& b)
{
	return a == b._ptr;
}

template <class T>
SLIB_INLINE sl_bool Ref<T>::operator==(const Ref<T>& other) const
{
	return _ptr == other._ptr;
}

template <class T>
template <class _T>
sl_bool Ref<T>::operator==(const Ref<_T>& other) const
{
	return (void*)_ptr == (void*)(other._ptr);
}

template <class T>
sl_bool Ref<T>::operator==(const AtomicRef<T>& other) const
{
	return _ptr == other._ptr;
}

template <class T>
template <class _T>
sl_bool Ref<T>::operator==(const AtomicRef<_T>& other) const
{
	return (void*)_ptr == (void*)(other._ptr);
}

template <class T>
sl_bool Ref<T>::operator!=(sl_null_t) const
{
	return _ptr != sl_null;
}

template <class T>
sl_bool Ref<T>::operator!=(T* other) const
{
	return _ptr != other;
}

template <class T>
sl_bool operator!=(sl_null_t, const Ref<T>& b)
{
	return sl_null != b._ptr;
}

template <class T>
sl_bool operator!=(T* a, const Ref<T>& b)
{
	return a != b._ptr;
}

template <class T>
sl_bool Ref<T>::operator!=(const Ref<T>& other) const
{
	return _ptr != other._ptr;
}

template <class T>
template <class _T>
sl_bool Ref<T>::operator!=(const Ref<_T>& other) const
{
	return (void*)_ptr != (void*)(other._ptr);
}

template <class T>
sl_bool Ref<T>::operator!=(const AtomicRef<T>& other) const
{
	return _ptr != other._ptr;
}

template <class T>
template <class _T>
sl_bool Ref<T>::operator!=(const AtomicRef<_T>& other) const
{
	return (void*)_ptr != (void*)(other._ptr);
}

template <class T>
SLIB_INLINE T& Ref<T>::operator*() const&
{
	return *(_ptr);
}

template <class T>
SLIB_INLINE T* Ref<T>::operator->() const&
{
	return _ptr;
}

template <class T>
SLIB_INLINE void Ref<T>::_replaceObject(T* other)
{
	if (_ptr) {
		_ptr->decreaseReference();
	}
	_ptr = other;
}

template <class T>
SLIB_INLINE void Ref<T>::_move_init(void* _other)
{
	Ref<T>& other = *(reinterpret_cast<Ref<T>*>(_other));
	_ptr = other._ptr;
	other._ptr = sl_null;
}

template <class T>
SLIB_INLINE void Ref<T>::_move_assign(void* _other)
{
	if ((void*)this != _other) {
		Ref<T>& other = *(reinterpret_cast<Ref<T>*>(_other));
		_replaceObject(other._ptr);
		other._ptr = sl_null;
	}
}


template <class T>
Atomic< Ref<T> >::Atomic(T* other)
{
	if (other) {
		other->increaseReference();
	}
	_ptr = other;
}

template <class T>
Atomic< Ref<T> >::Atomic(AtomicRef<T>&& other)
{
	_move_init(&other);
}

template <class T>
Atomic< Ref<T> >::Atomic(const AtomicRef<T>& other)
{
	T* o = other._retainObject();
	_ptr = o;
}

template <class T>
template <class _T>
Atomic< Ref<T> >::Atomic(AtomicRef<_T>&& other)
{
	SLIB_TRY_CONVERT_TYPE(_T*, T*)
	_move_init(&other);
}

template <class T>
template <class _T>
Atomic< Ref<T> >::Atomic(const AtomicRef<_T>& other)
{
	SLIB_TRY_CONVERT_TYPE(_T*, T*)
	T* o = other._retainObject();
	_ptr = o;
}

template <class T>
Atomic< Ref<T> >::Atomic(Ref<T>&& other)
{
	_move_init(&other);
}

template <class T>
Atomic< Ref<T> >::Atomic(const Ref<T>& other)
{
	T* o = other._ptr;
	if (o) {
		o->increaseReference();
	}
	_ptr = o;
}

template <class T>
template <class _T>
Atomic< Ref<T> >::Atomic(Ref<_T>&& other)
{
	_move_init(&other);
}

template <class T>
template <class _T>
Atomic< Ref<T> >::Atomic(const Ref<_T>& other)
{
	SLIB_TRY_CONVERT_TYPE(_T*, T*)
	T* o = other._ptr;
	if (o) {
		o->increaseReference();
	}
	_ptr = o;
}

template <class T>
Atomic< Ref<T> >::Atomic(const WeakRef<T>& _other)
{
	Ref<T> other(_other.lock());
	T* o = other._ptr;
	if (o) {
		o->increaseReference();
	}
	_ptr = o;
}

template <class T>
template <class _T>
Atomic< Ref<T> >::Atomic(const WeakRef<_T>& _other)
{
	SLIB_TRY_CONVERT_TYPE(_T*, T*)
	Ref<_T> other(_other.lock());
	T* o = other._ptr;
	if (o) {
		o->increaseReference();
	}
	_ptr = o;
}

template <class T>
Atomic< Ref<T> >::Atomic(const AtomicWeakRef<T>& _other)
{
	Ref<T> other(_other.lock());
	T* o = other._ptr;
	if (o) {
		o->increaseReference();
	}
	_ptr = o;
}

template <class T>
template <class _T>
Atomic< Ref<T> >::Atomic(const AtomicWeakRef<_T>& _other)
{
	SLIB_TRY_CONVERT_TYPE(_T*, T*)
	Ref<_T> other(_other.lock());
	T* o = other._ptr;
	if (o) {
		o->increaseReference();
	}
	_ptr = o;
}

template <class T>
Atomic< Ref<T> >::~Atomic()
{
	SLIB_TRY_CONVERT_TYPE(T*, Referable*)
	T* ptr = _ptr;
	if (ptr) {
		ptr->decreaseReference();
	}
}

template <class T>
SLIB_INLINE const AtomicRef<T>& Atomic< Ref<T> >::null()
{
	return *(reinterpret_cast<AtomicRef<T> const*>(&_Ref_Null));
}

template <class T>
sl_bool Atomic< Ref<T> >::isNull() const
{
	return (_ptr == sl_null);
}

template <class T>
sl_bool Atomic< Ref<T> >::isNotNull() const
{
	return (_ptr != sl_null);
}

template <class T>
void Atomic< Ref<T> >::setNull()
{
	_replaceObject(sl_null);
}

template <class T>
template <class _T>
SLIB_INLINE const AtomicRef<T>& Atomic< Ref<T> >::from(const AtomicRef<_T>& other)
{
	return *(reinterpret_cast<AtomicRef<T> const*>(&other));
}

template <class T>
template <class _T>
SLIB_INLINE AtomicRef<T>& Atomic< Ref<T> >::from(AtomicRef<_T>& other)
{
	return *(reinterpret_cast<AtomicRef<T>*>(&other));
}

template <class T>
template <class _T>
SLIB_INLINE AtomicRef<T>&& Atomic< Ref<T> >::from(AtomicRef<_T>&& other)
{
	return static_cast<AtomicRef<T>&&>(*(reinterpret_cast<AtomicRef<T>*>(&other)));
}

template <class T>
AtomicRef<T>& Atomic< Ref<T> >::operator=(sl_null_t)
{
	_replaceObject(sl_null);
	return *this;
}

template <class T>
AtomicRef<T>& Atomic< Ref<T> >::operator=(T* other)
{
	if (_ptr != other) {
		if (other) {
			other->increaseReference();
		}
		_replaceObject(other);
	}
	return *this;
}

template <class T>
AtomicRef<T>& Atomic< Ref<T> >::operator=(AtomicRef<T>&& other)
{
	_move_assign(&other);
	return *this;
}

template <class T>
AtomicRef<T>& Atomic< Ref<T> >::operator=(const AtomicRef<T>& other)
{
	if (_ptr != other._ptr) {
		T* o = other._retainObject();
		_replaceObject(o);
	}
	return *this;
}

template <class T>
template <class _T>
AtomicRef<T>& Atomic< Ref<T> >::operator=(AtomicRef<_T>&& other)
{
	SLIB_TRY_CONVERT_TYPE(_T*, T*)
	_move_assign(&other);
	return *this;
}

template <class T>
template <class _T>
AtomicRef<T>& Atomic< Ref<T> >::operator=(const AtomicRef<_T>& other)
{
	SLIB_TRY_CONVERT_TYPE(_T*, T*)
	if (_ptr != other._ptr) {
		T* o = other._retainObject();
		_replaceObject(o);
	}
	return *this;
}

template <class T>
AtomicRef<T>& Atomic< Ref<T> >::operator=(Ref<T>&& other)
{
	_move_assign(&other);
	return *this;
}

template <class T>
AtomicRef<T>& Atomic< Ref<T> >::operator=(const Ref<T>& other)
{
	T* o = other._ptr;
	if (_ptr != o) {
		if (o) {
			o->increaseReference();
		}
		_replaceObject(o);
	}
	return *this;
}

template <class T>
template <class _T>
AtomicRef<T>& Atomic< Ref<T> >::operator=(Ref<_T>&& other)
{
	SLIB_TRY_CONVERT_TYPE(_T*, T*)
	_move_assign(&other);
	return *this;
}

template <class T>
template <class _T>
AtomicRef<T>& Atomic< Ref<T> >::operator=(const Ref<_T>& other)
{
	SLIB_TRY_CONVERT_TYPE(_T*, T*)
	T* o = other._ptr;
	if (_ptr != o) {
		if (o) {
			o->increaseReference();
		}
		_replaceObject(o);
	}
	return *this;
}

template <class T>
AtomicRef<T>& Atomic< Ref<T> >::operator=(const WeakRef<T>& _other)
{
	Ref<T> other(_other.lock());
	T* o = other._ptr;
	if (o) {
		o->increaseReference();
	}
	_replaceObject(o);
	return *this;
}

template <class T>
template <class _T>
AtomicRef<T>& Atomic< Ref<T> >::operator=(const WeakRef<_T>& _other)
{
	SLIB_TRY_CONVERT_TYPE(_T*, T*)
	Ref<_T> other(_other.lock());
	T* o = other._ptr;
	if (o) {
		o->increaseReference();
	}
	_replaceObject(o);
	return *this;
}

template <class T>
AtomicRef<T>& Atomic< Ref<T> >::operator=(const AtomicWeakRef<T>& _other)
{
	Ref<T> other(_other.lock());
	T* o = other._ptr;
	if (o) {
		o->increaseReference();
	}
	_replaceObject(o);
	return *this;
}

template <class T>
template <class _T>
AtomicRef<T>& Atomic< Ref<T> >::operator=(const AtomicWeakRef<_T>& _other)
{
	SLIB_TRY_CONVERT_TYPE(_T*, T*)
	Ref<_T> other(_other.lock());
	T* o = other._ptr;
	if (o) {
		o->increaseReference();
	}
	_replaceObject(o);
	return *this;
}

template <class T>
sl_bool Atomic< Ref<T> >::operator==(sl_null_t) const
{
	return _ptr == sl_null;
}

template <class T>
sl_bool Atomic< Ref<T> >::operator==(T* other) const
{
	return _ptr == other;
}

template <class T>
sl_bool operator==(sl_null_t, const AtomicRef<T>& b)
{
	return sl_null == b._ptr;
}

template <class T>
sl_bool operator==(T* a, const AtomicRef<T>& b)
{
	return a == b._ptr;
}

template <class T>
sl_bool Atomic< Ref<T> >::operator==(const AtomicRef<T>& other) const
{
	return _ptr == other._ptr;
}

template <class T>
template <class _T>
sl_bool Atomic< Ref<T> >::operator==(const AtomicRef<_T>& other) const
{
	return (void*)_ptr == (void*)(other._ptr);
}

template <class T>
sl_bool Atomic< Ref<T> >::operator==(const Ref<T>& other) const
{
	return _ptr == other._ptr;
}

template <class T>
template <class _T>
sl_bool Atomic< Ref<T> >::operator==(const Ref<_T>& other) const
{
	return (void*)_ptr == (void*)(other._ptr);
}

template <class T>
sl_bool Atomic< Ref<T> >::operator!=(sl_null_t) const
{
	return _ptr != sl_null;
}

template <class T>
sl_bool Atomic< Ref<T> >::operator!=(T* other) const
{
	return _ptr != other;
}

template <class T>
sl_bool operator!=(sl_null_t, const AtomicRef<T>& b)
{
	return sl_null != b._ptr;
}

template <class T>
sl_bool operator!=(T* a, const AtomicRef<T>& b)
{
	return a != b._ptr;
}

template <class T>
sl_bool Atomic< Ref<T> >::operator!=(const AtomicRef<T>& other) const
{
	return _ptr != other._ptr;
}

template <class T>
template <class _T>
sl_bool Atomic< Ref<T> >::operator!=(const AtomicRef<_T>& other) const
{
	return (void*)_ptr != (void*)(other._ptr);
}

template <class T>
sl_bool Atomic< Ref<T> >::operator!=(const Ref<T>& other) const
{
	return _ptr != other._ptr;
}

template <class T>
template <class _T>
sl_bool Atomic< Ref<T> >::operator!=(const Ref<_T>& other) const
{
	return (void*)_ptr != (void*)(other._ptr);
}

template <class T>
Ref<T> Atomic< Ref<T> >::operator*() const
{
	return *this;
}

template <class T>
SLIB_INLINE T* Atomic< Ref<T> >::_retainObject() const
{
	if (_ptr) {
		SpinLocker lock(&m_lock);
		T* ptr = _ptr;
		if (ptr) {
			ptr->increaseReference();
		}
		return ptr;
	} else {
		return sl_null;
	}
}

template <class T>
SLIB_INLINE void Atomic< Ref<T> >::_replaceObject(T* other)
{
	T* before;
	{
		SpinLocker lock(&m_lock);
		before = _ptr;
		_ptr = other;
	}
	if (before) {
		before->decreaseReference();
	}
}

template <class T>
SLIB_INLINE void Atomic< Ref<T> >::_move_init(void* _other)
{
	AtomicRef<T>& other = *(reinterpret_cast<AtomicRef<T>*>(_other));
	_ptr = other._ptr;
	other._ptr = sl_null;
}

template <class T>
SLIB_INLINE void Atomic< Ref<T> >::_move_assign(void* _other)
{
	if ((void*)this != _other) {
		AtomicRef<T>& other = *(reinterpret_cast<AtomicRef<T>*>(_other));
		_replaceObject(other._ptr);
		other._ptr = sl_null;
	}
}


template <class T>
WeakRef<T>::WeakRef(T* _other)
{
	_set(_other);
}

template <class T>
SLIB_INLINE WeakRef<T>::WeakRef(WeakRef<T>&& other)
{
	_weak._move_init(&other);
}

template <class T>
SLIB_INLINE WeakRef<T>::WeakRef(const WeakRef<T>& other) : _weak(other._weak)
{
}

template <class T>
template <class _T>
WeakRef<T>::WeakRef(WeakRef<_T>&& other)
{
	SLIB_TRY_CONVERT_TYPE(_T*, T*)
	_weak._move_init(&other);
}

template <class T>
template <class _T>
WeakRef<T>::WeakRef(const WeakRef<_T>& other) : _weak(other._weak)
{
	SLIB_TRY_CONVERT_TYPE(_T*, T*)
}

template <class T>
WeakRef<T>::WeakRef(AtomicWeakRef<T>&& other)
{
	_weak._move_init(&other);
}


template <class T>
WeakRef<T>::WeakRef(const AtomicWeakRef<T>& other) : _weak(other._weak)
{
}

template <class T>
template <class _T>
WeakRef<T>::WeakRef(AtomicWeakRef<_T>&& other)
{
	SLIB_TRY_CONVERT_TYPE(_T*, T*)
	_weak._move_init(&other);
}

template <class T>
template <class _T>
WeakRef<T>::WeakRef(const AtomicWeakRef<_T>& other) : _weak(other._weak)
{
	SLIB_TRY_CONVERT_TYPE(_T*, T*)
}

template <class T>
WeakRef<T>::WeakRef(const Ref<T>& other)
{
	_set(other._ptr);
}

template <class T>
template <class _T>
WeakRef<T>::WeakRef(const Ref<_T>& other)
{
	SLIB_TRY_CONVERT_TYPE(_T*, T*)
	_set(other._ptr);
}

template <class T>
WeakRef<T>::WeakRef(const AtomicRef<T>& _other)
{
	Ref<T> other(_other);
	_set(other._ptr);
}

template <class T>
template <class _T>
WeakRef<T>::WeakRef(const AtomicRef<_T>& _other)
{
	SLIB_TRY_CONVERT_TYPE(_T*, T*)
	Ref<_T> other(_other);
	_set(other._ptr);
}

template <class T>
WeakRef<T>::~WeakRef()
{
	SLIB_TRY_CONVERT_TYPE(T*, Referable*)
}

template <class T>
SLIB_INLINE const WeakRef<T>& WeakRef<T>::null()
{
	return *(reinterpret_cast<WeakRef<T> const*>(&_Ref_Null));
}

template <class T>
sl_bool WeakRef<T>::isNull() const
{
	return _weak.isNull();
}

template <class T>
sl_bool WeakRef<T>::isNotNull() const
{
	return _weak.isNotNull();
}

template <class T>
void WeakRef<T>::setNull()
{
	_weak.setNull();
}

template <class T>
template <class _T>
SLIB_INLINE const WeakRef<T>& WeakRef<T>::from(const WeakRef<_T>& other)
{
	return *(reinterpret_cast<WeakRef<T> const*>(&other));
}

template <class T>
template <class _T>
SLIB_INLINE WeakRef<T>& WeakRef<T>::from(WeakRef<_T>& other)
{
	return *(reinterpret_cast<WeakRef<T>*>(&other));
}

template <class T>
template <class _T>
SLIB_INLINE WeakRef<T>&& WeakRef<T>::from(WeakRef<_T>&& other)
{
	return static_cast<WeakRef<T>&&>(*(reinterpret_cast<WeakRef<T>*>(&other)));
}

template <class T>
Ref<T> WeakRef<T>::lock() const
{
	if (_weak.isNotNull()) {
		return Ref<T>::from(_weak->lock());
	}
	return sl_null;
}

template <class T>
WeakRef<T> WeakRef<T>::fromReferable(Referable* referable)
{
	if (referable) {
		WeakRef<T> ret;
		if (referable->_isWeakRef()) {
			ret._weak = static_cast<CWeakRef*>(referable);
		} else {
			ret._weak = referable->_getWeakObject();
		}
		return ret;
	} else {
		return sl_null;
	}
}

template <class T>
WeakRef<T>& WeakRef<T>::operator=(sl_null_t)
{
	_weak.setNull();
	return *this;
}

template <class T>
WeakRef<T>& WeakRef<T>::operator=(T* _other)
{
	_set(_other);
	return *this;
}

template <class T>
SLIB_INLINE WeakRef<T>& WeakRef<T>::operator=(WeakRef<T>&& other)
{
	_weak._move_assign(&other);
	return *this;
}

template <class T>
SLIB_INLINE WeakRef<T>& WeakRef<T>::operator=(const WeakRef<T>& other)
{
	_weak = other._weak;
	return *this;
}

template <class T>
template <class _T>
WeakRef<T>& WeakRef<T>::operator=(WeakRef<_T>&& other)
{
	SLIB_TRY_CONVERT_TYPE(_T*, T*)
	_weak._move_assign(&other);
	return *this;
}

template <class T>
template <class _T>
WeakRef<T>& WeakRef<T>::operator=(const WeakRef<_T>& other)
{
	SLIB_TRY_CONVERT_TYPE(_T*, T*)
	_weak = other._weak;
	return *this;
}

template <class T>
WeakRef<T>& WeakRef<T>::operator=(AtomicWeakRef<T>&& other)
{
	_weak._move_assign(&other);
	return *this;
}


template <class T>
WeakRef<T>& WeakRef<T>::operator=(const AtomicWeakRef<T>& other)
{
	_weak = other._weak;
	return *this;
}


template <class T>
template <class _T>
SLIB_INLINE WeakRef<T>& WeakRef<T>::operator=(AtomicWeakRef<_T>&& other)
{
	SLIB_TRY_CONVERT_TYPE(_T*, T*)
	_weak._move_assign(&other);
	return *this;
}


template <class T>
template <class _T>
WeakRef<T>& WeakRef<T>::operator=(const AtomicWeakRef<_T>& other)
{
	SLIB_TRY_CONVERT_TYPE(_T*, T*)
	_weak = other._weak;
	return *this;
}

template <class T>
WeakRef<T>& WeakRef<T>::operator=(const Ref<T>& other)
{
	_set(other._ptr);
	return *this;
}

template <class T>
template <class _T>
WeakRef<T>& WeakRef<T>::operator=(const Ref<_T>& other)
{
	SLIB_TRY_CONVERT_TYPE(_T*, T*)
	_set(other._ptr);
	return *this;
}

template <class T>
WeakRef<T>& WeakRef<T>::operator=(const AtomicRef<T>& _other)
{
	Ref<T> other(_other);
	_set(other._ptr);
	return *this;
}

template <class T>
template <class _T>
WeakRef<T>& WeakRef<T>::operator=(const AtomicRef<_T>& _other)
{
	SLIB_TRY_CONVERT_TYPE(_T*, T*)
	Ref<_T> other(_other);
	_set(other._ptr);
	return *this;
}

template <class T>
sl_bool WeakRef<T>::operator==(const WeakRef<T>& other) const
{
	return _weak == other._weak;
}

template <class T>
template <class _T>
sl_bool WeakRef<T>::operator==(const WeakRef<_T>& other) const
{
	return _weak == other._weak;
}


template <class T>
sl_bool WeakRef<T>::operator==(const AtomicWeakRef<T>& other) const
{
	return _weak == other._weak;
}

template <class T>
template <class _T>
sl_bool WeakRef<T>::operator==(const AtomicWeakRef<_T>& other) const
{
	return _weak == other._weak;
}


template <class T>
sl_bool WeakRef<T>::operator!=(const WeakRef<T>& other) const
{
	return _weak != other._weak;
}

template <class T>
template <class _T>
sl_bool WeakRef<T>::operator!=(const WeakRef<_T>& other) const
{
	return _weak != other._weak;
}


template <class T>
sl_bool WeakRef<T>::operator!=(const AtomicWeakRef<T>& other) const
{
	return _weak != other._weak;
}

template <class T>
template <class _T>
sl_bool WeakRef<T>::operator!=(const AtomicWeakRef<_T>& other) const
{
	return _weak != other._weak;
}

template <class T>
SLIB_INLINE void WeakRef<T>::_set(T* object)
{
	if (object) {
		_weak = object->_getWeakObject();
	} else {
		_weak.setNull();
	}
}


template <class T>
Atomic< WeakRef<T> >::Atomic(T* _other)
{
	_set(_other);
}

template <class T>
Atomic< WeakRef<T> >::Atomic(AtomicWeakRef<T>&& other)
{
	_weak._move_init(&other);
}

template <class T>
Atomic< WeakRef<T> >::Atomic(const AtomicWeakRef<T>& other) : _weak(other._weak)
{
}

template <class T>
template <class _T>
Atomic< WeakRef<T> >::Atomic(AtomicWeakRef<_T>&& other)
{
	SLIB_TRY_CONVERT_TYPE(_T*, T*)
	_weak._move_init(&other);
}

template <class T>
template <class _T>
Atomic< WeakRef<T> >::Atomic(const AtomicWeakRef<_T>& other) : _weak(other._weak)
{
	SLIB_TRY_CONVERT_TYPE(_T*, T*)
}

template <class T>
Atomic< WeakRef<T> >::Atomic(WeakRef<T>&& other)
{
	_weak._move_init(&other);
}

template <class T>
Atomic< WeakRef<T> >::Atomic(const WeakRef<T>& other) : _weak(other._weak)
{
}

template <class T>
template <class _T>
Atomic< WeakRef<T> >::Atomic(WeakRef<_T>&& other)
{
	SLIB_TRY_CONVERT_TYPE(_T*, T*)
	_weak._move_init(&other);
}

template <class T>
template <class _T>
Atomic< WeakRef<T> >::Atomic(const WeakRef<_T>& other) : _weak(other._weak)
{
	SLIB_TRY_CONVERT_TYPE(_T*, T*)
}

template <class T>
Atomic< WeakRef<T> >::Atomic(const Ref<T>& other)
{
	_set(other._ptr);
}

template <class T>
template <class _T>
Atomic< WeakRef<T> >::Atomic(const Ref<_T>& other)
{
	SLIB_TRY_CONVERT_TYPE(_T*, T*)
	_set(other._ptr);
}

template <class T>
Atomic< WeakRef<T> >::Atomic(const AtomicRef<T>& _other)
{
	Ref<T> other(_other);
	_set(other._ptr);
}

template <class T>
template <class _T>
Atomic< WeakRef<T> >::Atomic(const AtomicRef<_T>& _other)
{
	SLIB_TRY_CONVERT_TYPE(_T*, T*)
	Ref<_T> other(_other);
	_set(other._ptr);
}

template <class T>
Atomic< WeakRef<T> >::~Atomic()
{
	SLIB_TRY_CONVERT_TYPE(T*, Referable*)
}

template <class T>
SLIB_INLINE const AtomicWeakRef<T>& Atomic< WeakRef<T> >::null()
{
	return *(reinterpret_cast<AtomicWeakRef<T> const*>(&_Ref_Null));
}

template <class T>
sl_bool Atomic< WeakRef<T> >::isNull() const
{
	return _weak.isNull();
}

template <class T>
sl_bool Atomic< WeakRef<T> >::isNotNull() const
{
	return _weak.isNotNull();
}

template <class T>
void Atomic< WeakRef<T> >::setNull()
{
	_weak.setNull();
}

template <class T>
template <class _T>
SLIB_INLINE const AtomicWeakRef<T>& Atomic< WeakRef<T> >::from(const AtomicWeakRef<_T>& other)
{
	return *(reinterpret_cast<AtomicWeakRef<T> const*>(&other));
}

template <class T>
template <class _T>
SLIB_INLINE AtomicWeakRef<T>& Atomic< WeakRef<T> >::from(AtomicWeakRef<_T>& other)
{
	return *(reinterpret_cast<AtomicWeakRef<T>*>(&other));
}

template <class T>
template <class _T>
SLIB_INLINE AtomicWeakRef<T>&& Atomic< WeakRef<T> >::from(AtomicWeakRef<_T>&& other)
{
	return static_cast<AtomicWeakRef<T>&&>(*(reinterpret_cast<AtomicWeakRef<T>*>(&other)));
}

template <class T>
Ref<T> Atomic< WeakRef<T> >::lock() const
{
	Ref<CWeakRef> weak(_weak);
	if (weak.isNotNull()) {
		return Ref<T>::from(weak->lock());
	}
	return sl_null;
}

template <class T>
WeakRef<T> Atomic< WeakRef<T> >::operator*() const
{
	return *this;
}

template <class T>
AtomicWeakRef<T>& Atomic< WeakRef<T> >::operator=(sl_null_t)
{
	_weak.setNull();
	return *this;
}

template <class T>
AtomicWeakRef<T>& Atomic< WeakRef<T> >::operator=(T* _other)
{
	_set(_other);
	return *this;
}

template <class T>
AtomicWeakRef<T>& Atomic< WeakRef<T> >::operator=(AtomicWeakRef<T>&& other)
{
	_weak._move_assign(&other);
	return *this;
}

template <class T>
AtomicWeakRef<T>& Atomic< WeakRef<T> >::operator=(const AtomicWeakRef<T>& other)
{
	_weak = other._weak;
	return *this;
}

template <class T>
template <class _T>
AtomicWeakRef<T>& Atomic< WeakRef<T> >::operator=(AtomicWeakRef<_T>&& other)
{
	SLIB_TRY_CONVERT_TYPE(_T*, T*)
	_weak._move_assign(&other);
	return *this;
}

template <class T>
template <class _T>
AtomicWeakRef<T>& Atomic< WeakRef<T> >::operator=(const AtomicWeakRef<_T>& other)
{
	SLIB_TRY_CONVERT_TYPE(_T*, T*)
	_weak = other._weak;
	return *this;
}

template <class T>
AtomicWeakRef<T>& Atomic< WeakRef<T> >::operator=(WeakRef<T>&& other)
{
	_weak._move_assign(&other);
	return *this;
}

template <class T>
AtomicWeakRef<T>& Atomic< WeakRef<T> >::operator=(const WeakRef<T>& other)
{
	_weak = other._weak;
	return *this;
}

template <class T>
template <class _T>
AtomicWeakRef<T>& Atomic< WeakRef<T> >::operator=(WeakRef<_T>&& other)
{
	SLIB_TRY_CONVERT_TYPE(_T*, T*)
	_weak._move_assign(&other);
	return *this;
}

template <class T>
template <class _T>
AtomicWeakRef<T>& Atomic< WeakRef<T> >::operator=(const WeakRef<_T>& other)
{
	SLIB_TRY_CONVERT_TYPE(_T*, T*)
	_weak = other._weak;
	return *this;
}

template <class T>
AtomicWeakRef<T>& Atomic< WeakRef<T> >::operator=(const Ref<T>& other)
{
	_set(other._ptr);
	return *this;
}

template <class T>
template <class _T>
AtomicWeakRef<T>& Atomic< WeakRef<T> >::operator=(const Ref<_T>& other)
{
	SLIB_TRY_CONVERT_TYPE(_T*, T*)
	_set(other._ptr);
	return *this;
}

template <class T>
AtomicWeakRef<T>& Atomic< WeakRef<T> >::operator=(const AtomicRef<T>& _other)
{
	Ref<T> other(_other);
	_set(other._ptr);
	return *this;
}

template <class T>
template <class _T>
AtomicWeakRef<T>& Atomic< WeakRef<T> >::operator=(const AtomicRef<_T>& _other)
{
	SLIB_TRY_CONVERT_TYPE(_T*, T*)
	Ref<_T> other(_other);
	_set(other._ptr);
	return *this;
}

template <class T>
sl_bool Atomic< WeakRef<T> >::operator==(const AtomicWeakRef<T>& other) const
{
	return _weak == other._weak;
}

template <class T>
template <class _T>
sl_bool Atomic< WeakRef<T> >::operator==(const AtomicWeakRef<_T>& other) const
{
	return _weak == other._weak;
}

template <class T>
sl_bool Atomic< WeakRef<T> >::operator==(const WeakRef<T>& other) const
{
	return _weak == other._weak;
}

template <class T>
template <class _T>
sl_bool Atomic< WeakRef<T> >::operator==(const WeakRef<_T>& other) const
{
	return _weak == other._weak;
}

template <class T>
sl_bool Atomic< WeakRef<T> >::operator!=(const AtomicWeakRef<T>& other) const
{
	return _weak != other._weak;
}

template <class T>
template <class _T>
sl_bool Atomic< WeakRef<T> >::operator!=(const AtomicWeakRef<_T>& other) const
{
	return _weak != other._weak;
}

template <class T>
sl_bool Atomic< WeakRef<T> >::operator!=(const WeakRef<T>& other) const
{
	return _weak != other._weak;
}

template <class T>
template <class _T>
sl_bool Atomic< WeakRef<T> >::operator!=(const WeakRef<_T>& other) const
{
	return _weak != other._weak;
}

template <class T>
SLIB_INLINE void Atomic< WeakRef<T> >::_set(T* object)
{
	if (object) {
		_weak = object->_getWeakObject();
	} else {
		_weak.setNull();
	}
}

template <class T>
SLIB_INLINE sl_bool operator>(const Ref<T>& a, const Ref<T>& b)
{
	return a._ptr > b._ptr;
}

template <class T>
SLIB_INLINE sl_bool operator<(const Ref<T>& a, const Ref<T>& b)
{
	return a._ptr < b._ptr;
}

SLIB_NAMESPACE_END

#endif
