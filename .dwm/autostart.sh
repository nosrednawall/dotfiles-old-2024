#!/bin/bash
#pgrep -x dwmblocks > /dev/null || dwmblocks &
pgrep -x dwmbar-colored > /dev/null || bash ~/.local/bin/statusbar/dwmbar-colored &
