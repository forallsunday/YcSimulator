/*
 * xml_api.c
 *
 *  Created on: 2019年10月22日
 *      Author: notebook
 */

#include "xml_api.h"
#include "rapidxml.hpp"
#include "xml_printf.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

using namespace rapidxml;

#define XML_NODE_CAST(node) static_cast<xml_document<> *>(node)

#define API_NODE_CAST(node) static_cast<xml_node_type>(node)

#define XML_ATTRIBUTE_CAST(node) static_cast<xml_attribute<> *>(node)

#define API_ATTRIBUTE_CAST(node) static_cast<xml_attribute_type>(node)

// 打开xml文件，文件节点，
int open_xml_file(const char *file_name, xml_doc_type *p_doc) {
    FILE *fp = NULL;
    //    struct stat stat_buf;
    xml_document<> *xdoc = NULL;
    int             size;
    int             len;

    if ((NULL == file_name) || ((NULL == p_doc))) {
        return -1;
    }

    xdoc = new xml_document<>();
    if (NULL == xdoc) {
        return -1;
    }

    //    if (stat(file_name, &stat_buf) < 0)
    //    {
    //        return -1;
    //    }

    // 读取xml文件
    fp = fopen(file_name, "r");
    if (NULL == fp) {
        ERROR_PRINT("Open [%s] failed", file_name);

        delete xdoc;
        return -1;
    }

    fseek(fp, 0L, SEEK_END);

    size = ftell(fp);

    fseek(fp, 0L, SEEK_SET);

    p_doc->text = (char *)malloc(size + 1);
    if (NULL == p_doc->text) {
        fclose(fp);
        delete xdoc;
        return -1;
    }

    memset(p_doc->text, 0, size + 1);

    len = fread(p_doc->text, 1, size, fp);
    if (len != size) {
        //        printf("Read %s failed, read len:%d\n", file_name, len);
        fclose(fp);

        ERROR_PRINT("Read [%s] failed", file_name);

        delete xdoc;
        return -1;
    }
    fclose(fp);

    xdoc->parse<0>(p_doc->text);
    p_doc->doc_node = API_NODE_CAST(xdoc);

    return 0;
}

void close_xml_file(xml_doc_type *doc) {
    xml_document<> *xdoc = XML_NODE_CAST(doc->doc_node);

    delete xdoc;
    xdoc = NULL;

    delete doc->text;
    doc->text = NULL;
}

xml_node_type get_root_node(xml_doc_type *p_doc) {
    xml_document<> *xdoc = XML_NODE_CAST(p_doc->doc_node);

    return API_NODE_CAST(xdoc->first_node());
}

char *get_node_value(xml_node_type node) {
    xml_node<> *xnode = XML_NODE_CAST(node);
    return xnode->value();
}

// 返回第一个name指定的兄弟节点，name为NULL，则返回第一个兄弟节点
xml_node_type get_next_sibling_node(xml_node_type node, const char *name) {
    xml_node<> *xnode = XML_NODE_CAST(node);
    return API_NODE_CAST(xnode->next_sibling(name));
}

// 返回第一个name指定的子节点，name为NULL，则返回第一个子节点
xml_node_type get_first_child_node(xml_node_type node, const char *name) {
    xml_node<> *xnode = XML_NODE_CAST(node);
    return API_NODE_CAST(xnode->first_node(name));
}

// 返回name指定的子节点个数，name为NULL，则返回所有子节点个数
int get_child_node_count(xml_node_type node, const char *name) {
    int         node_count  = 0;
    xml_node<> *xnode       = XML_NODE_CAST(node);
    xml_node<> *child_xnode = xnode->first_node(name);

    while (0 != child_xnode) {
        node_count++;

        child_xnode = child_xnode->next_sibling(name);
    }

    return node_count;
}

// 返回第一个name指定名称的属性，name为NULL，则返回第一个属性
xml_attribute_type get_first_attribute(xml_node_type node, const char *name) {
    xml_node<> *xnode = XML_NODE_CAST(node);

    return API_ATTRIBUTE_CAST(xnode->first_attribute(name));
}

