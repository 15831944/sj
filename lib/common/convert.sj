convert: ^(
	i32toString(val : 'i32) {
		count = 0
		data = 0 as ptr
		c{
			char buf[32] = { 0 };
			int i = 30;	
			do {
				buf[i] = "0123456789"[val % 10];	
				i--;
				val /= 10;
			} while (val && i);
			count = 30 - i;
			data = (uintptr_t)malloc(sizeof(char) * (count + 1));
			memcpy((void*)data, &buf[i+1], count + 1);
		}c
		string(count = count, data = array!char(size = count + 1, data = data))
	}
) { this }