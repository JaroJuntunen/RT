/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yaxml.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 09:27:01 by mmakinen          #+#    #+#             */
/*   Updated: 2022/11/29 09:27:37 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef YAXML_H
# define YAXML_H

# include <fcntl.h>
# include "libft.h"

# ifndef TRUE
#  define TRUE 1
# endif

# ifndef FALSE
#  define FALSE 0
# endif

typedef enum e_tag_type
{
	TAG_START,
	TAG_INLINE
}	t_tag_type;

typedef struct s_xml_attribute
{
	char	*key;
	char	*value;
}	t_xml_attr;

typedef struct s_xml_attribute_list
{
	int			memory_size;
	int			size;
	t_xml_attr	*list;
}	t_xml_attrlist;

typedef struct s_xml_node_list
{
	int					memory_size;
	int					size;
	struct s_xml_node	**list;
}	t_xml_nodelist;

typedef struct s_xml_node
{
	char				*tag;
	char				*data;
	struct s_xml_node	*parent;
	t_xml_nodelist		children;
	t_xml_attrlist		attributes;
}	t_xml_node;

typedef struct s_xml_document
{
	t_xml_node	*head;
	char		*version;
	char		*encoding;
}	t_xml_doc;

typedef struct s_buffers
{
	char	*mem;
	char	lex[1024];
	size_t	buff_len;
}	t_buffers;

/* XML doc */
int				xml_doc_load(t_xml_doc *doc, const char *path);
int				xml_comment(t_buffers *buf, int *index);
int				xml_declaration(t_buffers *buf, int *index, t_xml_doc *doc);
int				xml_start_tag(t_buffers *buf, int index[2], t_xml_node **node);

/* File handling */
size_t			xml_get_size(const char *path);
int				xml_read_file(t_buffers *buf, const char *path);

/* Utility function */
int				xml_return_error(const char *str);
int				xml_error_free(t_buffers *buf, char *err_str);

/* Free allocated memory */
void			xml_attr_free(t_xml_attr *attr);
void			xml_nodelist_free(t_xml_nodelist *list);
void			xml_node_free(t_xml_node *node);
void			xml_doc_free(t_xml_doc *doc);

/* Re-allocate memory for lists*/
void			*xml_resize_memory(void *ptr, size_t size, size_t old_size);

/* Node functions */
t_xml_node		*xml_node_new(t_xml_node *parent);
t_xml_node		*xml_node_child(t_xml_node *parent, int index);
t_xml_nodelist	*xml_node_children(t_xml_node *parent, const char *tag);
char			*xml_node_attr_value(t_xml_node *node, char *key);
t_xml_attr		*xml_node_attr(t_xml_node *node, char *key);
t_xml_node		*xml_node_tag(t_xml_nodelist *list, char *tag);

/* List functions */
int				xml_attrlist_init(t_xml_attrlist *list);
int				xml_attrlist_add(t_xml_attrlist *list, t_xml_attr *attr);
int				xml_nodelist_init(t_xml_nodelist *list);
int				xml_nodelist_add(t_xml_nodelist *list, t_xml_node *node);
t_xml_node		*xml_nodelist_at(t_xml_nodelist *list, int index);
t_tag_type		xml_parse_attr(t_buffers *buf, int index[2], \
				t_xml_node *current_node);
#endif