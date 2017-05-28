**class template**
# forked_linked_list

## Overview

### File Organization

```
dlib_cc/
	|
	Classes/
		|
		forked_linked_list/
			|
			+ forked_linked_list.h
			+ impl.h
			+ iterators.h
			+ node_cursor.h
			+ node.h
			- tutorial.cpp
```

### Namespace

```
namespace dlib
{
	template <typename T> class forked_linked_list;
	namespace forked_linked_list_bits
	{
		template <typename T> struct vh_iterator;
		template <typename T> struct const_vh_iterator;
		template <typename T> struct v_iterator;
		template <typename T> struct const_v_iterator;
		template <typename T> struct h_iterator;
		template <typename T> struct const_h_iterator;
		template <typename T> class node_cursor;
		template <typename T> struct node;
	}
}
```

### 