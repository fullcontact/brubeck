#ifndef __BRUBECK_SLAB_H__
#define __BRUBECK_SLAB_H__

/* Each slab has 40 bytes; 102 slabs per node = 4080 bytes (almost one page) */
#define SLAB_SIZE 40
#define SLABS_PER_NODE 102

/*  extra 16 bytes to avoid spanning pages */
#define NODE_SIZE (SLAB_SIZE * (SLABS_PER_NODE - 1) + 16)

struct brubeck_slab_node {
	struct brubeck_slab_node *next;
	size_t alloc;
	char heap[];
};

struct brubeck_slab {
	struct brubeck_slab_node *current;
	size_t total_alloc;
	pthread_mutex_t lock;
};

void brubeck_slab_init(struct brubeck_slab *slab);
void *brubeck_slab_alloc(struct brubeck_slab *slab, size_t need);

#endif
