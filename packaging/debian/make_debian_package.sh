#!/bin/bash

# Where is the player built with QtCreator?
build=$HOME/Miam-Player-build

# Current release
version=0.6.3

# Temporary folder
mkdir $HOME/miam-player_$version
dest=$HOME/miam-player_$version

# Copy the binary file and shared libs:
cp -f $build/MiamCore/libMiamCore.so* ./miam-player/usr/lib/
cp -f $build/MiamUniqueLibrary/libMiamUniqueLibrary.so* ./miam-player/usr/lib/
cp -f $build/MiamPlayer/MiamPlayer ./miam-player/usr/bin/

# Rename executable (lowercase)
cp $build/MiamPlayer/MiamPlayer ./miam-player/usr/bin/miamplayer

# Prepare final copy
cp -Rf ./miam-player/* $dest/

# Update the control file
sed -i "s/Version: /Version: $version/g" $dest/DEBIAN/control

# Change chmod
chmod 755 $dest/DEBIAN/p*
chmod 644 $dest/usr/lib/*
chmod 755 $dest/usr/bin/*

# Change chown
chown root:root $dest/usr/lib/*
chown root:root $dest/usr/bin/*

# Create package
dpkg-deb --build $dest

chmod 777 $dest.deb

# Clean temporary folder
rm -rf $dest

# Clean other directories
rm -f ./miam-player/usr/bin/*
rm -f ./miam-player/usr/lib/*
