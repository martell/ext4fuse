#ifndef INODE_H
#define INODE_H

#include <sys/types.h>

#include "types/ext4_inode.h"
#include "types/ext4_dentry.h"
#include "inode_in-memory.h"

struct inode_dir_ctx {
    uint32_t lblock;        /* Currently buffered lblock */
    uint8_t buf[];
};

static inline uint64_t inode_get_size(struct inode *inode)
{
    return ((uint64_t)inode->raw_inode->i_size_high << 32) | inode->raw_inode->i_size_lo;
}

uint64_t inode_get_data_pblock(struct inode *inode, uint32_t lblock, uint32_t *extent_len, int create);
int inode_remove_data_pblock(struct inode *inode, ext4_lblk_t from);

struct inode_dir_ctx *inode_dir_ctx_get(void);
void inode_dir_ctx_put(struct inode_dir_ctx *);
void inode_dir_ctx_reset(struct inode_dir_ctx *ctx, struct ext4_inode *inode);
struct ext4_dir_entry_2 *inode_dentry_get(struct ext4_inode *raw_inode, off_t offset, struct inode_dir_ctx *ctx);

int inode_get_by_number(uint32_t n, struct ext4_inode *inode);
int inode_set_by_number(uint32_t n, struct ext4_inode *inode);
int inode_get_by_path(const char *path, struct ext4_inode *inode);
uint32_t inode_get_idx_by_path(const char *path);

int inode_init(void);

#endif
