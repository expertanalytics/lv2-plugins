Clone the repo
```
git clone ...
```

# Install requirements:

## for Linux

install lv2core and lv2-dev:
```
apt install lv2core lv2-dev
```

## for mac

Installation of lv2core is the same as for Linux.

When building and installing your own LV2 plugins using waflib you need pkg-config installed. Run
```
brew update
brew install pkg-config
```

In addition, when building your own LV2-plugins, 
many hosts look for plugins in the standard folder "Library/Audio/Plug-Ins/LV2". 
To make waflib install your plugin in that location,
set the environment variable "LV2_PATH".
So either in the command line or in your ~/.bash_profile file:
```
export LV2_PATH="/Library/Audio/Plug-Ins/LV2"
```
**Note:** This requires installing with sudo rights, so you need to run
```
sudo python waf
```
after configuring.

# configure waf
```
python waf configure
```

# build plugin 
cd into the plugin folder
```
cd simple_delay
```

trigger the build
```
python waf
```

# Installation

## on linux 
LV2-plugins are folders/directories. They need to be installed in either /usr/lib/lv2, /usr/local/lib/lv2
```
sudo cp -r build/simple_delay.lv2/ /usr/local/lib/lv2
```

# Check LV2_PATH
```
echo $LV2_PATH
```
if not set make sure to set it to at least
```
export LV2_PATH=/usr/lib/lv2:/usr/local/lib/lv2
```
Now the plugin should be available in Ardour
if not uncheck hidden

