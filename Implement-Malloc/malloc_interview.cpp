/*
 * IMPLEMENT MALLOC — Interview Answer
 *
 * Say this first:
 *   "I'll use sbrk() to grow the heap. Every allocation gets a hidden
 *    header storing size, a free flag, and a next pointer — forming a
 *    linked list of all heap blocks. malloc does a first-fit scan,
 *    splits oversized blocks, and free coalesces adjacent free blocks."
 *
 * Draw on whiteboard:
 *   [hdr|payload] → [hdr|payload] → NULL
 *    size/free/next  size/free/next
 */

#include <unistd.h>   // sbrk
#include <cstring>    // memcpy
#include <cassert>

// ── 1. Block header ───────────────────────────────────────────────────────────
//
// Sits just BEFORE the pointer we return to the caller.
// Pointer arithmetic: payload = header + HEADER_SIZE
//                     header  = payload - HEADER_SIZE

struct Block
{
	size_t  size;     // payload bytes only. unsigned int
	bool    free;
	Block*  next;
};

static const size_t HEADER_SIZE = sizeof(Block);
static Block* head = nullptr;   // first block on the heap

// Given a pointer to the first byte of payload, move to the first byte of the header of that block
static Block* to_block(void* p)
{
	return (Block*)((char*)p - HEADER_SIZE);
}

// Given pointer to a block, jump to the byte address after the header to the payload start
static void* to_payload(Block* b)
{
	return (char*)b + HEADER_SIZE;
}

// ── 2. my_malloc ──────────────────────────────────────────────────────────────
//
// First-fit: walk the list, take the first free block big enough.
// Split:     if the block is much larger, carve off a free remainder.
// Extend:    if nothing fits, call sbrk() to grow the heap.

// Demand based: Initially there is no memory in heap, and then it is allocated block by block, on demand, using sbrk
void* my_malloc(size_t size)
{
	if (!size)
		return nullptr;

	Block* prev = nullptr;
	Block* cur  = head;

	// First-fit search
	// 2 pointer linked list traversal
	while (cur)
	{
		if (cur->free && cur->size >= size)
		{
			// Split: If too much space in the current block, split it
			// Split if leftover is worth keeping (header + 16 bytes minimum). Total size is header + payload. But also could have extra space of 16 bytes
			if (cur->size >= size + HEADER_SIZE + 16)
			{
				// Create a split block after leaving exact space for header and payload, in cur.  
				// Reconnect list appropriately
				Block* split = (Block*)((char*)cur + HEADER_SIZE + size);
				split->size  = cur->size - size - HEADER_SIZE;
				split->free  = true;
				split->next  = cur->next;
				
				// cur block that is the exact size needed for the payload
				cur->size    = size;	// because only payload
				cur->next    = split;
			}
			
			cur->free = false;
			return to_payload(cur);		// Return the address to the payload in the current block
		}
		
		prev = cur;
		cur  = cur->next;
	}

	// No fit found — ask OS for more heap space
	
	// Adjust break: sbrk grows the heap by the input bytes size, and then returns the first byte to that new region ()
	Block* blk = (Block*)sbrk(HEADER_SIZE + size);	
	
	// Returns (void*) -1  , if not available
	if (blk == (Block*)-1)
		return nullptr;   // out of memory

	// Set header
	blk->size = size;
	blk->free = false;
	blk->next = nullptr;

	// If no head to the list, this block is the head. Set head
	if (head == nullptr)
		head = blk;
	else
		prev->next = blk;

	return to_payload(blk);
}

// ── 3. my_free ────────────────────────────────────────────────────────────────
//
// Mark the block free, then coalesce consecutive free blocks
// so fragmentation doesn't accumulate over time.

// p is payload pointer
void my_free(void* p)
{
	if (!p)
		return;                            // free(NULL) is always a no-op

		
		
	Block* blk = to_block(p);	// Given a pointer to payload, get the pointer to the start of header of that block. Get the whole block pointer
	assert(!blk->free && "double free");
	blk->free = true;

	// Coalesce: merge any two adjacent free blocks into one. Do for the entire list every time any block is freed
	Block* cur = head;
	while (cur && cur->next)
	{
		if (cur->free && cur->next->free)
		{
			cur->size += HEADER_SIZE + cur->next->size;
			cur->next  = cur->next->next;
		}
		else
		{
			cur = cur->next;
		}
	}
}

// ── 4. my_realloc (follow-up) ─────────────────────────────────────────────────

void* my_realloc(void* p, size_t new_size)
{
	if (!p)
		return my_malloc(new_size);
	if (!new_size)
	{
		my_free(p);
		return nullptr;
	}

	Block* blk = to_block(p);
	if (blk->size >= new_size)
		return p;      // already fits

	void* np = my_malloc(new_size);
	if (!np)
		return nullptr;
	memcpy(np, p, blk->size);
	my_free(p);
	return np;
}

// ── Follow-up questions to expect ────────────────────────────────────────────
//
// Q: How to make it faster?
//    → Segregated free-lists: one list per size class → near-O(1) amortised.
//      (This is what jemalloc / tcmalloc do.)
//
// Q: Thread safety?
//    → Wrap list walk in a mutex, OR use per-thread arenas (no contention).
//
// Q: Internal vs external fragmentation?
//    → Internal  = wasted bytes INSIDE an allocated block (padding/splitting).
//      External  = free blocks too small to serve a request despite enough
//                  total free memory.
//
// Q: mmap vs sbrk?
//    → mmap is better for large allocations (can be returned to the OS
//      individually). sbrk is simpler but only shrinks from the top.
//
// Q: Minimum block size?
//    → At least sizeof(Block) so a freed payload can hold its own metadata.
