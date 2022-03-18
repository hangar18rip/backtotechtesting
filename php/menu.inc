<?php
//*****************************************************************************
// Copyright 2003-2006 by A J Marston <http://www.tonymarston.net>
// Distributed under the GNU General Public Licence
//*****************************************************************************

//*****************************************************************************
// This contains settings that in my main application are obtained from the
// the MENU database. As this sample aplication has no such database the
// settings must be done manually
//*****************************************************************************

// define the top-level buttons in the menu bar
$menu_buttons = array();
$menu_buttons['person']    = array('button_text' => 'Person', 'task_id' => 'person_list.php');
$menu_buttons['pers_type'] = array('button_text' => 'Person Type', 'task_id' => 'pers_type_list.php');
$menu_buttons['option']    = array('button_text' => 'Option', 'task_id' => 'option_list.php');
$menu_buttons['tree_type'] = array('button_text' => 'Tree Type', 'task_id' => 'tree_type_list.php');

if (!isset($table_id)) {
    $table_id = $outer_table;
} // if
// set one of these buttons as 'active'
switch ($table_id) {
	case 'x_option':
		$menu_buttons['option']['active'] = 'y';
		break;
	case 'person':
		$menu_buttons['person']['active'] = 'y';
		break;
    case 'pers_type':
		$menu_buttons['pers_type']['active'] = 'y';
		break;
	case 'tree_type':
    case 'tree_level':
    case 'tree_node':
    case 'tree_node_snr_s01':
		$menu_buttons['tree_type']['active'] = 'y';
		break;
    default:
		;
} // switch

