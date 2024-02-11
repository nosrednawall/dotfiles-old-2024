#!/bin/bash
# TODO: FAZER ALGO
# JAVA Bug
if which wmname; then
  wmname LG3D
fi
export AWT_TOOLKIT="MToolkit"
export _JAVA_AWT_WM_NONREPARENTING="1"
