from xml.dom import minidom

def get_xml_node(node, name):
    return node.getElementsByTagName(name) if node else []

def get_node_value(node, index = 0):
    return node.childNodes[index].nodeValue if node else ''

#get mach-header-flags-array
def get_xml_data(filename='./macho_const.xml'):
    doc = minidom.parse(filename)
    root = doc.documentElement

    macho_head_node = get_xml_node(root, 'macho-head')
    flag_node = get_xml_node(macho_head_node[0], 'flags')
    data_nodes = get_xml_node(flag_node[0], 'data')

    mach_head_flags_array = []

    for node in data_nodes:
        key = get_xml_node(node, 'key')
        value = get_xml_node(node, 'value')

        flag_obj = {}

        flag_obj['key'] = get_node_value(key[0]).encode('UTF-8')
        flag_obj['value'] = get_node_value(value[0]).encode('UTF-8')
        mach_head_flags_array.append(flag_obj)

    return mach_head_flags_array

def generate_mach_flags_mapping(array):
    file_handler = open("./macho_mappping.h", "w")
    file_handler.write("//the file is generated by python script, DO NOT EDIT\n\n\n")
    file_handler.write("#ifndef MACHO_MAPPING\n")
    file_handler.write("#define MACHO_MAPPING\n")
    file_handler.write("#include <map>\n")
    file_handler.write("#include <string>\n")
    file_handler.write("\n\n")
    file_handler.write("std::map<uint32_t, std::string> macho_mapping;\n")

    for node in array:
        file_handler.write("macho_mapping[")
        file_handler.write(node["value"])
        file_handler.write("]\t\t=\tstd::string(\"")
        file_handler.write(node["key"])
        file_handler.write("\");\n")

    file_handler.write("\n#endif")
    file_handler.close()
    pass

def load_xml():
    array = get_xml_data('./macho_const.xml')
    generate_mach_flags_mapping(array)

if __name__ == "__main__":
    load_xml()