// in the following array there is one entry for each script ....
// $title       = the form title
// $button_text = the breadcrumb area of the navigation bar
// $nav_buttons = array of optional navigation buttons
switch (basename($_SERVER['PHP_SELF'])) {
    case 'filepicker.php':
        $title         = 'Choose Picture';
        $button_text   = 'Choose Picture';
        break;
	case 'option_list.php':
        $title         = 'List OPTION';
		$button_text   = 'Option';
        $nav_buttons[] = array('button_text' => 'New', 'task_id' => 'option_add.php', 'context_preselect' => 'N');
        $nav_buttons[] = array('button_text' => 'Read', 'task_id' => 'option_enq.php', 'context_preselect' => 'Y');
        $nav_buttons[] = array('button_text' => 'Update', 'task_id' => 'option_upd.php', 'context_preselect' => 'Y');
        $nav_buttons[] = array('button_text' => 'Delete', 'task_id' => 'option_del.php', 'context_preselect' => 'Y');
        $nav_buttons[] = array('button_text' => 'Maintain Person', 'task_id' => 'pers_opt_xref_link(b).php', 'context_preselect' => 'Y');
        $nav_buttons[] = array('button_text' => 'List Person', 'task_id' => 'pers_opt_xref_list(b).php', 'context_preselect' => 'Y');
        $nav_buttons[] = array('button_text' => 'Search', 'task_id' => 'option_search.php', 'context_preselect' => 'N');
		break;
	case 'option_add.php':
		$title         = 'Insert OPTION';
        $button_text   = 'New';
		break;
	case 'option_del.php':
		$title         = 'Delete OPTION';
        $button_text   = 'Delete';
		break;
    case 'option_enq.php':
		$title         = 'Enquire OPTION';
        $button_text   = 'Read';
		break;
    case 'option_popup.php':
		$title         = 'Choose OPTION';
        $button_text   = 'Choose';
		break;
    case 'option_search.php':
		$title         = 'Search OPTION';
        $button_text   = 'Search';
		break;
    case 'option_upd.php':
		$title         = 'Update OPTION';
        $button_text   = 'Update';
		break;
    case 'person_list.php':
		$title         = 'List PERSON';
        $button_text   = 'Person';
        $nav_buttons[] = array('button_text' => 'New', 'task_id' => 'person_add.php', 'context_preselect' => 'N');
        $nav_buttons[] = array('button_text' => 'Read', 'task_id' => 'person_enq.php', 'context_preselect' => 'Y');
        $nav_buttons[] = array('button_text' => 'Update', 'task_id' => 'person_upd.php', 'context_preselect' => 'Y');
        $nav_buttons[] = array('button_text' => 'Delete', 'task_id' => 'person_del.php', 'context_preselect' => 'Y');
        $nav_buttons[] = array('button_text' => 'Search', 'task_id' => 'person_search.php', 'context_preselect' => 'N');
        $nav_buttons[] = array('button_text' => 'Maintain Options', 'task_id' => 'pers_opt_xref_link(a).php', 'context_preselect' => 'Y');
        $nav_buttons[] = array('button_text' => 'List Options', 'task_id' => 'pers_opt_xref_list(a).php', 'context_preselect' => 'Y');
		break;
    case 'person_list(a).php':
		$title         = 'List PERSON by PERSON TYPE';
        $button_text   = 'Person';
        $nav_buttons[] = array('button_text' => 'New', 'task_id' => 'person_add.php', 'context_preselect' => 'N');
        $nav_buttons[] = array('button_text' => 'Read', 'task_id' => 'person_enq.php', 'context_preselect' => 'Y');
        $nav_buttons[] = array('button_text' => 'Update', 'task_id' => 'person_upd.php', 'context_preselect' => 'Y');
        $nav_buttons[] = array('button_text' => 'Delete', 'task_id' => 'person_del.php', 'context_preselect' => 'Y');
        $nav_buttons[] = array('button_text' => 'Search', 'task_id' => 'person_search.php', 'context_preselect' => 'N');
		break;
    case 'person_add.php':
		$title         = 'Insert PERSON';
        $button_text   = 'New';
		break;
    case 'person_del.php':
		$title         = 'Delete PERSON';
        $button_text   = 'Delete';
		break;
    case 'person_enq.php':
		$title         = 'Enquire PERSON';
        $button_text   = 'Read';
		break;
    case 'person_popup.php':
		$title         = 'Choose PERSON';
        $button_text   = 'Choose';
		break;
    case 'person_search.php':
		$title         = 'Search PERSON';
        $button_text   = 'Search';
		break;
    case 'person_upd.php':
		$title         = 'Update PERSON';
        $button_text   = 'Update';
		break;
    case 'pers_opt_xref_list(a).php':
		$title         = 'List OPTION by PERSON';
        $button_text   = 'List Options';
		break;
    case 'pers_opt_xref_list(b).php':
		$title         = 'List PERSON by OPTION';
        $button_text   = 'List Person';
		break;
    case 'pers_opt_xref_add(a).php':
		$button_text   = 'New';
		break;
    case 'pers_opt_xref_add(b).php':
		$button_text   = 'New';
		break;
    case 'pers_opt_xref_link(a).php':
		$title         = 'Maintain OPTION by PERSON';
        $button_text   = 'Maintain Options';
        $nav_buttons[] = array('button_text' => 'Search', 'task_id' => 'option_search.php', 'context_preselect' => 'N');
		break;
    case 'pers_opt_xref_link(b).php':
		$title         = 'Maintain PERSON by OPTION';
        $button_text   = 'Maintain Person';
        $nav_buttons[] = array('button_text' => 'Search', 'task_id' => 'person_search.php', 'context_preselect' => 'N');
		break;
    case 'pers_type_list.php':
		$title         = 'List PERSON TYPE';
        $button_text   = 'Person Type';
        $nav_buttons[] = array('button_text' => 'New', 'task_id' => 'pers_type_add.php', 'context_preselect' => 'N');
        $nav_buttons[] = array('button_text' => 'Read', 'task_id' => 'pers_type_enq.php', 'context_preselect' => 'Y');
        $nav_buttons[] = array('button_text' => 'Update', 'task_id' => 'pers_type_upd.php', 'context_preselect' => 'Y');
        $nav_buttons[] = array('button_text' => 'Delete', 'task_id' => 'pers_type_del.php', 'context_preselect' => 'Y');
        $nav_buttons[] = array('button_text' => 'Person', 'task_id' => 'person_list(a).php', 'context_preselect' => 'Y');
        $nav_buttons[] = array('button_text' => 'Search', 'task_id' => 'pers_type_search.php', 'context_preselect' => 'N');
		break;
    case 'pers_type_add.php':
		$title         = 'Insert PERSON TYPE';
        $button_text   = 'New';
		break;
    case 'pers_type_del.php':
		$title         = 'Delete PERSON TYPE';
        $button_text   = 'Delete';
		break;
    case 'pers_type_enq.php':
		$title         = 'Enquire PERSON TYPE';
        $button_text   = 'Read';
		break;
    case 'pers_type_search.php':
		$title         = 'Search PERSON TYPE';
        $button_text   = 'Search';
		break;
    case 'pers_type_upd.php':
		$title         = 'Update PERSON TYPE';
        $button_text   = 'Update';
		break;
    case 'tree_type_list.php':
		$title         = 'List TREE TYPE';
        $button_text   = 'Tree Type';
        $nav_buttons[] = array('button_text' => 'New', 'task_id' => 'tree_type_add.php', 'context_preselect' => 'N');
        $nav_buttons[] = array('button_text' => 'Read', 'task_id' => 'tree_type_enq.php', 'context_preselect' => 'Y');
        $nav_buttons[] = array('button_text' => 'Update', 'task_id' => 'tree_type_upd.php', 'context_preselect' => 'Y');
        $nav_buttons[] = array('button_text' => 'Delete', 'task_id' => 'tree_type_del.php', 'context_preselect' => 'Y');
        $nav_buttons[] = array('button_text' => 'Tree Level', 'task_id' => 'tree_level_list.php', 'context_preselect' => 'Y');
        $nav_buttons[] = array('button_text' => 'Tree Structure', 'task_id' => 'tree_structure_list.php', 'context_preselect' => 'Y');
        $nav_buttons[] = array('button_text' => 'Search', 'task_id' => 'tree_type_search.php', 'context_preselect' => 'N');
		break;
    case 'tree_type_add.php':
		$title         = 'Insert TREE_TYPE';
        $button_text   = 'New';
		break;
    case 'tree_type_del.php':
		$title         = 'Delete TREE_TYPE';
        $button_text   = 'Delete';
		break;
    case 'tree_type_enq.php':
        $title         = 'Enquire TREE_TYPE';
		$button_text   = 'Read';
		break;
    case 'tree_type_search.php':
		$title         = 'Search TREE_TYPE';
        $button_text   = 'Search';
		break;
    case 'tree_type_upd.php':
		$title         = 'Update TREE_TYPE';
        $button_text   = 'Update';
		break;
    case 'tree_level_list.php':
		$title         = 'List TREE LEVEL';
        $button_text   = 'Tree Level';
        $nav_buttons[] = array('button_text' => 'New', 'task_id' => 'tree_level_add.php', 'context_preselect' => 'N');
        $nav_buttons[] = array('button_text' => 'Read', 'task_id' => 'tree_level_enq.php', 'context_preselect' => 'Y');
        $nav_buttons[] = array('button_text' => 'Update', 'task_id' => 'tree_level_upd.php', 'context_preselect' => 'Y');
        $nav_buttons[] = array('button_text' => 'Delete', 'task_id' => 'tree_level_del.php', 'context_preselect' => 'Y');
        $nav_buttons[] = array('button_text' => 'Update Seq No', 'task_id' => 'tree_level_multi.php', 'context_preselect' => 'N');
        $nav_buttons[] = array('button_text' => 'Nodes', 'task_id' => 'tree_node_list.php', 'context_preselect' => 'Y');
        $nav_buttons[] = array('button_text' => 'Search', 'task_id' => 'tree_level_search.php', 'context_preselect' => 'N');
		break;
    case 'tree_level_add.php':
		$title         = 'Insert TREE LEVEL';
        $button_text   = 'New';
		break;
    case 'tree_level_del.php':
		$title         = 'Delete TREE LEVEL';
        $button_text   = 'Delete';
		break;
    case 'tree_level_enq.php':
		$title         = 'Enquire TREE LEVEL';
        $button_text   = 'Read';
		break;
    case 'tree_level_multi.php':
		$title         = 'Update TREE LEVEL SEQ';
        $button_text   = 'Update Seq No';
		break;
    case 'tree_level_search.php':
		$title         = 'Search TREE LEVEL';
        $button_text   = 'Search';
		break;
    case 'tree_level_upd.php':
		$title         = 'Update TREE LEVEL';
        $button_text   = 'Update';
		break;
    case 'tree_node_list.php':
		$title         = 'List TREE NODE';
        $button_text   = 'Tree Node';
        $nav_buttons[] = array('button_text' => 'New', 'task_id' => 'tree_node_add.php', 'context_preselect' => 'N');
        $nav_buttons[] = array('button_text' => 'Read', 'task_id' => 'tree_node_enq.php', 'context_preselect' => 'Y');
        $nav_buttons[] = array('button_text' => 'Update', 'task_id' => 'tree_node_upd.php', 'context_preselect' => 'Y');
        $nav_buttons[] = array('button_text' => 'Delete', 'task_id' => 'tree_node_del.php', 'context_preselect' => 'Y');
        $nav_buttons[] = array('button_text' => 'Parent Nodes', 'task_id' => 'tree_node_snr_list.php', 'context_preselect' => 'Y');
        $nav_buttons[] = array('button_text' => 'Child Nodes', 'task_id' => 'tree_node_jnr_list.php', 'context_preselect' => 'Y');
        $nav_buttons[] = array('button_text' => 'Search', 'task_id' => 'tree_node_search.php', 'context_preselect' => 'N');
		break;
    case 'tree_node_add.php':
		$title         = 'Insert TREE NODE';
        $button_text   = 'New';
		break;
    case 'tree_node_del.php':
		$title         = 'Delete TREE NODE';
        $button_text   = 'Delete';
		break;
    case 'tree_node_enq.php':
		$title         = 'Enquire TREE NODE';
        $button_text   = 'Read';
		break;
    case 'tree_node_search.php':
		$title         = 'Search TREE_NODE';
        $button_text   = 'Search';
		break;
    case 'tree_node_upd':
		$title         = 'Update TREE NODE';
        $button_text   = 'Update';
		break;
    case 'tree_node_snr_list.php':
		$title         = 'List NODE Parentage';
        $button_text   = 'Parent Nodes';
		break;
    case 'tree_node_jnr_list.php':
		$title         = 'List NODE Children';
        $button_text   = 'Child Nodes';
        $nav_buttons[] = array('button_text' => 'Link Children', 'task_id' => 'tree_node_jnr_add.php', 'context_preselect' => 'N');
        $nav_buttons[] = array('button_text' => 'Unlink Children', 'task_id' => 'tree_node_jnr_del.php', 'context_preselect' => 'Y');
        $nav_buttons[] = array('button_text' => 'Search', 'task_id' => 'tree_node_search.php', 'context_preselect' => 'N');
		break;
    case 'tree_node_jnr_add.php':
		$button_text   = 'Link Children';
		break;
    case 'tree_node_jnr_popup.php':
		$title         = 'Choose Orphan NODE';
        $button_text   = 'Choose Node';
        $nav_buttons[] = array('button_text' => 'New', 'task_id' => 'tree_node_add.php', 'context_preselect' => 'N');
        $nav_buttons[] = array('button_text' => 'Delete', 'task_id' => 'tree_node_del.php', 'context_preselect' => 'Y');
		break;
    case 'tree_structure_list.php':
		$title         = 'List TREE Structure';
        $button_text   = 'Structure';
        $nav_buttons[] = array('button_text' => 'Read', 'task_id' => 'tree_node_enq.php', 'context_preselect' => 'Y');
		break;
    case 'tree_structure_popup.php':
		$title         = 'Choose from TREE Structure';
        $button_text   = 'Choose';
		break;
    default:
		$title         = 'unknown';
        $button_text   = 'unknown';
} // switch

?>