// 返回下一个name指定名称的属性，name为NULL，则返回第一个属性
xml_attribute_type get_next_attribute(xml_attribute_type attribute, const char *name) {
    xml_attribute<> *xattribute = XML_ATTRIBUTE_CAST(attribute);

    return API_ATTRIBUTE_CAST(xattribute->next_attribute(name));
}

char *get_attribute_value(xml_attribute_type attribute) {
    xml_attribute<> *xattribute = XML_ATTRIBUTE_CAST(attribute);
    return xattribute->value();
}

// 属性值为整型
long int get_attribute_int_value(xml_attribute_type attribute, int base) {
    xml_attribute<> *xattribute = XML_ATTRIBUTE_CAST(attribute);
    char            *value      = xattribute->value();
    char            *end        = NULL;
    return strtol(value, &end, base);
}

// 返回第一个name指定名称的属性，name为NULL，则返回第一个属性
char *get_first_attribute_value(xml_node_type node, const char *name) {
    xml_node<> *xnode = XML_NODE_CAST(node);

    return xnode->first_attribute(name)->value();
}

// 返回第一个name指定名称的属性，name为NULL，则返回第一个属性
long int get_first_attribute_int_value(xml_node_type node, const char *name, int base) {
    xml_node<> *xnode = XML_NODE_CAST(node);
    char       *value = xnode->first_attribute(name)->value();
    char       *end   = NULL;

    if (NULL == value) {
        return -1;
    }

    return strtol(value, &end, base);
}

// 返回第一个name指定名称的属性，name为NULL，则返回第一个属性
bool get_first_attribute_bool_value(xml_node_type node, const char *name) {
    xml_node<> *xnode = XML_NODE_CAST(node);
    char       *value = xnode->first_attribute(name)->value();
    if (0 == strcmp(value, "true") || 0 == strcmp(value, "TRUE") || 0 == strcmp(value, "True")) {
        return TRUE;
    } else {
        return FALSE;
    }
}

// 返回第一个name指定名称的属性，name为NULL，则返回第一个属性
long int get_first_attribute_str_or_int_value(xml_node_type node, const char *name, const char *special_str, int default_value, int base) {
    char       *end   = NULL;
    xml_node<> *xnode = XML_NODE_CAST(node);
    char       *value = xnode->first_attribute(name)->value();
    if (0 == strcmp(value, special_str)) {
        return default_value;
    } else {
        return strtol(value, &end, base);
    }
}

// 返回第一个name指定名称的属性，name为NULL，则返回第一个属性
double get_first_attribute_double_value(xml_node_type node, const char *name) {
    xml_node<> *xnode = XML_NODE_CAST(node);
    char       *value = xnode->first_attribute(name)->value();

    return atof(value);
}

xml_node_type get_root_node(const char *cfg_file, xml_doc_type *p_doc) {
    xml_doc_type  doc;
    xml_node_type root_node;

    if (open_xml_file(cfg_file, &doc) < 0) {
        ERROR_PRINT("Open XML[%s] failed", cfg_file);
        return NULL;
    }

    // 获取root接点
    root_node = get_first_child_node(doc.doc_node, NULL);
    if (NULL == root_node) {
        close_xml_file(&doc);

        ERROR_PRINT("Get XML[%s] root node failed", cfg_file);

        return NULL;
    }

    *p_doc = doc;

    return root_node;
}

/*
 * 按指定子节点个数分配空间，并返回分配的空间（已经清零），分配空间大小=node_size*子节点个数
 * node：父节点
 * name：子节点名称
 * node_size：每个字节分配空间大小
 * p_node_count：子节点数
 */
char *malloc_by_child_node(xml_node_type node, const char *name, int node_size, int *p_node_count) {
    int   child_node_count;
    char *node_buf = NULL;

    // 获取子节点个数
    child_node_count = get_child_node_count(node, name);
    if (child_node_count < 0) {
        return NULL; // 没子节点
    }

    // 分配空间
    node_buf = (char *)malloc(node_size * child_node_count);
    if (NULL == node_buf) {
        return NULL;
    }

    memset(node_buf, 0, (node_size * child_node_count));

    if (NULL != p_node_count) {
        *p_node_count = child_node_count;
    }

    return node_buf;
}
