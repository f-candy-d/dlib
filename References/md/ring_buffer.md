**class template**
# dlib::ring_buffer

<div class="mxgraph" style="max-width:100%;" data-mxgraph="{&quot;highlight&quot;:&quot;#0000ff&quot;,&quot;lightbox&quot;:false,&quot;nav&quot;:true,&quot;edit&quot;:&quot;_blank&quot;,&quot;xml&quot;:&quot;&lt;mxfile userAgent=\&quot;Mozilla/5.0 (Macintosh; Intel Mac OS X 10_11_6) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36\&quot; version=\&quot;6.6.5\&quot; editor=\&quot;www.draw.io\&quot; type=\&quot;github\&quot;&gt;&lt;diagram name=\&quot;Page-1\&quot;&gt;1ZfLjpswFIafhu0I7BDCsslcuuhIlVh0WRljwBrDQcaZkD59DZgEAlEiBaoOiwT/xze+/9gGC++y6k2SIn2HiAkL2VFl4WcLoc3a07+1cGwFz3NaIZE8aqWeEPA/zIi2Ufc8YuWgogIQihdDkUKeM6oGGpESDsNqMYjhqAVJ2EgIKBFj9RePVGoey7XP+nfGk7Qb2bFNJCT0I5Gwz814FsJxc7XhjHR9mfplSiI49CT8YuGdBFDtXVbtmKjRdtjadq9Xoqd5S5arexqgtsEnEXvWzbiZlzp2LHQDjV0XtoeUKxYUhNaRgzZea6nKhC45+paURetFzCum+9+WSsIH24EA2XSF7ebSkfE0zcw/mVSs6klm2m8MMqbkUVcxUdQhNynmrE35cDbspKV9szqRmCRJTn2fQekbw+oK6PVtcPWzcJ1TP0jIxE8oueKQ61AISkGmKXQVvgme1AEFF0RbgF0GNkpKirr7rErqhfcUkpLTp5SI+DflktZDb2MuRA96HFN9TdmB19jH0TJ2oNWddmzmcGPz/7ohQREz1Modu0MjFm7Cpd1xPDR0B/n3ueP5j7vj3zZH8JxNEo641HtKi6+Efa33LbmEO0cie+7tfWVyW3EeR+Uth2oRNM6daGZY43cs8RmyyJ/rdMJDVKft8QaqOXZDvOSZPjpcmpebpc/6Nb7YvvCIZge8T7PTHqGJ3BHOWIJ+lEumPWpTUClknF49SWLd4yvJuKifcNdURXZA8lL/vQemQmAGm2k5O/7Fke2Mc3Q1kaNohhydOBTqV+evDxX5myFU/99BxePjI9pn2fHrU8X44v3FHVN156Gqi+fPrybW+8TFL38B&lt;/diagram&gt;&lt;/mxfile&gt;&quot;}"></div>
<script type="text/javascript" src="https://www.draw.io/embed2.js?s=basic&"></script>

## Overview

リングバッファクラス。リングバッファ？なときは[コチラ][link-ring-buffer]。back -> front の向きは時計回り。  
`push_front()/back()`、`pop_front()/back()`がO(1)で可能。ランダムアクセスもOk。要素数（`size()`)が最大容量(`capacity()`)を超えると、front/backの要素から順に書き換わる。今のところinsert系のメソッドは無し。  
indexの正規化をビット演算で行うために最大容量は必ず2の冪乗になるが、内１つ分はダミー領域（イテレータの都合で...）となるので、実質使用できるのは２^n - 1の容量となる。

[link-ring-buffer]:https://ja.wikipedia.org/wiki/%E3%83%AA%E3%83%B3%E3%82%B0%E3%83%90%E3%83%83%E3%83%95%E3%82%A1

### File Organization

		dlib_cc/
			|
			Classes/
				|
				ring_buffer/
					|
					+ ring_buffer.h
					+ impl.h
					+ iterators.h
					- tutorial.cpp

### Namespace

		namespace dlib
		{
			template <typename T> class forked_linked_list;
		
			namespace ring_buffer_bits
			{
				template <typename T> struct iterator;
				template <typename T> struct const_iterator;
			}
		}

イテレータは別の名前空間に入っている（ファイルを分けるために）が、`ring_buffer`クラス内でエイリアスを定義してあるので、`ring_buffer<T>::iterator`で使用できる（というよりコッチを使って欲しい）。`begin()`はfrontの要素を指し、`end()`はbackの次の要素を指す。

### Public Methods

* `ring_buffer()`  
* `ring_buffer(size_t size, T def_value = T())`  
* `ring_buffer(size_t size, size_t cap_request, T def_value)`    
* `ring_buffer(const ring_buffer& other)`
  
	コンストラクタs。第2、第3コンストラクタはfillコンストラクタで、**size**だけ**def_value**で埋める。**cap_request**には最大容量を指定するが、希望通りになるかは分からない。**cap_request + 1 <= 2^n** を満たす最小の2^nが最大容量になる(+1はダミー領域の分)。  
	また、**cap_request < size** の場合はassert:エラー。
    
