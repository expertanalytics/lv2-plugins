#!/bin/bash

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

cp -r plugin_template ${base_folder}
mv ${base_folder}/template.ttl ${base_folder}/${snake_var}.ttl
mv ${base_folder}/template.c ${base_folder}/${snake_var}.c

sed -i 's/\<TypeNamePlaceholder\>/'${pascal_var}'/g' ${base_folder}/${snake_var}.c
sed -i 's/\<TypeNamePlaceholder\>/'${pascal_var}'/g' ${base_folder}/${snake_var}.ttl
sed -i 's/\<plugin_name_placeholder\>/'${snake_var}'/g' ${base_folder}/${snake_var}.c
sed -i 's/\<plugin_name_placeholder\>/'${snake_var}'/g' ${base_folder}/${snake_var}.ttl
sed -i 's/\<plugin_name_placeholder\>/'${snake_var}'/g' ${base_folder}/manifest.ttl.in
