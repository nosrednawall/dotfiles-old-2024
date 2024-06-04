

# DWM Configuration Keybindings

This document details all the keybindings configured for DWM (Dynamic Window Manager).

## General Keybindings

| Key Combination                  | Action                                         |
|----------------------------------|------------------------------------------------|
| `MODKEY + p`                     | Launch `dmenu_run`                             |
| `MODKEY + Shift + Return`        | Launch `st` (simple terminal)                  |
| `MODKEY + Shift + b`             | Toggle status bar                              |
| `MODKEY + Shift + c`             | Kill the focused window                        |
| `MODKEY + Tab`                   | Switch to the previously selected workspace    |
| `MODKEY + Shift + q`             | Quit dwm                                       |
| `MODKEY + Shift + r`             | Restart dwm                                    |

## Scratchpad Keybindings

| Key Combination                  | Action                                         |
|----------------------------------|------------------------------------------------|
| `MODKEY + s`                     | Toggle scratchpad terminal                     |
| `MODKEY + r`                     | Toggle scratchpad file manager (`ranger`)      |
| `MODKEY + b`                     | Toggle scratchpad `bitwarden`                  |
| `MODKEY + a`                     | Toggle scratchpad `pulsemixer`                 |
| `MODKEY + h`                     | Toggle scratchpad `btop`                       |
| `MODKEY + n`                     | Toggle scratchpad `nmtui`                      |
| `MODKEY + m`                     | Toggle scratchpad `ncmpcpp`                    |
| `MODKEY + c`                     | Toggle scratchpad `whatsapp-chrome`            |
| `MODKEY + y`                     | Toggle scratchpad `ytfzf`                      |

## Window Management Keybindings

| Key Combination                  | Action                                         |
|----------------------------------|------------------------------------------------|
| `MODKEY + Right`                 | Focus next window                              |
| `MODKEY + Left`                  | Focus previous window                          |
| `MODKEY + Shift + Up`            | Increase number of master windows              |
| `MODKEY + Shift + Down`          | Decrease number of master windows              |
| `MODKEY + Up`                    | Decrease master area size                      |
| `MODKEY + Down`                  | Increase master area size                      |
| `MODKEY + Return`                | Move focused window to master area             |
| `MODKEY + Space`                 | Toggle between tiling and floating layouts     |
| `MODKEY + Shift + Space`         | Toggle floating state of focused window        |
| `MODKEY + 0`                     | View all windows                               |
| `MODKEY + Shift + 0`             | Move focused window to all workspaces          |
| `MODKEY + ,`                     | Focus previous monitor                         |
| `MODKEY + .`                     | Focus next monitor                             |
| `MODKEY + Shift + ,`             | Move focused window to previous monitor        |
| `MODKEY + Shift + .`             | Move focused window to next monitor            |

## Tagging Keybindings

| Key Combination                  | Action                                         |
|----------------------------------|------------------------------------------------|
| `MODKEY + 1-5`                   | View tag (workspace) 1-5                       |
| `MODKEY + Control + 1-5`         | Toggle view tag 1-5                            |
| `MODKEY + Shift + 1-5`           | Move focused window to tag 1-5                 |
| `MODKEY + Control + Shift + 1-5` | Toggle focused window on tag 1-5               |

## Layout Keybindings

| Key Combination                  | Action                                         |
|----------------------------------|------------------------------------------------|
| `MODKEY + F1`                    | Set layout to tile                             |
| `MODKEY + F2`                    | Set layout to centered floating master         |
| `MODKEY + F3`                    | Set layout to centered master                  |
| `MODKEY + F4`                    | Set layout to monocle                          |
| `MODKEY + F5`                    | Set layout to spiral                           |
| `MODKEY + F6`                    | Set layout to dwindle                          |
| `MODKEY + F7`                    | Set layout to deck                             |
| `MODKEY + F8`                    | Set layout to bstack                           |
| `MODKEY + F9`                    | Set layout to bstack horizontal                |
| `MODKEY + F10`                   | Set layout to grid                             |
| `MODKEY + F11`                   | Set layout to nrowgrid                         |
| `MODKEY + F12`                   | Set layout to horizgrid                        |
| `MODKEY + Shift + F1`            | Set layout to gapless grid                     |
| `MODKEY + Shift + F2`            | Set layout to floating                         |

## Gaps Management Keybindings

