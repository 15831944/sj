#interface()
class #interface (
	bob : 0
) { this }

a : empty'i32
b : empty'i64
c : empty'u32
d : empty'u64
e : empty'f32
f : empty'f64
g : empty'char
h : empty'ptr
i : empty'class
j : isEmpty(a)
k : isEmpty(i)
l : empty'#interface
m : isEmpty(l)

n : value(class())
o : getValue(n)
p : n?.bob