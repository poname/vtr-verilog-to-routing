#ifndef RR_GRAPH_BUILDER_H
#define RR_GRAPH_BUILDER_H

#include "rr_graph_storage.h"
#include "rr_spatial_lookup.h"

/* A data structure allows data modification on a routing resource graph 
 *
 * Note that the builder does not own the storage
 * It serves a virtual protocol for
 * - node_storage: store the node list 
 * - node_lookup: store a fast look-up for the nodes
 *
 * Note:
 * - This is the only data structre allowed to modify a routing resource graph
 *
 */
class RRGraphBuilder {
    /* -- Constructors -- */
  public:
    /* See detailed comments about the data structures in the internal data storage section of this file */
    RRGraphBuilder(t_rr_graph_storage* node_storage,
                   RRSpatialLookup* node_lookup);

    /* Disable copy constructors and copy assignment operator
     * This is to avoid accidental copy because it could be an expensive operation considering that the 
     * memory footprint of the data structure could ~ Gb
     * Using the following syntax, we prohibit accidental 'pass-by-value' which can be immediately caught 
     * by compiler
     */
    RRGraphBuilder(const RRGraphBuilder&) = delete;
    void operator=(const RRGraphBuilder&) = delete;

    /* -- Mutators -- */
  public:
    /* Return a writable object for rr_nodes */
    t_rr_graph_storage& node_storage();
    /* Return a writable object for update the fast look-up of rr_node */
    RRSpatialLookup& node_lookup();
    /* Add an existing rr_node in the node storage to the node look-up
     * The node will be added to the lookup for every side it is on (for OPINs and IPINs) 
     * and for every (x,y) location at which it exists (for wires that span more than one (x,y)).
     * This function requires a valid node which has already been allocated in the node storage, with
     * - a valid node id
     * - valid geometry information: xlow/ylow/xhigh/yhigh
     * - a valid node type
     * - a valid node ptc number
     * - a valid side (applicable to OPIN and IPIN nodes only
     */
    void add_node_to_all_locs(RRNodeId node);

    /* -- Internal data storage -- */
  private:
    /* TODO: When the refactoring effort finishes, 
     * the builder data structure will be the owner of the data storages. 
     * That is why the reference to storage/lookup is used here.
     * It can avoid a lot of code changes once the refactoring is finished 
     * (there is no function get data directly through the node_storage in DeviceContext).
     * If pointers are used, it may cause many codes in client functions 
     * or inside the data structures to be changed later.
     * That explains why the reference is used here temporarily
     */
    /* node-level storage including edge storages */
    t_rr_graph_storage& node_storage_;
    /* Fast look-up for rr nodes */
    RRSpatialLookup& node_lookup_;
};

#endif
