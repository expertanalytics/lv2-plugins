#!/bin/bash
# Function for expanding manifest.ttl.in based on template in
# plugin_template/manifest.ttl.in
expand_manifest() {
        echo "INSIDE expand_manifest\n"
        sed -e 's/@PLUGIN_NAME@/'$1'/g' -e 's/@LIB_EXT@/'$2'/g' plugin_template/manifest.ttl.in
        echo "LEAVING expand_manifest\n"
}

case "$1" in
        --help|-h)
                echo "'$0' -m <PLUGIN_NAME> <LIB_EXT> to expand manifest file."
                echo "'$0' -t <PLUGIN_NAME> to expand plugin turtle file."
        ;;
        -m)
                expand_manifest $2 $3
        ;;
        -t)
                break
        ;;
        *)
                break
        ;;
esac

