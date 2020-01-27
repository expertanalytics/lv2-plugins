#!/usr/local/bin/bash

# Script for generating lv2 templates and plugin project folder.
# The name of the project is taken as input.

plugin_name_input=$1
snake_var=${plugin_name_input,,}
pascal_var=""

IFS='_' read -ra ADDR <<< ${snake_var}
for i in "${ADDR[@]}"; do
    pascal_var+=${i^}
done

base_folder=${snake_var}
[ ! -d "${snake_var}" ] && mkdir -p "${base_folder}"

cp plugin_template/{template.ttl,template.c,version.txt,manifest.ttl.in}  ${base_folder}
mv ${base_folder}/template.ttl ${base_folder}/${snake_var}.ttl
mv ${base_folder}/template.c ${base_folder}/${snake_var}.c
mv ${base_folder}/manifest.ttl.in ${base_folder}/manifest.ttl

# Get library file extension based on os:
if [[ "$OSTYPE" == "darwin"* ]]; then
        lib_ext="dylib"
else
        lib_ext="so"
fi

sed -i '' 's/\<TypeNamePlaceholder\>/'${pascal_var}'/g' ${base_folder}/${snake_var}.c
sed -i '' 's/\<TypeNamePlaceholder\>/'${pascal_var}'/g' ${base_folder}/${snake_var}.ttl
sed -i '' 's/plugin_name_placeholder/'${snake_var}'/g' ${base_folder}/${snake_var}.c
sed -i '' 's/plugin_name_placeholder/'${snake_var}'/g' ${base_folder}/${snake_var}.ttl
sed -i '' 's/PLUGIN_NAME_PLACEHOLDER/'${snake_var^^}'/g' ${base_folder}/${snake_var}.c
sed -i '' 's/@PLUGIN_NAME@/'${snake_var}'/g' ${base_folder}/manifest.ttl
sed -i '' 's/@LIB_EXT@/'${lib_ext}'/g' ${base_folder}/manifest.ttl

# Add line to CMakeLists.txt
sed -i '' '/^\# END of list of plugins/i\
            add_plugin\('${snake_var}'\)
' CMakeLists.txt
