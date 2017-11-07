array!t (
	size = 0
	data = 0 as ptr
	_isGlobal = false

	getAt(index : 'i32)'t c{
		#forceParent()

		if (index >= _parent->size || index < 0) {
			exit(-1);
		}

		#type(t)* p = (#type(t)*)_parent->data;
		#type(t) val = p[index];
		if (!#isValue(t)) {
			if (val == 0) {
				exit(-1);
			}
		}
		return val;		
	}c

	setAt(index : 'i32, item : 't)'void c{
		#forceParent()
		#forceHeap(item)

		if (index >= _parent->size || index < 0) {
			exit(-1);
		}

		#type(t)* p = (#type(t)*)_parent->data;
		#release(t, p[index]);
		#retain(t, item);
		p[index] = item;
	}c

	find(item : 't)'i32 c{	
		#forceParent()

		#type(t)* p = (#type(t)*)_parent->data;
		for (int index = 0; index < _parent->size; i++) {
			if (p[index] == item) {
				return index;
			}
		}
		return -1;
	}c

	grow(newSize :' i32)'array!t c{
		#forceParent()

		if (_parent->size != newSize) {
			if (newSize < _parent->size) {
				exit(-1);
			}
			
			if (_parent->_isGlobal) {
				_parent->_isGlobal = false;
				#type(t)* p = _parent->data;
				_parent->data = (uintptr_t)malloc(newSize * sizeof(#type(t)));
				memcpy(_parent->data, p, _parent->size * sizeof(#type(t)));
			} else {
				_parent->data = (uintptr_t)realloc((void*)_parent->data, newSize * sizeof(#type(t)));
			}
			_parent->size = newSize;
		}

		return _parent;
	}c 
)'array!t c{
	#forceThis()

	if (_this->size < 0) {
		exit(-1);
	}

	if (_this->data) {
		_this->_isGlobal = true;
	} else {
		_this->data = (uintptr_t)malloc(_this->size * sizeof(#type(t)));
	}

	#retain(array!t, _this);
	return _this;
}c destroy c{
	free((#type(t)*)_this->data);	
}c
