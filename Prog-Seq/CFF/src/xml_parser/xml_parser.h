#ifndef _XML_PARSER_H_
#define _XML_PARSER_H_

#include <libxml/parser.h>
#include <libxml/tree.h>
#include "../vector_list/connection_list.h"
#include "../vector_list/city_list.h"
#include "../matrix/matrix.h"
#include "limits.h" // pour avoir INT_MAX

/** append to list of cities those found in xml
 *
 * @param a_node a xml node
 */
void ville_xml_parser(xmlNode * a_node, lst_city* v);

/** add edges to graph based on links found in xml
 *
 * @param a_node link (liaison) xml node
 */
void graph_xml_parser(xmlNode * a_node, lst_city* v, lst_connection* tab, matrix* mat);

int read_xml(const char * filename, lst_city* v, lst_connection** tab, matrix* mat);
int get_index(char* name, lst_city* v);

matrix convert_lst_to_matrix(lst_connection** v, lst_city * v2);
lst_connection* convert_matrix_to_lst(matrix* mat, lst_city* v2);

#endif
