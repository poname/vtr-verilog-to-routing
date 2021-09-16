#ifndef CLEAN_H
#define CLEAN_H


//============================================================================================
//				INCLUDES
//============================================================================================

#include "vqm2blif_util.h"
#include "lut_recog.h"
#include "vqm_common.h"

//============================================================================================
//				GLOBALS
//============================================================================================

extern int buffer_count, invert_count, onelut_count;
extern int buffers_elim, inverts_elim, oneluts_elim;

void netlist_cleanup (t_module* module);

void remove_node ( t_node* node, t_node** nodes, int original_num_nodes );

void reorganize_module_node_list(int original_number_of_nodes, int number_of_nodes_eliminated, t_node** module_node_list, t_module* module);

//============================================================================================
//				STRUCTURES & TYPEDEFS
//============================================================================================
typedef enum d_type {NODRIVE, BUFFER, INVERT, BLACKBOX, CONST} drive_type;

typedef struct s_net{

	t_pin_def* pin;
	int bus_index;
	int wire_index;

	void* source;
	drive_type driver;

	t_node* block_src;

	int num_children;

} t_net;

typedef vector<t_net> netvec;
typedef vector<netvec> busvec;

//============================================================================================
//				CLEANUP DEFINES
//============================================================================================

//#define CLEAN_DEBUG	//dumps intermediate output files detailing the netlist as it is cleaned

#endif


