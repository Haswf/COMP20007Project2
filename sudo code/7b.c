function BUILDRIGHTHANDEDHEAP(A[0...(2^k)-1])
    /* Call BUILDHEAP to convert array to heap */
    BUILDHEAP(A);
    m ← 1;
    // Check right handed property of top k-1 layers
    while (m <= k) do
        for (p ← m to p >= (m + 1)/2 && RIGHTCHILD(p) < (2^k)-1; p--) do
            /* if left child is greater than right child */
            if (A[LEFTCHILD(p)] > A[RIGHTCHILD(p)]) then
                /* swap left child and right child */
                swap(A, LEFTCHILD(p), RIGHTCHILD(p])
                /* restore heap property on left subtree */
                siftdown(A, LEFTCHILD(p));
        m ← 2m + 1;

function LEFTCHILD(p)
    return 2p;

function RIGHTCHILD(p)
    return 2p+1;

function SWAP(A, left, right)
    tmp ← A[right]
    A[right] ← A[left]
    A[left] ← tmp