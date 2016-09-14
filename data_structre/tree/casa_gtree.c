/* 
 * MT safe
 */
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include "glib.h"
#include "casa_gtree.h"

static int cgtree_init = 0;
static pthread_rwlockattr_t attr;
#define _LIMIT_P_ERR(limit_bitmap, fmt, ...) \
do {\
	static u_int32_t my_print_cnt_ = 0;\
	if ((my_print_cnt_ & (limit_bitmap)) == 0)\
	{\
		fprintf(stderr, (fmt),  ##__VA_ARGS__);\
	}\
	my_print_cnt_++;\
} while(0)

#define _CGTREE_TRC() _LIMIT_P_ERR(0xFFF, "%s(): pid %d, %m\n", __FUNCTION__, getpid())

#define C_GTREE_WRLOCK(ctree) \
do { \
	if(pthread_rwlock_wrlock(&((ctree)->rw_lock)) != 0)\
	{\
		_CGTREE_TRC();\
		return ;\
	} \
} while(0)

#define C_GTREE_RDLOCK(ctree) \
	do { \
		if(pthread_rwlock_rdlock(&((ctree)->rw_lock)) != 0)\
		{\
			_CGTREE_TRC();\
			return ;\
		} \
	} while(0)
		
#define C_GTREE_RDLOCK_RETURN(ctree, ret) \
				do { \
					if(pthread_rwlock_rdlock(&((ctree)->rw_lock)) != 0)\
					{\
						_CGTREE_TRC();\
						return (ret);\
					} \
				} while(0)

#define C_GTREE_UNLOCK(ctree)	pthread_rwlock_unlock(&((ctree)->rw_lock))

typedef struct _GRealTree  GRealTree;
typedef struct _GTreeNode  GTreeNode;

struct _GRealTree
{
  GTreeNode *root;
  GCompareFunc key_compare;
};

struct _GTreeNode
{
  gint balance;      /* height (left) - height (right) */
  GTreeNode *left;   /* left subtree */
  GTreeNode *right;  /* right subtree */
  gpointer key;      /* key for this node */
  gpointer value;    /* value stored at this node */
};

static gpointer
g_tree_node_lookup_nr (GTreeNode    *node,
                    GCompareFunc  compare,
                    gpointer      key);

static gpointer
g_tree_node_lookup_next (GTreeNode    *node,
		    GCompareFunc  compare,
		    gpointer      key);


static gpointer
g_tree_node_lookup_nlt (GTreeNode    *node,
		    GCompareFunc  compare,
		    gpointer      key  );

//#define _GTREE_LOCK_DEBUG_

#ifdef _GTREE_LOCK_DEBUG_

#define _GNU_SOURCE 
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

static pid_t
gettid(void)
{
	return syscall(__NR_gettid);
}

#endif

#if 0
static inline void casa_g_tree_lock(CGtree *ctree) 
{ 
#ifdef _GTREE_LOCK_DEBUG_ 
	if(pthread_mutex_trylock(&ctree->lock))
	{ 
		printf("GTREE DEBUG: process[ pid = %u tid = %u ] mutex lock content in casa gtree %p\n",
		        getpid(), gettid(), ctree);
		pthread_mutex_lock(&ctree->lock); 
	} 
#else
	pthread_mutex_lock(&ctree->lock);
#endif
}

static inline void casa_g_tree_unlock(CGtree *ctree)
{
	pthread_mutex_unlock(&ctree->lock);
}

#endif

static int _pthread_rwlock_writer_prefer_init(pthread_rwlock_t *rwlock)
{
	if (!cgtree_init)
	{
		cgtree_init = 1;
		pthread_rwlockattr_init (&attr);
		pthread_rwlockattr_setkind_np (&attr,
			PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP);
	}

	return pthread_rwlock_init(rwlock, &attr);
}

/*
 * Casa gtree thread-safe wrapper functions
 *
 * These functions just are thread-safe wrappers,
 * their parameters and semantic are same as original
 * gtree of glib except for the CGtree objects. 
 */

int casa_g_tree_new(CGtree *ctree, GCompareFunc key_compare_func)
{
	int rc;

	ctree->tree = g_tree_new(key_compare_func);
	///rc = pthread_mutex_init(&ctree->lock, NULL);
	rc = _pthread_rwlock_writer_prefer_init(&ctree->rw_lock);// bug 33188

	return ctree->tree == NULL || rc != 0;
}

void casa_g_tree_destroy(CGtree *ctree)
{
	///pthread_mutex_destroy(&ctree->lock);
	pthread_rwlock_destroy(&ctree->rw_lock); // bug 31888
	g_tree_destroy(ctree->tree);
	ctree->tree = NULL;
}

void casa_g_tree_insert(CGtree *ctree, gpointer key, gpointer value)
{
	///casa_g_tree_lock(ctree);
	C_GTREE_WRLOCK(ctree);
	g_tree_insert(ctree->tree, key, value);
	///casa_g_tree_unlock(ctree);
	C_GTREE_UNLOCK(ctree);
}

void casa_g_tree_remove(CGtree *ctree, gconstpointer key)
{
	///casa_g_tree_lock(ctree);
	C_GTREE_WRLOCK(ctree);
	g_tree_remove(ctree->tree, key);
	C_GTREE_UNLOCK(ctree);
	///casa_g_tree_unlock(ctree);
}

void casa_g_tree_traverse(CGtree *ctree, GTraverseFunc traverse_func,
       GTraverseType traverse_type, gpointer user_data)
{
	g_return_if_fail(ctree != NULL);
	
	///casa_g_tree_lock(ctree);
	C_GTREE_WRLOCK(ctree); // it is used to release entries or reset counters in most cases
	g_tree_traverse(ctree->tree, traverse_func, traverse_type, user_data);
	C_GTREE_UNLOCK(ctree);
	///casa_g_tree_unlock(ctree);
} 

gpointer casa_g_tree_lookup(CGtree *ctree, gconstpointer key)
{
	gpointer val;

	g_return_val_if_fail(ctree != NULL, NULL);

	///casa_g_tree_lock(ctree);
	C_GTREE_RDLOCK_RETURN(ctree, NULL);
	val = g_tree_lookup(ctree->tree, key);
	///casa_g_tree_unlock(ctree);
	C_GTREE_UNLOCK(ctree);

	return val;
}

int  casa_g_tree_nnodes(CGtree * ctree) 
{
	gint rc;
	
	g_return_val_if_fail(ctree != NULL, 0);
	
	///casa_g_tree_lock(ctree);
	C_GTREE_RDLOCK_RETURN(ctree, -1);
	rc = g_tree_nnodes(ctree->tree);
	///casa_g_tree_unlock(ctree);
	C_GTREE_UNLOCK(ctree);
	return rc;
}

static gboolean
g_tree_node_has_more (GTreeNode *node, int *p_cnt)
{
  (*p_cnt)--;
  if ((*p_cnt) < 0)
  {
    return TRUE;
  }
  if (node->left)
  {
    if (g_tree_node_has_more (node->left, p_cnt))
    {
      return TRUE;
    }
  }
  if (node->right)
  {
    if (g_tree_node_has_more (node->right, p_cnt))
    {
      return TRUE;
    }
  }
  
  return FALSE;
}

/**
 * g_tree_has_more_nodes:
 * @tree: a #GTree.
 * 
 * check if the #GTree contains at least min_cnt nodes
 * 
 * Return value: TRUE if nnodes > min_cnt, else FALSE.
 **/
static gboolean
g_tree_has_more_nodes (CGtree * ctree, int min_cnt)
{
  g_return_val_if_fail (ctree != NULL, FALSE);
  
  int cnt = min_cnt;

  GRealTree *rtree = (GRealTree *)ctree->tree;

  if (rtree->root)
    return g_tree_node_has_more(rtree->root, &cnt);
  else
    return FALSE;
}

/** for bug 37258
 * casa_g_tree_has_more_nodes:
 * @tree: a #CGtree.
 * 
 * check if the #CGtree contains at least min_cnt nodes
 * 
 * Return value: TRUE if nnodes > min_cnt, else FALSE.
 **/
gboolean
casa_g_tree_has_more_nodes (CGtree * ctree, int min_cnt)
{
	gboolean rc;
	
	g_return_val_if_fail(ctree != NULL, FALSE);
	
	///casa_g_tree_lock(ctree);
	C_GTREE_RDLOCK_RETURN(ctree, FALSE);
	rc = g_tree_has_more_nodes(ctree, min_cnt);
	///casa_g_tree_unlock(ctree);
	C_GTREE_UNLOCK(ctree);
	return rc;
}


/*--------------------------------------*/

/**
  * none-recursive version of g_tree lookup
  **/
gpointer
casa_g_tree_lookup_nr (CGtree    *ctree,
               gpointer  key)
{ 
  gpointer val;
  GRealTree *rtree;

  g_return_val_if_fail (ctree != NULL && ctree->tree != NULL, NULL);

  rtree = (GRealTree *)ctree->tree;
  ///casa_g_tree_lock(ctree);
  C_GTREE_RDLOCK_RETURN(ctree, NULL);
  val = g_tree_node_lookup_nr (rtree->root, rtree->key_compare, key);
  ///casa_g_tree_unlock(ctree);
  C_GTREE_UNLOCK(ctree);

  return val;
}     

/**
 * g_tree_lookup_next:
 * @tree: a #GTree. 
 * @key: the key to look up.
 * 
 * Gets the value corresponding to the next node of the specified key.
 * Since a #GTree is automatically balanced as key/value pairs are added, 
 * key lookup is very fast. * 
 *
 * Return value: the value corresponding to the next node of the specified key,
 * or %NULL if the next node was not found.
 * 
 **/    
gpointer
casa_g_tree_lookup_next (CGtree    *ctree,
	       gpointer  key)
{
  gpointer val;
  GRealTree *rtree;

  g_return_val_if_fail (ctree != NULL && ctree->tree != NULL, NULL);

  rtree = (GRealTree *)ctree->tree;
  ///casa_g_tree_lock(ctree);
  C_GTREE_RDLOCK_RETURN(ctree, NULL);
  val = g_tree_node_lookup_next (rtree->root, rtree->key_compare, key);
  ///casa_g_tree_unlock(ctree);
  C_GTREE_UNLOCK(ctree);

  return val;
}

/**
 * g_tree_lookup_nlt:
 * @tree: a #GTree. 
 * @key: the key to look up.
 * 
 * Gets the value corresponding to the node which key is not less than the 
 * specified key. Since a #GTree is automatically balanced as key/value pairs are added, 
 * key lookup is very fast. * 
 *
 * Return value: the value corresponding to the node which key is not less 
 * than the specified key, or %NULL if the next node was not found.
 * 
 **/    
gpointer
casa_g_tree_lookup_nlt (CGtree    *ctree,
	       gpointer  key)
{
  gpointer val;
  GRealTree *rtree;

  g_return_val_if_fail (ctree != NULL && ctree->tree != NULL, NULL);

  rtree = (GRealTree *)ctree->tree;
  ///casa_g_tree_lock(ctree);
  C_GTREE_RDLOCK_RETURN(ctree, NULL);
  val = g_tree_node_lookup_nlt (rtree->root, rtree->key_compare, key);
  ///casa_g_tree_unlock(ctree);
  C_GTREE_UNLOCK(ctree);

  return val;
}

/*----------------------------------------------*/
static gpointer
g_tree_node_lookup_nr (GTreeNode    *node,
                    GCompareFunc  compare,
                    gpointer      key)
{
  gint cmp;

  if (!node)
    return NULL;

  while(1)
  {

  cmp = (* compare) (key, node->key);
  if (cmp == 0)
    return node->value;

  if (cmp < 0)
    {
      if (node->left)
        node = node->left;
      else
        return NULL;
    }
  else if (cmp > 0)
    {
      if (node->right)
        node = node->right;
      else
	 return NULL;
    }

  }

  return NULL;
}

static gpointer
g_tree_node_lookup_next (GTreeNode    *node,
		    GCompareFunc  compare,
		    gpointer      key  )
{
  gint cmp;  

  GTreeNode *prenode = NULL;    
  
  if (!node)
    return NULL;    

  while(1)
  {

  cmp = (* compare) (key, node->key);  

	if (cmp < 0)
	{
		if (node->left)
		{			
			prenode = node;
			
			node = node->left;
		} 
		else
		{
			return node->value;
		}
	}
	else
	{
		if (node->right)
		{			
			node = node->right;
		}
		else
		{
			if (prenode)
			{
				return prenode->value;
			}
			else
			{
				return NULL;
			}
		}
		
	}
  }

  return NULL;
}

static gpointer
g_tree_node_lookup_nlt (GTreeNode    *node,
		    GCompareFunc  compare,
		    gpointer      key  )
{
  gint cmp;  

  GTreeNode *prenode = NULL;    
  
  if (!node)
    return NULL;    

  while(1)
  {

  cmp = (* compare) (key, node->key);  

  if (cmp == 0)
    return node->value;	  

	if (cmp < 0)
	{
		if (node->left)
		{
			prenode = node;
			
			node = node->left;
		} 
		else
		{
			return node->value;
		}
	}
	else if (cmp > 0)
	{
		if (node->right)
		{			
			node = node->right;
		}
		else
		{
			if (prenode)
			{
				return prenode->value;
			}
			else
			{
				return NULL;
			}
		}
		
	}
  }

  return NULL;
}