-------------------------------------------------------------------------------------------------------

* `void change_capacity(size_t cap_request)`  
* `void expand_capacity(size_t cap_request)`  
* `void shrink_capacity(size_t cap_request)`  
  
	最大容量のサイズを変更する。要素の並びは変わらない。**change**は内部で**expand**か**shrink**を呼び出している。**shrink**は、新しい最大容量が要素数よりも小さい場合、入りきらない要素をbackの方から削っていく。  
	また、要素の入っていない部分はみ初期化なので、そこにアクセスした時の動作は未定義(何かしらの値が帰ってくるハズ)。  
	**cap_request**には新しい最大容量の希望の値を渡す。実際には、**cap_request + 1 <= 2^n** を満たす最小の2^nが最大容量になる。  
	  
	**実際に使用できる容量は2^n - 1であることに注意！！**

-------------------------------------------------------------------------------------------------------

* `void push_back(T value)`  
* `void push_front(T value)`  

	front/backに要素を追加する。要素数が溢れた時は、例えば**push_back**の場合、frontの要素が書き換わり、frontの直前だった要素がfrontになる。
	
-------------------------------------------------------------------------------------------------------

* `T pop_back()`  
* `T pop_front()` 

	front/backの要素を削除する。メモリは解放されない。**size()** が0でもエラーにはならないよ。  
	あと、削除した要素のデストラクタが呼ばれる。

-------------------------------------------------------------------------------------------------------
 
* `T& operator[](size_t index)`  
* `const T& operator[](size_t index) const`  

	要素にアクセスする基本の手段。**operator[0]**は常に**front()**と同じ要素を指す。つまり、**index**には、frontを0として考えた時のインデックスを渡す。また、リングバッファなので、**out-of-range** みたいなことは起こらず、たとえ最大容量を超えたインデックスを渡したとしても正規化されるので大丈夫(一周しても戻ってくる)。front <-> back 間の要素以外にもアクセスできるが、未初期化部分なのでどうなるかは知らない。  
	添字演算子で値を追加/削除しても**size()**や**front()**、**back()**等に反映されないので、**危険**です。やめてください。。。

-------------------------------------------------------------------------------------------------------

* `T front() const`  
* `T back() const`  

	front/backの値をそれぞれ返却する。**size()**が0の場合、**T()**を返す。

-------------------------------------------------------------------------------------------------------

* `void clear()`  

	要素を全て削除する。各要素のデストラクタは呼ばれるが、メモリの開放はしない。

-------------------------------------------------------------------------------------------------------

* `size_t capacity() const`  

	**正味**の最大容量を返す。つまり、**2^ - 1** のコト。

-------------------------------------------------------------------------------------------------------

* `size_t size() const`  

	要素数を返す。当たり前だけど、常に **size() <= capacity()** 。

-------------------------------------------------------------------------------------------------------

* `iterator begin()`  
* `const_iterator begin() const`  
* `const_iterator cbegin() const`  
* `iterator end()`  
* `const_iterator end() const`  
* `const_iterator cend() const`  

	イテレータの取得メソッドs。**begin**はfrontを指し、**end**はbackの次(ダミー領域)を指す。  
	リングバッファなので、**++end()**を繰り返せばいずれ**begin**に戻ることに注意。

-------------------------------------------------------------------------------------------------------

### How To Use ?

**基本**

		dlib::ring_buffer<int> buffer();                  // <- default, size() and capacity() is 0
		dlib::ring_buffer<int> buffer2(10, 6);            // <- size() is 10, capacity() is 15
		dlib::ring_buffer<int> buffer3(10, 16, 6);        // <- size() is 10, capacity() is 31
		dlib::ring_buffer<int> buffer4(buffer);           // <- copy constructor  
	
		buffer2.push_front(10);                           // <- append '10' to the front of the buffer
		buffer2.push_back(10);                            // <- append '10' to the back of the buffer

		int x = buffer2.front();                          // <- get the first element of the buffer
		int y = buffer2[0];                               // <- this is same as 'buffer.front()'

		buffer2.pop_front();                              // <- remove the first element of the buffer
		buffer2.pop_back();                               // <- remove the last element of the buffer

		buffer2.expand_capacity(buffer.capacity() * 2);   // <- size() is 10, capacity() is 31
		buffer2.shrink_capacity(5);                       // <- size() is 7, capacity() is 7

		buffer2.clear();                                  // <- size() is 0, capacity() is 7

	
**Iterators**  

		// navigate through a ring-buffer from front to back using iterators
		for(auto itr = buffer2.begin(); itr != buffer2.end(); ++itr)
		{
			std::cout << "data -> " << *itr << '\n';
		}
		
		// the following codes is the same as above...
		for(size_t i = 0; i < buffer2.size(); ++i)
		{
			std::cout << "data -> " << buffer2[i] << '\n';
		}