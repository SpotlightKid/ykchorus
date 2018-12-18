#!/bin/bash -e

PLUGIN_NAME=ykchorus
PLUGIN_VERSION=$(grep d_version plugins/YKChorus/PluginYKChorus.hpp | sed -E 's/.*([0-9]+), ([0-9]+), ([0-9]+).*/\1.\2.\3/g')
TARBALL_NAME="$PLUGIN_NAME-v$PLUGIN_VERSION-source.tar.gz"
REPO_URL=https://github.com/SpotlightKid/$PLUGIN_NAME.git

rm -rf "$PLUGIN_NAME"
git clone --recursive "$REPO_URL" --branch "v$PLUGIN_VERSION" --single-branch
cd "$PLUGIN_NAME"
find . -name ".git" -type f -delete
rm -rf .git
find . -name ".gitmodules" -type f -delete
cd ..
tar -zcvf "$TARBALL_NAME" "$PLUGIN_NAME/"
rm -rf "$PLUGIN_NAME/"

gpg --armor --detach-sign "$TARBALL_NAME"
