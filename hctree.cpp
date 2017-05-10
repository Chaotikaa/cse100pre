#include "hctree.h"

/*hctree::hctree(hcnode * hnl, hctree * htr) {
	root = get_hc_node(hnl->weight + htr->weight);
	root->left = hnl;
	root->right = htr->root;
}

hctree::hctree(hcnode * hnl, hcnode *hnr) {
	root = get_hc_node(hnl->weight + hnr->weight);
	root->left = hnl;
	root->right = hnr;
}*/

// Combines 
void hctree::combine_as_left(hctree * ht) {
	if (ht) {
		hcnode * this_root = root;
		root = get_hc_node('\0', weight + ht->weight);
		root->left = this_root;
		if (root->left)
		root->left->update_bit_rep("0", keys);
		root->right = ht->root;
		if (root->right)
		root->right->update_bit_rep("1", keys);
		weight = root->weight;
	}

}


/*void hctree::combine_as_left(hcnode * hn) {
	hcnode * this_root = root;
	root = get_hc_node(weight + hn->weight);
	root->left = this_root;
	root->right = hn;
}*/