| Key Combination                  | Action                                         |
|----------------------------------|------------------------------------------------|
| `MODKEY + Shift + h`             | Increase window size factor                    |
| `MODKEY + Shift + l`             | Decrease window size factor                    |
| `MODKEY + Shift + o`             | Reset window size factor                       |
| `MODKEY + Mod1 + u`              | Increase all gaps                              |
| `MODKEY + Mod1 + Shift + u`      | Decrease all gaps                              |
| `MODKEY + Mod1 + i`              | Increase inner gaps                            |
| `MODKEY + Mod1 + Shift + i`      | Decrease inner gaps                            |
| `MODKEY + Mod1 + o`              | Increase outer gaps                            |
| `MODKEY + Mod1 + Shift + o`      | Decrease outer gaps                            |
| `MODKEY + Mod1 + 6`              | Increase horizontal inner gaps                 |
| `MODKEY + Mod1 + Shift + 6`      | Decrease horizontal inner gaps                 |
| `MODKEY + Mod1 + 7`              | Increase vertical inner gaps                   |
| `MODKEY + Mod1 + Shift + 7`      | Decrease vertical inner gaps                   |
| `MODKEY + Mod1 + 8`              | Increase horizontal outer gaps                 |
| `MODKEY + Mod1 + Shift + 8`      | Decrease horizontal outer gaps                 |
| `MODKEY + Mod1 + 9`              | Increase vertical outer gaps                   |
| `MODKEY + Mod1 + Shift + 9`      | Decrease vertical outer gaps                   |
| `MODKEY + Mod1 + 0`              | Toggle gaps on/off                             |
| `MODKEY + Mod1 + Shift + 0`      | Reset gaps to default                          |

## Custom Keybindings

| Key Combination                  | Action                                         |
|----------------------------------|------------------------------------------------|
| `Control + Mod1 + l`             | Lock screen (slock personalizado)              |
| `Caps_Lock`                      | Play sound for Caps Lock                       |
| `Num_Lock`                       | Play sound for Num Lock                        |
| `Scroll_Lock`                    | Play sound for Scroll Lock                     |
| `MODKEY + k`                     | Change keyboard layout                         |

## Media Keybindings

### Volume Control

| Key Combination                  | Action                                         |
|----------------------------------|------------------------------------------------|
| `XF86AudioLowerVolume`           | Decrease volume                                |
| `XF86AudioRaiseVolume`           | Increase volume                                |
| `XF86AudioMute`                  | Mute volume                                    |
| `Control + XF86AudioRaiseVolume` | Increase microphone volume                     |
| `Control + XF86AudioLowerVolume` | Decrease microphone volume                     |
| `Control + XF86AudioMute`        | Mute microphone                                |

### Music Player Control

| Key Combination                  | Action                                         |
|----------------------------------|------------------------------------------------|
| `XF86AudioPlay`                  | Play/Pause music                               |
| `XF86AudioStop`                  | Stop music                                     |
| `XF86AudioPrev`                  | Previous track                                 |
| `XF86AudioNext`                  | Next track                                     |

### Miscellaneous

| Key Combination                  | Action                                         |
|----------------------------------|------------------------------------------------|
| `XF86HomePage`                   | Open homepage                                  |
| `XF86Mail`                       | Open mail program                              |
| `XF86Search`                     | Open search program                            |
| `XF86Calculator`                 | Open calculator                                |

### Print Screen

| Key Combination                  | Action                                         |
|----------------------------------|------------------------------------------------|
| `MODKEY + Shift + s`             | Take a screenshot and edit                     |
| `Print`                          | Take a screenshot and copy to clipboard        |

### Screen Brightness

| Key Combination                  | Action                                         |
|----------------------------------|------------------------------------------------|
| `XF86MonBrightnessUp`            | Increase screen brightness                     |
| `XF86MonBrightnessDown`          | Decrease screen brightness                     |

## Dmenu Keybindings

| Key Combination                  | Action                                         |
|----------------------------------|------------------------------------------------|
| `MODKEY + Shift + e`             | Open system exit menu                          |
| `Control + Mod1 + p`             | Open password manager menu                     |
| `MODKEY + Shift + p`             | Open pomodoro timer menu                       |
| `MODKEY + Shift + w`             | Open monitor control menu                      |
| `MODKEY + Shift + a`             | Open sound control menu                        |
| `MODKEY + Shift + y`             | Open YouTube menu                              |
| `MODKEY + d`                     | Open custom rofi menu                          |

## Application Launchers

| Key Combination                  | Action                                         |
|----------------------------------|------------------------------------------------|
| `MODKEY + w`                     | Launch Google Chrome                           |
| `MODKEY + e`                     | Launch VSCode                                  |
| `MODKEY + q`                     | Launch Emacs                                   |
| `MODKEY + f`                     | Launch Thunar file manager                     |
| `MODKEY + i`                     | Launch Flameshot                               |
| `MODKEY + z`                     | Launch Zotero                                  |

## Workspace Management

| Key Combination                  | Action                                         |
|----------------------------------|------------------------------------------------|
| `MODKEY + o`                     | Move window to scratchpad                      |

This file provides a comprehensive list of all the keybindings configured in your `dwm` setup. These keybindings offer efficient navigation, window management, workspace management, and quick access to frequently used applications and functions.
