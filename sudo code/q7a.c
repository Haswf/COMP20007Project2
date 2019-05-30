function BUILDHEAP(A[0...(2^k)-1])
	m ← 2^(k-2)
	wihle m > 0 do
		for p ← m to 2m - 1 do
			SiftDown(heap, p)
		m ← m/2

function SIFTDOWN(heap[0...(n-1)], p)
	while 
	2p <= (n-1) and (heap[p]<heap[LEFTCHILD(p)] or heap[p]<heap[RIGHTCHILD(p)]) do
	t ← MAXCHILD(heap, LEFTCHILD(p), RIGHTCHILD(p))
	swap(heap, p, t)
	p ← t

function MAXCHILD(heap, left, right)
	if heap[left] > heap[right]
		return left
	else 
		return right

function LEFTCHILD(p)
    return 2*p;

function RIGHTCHILD(p)
    return 2*p+1;

function SWAP(heap, left, right)
    tmp ← heap[right]
    heap[right] ← heap[left]
    heap[left] ← tmp