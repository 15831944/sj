include "../../lib/common/array.sj"

a : array!i32(1)
a.setAt(0, 1)
c : a.getAt(0)
c